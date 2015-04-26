from pyglet.gl import glPushMatrix, glBegin, GL_QUADS, glColor3f, glVertex3f, glEnd, glPopMatrix
from Quaternion import Quaternion


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