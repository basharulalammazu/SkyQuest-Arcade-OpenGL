#include <GL/glut.h>
#include <iostream>

int currentSelection = 0; // 0 = Level 1, 1 = Level 2, 2 = Level 3
const char *levels[] = {"Level 1", "Level 2", "Level 3"};
int mainWindow; // Main menu window ID
int levelWindow; // Level window ID

// Declare the keyboard function prototype
void keyboard(unsigned char key, int x, int y);






// *******************  Display function for Level 1  ***************************
void level1Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Show message for Level 1
    glRasterPos2i(-300, 0);  // Use integer positions
    const char *msg = "Level 1: Collect items (Press Esc to go back)";
    for (const char *c = msg; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glFlush();
}






// ********************  Display function for Level 2  **************************
void level2Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Show message for Level 2
    glRasterPos2i(-300, 0);  // Use integer positions
    const char *msg = "Level 2: Avoid obstacles (Press Esc to go back)";
    for (const char *c = msg; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glFlush();
}







// ********************  Display function for Level 3  **************************
void level3Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Show message for Level 3
    glRasterPos2i(-300, 0);  // Use integer positions
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
    glRasterPos2i(-100, 200);  // Use integer positions
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

        glRasterPos2i(-100, 100 - i * 50); // Position buttons with integer positions
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
    glutInitWindowSize(500, 400);
    glutInitWindowPosition(100, 100);
    mainWindow = glutCreateWindow("Level Selector");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color for the main menu

    glOrtho(-682, 682, -372, 372, -1, 1); // Set orthographic projection to integer values
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Register keyboard callback for main window

    glutMainLoop();
    return 0;
}
