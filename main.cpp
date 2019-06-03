#include <windows.h>
#include <cstdlib> // standard definitions
#include <iostream> // C++ I/O
#include <GL/glut.h> // GLUT
#include <GL/glu.h> // GLU
#include <GL/gl.h> // OpenGL
#include <math.h>
//#include <conio.h>
#define PI 3.14159265f
using namespace std; // make std accessible

//-lfreeglut
//-lopengl32
//-lglu32


//TODO
//add lighting

void myReshape(int w, int h) { // window is reshaped
    glViewport (0, 0, w, h); // update the viewport
    glMatrixMode(GL_PROJECTION); // update projection
        glLoadIdentity();
        gluPerspective(65, (GLdouble) w/h, 0.1, 20);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay(); // request redisplay
}

GLdouble y = 0;

void criaBoneco(){
	
	glPushMatrix();
		glPushMatrix();
	        glTranslatef(5, y, 7);
	        glColor3f(1, 0, 0);
	        glutSolidCube(1);
	        glColor3f(1, 1, 1);
	        glutWireCube(1.00001);
	    glPopMatrix();
	glPopMatrix();
}

void movimentoBoneco(int angle, int x, int z){
	//TODO
	//rotate arms and legs in x axis
}

void myDisplay(void) { // (re)display callback
    glClearColor(0.5, 0.5, 0.5, 1.0); // background is gray
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    
	gluLookAt(1, 1, 10,
          	  5, 0,  10,
           	  0, 1,  0);

	glPushMatrix();
    	criaBoneco();
    glPopMatrix();
    
//    glPushMatrix();
//    	movimentoBoneco();
//    glPopMatrix();

    glutSwapBuffers(); // swap buffers
}

float posY = 1.5;
float velocityY = 0.0;
float gravity = 0.5;
//bool onGround = false;

void fisica(bool pulo){
	
	if(pulo){
		printf("pulo\n");
		velocityY += gravity;
		posY *= velocityY;
		y += posY;
		
		if(posY > 1.5){
			posY = 1.5;
			y += posY;
			velocityY = 0;
			pulo = false;			
		}
	}
}

void cenario(){
	//TODO
	//if cube z position < 4.15 reset cube position to 15.85 (starting position) (values referent to 1270x720 screen size)
	//uptade look at values so objects are seen from far away
}

void colisao(){
	//TODO
	//verificar se o boneco bate no cenario
}

void spaceBar(unsigned char c, int, int)
{

    switch (c)
    {
	    case ' ':
	    {
	     	fisica(true);  
	        break;
	    }
    }
    glutPostRedisplay();
}

#define TEMPO 20

void timer(int id)
{
	//spaceBar(); //probably not necessary in this scope
	//fisica();	//probably not necessary in this scope

	//movimentoBoneco();
	//cenario();
    glutPostRedisplay();
    glutTimerFunc(TEMPO, timer, 0);
}

int main(int argc, char** argv) { // main program
    glutInit(&argc, argv); // OpenGL initializations
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);// double buffering and RGB
    glutInitWindowSize(1280, 720); // create a 400x400 window
    glutInitWindowPosition(350, 50); // ...in the upper left
    glutCreateWindow(argv[0]); // create the window

    glutDisplayFunc(myDisplay); // setup callbacks
    glutReshapeFunc(myReshape);
	glutKeyboardFunc(spaceBar);
	glutTimerFunc(TEMPO, timer, 0);

    glutMainLoop(); // start it running
    return 0; // ANSI C expects this
}
