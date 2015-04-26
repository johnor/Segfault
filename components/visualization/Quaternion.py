from math import acos, sqrt
from pyglet.gl import glRotatef


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