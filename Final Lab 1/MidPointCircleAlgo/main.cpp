#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

int X, Y, R; // Circle center and radius

void plotPoints(int xc, int yc, int x, int y)
{
    glBegin(GL_POINTS);

    // 8-way symmetry
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);

    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);

    glEnd();
}

void drawMidpointCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r; // initial decision parameter

    plotPoints(xc, yc, x, y);

    while (x < y)
    {
        if (d < 0)
        {
            d = d + (2 * x + 3);
        }
        else
        {
            d = d + (2 * (x - y) + 5);
            y--;
        }
        x++;
        plotPoints(xc, yc, x, y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(0, 200, 0);
    drawMidpointCircle(X, Y, R);

    glFlush();
}

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // background white
    glColor3ub(0, 200, 0);            // circle color green
    glPointSize(4.0);                 // pixel size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200); // coordinate system
}

int main(int argc, char** argv)
{
    cout << "Enter Circle Center (X Y): ";
    cin >> X >> Y;
    cout << "Enter Circle Radius: ";
    cin >> R;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Midpoint Circle Algorithm");

    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
}
