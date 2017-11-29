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


void init(void)
{
    glClearColor(0,0,0,0);
    //glClearColor(1, 1, 1, 1);
    
    // load an image file directly as a new OpenGL texture
    tex_2d = SOIL_load_OGL_texture
    (
    "/Users/elielr01/Documents/9no Semestre ITC/Gráficas Computacionales/Prueba/Prueba/mexico.png",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    //check for an error during the load process
    if( 0 == tex_2d )
    {
    printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
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
void drawBar( float x_coordinate, float z_coordinate,float height, float red, float green, float blue){
    
    // This is a constant square size defined for our bars
    float square_base_size = 0.25;
    
    // We recalculate the height because y axis goes from -1 to 1
    height = (height * 2.0) - 1.0;
    
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

void sceneRenderer(void) {
    
    glMatrixMode(GL_MODELVIEW);
    // Clear color and depth buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformation matrix.
    glLoadIdentity();
    
    // Set up the camera.
    gluLookAt(truckX, truckY, truckZ, dollyX, dollyY, dollyZ, boomX, boomY, boomZ);
    glTranslatef(translateX, translateY, translateZ);
    glTranslatef(0.0,0.0,5.5);
    
    //glPushMatrix();
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);
    
    glPushMatrix();
    
    /* Draw Mexico Map */
    glEnable(GL_TEXTURE_2D);
    glBindTexture (GL_TEXTURE_2D, tex_2d);

    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glColor4f(1,1,1,1);
    glVertex3f(10,-1.0f, 10);    // Front Right Quad
    glTexCoord2f(1,0 );
    glVertex3f(-10,-1.0f, 10);    // Front Left Quad
    glTexCoord2f(0, 0);
    glVertex3f(-10,-1.0f,-10);    // Back Right Quad
    glTexCoord2f(0, 1);
    glVertex3f(10,-1.0f,-10);    // Back Left Quad
    glTexCoord2f(1, 1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    
    /* Draw the cube canvas */
    glBegin(GL_QUADS);        // Draw partial cube with QUADS
    glColor4f(0.8f,0.8f,0.8f, 1);    // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor4f(0.5f,0.5f,0.5f, 1);
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    glColor4f(0.5f,0.5f,0.5f, 1);     // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    glEnd();            // End drawing partial cube
    
    
    /* Draw Strips */
    
    /* Back Strips */
    float y_strip = 0.75;
    for (int i = 1 ; i <= 7; i++, y_strip-=0.25) {
        glBegin(GL_QUADS);
        glColor4f(1,1,1,1);
        glVertex3f( 1.0f, y_strip,-1.0f);    // Top Right Of The Quad (Back)
        glVertex3f(-1.0f, y_strip,-1.0f);    // Top Left Of The Quad (Back)
        glVertex3f(-1.0f, y_strip - 0.02,-1.0f);    // Bottom Left Of The Quad (Back)
        glVertex3f( 1.0f, y_strip - 0.02,-1.0f);    // Bottom Right Of The Quad (Back)
        glEnd();
    }
    
    /* Left Strips */
    y_strip = 0.75;
    for (int i = 1 ; i <= 7; i++, y_strip-=0.25){
        glBegin(GL_QUADS);
        glColor4f(1,1,1,1);     // Color Blue
        glVertex3f(-1.0f, y_strip, 1.0f);    // Top Right Of The Quad (Left)
        glVertex3f(-1.0f, y_strip,-1.0f);    // Top Left Of The Quad (Left)
        glVertex3f(-1.0f, y_strip - 0.02,-1.0f);    // Bottom Left Of The Quad (Left)
        glVertex3f(-1.0f, y_strip - 0.02, 1.0f);    // Bottom Right Of The Quad (Left)
        glEnd();
    }
    
    /* Draw the bars */
    drawBar(0.8, 0.8, 0.8, 1.0, 0.0, 0.0);
    drawBar(0.8, 0.1, 0.25, 0.0, 1.0, 0.0);
    drawBar(0.1, 0.1, 0.5, 0.0, 0.0, 1.0);
    drawBar(-0.6, -0.6, 0.9, 1.0, 1.0, 0.0);
    
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
            // Scale. DONE
        case '6':
            scaleX += 0.1;
            break;
        case '4':
            scaleX -= 0.1;
            break;
        case '8':
            scaleY += 0.1;
            break;
        case '2':
            scaleY -= 0.1;
            break;
        case '7':
            scaleZ += 0.1;
            break;
        case '9':
            scaleZ -= 0.1;
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
    glutCreateWindow("TrilogyGraphs");
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

