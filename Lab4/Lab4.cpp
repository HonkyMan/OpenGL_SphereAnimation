#include <GL\glut.h>

GLfloat xRotated, yRotated, zRotated;
GLdouble zoomArr[3] = { .0, .0, .0 };
bool zoomFlag = false;

void redisplayFunc(void)
{
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0, 0.0, -5.0);
    // Red color used to draw.
    glColor3f(0.9, 0.8, 0.3);
    // changing in transformation matrix.
    // rotation about X axis
    glRotatef(xRotated, 1.0, 0.0, 0.0);
    // rotation about Y axis
    glRotatef(yRotated, 0.0, 1.0, 0.0);
    // rotation about Z axis
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    // scaling transfomation 
    //glScalef(2.0, 2.0, 2.0);
    glScalef(zoomArr[0], zoomArr[1], zoomArr[2]);

    // built-in (glut library) function , draw you a cubecube.
    glutWireSphere(1.0, 20, 12);
    // Flush buffers to screen
    glFlush();
    // sawp buffers called because we are using double buffering 
    glutSwapBuffers();
}

void reshapeFunc(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);  //Use the whole window for rendering
}

void idleFunc(void)
{
    xRotated += 0.03;
    yRotated += 0.03;
    zRotated += 0.01;

    if (zoomArr[0] > 1.7 && zoomArr[1] > 1.7 && zoomArr[2] > 1.7)
    {
        zoomFlag = true;
    }
    else if (zoomArr[0] < 0 && zoomArr[1] < 0 && zoomArr[2] < 0)
    {
        zoomFlag = false;
    }
     
    if (!zoomFlag)
    {
        zoomArr[0] += 0.0005;
        zoomArr[1] += 0.0005;
        zoomArr[2] += 0.0005;
    }
    else {
        zoomArr[0] -= 0.0005;
        zoomArr[1] -= 0.0005;
        zoomArr[2] -= 0.0005;
    }

    redisplayFunc();
}


int main(int argc, char** argv)
{
    //Initialize GLUT
    glutInit(&argc, argv);
    //double buffering used to avoid flickering problem in animation
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // window size
    glutInitWindowSize(500, 500);
    // create the window 
    glutCreateWindow("Cube3d animation");
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    xRotated = yRotated = zRotated = 0.0;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    //Assign  the function used in events
    glutDisplayFunc(redisplayFunc);
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    //Let start glut loop
    glutMainLoop();
    return 0;
}