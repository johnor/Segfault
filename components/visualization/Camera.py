from pyglet.gl import *


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