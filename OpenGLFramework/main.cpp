/**
 *	CS 344 - Fundamentals of Computer Graphics
 *	Basic 2D framework using OpenGL/FreeGLUT
 *
 *	Instructions:
 *	- Right click on window for showing the menu and change speed and color of the square
 *	- Press ESC to exit (option also available on menu)
 */

#include <iostream>
#include "GL/glut.h"

/* Window information */
float windowWidth = 800;
float windowHeight = 600;
int windowID = -1;

/*
 * Function to generate a random floating point value between two values.
 */
float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

/* Variables of the square */
float squareX = 0;
float squareY = 0;
float square2X = 0;
float square2Y = 0;
float lineX = 0;
float squareWidth = 50.0f;
float squareHeight = 50.0f;
float squareVX = 0;// RandomFloat(0.01f, 0.01f);
float squareVY = 0;// RandomFloat(0.01f, 0.05f);
float square2VX = 0;// RandomFloat(0.01f, 0.05f);
float square2VY = 0;// RandomFloat(0.01f, 0.05f);
float squareDX = 20.0f;
float squareDY = 20.0f;
float squareD2X = 20.0f;
float squareD2Y = 20.0f;

/* Vertices of the square */
/* 4 vertices x 2 values (X, Y) */
float squareVertices[8] = {
	squareX - squareWidth, squareY - squareHeight,	// Left - Top
	squareX + squareWidth, squareY - squareHeight,	// Right - Top
	squareX + squareWidth, squareY + squareHeight,	// Right - Bottom
	squareX - squareWidth, squareY + squareHeight	// Left - Bottom
};


/* Vertices of the second square */
/* 4 vertices x 2 values (X, Y) */
float square2Vertices[8] = {
	square2X - squareWidth, square2Y - squareHeight, //Top left
	square2X + squareWidth, square2Y - squareHeight, //Top right
	square2X + squareWidth, square2Y + squareHeight, //Bottom Right
	square2X - squareWidth, square2Y + squareHeight  //Bottom Left
};

/* Vertices of the line */
/* 2 vertices x 2 values (X, Y) */
float lineVertices[4] = {
	squareX, squareY,
	square2X, square2Y
};

/* Colors of the vertices */
/* 4 vertices x 3 values (R, G, B) */
float squareColors[12] = {
	1.0, 0.0, 0.0,			// Red
	0.0, 1.0, 0.0,			// Green
	0.0, 0.0, 1.0,			// Blue
	1.0, 0.0, 1.0			// Magenta
};

/* IDs of the menu and the submenus */
int menuID;
int speedSubmenuID;
int colorSubmenuID;


/**
 *	Function invoked for drawing using OpenGL
 */
void display() 
{
	/* Clear the window */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Draw the square */
	/* Step 1: Enable the clients for the vertex arrays */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	/* Step 2: Set up arrays and draw them */
	glVertexPointer(2, GL_FLOAT, 0, squareVertices);
	glColorPointer(3, GL_FLOAT, 0, squareColors);
	glDrawArrays(GL_POLYGON, 0, 4);
	glVertexPointer(2, GL_FLOAT, 0, square2Vertices);
	glColorPointer(3, GL_FLOAT, 0, squareColors);
	glDrawArrays(GL_POLYGON, 0, 4);
	glVertexPointer(2, GL_FLOAT, 0, lineVertices);
	glDrawArrays(GL_LINES, 0, 2);

	/* Step 3: Disable the clients */
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	/* Update square's location for the next frame */
	squareX += squareVX * squareDX;
	squareY += squareVY * squareDY;
	square2X += square2VX * squareD2X;
	square2Y += square2VY * squareD2Y;
	if(squareX - squareWidth <= 0.0 || squareX + squareWidth >= windowWidth) 
	{
		squareDX *= -1;
	}
	if(squareY - squareHeight <= 0.0 || squareY + squareHeight >= windowHeight) 
	{
		squareDY *= -1;
	}
	if (square2X - squareWidth <= 0.0 || square2X + squareWidth >= windowWidth)
	{
		squareD2X *= -1;
	}
	if (square2Y - squareHeight <= 0.0 || square2Y + squareHeight >= windowHeight)
	{
		squareD2Y *= -1;
	}
	lineX = (square2X + squareX) / 2;

	/* Update vertices based on the updated square's location */
	squareVertices[0] = squareX - squareWidth;
	squareVertices[1] = squareY - squareHeight;
	squareVertices[2] = squareX + squareWidth;
	squareVertices[3] = squareY - squareHeight;
	squareVertices[4] = squareX + squareWidth;
	squareVertices[5] = squareY + squareHeight;
	squareVertices[6] = squareX - squareWidth;
	squareVertices[7] = squareY + squareHeight;

	square2Vertices[0] = square2X - squareWidth;
	square2Vertices[1] = square2Y - squareHeight;
	square2Vertices[2] = square2X + squareWidth;
	square2Vertices[3] = square2Y - squareHeight;
	square2Vertices[4] = square2X + squareWidth;
	square2Vertices[5] = square2Y + squareHeight;
	square2Vertices[6] = square2X - squareWidth;
	square2Vertices[7] = square2Y + squareHeight;

	lineVertices[0] = squareX;
	lineVertices[1] = squareY;
	lineVertices[2] = square2X;
	lineVertices[3] = square2Y;

	/* Force execution of OpenGL commands */
	glFlush();

	/* Swap buffers for animation */
	glutSwapBuffers();
}


/**
 *	Function invoked when window system events are not being received
 */
void idle() 
{
	/* Redraw the window */
	glutPostRedisplay();
}


/**
 *	Function invoked when an event on regular keys occur
 */
void keyboard(unsigned char k, int x, int y) 
{
	/* Show which key was pressed */
	std::cout << "Pressed \"" << k << "\" ASCII: " << (int)k << std::endl;

	/* Close application if ESC is pressed */
	if(k == 27) 
	{
		exit(0);
	}
}


/**
 *	Set OpenGL initial state
 */
void init() 
{
	/* Set clear color */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	
	/* Set 2D orthogonal projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, windowHeight, 0.0);
}


/**
 *	Function invoked when a mouse event occur
 */
void mouse(int button, int state, int x, int y)
{
	/* Show location of the mouse inside the window */
	std::cout << "Mouse: (" << x << ", " << y << ")" << std::endl;

	/* Show the button and the event on the mouse */
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		std::cout << "Mouse: Left button down" << std::endl;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		std::cout << "Mouse: Left button up" << std::endl;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
		std::cout << "Mouse: Middle button down" << std::endl;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
		std::cout << "Mouse: Middle button up" << std::endl;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
	{
		std::cout << "Mouse: Right button down" << std::endl;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) 
	{
		std::cout << "Mouse: Right button up" << std::endl;
	}
}


/**
 *	Function called when the an option of the speed submenu is selected
 */
void speedSubmenu(int value) 
{
	if (value == 0) {
		if (squareVX * 2 >= 0.05) {
			squareVX = 0.05;
		}
		else {
			squareVX *= 2;
		}
		if (squareVY * 2 >= 0.05) {
			squareVY = 0.05;
		}
		else {
			squareVY *= 2;
		}
	}
	else if (value == 1) {
		if (square2VX * 2 >= 0.05) {
			square2VX = 0.05;
		}
		else {
			square2VX *= 2;
		}
		if (square2VY * 2 >= 0.05) {
			square2VY = 0.05;
		}
		else {
			square2VY *= 2;
		}
	}
	else if (value == 2) {
		if (squareVX * 0.5 <= 0.005) {
			squareVX = 0.005;
		}
		else {
			squareVX *= 0.5;
		}
		if (squareVY * 0.5 <= 0.005) {
			squareVY = 0.005;
		}
		else {
			squareVY *= 0.5;
		}
	}
	else {
		if (square2VX * 0.5 <= 0.005) {
			square2VX = 0.005;
		}
		else {
			square2VX *= 0.5;
		}
		if (square2VY * 0.5 <= 0.005) {
			square2VY = 0.005;
		}
		else {
			square2VY *= 0.5;
		}
	}
}


/**
 *	Function called when the an option of the color submenu is selected
 */
void colorSubmenu(int value) 
{
	if(value == 0) 
	{
		/* Swap color clockwise */
		float r = squareColors[9];
		float g = squareColors[10];
		float b = squareColors[11];
		
		squareColors[9] = squareColors[6];
		squareColors[10] = squareColors[7];
		squareColors[11] = squareColors[8];

		squareColors[6] = squareColors[3];
		squareColors[7] = squareColors[4];
		squareColors[8] = squareColors[5];

		squareColors[3] = squareColors[0];
		squareColors[4] = squareColors[1];
		squareColors[5] = squareColors[2];

		squareColors[0] = r;
		squareColors[1] = g;
		squareColors[2] = b;
	}
	else 
	{
		/* Swap counterclockwise */
		float r = squareColors[0];
		float g = squareColors[1];
		float b = squareColors[2];
		
		squareColors[0] = squareColors[3];
		squareColors[1] = squareColors[4];
		squareColors[2] = squareColors[5];

		squareColors[3] = squareColors[6];
		squareColors[4] = squareColors[7];
		squareColors[5] = squareColors[8];

		squareColors[6] = squareColors[9];
		squareColors[7] = squareColors[10];
		squareColors[8] = squareColors[11];

		squareColors[9] = r;
		squareColors[10] = g;
		squareColors[11] = b;
	}
}


/**
 *	Function called when the an option of the menu is selected
 */
void menu(int value) 
{
	if(value == 0) 
	{
		exit(0);
	}
}


/**
 *	Generates the menu
 */
void makeMenu() 
{
	/* Generate the speed submenu */
	speedSubmenuID = glutCreateMenu(speedSubmenu);
	/* add code here to create submenu */
	glutAddMenuEntry("Increase Square1 Speed", 0);
	glutAddMenuEntry("Increase Square2 Speed", 1);
	glutAddMenuEntry("Decrease Square1 Speed", 2);
	glutAddMenuEntry("Decrease Square2 Speed", 3);

	/* Generate the color submenu */
	colorSubmenuID = glutCreateMenu(colorSubmenu);
	glutAddMenuEntry("Swap Clockwise", 0);
	glutAddMenuEntry("Swap Counterclockwise", 1);

	/* Generate the menu */
	menuID = glutCreateMenu(menu);
	glutAddSubMenu("Speed", speedSubmenuID);
	glutAddSubMenu("Color", colorSubmenuID);
	glutAddMenuEntry("Exit", 0);

	/* Attach menu to the right click */
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/**
 *	Main function
 */
int main(int argc, char **argv) 
{
	srand(time(NULL));
	squareX = RandomFloat(100, windowWidth - 100);
	squareY = RandomFloat(100, windowHeight - 100);
	square2X = RandomFloat(100, windowWidth - 100);
	square2Y = RandomFloat(100, windowHeight - 100);
	squareVX = RandomFloat(0.01f, 0.05f);
	squareVY = RandomFloat(0.01f, 0.05f); 
	square2VX = RandomFloat(0.01f, 0.05f); 
	square2VY = RandomFloat(0.01f, 0.05f); 
	int direction1 = rand() % 2;
	if (direction1 == 0) {
		direction1 -= 1;
	}
	int direction2 = rand() % 2;
	if (direction2 == 0) {
		direction2 -= 1;
	}
	int direction3 = rand() % 2;
	if (direction3 == 0) {
		direction3 -= 1;
	}
	int direction4 = rand() % 2;
	if (direction4 == 0) {
		direction4 -= 1;
	}
	squareVX *= direction1;
	squareVY *= direction2;
	square2VX *= direction3;
	square2VY *= direction4;


	/* Initialize the GLUT window */
	glutInit(&argc, argv);
	glutInitWindowSize((int)windowWidth, (int)windowHeight);
	glutInitWindowPosition(30, 30);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	windowID = glutCreateWindow("OpenGL/FreeGLUT Example - Bouncing 2D square");
	
	/* Set OpenGL initial state */
	init();
	
	/* Callback functions */
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	/* Generate the menu */
	makeMenu();
	
	/* Start the main GLUT loop */
	/* NOTE: No code runs after this */
	glutMainLoop();
}
