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

	GLfloat x=0.0f; GLfloat y= -1.4f; GLfloat radius =1.0f;
	int triangleAmount = 100; //# of lines used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glColor3ub(38, 18, 0);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),
                        y + (radius * sin(i * twicePi / triangleAmount)) );
		}
	glEnd();
}



void item(GLfloat x, GLfloat y) {

    int i;

    GLfloat radius = 0.05f; // Radius of the circle
    int triangleAmount = 200; // Number of triangles used to draw the circle
    GLfloat twicePi = 2.0f * PI;

    glColor3ub(251, 176, 20); // Set color of the circle
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // Center of the circle
        for(i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
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
    glColor3ub(140, 140, 140);

    glBegin(GL_POLYGON);
    glVertex2f (-0.09f, 0.43f);
    glVertex2f (-0.058f, 0.445f);
    glVertex2f (0.045f, 0.445f);
    glVertex2f (0.045f, 0.415f);
    glVertex2f (-0.058f, 0.415f);
    glVertex2f (-0.09f, 0.43f);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f (-0.083f, 0.475f);
    glVertex2f (-0.055f, 0.428f);
    glVertex2f (-0.083f, 0.385f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f (-0.05f, 0.55f);
    glVertex2f (0.035f, 0.428f);
    glVertex2f (-0.02f, 0.428f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f (-0.02f, 0.428f);
    glVertex2f (0.035f, 0.428f);
    glVertex2f (-0.05f, 0.315f);
    glEnd();

    int i;

	GLfloat x=0.0465f; GLfloat y= 0.428f; GLfloat radius =0.0204f;
	int triangleAmount = 300; //# of lines used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glColor3ub(2, 65, 101);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),
                        y + (radius * sin(i * twicePi / triangleAmount)) );
		}
	glEnd();
}




void hills_trees(){
    //Hills

    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);
    glVertex2f (-0.96, -1.0);
    glVertex2f (-0.77, -0.64);
    glVertex2f (0.4, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);
    glVertex2f (0.96, -1.0);
    glVertex2f (0.77, -0.64);
    glVertex2f (-0.4, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);
    glVertex2f (-0.735, -0.68);
    glVertex2f (-0.32, -0.32);
    glVertex2f (0.2, -0.415);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);
    glVertex2f (0.735, -0.68);
    glVertex2f (0.32, -0.32);
    glVertex2f (-0.2, -0.415);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);
    glVertex2f (-0.3, -0.6);
    glVertex2f (0.05, -0.275);
    glVertex2f (0.45, -0.6);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);
    glVertex2f (-0.3, -0.6);
    glVertex2f (-0.12, -0.29);
    glVertex2f (0.45, -0.6);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);
    glVertex2f (-0.75, -0.807);
    glVertex2f (-0.6, -0.5);
    glVertex2f (0.0, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);
    glVertex2f (0.75, -0.807);
    glVertex2f (0.6, -0.5);
    glVertex2f (0.0, -0.5);
    glEnd();

    //Trees

    //Tree 1
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (-0.59, -0.7);
    glVertex2f (-0.6, -0.7);
    glVertex2f (-0.6, -0.61);
    glVertex2f (-0.59, -0.61);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56, -0.66);
    glVertex2f (-0.595, -0.61);
    glVertex2f (-0.63, -0.66);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.005, -0.66+0.03);
    glVertex2f (-0.595, -0.61+0.03);
    glVertex2f (-0.63+0.005, -0.66+0.03);
    glEnd();


    //Tree 2
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (-0.59+0.2, -0.7-0.1);
    glVertex2f (-0.6+0.2, -0.7-0.1);
    glVertex2f (-0.6+0.2, -0.61-0.1);
    glVertex2f (-0.59+0.2, -0.61-0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56+0.2, -0.66-0.1);
    glVertex2f (-0.595+0.2, -0.61-0.1);
    glVertex2f (-0.63+0.2, -0.66-0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.005+0.2, -0.66+0.03-0.1);
    glVertex2f (-0.595+0.2, -0.61+0.03-0.1);
    glVertex2f (-0.63+0.005+0.2, -0.66+0.03-0.1);
    glEnd();

    //Tree 3
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (-0.59+0.5, -0.7+0.25);
    glVertex2f (-0.6+0.5, -0.7+0.25);
    glVertex2f (-0.6+0.5, -0.61+0.25);
    glVertex2f (-0.59+0.5, -0.61+0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56+0.5, -0.66+0.25);
    glVertex2f (-0.595+0.5, -0.61+0.25);
    glVertex2f (-0.63+0.5, -0.66+0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.005+0.5, -0.66+0.03+0.25);
    glVertex2f (-0.595+0.5, -0.61+0.03+0.25);
    glVertex2f (-0.63+0.005+0.5, -0.66+0.03+0.25);
    glEnd();

    //Tree 4
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (-0.59+0.6, -0.7+0.12);
    glVertex2f (-0.6+0.6, -0.7+0.12);
    glVertex2f (-0.6+0.6, -0.61+0.12);
    glVertex2f (-0.59+0.6, -0.61+0.12);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56+0.6, -0.66+0.12);
    glVertex2f (-0.595+0.6, -0.61+0.12);
    glVertex2f (-0.63+0.6, -0.66+0.12);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.005+0.6, -0.66+0.03+0.12);
    glVertex2f (-0.595+0.6, -0.61+0.03+0.12);
    glVertex2f (-0.63+0.005+0.6, -0.66+0.03+0.12);
    glEnd();

    //Tree 5
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (-0.59+0.25, -0.7+0.18);
    glVertex2f (-0.6+0.25, -0.7+0.18);
    glVertex2f (-0.6+0.25, -0.61+0.18);
    glVertex2f (-0.59+0.25, -0.61+0.18);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56+0.25, -0.66+0.18);
    glVertex2f (-0.595+0.25, -0.61+0.18);
    glVertex2f (-0.63+0.25, -0.66+0.18);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.005+0.25, -0.66+0.03+0.18);
    glVertex2f (-0.595+0.25, -0.61+0.03+0.18);
    glVertex2f (-0.63+0.005+0.25, -0.66+0.03+0.18);
    glEnd();

    //Tree 6
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (-0.59-0.15, -0.7-0.18);
    glVertex2f (-0.6-0.15, -0.7-0.18);
    glVertex2f (-0.6-0.15, -0.61-0.18);
    glVertex2f (-0.59-0.15, -0.61-0.18);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.15, -0.66-0.18);
    glVertex2f (-0.595-0.15, -0.61-0.18);
    glVertex2f (-0.63-0.15, -0.66-0.18);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.005-0.15, -0.66+0.03-0.18);
    glVertex2f (-0.595-0.15, -0.61+0.03-0.18);
    glVertex2f (-0.63+0.005-0.15, -0.66+0.03-0.18);
    glEnd();

    //Tree 7
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (-0.59+0.35, -0.7-0.25);
    glVertex2f (-0.6+0.35, -0.7-0.25);
    glVertex2f (-0.6+0.35, -0.61-0.25);
    glVertex2f (-0.59+0.35, -0.61-0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56+0.35, -0.66-0.25);
    glVertex2f (-0.595+0.35, -0.61-0.25);
    glVertex2f (-0.63+0.35, -0.66-0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.005+0.35, -0.66+0.03-0.25);
    glVertex2f (-0.595+0.35, -0.61+0.03-0.25);
    glVertex2f (-0.63+0.005+0.35, -0.66+0.03-0.25);
    glEnd();

    //Tree 8
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (-0.59+0.6, -0.7-0.25);
    glVertex2f (-0.6+0.6, -0.7-0.25);
    glVertex2f (-0.6+0.6, -0.61-0.25);
    glVertex2f (-0.59+0.6, -0.61-0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56+0.6, -0.66-0.25);
    glVertex2f (-0.595+0.6, -0.61-0.25);
    glVertex2f (-0.63+0.6, -0.66-0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.005+0.6, -0.66+0.03-0.25);
    glVertex2f (-0.595+0.6, -0.61+0.03-0.25);
    glVertex2f (-0.63+0.005+0.6, -0.66+0.03-0.25);
    glEnd();

    //Tree 9
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (-0.59+0.75, -0.7+0.21);
    glVertex2f (-0.6+0.75, -0.7+0.21);
    glVertex2f (-0.6+0.75, -0.61+0.21);
    glVertex2f (-0.59+0.75, -0.61+0.21);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56+0.75, -0.66+0.21);
    glVertex2f (-0.595+0.75, -0.61+0.21);
    glVertex2f (-0.63+0.75, -0.66+0.21);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (-0.56-0.005+0.75, -0.66+0.03+0.21);
    glVertex2f (-0.595+0.75, -0.61+0.03+0.21);
    glVertex2f (-0.63+0.005+0.75, -0.66+0.03+0.21);
    glEnd();

    //Tree 10
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (0.59-0.15, -0.7-0.18);
    glVertex2f (0.6-0.15, -0.7-0.18);
    glVertex2f (0.6-0.15, -0.61-0.18);
    glVertex2f (0.59-0.15, -0.61-0.18);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (0.56-0.15, -0.66-0.18);
    glVertex2f (0.595-0.15, -0.61-0.18);
    glVertex2f (0.63-0.15, -0.66-0.18);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (0.56-0.005-0.15, -0.66+0.03-0.18);
    glVertex2f (0.595-0.15, -0.61+0.03-0.18);
    glVertex2f (0.63+0.005-0.15, -0.66+0.03-0.18);
    glEnd();


    //Tree 11
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (0.59, -0.7);
    glVertex2f (0.6, -0.7);
    glVertex2f (0.6, -0.61);
    glVertex2f (0.59, -0.61);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (0.56, -0.66);
    glVertex2f (0.595, -0.61);
    glVertex2f (0.63, -0.66);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (0.56-0.005, -0.66+0.03);
    glVertex2f (0.595, -0.61+0.03);
    glVertex2f (0.63+0.005, -0.66+0.03);
    glEnd();

    //Tree 12
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (0.59+0.15, -0.7-0.25);
    glVertex2f (0.6+0.15, -0.7-0.25);
    glVertex2f (0.6+0.15, -0.61-0.25);
    glVertex2f (0.59+0.15, -0.61-0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (0.56+0.15, -0.66-0.25);
    glVertex2f (0.595+0.15, -0.61-0.25);
    glVertex2f (0.63+0.15, -0.66-0.25);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (0.56-0.005+0.15, -0.66+0.03-0.25);
    glVertex2f (0.595+0.15, -0.61+0.03-0.25);
    glVertex2f (0.63+0.005+0.15, -0.66+0.03-0.25);
    glEnd();

    //Tree 13
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f (0.59-0.3, -0.7);
    glVertex2f (0.6-0.3, -0.7);
    glVertex2f (0.6-0.3, -0.61);
    glVertex2f (0.59-0.3, -0.61);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (0.56-0.3, -0.66);
    glVertex2f (0.595-0.3, -0.61);
    glVertex2f (0.63-0.3, -0.66);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f (0.56-0.005-0.3, -0.66+0.03);
    glVertex2f (0.595-0.3, -0.61+0.03);
    glVertex2f (0.63+0.005-0.3, -0.66+0.03);
    glEnd();
}





// Display function for Level 1
void level1Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to gray and opaque

    bg();
    aircraft();
    circle();
    item(0.75, 0.75);
    item(0.6, 0.42);
    item(0.8, 0.16);
    hills_trees();

    // Show message for Level 1
    glColor3ub(244, 244, 244);
    glRasterPos2f(-0.95f, 0.9f);
    const char *msg = "Score: ";
    for (const char *c = msg; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glFlush();
}









































































































































void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void level2Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
     circle();


     //Background of level 2
    glBegin(GL_POLYGON);
     glColor3f(0.0f, 0.0f, 0.2f); // Dark blue
    glVertex2f (1.0f, 1.0f);
    glVertex2f (-1.0f, 1.0f);
    glColor3f(0.1f, 0.1f, 0.3f); // light blue
    glVertex2f (-1.0f, -1.0f);
    glVertex2f (1.0f, -1.0f);
    glEnd();
     glColor3ub(230, 245, 255);
    drawCircle(-0.8f, 0.6f, 0.02f, 20); //snowflake
    drawCircle(-0.4f, 0.7f, 0.02f, 20);
    drawCircle(0.3f, 0.5f, 0.02f, 20);
    drawCircle(0.6f, 0.8f, 0.02f, 20);
    drawCircle(-0.1f, 0.9f, 0.02f, 20);

     glEnd();     // moon
     circle();
       glColor3ub(255, 236, 179); // yellow
       drawCircle(0.7f, 0.7f, 0.15f, 100);


        glColor4f(1.0f, 0.925f, 0.702f, 0.2f); // light yellow
        drawCircle(0.7f, 0.7f, 0.18f, 100);





    // house 1
    glColor3ub(100, 100, 150); // Dim colors for night
    glBegin(GL_POLYGON);
        glVertex2f(-0.2f, -0.5f);
        glVertex2f(0.2f, -0.5f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(-0.2f, -0.2f);
    glEnd();

    // house 1 roof
    glColor3ub(80, 50, 50);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.25f, -0.2f);
        glVertex2f(0.25f, -0.2f);
        glVertex2f(0.0f, 0.0f);
    glEnd();

    // house 1 door
    glColor3ub(60, 40, 30);
     glBegin(GL_POLYGON);
        glVertex2f(-0.05f, -0.5f);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.05f, -0.35f);
        glVertex2f(-0.05f, -0.35f);
    glEnd();


    // house 2 base
    glColor3ub(120, 120, 180);
    glBegin(GL_POLYGON);
        glVertex2f(0.3f, -0.5f);
        glVertex2f(0.7f, -0.5f);
        glVertex2f(0.7f, -0.2f);
        glVertex2f(0.3f, -0.2f);
    glEnd();

    // house 2 roof
    glColor3ub(90, 60, 60);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.25f, -0.2f);
        glVertex2f(0.75f, -0.2f);
        glVertex2f(0.5f, 0.0f);
    glEnd();

    // house 2 door
    glColor3ub(60, 40, 30);
    glBegin(GL_POLYGON);
        glVertex2f(0.45f, -0.5f);
        glVertex2f(0.55f, -0.5f);
        glVertex2f(0.55f, -0.35f);
        glVertex2f(0.45f, -0.35f);
    glEnd();


// Draw trees
    // Tree 1
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
        glVertex2f(-0.6f, -0.5f);
        glVertex2f(-0.55f, -0.5f);
        glVertex2f(-0.55f, -0.35f);
        glVertex2f(-0.6f, -0.35f);
    glEnd();
    glColor3ub(34, 139, 34);
    drawCircle(-0.575f, -0.3f, 0.1f, 100);

    // Tree 2
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.5f);
        glVertex2f(-0.35f, -0.5f);
        glVertex2f(-0.35f, -0.35f);
        glVertex2f(-0.4f, -0.35f);
    glEnd();
    glColor3ub(34, 139, 34);
    drawCircle(-0.375f, -0.3f, 0.1f, 100);

    // Tree 3
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
        glVertex2f(-0.8f, -0.5f);
        glVertex2f(-0.75f, -0.5f);
        glVertex2f(-0.75f, -0.35f);
        glVertex2f(-0.8f, -0.35f);
    glEnd();
    glColor3ub(34, 139, 34);
    drawCircle(-0.775f, -0.3f, 0.1f, 100);
      //Tree 4
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
        glVertex2f(0.75f, -0.5f);
        glVertex2f(0.8f, -0.5f);
        glVertex2f(0.8f, -0.35f);
        glVertex2f(0.75f, -0.35f);
    glEnd();
    glColor3ub(34, 139, 34);
    drawCircle(0.775f, -0.3f, 0.1f, 100);


     //  clouds
    glColor3ub(80, 80, 80); // Gray color
    drawCircle(-0.9f, 0.5f, 0.08f, 100);
    drawCircle(-0.8f, 0.55f, 0.12f, 100);
    drawCircle(-0.7f, 0.5f, 0.08f, 100);

    drawCircle(0.1f, 0.6f, 0.1f, 100);
    drawCircle(0.2f, 0.65f, 0.12f, 100);
    drawCircle(0.3f, 0.6f, 0.1f, 100);

    drawCircle(0.1f, 0.6f, 0.1f, 100);
    drawCircle(-0.2f, 0.65f, 0.12f, 100);
    drawCircle(-0.3f, 0.6f, 0.1f, 100);

    drawCircle(0.9f, 0.5f, 0.08f, 100);
    drawCircle(0.8f, 0.55f, 0.12f, 100);
    drawCircle(0.7f, 0.5f, 0.08f, 100);

    // Draw message for Level 2
    glColor3ub(255, 255, 255);
    glRasterPos2f(-0.95f, 0.9f);
    const char *msg = "Level 2: Avoid obstacles (Press Esc to go back";
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
