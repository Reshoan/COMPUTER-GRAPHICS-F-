#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float angle = 175.0f;

void drawCircle(float cx, float cy, float r, int num_segments = 100) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the car body (polygon)
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(-1.0f, 0.5f);//A
        glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex2f(-1.0f, -0.5f);//B
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex2f(1.0f, -0.5f);//C
        glColor3f(1.0f, 0.0f, 1.0f); // Blue
        glVertex2f(1.0f, 0.0f);//D
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
        glVertex2f(0.5f, 0.5f);//E
    glEnd();

    // Draw wheels (filled circles)
    glColor3f(0.0f, 1.0f, 0.0f); // Black wheels
    drawCircle(-0.5f, -0.5f, 0.25f); // Left wheel
    drawCircle(0.5f, -0.5f, 0.25f);  // Right wheel

    // Apply transformations
    glTranslatef(3.0f, -4.0f, 0.0f); // Translation
    glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotation
    glScalef(0.3f, 0.4f, 1.0f); // Scaling



    // Draw the car body (polygon)
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(-1.0f, 0.5f);//A
        glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex2f(-1.0f, -0.5f);//B
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex2f(1.0f, -0.5f);//C
        glColor3f(1.0f, 0.0f, 1.0f); // Blue
        glVertex2f(1.0f, 0.0f);//D
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
        glVertex2f(0.5f, 0.5f);//E
    glEnd();

    // Draw wheels (filled circles)
    glColor3f(0.0f, 1.0f, 0.0f); // Black wheels
    drawCircle(-0.5f, -0.5f, 0.25f); // Left wheel
    drawCircle(0.5f, -0.5f, 0.25f);  // Right wheel

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0); // 2D Orthographic projection
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Car with Wheels");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
