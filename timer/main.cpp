#include <windows.h>
#include <GL/glut.h>
#include <cmath>

// Motorcycle position
float motoX = -0.9f;  // starting at left edge
float speed = 0.01f;
bool legalScene = true;   // true = legal (slow lane), false = illegal (fast lane)
float wheelAngle = 0.0f;  // for rotating wheels

void initGL() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
}

void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawRoad() {
    // Road background
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.2f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(1.0f, -0.8f);
    glVertex2f(-1.0f, -0.8f);
    glEnd();

    // Lane divider
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(1.0f, -0.5f);
    glEnd();

    // Speed labels
    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(0.8f, -0.35f, "50");  // fast lane
    drawText(0.8f, -0.65f, "40");  // slow lane
}

void drawWheel(float x, float y, float radius) {
    // Tire
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x, y, radius);

    // Rim
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(x, y, radius * 0.6f);

    // Spokes (rotating)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 4; i++) {
        float angle = wheelAngle + i * 3.14159f / 2;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x, y);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawMotorcycle(float x, float y) {
    float rearWheelR = 0.12f;
    float frontWheelR = 0.1f;

    float rearWheelX = x - 0.2f;
    float frontWheelX = x + 0.25f;

    // Wheels
    drawWheel(rearWheelX, y, rearWheelR);
    drawWheel(frontWheelX, y, frontWheelR);

    // Frame (long chopper style)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex2f(rearWheelX, y);
    glVertex2f(x, y + 0.1f);         // to engine
    glVertex2f(x, y + 0.1f);
    glVertex2f(frontWheelX, y);      // to front wheel
    glEnd();

    // Gas Tank (classic Harley curve)
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.05f, y + 0.1f);
    glVertex2f(x + 0.05f, y + 0.1f);
    glVertex2f(x + 0.07f, y + 0.2f);
    glVertex2f(x - 0.07f, y + 0.2f);
    glEnd();

    // Seat (low cruiser seat)
    glColor3f(0.0f, 0.0f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.08f, y + 0.1f);
    glVertex2f(x + 0.02f, y + 0.1f);
    glVertex2f(x + 0.02f, y + 0.15f);
    glVertex2f(x - 0.08f, y + 0.15f);
    glEnd();

    // Handlebar (extended chopper style)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex2f(frontWheelX, y);      // from wheel
    glVertex2f(frontWheelX - 0.05f, y + 0.3f); // angled fork
    glVertex2f(frontWheelX - 0.05f, y + 0.3f);
    glVertex2f(frontWheelX + 0.05f, y + 0.35f); // bar
    glEnd();

    // Exhaust pipes
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_LINES);
    glVertex2f(rearWheelX, y + 0.05f);
    glVertex2f(rearWheelX - 0.25f, y + 0.15f);
    glVertex2f(rearWheelX, y + 0.02f);
    glVertex2f(rearWheelX - 0.25f, y + 0.12f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw road
    drawRoad();

    // Lane position
    float laneY = legalScene ? -0.65f : -0.35f;

    // Draw motorcycle
    drawMotorcycle(motoX, laneY);

    glutSwapBuffers();
}

void update(int value) {
    // Move motorcycle
    motoX += speed;
    if (motoX > 1.2f) motoX = -1.2f; // loop back

    // Rotate wheels
    wheelAngle -= 0.2f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void handleKeypress(unsigned char key, int x, int y) {
    if (key == ' ') {
        legalScene = !legalScene; // toggle lane
    }
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Legal vs Illegal Scene - Harley Style Motorcycle");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(0, update, 0);
    initGL();
    glutMainLoop();
    return 0;
}
