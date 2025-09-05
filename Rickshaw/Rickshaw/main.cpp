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
#include <windows.h>
#include <iostream>
#include <sstream>

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
void geoPoint(const string &geoStr) {
    float x, y;

    // Find the '(' and ')'
    size_t start = geoStr.find('(');
    size_t end   = geoStr.find(')');

    if (start != string::npos && end != string::npos && end > start) {
        string coords = geoStr.substr(start + 1, end - start - 1); // extract "x,y"

        // Replace comma with space (old-style loop for pre-C++11)
        for (size_t i = 0; i < coords.size(); i++) {
            if (coords[i] == ',') coords[i] = ' ';
        }

        stringstream ss(coords);
        if (ss >> x >> y) {
            glVertex2f(x, y);
        } else {
            cerr << "Error: Could not parse numbers from -> " << geoStr << endl;
        }
    } else {
        cerr << "Error: Invalid format -> " << geoStr << endl;
    }
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


// ---------- Rickshaw ----------
void drawRickshaw(float x, float y, float scale, float wheelSpinDeg) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    //HOOD-1
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("C=$point(-3.07781,1.4511)");
        geoPoint("D=$point(-2.87873,1.49092)");
        geoPoint("E=$point(-2.89465,2.53413)");
        geoPoint("F=$point(-3.00614,4.31795)");
        geoPoint("G=$point(-3.49191,4.07904)");
        geoPoint("H=$point(-4.08121,3.9357)");
        geoPoint("I=$point(-3.46006,2.70933)");
    glEnd();
    //HOOD-2
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("E=$point(-2.89465,2.53413)");
        geoPoint("J=$point(-2.6876,2.73322)");
        geoPoint("K=$point(-2.44521,2.74716)");
        geoPoint("F=$point(-3.00614,4.31795)");
    glEnd();
    //HOOD-3
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("K=$point(-2.44521,2.74716)");
        geoPoint("L=$point(-2.09831,2.89249)");
        geoPoint("M=$point(-1.8337,2.83747)");
        geoPoint("N=$point(-1.69217,3.66494)");
        geoPoint("O=$point(-1.80366,4.50907)");
        geoPoint("P=$point(-2.38499,4.35776)");
        geoPoint("F=$point(-3.00614,4.31795)");
    glEnd();

    //HOOD-4

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("M=$point(-1.8337,2.83747)");
        geoPoint("Q=$point(-1.38475,2.68266)");
        geoPoint("R=$point(-1.07102,3.03583)");
        geoPoint("S=$point(-0.81619,3.47382)");
        geoPoint("T=$point(-0.6171,4.09497)");
        geoPoint("U=$point(-0.60118,4.23831)");
        geoPoint("V=$point(-0.97546,4.2622)");
        geoPoint("W=$point(-1.46123,4.37369)");
        geoPoint("O=$point(-1.80366,4.50907)");
        geoPoint("N=$point(-1.69217,3.66494)");
    glEnd();

    //BAR-1
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("K=$point(-2.44521,2.74716)");
        geoPoint("Z=$point(-1.95497,1.60414)");
        geoPoint("E_{1}=$point(-1.92917,1.74347)");
        geoPoint("B_{1}=$point(-2.34974,2.7678)");
    glEnd();
    //BAR-2
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("E_{1}=$point(-1.92917,1.74347)");
        geoPoint("F_{1}=$point(-1.83112,1.85958)");
        geoPoint("C_{1}=$point(-1.74598,2.82715)");
        geoPoint("M=$point(-1.8337,2.83747)");
    glEnd();
    //BAR-3
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("F_{1}=$point(-1.83112,1.85958)");
        geoPoint("A_{1}=$point(-1.84661,1.5964)");
        geoPoint("Q=$point(-1.38475,2.68266)");
        geoPoint("D_{1}=$point(-1.45958,2.73942)");
    glEnd();
    //BAR-Joint
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("Z=$point(-1.95497,1.60414)");
        geoPoint("A_{1}=$point(-1.84661,1.5964)");
        geoPoint("F_{1}=$point(-1.83112,1.85958)");
        geoPoint("E_{1}=$point(-1.92917,1.74347)");
    glEnd();

    //seat
    glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.0f, 0.5f);
        geoPoint("D=$point(-2.87873,1.49092)");
        geoPoint("P_{1}=$point(-1.74689,1.3231)");
        geoPoint("O_{1}=$point(-1.74689,1.45244)");
        geoPoint("N_{1}=$point(-1.75481,1.51842)");
        geoPoint("M_{1}=$point(-1.79176,1.56857)");
        geoPoint("A_{1}=$point(-1.84661,1.5964)");
        geoPoint("L_{1}=$point(-1.90526,1.61345)");
        geoPoint("Z=$point(-1.95497,1.60414)");
        geoPoint("K_{1}=$point(-2.72615,1.61345)");
        geoPoint("J_{1}=$point(-2.72861,2.4745)");
        geoPoint("I_{1}=$point(-2.7339,2.56704)");
        geoPoint("H_{1}=$point(-2.76827,2.60934)");
        geoPoint("G_{1}=$point(-2.82908,2.649)");
        geoPoint("E=$point(-2.89465,2.53413)");
    glEnd();

    //support bar 1_1
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("R_{1}=$point(-2.93359,1.12109)");
        geoPoint("U_{1}=$point(-2.93681,0.65605)");
        geoPoint("T_{1}=$point(-2.90286,0.65443)");
        geoPoint("S_{1}=$point(-2.9005,1.12661)");
    glEnd();
    //support bar 1_2
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("C_{2}=$point(-2.16841,0.49957)");
        geoPoint("D_{2}=$point(-2.16488,1.00308)");
        geoPoint("E_{2}=$point(-2.20693,1.02235)");
        geoPoint("F_{2}=$point(-2.2,0.5)");
    glEnd();
    //support bar 1_3
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("U_{1}=$point(-2.93681,0.65605)");
        geoPoint("V_{1}=$point(-2.97077,0.63503)");
        geoPoint("W_{1}=$point(-2.96915,0.57844)");
        geoPoint("Z_{1}=$point(-2.92388,0.54448)");
        geoPoint("A_{2}=$point(-0.85926,0.12923)");
        geoPoint("B_{2}=$point(-0.81538,0.21824)");
        geoPoint("C_{2}=$point(-2.16841,0.49957)");
        geoPoint("F_{2}=$point(-2.2,0.5)");
        geoPoint("T_{1}=$point(-2.90286,0.65443)");
    glEnd();
    //support bar 2_1
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("N_{2}=$point(-2.84647,0.3113)");
        geoPoint("G_{2}=$point(-3.03394,0.30528)");
        geoPoint("H_{2}=$point(-3.08817,0.28325)");
        geoPoint("I_{2}=$point(-3.10342,0.23749)");
        geoPoint("J_{2}=$point(-3.04071,0.17986)");
        geoPoint("K_{2}=$point(-2.93394,0.16969)");
        geoPoint("L_{2}=$point(-0.8,0)");
        geoPoint("M_{2}=$point(-0.78701,0.11988)");
    glEnd();
    //support bar 2_2
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("T_{2}=$point(-0.70479,0.21753)");
        geoPoint("M_{2}=$point(-0.78701,0.11988)");
        geoPoint("L_{2}=$point(-0.8,0)");
        geoPoint("O_{2}=$point(1.07663,-0.13532)");
        geoPoint("P_{2}=$point(1.04037,0.01249)");
        geoPoint("Q_{2}=$point(-0.46495,0.08141)");
        geoPoint("U_{2}=$point(-0.51312,0.11237)");
        geoPoint("R_{2}=$point(-0.54127,0.14857)");
        geoPoint("S_{2}=$point(-0.55438,0.19053)");
    glEnd();
    //support bar 2_3
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("T_{2}=$point(-0.70479,0.21753)");
        geoPoint("S_{2}=$point(-0.55438,0.19053)");
        geoPoint("F_{3}=$point(-0.4,0.4)");
        geoPoint("E_{3}=$point(-0.2,0.6)");
        geoPoint("D_{3}=$point(0.02758,0.79178)");
        geoPoint("C_{3}=$point(0.2868,0.96929)");
        geoPoint("B_{3}=$point(0.58018,1.1136)");
        geoPoint("A_{3}=$point(0.54038,1.22851)");
        geoPoint("Z_{2}=$point(0.22339,1.06054)");
        geoPoint("W_{2}=$point(-0.07104,0.84532)");
        geoPoint("V_{2}=$point(-0.36406,0.59455)");
    glEnd();

    //support bar 2_4
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("O_{2}=$point(1.07663,-0.13532)");
        geoPoint("G_{3}=$point(1.29363,-0.12702)");
        geoPoint("H_{3}=$point(1.5,-0.1)");
        geoPoint("V_{3}=$point(1.45389,0.03558)");
        geoPoint("W_{3}=$point(1.31565,0.01278)");
        geoPoint("C_{4}=$point(1.2,0)");
        geoPoint("P_{2}=$point(1.04037,0.01249)");
    glEnd();
    //support bar 2_5
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("H_{3}=$point(1.5,-0.1)");
        geoPoint("I_{3}=$point(1.61401,-0.01757)");
        geoPoint("K_{3}=$point(1.66774,0.04014)");
        geoPoint("J_{3}=$point(1.73341,0.09387)");
        geoPoint("T_{3}=$point(1.61082,0.16601)");
        geoPoint("U_{3}=$point(1.52115,0.0743)");
        geoPoint("V_{3}=$point(1.45389,0.03558)");
    glEnd();
    //support bar 2_6
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("H_{3}=$point(1.5,-0.1)");
        geoPoint("I_{3}=$point(1.61401,-0.01757)");
        geoPoint("K_{3}=$point(1.66774,0.04014)");
        geoPoint("J_{3}=$point(1.73341,0.09387)");
        geoPoint("L_{3}=$point(1.83887,0.23117)");
        geoPoint("M_{3}=$point(2.31065,0.82264)");
        geoPoint("N_{3}=$point(2.65888,1.24105)");
        geoPoint("Z_{3}=$point(2.69807,1.26775)");
        geoPoint("O_{3}=$point(2.58426,1.4072)");
        geoPoint("P_{3}=$point(2.58498,1.34805)");
        geoPoint("Q_{3}=$point(2.49531,1.22781)");
        geoPoint("R_{3}=$point(2.34246,1.03624)");
        geoPoint("S_{3}=$point(1.82685,0.41873)");
        geoPoint("T_{3}=$point(1.61082,0.16601)");
        geoPoint("U_{3}=$point(1.52115,0.0743)");
        geoPoint("V_{3}=$point(1.45389,0.03558)");
    glEnd();
    //support bar 2_7
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("P_{2}=$point(1.04037,0.01249)");
        geoPoint("C_{4}=$point(1.2,0)");
        geoPoint("B_{4}=$point(0.68916,1.16313)");
        geoPoint("A_{4}=$point(0.64756,1.26972)");
        geoPoint("A_{3}=$point(0.54038,1.22851)");
        geoPoint("B_{3}=$point(0.58018,1.1136)");
    glEnd();
    //support bar 2_8
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("B_{4}=$point(0.68916,1.16313)");
        geoPoint("B_{5}=$point(0.85626,1.20241)");
        geoPoint("L_{4}=$point(1.07787,1.23935)");
        geoPoint("F_{5}=$point(1.05843,1.34626)");
        geoPoint("Z_{4}=$point(0.92819,1.33071)");
        geoPoint("A_{5}=$point(0.8,1.3)");
        geoPoint("A_{4}=$point(0.64756,1.26972)");
    glEnd();
    //support bar 2_9
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("L_{4}=$point(1.07787,1.23935)");
        geoPoint("C_{5}=$point(1.20034,1.25101)");
        geoPoint("W_{4}=$point(1.19062,1.35209)");
        geoPoint("E_{5}=$point(1.34613,1.27239)");
        geoPoint("M_{4}=$point(1.47249,1.27822)");
        geoPoint("N_{4}=$point(1.6,1.3)");
        geoPoint("U_{4}=$point(1.57358,1.40847)");
        geoPoint("V_{4}=$point(1.47638,1.38514)");
        geoPoint("D_{5}=$point(1.33642,1.37153)");
        geoPoint("W_{4}=$point(1.19062,1.35209)");
        geoPoint("F_{5}=$point(1.05843,1.34626)");
    glEnd();
    //support bar 2_10
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("L_{4}=$point(1.07787,1.23935)");
        geoPoint("C_{5}=$point(1.20034,1.25101)");
        geoPoint("W_{4}=$point(1.19062,1.35209)");
        geoPoint("E_{5}=$point(1.34613,1.27239)");
        geoPoint("M_{4}=$point(1.47249,1.27822)");
        geoPoint("N_{4}=$point(1.6,1.3)");
        geoPoint("U_{4}=$point(1.57358,1.40847)");
        geoPoint("V_{4}=$point(1.47638,1.38514)");
        geoPoint("D_{5}=$point(1.33642,1.37153)");
        geoPoint("W_{4}=$point(1.19062,1.35209)");
        geoPoint("F_{5}=$point(1.05843,1.34626)");
    glEnd();
    //support bar 2_11
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("N_{4}=$point(1.6,1.3)");
        geoPoint("O_{4}=$point(1.81074,1.37542)");
        geoPoint("G_{5}=$point(1.97403,1.45124)");
        geoPoint("P_{4}=$point(2.14898,1.50567)");
        geoPoint("R_{4}=$point(2.1,1.6)");
        geoPoint("S_{4}=$point(1.9196,1.53871)");
        geoPoint("T_{4}=$point(1.78158,1.48623)");
        geoPoint("U_{4}=$point(1.57358,1.40847)");
    glEnd();
    //support bar 2_12
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("P_{4}=$point(2.14898,1.50567)");
        geoPoint("Q_{4}=$point(2.25767,1.52279)");
        geoPoint("H_{5}=$point(2.41304,1.54723)");
        geoPoint("E_{4}=$point(2.52326,1.54948)");
        geoPoint("G_{4}=$point(2.53994,1.69622)");
        geoPoint("I_{5}=$point(2.4078,1.65895)");
        geoPoint("F_{4}=$point(2.23673,1.62753)");
        geoPoint("R_{4}=$point(2.1,1.6)");
    glEnd();
    //support bar 2_13
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("E_{4}=$point(2.52326,1.54948)");
        geoPoint("D_{4}=$point(2.56886,1.49294)");
        geoPoint("O_{3}=$point(2.58426,1.4072)");
        geoPoint("P_{3}=$point(2.58498,1.34805)");
        geoPoint("N_{3}=$point(2.65888,1.24105)");
        geoPoint("Z_{3}=$point(2.69807,1.26775)");
        geoPoint("K_{4}=$point(2.73977,1.25939)");
        geoPoint("J_{4}=$point(2.83679,1.28291)");
        geoPoint("I_{4}=$point(2.85069,1.33008)");
        geoPoint("H_{4}=$point(2.72516,1.72636)");
        geoPoint("M_{5}=$point(2.70583,1.81325)");
        geoPoint("L_{5}=$point(2.6431,1.85002)");
        geoPoint("K_{5}=$point(2.55498,1.8326)");
        geoPoint("J_{5}=$point(2.53601,1.78608)");
        geoPoint("G_{4}=$point(2.53994,1.69622)");
    glEnd();
    //support bar 2_14
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("E_{4}=$point(2.52326,1.54948)");
        geoPoint("D_{4}=$point(2.56886,1.49294)");
        geoPoint("O_{3}=$point(2.58426,1.4072)");
        geoPoint("P_{3}=$point(2.58498,1.34805)");
        geoPoint("N_{3}=$point(2.65888,1.24105)");
        geoPoint("Z_{3}=$point(2.69807,1.26775)");
        geoPoint("K_{4}=$point(2.73977,1.25939)");
        geoPoint("J_{4}=$point(2.83679,1.28291)");
        geoPoint("I_{4}=$point(2.85069,1.33008)");
        geoPoint("H_{4}=$point(2.72516,1.72636)");
        geoPoint("M_{5}=$point(2.70583,1.81325)");
        geoPoint("L_{5}=$point(2.6431,1.85002)");
        geoPoint("K_{5}=$point(2.55498,1.8326)");
        geoPoint("J_{5}=$point(2.53601,1.78608)");
        geoPoint("G_{4}=$point(2.53994,1.69622)");
    glEnd();
    //support bar 2_15
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("E_{4}=$point(2.52326,1.54948)");
        geoPoint("D_{4}=$point(2.56886,1.49294)");
        geoPoint("O_{3}=$point(2.58426,1.4072)");
        geoPoint("P_{3}=$point(2.58498,1.34805)");
        geoPoint("N_{3}=$point(2.65888,1.24105)");
        geoPoint("Z_{3}=$point(2.69807,1.26775)");
        geoPoint("K_{4}=$point(2.73977,1.25939)");
        geoPoint("J_{4}=$point(2.83679,1.28291)");
        geoPoint("I_{4}=$point(2.85069,1.33008)");
        geoPoint("H_{4}=$point(2.72516,1.72636)");
        geoPoint("M_{5}=$point(2.70583,1.81325)");
        geoPoint("L_{5}=$point(2.6431,1.85002)");
        geoPoint("K_{5}=$point(2.55498,1.8326)");
        geoPoint("J_{5}=$point(2.53601,1.78608)");
        geoPoint("G_{4}=$point(2.53994,1.69622)");
    glEnd();
    //support bar 2_16
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("K_{4}=$point(2.73977,1.25939)");
        geoPoint("N_{5}=$point(2.74741,1.21974)");
        geoPoint("O_{5}=$point(2.91984,0.77331)");
        geoPoint("P_{5}=$point(3,0.6)");
        geoPoint("D_{6}=$point(3.07363,0.64617)");
        geoPoint("S_{5}=$point(3,0.8) ");
        geoPoint("T_{5}=$point(2.84448,1.24224) ");
        geoPoint("J_{4}=$point(2.82667,1.28988)");
    glEnd();
    //support bar 2_17
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("P_{5}=$point(3,0.6)");
        geoPoint("U_{5}=$point(3.12397,0.42318)");
        geoPoint("V_{5}=$point(3.28084,0.23779) ");
        geoPoint("B_{6}=$point(3.33928,0.30067)");
        geoPoint("C_{6}=$point(3.2078,0.46587)");
        geoPoint("D_{6}=$point(3.07363,0.64617)");
    glEnd();
    //support bar 2_18
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("V_{5}=$point(3.28084,0.23779) ");
        geoPoint("W_{5}=$point(3.46908,0.04385)");
        geoPoint("Q_{5}=$point(3.49877,0.00296)");
        geoPoint("A_{6}=$point(3.58502,0.07832) ");
        geoPoint("B_{6}=$point(3.33928,0.30067)");
    glEnd();
    //handle bar 1_1
    glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("K_{5}=$point(2.55498,1.8326)");
        geoPoint("L_{5}=$point(2.6431,1.85002)");
        geoPoint("Z_{5}=$point(2.6,2)");
        geoPoint("R_{5}=$point(2.51969,1.98521)");
    glEnd();
    //handle bar 1_2
    glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("R_{5}=$point(2.51969,1.98521)");
        geoPoint("Z_{5}=$point(2.6,2)");
        geoPoint("E_{6}=$point(2.60658,2.05493)");
        geoPoint("F_{6}=$point(2.51862,2.05279)");
    glEnd();
    //handle bar 1_3
    glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("F_{6}=$point(2.51862,2.05279)");
        geoPoint("E_{6}=$point(2.60658,2.05493)");
        geoPoint("G_{6}=$point(2.5272,2.11715)");
    glEnd();
    //handle bar 1_4
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("G_{6}=$point(2.5272,2.11715)");
        geoPoint("E_{6}=$point(2.60658,2.05493)");
        geoPoint("H_{6}=$point(2.63017,2.11179)");
        geoPoint("I_{6}=$point(2.5701,2.16864)");
    glEnd();
    //handle bar 1_5
    glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("H_{6}=$point(2.63017,2.11179)");
        geoPoint("J_{6}=$point(2.69346,2.14718)");
        geoPoint("M_{6}=$point(2.74732,2.1749)");
        geoPoint("N_{6}=$point(2.8,2.2)");
        geoPoint("O_{6}=$point(2.80073,2.2448)");
        geoPoint("P_{6}=$point(2.76385,2.27836)");
        geoPoint("L_{6}=$point(2.70097,2.2566)");
        geoPoint("K_{6}=$point(2.63876,2.22656)");
        geoPoint("I_{6}=$point(2.5701,2.16864)");
    glEnd();
    //handle bar 2_1
    glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("L_{6}=$point(2.70097,2.2566)");
        geoPoint("P_{6}=$point(2.76385,2.27836)");
        geoPoint("R_{6}=$point(2.69275,2.44107)");
        geoPoint("Q_{6}=$point(2.6385,2.40538)");
    glEnd();
    //handle bar 2_2
    glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("Q_{6}=$point(2.6385,2.40538)");
        geoPoint("R_{6}=$point(2.69275,2.44107)");
        geoPoint("B_{7}=$point(2.67002,2.47144)");
        geoPoint("T_{6}=$point(2.64635,2.48605)");
        geoPoint("U_{6}=$point(2.61137,2.43394)");
    glEnd();
    //handle bar 2_3
    glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("U_{6}=$point(2.61137,2.43394)");
        geoPoint("T_{6}=$point(2.64635,2.48605)");
        geoPoint("S_{6}=$point(2.6,2.5)");
    glEnd();
    //handle bar 2_4
    glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("U_{6}=$point(2.61137,2.43394)");
        geoPoint("S_{6}=$point(2.6,2.5)");
        geoPoint("V_{6}=$point(2.55,2.45)");
    glEnd();
    //handle bar 2_5
    glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("V_{6}=$point(2.55,2.45)");
        geoPoint("S_{6}=$point(2.6,2.5)");
        geoPoint("W_{6}=$point(2.54856,2.51317)");
    glEnd();
    //handle bar 2_6
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("V_{6}=$point(2.55,2.45)");
        geoPoint("W_{6}=$point(2.54856,2.51317)");
        geoPoint("Z_{6}=$point(2.45647,2.5146)");
        geoPoint("A_{7}=$point(2.45861,2.45107)");
    glEnd();
    //handle bar 3_1
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("A_{7}=$point(2.45861,2.45107)");
        geoPoint("L_{7}=$point(2.44266,2.43726)");
        geoPoint("C_{7}=$point(2.41951,2.41902) ");
        geoPoint("D_{7}=$point(2.10198,2.42327)");
        geoPoint("E_{7}=$point(2.07488,2.43933)");
        geoPoint("F_{7}=$point(2.05481,2.4614)");
        geoPoint("G_{7}=$point(2.0528,2.50958)");
        geoPoint("H_{7}=$point(2.07689,2.53266)");
        geoPoint("I_{7}=$point(2.1,2.55)");
        geoPoint("J_{7}=$point(2.41249,2.54528)");
        geoPoint("K_{7}=$point(2.43143,2.52914)");
        geoPoint("Z_{6}=$point(2.45647,2.5146)");
    glEnd();
    //handle bar 3_2
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f);
        geoPoint("F_{7}=$point(2.05481,2.4614)");
        geoPoint("G_{7}=$point(2.0528,2.50958)");
        geoPoint("N_{7}=$point(2.00918,2.508)");
        geoPoint("M_{7}=$point(2.01173,2.46851)");
    glEnd();
    //seat 1
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("A_{3}=$point(0.54038,1.22851)");
        geoPoint("A_{4}=$point(0.64756,1.26972)");
        geoPoint("P_{7}=$point(0.50444,1.6268)");
        geoPoint("O_{7}=$point(0.39181,1.58389)");
    glEnd();
    //seat 2
    glBegin(GL_POLYGON);
        glColor3f(0.5f, 0.0f, 0.5f);
        geoPoint("O_{7}=$point(0.39181,1.58389)");
        geoPoint("P_{7}=$point(0.50444,1.6268)");
        geoPoint("N_{8}=$point(0.60574,1.66209)");
        geoPoint("M_{8}=$point(0.67382,1.68653)");
        geoPoint("L_{8}=$point(0.77158,1.72493)");
        geoPoint("K_{8}=$point(0.84315,1.77032)");
        geoPoint("J_{8}=$point(0.85712,1.82095)");
        geoPoint("I_{8}=$point(0.8449,1.87332)");
        geoPoint("H_{8}=$point(0.82046,1.8995)");
        geoPoint("G_{8}=$point(0.75412,1.9414)");
        geoPoint("F_{8}=$point(0.66859,1.96234)");
        geoPoint("E_{8}=$point(0.57083,1.9606)");
        geoPoint("D_{8}=$point(0.45562,1.96234)");
        geoPoint("C_{8}=$point(0.25367,1.95221)");
        geoPoint("B_{8}=$point(-0.0747,1.94496)");
        geoPoint("O_{8}=$point(-0.12849,1.93855)");
        geoPoint("A_{8}=$point(-0.15528,1.89856)");
        geoPoint("Z_{7}=$point(-0.16243,1.85029)");
        geoPoint("W_{7}=$point(-0.1374,1.77698)");
        geoPoint("V_{7}=$point(-0.11416,1.74301)");
        geoPoint("P_{8}=$point(-0.05933,1.71186)");
        geoPoint("U_{7}=$point(-0.00689,1.66971)");
        geoPoint("T_{7}=$point(0.05211,1.63574)");
        geoPoint("S_{7}=$point(0.16832,1.59641)");
        geoPoint("R_{7}=$point(0.24341,1.58032)");
        geoPoint("Q_{7}=$point(0.32744,1.57317)");
    glEnd();

    float rwR = 1.25f;
    float fwR = 1.25f;

    drawWheel(-2.75192, 0.20551, rwR, 14, wheelSpinDeg);   // left rear
    drawWheel(3.54232, 0.04381, rwR, 14, wheelSpinDeg);   // right rear
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
    drawRickshaw(rickshawX, rickshawY, 75.0f, wheelAngle);

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
