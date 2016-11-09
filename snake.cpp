//
// Created by Admin on 06.11.2016.
//

#include "snake.h"

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
    point p1 = {M/2 + 2, N/2};
    point p2 = {M/2 + 1, N/2};
    point p3 = {M/2, N/2};
    point p4 = {M/2 - 1, N/2};
    coordinates.push_back(p1);
    coordinates.push_back(p2);
    coordinates.push_back(p3);
    coordinates.push_back(p4);
    np = next_point(direction);
}

point Snake::next_point(int dir){
    point p1;
    switch (dir){
        case 0: p1.x = coordinates[0].x;
                p1.y = coordinates[0].y;
        case 1: p1.x = coordinates[0].x + 1;
                p1.y = coordinates[0].y;
        case 2: p1.x = coordinates[0].x;
                p1.y = coordinates[0].y - 1;
        case 3: p1.x = coordinates[0].x - 1;
                p1.y = coordinates[0].y;
    }
    return p1;
}

void Snake::move(){
    coordinates.pop_back();
    np = next_point(direction);
    if ((np.x < 0) || (np.x > M) || (np.y < 0) || (np.y > N)){
        die();
        return;
    }
    for(int i = 0; i < coordinates.size() - 1; i++){
        if ((np.x == coordinates[i].x) && (np.y == coordinates[i].y)){
            die();
            return;
        }
    }
    if ((np.x == f->x) && (np.y == f->y)){
        eat(f);
    }
    else{
        coordinates.pop_back();
        coordinates.push_front(np);
    }
}

void Snake::draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = 0; i < coordinates.size(); i++){
        glColor3ub(255, 156, 30);
        glRectf(coordinates[i].x * SCALE, (coordinates[i].y+1)* SCALE, (coordinates[i].x+1)* SCALE, coordinates[i].y* SCALE);
    }
    f->draw_fruit();
    glFlush();
    if (dead == 0){
        move();
    }
}

void Snake::eat(Fruit *f){
    point p = {f->x, f->y};
    coordinates.push_front(p);
    f->reload();
    //don`t forget
}

void Snake::die(){
    dead = 1;
    std::cout << "You die";
    glutPostRedisplay();
}

void press_key(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP: direction = 0;
        case GLUT_KEY_RIGHT: direction = 1;
        case GLUT_KEY_DOWN: direction = 2;
        case GLUT_KEY_LEFT: direction = 3;
    }
}