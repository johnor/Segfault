from argparse import ArgumentParser
from math import sqrt, acos
import socket
import struct
import traceback
import sys

import pyglet.clock
from pyglet import window
from pyglet.gl import *


class Quaternion():
    def __init__(self, w, x, y, z):
        self.q = (w, x, y, z)

    def set_rotation(self):
        w, x, y, z = self.q
        l = 1. / self.norm()
        glRotatef(acos(w) * 360. / 3.14159, x * l, y * l, z * l)

    def norm(self):
        mag_sqr = sum(n * n for n in self.q)
        length = sqrt(mag_sqr)
        return length


class RpiModel():
    width = 1
    height = 0.2
    length = 2

    def __init__(self, quaternion):
        self.quaternion = quaternion

    def update_quat(self, w, x, y, z):
        self.quaternion = Quaternion(w, x, y, z)

    def draw(self):
        glPushMatrix()
        self.quaternion.set_rotation()

        glBegin(GL_QUADS)

        # top
        glColor3f(1.0, 0.0, 0.0)
        glVertex3f(self.length, self.width, self.height)
        glVertex3f(-self.length, self.width, self.height)
        glVertex3f(-self.length, -self.width, self.height)
        glVertex3f(self.length, -self.width, self.height)

        #bottom
        glColor3f(1.0, 1.0, 0.0)
        glVertex3f(self.length, -self.width, -self.height)
        glVertex3f(-self.length, -self.width, -self.height)
        glVertex3f(-self.length, self.width, -self.height)
        glVertex3f(self.length, self.width, -self.height)

        #left
        glColor3f(0.0, 1.0, 0.0)
        glVertex3f(self.length, self.width, -self.height)
        glVertex3f(-self.length, self.width, -self.height)
        glVertex3f(-self.length, self.width, self.height)
        glVertex3f(self.length, self.width, self.height)

        #right
        glColor3f(1.0, 0.5, 0.0)
        glVertex3f(self.length, -self.width, -self.height)
        glVertex3f(-self.length, -self.width, -self.height)
        glVertex3f(-self.length, -self.width, self.height)
        glVertex3f(self.length, -self.width, self.height)

        #front
        glColor3f(0.0, 0.0, 1.0)
        glVertex3f(-self.length, self.width, self.height)
        glVertex3f(-self.length, self.width, -self.height)
        glVertex3f(-self.length, -self.width, -self.height)
        glVertex3f(-self.length, -self.width, self.height)

        #back
        glColor3f(1.0, 0.0, 1.0)
        glVertex3f(self.length, self.width, self.height)
        glVertex3f(self.length, self.width, -self.height)
        glVertex3f(self.length, -self.width, -self.height)
        glVertex3f(self.length, -self.width, self.height)
        glEnd()

        glPopMatrix()


class World():
    def __init__(self):
        self.cube = RpiModel(Quaternion(1., 0., 0., 0.))

    def draw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        self.cube.draw()


class Camera():
    def __init__(self, win, x=-10.0, y=0.0, z=0.0, rot=0.0):
        self.win = win
        self.x = x
        self.y = y
        self.z = z
        self.rot = rot

    def perspective_projection(self):
        glViewport(0, 0, self.win.width, self.win.height)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(60.0, self.win.width / self.win.height, 0.1, 200.0)

    def hud_projection(self):
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluOrtho2D(0, self.win.width, 0, self.win.height)

    def setup_modelview_matrix(self):
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        gluLookAt(self.x, self.y, self.z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0)


class Hud():
    def __init__(self):
        self.fps = pyglet.clock.ClockDisplay()

    def draw(self):
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        self.fps.draw()


class Network():
    def __init__(self, ip, port, callback_func):
        print("Connecting to ip: {0}, port: {1}".format(ip, port))
        self.ip = ip
        self.port = port

        self.socket = None

        self.reply = bytes()
        self.callback_func = callback_func

        self.header_format = "II"
        self.header_size = struct.calcsize(self.header_format)

        self.connect()

    def tick(self):
        try:
            if self.socket:
                self.reply = self.reply + self.socket.recv(100)

            while len(self.reply) > self.header_size:
                header_data = self.reply[0:self.header_size]
                (body_length_from_header, command) = struct.unpack(self.header_format, header_data)
                # print("-------Reply:")
                # print("Length: %i" % (body_length_from_header))
                # print("Cmd: %i" % (command))

                struct_type, body_length = self.get_msg_type_and_length(command)

                if len(self.reply) > body_length_from_header + self.header_size:
                    body_data = self.reply[self.header_size:self.header_size + body_length_from_header]

                    if command == 2:
                        (f1, f2, f3) = struct.unpack(struct_type, body_data)
                        body_length = struct.calcsize(struct_type)
                        print("F1: %.2f" % (f1))
                        print("F2: %.2f" % (f2))
                        print("F3: %.2f" % (f3))
                    elif command == 3:
                        (w, x, y, z) = struct.unpack(struct_type, body_data)

                        # print("F1: %.2f" % (w))
                        # print("F2: %.2f" % (x))
                        # print("F3: %.2f" % (y))
                        # print("F4: %.2f" % (z))
                        self.callback_func(w, x, y, z)
                    else:
                        raise SystemExit("Command not supported")

                    self.reply = self.reply[self.header_size + body_length:]
                else:
                    break
        except BlockingIOError:
            pass
        except socket.error as e:
            # print("Unknown socket error: {0}".format(str(e).encode('UTF-8')))
            self.connect()

    def connect(self):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.setblocking(False)
            self.socket.connect((self.ip, self.port))
        except ConnectionRefusedError:
            print("Connection to server refused")
            self.socket = None
        except BlockingIOError:
            pass

    @staticmethod
    def get_msg_type_and_length(command):
        if command == 2:
            struct_type = "fff"
        elif command == 3:
            struct_type = "ffff"
        else:
            struct_type = None

        if struct_type is None:
            return struct_type, 0

        msg_size = struct.calcsize(struct_type)
        return struct_type, msg_size


class App():
    def __init__(self, port, ip):
        self.world = World()
        self.win = window.Window(fullscreen=False, vsync=True, resizable=True)

        self.network = Network(ip=ip, port=port, callback_func=self.world.cube.update_quat)
        self.camera = Camera(self.win, z=4)
        self.hud = Hud()

        self.init_gl()

        pyglet.clock.set_fps_limit(60)

    @staticmethod
    def init_gl():
        glClearColor(0.0, 0.0, 0.0, 0.0)
        glClearDepth(1.0)
        glDepthFunc(GL_LESS)
        glEnable(GL_DEPTH_TEST)
        glShadeModel(GL_SMOOTH)

    def main_loop(self):
        while not self.win.has_exit:
            self.win.dispatch_events()

            self.network.tick()

            self.camera.perspective_projection()
            self.camera.setup_modelview_matrix()
            self.world.draw()

            self.camera.hud_projection()
            self.hud.draw()

            pyglet.clock.tick()
            self.win.flip()


if __name__ == "__main__":
    parser = ArgumentParser()

    parser.add_argument("--ip", default="127.0.0.1", help="Ip to connect to")
    parser.add_argument("--port", "-p", default=5001, type=int, help="Port to use")

    args = parser.parse_args()

    try:
        app = App(ip=args.ip, port=args.port)
        app.main_loop()
    except struct.error as err:
        print("Struct error: " + str(err))
    except Exception as err:
        print("Unknown exception: ")
        traceback.print_exc(file=sys.stdout)
