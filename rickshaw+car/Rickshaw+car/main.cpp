// --------- Scene ----------
void drawGround() {
    // Sky (top quarter = 180 units)
    glColor3f(0.82f, 0.93f, 0.99f);
    glBegin(GL_QUADS);
    glVertex2f(-worldHalfW, 180);
    glVertex2f(worldHalfW, 180);
    glVertex2f(worldHalfW, worldHalfH);   // +360
    glVertex2f(-worldHalfW, worldHalfH);
    glEnd();

    // Road (bottom 3/4 = 540 units)
    glColor3f(0.92f, 0.92f, 0.92f);
    glBegin(GL_QUADS);
    glVertex2f(-worldHalfW, -worldHalfH); // -360
    glVertex2f(worldHalfW, -worldHalfH);
    glVertex2f(worldHalfW, 180);
    glVertex2f(-worldHalfW, 180);
    glEnd();

    // --- Lane dividers ---
    glLineWidth(3.0f);
    glColor3f(0.7f, 0.7f, 0.7f);

    // Top divider
    glBegin(GL_LINES);
    glVertex2f(-worldHalfW, 30);
    glVertex2f(worldHalfW, 30);
    glEnd();

    // between middle & bottom
    glBegin(GL_LINES);
    glVertex2f(-worldHalfW, -150);
    glVertex2f(worldHalfW, -150);
    glEnd();

    // --- Lane speed text ---
    glColor3f(0, 0, 0);          // black text
    void *font = GLUT_BITMAP_HELVETICA_18;

    // Top lane
    glRasterPos2f(-600, laneY[0] - 10);   // slightly below center
    const char *lane1 = "Speed Limit: 40 km/h";
    for (const char* p = lane1; *p; ++p) glutBitmapCharacter(font, *p);

    // Middle lane
    glRasterPos2f(-600, laneY[1] - 10);
    const char *lane2 = "Speed Limit: 40 km/h";
    for (const char* p = lane2; *p; ++p) glutBitmapCharacter(font, *p);

    // Bottom lane (fast)
    glRasterPos2f(-600, laneY[2] - 10);
    const char *lane3 = "Speed Limit: 80 km/h (fast lane)";
    for (const char* p = lane3; *p; ++p) glutBitmapCharacter(font, *p);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGround();

    // Draw car and rickshaw (order so closer object can overlay)
    drawRickshaw(rickshawX, rickshawY, rickshawScale, rickshawWheelAngle);
    drawCar(carX, carY, carScale, carWheelAngle);

    // HUD text
    glColor3f(0, 0, 0);
    glRasterPos2f(-worldHalfW + 10, worldHalfH - 20);
    char buf[256];
    std::snprintf(buf, sizeof(buf), "Rickshaw speed: %.0f km/h  |  Car speed: %.0f km/h  |  %s",
                  rickshawSpeed, carSpeed, paused ? "Paused" : "Running");
    for (const char* p = buf; *p; ++p) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);

    // small legend for controls
    glRasterPos2f(-worldHalfW + 10, worldHalfH - 40);
    const char *legend = "Rickshaw: A/D move, W/S speed, Q/E lane.  Car: Arrow keys move, i/k speed, z/x lane.  Mouse L/R = shrink/enlarge both.";
    for (const char* p = legend; *p; ++p) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p);

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
        // compute wheel angular velocity for each vehicle
        // Rickshaw movement
        rickshawX += rickshawSpeed * dt;
        if (rickshawX > worldHalfW + 160.0f) rickshawX = -worldHalfW - 160.0f;
        if (rickshawX < -worldHalfW - 160.0f) rickshawX = worldHalfW + 160.0f;

        float rwheelRadius = 28.0f;
        float romega = (rickshawSpeed / rwheelRadius) * 180.0f / 3.1415926535f;
        rickshawWheelAngle = std::fmod(rickshawWheelAngle - romega * dt, 360.0f);

        // Car movement, but check for jam (if rickshaw is ahead in same lane and close)
        bool jam = false;
        float jamThreshold = 140.0f; // horizontal proximity threshold for jam
        if (carLane == rickshawLane) {
            // if rickshaw is in front (x greater than car) and within threshold -> jam
            if ((rickshawX > carX) && (fabs(rickshawX - carX) < jamThreshold)) {
                jam = true;
            }
            // also if car is in front and close and moving slower, it still causes no jam for car
        }

        float carEffectiveSpeed = jam ? min(carSpeed, rickshawSpeed) : carSpeed;
        // Move car
        carX += carEffectiveSpeed * dt;
        if (carX > worldHalfW + 200.0f) carX = -worldHalfW - 200.0f;
        if (carX < -worldHalfW - 200.0f) carX = worldHalfW + 200.0f;

        float cwheelRadius = 28.0f;
        float comega = (carEffectiveSpeed / cwheelRadius) * 180.0f / 3.1415926535f;
        carWheelAngle = std::fmod(carWheelAngle - comega * dt, 360.0f);

        // chain offset (visual)
        chainOffset += (romega * dt) / 360.0f;
        chainOffset = fmod(chainOffset, 1.0f);
    }

    // Smooth lane switching (both vehicles)
    float laneSpeed = 200.0f; // units per second (adjust smoothness)
    if (fabs(rickshawY - rickshawTargetY) > 1.0f) {
        if (rickshawY < rickshawTargetY) rickshawY += laneSpeed * dt;
        else if (rickshawY > rickshawTargetY) rickshawY -= laneSpeed * dt;
    } else {
        rickshawY = rickshawTargetY;
    }

    if (fabs(carY - carTargetY) > 1.0f) {
        if (carY < carTargetY) carY += laneSpeed * dt;
        else if (carY > carTargetY) carY -= laneSpeed * dt;
    } else {
        carY = carTargetY;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 27: exit(0); break; // Esc
        case ' ': paused = !paused; break;
        case 'r': case 'R':
            // reset both vehicles
            rickshawX = -250.0f; rickshawWheelAngle = 0.0f; rickshawSpeed = 40.0f; paused = false;
            rickshawLane = 1; rickshawY = laneY[rickshawLane]; rickshawTargetY = rickshawY;
            carX = 50.0f; carWheelAngle = 0.0f; carSpeed = 80.0f;
            carLane = 2; carY = laneY[carLane]; carTargetY = carY;
            break;

        // Rickshaw controls (existing)
        case 'a': case 'A': rickshawX -= 10.0f; break;
        case 'd': case 'D': rickshawX += 10.0f; break;
        case 'w': case 'W': rickshawSpeed = clamp(rickshawSpeed + 20.0f, 0.0f, 400.0f); break;
        case 's': case 'S': rickshawSpeed = clamp(rickshawSpeed - 20.0f, 0.0f, 400.0f); break;

        // Rickshaw lane switching with safety check
        case 'q': case 'Q': // move UP a lane (index lower)
            if (rickshawLane > 0) {
                int desired = rickshawLane - 1;
                // if desired lane is occupied by car, only allow change if rickshaw is entirely before or after car
                if (desired == carLane) {
                    float safeGap = 140.0f;
                    if ( (rickshawX + safeGap < carX) || (rickshawX - safeGap > carX) ) {
                        rickshawLane = desired;
                        rickshawTargetY = laneY[rickshawLane];
                    } else {
                        // deny lane change (unsafe)
                        // optionally you could flash or give feedback; we just ignore the request
                    }
                } else {
                    rickshawLane = desired;
                    rickshawTargetY = laneY[rickshawLane];
                }
            }
            break;

        case 'e': case 'E': // move DOWN a lane (index higher)
            if (rickshawLane < 2) {
                int desired = rickshawLane + 1;
                if (desired == carLane) {
                    float safeGap = 140.0f;
                    if ( (rickshawX + safeGap < carX) || (rickshawX - safeGap > carX) ) {
                        rickshawLane = desired;
                        rickshawTargetY = laneY[rickshawLane];
                    } else {
                        // deny change
                    }
                } else {
                    rickshawLane = desired;
                    rickshawTargetY = laneY[rickshawLane];
                }
            }
            break;

        // Car controls (different keys)
        case 'i': case 'I': carSpeed = clamp(carSpeed + 20.0f, 0.0f, 400.0f); break;
        case 'k': case 'K': carSpeed = clamp(carSpeed - 20.0f, 0.0f, 400.0f); break;

        // Car lane switching (z/x) - no extra safety: car can switch lanes freely
        case 'z': case 'Z':
            if (carLane > 0) { carLane--; carTargetY = laneY[carLane]; }
            break;
        case 'x': case 'X':
            if (carLane < 2) { carLane++; carTargetY = laneY[carLane]; }
            break;

        default:
            break;
    }
}

// Special (arrow keys) for car left/right
void specialKeys(int key, int, int) {
    switch(key) {
        case GLUT_KEY_LEFT: carX -= 10.0f; break;
        case GLUT_KEY_RIGHT: carX += 10.0f; break;
        case GLUT_KEY_UP: carSpeed = clamp(carSpeed + 10.0f, 0.0f, 400.0f); break;
        case GLUT_KEY_DOWN: carSpeed = clamp(carSpeed - 10.0f, 0.0f, 400.0f); break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int mx, int my) {
    if (state == GLUT_DOWN) {  // only act on press
        if (button == GLUT_LEFT_BUTTON) {
            // shrink both vehicles
            rickshawScale = clamp(rickshawScale - 5.0f, 5.0f, 200.0f);
            carScale = clamp(carScale - 5.0f, 10.0f, 300.0f);
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            // enlarge both vehicles
            rickshawScale = clamp(rickshawScale + 5.0f, 5.0f, 200.0f);
            carScale = clamp(carScale + 5.0f, 10.0f, 300.0f);
        }
        glutPostRedisplay(); // redraw scene
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
    // initial lanes/positions
    rickshawLane = 1; rickshawY = laneY[rickshawLane]; rickshawTargetY = rickshawY;
    carLane = 2; carY = laneY[carLane]; carTargetY = carY;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Bangladesh Rickshaw and Car - Lanes & Jam Logic");

    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse); // bind mouse

    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}
