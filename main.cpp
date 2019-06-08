//#include <windows.h>
#include <cstdlib> // standard definitions
#include <iostream> // C++ I/O
#include "GL/glut.h" // GLUT
#include "GL/glu.h" // GLU
#include "GL/gl.h" // OpenGL
#include <math.h>
//#include <conio.h>
#define PI 3.14159265f
using namespace std; // make std accessible

//-lfreeglut
//-lopengl32
//-lglu32


//TODO
//add lighting
//when jump true spin head in y axis

void myReshape(int w, int h) { // window is reshaped
    glViewport (0, 0, w, h); // update the viewport
    glMatrixMode(GL_PROJECTION); // update projection
        glLoadIdentity();
        gluPerspective(65, (GLdouble) w/h, 0.1, 20);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay(); // request redisplay
}

GLdouble yBoneco = 0; //max value must be 1.5 (values relative to 1270x720 screen size)
float headSpin = 0;
GLdouble angle1 = 0; 
GLdouble angle2 = 0;

void criaBoneco(){
	
	glTranslatef(0, yBoneco, 0); //used for the jump moviment
	
	glPushMatrix();
		glPushMatrix();//back leg
	        glTranslatef(5.15, -1.7, 7.1);
	        glTranslatef(0, 0.5, 0);
	        glRotatef(angle2, 1, 0, 0);
	        glTranslatef(0, -0.5, 0);
	        glColor3f(1, 0, 0);
	        glScalef(0.4, 2, 0.5);
	        glutSolidCube(0.5);
	        glColor3f(1, 1, 1);
	        glutWireCube(0.50001);
	    glPopMatrix();
	
		glPushMatrix();//back arm
	        glTranslatef(5.45, -0.8, 7.1);
			glTranslatef(0, 0.5, 0);
	        glRotatef(angle1, 1, 0, 0);
	        glTranslatef(0, -0.5, 0);
	        glColor3f(1, 0, 0);
	        glScalef(0.4, 2, 0.5);
	        glutSolidCube(0.5);
	        glColor3f(1, 1, 1);
	        glutWireCube(0.50001);
	    glPopMatrix();
	    
	    glPushMatrix();//front leg
	        glTranslatef(4.8, -1.8, 7);
	        glTranslatef(0, 0.5, 0);
	        glRotatef(angle1, 1, 0, 0);
	        glTranslatef(0, -0.5, 0);
	        glColor3f(1, 0, 0);
	        glScalef(0.4, 2, 0.5);
	        glutSolidCube(0.5);
	        glColor3f(1, 1, 1);
	        glutWireCube(0.50001);
	    glPopMatrix(); 
	
		glPushMatrix();//body
	        glTranslatef(5, -0.8, 7);
	        glColor3f(1, 0, 0);
	        glScalef(1.8, 2, 0.7);
	        glutSolidCube(0.5);
	        glColor3f(1, 1, 1);
	        glutWireCube(0.50001);
	    glPopMatrix();
	    
	    glPushMatrix();//front arm
	        glTranslatef(4.45, -0.8, 7);
	        glTranslatef(0, 0.5, 0);
	        glRotatef(angle2, 1, 0, 0);
	        glTranslatef(0, -0.5, 0);
	        glColor3f(1, 0, 0);
	        glScalef(0.4, 2, 0.5);
	        glutSolidCube(0.5);
	        glColor3f(1, 1, 1);
	        glutWireCube(0.50001);
	    glPopMatrix(); 
	    
		glPushMatrix();//head
	        glTranslatef(4.9, 0, 7.1);
	        glRotatef(headSpin, 0, 1, 0);
	        glColor3f(1, 0, 0);
	        glutSolidCube(0.5);
	        glColor3f(1, 1, 1);
	        glutWireCube(0.50001);
	    glPopMatrix();
	    
	glPopMatrix();
}

float posCenario = 15.85;

void cenario(){
	//TODO
	//if cube z position < 4.15 reset cube position to 15.85 (starting position) (values relative to 1270x720 screen size)
	//uptade look at values so objects are seen from far away
	
	//posCenario *= 0.5;
	posCenario -= 0.15;
	
	glPushMatrix();
		glTranslatef(5, -1.5, posCenario);
		//glTranslatef(0, 0, posCenario);
        glColor3f(0, 0, 1);
        glutSolidCube(1);
        glColor3f(1, 1, 1);
	    glutWireCube(1.0001);
	glPopMatrix();
	
	if(posCenario <= 4.15){
		posCenario = 15.85;
	}
	
	//printf("%f\n", posCenario);
	
	//glutPostRedisplay();
}

void myDisplay(void) { // (re)display callback
    glClearColor(0.5, 0.5, 0.5, 1.0); // background is gray
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    
	gluLookAt(1, 1, 10,
          	  5, 0,  10,
           	  0, 1,  0);

	glPushMatrix();
    	cenario();
    glPopMatrix();

	glPushMatrix();
    	criaBoneco();
    glPopMatrix();

	glutSwapBuffers(); // swap buffers
}

GLdouble posY = 1.5;
GLdouble yspeed = 1;
GLdouble gravity = 0.5;
//bool onGround = false;
bool pulo = false;
float a = 0;
float amplitude = 33;
float period = 200;
float x;

void fisica(){
	//TODO
	//make the first part of the jump smoother
	//implement head spin with acceleration and deacceleration
	
	if(pulo){
		//x = 360 * cos(100) * sin(100);
		//headSpin = (headSpin + x);
		//printf("%f\n", headSpin);

		posY += yspeed;
		
		if(posY > 2.5){
			posY = 2.5;
			yBoneco = posY * yspeed;
			if(yBoneco > 2.5){
				yBoneco = 2.5;
			}
			pulo = false;			
		}
	}
	
	yBoneco -= 0.13f;
	if(yBoneco < 0){
		yBoneco = 0;
	}
}

void scoreSystem(){
	//TODO
	//implement a score system in order to make the game faster
}

void movimentoBoneco(){
	
	x = amplitude * cos(a) * sin(a);

	angle1 = (angle1 + x) / 2;
	angle2 = (angle2 - x) / 2;
	
	a += 0.1;
	
	//implement a score system in order to make the game faster

    //printf("%f   -   %f   -   %f\n", angle1, angle2, a);
}

void colisao(){
	//TODO
	//verificar se o boneco bate no cenario
}

void spaceBar(unsigned char c, int, int){

    switch (c)
    {
	    case ' ':
	    {
	    	pulo = true;
	     	//fisica();  
	        break;
	    }
    }
    glutPostRedisplay();
}

#define TEMPO 20

void timer(int id){
	fisica();
	movimentoBoneco();
	cenario();
	//colisao();
	
    glutPostRedisplay();
    glutTimerFunc(TEMPO, timer, 10);
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
