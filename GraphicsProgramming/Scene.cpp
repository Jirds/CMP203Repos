#include "Scene.h"


// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input* in)
{
	// Store pointer for input class
	input = in;

	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	gluPerspective(120.0f, (GLfloat)16.0 / (GLfloat)9.0, 1, 150.0f);

	//glutSetCursor(GLUT_CURSOR_NONE);
	// Other OpenGL / render setting should be applied here.
	//glEnable(GL_LIGHTING);

	sphere.load("Models/largeSphere.obj", "Models/brick.jpg");

	/*glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Initialise scene variables
	*/
}

void Scene::handleInput(float dt)
{
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);
	if (input->isKeyDown('r'))
	{
		if (polygonMode[0] == GL_LINE)
		{
			glPolygonMode(GL_FRONT, GL_FILL);
			input->SetKeyUp('r');
		}
		else if (polygonMode[0] == GL_FILL)
		{
			glPolygonMode(GL_FRONT, GL_LINE);
			input->SetKeyUp('r');
		}
	}
	if (input->isKeyDown('w'))
	{
		camera1.moveForward(dt);
		input->SetKeyUp('w');
	}
	if (input->isKeyDown('s'))
	{
		camera1.moveBackward(dt);
		input->SetKeyUp('s');
	}
	if (input->isKeyDown('q'))
	{
		camera1.moveUp(dt);
		input->SetKeyUp('q');
	}
	if (input->isKeyDown('e'))
	{
		camera1.moveDown(dt);
		input->SetKeyUp('e');
	}


	float xCurr, yCurr = 0;
	float yaw = 0, pitch = 0, roll = 0;
	//Get the change in mouse position since last frame
	yaw = input->getMouseX() - xLast;
	pitch = input->getMouseY() - yLast;
	yaw = 0 - yaw;
	yaw *= 7 * dt;
	pitch *= 10 * dt;
	camera1.viewRotate(yaw, pitch, roll);
	//Save mouse position as last mouse position
	xLast = input->getMouseX();
	yLast = input->getMouseY();
	// Handle user input
	void setKeyDown(unsigned char key);
	void setKeyup(unsigned char key);
	bool isKeyDown(int);



}
void Scene::update(float dt)
{
	// update scene related variables.
	camera1.update();
	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera  (Translate, Coords of intrest, Which way is up)
	//			x	y	  z     x(?)  y(?)  z(?)
	//gluLookAt(camera1.getPos().x, camera1.getPos().y, camera1.getPos().z, camera1.getLook().x, camera1.getLook().y, camera1.getLook().z, camera1.getUp().x, camera1.getUp().y, camera1.getUp().z);
	gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 5.0, 0.0, 1.0, 0.0);

	GLfloat Light_Ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat Light_Diffuse[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat Light_Specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat Light_Position[] = { 0.0f, 0.0f, 5.0f, 1.0f };


	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light_Specular);



	//glEnable(GL_LIGHT0);

	sphere.render();

	glBegin(GL_TRIANGLE_FAN);



	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-50.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 0.0f, -50.0f);
	glVertex3f(50.0f, 0.0f, -50.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);
	glEnd();

	// Render text, should be last object rendered.
	renderTextOutput();

	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h)
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);


}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width / (float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
