import pyglet.clock
from pyglet.gl import glMatrixMode, GL_MODELVIEW, glLoadIdentity


class Hud():
    def __init__(self):
        self.fps = pyglet.clock.ClockDisplay()

    def draw(self):
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        self.fps.draw()