import pyglet.clock
from pyglet.gl import glMatrixMode, GL_MODELVIEW, glLoadIdentity


class Hud():
    def __init__(self, win):
        self.fps = pyglet.clock.ClockDisplay()
        self.win = win

    def draw(self):
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        self.fps.draw()

        label = pyglet.text.Label('Bias model',
                                  font_name='Times New Roman',
                                  font_size=10,
                                  x=150, y=self.win.height - 50,
                                  anchor_x='left', anchor_y='top')
        label.draw()

        label = pyglet.text.Label('Gyro input model',
                                  font_name='Times New Roman',
                                  font_size=10,
                                  x=350, y=self.win.height - 50,
                                  anchor_x='left', anchor_y='top')
        label.draw()



