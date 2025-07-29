#include<windows.h>
#include<iostream>
#include<math.h>
#include <stdio.h>
#include<GL/gl.h>
#include <GL/glut.h>

using namespace std;

int X1, Y1, X2, Y2, X3, Y3, X4, Y4;

void drawDDA(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    if (dx == 0) // vertical line
    {
        if (y1 > y2) swap(y1, y2);
        glBegin(GL_POINTS);
        glColor3ub(r, g, b);
        for (int y = y1; y <= y2; y++)
            glVertex2i(x1, y);
        glEnd();
        return;
    }

    float m = dy / dx;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    glColor3ub(r, g, b);

    if (fabs(m) <= 1)
    {
        if (x1 > x2) { x = x2; y = y2; dx = -dx; dy = -dy; }

        for (int i = 0; i <= abs(dx); i++)
        {
            glVertex2i(round(x), round(y));
            x += 1;
            y += m;
        }
    }
    else
    {
        if (y1 > y2) { x = x2; y = y2; dx = -dx; dy = -dy; }

        for (int i = 0; i <= abs(dy); i++)
        {
            glVertex2i(round(x), round(y));
            y += 1;
            x += 1 / m;
        }
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw coordinate axes
    glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex2f(-100, 0);
        glVertex2f(100, 0);
        glVertex2f(0, -100);
        glVertex2f(0, 100);
    glEnd();

    // Draw first line in red
    drawDDA(X1, Y1, X2, Y2, 255, 0, 0);

    // Draw second line in blue
    drawDDA(X3, Y3, X4, Y4, 0, 0, 255);

    glFlush();
}

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3ub(0, 200, 0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("DDA LINE");

    cout << "Enter line 1 initial points:\t";
    cin >> X1 >> Y1;
    cout << "Enter line 1 final points:\t";
    cin >> X2 >> Y2;
    cout << "Enter line 2 initial points:\t";
    cin >> X3 >> Y3;
    cout << "Enter line 2 final points:\t";
    cin >> X4 >> Y4;

    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
}
