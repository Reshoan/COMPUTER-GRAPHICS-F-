#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

using namespace std;

void drawRectangle(float x1, float y1, float x2, float y2) {
    glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

void drawRotatedRectangle(float cx, float cy, float w, float h, float angle) {
    float rad = angle * 3.14159 / 180.0;
    float hw = w / 2.0;
    float hh = h / 2.0;

    float vertices[4][2] = {
        {-hw, -hh},
        { hw, -hh},
        { hw,  hh},
        {-hw,  hh}
    };

    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        float xr = x * cos(rad) - y * sin(rad);
        float yr = x * sin(rad) + y * cos(rad);
        glVertex2f(cx + xr, cy + yr);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0); // Black

    // Body
    drawRectangle(-0.3, -0.1, 0.3, 0.2);

    // Legs
    drawRectangle(-0.25, -0.5, -0.15, -0.1);
    drawRectangle( 0.15, -0.5,  0.25, -0.1);

    // Head (rectangle tilted left)
    drawRotatedRectangle(-0.45, 0.25, 0.3, 0.2, -35);

    // Tail (rectangle tilted right)
    drawRotatedRectangle(0.45, 0.15, 0.25, 0.1, 30);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Primitive Dog Shape");

    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
