from argparse import ArgumentParser
import struct
import traceback
import sys

import pyglet.clock
from pyglet import window
from pyglet.gl import *

from Camera import Camera
from Hud import Hud
from Network import Network
from World import World


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
