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
    //top-1
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("E_{3}=$point(-2.21247,2.24073)");
        geoPoint("D_{3}=$point(-2.16006,2.22424)");
        geoPoint("C_{3}=$point(-2.0875,2.21497)");
        geoPoint("B_{3}=$point(-2.04107,2.21341)");
        geoPoint("M_{3}=$point(-2.10195,2.2719)");
    glEnd();
    //top-2
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("M_{3}=$point(-2.10195,2.2719)");
        geoPoint("B_{3}=$point(-2.04107,2.21341)");
        geoPoint("P_{3}=$point(-2.02095,2.19193)");
        geoPoint("K_{3}=$point(-1.73871,2.16862)");
        geoPoint("S_{3}=$point(-1.99698,2.2889)");
    glEnd();
    //top-3
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("S_{3}=$point(-1.99698,2.2889)");
        geoPoint("K_{3}=$point(-1.73871,2.16862)");
        geoPoint("T_{3}=$point(-1.87326,2.31053)");
    glEnd();
    //top-4
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("T_{3}=$point(-1.87326,2.31053)");
        geoPoint("K_{3}=$point(-1.73871,2.16862)");
        geoPoint("O_{4}=$point(-1.6086,2.23023)");
        geoPoint("U_{3}=$point(-1.66324,2.33074)");
    glEnd();
    //top-5
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("O_{4}=$point(-1.6086,2.23023)");
        geoPoint("Q_{4}=$point(-1.54313,2.25485)");
        geoPoint("U_{3}=$point(-1.66324,2.33074)");
    glEnd();
    //top-6
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("U_{3}=$point(-1.66324,2.33074)");
        geoPoint("Q_{4}=$point(-1.54313,2.25485)");
        geoPoint("P_{4}=$point(-1.48346,2.26623)");
        geoPoint("V_{3}=$point(-1.45647,2.34509)");
    glEnd();
    //top-7
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("V_{3}=$point(-1.45647,2.34509)");
        geoPoint("P_{4}=$point(-1.48346,2.26623)");
        geoPoint("R_{4}=$point(-1.32917,2.27823)");
        geoPoint("W_{3}=$point(-1.19555,2.36406)");
    glEnd();
    //top-8
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("W_{3}=$point(-1.19555,2.36406)");
        geoPoint("R_{4}=$point(-1.32917,2.27823)");
        geoPoint("S_{4}=$point(-1.00344,2.2857)");
    glEnd();
    //top-9
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("W_{3}=$point(-1.19555,2.36406)");
        geoPoint("S_{4}=$point(-1.00344,2.2857)");
        geoPoint("Z_{3}=$point(-0.80168,2.37766)");
    glEnd();
    //top-10
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("S_{4}=$point(-1.00344,2.2857)");
        geoPoint("T_{4}=$point(-0.62248,2.29231)");
        geoPoint("Z_{3}=$point(-0.80168,2.37766)");
    glEnd();
    //top-11
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("T_{4}=$point(-0.62248,2.29231)");
        geoPoint("A_{4}=$point(-0.60227,2.3797)");
        geoPoint("Z_{3}=$point(-0.80168,2.37766)");
    glEnd();
    //top-12
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("T_{4}=$point(-0.62248,2.29231)");
        geoPoint("B_{4}=$point(-0.39878,2.37224)");
        geoPoint("A_{4}=$point(-0.60227,2.3797)");
    glEnd();
    //top-13
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("T_{4}=$point(-0.62248,2.29231)");
        geoPoint("U_{4}=$point(-0.2965,2.2857)");
        geoPoint("B_{4}=$point(-0.39878,2.37224)");
    glEnd();
    //top-14
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("U_{4}=$point(-0.2965,2.2857)");
        geoPoint("C_{4}=$point(-0.20114,2.36353)");
        geoPoint("B_{4}=$point(-0.39878,2.37224)");
    glEnd();
    //top-15
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("U_{4}=$point(-0.2965,2.2857)");
        geoPoint("V_{4}=$point(-0.02451,2.27671)");
        geoPoint("D_{4}=$point(-0.01103,2.34976)");
        geoPoint("C_{4}=$point(-0.20114,2.36353)");
    glEnd();
    //top-16
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("V_{4}=$point(-0.02451,2.27671)");
        geoPoint("W_{4}=$point(0.18842,2.26386)");
        geoPoint("E_{4}=$point(0.18521,2.33105)");
        geoPoint("D_{4}=$point(-0.01103,2.34976)");
    glEnd();
    //top-17
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("W_{4}=$point(0.18842,2.26386)");
        geoPoint("Z_{4}=$point(0.32217,2.24258)");
        geoPoint("F_{4}=$point(0.36903,2.31243)");
        geoPoint("E_{4}=$point(0.18521,2.33105)");
    glEnd();
    //top-18
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("Z_{4}=$point(0.32217,2.24258)");
        geoPoint("A_{5}=$point(0.44833,2.20762)");
        geoPoint("G_{4}=$point(0.50101,2.28644)");
        geoPoint("F_{4}=$point(0.36903,2.31243)");
    glEnd();
    //top-19
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("A_{5}=$point(0.44833,2.20762)");
        geoPoint("B_{5}=$point(0.5737,2.1663)");
        geoPoint("J_{4}=$point(0.59434,2.2264)");
        geoPoint("G_{4}=$point(0.50101,2.28644)");
    glEnd();
    //top-20
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("G_{4}=$point(0.50101,2.28644)");
        geoPoint("J_{4}=$point(0.59434,2.2264)");
        geoPoint("I_{4}=$point(0.60449,2.2434)");
    glEnd();
    //top-21
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("G_{4}=$point(0.50101,2.28644)");
        geoPoint("I_{4}=$point(0.60449,2.2434)");
        geoPoint("H_{4}=$point(0.63659,2.257)");
    glEnd();
    //front-1
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("J_{4}=$point(0.59434,2.2264)");
        geoPoint("B_{5}=$point(0.5737,2.1663)");
        geoPoint("K_{4}=$point(0.61674,2.20341)");
    glEnd();
    //front-2
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("B_{5}=$point(0.5737,2.1663)");
        geoPoint("L_{4}=$point(0.66095,2.1816)");
        geoPoint("K_{4}=$point(0.61674,2.20341)");
    glEnd();
    //front-3
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("B_{5}=$point(0.5737,2.1663)");
        geoPoint("C_{5}=$point(0.68654,2.11592)");
        geoPoint("M_{4}=$point(0.71333,2.15332)");
        geoPoint("L_{4}=$point(0.66095,2.1816)");
    glEnd();
    //front-4
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("C_{5}=$point(0.68654,2.11592)");
        geoPoint("D_{5}=$point(0.8014,2.05547)");
        geoPoint("M_{4}=$point(0.71333,2.15332)");
    glEnd();
    //front-5
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("D_{5}=$point(0.8014,2.05547)");
        geoPoint("P_{5}=$point(1.12251,1.92411)");
        geoPoint("M_{4}=$point(0.71333,2.15332)");
    glEnd();
    //front-6
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("D_{5}=$point(0.8014,2.05547)");
        geoPoint("E_{5}=$point(1.19031,1.82575)");
        geoPoint("P_{5}=$point(1.12251,1.92411)");
    glEnd();
    //front-7
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("E_{5}=$point(1.19031,1.82575)");
        geoPoint("Q_{5}=$point(1.43564,1.73464)");
        geoPoint("P_{5}=$point(1.12251,1.92411)");
    glEnd();
    //front-8
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("E_{5}=$point(1.19031,1.82575)");
        geoPoint("F_{5}=$point(1.44018,1.66052)");
        geoPoint("Q_{5}=$point(1.43564,1.73464)");
    glEnd();
    //front-9
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("F_{5}=$point(1.44018,1.66052)");
        geoPoint("N_{4}=$point(1.84377,1.47202)");
        geoPoint("Q_{5}=$point(1.43564,1.73464)");
    glEnd();
    //front-10
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("F_{5}=$point(1.44018,1.66052)");
        geoPoint("G_{5}=$point(1.69535,1.44211)");
        geoPoint("N_{4}=$point(1.84377,1.47202)");
    glEnd();
    //front-11
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("G_{5}=$point(1.69535,1.44211)");
        geoPoint("S_{5}=$point(1.85892,1.45157) ");
        geoPoint("N_{4}=$point(1.84377,1.47202)");
    glEnd();
    //front wind shield-1
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("J_{4}=$point(0.59434,2.2264)");
        geoPoint("K_{4}=$point(0.61674,2.20341)");
        geoPoint("H_{4}=$point(0.63659,2.257)");
        geoPoint("I_{4}=$point(0.60449,2.2434)");
    glEnd();
    //front wind shield-2
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("K_{4}=$point(0.61674,2.20341)");
        geoPoint("L_{4}=$point(0.66095,2.1816)");
        geoPoint("D_{6}=$point(0.8,2.2)");
        geoPoint("H_{4}=$point(0.63659,2.257)");
     glEnd();
     //front wind shield-3
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("L_{4}=$point(0.66095,2.1816)");
        geoPoint("M_{4}=$point(0.71333,2.15332)");
        geoPoint("D_{6}=$point(0.8,2.2)");
     glEnd();
     //front wind shield-4
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("M_{4}=$point(0.71333,2.15332)");
        geoPoint("C_{6}=$point(1.03764,2.08992)");
        geoPoint("D_{6}=$point(0.8,2.2)");
     glEnd();
     //front wind shield-5
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("M_{4}=$point(0.71333,2.15332)");
        geoPoint("P_{5}=$point(1.12251,1.92411)");
        geoPoint("C_{6}=$point(1.03764,2.08992)");
     glEnd();
     //front wind shield-6
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("P_{5}=$point(1.12251,1.92411)");
        geoPoint("B_{6}=$point(1.5009,1.8349)");
        geoPoint("C_{6}=$point(1.03764,2.08992)");
     glEnd();
     //front wind shield-7
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("P_{5}=$point(1.12251,1.92411)");
        geoPoint("Q_{5}=$point(1.43564,1.73464)");
        geoPoint("B_{6}=$point(1.5009,1.8349)");
     glEnd();
     //front wind shield-8
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("Q_{5}=$point(1.43564,1.73464)");
        geoPoint("A_{6}=$point(2.05616,1.50344)");
        geoPoint("B_{6}=$point(1.5009,1.8349)");
     glEnd();
    //front wind shield-9
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("Q_{5}=$point(1.43564,1.73464)");
        geoPoint("N_{4}=$point(1.84377,1.47202)");
        geoPoint("A_{6}=$point(2.05616,1.50344)");
     glEnd();
     //front wind shield-10
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("N_{4}=$point(1.84377,1.47202)");
        geoPoint("R_{5}=$point(1.86499,1.46376)");
        geoPoint("T_{5}=$point(1.90382,1.4654)");
        geoPoint("U_{5}=$point(1.94261,1.46723)");
        geoPoint("V_{5}=$point(1.98544,1.4759)");
        geoPoint("W_{5}=$point(2.01435,1.48063)");
        geoPoint("Z_{5}=$point(2.03215,1.49)");
        geoPoint("A_{6}=$point(2.05616,1.50344)");
     glEnd();
     //window-1
     glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("F_{3}=$point(-2.3801827320273716,1.5712207195797614)");
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("H_{3}=$point(-2.37678,1.65085)");
        geoPoint("G_{3}=$point(-2.4,1.6)");
    glEnd();
    //window-2
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("I_{3}=$point(-2.31036,1.73387)");
        geoPoint("H_{3}=$point(-2.37678,1.65085)");
    glEnd();
    //window-3
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("J_{3}=$point(-2.21224,1.82444)");
        geoPoint("I_{3}=$point(-2.31036,1.73387)");
    glEnd();
    //window-4
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("L_{3}=$point(-2.05326,1.96718)");
        geoPoint("J_{3}=$point(-2.21224,1.82444)");
    glEnd();
    //window-5
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("N_{3}=$point(-1.8616,2.09402)");
        geoPoint("L_{3}=$point(-2.05326,1.96718)");
    glEnd();
    //window-6
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("K_{3}=$point(-1.73871,2.16862)");
        geoPoint("N_{3}=$point(-1.8616,2.09402)");
    glEnd();
    //window-7
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("O_{4}=$point(-1.6086,2.23023)");
        geoPoint("K_{3}=$point(-1.73871,2.16862)");
    glEnd();
    //window-8
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("Q_{4}=$point(-1.54313,2.25485)");
        geoPoint("O_{4}=$point(-1.6086,2.23023)");
    glEnd();
    //window-9
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("P_{4}=$point(-1.48346,2.26623)");
        geoPoint("Q_{4}=$point(-1.54313,2.25485)");
    glEnd();
    //window-10
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("R_{4}=$point(-1.32917,2.27823)");
        geoPoint("P_{4}=$point(-1.48346,2.26623)");
    glEnd();
    //window-11
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("S_{4}=$point(-1.00344,2.2857)");
        geoPoint("R_{4}=$point(-1.32917,2.27823)");
    glEnd();
    //window-12
     glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("T_{4}=$point(-0.62248,2.29231)");
        geoPoint("S_{4}=$point(-1.00344,2.2857)");
    glEnd();
    //window-13
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("I_{5}=$point(-0.46814,1.49184)");
        geoPoint("T_{4}=$point(-0.62248,2.29231)");
    glEnd();
    //window-14
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("I_{5}=$point(-0.46814,1.49184)");
        geoPoint("J_{5}=$point(0.19191,1.4735)");
        geoPoint("U_{4}=$point(-0.2965,2.2857)");
        geoPoint("T_{4}=$point(-0.62248,2.29231)");
    glEnd();
    //window-15
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("J_{5}=$point(0.19191,1.4735)");
        geoPoint("B_{5}=$point(0.5737,2.1663)");
        geoPoint("A_{5}=$point(0.44833,2.20762)");
        geoPoint("Z_{4}=$point(0.32217,2.24258)");
        geoPoint("W_{4}=$point(0.18842,2.26386)");
        geoPoint("V_{4}=$point(-0.02451,2.27671)");
        geoPoint("U_{4}=$point(-0.2965,2.2857)");
    glEnd();
    //window-16
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("G_{5}=$point(1.69535,1.44211)");
        geoPoint("F_{5}=$point(1.44018,1.66052)");
        geoPoint("L_{5}=$point(1.28893,1.45211)");
        geoPoint("F_{5}=$point(1.44018,1.66052)");
        geoPoint("E_{5}=$point(1.19031,1.82575)");
        geoPoint("L_{5}=$point(1.28893,1.45211)");
        geoPoint("K_{5}=$point(0.7939,1.45211)");
        geoPoint("E_{5}=$point(1.19031,1.82575)");
        geoPoint("D_{5}=$point(0.8014,2.05547)");
        geoPoint("K_{5}=$point(0.7939,1.45211)");
        geoPoint("D_{5}=$point(0.8014,2.05547)");
        geoPoint("C_{5}=$point(0.68654,2.11592)");
    glEnd();
    //window-17
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("J_{5}=$point(0.19191,1.4735)");
        geoPoint("K_{5}=$point(0.7939,1.45211)");
        geoPoint("C_{5}=$point(0.68654,2.11592)");
        geoPoint("B_{5}=$point(0.5737,2.1663)");
    glEnd();
    //body
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("Q_{3}=$point(-1.95196,0.08155)");
        geoPoint("I_{5}=$point(-0.46814,1.49184)");
        geoPoint("H_{5}=$point(-1.40626,1.53462)");
        geoPoint("F_{3}=$point(-2.3801827320273716,1.5712207195797614)");
    glEnd();
    //body-1
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("Q_{3}=$point(-1.95196,0.08155)");
        geoPoint("U=$point(2.18916,0.11667)");
        geoPoint("J_{5}=$point(0.19191,1.4735)");
        geoPoint("I_{5}=$point(-0.46814,1.49184)");
    glEnd();
    //body-2
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("U=$point(2.18916,0.11667)");
        geoPoint("G_{5}=$point(1.69535,1.44211)");
        geoPoint("L_{5}=$point(1.28893,1.45211)");
        geoPoint("K_{5}=$point(0.7939,1.45211)");
        geoPoint("J_{5}=$point(0.19191,1.4735)");
    glEnd();
    //body-3
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("U=$point(2.18916,0.11667)");
        geoPoint("V=$point(2.4,0.1)");
        geoPoint("S_{5}=$point(1.85892,1.45157)");
        geoPoint("G_{5}=$point(1.69535,1.44211)");
    glEnd();
    //lower side bumper 1
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("Q_{3}=$point(-1.95196,0.08155)");
        geoPoint("M_{5}=$point(-1.92319,-0.1978)");
        geoPoint("N_{5}=$point(-1.71607,-0.15579)");
    glEnd();
    //lower side bumper 2
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("Q_{3}=$point(-1.95196,0.08155)");
        geoPoint("N_{5}=$point(-1.71607,-0.15579)");
        geoPoint("W=$point(2.17429,-0.13702)");
        geoPoint("U=$point(2.18916,0.11667)");
    glEnd();
    //lower side bumper 3
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("W=$point(2.17429,-0.13702)");
        geoPoint("B_{1}=$point(2.39675,-0.12501)");
        geoPoint("V=$point(2.4,0.1)");
        geoPoint("U=$point(2.18916,0.11667)");
    glEnd();
    //lower side bumper 4
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("W=$point(2.17429,-0.13702)");
        geoPoint("Z=$point(2.29552,-0.24868)");
        geoPoint("A_{1}=$point(2.37528,-0.25187)");
        geoPoint("B_{1}=$point(2.39675,-0.12501)");
    glEnd();
    //lower side bumper 5
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("B_{1}=$point(2.39675,-0.12501)");
        geoPoint("O_{5}=$point(3.97921,-0.01359)");
        geoPoint("E_{6}=$point(3.99701,0.08181)");
        geoPoint("V=$point(2.4,0.1)");
    glEnd();
    //lower side bumper 6
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("F_{6}=$point(3.86,-0.02)");
        geoPoint("C_{1}=$point(3.95449,-0.05407)");
        geoPoint("D_{1}=$point(4.4,0)");
        geoPoint("O_{5}=$point(3.97921,-0.01359)");
    glEnd();

    //front hood-1
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("N_{4}=$point(1.84377,1.47202)");
        geoPoint("S_{5}=$point(1.85892,1.45157)");
        geoPoint("R_{5}=$point(1.86499,1.46376)");
    glEnd();
    //front hood-2
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("V=$point(2.4,0.1)");
        geoPoint("A_{6}=$point(2.05616,1.50344)");
        geoPoint("Z_{5}=$point(2.03215,1.49)");
        geoPoint("W_{5}=$point(2.01435,1.48063)");
        geoPoint("V_{5}=$point(1.98544,1.4759)");
        geoPoint("U_{5}=$point(1.94261,1.46723)");
        geoPoint("T_{5}=$point(1.90382,1.4654)");
        geoPoint("R_{5}=$point(1.86499,1.46376)");
        geoPoint("S_{5}=$point(1.85892,1.45157)");
    glEnd();
    //front hood-3
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("V=$point(2.4,0.1)");
        geoPoint("G_{6}=$point(2.45276,1.47459)");
        geoPoint("A_{6}=$point(2.05616,1.50344)");
    glEnd();
    //front hood-4
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("V=$point(2.4,0.1)");
        geoPoint("E_{6}=$point(3.99701,0.08181)");
        geoPoint("V_{6}=$point(4.09346,0.92912)");
        geoPoint("U_{6}=$point(4.0911,0.95748)");
        geoPoint("H_{6}=$point(2.92422,1.42564)");
        geoPoint("G_{6}=$point(2.45276,1.47459)");
    glEnd();
    //front hood-5
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("O_{5}=$point(3.97921,-0.01359)");
        geoPoint("D_{1}=$point(4.4,0)");
        geoPoint("E_{6}=$point(3.99701,0.08181)");
    glEnd();
    //front hood-6
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("E_{6}=$point(3.99701,0.08181)");
        geoPoint("D_{1}=$point(4.4,0)");
        geoPoint("E_{1}=$point(4.67869,0.02249)");
        geoPoint("F_{1}=$point(4.75336,0.1005)");
        geoPoint("G_{1}=$point(4.70882,0.21716)");
        geoPoint("H_{1}=$point(4.75761,0.3826)");
        geoPoint("I_{1}=$point(4.8276,0.44624)");
        geoPoint("J_{1}=$point(4.81275,0.70713)");
        geoPoint("K_{1}=$point(4.72342,0.74581)");
        geoPoint("A_{7}=$point(4.48097,0.75714)");
        geoPoint("Z_{6}=$point(4.25086,0.76157)");
        geoPoint("V_{6}=$point(4.09346,0.92912)");
    glEnd();
    //front hood-7
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("H_{6}=$point(2.92422,1.42564)");
        geoPoint("U_{6}=$point(4.0911,0.95748)");
        geoPoint("T_{6}=$point(4.097,0.98112)");
        geoPoint("I_{6}=$point(3.45365,1.35351)");
    glEnd();
    //front hood-8
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("T_{6}=$point(4.097,0.98112)");
        geoPoint("S_{6}=$point(4.12655,0.98821)");
        geoPoint("J_{6}=$point(3.74864,1.30069)");
        geoPoint("I_{6}=$point(3.45365,1.35351)");
    glEnd();
    //front hood-9
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("S_{6}=$point(4.12655,0.98821)");
        geoPoint("R_{6}=$point(4.2,1)");
        geoPoint("K_{6}=$point(4.04749,1.23629)");
        geoPoint("J_{6}=$point(3.74864,1.30069)");
    glEnd();
    //front hood-10
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("S_{6}=$point(4.12655,0.98821)");
        geoPoint("R_{6}=$point(4.2,1)");
        geoPoint("K_{6}=$point(4.04749,1.23629)");
        geoPoint("J_{6}=$point(3.74864,1.30069)");
    glEnd();
    //front hood-11
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("R_{6}=$point(4.2,1)");
        geoPoint("Q_{6}=$point(4.31207,1.00714)");
        geoPoint("L_{6}=$point(4.26003,1.17574)");
        geoPoint("K_{6}=$point(4.04749,1.23629)");
    glEnd();
    //front hood-12
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("Q_{6}=$point(4.31207,1.00714)");
        geoPoint("P_{6}=$point(4.63672,1.00284)");
        geoPoint("O_{6}=$point(4.56532,1.05079)");
        geoPoint("N_{6}=$point(4.48545,1.08815)");
        geoPoint("M_{6}=$point(4.38756,1.13581)");
        geoPoint("L_{6}=$point(4.26003,1.17574)");
    glEnd();
    //front light-1
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.75f, 0.75f, 0.75f); // Light gray
        geoPoint("A_{7}=$point(4.48097,0.75714)");
        geoPoint("K_{1}=$point(4.72342,0.74581)");
        geoPoint("B_{7}=$point(4.71883,0.8158)");
        geoPoint("C_{7}=$point(4.7,0.9)");
        geoPoint("D_{7}=$point(4.67007,0.96794)");
        geoPoint("P_{6}=$point(4.63672,1.00284)");
        geoPoint("Q_{6}=$point(4.31207,1.00714)");
    glEnd();
    //front light-2
    glBegin(GL_QUADS);
        glColor3f(0.75f, 0.75f, 0.75f); // Light gray
        geoPoint("A_{7}=$point(4.48097,0.75714)");
        geoPoint("Q_{6}=$point(4.31207,1.00714)");
        geoPoint("R_{6}=$point(4.2,1)");
        geoPoint("Z_{6}=$point(4.25086,0.76157)");
    glEnd();
    //front light-3
    glBegin(GL_TRIANGLES);
        glColor3f(0.75f, 0.75f, 0.75f); // Light gray
        geoPoint("Z_{6}=$point(4.25086,0.76157)");
        geoPoint("U_{6}=$point(4.0911,0.95748)");
        geoPoint("V_{6}=$point(4.09346,0.92912)");
    glEnd();
    //front light-4
    glBegin(GL_TRIANGLES);
        glColor3f(0.75f, 0.75f, 0.75f); // Light gray
        geoPoint("Z_{6}=$point(4.25086,0.76157)");
        geoPoint("T_{6}=$point(4.097,0.98112)");
        geoPoint("U_{6}=$point(4.0911,0.95748)");
    glEnd();
    //front light-5
    glBegin(GL_TRIANGLES);
        glColor3f(0.75f, 0.75f, 0.75f); // Light gray
        geoPoint("Z_{6}=$point(4.25086,0.76157)");
        geoPoint("S_{6}=$point(4.12655,0.98821)");
        geoPoint("T_{6}=$point(4.097,0.98112)");
    glEnd();
    //front light-6
    glBegin(GL_TRIANGLES);
        glColor3f(0.75f, 0.75f, 0.75f); // Light gray
        geoPoint("Z_{6}=$point(4.25086,0.76157)");
        geoPoint("R_{6}=$point(4.2,1)");
        geoPoint("S_{6}=$point(4.12655,0.98821)");
    glEnd();

    //cosmetics
    //back-1
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("P=$point(-4.52185,0.05462)");
        geoPoint("Q=$point(-4.53389,0.09402)");
        geoPoint("R=$point(-4.54265,0.12357)");
        geoPoint("S=$point(-4.54593,0.18049)");
        geoPoint("T=$point(-4.54374,0.21661)");
        geoPoint("U=$point(-4.53279,0.30089)");
        geoPoint("V=$point(-4.54375,0.39425)");
        geoPoint("W=$point(-4.54572,0.70724)");
        geoPoint("Z=$point(-4.54375,1.00252)");
    glEnd();

    //back-2
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("C=$point(-5.00848,1.28657)");
        geoPoint("D=$point(-4.97575,1.34604)");
        geoPoint("E=$point(-4.93571,1.41175)");
        geoPoint("F=$point(-4.89566,1.47746)");
        geoPoint("G=$point(-4.86486,1.51237)");
        geoPoint("H=$point(-4.77142,1.50929)");
        geoPoint("F_{5}=$point(-4.45153,1.51995)");
        geoPoint("G_{5}=$point(-4.42685,1.52574)");
        geoPoint("I=$point(-4.41115,1.54229) ");
        geoPoint("J=$point(-3.87931,1.56199)");
        geoPoint("K=$point(-3.65169,1.57731)");
        geoPoint("L=$point(-3.50724,1.59263)");
        geoPoint("M=$point(-3.39044,1.61255)");
        geoPoint("N=$point(-3.35271,1.62727)");
        geoPoint("O=$point(-3.32153,1.659)");
    glEnd();
    //oil
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("N_{1}=$point(-3.57643,1.42531)");
        geoPoint("M_{1}=$point(-3.57694,1.23332)");
        geoPoint("L_{1}=$point(-3.56838,1.20636)");
        geoPoint("K_{1}=$point(-3.54998,1.19138)");
        geoPoint("J_{1}=$point(-3.5243,1.1847)");
        geoPoint("I_{1}=$point(-3.24124,1.18613)");
        geoPoint("H_{1}=$point(-3.2147,1.18869)");
        geoPoint("G_{1}=$point(-3.19583,1.20052)");
        geoPoint("F_{1}=$point(-3.18929,1.22313) ");
        geoPoint("E_{1}=$point(-3.19,1.44)");
        geoPoint("D_{1}=$point(-3.19308,1.45037)");
        geoPoint("C_{1}=$point(-3.21445,1.47051)");
        geoPoint("B_{1}=$point(-3.23468,1.478) ");
        geoPoint("A_{1}=$point(-3.52713,1.47709)");
        geoPoint("P_{1}=$point(-3.5517,1.47243)");
        geoPoint("O_{1}=$point(-3.56997,1.45249)");
        geoPoint("N_{1}=$point(-3.57643,1.42531)");
    glEnd();
    //backdoor
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("H_{4}=$point(-2.34782,1.57894)");
        geoPoint("I_{4}=$point(-2.46498,1.50665)");
        geoPoint("J_{4}=$point(-2.53383,1.4523)");
        geoPoint("K_{4}=$point(-2.56645,1.407)");
        geoPoint("L_{4}=$point(-2.59363,1.33271)");
        geoPoint("M_{4}=$point(-2.61537,1.27291)");
        geoPoint("N_{4}=$point(-2.63893,1.18413)");
        geoPoint("O_{4}=$point(-2.64255,1.05186)");
        geoPoint("P_{4}=$point(-2.61537,1.00475)");
        geoPoint("Q_{4}=$point(-2.58819,0.97576)");
        geoPoint("R_{4}=$point(-2.53927,0.94677)");
        geoPoint("S_{4}=$point(-2.46136,0.90872)");
        geoPoint("T_{4}=$point(-2.37438,0.87067)");
        geoPoint("U_{4}=$point(-2.26929,0.80725)");
        geoPoint("V_{4}=$point(-2.16782,0.73115)");
        geoPoint("W_{4}=$point(-2.09535,0.6623)");
        geoPoint("Z_{4}=$point(-2.03374,0.58801)");
        geoPoint("A_{5}=$point(-1.96851,0.47748)");
        geoPoint("B_{5}=$point(-1.92684,0.39051)");
        geoPoint("C_{5}=$point(-1.89604,0.27092)");
        geoPoint("D_{5}=$point(-1.87973,0.19663)");
        geoPoint("E_{5}=$point(-1.88159,0.06548)");
    glEnd();
    //door handle back-1
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("G_{6}=$point(-2.45,1.3)");
        geoPoint("H_{6}=$point(-2.47522,1.27937)");
        geoPoint("I_{6}=$point(-2.49501,1.25738)");
        geoPoint("J_{6}=$point(-2.49428,1.17602)");
        geoPoint("U_{5}=$point(-2.47023,1.15369)");
        geoPoint("V_{5}=$point(-2.4459,1.14157)");
        geoPoint("W_{5}=$point(-2.42117,1.1311)");
        geoPoint("Z_{5}=$point(-2.11425,1.1311)");
        geoPoint("A_{6}=$point(-2.07795,1.15109)");
        geoPoint("B_{6}=$point(-2.07062,1.17308)");
        geoPoint("C_{6}=$point(-2.07355,1.25005)");
        geoPoint("D_{6}=$point(-2.10434,1.28156)");
        geoPoint("E_{6}=$point(-2.12926,1.29256)");
        geoPoint("F_{6}=$point(-2.15,1.3)");
        geoPoint("G_{6}=$point(-2.45,1.3)");
    glEnd();
    //door handle back-2
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("P_{6}=$point(-2.37334,1.2757)");
        geoPoint("Q_{6}=$point(-2.39679,1.25957)");
        geoPoint("K_{6}=$point(-2.39669,1.22011)");
        geoPoint("L_{6}=$point(-2.12119,1.21853)");
        geoPoint("M_{6}=$point(-2.11826,1.24931)");
        geoPoint("N_{6}=$point(-2.14612,1.26837)");
        geoPoint("O_{6}=$point(-2.16224,1.27423)");
    glEnd();
    //door divide
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("W_{2}=$point(-0.45126,0.03519)");
        geoPoint("Z_{2}=$point(-0.42218,0.2092)");
        geoPoint("A_{3}=$point(-0.38906,0.37089)");
        geoPoint("B_{3}=$point(-0.37542,0.53648)");
        geoPoint("C_{3}=$point(-0.37153,0.86181)");
        geoPoint("D_{3}=$point(-0.4027,1.23195)");
        geoPoint("E_{3}=$point(-0.45679,1.54279)");
    glEnd();
    //door handle front-1
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("V_{6}=$point(-0.22398,1.08977)");
        geoPoint("W_{6}=$point(0.0982,1.088)");
        geoPoint("Z_{6}=$point(0.12661,1.10486)");
        geoPoint("A_{7}=$point(0.13829,1.11822)");
        geoPoint("B_{7}=$point(0.1388,1.19001)");
        geoPoint("C_{7}=$point(0.12353,1.21343)");
        geoPoint("D_{7}=$point(0.09603,1.2394)");
        geoPoint("E_{7}=$point(0.08004,1.25125) ");
        geoPoint("F_{7}=$point(-0.21789,1.25312)");
        geoPoint("G_{7}=$point(-0.26,1.23758)");
        geoPoint("H_{7}=$point(-0.27296,1.22462)");
        geoPoint("R_{6}=$point(-0.28079,1.20427)");
        geoPoint("S_{6}=$point(-0.28167,1.14036)");
        geoPoint("T_{6}=$point(-0.26925,1.11373)");
        geoPoint("U_{6}=$point(-0.2444,1.09243)");
        geoPoint("V_{6}=$point(-0.22398,1.08977)");
    glEnd();
    //door handle front-2
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("I_{7}=$point(-0.18671,1.17397)");
        geoPoint("J_{7}=$point(0.09732,1.17297)");
        geoPoint("K_{7}=$point(0.0933,1.19881)");
        geoPoint("L_{7}=$point(0.08177,1.21577)");
        geoPoint("M_{7}=$point(0.07159,1.21984)");
        geoPoint("N_{7}=$point(0.06034,1.23079)");
        geoPoint("O_{7}=$point(-0.17193,1.23138)");
        geoPoint("P_{7}=$point(-0.18687,1.20763)");
        geoPoint("I_{7}=$point(-0.18671,1.17397)");
    glEnd();
    //front door divide
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("Q_{7}=$point(1.611,1.44835)");
        geoPoint("V_{2}=$point(1.71056,1.44766)");
        geoPoint("U_{2}=$point(1.83169,1.36471)");
        geoPoint("T_{2}=$point(1.9,1.3)");
        geoPoint("S_{2}=$point(1.91882,1.25581)");
        geoPoint("R_{2}=$point(1.94931,1.15562)");
        geoPoint("Q_{2}=$point(1.9798,0.99008)");
        geoPoint("P_{2}=$point(2,0.8)");
        geoPoint("O_{2}=$point(1.99128,0.59929)");
        geoPoint("N_{2}=$point(1.98421,0.50281)");
        geoPoint("M_{2}=$point(1.95697,0.37027)");
        geoPoint("L_{2}=$point(1.91354,0.23021)");
        geoPoint("K_{2}=$point(1.8667,0.10544)");
    glEnd();
    //hood divide
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("U_{3}=$point(1.98312,1.49486)");
        geoPoint("V_{3}=$point(2.04461,1.46063)");
        geoPoint("W_{3}=$point(2.09862,1.44215)");
        geoPoint("Z_{3}=$point(2.18532,1.42936)");
        geoPoint("A_{4}=$point(2.58327,1.40662)");
        geoPoint("B_{4}=$point(3.37207,1.31993)");
        geoPoint("C_{4}=$point(4.0557,1.19485)");
        geoPoint("D_{4}=$point(4.4,1.1)");
        geoPoint("E_{4}=$point(4.50482,1.04704)");
        geoPoint("F_{4}=$point(4.52183,1.02505)");
        geoPoint("G_{4}=$point(4.53223,1.00426)");
    glEnd();
    //front light divide
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("Q_{1}=$point(4.3101,1.00586)");
        geoPoint("R_{1}=$point(4.48091,0.76225)");
    glEnd();
    //front signal light
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.5f, 0.0f);
        geoPoint("U_{1}=$point(4.1365,0.94239)");
        geoPoint("V_{1}=$point(4.25877,0.80518)");
        geoPoint("S_{1}=$point(4.37731,0.80612)");
        geoPoint("T_{1}=$point(4.2653,0.94239)");
    glEnd();
    //line from light to front tire
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        geoPoint("Z_{1}=$point(4.2541,0.76505)");
        geoPoint("W_{1}=$point(3.72301,0.77252)");
    glEnd();
    //flood light
    glBegin(GL_POLYGON);
        glColor3f(0.75f, 0.75f, 0.75f); // Light gray
        geoPoint("H_{2}=$point(4.43524,0.3755)");
        geoPoint("G_{2}=$point(4.41978,0.3636)");
        geoPoint("F_{2}=$point(4.40312,0.33446)");
        geoPoint("E_{2}=$point(4.39777,0.28926)");
        geoPoint("D_{2}=$point(4.40191,0.22274)");
        geoPoint("C_{2}=$point(4.42582,0.20665)");
        geoPoint("B_{2}=$point(4.58098,0.20616)");
        geoPoint("A_{2}=$point(4.70744,0.21264)");
        geoPoint("J_{2}=$point(4.75282,0.36301)");
        geoPoint("I_{2}=$point(4.74806,0.37728)");
    glEnd();
    //side mirror
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 1.0f);
        geoPoint("G_{3}=$point(1.27436,1.46409)");
        geoPoint("F_{3}=$point(1.58503,1.47144)");
        geoPoint("T_{3}=$point(1.41246,1.60164)");
        geoPoint("S_{3}=$point(1.3926,1.64534)");
        geoPoint("R_{3}=$point(1.38307,1.68109)");
        geoPoint("Q_{3}=$point(1.36082,1.71049)");
        geoPoint("P_{3}=$point(1.3211,1.72876)");
        geoPoint("O_{3}=$point(1.23472,1.74933)");
        geoPoint("N_{3}=$point(1.07967,1.74802)");
        geoPoint("M_{3}=$point(1.06388,1.73263)");
        geoPoint("L_{3}=$point(1.05491,1.70735)");
        geoPoint("K_{3}=$point(1.05899,1.5777)");
        geoPoint("J_{3}=$point(1.07693,1.53693)");
        geoPoint("I_{3}=$point(1.10099,1.51285)");
        geoPoint("H_{3}=$point(1.17503,1.48215)");
    glEnd();


    glutSwapBuffers();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15.0, 15.0, -15.0, 15.0); // 2D Orthographic projection
    glLineWidth(1.0f); // set global line thickness
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
