from math import sqrt, acos, cos, sin
import os
import socket
import struct

from pyglet import clock, font, image, window
from pyglet.gl import *
import sys


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

        #top
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
        self.fps = clock.ClockDisplay()

    def draw(self):
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        self.fps.draw()

class Network():
    #ip = '127.0.0.1'
    ip = '192.168.137.2'
    port = 5001

    def __init__(self, callback_func):
        self.reply = bytes()
        self.callback_func = callback_func
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.setblocking(False)
            self.socket.connect((self.ip, self.port))
        except ConnectionRefusedError:
            print("Connection to server refused")
            self.socket = None
        except BlockingIOError:
             pass


    def tick(self):
        try:
            if self.socket:
                self.reply = self.reply + self.socket.recv(100)

            while self.reply:
                header_size = struct.calcsize("II")
                (length, cmd) = struct.unpack("II", self.reply[0:header_size])
                print("-------Reply:")
                print("Length: %i" % (length))
                print("Cmd: %i" % (cmd))

                if cmd == 1:
                    struct_type = str(length) + "s"
                    msg = struct.unpack(struct_type, self.reply[header_size:header_size + length])[0]
                    msg_size = struct.calcsize(struct_type)
                    print("Msg: " + str(msg))
                elif cmd == 2:
                    struct_type = "fff"
                    (f1, f2, f3) = struct.unpack(struct_type, self.reply[header_size:header_size + length])
                    msg_size = struct.calcsize(struct_type)
                    print("F1: %.2f" % (f1))
                    print("F2: %.2f" % (f2))
                    print("F3: %.2f" % (f3))
                elif cmd == 3:
                    struct_type = "ffff"
                    (w, x, y, z) = struct.unpack(struct_type, self.reply[header_size:header_size + length])
                    msg_size = struct.calcsize(struct_type)
                    print("F1: %.2f" % (w))
                    print("F2: %.2f" % (x))
                    print("F3: %.2f" % (y))
                    print("F4: %.2f" % (z))
                    self.callback_func(w, x, y, z)

                self.reply = self.reply[header_size + msg_size:]
        except BlockingIOError:
            pass


class App():
    def __init__(self):
        self.world = World()
        self.win = window.Window(fullscreen=False, vsync=True, resizable=True)

        self.network = Network(self.world.cube.update_quat)
        self.camera = Camera(self.win, z=4)
        self.hud = Hud()

        self.init_gl()

        clock.set_fps_limit(60)

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

            clock.tick()
            self.win.flip()

try:
    app = App()
    app.main_loop()
except Exception as err:
    print("Unknown exception")
    exc_type, exc_obj, exc_tb = sys.exc_info()
    fname = os.path.split(exc_tb.tb_frame.f_code.co_filename)[1]
    print(exc_type, fname, exc_tb.tb_lineno)