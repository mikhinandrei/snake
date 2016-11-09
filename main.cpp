#include "snake.h"
#include <windows.h>

void draw();
Snake *s;

int main(int argc, char * argv[]) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Snake");

    glClearColor(0, 0, 0, 0);

    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glutSpecialFunc(press_key);
    glutDisplayFunc(draw);

    glutMainLoop();

    return 0;
}

void draw(){
    s->Snake::draw();
}