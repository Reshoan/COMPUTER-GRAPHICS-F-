#include <windows.h> // for MS Windows
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <cstdlib>
#include <cmath>

// ---- Utility to draw a wheel ----
void drawWheel(float cx, float cy, float r) {
    int numSegments = 50;

    // Tire
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();

    // Spokes
    glBegin(GL_LINES);
    for (int i = 0; i < numSegments; i += 10) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx, cy);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// ---- Hood/Canopy ----
void drawCanopy() {
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.7f, 0.0f, 0.0f); // red hood
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(-0.19f, 1.5f);
        glVertex2f(-0.59f, 1.65f);
        glVertex2f(-0.93f, 1.67f);
        glVertex2f(-1.26f, 1.56f);
        glVertex2f(-1.43f, 1.37f);
        glVertex2f(-1.49f, 1.31f);
        glVertex2f(-1.45f, 0.80f);
    glEnd();


}

// ---- Seat ----
void drawSeat() {
    // base
    glColor3f(0.2f, 0.6f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-1.4f, 0.0f);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.2f, 0.3f);
        glVertex2f(-1.4f, 0.3f);
    glEnd();

    // backrest
    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.4f, 0.3f);
        glVertex2f(-0.2f, 0.3f);
        glVertex2f(-0.2f, 0.8f);
        glVertex2f(-1.4f, 0.8f);
    glEnd();
}

// ---- Frame with triangles ----
void drawFrame() {
    glColor3f(0.3f, 0.3f, 0.3f);

    glBegin(GL_TRIANGLES);
        // Rear triangle (wheel to seat)
        glVertex2f(-1.2f, -0.5f);  // rear wheel hub
        glVertex2f(-1.4f, 0.0f);   // seat base left
        glVertex2f(-0.8f, 0.0f);   // seat base mid


    glEnd();


}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Rear wheel (only one, side view)
    drawWheel(-1.2f, -0.5f, 0.35f);

    // Draw rickshaw parts
    drawFrame();
    drawSeat();
    drawCanopy();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2D Side View Rickshaw");

    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -1.5, 2.0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
