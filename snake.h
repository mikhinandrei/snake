//
// Created by Admin on 06.11.2016.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#endif //SNAKE_SNAKE_H

#define GLUT_DISABLE_ATEXIT_HACK

#pragma comment(lib, "glut32.lib")


#include <deque>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int M = 15;
const int N = 10;

const int SCALE = 20;

int WIDTH =  M * SCALE;
int HEIGHT = N * SCALE;

short direction;

using namespace std;

struct point {
    int x;
    int y;
};

class Fruit{
    public:
    int x, y;
    Fruit();
    void draw_fruit();
    void reload();
    void remove();
};

class Snake{
    private:
    point np;
    short dead;
    Fruit* f;
    deque<point> coordinates;

    public:
    Snake();
    point next_point(int);
    void move();
    void draw();
    void eat(Fruit *f);
    void die();
};

void press_key(int, int, int);
