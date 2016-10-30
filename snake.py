from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import random
import sys
import time

M = 15        # размеры поля (в квадратиках)
N = 10

SCALE = 20         # величина квадратика

WIDTH = SCALE * (M+1)
HEIGHT = SCALE * (N+1)

START_LEN = 4

direction = 'right'

class Fruit():
    global M
    global N
    global SCALE
    def __init__(self):
        self.x = random.randrange(M)
        self.y = random.randrange(N)

    def draw_fruit(self):
        glColor3ub(255, 255, 0)
        glRectf(self.x* SCALE, (self.y + 1)* SCALE, (self.x + 1)* SCALE, self.y* SCALE)

    def remove(self):
        glColor3f(0.0, 0.0, 0.0)
        glRectf(self.x * SCALE, (self.y + 1) * SCALE, (self.x + 1) * SCALE, self.y * SCALE)

    def reload(self):
        self.remove()
        self.x = random.randrange(M)
        self.y = random.randrange(N)
        self.draw_fruit()

class Snake():
    global M
    global N
    global SCALE
    global direction

    def __init__(self):
        self.dead = 0
        self.f = Fruit()
        self.coordinates = [[M//2 + 2, N//2], [M//2 + 1, N//2], [M//2, N//2], [M//2 - 1, N//2]]
        self.np = self.next_point(direction)


    def next_point(self, direction):
        if direction == 'right':
            return [self.coordinates[0][0] + 1, self.coordinates[0][1]]
        if direction == 'left':
            return [self.coordinates[0][0] - 1, self.coordinates[0][1]]
        if direction == 'up':
            return [self.coordinates[0][0], self.coordinates[0][1] + 1]
        if direction == 'down':
            return [self.coordinates[0][0], self.coordinates[0][1] - 1]

    def move(self):
        time.sleep(0.15)
        self.np = self.next_point(direction)
        if self.np[0] < 0 or self.np[0] > M or self.np[1] < 0 or self.np[1] > N:
            self.die()
            return
        if self.np in self.coordinates[:-1]:
            self.die()
        else:
            if self.np[0] == self.f.x and self.np[1] == self.f.y:
                self.eat(self.f)
            else:
                self.coordinates = self.coordinates[:-1]
                self.coordinates.insert(0, self.np)
        glutPostRedisplay()

    def draw(self):
        glClear(GL_COLOR_BUFFER_BIT)
        for [x, y] in self.coordinates:
            glColor3ub(255, 156, 30)
            glRectf(x * SCALE, (y+1)* SCALE, (x+1)* SCALE, y* SCALE)
        self.f.draw_fruit()
        glFlush()
        if self.dead == 0:
            self.move()

    def eat(self, f):
        self.coordinates = [[f.x, f.y]] + self.coordinates
        f.reload()
        while [f.x, f.y] in self.coordinates:
            f.reload()

    def die(self):
        self.dead = 1
        print("You die")
        glutPostRedisplay()


def press_key(key, x, y):
    global direction
    if key == GLUT_KEY_UP:
        direction = 'up'
    if key == GLUT_KEY_DOWN:
        direction = 'down'
    if key == GLUT_KEY_LEFT:
        direction = 'left'
    if key == GLUT_KEY_RIGHT:
        direction = 'right'


def display():
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3ub(255, 255, 255)
    glRectf(-0.1, 0.4, 0.0, 0.2)
    glFlush()

if __name__ == '__main__':
    glutInit(sys.argv)

    snake = Snake()

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(WIDTH, HEIGHT)
    glutCreateWindow(b"Snake")

    glClearColor(0, 0, 0, 0)

    gluOrtho2D(0, WIDTH, 0, HEIGHT)

    glutSpecialFunc(press_key)
    glutDisplayFunc(snake.draw)

    glutMainLoop()