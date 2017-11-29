/*
 * Trilogy Graphs
 *
 * Team:
 *  Juan Luis Flores A01280767
 *  Alex de la Rosa
 *  Eli Emmanuel
 *
 * 3D Bar Charts over Image. Create a visualization tool that
 * is designed to compare geographically distributed scalar data.
 */

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

#include "SOIL.h"

using namespace std;

// Global variables.
float truckX = 0.0f, truckY = 0.0f, truckZ = 10.0f;
float dollyX = 0.0f, dollyY = 0.0f, dollyZ = 0.0f;
float boomX = 0.0f, boomY = 1.0f, boomZ = 0.0f;
float rotateX = 0.0f, rotateY = 0.0f, rotateZ = 0.0f;
float translateX = 0.0f, translateY = 0.0f, translateZ = 0.0f;
float scaleX = 1.0f, scaleY = 1.0f, scaleZ = 1.0f;
float scalingFactor = 1.0f;

GLuint tex_2d;
int intWINDOW_ID = -1;

// We are showing 3 context variables for the 32 states
int intContext = 0; // Only values 0, 1, or 2
float STATES[3][32];

void init(void)
{
    glClearColor(0,0,0,0);
    //glClearColor(1, 1, 1, 1);
    
    // load an image file directly as a new OpenGL texture
    tex_2d = SOIL_load_OGL_texture
    (
     "mexico.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
     );
    
    //check for an error during the load process
    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    // We load population data
    ifstream popFile;
    popFile.open("population.txt");
    int index = 0;
    if (popFile.is_open()) {
        while (!popFile.eof()) {
            popFile >> STATES[0][index];
            //cout << STATES[0][index] << "\n";
            index++;
        }
    }
    popFile.close();
    
    // We load unemployment data
    ifstream unemployFile;
    unemployFile.open("unemployment.txt");
    index = 0;
    if (unemployFile.is_open()) {
        while (!unemployFile.eof()) {
            unemployFile >> STATES[1][index];
            //cout << STATES[1][index] << "\n";
            index++;
        }
    }
    unemployFile.close();
    
    // We load the poverty data
    ifstream povertyFile;
    povertyFile.open("poverty.txt");
    index = 0;
    if (povertyFile.is_open()) {
        while (!povertyFile.eof()) {
            povertyFile >> STATES[2][index];
            //cout << STATES[2][index] << "\n";
            index++;
        }
    }
    povertyFile.close();
    
    ifstream sessionFile("session.txt");
    if (sessionFile.good()) {
        sessionFile >> intContext;
    }
    sessionFile.close();
}

/*
 Function that draws a bar within the cube.
 
 Let's keep it to a grid of 3x3 where we manage coordinates (x,z) as:
 
 ----------------------------------------
 |            |            |              |
 | (-0.6,-0.6)| (0.1,-0.6) |  (0.8,-0.6)  |
 |            |            |              |
 ----------------------------------------
 |            |            |              |
 | (-0.6,0.1) | (0.1,0.1)  |  (0.8,0.1)   |
 |            |            |              |
 ----------------------------------------
 |            |            |              |
 | (-0.6,0.8) | (0.1,0.8)  |  (0.8,0.8)   |
 |            |            |              |
 ----------------------------------------
 
 The height should be in a range within 0 and 1.
 
 The red, green and blue parameters should be also within 0 and 1 and represent RGB
 */
void drawBar( float x_coordinate, float z_coordinate,float height, float red, float green, float blue, float square_base_size){
    
    // This is a constant square size defined for our bars
    //float square_base_size = 0.25;
    
    // We recalculate the height because y axis goes from -1 to 1
    height = (height * 6.0) - 1.0;
    
    glBegin(GL_QUADS);        // Draw the bar using QUADS
    glColor3f(red,green,blue);    // Color Blue
    
    glVertex3f( x_coordinate, 1.0f * height, z_coordinate);    // Top Right Of The Quad (Top)
    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate);    // Top Left Of The Quad (Top)
    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate - square_base_size);    // Bottom Left Of The Quad (Top)
    glVertex3f( x_coordinate, 1.0f * height, z_coordinate - square_base_size);    // Bottom Right Of The Quad (Top)
    
    
    glVertex3f( x_coordinate,-1.0f, z_coordinate);    // Top Right Of The Quad (Bottom)
    glVertex3f(x_coordinate - square_base_size,-1.0f, z_coordinate);    // Top Left Of The Quad (Bottom)
    glVertex3f(x_coordinate - square_base_size,-1.0f,z_coordinate - square_base_size);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( x_coordinate,-1.0f,z_coordinate - square_base_size);    // Bottom Right Of The Quad (Bottom)
    
    
    glVertex3f( x_coordinate, 1.0f * height, z_coordinate);    // Top Right Of The Quad (Front)
    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate);    // Top Left Of The Quad (Front)
    glVertex3f(x_coordinate - square_base_size,-1.0f, z_coordinate);    // Bottom Left Of The Quad (Front)
    glVertex3f( x_coordinate,-1.0f, z_coordinate);    // Bottom Right Of The Quad (Front)
    
    
    glVertex3f( x_coordinate,-1.0f,z_coordinate - square_base_size);    // Top Right Of The Quad (Back)
    glVertex3f(x_coordinate - square_base_size,-1.0f,z_coordinate - square_base_size);    // Top Left Of The Quad (Back)
    glVertex3f(x_coordinate - square_base_size, 1.0f * height,z_coordinate - square_base_size);    // Bottom Left Of The Quad (Back)
    glVertex3f( x_coordinate, 1.0f * height,z_coordinate - square_base_size);    // Bottom Right Of The Quad (Back)
    
    
    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate);    // Top Right Of The Quad (Left)
    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate - square_base_size);    // Top Left Of The Quad (Left)
    glVertex3f(x_coordinate - square_base_size,-1.0f, z_coordinate - square_base_size);    // Bottom Left Of The Quad (Left)
    glVertex3f(x_coordinate - square_base_size,-1.0f, z_coordinate);    // Bottom Right Of The Quad (Left)
    
    
    glVertex3f( x_coordinate, 1.0f * height, z_coordinate - square_base_size);    // Top Right Of The Quad (Right)
    glVertex3f( x_coordinate, 1.0f * height, z_coordinate);    // Top Left Of The Quad (Right)
    glVertex3f( x_coordinate,-1.0f, z_coordinate);    // Bottom Left Of The Quad (Right)
    glVertex3f( x_coordinate,-1.0f, z_coordinate - square_base_size);    // Bottom Right Of The Quad (Right)
    
    glEnd();            // End drawing bar
    
}

void drawStates() {
    
    //float height = 1;
    float red = 1;
    float green = 0;
    float blue = 0;
    
    int intStateIndex = 0;
    
    //Baja California Norte
    drawBar(-12, -6, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Baja California Sur
    drawBar(-9, -2, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Sonora
    drawBar(-7.7, -5.1, STATES[intContext][intStateIndex++], red, green, blue, 0.5);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Chihuahua
    drawBar(-3.7, -4.2, STATES[intContext][intStateIndex++], red, green, blue, 0.5);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Coahuila
    drawBar(0.5, -2.2, STATES[intContext][intStateIndex++], red, green, blue, 0.5);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Nuevo Leon
    drawBar(2.8, -1.3, STATES[intContext][intStateIndex++], red, green, blue, 0.3);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Tamaulipas
    drawBar(4, 0.5, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Sinaloa
    drawBar(-4.3, -0.3, STATES[intContext][intStateIndex++], red, green, blue, 0.3);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Durango
    drawBar(-2.1, -0.3, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Zacatecas
    drawBar(-0.4, 0.7, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //San Luis Potosi
    drawBar(1.8, 0.9, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Nayarit
    drawBar(-2.4, 2, STATES[intContext][intStateIndex++], red, green, blue, 0.3);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Aguascalientes
    drawBar(0.2, 1.9, STATES[intContext][intStateIndex++], red, green, blue, 0.2);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Jalisco
    drawBar(-1.8, 4, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Guanajuato
    drawBar(1.4, 3.1, STATES[intContext][intStateIndex++], red, green, blue, 0.3);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Querétaro
    drawBar(2.6, 3.1, STATES[intContext][intStateIndex++], red, green, blue, 0.2);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Hidalgo
    drawBar(3.6, 3.2, STATES[intContext][intStateIndex++], red, green, blue, 0.25);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Veracruz
    drawBar(6, 5.1, STATES[intContext][intStateIndex++], red, green, blue, 0.3);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Michoacán
    drawBar(1, 4.7, STATES[intContext][intStateIndex++], red, green, blue, 0.3);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Colima
    drawBar(-1.5, 4.9, STATES[intContext][intStateIndex++], red, green, blue, 0.2);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    //Edo. México
    drawBar(2.8, 4.6, STATES[intContext][intStateIndex++], red, green, blue, 0.2);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // DF
    drawBar(3.3, 4.8, STATES[intContext][intStateIndex++], red, green, blue, 0.2);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Morelos
    drawBar(3.3, 5.3, STATES[intContext][intStateIndex++], red, green, blue, 0.15);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Tlaxcala
    drawBar(4.4, 4.5, STATES[intContext][intStateIndex++], red, green, blue, 0.15);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Puebla
    drawBar(4.4, 5.5, STATES[intContext][intStateIndex++], red, green, blue, 0.25);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Guerrero
    drawBar(2.5, 6.3, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Oaxaca
    drawBar(6.2, 6.9, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Yucatan
    drawBar(13.8, 3.2, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Quintana Roo
    drawBar(14.2, 4.8, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Campeche
    drawBar(12.3, 5.2, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Tabasco
    drawBar(9.5, 6, STATES[intContext][intStateIndex++], red, green, blue, 0.2);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
    
    // Chiapas
    drawBar(10.5, 7.5, STATES[intContext][intStateIndex++], red, green, blue, 0.4);
    
    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }
}

void sceneRenderer(void) {
    
    glMatrixMode(GL_MODELVIEW);
    // Clear color and depth buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformation matrix.
    glLoadIdentity();
    
    // Set up the camera.
    gluLookAt(truckX, truckY, truckZ, dollyX, dollyY, dollyZ, boomX, boomY, boomZ);
    glTranslatef(translateX, translateY, translateZ);
    //glTranslatef(0.0,-1,-5);
    glTranslatef(0.0,-1,5);
    
    //glPushMatrix();
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);
    
    //glRotatef(20, 1, 0, 0);
    
    
    glPushMatrix();
    
    /* Draw Mexico Map */
    glEnable(GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, tex_2d);
    
    glBegin(GL_QUADS);
    glColor4f(1,1,1,1);
    glVertex3f(16,-1.0f, 10);    // Front Right Quad
    glTexCoord2f(1,0 );
    glVertex3f(-16,-1.0f, 10);    // Front Left Quad
    glTexCoord2f(0, 0);
    glVertex3f(-16,-1.0f,-10);    // Back Right Quad
    glTexCoord2f(0, 1);
    glVertex3f(16,-1.0f,-10);    // Back Left Quad
    glTexCoord2f(1, 1);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    //Draw the bars per states
    drawStates();
    
    glFlush();
    glutSwapBuffers();
}

void changeWindowSize(int width, int height) {
    // To prevent a window that can't exist.
    if (height == 0) {
        height = 1;
    }
    
    float ratio = width * (1.0 / height);
    
    // Use and reset the projection matrix.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Set the viewport to the entire window.
    glViewport(0, 0, width, height);
    
    // Set the right perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    
    // Bring back the model view.
    glMatrixMode(GL_MODELVIEW);
}

void storeSessionData(){
    
    ofstream sessionFile("session.txt");
    if (sessionFile.is_open()) {
        sessionFile << intContext;
    }
    else{
        printf("There's a problem while creating new session file.");
    }
    sessionFile.close();
}

void processKeyInput(unsigned char key, int x, int y) {
    if (key == 27)  // ESC Exit. DONE
        exit(0);
    switch (key) {
            // Move the camera up or down. DONE
        case 'r':
            translateY -= 0.9f;
            break;
        case 'f':
            translateY += 0.9f;
            break;
            // Move the camera forward or backward. DONE
        case 'w':
            translateZ += 0.9f;
            break;
        case 's':
            translateZ -= 0.9f;
            break;
            // Move the camera left or right. DONE
        case 'a':
            translateX += 0.9f;
            break;
        case 'd':
            translateX -= 0.9f;
            break;
            // Scalations. DONE
            // Scale in X
        case '5':
            scaleX += 0.1;
            break;
        case '4':
            scaleX -= 0.1;
            break;
            // Scale in Y
        case '7':
            scaleY += 0.1;
            break;
        case '6':
            scaleY -= 0.1;
            break;
            // Scale in Z
        case '9':
            scaleZ += 0.1;
            break;
        case '8':
            scaleZ -= 0.1;
            break;
            // Different contexts. DONE
        case '1':
            intContext = 0;
            storeSessionData();
            break;
        case '2':
            intContext = 1;
            storeSessionData();
            break;
        case '3':
            intContext = 2;
            storeSessionData();
            break;
        case 27: // Escape key
            glutDestroyWindow (intWINDOW_ID);
            exit (0);
            break;
    }
    glutPostRedisplay();
}

void ArrowClick(int key, int x, int y) {
    switch (key) {
            // Look left and right. DONE
        case GLUT_KEY_LEFT :
            dollyX -= 0.9f;
            break;
        case GLUT_KEY_RIGHT :
            dollyX += 0.9f;
            break;
            // Look up and down. DONE
        case GLUT_KEY_UP :
            dollyY += 0.9f;
            break;
        case GLUT_KEY_DOWN :
            dollyY -= 0.9f;
            break;
    }
}


int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(900, 600);
    intWINDOW_ID = glutCreateWindow("TrilogyGraphs");
    init();
    
    
    // Register GLUT callback functions.
    glutReshapeFunc(changeWindowSize);
    glutKeyboardFunc(processKeyInput);
    glutSpecialFunc(ArrowClick); // Arrow Keys to move
    glutDisplayFunc(sceneRenderer);
    glutIdleFunc(sceneRenderer);
    //glutMouseFunc(processMouseInput);
    
    // Enter GLUT event processing cycle.
    glutMainLoop();
    return 0;
}

