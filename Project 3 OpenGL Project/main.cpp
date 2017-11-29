/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

GLfloat xRotated, yRotated, zRotated;
void init(void)
{
    glClearColor(0,0,0,0);

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

void DrawCube(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0,0.0,-5.5);

    //glPushMatrix();
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);

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
}


void animation(void)
{

    yRotated += 0.5;
    //xRotated += 0.2;
    DrawCube();
}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0

    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    //we initizlilze the glut. functions
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glutDisplayFunc(DrawCube);

    glutReshapeFunc(reshape);

    //Set the function for the animation.
    glutIdleFunc(animation);


    glutMainLoop();
    return 0;
}
