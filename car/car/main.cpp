#include <windows.h> // for MS Windows
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#ifdef _WIN32
#endif
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;
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
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //back-1
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("C=$point(-5.02276,0.99137)");
        geoPoint("D=$point(-5.04243,0.93042)");
        geoPoint("E=$point(-5.1,0.9)");
        geoPoint("F=$point(-5.13483,0.80459)");
        geoPoint("G=$point(-5.14663,0.57653)");
        geoPoint("H=$point(-5.13483,0.52148)");
        geoPoint("I=$point(-5.09354,0.4448)");
        geoPoint("J=$point(-5.03653,0.37599)");
        geoPoint("K=$point(-5.01293,0.3229)");
        geoPoint("L=$point(-5.05422,0.201)");
        geoPoint("M=$point(-4.53125,0.05158)");
        geoPoint("N=$point(-4.54894,0.9953)");
    glEnd();

    //back light-1
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        geoPoint("C=$point(-5.02276,0.99137)");
        geoPoint("N=$point(-4.54894,0.9953)");
        geoPoint("U_{2}=$point(-4.61779,1.06562)");
        geoPoint("P_{2}=$point(-4.99167,1.07262)");
    glEnd();
    //back light-2
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        geoPoint("N=$point(-4.55,1)");
        geoPoint("Q=$point(-4.56568,1.06898)");
        geoPoint("U_{2}=$point(-4.61779,1.06562)");
    glEnd();
    //back light-3
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        geoPoint("U_{2}=$point(-4.61779,1.06562)");
        geoPoint("Q=$point(-4.56568,1.06898)");
        geoPoint("R=$point(-4.72455,1.24047)");
        geoPoint("T_{2}=$point(-4.74805,1.20539)");
    glEnd();
    //back light-4
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        geoPoint("T_{2}=$point(-4.74805,1.20539)");
        geoPoint("R=$point(-4.72455,1.24047)");
        geoPoint("R_{1}=$point(-4.76388,1.26142)");
    glEnd();
    //back light-5
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        geoPoint("S_{2}=$point(-4.97705,1.22001)");
        geoPoint("T_{2}=$point(-4.74805,1.20539)");
        geoPoint("R_{1}=$point(-4.76388,1.26142)");
        geoPoint("Q_{1}=$point(-5.00994,1.27117)");
    glEnd();

    //actual back light
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("P_{2}=$point(-4.99167,1.07262)");
        geoPoint("U_{2}=$point(-4.61779,1.06562)");
        geoPoint("T_{2}=$point(-4.74805,1.20539)");
        geoPoint("S_{2}=$point(-4.97705,1.22001)");
        geoPoint("R_{2}=$point(-5.01725,1.17616)");
        geoPoint("Q_{2}=$point(-5.02212,1.10185)");
    glEnd();

    //back-2
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("Q_{1}=$point(-5.00994,1.27117)");
        geoPoint("R_{1}=$point(-4.76388,1.26142)");
        geoPoint("O_{1}=$point(-4.76225,1.52233)");
        geoPoint("T=$point(-4.91829,1.5187)");
    glEnd();

    //back-3
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("O_{1}=$point(-4.76225,1.52233)");
        geoPoint("T=$point(-4.91829,1.5187)");
        geoPoint("S_{1}=$point(-4.87193,1.56765)");
    glEnd();

    //back-4
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("Q=$point(-4.56568,1.06898)");
        geoPoint("N=$point(-4.55,1)");
        geoPoint("N_{1}=$point(-4.41283,1.53998)");
    glEnd();
    //back-5
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("R=$point(-4.72455,1.24047)");
        geoPoint("Q=$point(-4.56568,1.06898)");
        geoPoint("N_{1}=$point(-4.41283,1.53998)");
    glEnd();
    //back-6
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("R=$point(-4.72455,1.24047)");
        geoPoint("N_{1}=$point(-4.41283,1.53998)");
        geoPoint("O_{1}=$point(-4.76225,1.52233)");
        geoPoint("R_{1}=$point(-4.76388,1.26142)");
    glEnd();

    //fender-1
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("T_{1}=$point(-4.92998,1.63053)");
        geoPoint("S_{1}=$point(-4.87193,1.56765)");
        geoPoint("V_{1}=$point(-4.83485,1.71599)");
        geoPoint("G_{2}=$point(-4.88529,1.7061)");
        geoPoint("U_{1}=$point(-4.9461,1.69019)");
    glEnd();

    //fender-2
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("S_{1}=$point(-4.87193,1.56765)");
        geoPoint("O_{1}=$point(-4.76225,1.52233)");
        geoPoint("W_{1}=$point(-4.70264,1.72566)");
        geoPoint("V_{1}=$point(-4.83485,1.71599)");
    glEnd();
    //fender-3
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("E_{2}=$point(-4.59945,1.6789)");
        geoPoint("Z_{1}=$point(-4.57043,1.72083)");
        geoPoint("W_{1}=$point(-4.70264,1.72566)");
        geoPoint("P_{1}=$point(-4.72, 1.68)");
    glEnd();
    //fender-4
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("P_{1}=$point(-4.72, 1.68)");
        geoPoint("O_{1}=$point(-4.76225,1.52233)");
        geoPoint("F_{2}=$point(-4.49636,1.52562)");
        geoPoint("D_{2}=$point(-4.5,1.6)");
        geoPoint("E_{2}=$point(-4.59945,1.6789)");
    glEnd();
    //fender-5
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("D_{2}=$point(-4.5,1.6)");
        geoPoint("F_{2}=$point(-4.49636,1.52562)");
        geoPoint("N_{1}=$point(-4.41283,1.53998)");
        geoPoint("H_{2}=$point(-4.43953,1.58473)");
    glEnd();
    //fender in-1
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("E_{2}=$point(-4.59945,1.6789)");
        geoPoint("D_{2}=$point(-4.5,1.6)");
        geoPoint("A_{2}=$point(-4.41564,1.70148)");
        geoPoint("Z_{1}=$point(-4.57043,1.72083)");
    glEnd();
    //fender in-2
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("D_{2}=$point(-4.5,1.6)");
        geoPoint("H_{2}=$point(-4.43953,1.58473)");
        geoPoint("B_{2}=$point(-4.29794,1.67407)");
        geoPoint("A_{2}=$point(-4.41564,1.70148)");
    glEnd();
    //fender in-3
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{2}=$point(-4.43953,1.58473)");
        geoPoint("I_{2}=$point(-4.15979,1.60581)");
        geoPoint("C_{2}=$point(-4.15122,1.63537)");
        geoPoint("B_{2}=$point(-4.29794,1.67407)");
    glEnd();
    //fender in-4
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("I_{2}=$point(-4.15979,1.60581)");
        geoPoint("J_{2}=$point(-4.10077,1.61479)");
        geoPoint("C_{2}=$point(-4.15122,1.63537)");
    glEnd();
    //back-7
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("N_{1}=$point(-4.41283,1.53998)  ");
        geoPoint("I_{2}=$point(-4.15979,1.60581)");
        geoPoint("H_{2}=$point(-4.43953,1.58473)");
    glEnd();
    //back-8
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("N=$point(-4.55,1)");
        geoPoint("M=$point(-4.53125,0.05158)");
        geoPoint("O=$point(-4,0)");
        geoPoint("P=$point(-3.88466,0.08789)");
        geoPoint("L_{2}=$point(-3.2636,1.6574)");
        geoPoint("K_{2}=$point(-3.55287,1.6572)");
        geoPoint("J_{2}=$point(-4.10077,1.61479)");
        geoPoint("I_{2}=$point(-4.15979,1.60581)");
        geoPoint("N_{1}=$point(-4.41283,1.53998)");
    glEnd();
    //back wind shield-1
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("K_{2}=$point(-3.55287,1.6572)");
        geoPoint("L_{2}=$point(-3.2636,1.6574)");
        geoPoint("M_{2}=$point(-3.03868,1.6574)");
        geoPoint("N_{2}=$point(-2.91777,1.68918)");
        geoPoint("O_{2}=$point(-2.70411,1.79149)");
        geoPoint("V_{2}=$point(-2.51152,1.89983)");
        geoPoint("W_{2}=$point(-2.343,1.99612)");
        geoPoint("Z_{2}=$point(-2.16245,2.10145)");
        geoPoint("D_{3}=$point(-2.16006,2.22424)");
        geoPoint("E_{3}=$point(-2.21247,2.24073)");
    glEnd();
    //back wind shield-2
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("Z_{2}=$point(-2.16245,2.10145)");
        geoPoint("A_{3}=$point(-2.03519,2.16441)");
        geoPoint("P_{3}=$point(-2.02095,2.19193)");
        geoPoint("B_{3}=$point(-2.04107,2.21341)");
        geoPoint("C_{3}=$point(-2.0875,2.21497)");
    glEnd();
    //back wind shield-3
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("Z_{2}=$point(-2.16245,2.10145)");
        geoPoint("C_{3}=$point(-2.0875,2.21497)");
        geoPoint("D_{3}=$point(-2.16006,2.22424)");
    glEnd();

    //back tire back flap-1
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("O=$point(-4,0)");
        geoPoint("R_{3}=$point(-3.76117,-0.04746)");
        geoPoint("O_{3}=$point(-3.6044155385006333,0.08607220550752162)");
        geoPoint("P=$point(-3.88466,0.08789)");
    glEnd();
    //back tire back flap-2
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("R_{3}=$point(-3.76117,-0.04746)");
        geoPoint("S=$point(-3.6,-0.2)");
        geoPoint("O_{3}=$point(-3.6044155385006333,0.08607220550752162)");
    glEnd();
    //back 9
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("P=$point(-3.88466,0.08789)");
        geoPoint("O_{3}=$point(-3.6044155385006333,0.08607220550752162)");
        geoPoint("M_{2}=$point(-3.03868,1.6574)");
        geoPoint("L_{2}=$point(-3.2636,1.6574)");
    glEnd();
    //back 10
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("O_{3}=$point(-3.6044155385006333,0.08607220550752162)");
        geoPoint("Q_{3}=$point(-1.95196,0.08155)");
        geoPoint("F_{3}=$point(-2.3801827320273716,1.5712207195797614)");
        geoPoint("G_{3}=$point(-2.4,1.6)");
        geoPoint("M_{2}=$point(-3.03868,1.6574)");
    glEnd();

    //rear upper-1
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("M_{2}=$point(-3.03868,1.6574)");
        geoPoint("G_{3}=$point(-2.4,1.6)");
        geoPoint("H_{3}=$point(-2.37678,1.65085)");
        geoPoint("N_{2}=$point(-2.91777,1.68918)");
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("N_{2}=$point(-2.91777,1.68918)");
        geoPoint("H_{3}=$point(-2.37678,1.65085)");
        geoPoint("O_{2}=$point(-2.70411,1.79149)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("O_{2}=$point(-2.70411,1.79149)");
        geoPoint("H_{3}=$point(-2.37678,1.65085)");
        geoPoint("V_{2}=$point(-2.51152,1.89983)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("V_{2}=$point(-2.51152,1.89983)");
        geoPoint("H_{3}=$point(-2.37678,1.65085)");
        geoPoint("I_{3}=$point(-2.31036,1.73387)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("V_{2}=$point(-2.51152,1.89983)");
        geoPoint("I_{3}=$point(-2.31036,1.73387)");
        geoPoint("W_{2}=$point(-2.343,1.99612)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("W_{2}=$point(-2.343,1.99612)");
        geoPoint("I_{3}=$point(-2.31036,1.73387)");
        geoPoint("J_{3}=$point(-2.21224,1.82444)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("W_{2}=$point(-2.343,1.99612)");
        geoPoint("J_{3}=$point(-2.21224,1.82444)");
        geoPoint("Z_{2}=$point(-2.16245,2.10145)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("Z_{2}=$point(-2.16245,2.10145)");
        geoPoint("J_{3}=$point(-2.21224,1.82444)");
        geoPoint("L_{3}=$point(-2.05326,1.96718)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("Z_{2}=$point(-2.16245,2.10145)");
        geoPoint("L_{3}=$point(-2.05326,1.96718)");
        geoPoint("A_{3}=$point(-2.03519,2.16441)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("A_{3}=$point(-2.03519,2.16441)");
        geoPoint("L_{3}=$point(-2.05326,1.96718)");
        geoPoint("N_{3}=$point(-1.8616,2.09402)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("A_{3}=$point(-2.03519,2.16441)");
        geoPoint("N_{3}=$point(-1.8616,2.09402)");
        geoPoint("K_{3}=$point(-1.73871,2.16862)");
    glEnd();
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("A_{3}=$point(-2.03519,2.16441)");
        geoPoint("K_{3}=$point(-1.73871,2.16862)");
        geoPoint("P_{3}=$point(-2.02095,2.19193)");
    glEnd();









    glutSwapBuffers();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15.0, 15.0, -15.0, 15.0); // 2D Orthographic projection
    glLineWidth(2.0f); // set global line thickness
    glScalef(2.0f, 2.0f, 1.0f); // scale everything 2x in X and Y

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 768);
    glutCreateWindow("Car with Wheels");

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
