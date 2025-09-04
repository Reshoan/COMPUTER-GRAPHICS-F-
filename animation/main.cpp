#include <windows.h> // for MS Windows
#include <GL/glut.h> // GLUT, include glu.h and gl.h

// main.cpp
// Cycle rickshaw (Bangladesh style) in 2D with simple animation.
// Build in Code::Blocks with GLUT/freeglut.
//
// Controls:
//   A / D  : move left / right
//   W / S  : speed up / slow down
//   Space  : pause / resume
//   R      : reset position
//   Esc    : quit

#ifdef _WIN32
#endif
#include <GL/glut.h>
#include <cmath>
#include <cstdio>
using namespace std;

// ---- World settings ----
static float worldHalfW = 400.0f;   // world half-width in units
static float worldHalfH = 300.0f;   // world half-height in units

// ---- Animation state ----
static float rickshawX = -250.0f;   // rickshaw position (center)
static float rickshawY = -80.0f;    // ground level baseline for wheels
static float speed = 80.0f;         // units per second
static bool  paused = false;
static float wheelAngle = 0.0f;     // degrees

// Utility: clamp
template<typename T>
T clamp(T v, T lo, T hi) { return v < lo ? lo : (v > hi ? hi : v); }

// --------- Simple drawing helpers ----------
void drawCircle(float cx, float cy, float r, int segments = 48, bool filled = true) {
    float step = 2.0f * 3.1415926535f / segments;
    if (filled) glBegin(GL_TRIANGLE_FAN);
    else        glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float a = i * step;
        glVertex2f(cx + r * std::cos(a), cy + r * std::sin(a));
    }
    glEnd();
}

void drawWheel(float x, float y, float r, int spokes, float angleDeg) {
    // Tire
    glLineWidth(3.0f);
    glColor3f(0.05f, 0.05f, 0.05f);
    drawCircle(x, y, r, 64, false);

    // Rim
    glLineWidth(1.5f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawCircle(x, y, r * 0.85f, 64, false);

    // Hub
    glColor3f(0.6f, 0.6f, 0.6f);
    drawCircle(x, y, r * 0.07f, 24, true);

    // Spokes
    glColor3f(0.75f, 0.75f, 0.75f);
    glBegin(GL_LINES);
    float step = 360.0f / spokes;
    for (int i = 0; i < spokes; ++i) {
        float a = (angleDeg + i * step) * 3.1415926535f / 180.0f;
        float sx = x + std::cos(a) * (r * 0.07f);
        float sy = y + std::sin(a) * (r * 0.07f);
        float ex = x + std::cos(a) * (r * 0.85f);
        float ey = y + std::sin(a) * (r * 0.85f);
        glVertex2f(sx, sy);
        glVertex2f(ex, ey);
    }
    glEnd();
}

void drawRoundedRect(float x, float y, float w, float h, float r) {
    // very simple rounded rectangle (approximate)
    int seg = 12;
    float cx, cy;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    // Build as a convex fan around perimeter
    // bottom edge
    for (int i = 0; i <= seg; ++i) {
        float t = (float)i / seg;
        glVertex2f(x - w * 0.5f + r + (w - 2*r) * t, y - h * 0.5f);
    }
    // bottom-right arc
    cx = x + w*0.5f - r; cy = y - h*0.5f + r;
    for (int i = 0; i <= seg; ++i) {
        float a = (-90.0f + 90.0f * (float)i / seg) * 3.1415926535f / 180.0f;
        glVertex2f(cx + r * std::cos(a), cy + r * std::sin(a));
    }
    // right edge
    for (int i = 0; i <= seg; ++i) {
        float t = (float)i / seg;
        glVertex2f(x + w * 0.5f, y - h * 0.5f + r + (h - 2*r) * t);
    }
    // top-right arc
    cx = x + w*0.5f - r; cy = y + h*0.5f - r;
    for (int i = 0; i <= seg; ++i) {
        float a = (0.0f + 90.0f * (float)i / seg) * 3.1415926535f / 180.0f;
        glVertex2f(cx + r * std::cos(a), cy + r * std::sin(a));
    }
    // top edge
    for (int i = 0; i <= seg; ++i) {
        float t = (float)i / seg;
        glVertex2f(x + w * 0.5f - r - (w - 2*r) * t, y + h * 0.5f);
    }
    // top-left arc
    cx = x - w*0.5f + r; cy = y + h*0.5f - r;
    for (int i = 0; i <= seg; ++i) {
        float a = (90.0f + 90.0f * (float)i / seg) * 3.1415926535f / 180.0f;
        glVertex2f(cx + r * std::cos(a), cy + r * std::sin(a));
    }
    // left edge
    for (int i = 0; i <= seg; ++i) {
        float t = (float)i / seg;
        glVertex2f(x - w * 0.5f, y + h * 0.5f - r - (h - 2*r) * t);
    }
    // bottom-left arc
    cx = x - w*0.5f + r; cy = y - h*0.5f + r;
    for (int i = 0; i <= seg; ++i) {
        float a = (180.0f + 90.0f * (float)i / seg) * 3.1415926535f / 180.0f;
        glVertex2f(cx + r * std::cos(a), cy + r * std::sin(a));
    }
    glEnd();
}

// ---------- Rickshaw ----------
void drawRickshaw(float x, float y, float scale, float wheelSpinDeg) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Ground shadow
    glColor4f(0.0f, 0.0f, 0.0f, 0.15f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, -18);
    glVertex2f(140, -22); glVertex2f(60, -28); glVertex2f(-60, -28); glVertex2f(-140, -22);
    glEnd();

    // Wheels: two large rear wheels, one smaller front wheel
    float rwR = 28.0f;
    float fwR = 20.0f;

    drawWheel(-70.0f, 0.0f, rwR, 14, wheelSpinDeg);   // left rear
    drawWheel(+70.0f, 0.0f, rwR, 14, wheelSpinDeg);   // right rear
    drawWheel(+140.0f, 6.0f, fwR, 12, wheelSpinDeg);  // front

    // Chassis/frame
    glLineWidth(5.0f);
    glColor3f(0.10f, 0.35f, 0.10f);
    glBegin(GL_LINES);
    // axle to body
    glVertex2f(-70, 0);  glVertex2f(-20, 10);
    glVertex2f( 70, 0);  glVertex2f( 20, 10);
    // floor beams
    glVertex2f(-20, 10); glVertex2f( 80, 10);
    glVertex2f(-15, 14); glVertex2f( 85, 14);
    // front fork bars
    glVertex2f( 80, 10); glVertex2f(120, 20);
    glVertex2f( 85, 14); glVertex2f(125, 24);
    // front fork to wheel hub
    glVertex2f(120, 20); glVertex2f(140, 6);
    glVertex2f(125, 24); glVertex2f(140, 6);
    glEnd();

    // Step / footboard
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(70, 10); glVertex2f(95, 10); glVertex2f(90, 18); glVertex2f(65, 18);
    glEnd();

    // Passenger seat base
    glColor3f(0.80f, 0.10f, 0.10f);
    drawRoundedRect(-20.0f, 28.0f, 100.0f, 24.0f, 6.0f);

    // Backrest
    glColor3f(0.85f, 0.15f, 0.15f);
    drawRoundedRect(-20.0f, 60.0f, 110.0f, 36.0f, 8.0f);

    // Decorative side panels (often painted)
    glColor3f(0.10f, 0.60f, 0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-60, 10); glVertex2f(-20, 10); glVertex2f(-20, 46); glVertex2f(-60, 38);
    glVertex2f( 20, 10); glVertex2f( 60, 10); glVertex2f( 60, 38); glVertex2f( 20, 46);
    glEnd();

    // Canopy rods
    glLineWidth(3.0f);
    glColor3f(0.10f, 0.35f, 0.10f);
    glBegin(GL_LINES);
    glVertex2f(-40, 46); glVertex2f(-20, 96);
    glVertex2f( 40, 46); glVertex2f( 20, 96);
    glVertex2f(-20, 96); glVertex2f( 20, 96);
    glEnd();

    // Canopy cloth (arched)
    glColor3f(0.10f, 0.45f, 0.20f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 100);
    for (int i = 0; i <= 18; ++i) {
        float t = (float)i / 18.0f;
        float ax = -22.0f + 44.0f * t;
        float ay = 96.0f + 14.0f * std::sin(t * 3.1415926535f);
        glVertex2f(ax, ay);
    }
    glEnd();

    // Seat cushion stripes (embroidery vibe)
    glLineWidth(2.0f);
    glColor3f(1.0f, 0.85f, 0.25f);
    glBegin(GL_LINES);
    glVertex2f(-60, 28); glVertex2f(20, 28);
    glVertex2f(-58, 36); glVertex2f(22, 36);
    glEnd();

    // Handlebar + stem
    glLineWidth(4.0f);
    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_LINES);
    glVertex2f(135, 26); glVertex2f(150, 40);   // right handle
    glVertex2f(135, 26); glVertex2f(120, 40);   // left handle
    glVertex2f(120, 20); glVertex2f(135, 26);   // stem
    glEnd();

    // Driver saddle
    glColor3f(0.2f, 0.2f, 0.2f);
    drawRoundedRect(95.0f, 28.0f, 28.0f, 10.0f, 3.0f);

    // Chain cover (stylized)
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(40, 2); glVertex2f(60, 6); glVertex2f(75, 12); glVertex2f(55, 8);
    glEnd();

    glPopMatrix();
}

// --------- Scene ----------
void drawGround() {
    // Sky
    glColor3f(0.82f, 0.93f, 0.99f);
    glBegin(GL_QUADS);
    glVertex2f(-worldHalfW, 0);
    glVertex2f( worldHalfW, 0);
    glVertex2f( worldHalfW, worldHalfH);
    glVertex2f(-worldHalfW, worldHalfH);
    glEnd();

    // Road
    glColor3f(0.92f, 0.92f, 0.92f);
    glBegin(GL_QUADS);
    glVertex2f(-worldHalfW, -40);
    glVertex2f( worldHalfW, -40);
    glVertex2f( worldHalfW, -140);
    glVertex2f(-worldHalfW, -140);
    glEnd();

    // Divider dashes
    glLineWidth(6.0f);
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_LINES);
    for (float x = -worldHalfW; x < worldHalfW; x += 60.0f) {
        glVertex2f(x + 10.0f, -90.0f);
        glVertex2f(x + 40.0f, -90.0f);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGround();
    drawRickshaw(rickshawX, rickshawY, 1.0f, wheelAngle);

    // HUD text
    glColor3f(0, 0, 0);
    glRasterPos2f(-worldHalfW + 10, worldHalfH - 20);
    char buf[128];
    std::snprintf(buf, sizeof(buf), "Speed: %.0f  |  %s", speed, paused ? "Paused" : "Running");
    for (const char* p = buf; *p; ++p) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Maintain aspect ratio by expanding the shorter axis
    float windowAspect = (h == 0) ? 1.0f : (float)w / (float)h;
    float worldAspect  = worldHalfW / worldHalfH;

    if (windowAspect >= worldAspect) {
        // window wider: extend x
        float halfW = worldHalfH * windowAspect;
        gluOrtho2D(-halfW, halfW, -worldHalfH, worldHalfH);
    } else {
        // window taller: extend y
        float halfH = worldHalfW / windowAspect;
        gluOrtho2D(-worldHalfW, worldHalfW, -halfH, halfH);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    static int prev = 0;
    int now = glutGet(GLUT_ELAPSED_TIME); // ms
    float dt = (prev == 0) ? 0.016f : (now - prev) / 1000.0f;
    prev = now;

    if (!paused) {
        rickshawX += speed * dt;
        // Wrap-around
        if (rickshawX > worldHalfW + 160.0f) rickshawX = -worldHalfW - 160.0f;
        if (rickshawX < -worldHalfW - 160.0f) rickshawX = worldHalfW + 160.0f;

        // Spin wheels according to linear speed (v = omega * r)
        float wheelRadius = 28.0f; // match rear wheel
        float omega = (speed / wheelRadius) * 180.0f / 3.1415926535f; // deg/s
        wheelAngle = std::fmod(wheelAngle - omega * dt, 360.0f);
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 27: exit(0); break; // Esc
        case ' ': paused = !paused; break;
        case 'r': case 'R':
            rickshawX = -250.0f; wheelAngle = 0.0f; speed = 80.0f; paused = false; break;
        case 'a': case 'A': rickshawX -= 10.0f; break;
        case 'd': case 'D': rickshawX += 10.0f; break;
        case 'w': case 'W': speed = clamp(speed + 20.0f, 0.0f, 400.0f); break;
        case 's': case 'S': speed = clamp(speed - 20.0f, 0.0f, 400.0f); break;
        default: break;
    }
}

void initGL() {
    glClearColor(0.96f, 0.98f, 1.0f, 1.0f); // light background
    glDisable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Bangladesh Manual Rickshaw - OpenGL (GLUT)");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}
