#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<Windows.h> 
#include<glut.h>
#include<stb_image.h>
#include<cmath>
#include<MMsystem.h>

bool fullscreen = true, Stop = false, Lose = false, flag[10] = { 0 };
int score = 0, z = 0, i = 0;
float width, height, x1 = -9, x2 = -7, x3 = -4, x4 = -2, x5 = 1,
x6 = 3, x7 = 6, x8 = 8, x9 = -9, x10 = -7,
x11 = -8.5, x12 = -7.5, x13 = -6.75, x14 = -9.25,
y2 = 28, y3 = 40, y4 = 38, y5 = 60,
y6 = 62, y7 = 30, y8 = 28, y9 = -8, y10 = -3,
y11 = -2.5, y12 = -8.5, y13 = -4, y14 = -7, y20 = 30,
cx, cy, angle, eyey, eyez, eyex, upx, upz = -10;

unsigned int texture;
int Width, Height, nrChannels;
unsigned char* data = NULL;

void load(int);
void check(unsigned char*);
void draw();
void reshape(int, int);
void backGround();
void timer(int);
void drawString();
void keyboarddown(unsigned char, int, int);
void keySpecialdown(int, int, int);
void mouse(int, int, int, int);

int main(int argc, char** argv) {
	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	// create window
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);
	glutInitWindowSize(width, height);
	glutCreateWindow("Car and boxes collision");

	// call back functions
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000, timer, 0);
	glutKeyboardFunc(keyboarddown);
	glutSpecialFunc(keySpecialdown);
	glutMouseFunc(mouse);
	backGround();

	// main loop
	glutMainLoop();
}
void get_backgeound();
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);                        // To operate on model-view matrix
	glLoadIdentity();                                  // Reset the model-view matrix

	gluLookAt(eyex, eyey, eyez,
		upx, eyey, upz,
		0, 1, 0);

	glTranslatef(0.0f, -0.5f, -5.5f);
	// The Squares
	load(1);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x1, y20, 0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x1, y2, 0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x2, y2, 0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x2, y20, 0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex2f(x3, y3);
	glTexCoord2d(1.0f, 0.0f);
	glVertex2f(x3, y4);
	glTexCoord2d(1.0f, 1.0f);
	glVertex2f(x4, y4);
	glTexCoord2d(0.0f, 1.0f);
	glVertex2f(x4, y3);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex2f(x5, y5);
	glTexCoord2d(1.0f, 0.0f);
	glVertex2f(x5, y6);
	glTexCoord2d(1.0f, 1.0f);
	glVertex2f(x6, y6);
	glTexCoord2d(0.0f, 1.0f);
	glVertex2f(x6, y5);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex2f(x7, y7);
	glTexCoord2d(1.0f, 0.0f);
	glVertex2f(x7, y8);
	glTexCoord2d(1.0f, 1.0f);
	glVertex2f(x8, y8);
	glTexCoord2d(0.0f, 1.0f);
	glVertex2f(x8, y7);
	glEnd();

	//The  Lines
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex2f(-6, 100);
	glTexCoord2d(1.0f, 0.0f);
	glVertex2f(-6, -100);
	glTexCoord2d(1.0f, 1.0f);
	glVertex2f(-5, -100);
	glTexCoord2d(0.0f, 1.0f);
	glVertex2f(-5, 100);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex2f(-1, 100);
	glTexCoord2d(1.0f, 0.0f);
	glVertex2f(-1, -100);
	glTexCoord2d(1.0f, 1.0f);
	glVertex2f(0, -100);
	glTexCoord2d(0.0f, 1.0f);
	glVertex2f(0, 100);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex2f(4, 100);
	glTexCoord2d(1.0f, 0.0f);
	glVertex2f(4, -100);
	glTexCoord2d(1.0f, 1.0f);
	glVertex2f(5, -100);
	glTexCoord2d(0.0f, 1.0f);
	glVertex2f(5, 100);
	glEnd();

	//The Pavements
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(-12, 100);
	glVertex2f(-20, 100);
	glVertex2f(-20, -100);
	glVertex2f(-12, -100);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(11, 100);
	glVertex2f(19, 100);
	glVertex2f(19, -100);
	glVertex2f(11, -100);
	glEnd();
	////////////////////////////////////////Draw Car////////////////////////////////////////////////
	//The Rectanglular
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(cx + x9, cy + y9, 0.25);
	glVertex3f(cx + x10, cy + y9, 0.25);
	glVertex3f(cx + x10, cy + y10, 0.25);
	glVertex3f(cx + x9, cy + y10, 0.25);

	glColor3f(0, 0, 1);
	glVertex3f(cx + x9, cy + y9, -0.25);
	glVertex3f(cx + x10, cy + y9, -0.25);
	glVertex3f(cx + x10, cy + y10, -0.25);
	glVertex3f(cx + x9, cy + y10, -0.25);

	glColor3f(0, 0, 1);
	glVertex3f(cx + x9, cy + y9, -0.25);
	glVertex3f(cx + x10, cy + y9, -0.25);
	glVertex3f(cx + x10, cy + y10, 0.25);
	glVertex3f(cx + x9, cy + y10, 0.25);

	glColor3f(0, 0, 1);
	glVertex3f(cx + x9, cy + y9, 0.25);
	glVertex3f(cx + x10, cy + y9, 0.25);
	glVertex3f(cx + x10, cy + y10, -0.25);
	glVertex3f(cx + x9, cy + y10, -0.25);
	/*
	glColor3f(0, 0, 0);
	glVertex3f(cx + x9, cy + y9, -0.25);
	glVertex3f(cx + x10, cy + y9, 0.25);
	glVertex3f(cx + x10, cy + y10, 0.25);
	glVertex3f(cx + x9, cy + y10, -0.25);

	glColor3f(0, 0, 0);
	glVertex3f(cx + x9, cy + y9, 0.25);
	glVertex3f(cx + x10, cy + y9, -0.25);
	glVertex3f(cx + x10, cy + y10, -0.25);
	glVertex3f(cx + x9, cy + y10, 0.25);
	*/
	glEnd();
	//The Edges
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0);
	glVertex3f(cx + x9, cy + y10, 0.25);
	glVertex3d(cx + x11, cy + y11, 0.25);
	glVertex3d(cx + x12, cy + y11, 0.25);
	glVertex3f(cx + x10, cy + y10, 0.25);

	glVertex3f(cx + x9, cy + y10, -0.25);
	glVertex3d(cx + x11, cy + y11, -0.25);
	glVertex3d(cx + x12, cy + y11, -0.25);
	glVertex3f(cx + x10, cy + y10, -0.25);

	glVertex3f(cx + x9, cy + y10, 0.25);
	glVertex3d(cx + x11, cy + y11, 0.25);
	glVertex3d(cx + x12, cy + y11, -0.25);
	glVertex3f(cx + x10, cy + y10, -0.25);

	glVertex3f(cx + x9, cy + y10, -0.25);
	glVertex3d(cx + x11, cy + y11, -0.25);
	glVertex3d(cx + x12, cy + y11, 0.25);
	glVertex3f(cx + x10, cy + y10, 0.25);

	glVertex3f(cx + x9, cy + y10, 0.25);
	glVertex3d(cx + x11, cy + y11, -0.25);
	glVertex3d(cx + x12, cy + y11, -0.25);
	glVertex3f(cx + x10, cy + y10, 0.25);

	glVertex3f(cx + x9, cy + y10, -0.25);
	glVertex3d(cx + x11, cy + y11, 0.25);
	glVertex3d(cx + x12, cy + y11, -0.25);
	glVertex3f(cx + x10, cy + y10, 0.25);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 0);
	glVertex3f(cx + x9, cy + y9, 0.25);
	glVertex3d(cx + x11, cy + y12, 0.25);
	glVertex3f(cx + x12, cy + y12, 0.25);
	glVertex3f(cx + x10, cy + y9, 0.25);

	glVertex3f(cx + x9, cy + y9, -0.25);
	glVertex3d(cx + x11, cy + y12, -0.25);
	glVertex3f(cx + x12, cy + y12, -0.25);
	glVertex3f(cx + x10, cy + y9, -0.25);

	glVertex3f(cx + x9, cy + y9, -0.25);
	glVertex3d(cx + x11, cy + y12, -0.25);
	glVertex3f(cx + x12, cy + y12, 0.25);
	glVertex3f(cx + x10, cy + y9, 0.25);

	glVertex3f(cx + x9, cy + y9, 0.25);
	glVertex3d(cx + x11, cy + y12, 0.25);
	glVertex3f(cx + x12, cy + y12, -0.25);
	glVertex3f(cx + x10, cy + y9, -0.25);

	glVertex3f(cx + x9, cy + y9, -0.25);
	glVertex3d(cx + x11, cy + y12, 0.25);
	glVertex3f(cx + x12, cy + y12, -0.25);
	glVertex3f(cx + x10, cy + y9, 0.25);

	glVertex3f(cx + x9, cy + y9, 0.25);
	glVertex3d(cx + x11, cy + y12, -0.25);
	glVertex3f(cx + x12, cy + y12, 0.25);
	glVertex3f(cx + x10, cy + y9, -0.25);
	glEnd();
	////////////////////////////////////
	//The Weels
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(cx + x10, cy + y10, 0.25);
	glVertex3f(cx + x13, cy + y10, 0.25);
	glVertex3f(cx + x13, cy + y13, 0.25);
	glVertex3f(cx + x10, cy + y13, 0.25);

	glVertex3f(cx + x10, cy + y10, -0.25);
	glVertex3f(cx + x13, cy + y10, -0.25);
	glVertex3f(cx + x13, cy + y13, -0.25);
	glVertex3f(cx + x10, cy + y13, -0.25);

	glVertex3f(cx + x10, cy + y10, -0.25);
	glVertex3f(cx + x13, cy + y10, -0.25);
	glVertex3f(cx + x13, cy + y13, 0.25);
	glVertex3f(cx + x10, cy + y13, 0.25);


	glVertex3f(cx + x10, cy + y10, 0.25);
	glVertex3f(cx + x13, cy + y10, 0.25);
	glVertex3f(cx + x13, cy + y13, -0.25);
	glVertex3f(cx + x10, cy + y13, -0.25);


	glVertex3f(cx + x10, cy + y10, -0.25);
	glVertex3f(cx + x13, cy + y10, 0.25);
	glVertex3f(cx + x13, cy + y13, -0.25);
	glVertex3f(cx + x10, cy + y13, 0.25);

	glVertex3f(cx + x10, cy + y10, 0.25);
	glVertex3f(cx + x13, cy + y10, -0.25);
	glVertex3f(cx + x13, cy + y13, 0.25);
	glVertex3f(cx + x10, cy + y13, -0.25);

	glEnd();
	///////////////////////////////////
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(cx + x9, cy + y10, 0.25);
	glVertex3f(cx + x14, cy + y10, 0.25);
	glVertex3f(cx + x14, cy + y13, 0.25);
	glVertex3f(cx + x9, cy + y13, 0.25);

	glVertex3f(cx + x9, cy + y10, -0.25);
	glVertex3f(cx + x14, cy + y10, -0.25);
	glVertex3f(cx + x14, cy + y13, -0.25);
	glVertex3f(cx + x9, cy + y13, -0.25);

	glVertex3f(cx + x9, cy + y10, -0.25);
	glVertex3f(cx + x14, cy + y10, -0.25);
	glVertex3f(cx + x14, cy + y13, 0.25);
	glVertex3f(cx + x9, cy + y13, 0.25);

	glVertex3f(cx + x9, cy + y10, 0.25);
	glVertex3f(cx + x14, cy + y10, 0.25);
	glVertex3f(cx + x14, cy + y13, -0.25);
	glVertex3f(cx + x9, cy + y13, -0.25);

	glVertex3f(cx + x9, cy + y10, -0.25);
	glVertex3f(cx + x14, cy + y10, 0.25);
	glVertex3f(cx + x14, cy + y13, -0.25);
	glVertex3f(cx + x9, cy + y13, 0.25);

	glVertex3f(cx + x9, cy + y10, 0.25);
	glVertex3f(cx + x14, cy + y10, -0.25);
	glVertex3f(cx + x14, cy + y13, 0.25);
	glVertex3f(cx + x9, cy + y13, -0.25);
	glEnd();
	//////////////////////////////////
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(cx + x10, cy + y9, 0.25);
	glVertex3f(cx + x13, cy + y9, 0.25);
	glVertex3f(cx + x13, cy + x10, 0.25);
	glVertex3f(cx + x10, cy + y14, 0.25);

	glVertex3f(cx + x10, cy + y9, -0.25);
	glVertex3f(cx + x13, cy + y9, -0.25);
	glVertex3f(cx + x13, cy + x10, -0.25);
	glVertex3f(cx + x10, cy + y14, -0.25);

	glVertex3f(cx + x10, cy + y9, -0.25);
	glVertex3f(cx + x13, cy + y9, -0.25);
	glVertex3f(cx + x13, cy + x10, 0.25);
	glVertex3f(cx + x10, cy + y14, 0.25);

	glVertex3f(cx + x10, cy + y9, 0.25);
	glVertex3f(cx + x13, cy + y9, 0.25);
	glVertex3f(cx + x13, cy + x10, -0.25);
	glVertex3f(cx + x10, cy + y14, -0.25);

	glVertex3f(cx + x10, cy + y9, -0.25);
	glVertex3f(cx + x13, cy + y9, 0.25);
	glVertex3f(cx + x13, cy + x10, -0.25);
	glVertex3f(cx + x10, cy + y14, 0.25);

	glVertex3f(cx + x10, cy + y9, 0.25);
	glVertex3f(cx + x13, cy + y9, -0.25);
	glVertex3f(cx + x13, cy + x10, 0.25);
	glVertex3f(cx + x10, cy + y14, -0.25);
	glEnd();
	////////////////////////////////
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(cx + x9, cy + -8, 0.25);
	glVertex3f(cx + x14, cy + y9, 0.25);
	glVertex3f(cx + x14, cy + y14, 0.25);
	glVertex3f(cx + x9, cy + y14, 0.25);

	glVertex3f(cx + x9, cy + -8, -0.25);
	glVertex3f(cx + x14, cy + y9, -0.25);
	glVertex3f(cx + x14, cy + y14, -0.25);
	glVertex3f(cx + x9, cy + y14, -0.25);

	glVertex3f(cx + x9, cy + -8, -0.25);
	glVertex3f(cx + x14, cy + y9, -0.25);
	glVertex3f(cx + x14, cy + y14, 0.25);
	glVertex3f(cx + x9, cy + y14, 0.25);

	glVertex3f(cx + x9, cy + -8, 0.25);
	glVertex3f(cx + x14, cy + y9, 0.25);
	glVertex3f(cx + x14, cy + y14, -0.25);
	glVertex3f(cx + x9, cy + y14, -0.25);

	glVertex3f(cx + x9, cy + -8, -0.25);
	glVertex3f(cx + x14, cy + y9, 0.25);
	glVertex3f(cx + x14, cy + y14, -0.25);
	glVertex3f(cx + x9, cy + y14, 0.25);

	glVertex3f(cx + x9, cy + -8, 0.25);
	glVertex3f(cx + x14, cy + y9, -0.25);
	glVertex3f(cx + x14, cy + y14, 0.25);
	glVertex3f(cx + x9, cy + y14, -0.25);
	glEnd();
	//////////////////////////////////////End Draw Car//////////////////////////////////////////////

	drawString();
	get_backgeound();
	glutSwapBuffers();
}
//Texture
void load(int imgnum) {
	if (imgnum == 1) {

		data = stbi_load("my sky.jpeg", &Width, &Height, &nrChannels, 0);
		check(data);
	}
}
void check(unsigned char* data) {
	if (data)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
void timer(int v) {
	// repaint
	glutPostRedisplay();
	//spead
	glutTimerFunc(1000 / 20, timer, 0);
	//To stop game
	if (Stop)
	{
		y20--; y2--; y3--; y4--; y5--; y6--; y7--; y8--;
	}
	if (y2 == -30)
	{
		y20 = 30;
		y2 = 28;
		score++;
		z++;
	}
	if (y4 == -30)
	{
		y3 = 40;
		y4 = 38;
		score++;
		z++;
	}
	if (y6 == -30)
	{
		y5 = 60;
		y6 = 62;
		score++;
		z++;
	}
	if (y8 == -30)
	{
		y7 = 30;
		y8 = 28;
		score++;
		z++;
	}

	//collision
	if ((x1 == x9 + cx && y20 == y10 + cy) && (x2 == x10 + cx && y20 == y10 + cy) ||
		(x1 == x9 + cx && y2 == y9 + cy) && (x2 == x10 + cx && y2 == y9 + cy) ||

		(x3 == x9 + cx && y3 == y10 + cy) && (x4 == x10 + cx && y3 == y10 + cy) ||
		(x3 == x9 + cx && y4 == y9 + cy) && (x4 == x10 + cx && y4 == y9 + cy) ||

		(x5 == x9 + cx && y5 == y10 + cy) && (x6 == x10 + cx && y5 == y10 + cy) ||
		(x5 == x9 + cx && y6 == y9 + cy) && (x6 == x10 + cx && y6 == y9 + cy) ||

		(x7 == x9 + cx && y7 == y10 + cy) && (x8 == x10 + cx && y7 == y10 + cy) ||
		(x7 == x9 + cx && y8 == y9 + cy) && (x8 == x10 + cx && y8 == y9 + cy))
	{

		//Sound 
		PlaySound(TEXT("sound.mkv"), NULL, SND_ASYNC);
		y20 = y2 = y3 = y4 = y5 = y6 = y7 = y8 = -40;
		Lose = true;
	}
}
//To use button W & A & S & D & Esc
void keyboarddown(unsigned char key, int x, int y)
{
	if (key == 'A' || key == 'a')
	{
		if (x9 + cx < -8)
		{
			cx += 0;
		}
		else
		{
			cx -= 5;
		}
	}

	else if (key == 'D' || key == 'd')
	{
		if (x9 + cx > 5)
		{
			cx += 0;
		}
		else
		{
			cx += 5;
		}
	}

	else if (key == 'W' || key == 'w')
	{
		if (y9 + cy > 20)
		{
			cy += 0;
		}
		else
		{
			cy += 5;
		}
	}

	else if (key == 'S' || key == 's')
	{
		if (y9 + cy < -20)
		{
			cy += 0;
		}
		else
		{
			cy -= 5;
		}
	}

	else if (key == GLUT_KEY_F5)
		exit(1);
}
//To use button up & down & left & right
void keySpecialdown(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
	{
		eyez -= 1;
		eyey = 0.3 * abs(cos(angle));
		/*	if (y9 + cy > 20)
			{
				cy += 0;
			}
			else
			{
				cy += 0;
			}
			*/
	}
	else if (key == GLUT_KEY_DOWN)
	{
		eyez += 1;
		eyey = 0.3 * abs(cos(angle));

		/*if (y9 + cy < -20)
		{
			cy += 0;
		}
		else
		{
			cy -= 5;
		}
		*/
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		if (i > -2) {
			upx += 0.2 * cos(0.1);
			upz += 0.2 * sin(0.1);
			i--;
		}
		/*
		if (x9 + cx > 5)
		{
			cx += 0;
		}
		else
		{
			cx += 1;
		}
	}
	*/
	}
	else if (key == GLUT_KEY_LEFT) {
		if (i < 2) {
			upx -= 0.2 * cos(0.1);
			upz -= 0.2 * sin(0.1);
			i++;
		}
		/*
		if (x9 + cx < -8)
		{
			cx += 0;
		}
		else
		{
			cx -= 1;
		}
	}
	*/
	}
	else if (key == GLUT_KEY_F10) {
		fullscreen = !fullscreen;
		if (fullscreen)
			glutFullScreen();
		else {
			glutReshapeWindow(width / 2, height / 2);
			glutPositionWindow(width / 2 - width / 4, height / 2 - height / 4);

		}
	}
}
//Draw Score & We are Win or Lose
void drawString()
{
	if (z >= 50)
	{
		char win[] = "You Won";
		glColor3f(0, 0, 0);
		glRasterPos3f(35, 0, 0.0);
		y20 = y2 = y3 = y4 = y5 = y6 = y7 = y8 = -35;
		for (int j = 0; win[j] != '\0'; j++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, win[j]);
		Lose = true;
	}

	else if (y20 <= -40 && y2 <= -40 && y3 <= -40 && y4 <= -40
		&& y5 <= -40 && y6 <= -40 && y7 <= -40 && y8 <= -40)
	{
		char c[] = "You Are Lose";
		glColor3f(0, 0, 0);
		glRasterPos3f(35, 0, 0.0);
		for (int i = 0; c[i] != '\0'; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
		Lose = true;
	}

	glColor3f(0, 0, 0);
	glRasterPos3f(-40, 0, 0.0);
	char c[] = "Your Score is: ";
	int i;
	for (i = 0; c[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c[i]);
	}
	if (score >= 10)
		score = 0;

	if (z >= 10 && z < 20)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');

	else if (z >= 20 && z < 30)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '2');

	else if (z >= 30 && z < 40)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '3');

	else if (z >= 40 && z < 50)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '4');

	else if (z >= 50)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '5');

	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 48 + char(score));

}

//Mouse TO Stop and start again game
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (Stop == false)
		{
			Stop = true;
		}
		else if (Stop == true)
		{
			Stop = false;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && Lose) {
		y20 = 30; y2 = 28; y3 = 40; y4 = 38; y5 = 60; y6 = 62; y7 = 30; y8 = 28;
		Lose = false;
		score = 0;
		z = 0;
	}
}

void exit(int)
{
}
void reshape(int w, int h) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(160.0f, aspect, 0.25f, 100.0f);
}
void backGround() {
	// color [0,1]
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
}
void get_backgeound() {
	glEnable(GL_TEXTURE_2D);
	load(1);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-70, -100, 0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(70, -100, 0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(70, 100, 0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-70, 100, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}