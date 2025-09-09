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
