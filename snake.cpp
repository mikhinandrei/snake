//
// Created by Admin on 06.11.2016.
//

#include "snake.h"
#include <cstdlib>
#include <ctime>

Fruit::Fruit(){
    srand(time(0));
    x = rand() % M;
    y = rand() % N;
}

void Fruit::draw_fruit(){
    glColor3ub(255, 255, 0);
    glRectf(x * SCALE, (y + 1) * SCALE, (x+1) * SCALE, y * SCALE);
}

void Fruit::remove(){
    glColor3f(0,0,0);
    glRectf(x * SCALE, (y + 1) * SCALE, (x + 1) * SCALE, y * SCALE);
}

void Fruit::reload(){
    remove();
    srand(time(0));
    x = rand() % M;
    y = rand() % N;
    draw_fruit();
}

Snake::Snake(){
    direction = 1;
    dead = 0;
    f = new Fruit();
    coordinates = {{M/2 + 2, N/2}, {M/2 + 1, N/2}, {M/2, N/2}, {M/2 - 1, N/2}};
    np = next_point(direction);
}

point Snake::next_point(int dir){
    switch (dir){
        case 0: return {coordinates[0].x, coordinates[0].y + 1};
        case 1: return {coordinates[0].x + 1, coordinates[0].y};
        case 2: return {coordinates[0].x, coordinates[0].y - 1};
        case 3: return {coordinates[0].x - 1, coordinates[0].y};
    }
}

