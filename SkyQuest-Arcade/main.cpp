#include <windows.h>
#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include<cmath>
#include<stdlib.h>
#include<time.h>
#include <stdio.h>
#include <string.h>


# define PI 3.14159265358979323846
#define HIGHEST_SCORE_FILE "highest_scores.txt"
#define NUM_LEVELS 3


// Function
void keyboard(unsigned char key, int x, int y);
void circle();
void item(GLfloat x, GLfloat y);
void bg();
void aircraft();
void hills_trees();
void dayclouds(float x, float y, float radius, int segments);
void daysky();
void updateSky(int value);
void level1Display();
void darkclouds(float cx, float cy, float r, int num_segments);
void obstacles(GLfloat x, GLfloat y);
void level2Display();
void bomb(GLfloat x, GLfloat y);
void snow(GLfloat x, GLfloat y);
void snowclouds(float cx, float cy, float r, int num_segments);
void wave(float cx, float cy, float r, int num_segments);
void dayskyL3();
void itemL3(GLfloat x, GLfloat y);
void obstaclesL3(GLfloat x, GLfloat y);
void updateWave(int value);
void initializeRandomPositions();
void drawCrescentMoon();
void sound(const char* soundFile);
void playContinuousSound(const char* soundFile);
void cleanupLevelResources();



// Variable
int currentSelection = 0 , selected_level = 0; // 0 = Level 1, 1 = Level 2, 2 = Level 3
const char *levels[] = {"Level 1", "Level 2", "Level 3"};
int mainWindow; // Main menu window ID
int levelWindow; // Level window ID
float cloud1X = -0.9f, cloud2X = -0.35f, cloud3X = 0.35f, cloud4X = 0.75f, cloud5X = -0.8f, cloud6X = 1.15f;
float waveOffsetX = 0.0f, waveOffsetY = 0.0f;  // Horizontal offset for waves
GLfloat itemPosX[] = {0.6f, 0.8f, 1.2f, 0.0f, 0.3f, 0.0f, -0.2f};  // Initial X positions for items
// Fixed Y positions as provided
GLfloat itemPosY[] = {0.75f, 0.42f, 0.16f, 0.05f, -0.3f, 0.0f, -0.55f};
GLfloat obstaclePosX[] = {1.27f, 1.5f, 1.8f, 0.8f, 0.6f, 1.0f, 2.1f, 1.95f, 2.5f};  // Initial X positions for obstacles
GLfloat obstaclePosY[] = {-0.2f, 0.62f, -0.4f, 0.8f, -0.45f, 0.1f, 0.9f, 0.27f, -0.3};
GLfloat bombPosY[] = {1.6f, 1.1f, 0.95f, 1.3f, 1.5f, 1.6f, 1.2f, 1.7f, 1.0f};
GLfloat speed = 0.005f; // Speed of animation
float translationX = 1.8f;
float aircraftX = 0.0f;  // Initial X position of the aircraft
float aircraftY = 0.0f; // Initial Y position of the aircraft
float aircraftBorderX = 0.0f;
float aircraftBorderY = 0.0f; // Initial position of border
float aircraftSpeed =0.01f;
int currentDirection = 0;                  // Direction (0 = no movement, 1 = up, 2 = down, 3 = left, 4 = right)
float translationOffset = 0.0f; // Offset for horizontal translation

int score = -10, life_have = 3; bool gameOver = false;




bool running = false; // Flag to check if the game is running






GLfloat generateRandomFloat()
{
    return (GLfloat)rand() / RAND_MAX * 2.0f - 1.0f; // Normalize rand() to range -1 to 1
}

void initializeRandomPositions()
{
    // Seed the random number generator
    srand(time(0));

    // Generate random values for item positions
    for (int i = 0; i < 5; i++)
        itemPosX[i] = generateRandomFloat();


    // Generate random values for obstacle positions
    for (int i = 0; i < 6; i++)
        obstaclePosX[i] = generateRandomFloat();


    // Generate random values for bomb positions
    for (int i = 0; i < 7; i++)
        bombPosY[i] = generateRandomFloat();

}


void circle()
{
    int i;

    GLfloat x=0.0f;
    GLfloat y= -1.4f;
    GLfloat radius =1.0f;
    int triangleAmount = 100; //# of lines used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glColor3ub(38, 18, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),
                    y + (radius * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();
}




void checkCollisions(GLfloat aircraftX, GLfloat aircraftY)
{
    // Define the actual dimensions of the aircraft border
    float aircraftLeft = aircraftX - 0.09f;  // Left side of the aircraft border
    float aircraftRight = aircraftX + 0.07f; // Right side of the aircraft border
    float aircraftTop = aircraftY + 0.55f;  // Top of the aircraft border
    float aircraftBottom = aircraftY + 0.315f; // Bottom of the aircraft border

    // Iterate through all items to check for collisions
    for (int i = 0; i < sizeof(itemPosX) / sizeof(itemPosX[0]); i++)
    {
        // Check if the item is still active
        if (itemPosX[i] != -999.0f)
        {
            // Get the position of the item
            float itemX = itemPosX[i];
            float itemY = itemPosY[i];
            float itemRadius = 0.05f;

            // Check if any corner of the aircraft border intersects with the item's circle
            bool collision = (aircraftLeft <= itemX + itemRadius &&
                              aircraftRight >= itemX - itemRadius &&
                              aircraftBottom <= itemY + itemRadius &&
                              aircraftTop >= itemY - itemRadius);

            if (collision)
            {
                score += 10;               // Increment the score by 10
                itemPosX[i] = -999.0f;     // Mark the item as collected
                printf("Item collected! Current score: %d\n", score);
                printf("\n");
                printf("Aircraft: Left=%.2f, Right=%.2f, Top=%.2f, Bottom=%.2f\n", aircraftLeft, aircraftRight, aircraftTop, aircraftBottom);
                printf("Item %d: X=%.2f, Y=%.2f, Active=%s\n", i, itemX, itemY, (itemPosX[i] != -999.0f ? "Yes" : "No"));
                return;   // Exit after handling the collision for this item
            }
        }
    }
}








void gameOverScreen()
{
     // Clear the screen with black
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background

    // Set the color for the text
    glColor3ub(255, 0, 0); // Red color for "Game Over"

    // Position the text
    glRasterPos2f(-0.15f, 0.0f); // Centered position

    // Display the "Game Over" message
    const char *msg = "GAME OVER";
    for (const char *c = msg; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    // Flush to ensure it renders immediately
    glFlush();
}





void checkObstacleCollisions(GLfloat aircraftX, GLfloat aircraftY)
{
    if (gameOver) return; // Skip collision checks if already game over

    // Define the actual dimensions of the aircraft border
    float aircraftLeft = aircraftX - 0.09f;   // Left side of the aircraft border
    float aircraftRight = aircraftX + 0.07f;  // Right side of the aircraft border
    float aircraftTop = aircraftY + 0.55f;    // Top of the aircraft border
    float aircraftBottom = aircraftY + 0.315f; // Bottom of the aircraft border

    // Iterate through all obstacles to check for collisions
    for (int i = 0; i < sizeof(obstaclePosX) / sizeof(obstaclePosX[0]); i++)
    {
        // Get the position of the obstacle
        float obstacleX = obstaclePosX[i];
        float obstacleY = obstaclePosY[i];
        float obstacleRadius = 0.05f;

        // Check if any corner of the aircraft border intersects with the obstacle's circle
        bool collision = (aircraftLeft <= obstacleX + obstacleRadius &&
                          aircraftRight >= obstacleX - obstacleRadius &&
                          aircraftBottom <= obstacleY + obstacleRadius &&
                          aircraftTop >= obstacleY - obstacleRadius);

        if (collision)
        {
            printf("Collision with obstacle %d detected! Game Over.\n", i);
            gameOverScreen(); // Call the function to show the Game Over screen
            return;           // Exit after handling the collision
        }
    }
}





/*
void checkCollisions(float aircraftX, float aircraftY, int* score, int* life)
{
    // Check collision with items
    for (int i = 0; i < sizeof(itemPosX) / sizeof(itemPosX[0]); i++)
    {
        if (fabs(aircraftX - itemPosX[i]) < 0.05f && fabs(aircraftY - itemPosY[i]) < 0.05f) // Threshold for collision
        {
            (*score)++; // Increment score
            printf("Item collected! Score: %d\n", *score);

            // Reset item position (move off-screen or reset logic)
            itemPosX[i] = 1.2f; // Move back to the right
            return; // Exit after collision
        }
    }

    // Check collision with obstacles
    for (int i = 0; i < sizeof(obstaclePosX) / sizeof(obstaclePosX[0]); i++)
    {
        if (fabs(aircraftX - obstaclePosX[i]) < 0.05f && fabs(aircraftY - obstaclePosY[i]) < 0.05f) // Threshold for collision
        {
            *life -= 1.0f; // Decrement life
            printf("Hit obstacle! Life: %.2f\n", *life);

            // Reset obstacle position (move off-screen or reset logic)
            obstaclePosX[i] = 1.2f; // Move back to the right
            return; // Exit after collision
        }
    }

    // Check collision with bombs
    for (int i = 0; i < sizeof(bombPosY) / sizeof(bombPosY[0]); i++)
    {
        if (fabs(aircraftY - bombPosY[i]) < 0.05f) // Check Y-axis collision
        {
            *life -= 1.0f; // Decrement life
            printf("Hit bomb! Life: %.2f\n", *life);

            // Reset bomb position (move off-screen or reset logic)
            bombPosY[i] = 1.2f; // Move back to the top
            return; // Exit after collision
        }
    }
}
*/

void item(GLfloat x, GLfloat y)
{
    int i;

    GLfloat radius = 0.05f; // Radius of the circle
    int triangleAmount = 200; // Number of triangles used to draw the circle
    GLfloat twicePi = 2.0f * PI;

    glColor3ub(221, 136, 4); // Set color of the circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void bg()
{
    glColor3ub(50, 50, 50);
    glBegin(GL_POLYGON);
    glVertex2f (1.0f, 1.0f);
    glVertex2f (-1.0f, 1.0f);
    glVertex2f (-1.0f, -1.0f);
    glVertex2f (1.0f, -1.0f);
    glEnd();
}


 //life generate



void life()//full life

{
    glBegin(GL_POLYGON);
    glColor3ub(0, 255, 0);
    glVertex2f (0.98, 0.98);
    glVertex2f (0.9, 0.98);
    glVertex2f (0.9, 0.90);
    glVertex2f (0.98, 0.90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f (0.9, 0.98);
    glVertex2f (0.9, 0.90);
    glVertex2f (0.82, 0.90);
    glVertex2f (0.82, 0.98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,0, 0);
    glVertex2f (0.82, 0.98);
    glVertex2f (0.82, 0.90);
    glVertex2f (0.74, 0.90);
    glVertex2f (0.74, 0.98);
    glEnd();

}

void life1()// green vanish
{
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f (0.98, 0.98);
    glVertex2f (0.9, 0.98);
    glVertex2f (0.9, 0.90);
    glVertex2f (0.98, 0.90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 0);
    glVertex2f (0.9, 0.98);
    glVertex2f (0.9, 0.90);
    glVertex2f (0.82, 0.90);
    glVertex2f (0.82, 0.98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2f (0.9, 0.98);
    glVertex2f (0.9, 0.90);
    glVertex2f (0.86, 0.90);
    glVertex2f (0.86, 0.98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,0, 0);
    glVertex2f (0.82, 0.98);
    glVertex2f (0.82, 0.90);
    glVertex2f (0.74, 0.90);
    glVertex2f (0.74, 0.98);
    glEnd();

    }


    life2()// yeollow vanish
{
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f (0.98, 0.98);
    glVertex2f (0.9, 0.98);
    glVertex2f (0.9, 0.90);
    glVertex2f (0.98, 0.90);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f (0.9, 0.98);
    glVertex2f (0.9, 0.90);
    glVertex2f (0.82, 0.90);
    glVertex2f (0.82, 0.98);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,0, 0);
    glVertex2f (0.82, 0.98);
    glVertex2f (0.82, 0.90);
    glVertex2f (0.74, 0.90);
    glVertex2f (0.74, 0.98);
    glEnd();



}




void aircraft_Border()
{
    glPushMatrix();
    glTranslatef(aircraftBorderX, aircraftBorderY, 0.0f);
    glColor3ub(244, 244, 244);

    glBegin(GL_LINE_STRIP);
    glVertex2f (-0.09f, 0.55f);
    glVertex2f (0.07f, 0.55f);
    glVertex2f (0.07f, 0.315f);
    glVertex2f (-0.09f, 0.315f);
    glVertex2f (-0.09f, 0.55f);
    glEnd();

    glPopMatrix();
}






void aircraft()
{
    glPushMatrix();  // Save the current transformation state
    glTranslatef(aircraftX, aircraftY, 0.0f);  // Apply translation for movement

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

    GLfloat x=0.0465f;
    GLfloat y= 0.428f;
    GLfloat radius =0.0204f;
    int triangleAmount = 300; // lines used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glColor3ub(10, 10, 10);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f( x + (radius * cos(i *  twicePi / triangleAmount)),
                    y + (radius * sin(i * twicePi / triangleAmount)) );
    }
    glEnd();

    glPopMatrix();
}




void updateAircraft(int value)
{
     int score = 0;       // Keep score persistent
     int life_have = 3;   // Initial life value (if life is used)

    switch (currentDirection)
    {
        case 1: // Up
            if (aircraftY + aircraftSpeed <= 0.3f)  // Check upper boundary
                aircraftY += aircraftSpeed;
            break;

        case 2: // Down
            if (aircraftY - aircraftSpeed >= -0.6f)  // Check lower boundary
                aircraftY -= aircraftSpeed;
            break;

        case 3: // Left
            if (aircraftX - aircraftSpeed >= -0.25f)  // Check left boundary
                aircraftX -= aircraftSpeed;
            break;

        case 4: // Right
            if (aircraftX + aircraftSpeed <= 0.25f)  // Check right boundary
                aircraftX += aircraftSpeed;
            break;

        default: // No movement
            break;
    }

    // Check for collisions and update score/life
    //checkCollisions(aircraftX, aircraftY);

    glutPostRedisplay();  // Request a redraw
    glutTimerFunc(16, updateAircraft, 0);  // Update every 16ms (~60 FPS)
}



// Update function for continuous movement of the border
void updateAircraftBorder(int value)
{
    switch (currentDirection)
    {
        case 1: // Up
            if (aircraftBorderY + aircraftSpeed <= 0.3f) // Check upper boundary
                aircraftBorderY += aircraftSpeed;
            break;

        case 2: // Down
            if (aircraftBorderY - aircraftSpeed >= -0.6f) // Check lower boundary
                aircraftBorderY -= aircraftSpeed;
            break;

        case 3: // Left
            if (aircraftBorderX - aircraftSpeed >= -0.25f) // Check left boundary
                aircraftBorderX -= aircraftSpeed;
            break;

        case 4: // Right
            if (aircraftBorderX + aircraftSpeed <= 0.25f) // Check right boundary
                aircraftBorderX += aircraftSpeed;
            break;

        default: // No movement
            break;
    }

    // Check for collisions after updating the position
    if (selected_level == 1)
    {
        checkCollisions(aircraftBorderX, aircraftBorderY);
    }
    else if (selected_level == 2)
    {
        checkCollisions(aircraftBorderX, aircraftBorderY);
        checkObstacleCollisions(aircraftBorderX, aircraftBorderY);
    }
    else if (selected_level == 3)
    {
        checkCollisions(aircraftBorderX, aircraftBorderY);
        checkObstacleCollisions(aircraftBorderX, aircraftBorderY);
        //checkBombCollisions(aircraftBorderX, aircraftBorderY);
    }

    glutPostRedisplay();   // Request a redraw
    glutTimerFunc(16, updateAircraftBorder, 0); // Update every 16ms (~60 FPS)
}




void hills_trees()
{
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
}




void drawTree(float offsetX, float offsetY)
{
    // Tree Trunk (positioned with respect to the center)
    glBegin(GL_POLYGON);
    glColor3ub(14, 4, 4);
    glVertex2f(-0.59f + offsetX, -0.7f + offsetY);
    glVertex2f(-0.6f + offsetX, -0.7f + offsetY);
    glVertex2f(-0.6f + offsetX, -0.61f + offsetY);
    glVertex2f(-0.59f + offsetX, -0.61f + offsetY);
    glEnd();

    // First Layer of Leaves (positioned with respect to the center)
    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f(-0.56f + offsetX, -0.66f + offsetY);
    glVertex2f(-0.595f + offsetX, -0.61f + offsetY);
    glVertex2f(-0.63f + offsetX, -0.66f + offsetY);
    glEnd();

    // Second Layer of Leaves (positioned with respect to the center)
    glBegin(GL_POLYGON);
    glColor3ub(14, 85, 31);
    glVertex2f(-0.56f - 0.005f + offsetX, -0.66f + 0.03f + offsetY);
    glVertex2f(-0.595f + offsetX, -0.61f + 0.03f + offsetY);
    glVertex2f(-0.63f + 0.005f + offsetX, -0.66f + 0.03f + offsetY);
    glEnd();
}





void drawPolygonWithTrees1()
{
    glPushMatrix();  // Save the current matrix state
    glTranslatef(translationX, 0.0f, 0.0f);
    // Draw the outer polygon with the dimensions of -1.0f to 1.5f in length and -1.0f to -0.7f in height
    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);  // Color for the polygon (grey, or choose any color)
    glVertex2f(1.5f, -1.0f);  // Bottom-left corner
    glVertex2f(4.0f, -1.0f);   // Bottom-right corner
    glVertex2f(4.0f, -0.5f);   // Top-right corner
    glVertex2f(1.5f, -0.5f);  // Top-left corner
    glEnd();

    // Call drawTree at various positions inside the polygon
    drawTree(0.0f+2.5, -0.05f);
    drawTree(0.25f+2.5, -0.15f);
    drawTree(0.5f+2.5, -0.2f);
    drawTree(0.65f+2.5, 0.0f);
    drawTree(0.35f+2.5, 0.1f);
    drawTree(0.75f+2.5, -0.2f);
    drawTree(-0.2f+2.5, -0.2f);
    drawTree(-0.25f+2.5, 0.0f);
    drawTree(0.85f+2.5, 0.1f);
    drawTree(1.0f+2.5, -0.1f);
    drawTree(1.2f+2.5, -0.2f);
    drawTree(1.3f+2.5, 0.0f);
    drawTree(1.48f+2.5, 0.0f);
    drawTree(1.6f+2.5, -0.2f);
    drawTree(1.75f+2.5, -0.1f);
    drawTree(1.85f+2.5, 0.0f);
    drawTree(1.95f+2.5, -0.2f);
    glPopMatrix();  // Restore the previous matrix state

    // Update the translation value for continuous movement
    translationX -= 0.008f;  // Adjust the speed of the movement here
    if (translationX < -3.0f)    // Reset translation when it moves out of screen
        translationX = -1.0f;
}




void drawPolygonWithTrees()
{
    glPushMatrix();  // Save the current matrix state
    glTranslatef(translationX, 0.0f, 0.0f);
    // Draw the outer polygon with the dimensions of -1.0f to 1.5f in length and -1.0f to -0.7f in height
    glBegin(GL_POLYGON);
    glColor3ub(38, 18, 0);  // Color for the polygon (grey, or choose any color)
    glVertex2f(-3.0f, -1.0f);  // Bottom-left corner
    glVertex2f(1.5f, -1.0f);   // Bottom-right corner
    glVertex2f(1.5f, -0.5f);   // Top-right corner
    glVertex2f(-3.0f, -0.5f);  // Top-left corner
    glEnd();

    // Call drawTree at various positions inside the polygon
    drawTree(0.0f-2.0, -0.05f);
    drawTree(0.25f-2.0, -0.15f);
    drawTree(0.5f-2.0, -0.2f);
    drawTree(0.65f-2.0, 0.0f);
    drawTree(0.35f-2.0, 0.1f);
    drawTree(0.75f-2.0, -0.2f);
    drawTree(-0.2f-2.0, -0.2f);
    drawTree(-0.25f-2.0, 0.0f);
    drawTree(0.85f-2.0, 0.1f);
    drawTree(1.0f-2.0, -0.1f);
    drawTree(1.2f-2.0, -0.2f);
    drawTree(1.3f-2.0, 0.0f);
    drawTree(1.48f-2.0, 0.0f);
    drawTree(1.6f-2.0, -0.2f);
    drawTree(1.85f-2.0, 0.0f);
    drawTree(1.95f-2.0, -0.2f);
    drawTree(0.0f, -0.05f);
    drawTree(0.25f, -0.15f);
    drawTree(0.5f, -0.2f);
    drawTree(0.65f, 0.0f);
    drawTree(0.35f, 0.1f);
    drawTree(0.75f, -0.2f);
    drawTree(-0.2f, -0.2f);
    drawTree(-0.25f, 0.0f);
    drawTree(0.85f, 0.1f);
    drawTree(1.0f, -0.1f);
    drawTree(1.2f, -0.2f);
    drawTree(1.3f, 0.0f);
    drawTree(1.48f, 0.0f);
    drawTree(1.6f, -0.2f);
    drawTree(1.75f, -0.1f);
    drawTree(1.85f, 0.0f);
    drawTree(1.95f, -0.2f);
    glPopMatrix();  // Restore the previous matrix state

    // Update the translation value for continuous movement
    translationX -= 0.008f;  // Adjust the speed of the movement here
    if (translationX < -3.0f)    // Reset translation when it moves out of screen
        translationX = -1.0f;
}




// Function to draw clouds
void dayclouds(float x, float y, float radius, int segments)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void daysky()
{
    glBegin(GL_POLYGON);
    glColor3ub(0, 79, 190);
    glVertex2f (1.0, 1.0);
    glVertex2f (-1.0, 1.0);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 75, 180);
    glVertex2f (1.0, 0.9);
    glVertex2f (-1.0, 0.9);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 72, 165);
    glVertex2f (1.0, 0.8);
    glVertex2f (-1.0, 0.8);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 68, 150);
    glVertex2f (1.0, 0.7);
    glVertex2f (-1.0, 0.7);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 62, 140);
    glVertex2f (1.0, 0.6);
    glVertex2f (-1.0, 0.6);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 57, 125);
    glVertex2f (1.0, 0.5);
    glVertex2f (-1.0, 0.5);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 56, 118);
    glVertex2f (1.0, 0.4);
    glVertex2f (-1.0, 0.4);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 54, 110);
    glVertex2f (1.0, 0.3);
    glVertex2f (-1.0, 0.3);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 53, 105);
    glVertex2f (1.0, 0.2);
    glVertex2f (-1.0, 0.2);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 51, 97);
    glVertex2f (1.0, 0.1);
    glVertex2f (-1.0, 0.1);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 48, 92);
    glVertex2f (1.0, 0.1);
    glVertex2f (-1.0, 0.1);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 45, 86);
    glVertex2f (1.0, 0.0);
    glVertex2f (-1.0, 0.0);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 43, 80);
    glVertex2f (1.0, -0.1);
    glVertex2f (-1.0, -0.1);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 40, 76);
    glVertex2f (1.0, -0.2);
    glVertex2f (-1.0, -0.2);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 37, 76);
    glVertex2f (1.0, -0.3);
    glVertex2f (-1.0, -0.3);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 35, 72);
    glVertex2f (1.0, -0.4);
    glVertex2f (-1.0, -0.4);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 32, 67);
    glVertex2f (1.0, -0.5);
    glVertex2f (-1.0, -0.5);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 29, 64);
    glVertex2f (1.0, -0.6);
    glVertex2f (-1.0, -0.6);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 26, 60);
    glVertex2f (1.0, -0.7);
    glVertex2f (-1.0, -0.7);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 22, 55);
    glVertex2f (1.0, -0.8);
    glVertex2f (-1.0, -0.8);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 17, 50);
    glVertex2f (1.0, -0.9);
    glVertex2f (-1.0, -0.9);
    glVertex2f (-1.0, -1.0);
    glVertex2f (1.0, -1.0);
    glEnd();
}



void updateSky(int value)
{
    // Update cloud positions to move from right to left
    cloud1X -= 0.0004f;
    cloud2X -= 0.0004f;
    cloud3X -= 0.0004f;
    cloud4X -= 0.0004f;
    cloud5X -= 0.0004f;
    cloud6X -= 0.0004f;

    // Reset positions when clouds move off-screen (right side)
    if (cloud1X < -1.2f) cloud1X = 1.2f;
    if (cloud2X < -1.2f) cloud2X = 1.2f;
    if (cloud3X < -1.2f) cloud3X = 1.2f;
    if (cloud4X < -1.2f) cloud4X = 1.2f;
    if (cloud5X < -1.2f) cloud5X = 1.2f;
    if (cloud6X < -1.2f) cloud6X = 1.2f;

    glutPostRedisplay();              // Request a redraw
    glutTimerFunc(16, updateSky, 0);   // Call update again after 16ms (~60 FPS)
}

// Display function for Level 1
void level1Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to gray and opaque

    bg();
    daysky();


    //  clouds
    glColor3ub(235, 235, 235);
    dayclouds(cloud1X, 0.5f, 0.08f, 200);
    dayclouds(cloud1X + 0.1f, 0.55f, 0.12f, 200);
    dayclouds(cloud1X + 0.2f, 0.5f, 0.08f, 200);

    glColor3ub(235, 235, 235);
    dayclouds(cloud2X, 0.25f, 0.08f, 200);
    dayclouds(cloud2X + 0.1f, 0.3f, 0.12f, 200);
    dayclouds(cloud2X + 0.2f, 0.25f, 0.08f, 200);

    glColor3ub(235, 235, 235);
    dayclouds(cloud3X, 0.6f, 0.08f, 200);
    dayclouds(cloud3X + 0.1f, 0.65f, 0.12f, 200);
    dayclouds(cloud3X + 0.2f, 0.6f, 0.08f, 200);

    glColor3ub(235, 235, 235);
    dayclouds(cloud4X, 0.05f, 0.08f, 200);
    dayclouds(cloud4X + 0.1f, 0.1f, 0.12f, 200);
    dayclouds(cloud4X + 0.2f, 0.05f, 0.08f, 200);

    glColor3ub(235, 235, 235);
    dayclouds(cloud5X, -0.1f, 0.08f, 200);
    dayclouds(cloud5X + 0.1f, -0.05f, 0.12f, 200);
    dayclouds(cloud5X + 0.2f, -0.1f, 0.08f, 200);

    glColor3ub(235, 235, 235);
    dayclouds(cloud6X, 0.8f, 0.08f, 200);
    dayclouds(cloud6X - 0.2f, 0.85f, 0.12f, 200);
    dayclouds(cloud6X - 0.3f, 0.8f, 0.08f, 200);


    //collectibles
    itemL3(itemPosX[0], itemPosY[0]);
    itemL3(itemPosX[1], itemPosY[1]);
    itemL3(itemPosX[2], itemPosY[2]);
    itemL3(itemPosX[3], itemPosY[3]);
    itemL3(itemPosX[4], itemPosY[4]);



    drawPolygonWithTrees();
    drawPolygonWithTrees1();

    aircraft_Border();
    aircraft();
    life();

    // Show message for Level 1
    glColor3ub(244, 244, 244);
    glRasterPos2f(-0.95f, 0.9f);
    // Prepare the score message
    char scoreMessage[50];
    if (score == -10)
    {
        snprintf(scoreMessage, sizeof(scoreMessage), "Score: %d", 0);
    }
    else
    {
        snprintf(scoreMessage, sizeof(scoreMessage), "Score: %d", score);
    }
    // Render the score message
    for (const char *c = scoreMessage; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glFlush();
}








































































































































void drawCrescentMoon()
{

    int i;
    GLfloat radius = 0.1f;  // Outer moon radius
    GLfloat innerRadius = 0.08f;  // Inner cutout radius
    int triangleAmount = 360;  // Smoothness of the circle
    GLfloat twicePi = 2.0f * PI;

    // Outer white circle (main moon)
    glColor3f(1.0f, 1.0f, 1.0f);  // White color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.75f, 0.75f);  // Center of the moon
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            -0.75f + (radius * cos(i * twicePi / triangleAmount)),
            0.75f + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    // Inner background-colored circle to create the crescent effect
    glColor3f(0.0f, 0.0f, 0.2f);  // Same as background color for blending
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.72f, 0.78f);  // Slight offset to create the curve
    for (i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            -0.72f + (innerRadius * cos(i * twicePi / triangleAmount)),
            0.78f + (innerRadius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    }


void darkclouds(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}




void obstacles(GLfloat x, GLfloat y)
{
    int i;

    GLfloat radius = 0.065f; // Radius of the circle
    int triangleAmount = 200; // Number of triangles used to draw the circle
    GLfloat twicePi = 2.0f * PI;

    // Draw the hexagon
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON); // Use line loop to draw sharp sides
    for (i = 0; i < 6; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / 6)), // 6 for hexagon
            y + (radius * sin(i * twicePi / 6))
        );
    }
    glEnd();
}

void bg2()
{
    glColor3f(0.0f, 0.0f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f (1.0f, 1.0f);
    glVertex2f (-1.0f, 1.0f);
    glVertex2f (-1.0f, -1.0f);
    glVertex2f (1.0f, -1.0f);
    glEnd();
}



void hills1()
{
    glPushMatrix();  // Save the current matrix state
    glTranslatef(translationX, 0.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.3f, 0.5f);
    glVertex2f(-0.8f+1.2, -1.0f);
    glVertex2f(-0.1f+1.2, 0.0f);
    glVertex2f(0.7f+1.2, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.5f, 0.7f);
    glVertex2f(-1.0f+1.2, -1.0f);
    glVertex2f(-0.4f+1.2, -0.1f);
    glVertex2f(0.3f+1.2, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.6f, 0.8f);
    glVertex2f(-1.15f+1.2, -1.0f);
    glVertex2f(-0.7f+1.2, 0.05f);
    glVertex2f(0.0f+1.2, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.2f, 0.4f);
    glVertex2f(-0.5f+1.2, -1.0f);
    glVertex2f(0.3f+1.2, -0.15f);
    glVertex2f(0.9f+1.2, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.15f, 0.15f, 0.3f);
    glVertex2f(0.3f+1.2, -1.0f);
    glVertex2f(0.8f+1.2, -0.3f);
    glVertex2f(1.5f+1.2, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 0.1f, 0.2f);
    glVertex2f(0.02f+1.2, -1.0f);
    glVertex2f(0.4f+1.2, -0.6f);
    glVertex2f(0.8f+1.2, -1.0f);
    glEnd();

    /////////////////////////////////

    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.3f, 0.5f);
    glVertex2f(-0.8f+2.5, -1.0f);
    glVertex2f(-0.1f+2.5, 0.0f);
    glVertex2f(0.7f+2.5, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.5f, 0.7f);
    glVertex2f(-1.0f+2.5, -1.0f);
    glVertex2f(-0.4f+2.5, -0.1f);
    glVertex2f(0.3f+2.5, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.6f, 0.8f);
    glVertex2f(-1.15f+2.5, -1.0f);
    glVertex2f(-0.7f+2.5, 0.05f);
    glVertex2f(0.0f+2.5, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.2f, 0.4f);
    glVertex2f(-0.5f+2.5, -1.0f);
    glVertex2f(0.3f+2.5, -0.15f);
    glVertex2f(0.9f+2.5, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.15f, 0.15f, 0.3f);
    glVertex2f(0.3f+2.5, -1.0f);
    glVertex2f(0.8f+2.5, -0.3f);
    glVertex2f(1.5f+2.5, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 0.1f, 0.2f);
    glVertex2f(0.02f+2.5, -1.0f);
    glVertex2f(0.4f+2.5, -0.6f);
    glVertex2f(0.8f+2.5, -1.0f);
    glEnd();

    glPopMatrix(); // Restore the transformation matrix


    // Update the translation value for continuous movement
    translationX -= 0.004f;  // Adjust the speed of the movement here
    if (translationX < -2.5f)    // Reset translation when it moves out of screen
        translationX = 3.0f;
}




void hills()
{
    glPushMatrix();  // Save the current matrix state
    glTranslatef(translationX, 0.0f, 0.0f);


    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.3f, 0.5f);
    glVertex2f(-0.8f-4.0, -1.0f);
    glVertex2f(-0.1f-4.0, 0.0f);
    glVertex2f(0.7f-4.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.5f, 0.7f);
    glVertex2f(-1.0f-4.0, -1.0f);
    glVertex2f(-0.4f-4.0, -0.1f);
    glVertex2f(0.3f-4.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.6f, 0.8f);
    glVertex2f(-1.15f-4.0, -1.0f);
    glVertex2f(-0.7f-4.0, 0.05f);
    glVertex2f(0.0f-4.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.2f, 0.4f);
    glVertex2f(-0.5f-4.0, -1.0f);
    glVertex2f(0.3f-4.0, -0.15f);
    glVertex2f(0.9f-4.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.15f, 0.15f, 0.3f);
    glVertex2f(0.3f-4.0, -1.0f);
    glVertex2f(0.8f-4.0, -0.3f);
    glVertex2f(1.5f-4.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 0.1f, 0.2f);
    glVertex2f(0.02f-4.0, -1.0f);
    glVertex2f(0.4f-4.0, -0.6f);
    glVertex2f(0.8f-4.0, -1.0f);
    glEnd();


    ///////////////////////////////

    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.3f, 0.5f);
    glVertex2f(-0.8f-2.0, -1.0f);
    glVertex2f(-0.1f-2.0, 0.0f);
    glVertex2f(0.7f-2.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.5f, 0.7f);
    glVertex2f(-1.0f-2.0, -1.0f);
    glVertex2f(-0.4f-2.0, -0.1f);
    glVertex2f(0.3f-2.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.6f, 0.8f);
    glVertex2f(-1.15f-2.0, -1.0f);
    glVertex2f(-0.7f-2.0, 0.05f);
    glVertex2f(0.0f-2.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.2f, 0.4f);
    glVertex2f(-0.5f-2.0, -1.0f);
    glVertex2f(0.3f-2.0, -0.15f);
    glVertex2f(0.9f-2.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.15f, 0.15f, 0.3f);
    glVertex2f(0.3f-2.0, -1.0f);
    glVertex2f(0.8f-2.0, -0.3f);
    glVertex2f(1.5f-2.0, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 0.1f, 0.2f);
    glVertex2f(0.02f-2.0, -1.0f);
    glVertex2f(0.4f-2.0, -0.6f);
    glVertex2f(0.8f-2.0, -1.0f);
    glEnd();

/////////////////////////////////////////////

    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.3f, 0.5f);
    glVertex2f(-0.8f, -1.0f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(0.7f, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.5f, 0.7f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-0.4f, -0.1f);
    glVertex2f(0.3f, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.6f, 0.8f);
    glVertex2f(-1.15f, -1.0f);
    glVertex2f(-0.7f, 0.05f);
    glVertex2f(0.0f, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.2f, 0.4f);
    glVertex2f(-0.5f, -1.0f);
    glVertex2f(0.3f, -0.15f);
    glVertex2f(0.9f, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.15f, 0.15f, 0.3f);
    glVertex2f(0.3f, -1.0f);
    glVertex2f(0.8f, -0.3f);
    glVertex2f(1.5f, -1.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 0.1f, 0.2f);
    glVertex2f(0.02f, -1.0f);
    glVertex2f(0.4f, -0.6f);
    glVertex2f(0.8f, -1.0f);
    glEnd();

    glPopMatrix(); // Restore the transformation matrix


    // Update the translation value for continuous movement
    translationX -= 0.004f;  // Adjust the speed of the movement here
    if (translationX < -3.5f)    // Reset translation when it moves out of screen
        translationX = 0.0f;
}


void level2Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glVertex2f (1.0f, -1.0f);
    glEnd();

    bg2();

    hills1();
    hills();
    drawCrescentMoon();

    // Draw collectibles (move from right to left with fixed Y positions)
    itemL3(itemPosX[0], itemPosY[0]);
    itemL3(itemPosX[1], itemPosY[1]);
    itemL3(itemPosX[2], itemPosY[2]);
    itemL3(itemPosX[3], itemPosY[3]);
    itemL3(itemPosX[4], itemPosY[4]);

    // Draw obstacles (move from right to left with fixed Y positions)
    obstaclesL3(obstaclePosX[0], obstaclePosY[0]);
    obstaclesL3(obstaclePosX[1], obstaclePosY[1]);
    obstaclesL3(obstaclePosX[2], obstaclePosY[2]);
    obstaclesL3(obstaclePosX[3], obstaclePosY[3]);
    obstaclesL3(obstaclePosX[4], obstaclePosY[4]);
    obstaclesL3(obstaclePosX[5], obstaclePosY[5]);
    obstaclesL3(obstaclePosX[6], obstaclePosY[6]);
    obstaclesL3(obstaclePosX[7], obstaclePosY[7]);
    obstaclesL3(obstaclePosX[8], obstaclePosY[8]);

    aircraft_Border();
    aircraft();
    life();

    // Draw message for Level 2
    glColor3ub(255, 255, 255);
    glRasterPos2f(-0.95f, 0.9f);
    // Prepare the score message
    char scoreMessage[50];
    if (score == -10)
    {
        snprintf(scoreMessage, sizeof(scoreMessage), "Score: %d", 0);
    }
    else
    {
        snprintf(scoreMessage, sizeof(scoreMessage), "Score: %d", score);
    }
    // Render the score message
    for (const char *c = scoreMessage; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glFlush();
}






















































































void bomb(GLfloat x, GLfloat y)
{
    int i;

    GLfloat radius = 0.04f; // Radius of the circle
    int triangleAmount = 200; // Number of triangles used to draw the circle
    GLfloat twicePi = 2.0f * PI;


    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0, 0, 0); // Set color of the circle
    glVertex2f(x, y); // Center of the circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();


    // Draw the sparking string
    glColor3ub(255, 165, 0); // Orange color for the string
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(x, y + radius); // Starting point at the top edge of the circle
    glVertex2f(x, y + radius + 0.04f); // End point extending upward
    glEnd();

}









void snow(GLfloat x, GLfloat y)
{

    int i;

    GLfloat radius = 0.01f; // Radius of the circle
    int triangleAmount = 200; // Number of triangles used to draw the circle
    GLfloat twicePi = 2.0f * PI;

    glColor3ub(244, 244, 244); // Set color of the circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}





void snowclouds(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void wave(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++)
    {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}




//level3 sky


void dayskyL3()
{
    glBegin(GL_QUADS);

    // Top color (light blue)
    glColor3ub(135,206,235);
    glVertex2f(-1.0, 1.0); // Top-left
    glVertex2f(1.0, 1.0);  // Top-right

    // Bottom color (darker blue)
    glColor3ub(255,255,200);
    glVertex2f(1.0, -1.0); // Bottom-right
    glVertex2f(-1.0, -1.0); // Bottom-left

    glEnd();
}


void itemL3(GLfloat x, GLfloat y)
{

    int i;

    GLfloat radius = 0.05f; // Radius of the circle
    int triangleAmount = 200; // Number of triangles used to draw the circle
    GLfloat twicePi = 2.0f * PI;

    glColor3ub(255, 215, 0); // Set color of the circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}



void obstaclesL3(GLfloat x, GLfloat y)
{
    int i;

    GLfloat radius = 0.065f; // Radius of the circle
    int triangleAmount = 200; // Number of triangles used to draw the circle
    GLfloat twicePi = 2.0f * PI;

    // Draw the hexagon
    glColor3ub(74,71,51);
    glBegin(GL_POLYGON); // Use line loop to draw sharp sides
    for (i = 0; i < 6; i++)
    {
        glVertex2f(
            x + (radius * cos(i * twicePi / 6)), // 6 for hexagon
            y + (radius * sin(i * twicePi / 6))
        );
    }
    glEnd();
}


void updateWave(int value)
{
    waveOffsetX -= 0.005f;  // Move the waves to the right over time
    waveOffsetY = 0.1f * sin(waveOffsetX * 3.14f);
    if (waveOffsetX < 0.0f) {
        waveOffsetX =  1.05f;  // Reset position when it moves off-screen
    }

    glutPostRedisplay();   // Request a redraw
    glutTimerFunc(16, updateWave, 0);  // Update every 16ms (~60 FPS)
}


void updateLevel3(int value)
{
    // Update item positions (move from right to left)
    for (int i = 0; i < sizeof (itemPosX)/ sizeof (itemPosX[0]); i++)
    {
        itemPosX[i] -= speed;  // Move items leftward
        if (itemPosX[i] < -1.2f)
        {
            itemPosX[i] = 1.2f; // Reset position to the right
            // initializeRandomPositions();
        }
    }

    // Update obstacle positions (move from right to left)
    for (int i = 0; i < sizeof (obstaclePosX)/ sizeof (obstaclePosX[0]); i++)
    {
        obstaclePosX[i] -= speed * 1.2f;  // Move obstacles faster than items
        if (obstaclePosX[i] < -1.2f)
        {
            obstaclePosX[i] = 1.2f;  // Reset position to the right
            // initializeRandomPositions();
        }
    }

    // Update bomb positions
    for (int i = 0; i < sizeof (bombPosY)/ sizeof (bombPosY[0]); i++)
    {
        bombPosY[i] -= speed * 0.6f; // Faster than obstacles
        if (bombPosY[i] < -1.2f)
        {
            bombPosY[i] = 1.2f;
            // initializeRandomPositions();
        }
    }

    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, updateLevel3, 0); // Schedule the next update (16ms for ~60 FPS)


}


// Display function for Level 3
void level3Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to gray and opaque

    bg();
    dayskyL3();


    //  clouds
    glColor3ub(235, 235, 235);
    dayclouds(cloud1X, 0.5f, 0.08f, 200);
    dayclouds(cloud1X - 0.1f, 0.55f, 0.12f, 200);
    dayclouds(cloud1X - 0.2f, 0.5f, 0.08f, 200);

    dayclouds(cloud2X, 0.25f, 0.08f, 200);
    dayclouds(cloud2X - 0.1f, 0.3f, 0.12f, 200);
    dayclouds(cloud2X - 0.2f, 0.25f, 0.08f, 200);

    dayclouds(cloud3X, 0.6f, 0.08f, 200);
    dayclouds(cloud3X - 0.1f, 0.65f, 0.12f, 200);
    dayclouds(cloud3X - 0.2f, 0.6f, 0.08f, 200);

    dayclouds(cloud4X, 0.05f, 0.08f, 200);
    dayclouds(cloud4X - 0.1f, 0.1f, 0.12f, 200);
    dayclouds(cloud4X - 0.2f, 0.05f, 0.08f, 200);

    dayclouds(cloud5X, -0.1f, 0.08f, 200);
    dayclouds(cloud5X - 0.1f, -0.05f, 0.12f, 200);
    dayclouds(cloud5X - 0.2f, -0.1f, 0.08f, 200);

    dayclouds(cloud6X, 0.8f, 0.08f, 200);
    dayclouds(cloud6X + 0.2f, 0.85f, 0.12f, 200);
    dayclouds(cloud6X + 0.3f, 0.8f, 0.08f, 200);



    //  wave4
    glColor3ub(6,66,115); // Gray color
    wave(-3.95f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-3.85f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-3.75f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-3.65f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-3.55f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-3.45f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-3.35f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-3.25f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-3.15f-.2f + waveOffsetX,-0.72f + waveOffsetY, 0.18f, 100);
    wave(-3.05f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);


    wave(-2.95f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-2.85f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-2.75f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-2.65f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-2.55f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-2.45f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-2.35f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-2.25f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-2.15f-.2f + waveOffsetX,-0.72f + waveOffsetY, 0.18f, 100);
    wave(-2.05f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);

    wave(-1.95f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-1.85f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-1.75f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-1.65f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-1.55f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-1.45f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-1.35f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-1.25f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-1.15f-.2f + waveOffsetX,-0.72f + waveOffsetY, 0.18f, 100);
    wave(-1.05f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);

    wave(-0.95f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-0.85f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-0.75f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-0.65f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-0.55f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-0.45f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-0.35f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(-0.25f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(-0.15f-.2f + waveOffsetX,-0.72f + waveOffsetY, 0.18f, 100);
    wave(-0.05f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(0.05f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(0.15f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(0.25f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(0.35f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(0.45f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(0.55f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(0.65f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(0.75f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(0.85f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);
    wave(0.95f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.21f, 100);
    wave(1.05f-.2f + waveOffsetX, -0.72f + waveOffsetY, 0.18f, 100);




    //wave 3
    glColor3ub(118,182,196); // light occen color
    wave(-2.95f + waveOffsetX, -0.80f + waveOffsetY, 0.18f, 100);
    wave(-2.85f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(-2.75f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-2.65f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-2.55f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(-2.45f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-2.35f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-2.25f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(-2.15f + waveOffsetX,-0.80 + waveOffsetY, 0.18f, 100);
    wave(-2.05f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);

    wave(-1.95f + waveOffsetX, -0.80f + waveOffsetY, 0.18f, 100);
    wave(-1.85f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(-1.75f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-1.65f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-1.55f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(-1.45f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-1.35f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-1.25f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(-1.15f + waveOffsetX,-0.80 + waveOffsetY, 0.18f, 100);
    wave(-1.05f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);


    wave(-0.95f + waveOffsetX, -0.80f + waveOffsetY, 0.18f, 100);
    wave(-0.85f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(-0.75f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-0.65f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-0.55f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(-0.45f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-0.35f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(-0.25f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(-0.15f + waveOffsetX,-0.80 + waveOffsetY, 0.18f, 100);
    wave(-0.05f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(0.05f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(0.15f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(0.25f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(0.35f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(0.45f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(0.55f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(0.65f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(0.75f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(0.85f + waveOffsetX, -0.80 + waveOffsetY, 0.18f, 100);
    wave(0.95f + waveOffsetX, -0.80 + waveOffsetY, 0.21f, 100);
    wave(1.05f + waveOffsetX, -0.80f + waveOffsetY, 0.18f, 100);



    //  wave2
    glColor3ub(127,205,255); // Gray color
    wave(-2.95f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-2.85f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(-2.75f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-2.65f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-2.55f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(-2.45f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-2.35f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-2.25f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(-2.15f+.2f + waveOffsetX,-0.90f + waveOffsetY, 0.18f, 100);
    wave(-2.05f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);

    wave(-1.95f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-1.85f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(-1.75f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-1.65f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-1.55f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(-1.45f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-1.35f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-1.25f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(-1.15f+.2f + waveOffsetX,-0.90f + waveOffsetY, 0.18f, 100);
    wave(-1.05f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);

    wave(-0.95f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-0.85f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(-0.75f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-0.65f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-0.55f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(-0.45f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-0.35f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(-0.25f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(-0.15f+.2f + waveOffsetX,-0.90f + waveOffsetY, 0.18f, 100);
    wave(-0.05f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(0.05f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(0.15f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(0.25f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(0.35f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(0.45f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(0.45f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(0.55f+.2f + waveOffsetX, -0.90f  + waveOffsetY, 0.18f, 100);
    wave(0.65f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(0.75f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(0.85f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);
    wave(0.95f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.21f, 100);
    wave(1.05f+.2f + waveOffsetX, -0.90f + waveOffsetY, 0.18f, 100);


    //  wave
    glColor3ub(29,162,216); // occen green color
    wave(-2.95f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-2.85f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(-2.75f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-2.65f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-2.55f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(-2.45f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-2.35f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-2.25f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(-2.15f + waveOffsetX,-0.98f + waveOffsetY, 0.18f, 100);
    wave(-2.05f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);

    wave(-1.95f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-1.85f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(-1.75f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-1.65f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-1.55f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(-1.45f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-1.35f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-1.25f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(-1.15f + waveOffsetX,-0.98f + waveOffsetY, 0.18f, 100);
    wave(-1.05f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);

    wave(-0.95f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-0.85f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(-0.75f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-0.65f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-0.55f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(-0.45f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-0.35f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(-0.25f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(-0.15f + waveOffsetX,-0.98f + waveOffsetY, 0.18f, 100);
    wave(-0.05f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(0.05f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(0.15f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(0.25f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(0.35f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(0.45f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(0.55f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(0.65f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(0.75f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(0.85f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);
    wave(0.95f + waveOffsetX, -0.98f + waveOffsetY, 0.21f, 100);
    wave(1.05f + waveOffsetX, -0.98f + waveOffsetY, 0.18f, 100);


    //wave0
    glColor3ub(222,243,246); // occen green color
    wave(-2.95f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-2.85f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(-2.75f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-2.65f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-2.55f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(-2.45f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-2.35f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-2.25f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(-2.15f-.2f + waveOffsetX,-1.06f + waveOffsetY, 0.18f, 100);
    wave(-2.05f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);

    wave(-1.95f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-1.85f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(-1.75f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-1.65f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-1.55f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(-1.45f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-1.35f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-1.25f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(-1.15f-.2f + waveOffsetX,-1.06f + waveOffsetY, 0.18f, 100);
    wave(-1.05f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);


    wave(-0.95f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-0.85f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(-0.75f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-0.65f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-0.55f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(-0.45f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-0.35f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(-0.25f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(-0.15f-.2f + waveOffsetX,-1.06f + waveOffsetY, 0.18f, 100);
    wave(-0.05f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(0.05f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(0.15f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(0.25f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(0.35f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(0.45f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(0.55f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(0.65f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(0.75f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(0.85f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);
    wave(0.95f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.21f, 100);
    wave(1.05f-.2f + waveOffsetX, -1.06f + waveOffsetY, 0.18f, 100);




    // Draw collectibles (move from right to left with fixed Y positions)
    itemL3(itemPosX[0], itemPosY[0]);
    itemL3(itemPosX[1], itemPosY[1]);
    itemL3(itemPosX[2], itemPosY[2]);
    itemL3(itemPosX[3], itemPosY[3]);
    itemL3(itemPosX[4], itemPosY[4]);

    // Draw obstacles (move from right to left with fixed Y positions)
    obstaclesL3(obstaclePosX[0], obstaclePosY[0]);
    obstaclesL3(obstaclePosX[1], obstaclePosY[1]);
    obstaclesL3(obstaclePosX[2], obstaclePosY[2]);
    obstaclesL3(obstaclePosX[3], obstaclePosY[3]);
    obstaclesL3(obstaclePosX[4], obstaclePosY[4]);
    obstaclesL3(obstaclePosX[5], obstaclePosY[5]);
    obstaclesL3(obstaclePosX[6], obstaclePosY[6]);
    obstaclesL3(obstaclePosX[7], obstaclePosY[7]);
    obstaclesL3(obstaclePosX[8], obstaclePosY[8]);

    // Draw bombs
    bomb(-0.17f, bombPosY[0]);
    bomb(-0.8f, bombPosY[1]);
    bomb(-0.6f, bombPosY[2]);
    bomb(0.2f, bombPosY[3]);
    bomb(0.5f, bombPosY[4]);
    bomb(0.75f, bombPosY[5]);
    bomb(0.9f, bombPosY[6]);
    bomb(-0.4f, bombPosY[7]);
    bomb(0.1f, bombPosY[8]);

    aircraft_Border();
    aircraft();
    life();

    // Show message for Level 3
    glColor3ub(244, 244, 244);
    glRasterPos2f(-0.95f, 0.9f);
    // Prepare the score message
    char scoreMessage[50];
    if (score == -10)
    {
        snprintf(scoreMessage, sizeof(scoreMessage), "Score: %d", 0);
    }
    else
    {
        snprintf(scoreMessage, sizeof(scoreMessage), "Score: %d", score);
    }
    // Render the score message
    for (const char *c = scoreMessage; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glFlush();
}










// Display function for the main menu (level selector)
void drawButtons()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Title
    glRasterPos2f(-0.2f, 0.4f);
    const char *title = "Select Level:";
    for (const char *c = title; *c != '\0'; ++c)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);


    // Draw buttons
    for (int i = 0; i < 3; ++i)
    {
        if (i == currentSelection)
            glColor3f(0.0, 1.0, 0.0); // Highlight selected button
        else
            glColor3f(1.0, 1.0, 1.0); // Normal color

        glRasterPos2f(-0.1f, 0.2f - i * 0.2f); // Position buttons
        for (const char *c = levels[i]; *c != '\0'; ++c)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glFlush();
}












// Switch to the main menu (level selector)
void returnToMainMenu()
{
    // Set the display function to draw the main menu
    glutSetWindow(mainWindow);
    glutDisplayFunc(drawButtons);


    // Reset or clean up resources

    // Clear the screen to ensure no leftover level graphics are displayed
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Redraw the main menu
    glutPostRedisplay();
}






// Switch to Level 1 view
void openLevel1()
{
    if (selected_level == 1)
    {
        glutSetWindow(mainWindow); // Keep using the same window
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color for Level 1
        glutDisplayFunc(level1Display); // Register display callback for Level 1
        glutTimerFunc(16, updateSky, 0);         // Start animation for Level 1
        glutTimerFunc(16, updateLevel3, 0);
        glutTimerFunc(16, updateAircraft, 0);
        glutTimerFunc(16, updateAircraftBorder, 0);
        glutPostRedisplay(); // Redraw to display Level 1 content
    }
}

// Switch to Level 2 view
void openLevel2()
{
    if (selected_level == 2 && !gameOver)
    {
        glutSetWindow(mainWindow); // Keep using the same window
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color for Level 2
        glutDisplayFunc(level2Display); // Register display callback for Level 2
        glutTimerFunc(16, updateLevel3, 0); // obstacle moove
        glutTimerFunc(16, updateAircraft, 0);
        glutTimerFunc(16, updateAircraftBorder, 0);
        glutPostRedisplay(); // Redraw to display Level 2 content
    }
    else if (selected_level == 2 && gameOver)
    {
        gameOverScreen();
    }
}

// Switch to Level 3 view
void openLevel3()
{
    glutSetWindow(mainWindow); // Keep using the same window
    glLoadIdentity();
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color for Level 3
    glutDisplayFunc(level3Display); // Register display callback for Level 3
    glutTimerFunc(16, updateSky, 0);
    glutTimerFunc(16, updateWave, 0);  // Start animation by calling update every 16ms
    glutTimerFunc(16, updateLevel3, 0); // Start animation by calling update every 16ms
    glutTimerFunc(16, updateAircraft, 0);
    glutTimerFunc(16, updateAircraftBorder, 0);
    glutPostRedisplay(); // Redraw to display Level 3 content
}












void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)    // 27 is the ASCII code for Esc key
    {
        //isRunning = false;  // Stop the timer function
        selected_level = 0;
        returnToMainMenu(); // Return to the level selector
        score = -10;
    }
    else
    {
        switch (key)
        {
        case 'w': // Move up
        case 'W':
            if (currentSelection > 0)
            {
                currentSelection--;
                sound("levelSelect.wav");  // Play sound when level selection moves up
            }
            break;

        case 's': // Move down
        case 'S':
             if (currentSelection < 2)
            {
                currentSelection++;
                sound("levelSelect.wav");  // Play sound when level selection moves down
            }
            break;

        case 13: // Enter key
             if (currentSelection == 0)
            {
                selected_level = 1;
                openLevel1();
                playContinuousSound("backgorund_music.wav");  // Play sound when selecting level 1
            }
            else if (currentSelection == 1)
            {
                selected_level = 2;
                openLevel2();
                playContinuousSound("backgorund_music.wav");  // Play sound when selecting level 1
            }
            else if (currentSelection == 2)
            {
                selected_level = 3;
                openLevel3();
                playContinuousSound("backgorund_music.wav");  // Play sound when selecting level 1
            }
            break;
        }
    }
    glutPostRedisplay();
}







// Function to handle special key press (arrow keys)
void handleSpecialKeypress(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            currentDirection = 1;
            break;

        case GLUT_KEY_DOWN:
            currentDirection = 2;
            break;

        case GLUT_KEY_LEFT:
            currentDirection = 3;
            break;

        case GLUT_KEY_RIGHT:
            currentDirection = 4;
            break;
    }
}

// Function to handle special key release
void handleSpecialKeyRelease(int key, int x, int y)
{
    // Stop movement when key is released
    currentDirection = 0;
}







void display()
{
    drawButtons();
}





/*-------------------------- Functions for High Score Management---------------------------*/
// Initialize Scores in the File (If the File Doesn't Exist)
void initializeHighScores()
{
    FILE *file = fopen(HIGHEST_SCORE_FILE, "r");
    if (file == NULL) // If file doesn't exist, create it
    {
        file = fopen(HIGHEST_SCORE_FILE, "w");
        if (file != NULL)
        {
            for (int i = 0; i < NUM_LEVELS; i++)
                fprintf(file, "Level %d: 0\n", i + 1); // Default score is 0 for each level

            fclose(file);
        }
    }
    else
        fclose(file); // File exists, no need to initialize

}

// Read the Highest Scores
void readHighScores(int scores[NUM_LEVELS])
{
    FILE *file = fopen(HIGHEST_SCORE_FILE, "r");
    if (file != NULL)
    {
        for (int i = 0; i < NUM_LEVELS; i++)
            fscanf(file, "Level %*d: %d\n", &scores[i]);
        fclose(file);
    }
}

// Update the Highest Score for a Specific Level
void updateHighScore(int level, int newScore)
{
    int scores[NUM_LEVELS];
    readHighScores(scores); // Load current scores

    if (level < 1 || level > NUM_LEVELS)
    {
        printf("Invalid level: %d\n", level);
        return;
    }

    if (newScore > scores[level - 1]) // Check if the new score is higher
    {
        scores[level - 1] = newScore; // Update the score for the level

        // Save updated scores back to the file
        FILE *file = fopen(HIGHEST_SCORE_FILE, "w");
        if (file != NULL)
        {
            for (int i = 0; i < NUM_LEVELS; i++)
                fprintf(file, "Level %d: %d\n", i + 1, scores[i]);

            fclose(file);
        }
    }
}


// Display High Scores
void displayHighScores()
{
    int scores[NUM_LEVELS];
    readHighScores(scores); // Load scores from file

    printf("Highest Scores:\n");
    for (int i = 0; i < NUM_LEVELS; i++)
        printf("Level %d: %d\n", i + 1, scores[i]);

}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 400);
    glutInitWindowPosition(300, 100);
    mainWindow = glutCreateWindow("SkyQuest");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color for the main menu

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // Register keyboard callback for main window
    glutSpecialFunc(handleSpecialKeypress);  // Register key press handler
    glutSpecialUpFunc(handleSpecialKeyRelease);  // Register key release handler

    glutMainLoop();
    return 0;
}









































































































void sound(const char* soundFile)
{
    if (!PlaySound(soundFile, NULL, SND_ASYNC | SND_FILENAME))
        printf("Error playing sound: %s\n", soundFile);
}


void playContinuousSound(const char* soundFile)
{
    PlaySound(TEXT(soundFile), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
