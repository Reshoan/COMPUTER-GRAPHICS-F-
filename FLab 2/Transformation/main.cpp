#include <windows.h>
#include <GL/glut.h>


void display() {
  glClear(GL_COLOR_BUFFER_BIT);


  //original triangle
    glBegin(GL_TRIANGLES);
        glColor3ub(255, 0, 0);
        glVertex2i(58,75);
        glVertex2i(45,45);
        glVertex2i(70,45);
    glEnd();

    //translation tx=12 ty=25
    glTranslatef(12,25,0);
    glBegin(GL_TRIANGLES);
        glColor3ub(0, 255, 0);
        glVertex2i(58,75);
        glVertex2i(45,45);
        glVertex2i(70,45);
    glEnd();

    //scaling sx=2, sy=3
    glScalef(2,3,0);
    glBegin(GL_TRIANGLES);
        glColor3ub(0, 0, 255);
        glVertex2i(58,75);
        glVertex2i(45,45);
        glVertex2i(70,45);
    glEnd();


    //rotation theta=-75 center of rotation (0,0)
    glRotatef(-75,0,0,0);
    glBegin(GL_TRIANGLES);
        glColor3ub(0, 0, 255);
        glVertex2i(58,75);
        glVertex2i(45,45);
        glVertex2i(70,45);
    glEnd();
  glFlush();




}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
  glutInit(&argc, argv);                 // Initialize GLUT
  glutCreateWindow("First OpenGL Lab-CG_G"); // Create a window with the given title
  glutInitWindowSize(320, 320);   // Set the window's initial width & height
  init();
  glutDisplayFunc(display); // Register display callback handler for window re-paint
  glutMainLoop();           // Enter the event-processing loop
  return 0;
}

