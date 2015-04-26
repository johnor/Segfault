from pyglet.gl import glClear, GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT
from Quaternion import Quaternion
from RpiModel import RpiModel


class World():
    def __init__(self):
        self.cube = RpiModel(Quaternion(1., 0., 0., 0.))

    def draw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        self.cube.draw()