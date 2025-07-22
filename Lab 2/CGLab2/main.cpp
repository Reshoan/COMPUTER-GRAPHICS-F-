#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

	//drawing the blue point in co-or (0.5,0.5)
    glPointSize(10);


    //drawing a line with vertex (-1,0) and (1,0)
    glBegin(GL_LINES);
        glColor3f(0,0,0);
        //X-Axis
        glVertex2f(-1,0);
        glVertex2f(1,0);
        //Y-Axis
        glVertex2f(0,-1);
        glVertex2f(0,1);
    glEnd();


    glBegin(GL_TRIANGLES);
        glColor3f(0,1,0);
        glVertex2f(-0.6, -0.2);
        glVertex2f(-0.6, -0.5);
        glVertex2f(-0.3, -0.5);
    glEnd();

    glBegin(GL_POINTS);
        glColor3f(0,0,1);
        glVertex2f(0.5 ,0.5);

        glColor3f(1,1,0);
        glVertex2f(0 ,0);

    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(-0.9, 0.9);
        glVertex2f(-0.9, 0.7);
        glVertex2f(-0.5, 0.7);
        glVertex2f(-0.5, 0.9);

        glColor3f(0, 1, 1);
        glVertex2f(-0.3, 0.8);
        glVertex2f(-0.3, 0.1);
        glVertex2f(-0.1, 0.1);
        glVertex2f(-0.1, 0.8);

    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(1, 0, 1);
        glVertex2f(0.5, -0.1);
        glVertex2f(0.2, -0.3);
        glVertex2f(0.3, -0.7);
        glVertex2f(0.7, -0.7);
        glVertex2f(0.8, -0.3);

    glEnd();

	glFlush();  // Render now
}
void displayB() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    glPointSize(5); // Set point size

    glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f); // Red wings
        // Left wing (mirrored points)
        glVertex2f(-0.4f, 0.2f);
        glVertex2f(-0.45f, 0.3f);
        glVertex2f(-0.35f, 0.4f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(-0.4f, -0.2f);
        glVertex2f(-0.45f, -0.3f);
        glVertex2f(-0.35f, -0.4f);
        glVertex2f(-0.5f, 0.0f);

        // Right wing
        glVertex2f(0.4f, 0.2f);
        glVertex2f(0.45f, 0.3f);
        glVertex2f(0.35f, 0.4f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.4f, -0.2f);
        glVertex2f(0.45f, -0.3f);
        glVertex2f(0.35f, -0.4f);
        glVertex2f(0.5f, 0.0f);

        glColor3f(0.0f, 0.0f, 0.0f); // Black body
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.0f, -0.1f);
    glEnd();

    glFlush();  // Render now
}
void displayBfly() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2); // Smaller points for more density

    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.2f, 0.8f); // Butterfly wing color

    for (float x = -0.5f; x <= 0.5f; x += 0.01f) {
        for (float y = -0.5f; y <= 0.5f; y += 0.01f) {
            float r = x * x + y * y;
            // Define butterfly wing shape: heart-like or circular pattern
            if ((x < 0 && r < 0.15f) || (x > 0 && r < 0.15f)) {
                glVertex2f(x, y);
            }
        }
    }

    glColor3f(0.0f, 0.0f, 0.0f); // Body color
    for (float y = -0.1f; y <= 0.1f; y += 0.01f) {
        glVertex2f(0.0f, y);
    }

    glEnd();
    glFlush();
}
void displayQuad() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    glPointSize(5); // Set point size

    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f); // Red wings
        // Left wing (mirrored points)
        glVertex2f(-0.4f, 0.2f);
        glVertex2f(-0.45f, 0.3f);
        glVertex2f(-0.35f, 0.4f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(-0.4f, -0.2f);
        glVertex2f(-0.45f, -0.3f);
        glVertex2f(-0.35f, -0.4f);
        glVertex2f(-0.5f, 0.0f);

        // Right wing
        glVertex2f(0.4f, 0.2f);
        glVertex2f(0.45f, 0.3f);
        glVertex2f(0.35f, 0.4f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.4f, -0.2f);
        glVertex2f(0.45f, -0.3f);
        glVertex2f(0.35f, -0.4f);
        glVertex2f(0.5f, 0.0f);

        glColor3f(0.0f, 0.0f, 0.0f); // Black body
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.0f, -0.1f);
    glEnd();

    glFlush();  // Render now
}
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutCreateWindow("First OpenGL Lab-CG_G"); // Create a window with the given title
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutMainLoop();           // Enter the event-processing loop
	return 0;
}
