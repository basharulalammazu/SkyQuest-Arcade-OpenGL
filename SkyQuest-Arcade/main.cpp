#include <GL/glut.h>
#include <iostream>
#include<math.h>>

# define PI           3.14159265358979323846

int currentSelection = 0; // 0 = Level 1, 1 = Level 2, 2 = Level 3
const char *levels[] = {"Level 1", "Level 2", "Level 3"};
int mainWindow; // Main menu window ID
int levelWindow; // Level window ID

// Declare the keyboard function prototype
void keyboard(unsigned char key, int x, int y);






void circle() {
    int i;

	GLfloat x=0.0f; GLfloat y= -1.0f; GLfloat radius =1.0f;
	int triangleAmount = 100; //# of lines used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glColor3ub(220, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),
                        y + (radius * sin(i * twicePi / triangleAmount)) );
		}
	glEnd();
}



void item(){
    int i;

	GLfloat x=0.0f; GLfloat y= -1.0f; GLfloat radius =1.0f;
	int triangleAmount = 100; //# of lines used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glColor3ub(220, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),
                        y + (radius * sin(i * twicePi / triangleAmount)) );
		}
	glEnd();
}







void bg(){
    glColor3ub(50, 50, 50);
    glBegin(GL_POLYGON);
    glVertex2f (1.0f, 1.0f);
    glVertex2f (-1.0f, 1.0f);
    glVertex2f (-1.0f, -1.0f);
    glVertex2f (1.0f, -1.0f);
    glEnd();
}







void aircraft(){
    glColor3ub(244, 244, 244);
    glRasterPos2f(-0.95f, 0.9f);

    glBegin(GL_POLYGON);
    glVertex2f (-0.18f, 0.35f);
    glVertex2f (-0.2f, 0.35f);
    glVertex2f (-0.2f, 0.28f);
    glVertex2f (-0.18f, 0.28f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f (-0.17f, 0.35f);
    glVertex2f (0.075f, 0.35f);
    glVertex2f (0.085f, 0.329f);
    glVertex2f (0.085f, 0.329f);
    glVertex2f (0.15f, 0.315f);
    glVertex2f (0.085f, 0.305f);
    glVertex2f (0.075f, 0.28f);
    glVertex2f (-0.17f, 0.28f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f (-0.11f, 0.363f);
    glVertex2f (-0.13f, 0.58f);
    glVertex2f (-0.09f, 0.58f);
    glVertex2f (-0.013f, 0.363f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f (-0.11f, 0.267f);
    glVertex2f (-0.13f, 0.063f);
    glVertex2f (-0.09f, 0.063f);
    glVertex2f (-0.013f, 0.267f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f (-0.135f, 0.363);
    glVertex2f (-0.175f, 0.398f);
    glVertex2f (-0.195f, 0.45f);
    glVertex2f (-0.185f, 0.45f);
    glVertex2f (-0.178f, 0.363f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f (-0.135f, 0.267);
    glVertex2f (-0.175f, 0.254f);
    glVertex2f (-0.195f, 0.18f);
    glVertex2f (-0.185f, 0.18f);
    glVertex2f (-0.178f, 0.267f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f (-0.048f, 0.485);
    glVertex2f (-0.055f, 0.51f);
    glVertex2f (0.015f, 0.495f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f (-0.055f, 0.002+0.123);
    glVertex2f (-0.048f, 0.032f+0.123);
    glVertex2f (0.014f, 0.013f+0.123);
    glEnd();
}






// Display function for Level 1
void level1Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to gray and opaque

    bg();
    aircraft();
    circle();



    // Show message for Level 1
    glColor3ub(244, 244, 244);
    glRasterPos2f(-0.95f, 0.9f);
    const char *msg = "Score: ";
    for (const char *c = msg; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glFlush();
}










// Display function for Level 2
void level2Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to gray and opaque

    bg();
    circle();

    // Show message for Level 2
    glColor3ub(244, 244, 244);
    glRasterPos2f(-0.95f, 0.9f);
    const char *msg = "Level 2: Avoid obstacles (Press Esc to go back)";
    for (const char *c = msg; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glFlush();
}










// Display function for Level 3
void level3Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to gray and opaque

    bg();
    circle();

    // Show message for Level 3
    glColor3ub(244, 244, 244);
    glRasterPos2f(-0.95f, 0.9f);
    const char *msg = "Level 3: Bombs falling from the sky (Press Esc to go back)";
    for (const char *c = msg; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glFlush();
}











// Display function for the main menu (level selector)
void drawButtons() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Title
    glRasterPos2f(-0.2f, 0.4f);
    const char *title = "Select Level:";
    for (const char *c = title; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    // Draw buttons
    for (int i = 0; i < 3; ++i) {
        if (i == currentSelection)
            glColor3f(0.0, 1.0, 0.0); // Highlight selected button
        else
            glColor3f(1.0, 1.0, 1.0); // Normal color

        glRasterPos2f(-0.1f, 0.2f - i * 0.2f); // Position buttons
        for (const char *c = levels[i]; *c != '\0'; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }

    glFlush();
}













// Switch to the main menu (level selector)
void returnToMainMenu() {
    glutSetWindow(mainWindow); // Switch back to the main window
    glutDisplayFunc(drawButtons); // Set display function to the main menu
    glutPostRedisplay(); // Redraw the level selector screen
}

// Switch to Level 1 view
void openLevel1() {
    glutSetWindow(mainWindow); // Keep using the same window
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color for Level 1
    glutDisplayFunc(level1Display); // Register display callback for Level 1
    glutPostRedisplay(); // Redraw to display Level 1 content
}

// Switch to Level 2 view
void openLevel2() {
    glutSetWindow(mainWindow); // Keep using the same window
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color for Level 2
    glutDisplayFunc(level2Display); // Register display callback for Level 2
    glutPostRedisplay(); // Redraw to display Level 2 content
}

// Switch to Level 3 view
void openLevel3() {
    glutSetWindow(mainWindow); // Keep using the same window
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color for Level 3
    glutDisplayFunc(level3Display); // Register display callback for Level 3
    glutPostRedisplay(); // Redraw to display Level 3 content
}












void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {  // 27 is the ASCII code for Esc key
        returnToMainMenu(); // Return to the level selector
    } else {
        switch (key) {
            case 'w': // Move up
            case 'W':
                if (currentSelection > 0)
                    currentSelection--;
                break;
            case 's': // Move down
            case 'S':
                if (currentSelection < 2)
                    currentSelection++;
                break;
            case 13: // Enter key
                if (currentSelection == 0)
                    openLevel1();
                else if (currentSelection == 1)
                    openLevel2();
                else if (currentSelection == 2)
                    openLevel3();
                break;
        }
    }
    glutPostRedisplay();
}





void display() {
    drawButtons();
}




int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 400);
    glutInitWindowPosition(300, 100);
    mainWindow = glutCreateWindow("SkyQuest");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color for the main menu

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Register keyboard callback for main window

    glutMainLoop();
    return 0;
}
