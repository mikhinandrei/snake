//
// Created by Admin on 06.11.2016.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#endif //SNAKE_SNAKE_H

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Gl/glut.h>

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
    private:
    int x, y;

    public:
    Fruit();
    void draw_fruit();
    void reload();
    void remove();
};

class Snake{
    private:
    short dead;
    Fruit* f;
    vector<point> coordinates;
    point np;

    public:
    Snake();
    point next_point(int);
    void move();
    void draw();
    void eat();
    void die();
};

void press_key(int, int, int);
void display();
