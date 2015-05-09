from pyglet.gl import glClear, GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT
from Quaternion import Quaternion
from RpiModel import RpiModel


class World():
    def __init__(self):
        self.gyro_input_model = RpiModel(Quaternion(1., 0., 0., 0.), y_offset=-3)
        self.bias_model = RpiModel(Quaternion(1., 0., 0., 0.), y_offset=3)

    def draw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        self.gyro_input_model.draw()
        self.bias_model.draw()