/*
 * Trilogy Graphs
 *
 * Team:
 *  Juan Luis Flores A01280767
 *  Alex de la Rosa A01381412
 *  Eli Emmanuel A00815654
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

float vertexArrayX[32][24];
float vertexArrayY[32][24];
float vertexArrayZ[32][24];
int facesArray[32][6][4];

float planeVertices[4][3];

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

        sessionFile >> truckX;
        sessionFile >> truckY;
        sessionFile >> truckZ;

        sessionFile >> dollyX;
        sessionFile >> dollyY;
        sessionFile >> dollyZ;

        sessionFile >> boomX;
        sessionFile >> boomY;
        sessionFile >> boomZ;

        sessionFile >> rotateX;
        sessionFile >> rotateY;
        sessionFile >> rotateZ;

        sessionFile >> translateX;
        sessionFile >> translateY;
        sessionFile >> translateZ;

        sessionFile >> scaleX;
        sessionFile >> scaleY;
        sessionFile >> scaleZ;
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
void drawBar( float x_coordinate, float z_coordinate,float height, float red, float green, float blue, float square_base_size, int barNumber) {

    // This is a constant square size defined for our bars
    //float square_base_size = 0.25;

    // We recalculate the height because y axis goes from -1 to 1
    height = (height * 8.0) - 1.0;

    glBegin(GL_QUADS);        // Draw the bar using QUADS
    glColor3f(red,green,blue);    // Color Blue

    // FIRST FACE
    glVertex3f( x_coordinate, 1.0f * height, z_coordinate);    // Top Right Of The Quad (Top)
    vertexArrayX[barNumber][0] = x_coordinate;
    vertexArrayY[barNumber][0] = 1.0f * height;
    vertexArrayZ[barNumber][0] = z_coordinate;
    facesArray[barNumber][0][0] = barNumber * 24 + 1;

    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate);    // Top Left Of The Quad (Top)
    vertexArrayX[barNumber][1] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][1] = 1.0f * height;
    vertexArrayZ[barNumber][1] = z_coordinate;
    facesArray[barNumber][0][1] = barNumber * 24 + 2;

    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate - square_base_size);    // Bottom Left Of The Quad (Top)
    vertexArrayX[barNumber][2] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][2] = 1.0f * height;
    vertexArrayZ[barNumber][2] = z_coordinate - square_base_size;
    facesArray[barNumber][0][2] = barNumber * 24 + 3;

    glVertex3f( x_coordinate, 1.0f * height, z_coordinate - square_base_size);    // Bottom Right Of The Quad (Top)
    vertexArrayX[barNumber][3] = x_coordinate;
    vertexArrayY[barNumber][3] = 1.0f * height;
    vertexArrayZ[barNumber][3] = z_coordinate - square_base_size;
    facesArray[barNumber][0][3] = barNumber * 24 + 4;

    // SECOND FACE
    glVertex3f( x_coordinate, -1.0f, z_coordinate);    // Top Right Of The Quad (Bottom)
    vertexArrayX[barNumber][4] = x_coordinate;
    vertexArrayY[barNumber][4] = -1.0f;
    vertexArrayZ[barNumber][4] = z_coordinate;
    facesArray[barNumber][1][0] = barNumber * 24 + 5;

    glVertex3f(x_coordinate - square_base_size, -1.0f, z_coordinate);    // Top Left Of The Quad (Bottom)
    vertexArrayX[barNumber][5] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][5] = -1.0f;
    vertexArrayZ[barNumber][5] = z_coordinate;
    facesArray[barNumber][1][1] = barNumber * 24 + 6;

    glVertex3f(x_coordinate - square_base_size, -1.0f, z_coordinate - square_base_size);    // Bottom Left Of The Quad (Bottom)
    vertexArrayX[barNumber][6] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][6] = -1.0f;
    vertexArrayZ[barNumber][6] = z_coordinate - square_base_size;
    facesArray[barNumber][1][2] = barNumber * 24 + 7;

    glVertex3f( x_coordinate, -1.0f, z_coordinate - square_base_size);    // Bottom Right Of The Quad (Bottom)
    vertexArrayX[barNumber][7] = x_coordinate;
    vertexArrayY[barNumber][7] = -1.0f;
    vertexArrayZ[barNumber][7] = z_coordinate - square_base_size;
    facesArray[barNumber][1][3] = barNumber * 24 + 8;

    // THIRD FACE
    glVertex3f( x_coordinate, 1.0f * height, z_coordinate);    // Top Right Of The Quad (Front)
    vertexArrayX[barNumber][8] = x_coordinate;
    vertexArrayY[barNumber][8] = 1.0f * height;
    vertexArrayZ[barNumber][8] = z_coordinate;
    facesArray[barNumber][2][0] = barNumber * 24 + 9;

    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate);    // Top Left Of The Quad (Front)
    vertexArrayX[barNumber][9] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][9] = 1.0f * height;
    vertexArrayZ[barNumber][9] = z_coordinate;
    facesArray[barNumber][2][1] = barNumber * 24 + 10;

    glVertex3f(x_coordinate - square_base_size, -1.0f, z_coordinate);    // Bottom Left Of The Quad (Front)
    vertexArrayX[barNumber][10] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][10] = -1.0f;
    vertexArrayZ[barNumber][10] = z_coordinate;
    facesArray[barNumber][2][2] = barNumber * 24 + 11;

    glVertex3f( x_coordinate, -1.0f, z_coordinate);    // Bottom Right Of The Quad (Front)
    vertexArrayX[barNumber][11] = x_coordinate;
    vertexArrayY[barNumber][11] = -1.0f;
    vertexArrayZ[barNumber][11] = z_coordinate;
    facesArray[barNumber][2][3] = barNumber * 24 + 12;

    // FOURTH FACE
    glVertex3f( x_coordinate, -1.0f,z_coordinate - square_base_size);    // Top Right Of The Quad (Back)
    vertexArrayX[barNumber][12] = x_coordinate;
    vertexArrayY[barNumber][12] = -1.0f;
    vertexArrayZ[barNumber][12] = z_coordinate - square_base_size;
    facesArray[barNumber][3][0] = barNumber * 24 + 13;

    glVertex3f(x_coordinate - square_base_size, -1.0f, z_coordinate - square_base_size);    // Top Left Of The Quad (Back)
    vertexArrayX[barNumber][13] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][13] = -1.0f;
    vertexArrayZ[barNumber][13] = z_coordinate - square_base_size;
    facesArray[barNumber][3][1] = barNumber * 24 + 14;

    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate - square_base_size);    // Bottom Left Of The Quad (Back)
    vertexArrayX[barNumber][14] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][14] = 1.0f * height;
    vertexArrayZ[barNumber][14] = z_coordinate - square_base_size;
    facesArray[barNumber][3][2] = barNumber * 24 + 15;

    glVertex3f( x_coordinate, 1.0f * height, z_coordinate - square_base_size);    // Bottom Right Of The Quad (Back)
    vertexArrayX[barNumber][15] = x_coordinate;
    vertexArrayY[barNumber][15] = 1.0f * height;
    vertexArrayZ[barNumber][15] = z_coordinate - square_base_size;
    facesArray[barNumber][3][3] = barNumber * 24 + 16;

    // FIFTH FACE
    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate);    // Top Right Of The Quad (Left)
    vertexArrayX[barNumber][16] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][16] = 1.0f * height;
    vertexArrayZ[barNumber][16] = z_coordinate;
    facesArray[barNumber][4][0] = barNumber * 24 + 17;

    glVertex3f(x_coordinate - square_base_size, 1.0f * height, z_coordinate - square_base_size);    // Top Left Of The Quad (Left)
    vertexArrayX[barNumber][17] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][17] = 1.0f * height;
    vertexArrayZ[barNumber][17] = z_coordinate - square_base_size;
    facesArray[barNumber][4][1] = barNumber * 24 + 18;

    glVertex3f(x_coordinate - square_base_size, -1.0f, z_coordinate - square_base_size);    // Bottom Left Of The Quad (Left)
    vertexArrayX[barNumber][18] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][18] = -1.0f;
    vertexArrayZ[barNumber][18] = z_coordinate - square_base_size;
    facesArray[barNumber][4][2] = barNumber * 24 + 19;

    glVertex3f(x_coordinate - square_base_size, -1.0f, z_coordinate);    // Bottom Right Of The Quad (Left)
    vertexArrayX[barNumber][19] = x_coordinate - square_base_size;
    vertexArrayY[barNumber][19] = -1.0f;
    vertexArrayZ[barNumber][19] = z_coordinate;
    facesArray[barNumber][4][3] = barNumber * 24 + 20;

    // SIXTH FACE
    glVertex3f( x_coordinate, 1.0f * height, z_coordinate - square_base_size);    // Top Right Of The Quad (Right)
    vertexArrayX[barNumber][20] = x_coordinate;
    vertexArrayY[barNumber][20] = 1.0f * height;
    vertexArrayZ[barNumber][20] = z_coordinate - square_base_size;
    facesArray[barNumber][5][0] = barNumber * 24 + 21;

    glVertex3f( x_coordinate, 1.0f * height, z_coordinate);    // Top Left Of The Quad (Right)
    vertexArrayX[barNumber][21] = x_coordinate;
    vertexArrayY[barNumber][21] = 1.0f * height;
    vertexArrayZ[barNumber][21] = z_coordinate;
    facesArray[barNumber][5][1] = barNumber * 24 + 22;

    glVertex3f( x_coordinate, -1.0f, z_coordinate);    // Bottom Left Of The Quad (Right)
    vertexArrayX[barNumber][22] = x_coordinate;
    vertexArrayY[barNumber][22] = -1.0f;
    vertexArrayZ[barNumber][22] = z_coordinate;
    facesArray[barNumber][5][2] = barNumber * 24 + 23;

    glVertex3f( x_coordinate, -1.0f, z_coordinate - square_base_size);    // Bottom Right Of The Quad (Right)
    vertexArrayX[barNumber][23] = x_coordinate;
    vertexArrayY[barNumber][23] = -1.0f;
    vertexArrayZ[barNumber][23] = z_coordinate - square_base_size;
    facesArray[barNumber][5][3] = barNumber * 24 + 24;

    glEnd();            // End drawing bar
}

void drawStates() {

    //float height = 1;
    float red = 1;
    float green = 0;
    float blue = 0;

    int intStateIndex = 0;

    //Baja California Norte
    drawBar(-12, -6, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 0);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Baja California Sur
    drawBar(-9, -2, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 1);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Sonora
    drawBar(-7.7, -5.1, STATES[intContext][intStateIndex++], red, green, blue, 0.5, 2);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Chihuahua
    drawBar(-3.7, -4.2, STATES[intContext][intStateIndex++], red, green, blue, 0.5, 3);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Coahuila
    drawBar(0.5, -2.2, STATES[intContext][intStateIndex++], red, green, blue, 0.5, 4);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Nuevo Leon
    drawBar(2.8, -1.3, STATES[intContext][intStateIndex++], red, green, blue, 0.3, 5);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Tamaulipas
    drawBar(4, 0.5, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 6);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Sinaloa
    drawBar(-4.3, -0.3, STATES[intContext][intStateIndex++], red, green, blue, 0.3, 7);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Durango
    drawBar(-2.1, -0.3, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 8);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Zacatecas
    drawBar(-0.4, 0.7, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 9);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //San Luis Potosi
    drawBar(1.8, 0.9, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 10);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Nayarit
    drawBar(-2.4, 2, STATES[intContext][intStateIndex++], red, green, blue, 0.3, 11);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Aguascalientes
    drawBar(0.2, 1.9, STATES[intContext][intStateIndex++], red, green, blue, 0.2, 12);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Jalisco
    drawBar(-1.8, 4, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 13);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Guanajuato
    drawBar(1.4, 3.1, STATES[intContext][intStateIndex++], red, green, blue, 0.3, 14);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Querétaro
    drawBar(2.6, 3.1, STATES[intContext][intStateIndex++], red, green, blue, 0.2, 15);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Hidalgo
    drawBar(3.6, 3.2, STATES[intContext][intStateIndex++], red, green, blue, 0.25, 16);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Veracruz
    drawBar(6, 5.1, STATES[intContext][intStateIndex++], red, green, blue, 0.3, 17);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Michoacán
    drawBar(1, 4.7, STATES[intContext][intStateIndex++], red, green, blue, 0.3, 18);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Colima
    drawBar(-1.5, 4.9, STATES[intContext][intStateIndex++], red, green, blue, 0.2, 19);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    //Edo. México
    drawBar(2.8, 4.6, STATES[intContext][intStateIndex++], red, green, blue, 0.2, 20);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // DF
    drawBar(3.3, 4.8, STATES[intContext][intStateIndex++], red, green, blue, 0.2, 21);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Morelos
    drawBar(3.3, 5.3, STATES[intContext][intStateIndex++], red, green, blue, 0.15, 22);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Tlaxcala
    drawBar(4.4, 4.5, STATES[intContext][intStateIndex++], red, green, blue, 0.15, 23);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Puebla
    drawBar(4.4, 5.5, STATES[intContext][intStateIndex++], red, green, blue, 0.25, 24);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Guerrero
    drawBar(2.5, 6.3, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 25);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Oaxaca
    drawBar(6.2, 6.9, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 26);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Yucatan
    drawBar(13.8, 3.2, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 27);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Quintana Roo
    drawBar(14.2, 4.8, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 28);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Campeche
    drawBar(12.3, 5.2, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 29);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Tabasco
    drawBar(9.5, 6, STATES[intContext][intStateIndex++], red, green, blue, 0.2, 30);

    if (red == 0.0) {
        red = 1.0;
        green = 0.0;
    }
    else {
        red = 0.0;
        green = 1.0;
    }

    // Chiapas
    drawBar(10.5, 7.5, STATES[intContext][intStateIndex++], red, green, blue, 0.4, 31);

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
    planeVertices[0][0] = 16;
    planeVertices[0][1] = -1.0f;
    planeVertices[0][2] = 10;

    glTexCoord2f(1,0 );
    glVertex3f(-16,-1.0f, 10);    // Front Left Quad
    planeVertices[1][0] = -16;
    planeVertices[1][1] = -1.0f;
    planeVertices[1][2] = 10;

    glTexCoord2f(0, 0);
    glVertex3f(-16,-1.0f,-10);    // Back Right Quad
    planeVertices[2][0] = -16;
    planeVertices[2][1] = -1.0f;
    planeVertices[2][2] = -10;

    glTexCoord2f(0, 1);
    glVertex3f(16,-1.0f,-10);    // Back Left Quad
    planeVertices[3][0] = 16;
    planeVertices[3][1] = -1.0f;
    planeVertices[3][2] = -10;

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
        sessionFile << intContext << "\n";

        sessionFile << fixed << truckX  << "\n";
        sessionFile << fixed << truckY << "\n";
        sessionFile << fixed << truckZ << "\n";

        sessionFile << fixed << dollyX << "\n";
        sessionFile << fixed << dollyY  << "\n";
        sessionFile << fixed << dollyZ  << "\n";

        sessionFile << fixed << boomX << "\n";
        sessionFile << fixed << boomY << "\n";
        sessionFile << fixed << boomZ << "\n";

        sessionFile << fixed << rotateX << "\n";
        sessionFile << fixed << rotateY << "\n";
        sessionFile << fixed << rotateZ << "\n";

        sessionFile << fixed << translateX << "\n";
        sessionFile << fixed << translateY << "\n";
        sessionFile << fixed << translateZ << "\n";

        sessionFile << fixed << scaleX << "\n";
        sessionFile << fixed << scaleY << "\n";
        sessionFile << fixed << scaleZ << "\n";

    }
    else{
        printf("There's a problem while creating new session file.");
    }
    sessionFile.close();
}

void saveOBJFile() {
    ofstream objFile("graph.obj");
    if (objFile.is_open()) {
        for(int i = 0; i < 32; i++) {
            for(int j = 0; j < 24; j++) {
                objFile << "v " << vertexArrayX[i][j] << " " << vertexArrayY[i][j] << " " << vertexArrayZ[i][j] << endl;
            }
        }

        for (int i = 0; i < 4; i++) {
            objFile << "v " << planeVertices[i][0] << " " << planeVertices[i][1] << " " << planeVertices[i][2] << endl;
        }

        for(int i = 0; i < 32; i++) {
            for(int j = 0; j < 6; j++) {
                objFile << "f " << facesArray[i][j][0] << " " << facesArray[i][j][1] << " " << facesArray[i][j][2] << " " << facesArray[i][j][3] << endl;
            }
        }
        // Plane face
        objFile << "f " << 32 * 6 * 4 + 1 << " " << 32 * 6 * 4 + 2  << " " << 32 * 6 * 4 + 3 << " " << 32 * 6 * 4 + 4 << endl;
    }
    else{
        printf("There's a problem while creating new session file.");
    }
    objFile.close();
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
            break;
        case '3':
            intContext = 2;
            break;
        case 'p':
            saveOBJFile();
            break;
        case 27: // Escape key
            glutDestroyWindow (intWINDOW_ID);
            exit (0);
            break;
    }
    storeSessionData();
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
    storeSessionData();
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
