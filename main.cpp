//#include <windows.h>
#include <cstdlib> // standard definitions
#include <iostream> // C++ I/O
#include <GL/glut.h> // GLUT
#include <GL/glu.h> // GLU
#include <GL/gl.h> // OpenGL
//#include <math.h>
//#include <conio.h>
//#define PI 3.14159265f
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

GLdouble y = 0; //max value must be 1.5 (values relative to 1270x720 screen size)

void criaBoneco(){
	
	gl
	glPushMatrix();
		glPushMatrix();//head
	        glTranslatef(5, y, 7);
	        glColor3f(1, 0, 0);
	        glutSolidCube(0.5);
	        glColor3f(1, 1, 1);
	        glutWireCube(0.50001);
	    glPopMatrix();
	    
	    glPushMatrix();//body
	        glTranslatef(5, y, 7);
	        glColor3f(1, 0, 0);
	        glutSolidCube(0.5);
	        glColor3f(1, 1, 1);
	        glutWireCube(0.50001);
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

GLdouble posY = 1.5;
GLdouble yspeed = 1;
GLdouble gravity = 0.5;
//bool onGround = false;
bool pulo = false;

void fisica(){
	if(pulo){
		
		yspeed += gravity;
		posY += yspeed;
		y += posY;
		
		printf("pulo  %g\n", yspeed);
		
		if(posY > 1.5){
			posY = 1.5;
			y = posY * yspeed;
			if(y > 1.5){
				y = 1.5;
			}
			printf("%g ", y);
			//yspeed = 0;
			pulo = false;			
		}
	}
}

void cenario(){
	//TODO
	//if cube z position < 4.15 reset cube position to 15.85 (starting position) (values relative to 1270x720 screen size)
	//uptade look at values so objects are seen from far away
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
	     	fisica();  
	        break;
	    }
    }
    glutPostRedisplay();
}

#define TEMPO 20

void timer(int id){
	//spaceBar(); //probably not necessary in this scope
	//fisica();	//probably not necessary in this scope

	//movimentoBoneco();
	//cenario();
	
	y -= 0.1f;
	if(y < 0){
		y = 0;
	}
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
