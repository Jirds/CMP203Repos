#include "shape.h"


extern float verts[] = {	-1.0, 1.0, 1.0,			// Vertex #0
							-1.0, -1.0, 1.0,		// Vertex #1
							1.0,  -1.0, 1.0,		// Vertex #2
							1.0,  1.0, 1.0,			// Vertex #3
						};

extern float cubeVerts[] = {	-1.0, -1.0, -1.0,			// Vertex #0
								1.0, -1.0, -1.0,		// Vertex #1
								1.0,  1.0, -1.0,		// Vertex #2
								-1.0,  1.0, -1.0,		// Vertex #3
								-1.0, -1.0, 1.0,		// Vertex #4
								-1.0, -1.0, 1.0,		// Vertex #5
								1.0,  1.0, 1.0,			// Vertex #6
								-1.0,  1.0, 1.0,		// Vertex #7
						};



extern float norms[] = { 0.0, 0.0, 1.0,		//0
						0.0, 0.0, 1.0,		//1
 						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,		//3
						};		


extern float texCoords[]= {	0.0, 0.0, 		//0
							0.0, 1.0, 		//1
 							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
							};

void Shape::render1()
{
	// add code to render the cube (above) using method 1
	// glArrayElement()

	glBegin(GL_QUADS);
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(3);
	glEnd();

}

void Shape::render2()
{
	// add code to render the cube (above) using method 2
	// glDrawArrays()

}

void Shape::render3()
{
	// add code to render the cube (above) using method 3
	// glDrawElements()

}


