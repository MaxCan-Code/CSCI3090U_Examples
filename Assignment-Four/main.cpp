/************************************************
 *
 *             Example Four
 *
 *  A basic OpenGL program that draws a
 *  triangle on the screen in perspective with
 *  simple control over the eye position.  
 *  This program illustrates the construction of
 *  perspective and viewing transformations.
 *
 ************************************************/

//#include <Windows.h>
#include <gl/glew.h>
#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shaders.h>
#include <stdio.h>

GLuint program;			// shader programs
GLuint triangleVAO;		// the data to be displayed
float angle = 0.0;
double theta, phi;		// user's position  on a sphere centered on the object
double r;				// radius of the sphere
GLuint ibuffer;

glm::mat4 projection;	// projection matrix
float eyex, eyey, eyez;	// eye position

/*
 *  The init procedure creates the OpenGL data structures
 *  that contain the triangle geometry, compiles our
 *  shader program and links the shader programs to
 *  the data.
 */

void init() {
	GLuint vbuffer;
	GLint vPosition;
	GLint vNormal;
	int vs;
	int fs;

	glGenVertexArrays(1, &triangleVAO);
	glBindVertexArray(triangleVAO);

    glm::vec3 pair[] = {
            glm::vec3(-.5, .5, -.5), //0
            glm::vec3(-.5, -.5, .5), //1
    };
    glm::vec3 diff = pair[1] - pair[0];

    float x, y, z;
    x = diff.x;
    y = diff.y;
    z = diff.z;

    float minh = glm::min(glm::min(x, y), z);

    glm::vec3 swap, kris, kross, add_ris, sub_ris, add_ross, sub_ross;

    if (x <= minh) { swap = glm::vec3(x, -y, z); }
    else if (y <= minh) { swap = glm::vec3(-z, y, x); }
    else swap = glm::vec3(-y, x, z);

    kris = glm::cross(diff, swap);
    kris = glm::normalize(kris);

    kross = glm::cross(kris, swap);
    kross = glm::normalize(kross);

    add_ris = pair[0] + kris;
    sub_ris = pair[0] - kris;

    add_ross = pair[0] + kross;
    sub_ross = pair[0] - kross;

    glm::vec4 vertices[] = {
            glm::vec4(add_ris, 1), //0
            glm::vec4(sub_ris, 1), //1
            glm::vec4(add_ross, 1), //2
            glm::vec4(sub_ross, 1), //3

            glm::vec4(add_ris + diff, 1), //4
            glm::vec4(sub_ris + diff, 1), //5
            glm::vec4(add_ross + diff, 1), //7
            glm::vec4(sub_ross + diff, 1) //6
    };

/*
    GLushort indexes[8];
    for (int i = 0; i <= 8-1; i++)
        indexes[i] = i;
*/

    GLushort indexes[36] = {
            0, 1, 3, 0, 2, 3,
            0, 4, 5, 0, 1, 5,
            2, 6, 7, 2, 3, 7,
            0, 4, 6, 0, 2, 6,
            1, 5, 7, 1, 3, 7,
            4, 5, 7, 4, 6, 7
    };

	GLfloat normals[8][3] = {
//		{ -1.0, -1.0, -1.0 }, //0
		{ -1.0, -1.0, 1.0 }, //1
//		{ -1.0, 1.0, -1.0 }, //2
		{ -1.0, 1.0, 1.0 }, //3
//		{ 1.0, -1.0, -1.0 }, //4
		{ 1.0, -1.0, 1.0 }, //5
		{ 1.0, 1.0, -1.0 }, //6
		{ 1.0, 1.0, 1.0 } //7
	};

	/*
	 *  load the vertex coordinate data
	 */
	glGenBuffers(1, &vbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(normals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);

	/*
	 *  load the vertex indexes
	 */
	glGenBuffers(1, &ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	/*
	 *  compile and build the shader program
	 */
	vs = buildShader(GL_VERTEX_SHADER, "example4.vs");
	fs = buildShader(GL_FRAGMENT_SHADER, "example4.fs");
	program = buildProgram(vs,fs,0);

	/*
	 *  link the vertex coordinates to the vPosition
	 *  variable in the vertex program
	 */
	glUseProgram(program);
	vPosition = glGetAttribLocation(program,"vPosition");
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vPosition);
	vNormal = glGetAttribLocation(program, "vNormal");
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*) sizeof(vertices));
	glEnableVertexAttribArray(vNormal);

    glEnable(GL_PROGRAM_POINT_SIZE);
}

void framebufferSizeCallback(GLFWwindow *window, int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).

	if (h == 0)
		h = 1;

	float ratio = 1.0f * w / h;

	glfwMakeContextCurrent(window);

	glViewport(0, 0, w, h);

	projection = glm::perspective(0.7f, ratio, 1.0f, 100.0f);

}

/*
 *  This procedure is called each time the screen needs
 *  to be redisplayed
 */
void display() {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 modelViewPerspective;
	int modelLoc;
	int normalLoc;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	model = glm::rotate(glm::mat4(1.0), angle, glm::vec3(0.0, 1.0, 0.0));

	view = glm::lookAt(glm::vec3(eyex, eyey, eyez),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat3 normal = glm::transpose(glm::inverse(glm::mat3(view*model)));
					
	modelViewPerspective = projection * view * model;

	glUseProgram(program);
	modelLoc = glGetUniformLocation(program,"model");
	glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(modelViewPerspective));
	normalLoc = glGetUniformLocation(program,"normalMat");
	glUniformMatrix3fv(normalLoc, 1, 0, glm::value_ptr(normal));

	glBindVertexArray(triangleVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, NULL);
	glDrawElements(GL_POINTS, 36, GL_UNSIGNED_SHORT, NULL);
	glDrawElements(GL_LINE_STRIP, 36, GL_UNSIGNED_SHORT, NULL);
//	from https://solarianprogrammer.com/2013/05/13/opengl-101-drawing-primitives/

}


/*
 *  Called each time a key is pressed on
 *  the keyboard.
 */

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		phi -= 0.1;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		phi += 0.1;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		theta += 0.1;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		theta -= 0.1;

	eyex = (float)(r*sin(theta)*cos(phi));
	eyey = (float)(r*sin(theta)*sin(phi));
	eyez = (float)(r*cos(theta));

}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


int main(int argc, char **argv) {
	GLFWwindow *window;

	// start by setting error callback in case something goes wrong

	glfwSetErrorCallback(error_callback);

	// initialize glfw

	if (!glfwInit()) {
		fprintf(stderr, "can't initialize GLFW\n");
	}

	// create the window used by our application
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(512, 512, "Example Four", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// establish framebuffer size change and input callbacks

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glfwSetKeyCallback(window, key_callback);

	/*
	 *  initialize glew
	 */
	glfwMakeContextCurrent(window);
//    glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if(error != GLEW_OK) {
		printf("Error starting GLEW: %s\n",glewGetErrorString(error));
		exit(0);
	}

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glViewport(0, 0, 512, 512);

	projection = glm::perspective(0.7f, 1.0f, 1.0f, 100.0f);

	init();

	theta = 0.0;
	phi = -1.5;
	r = 6.0;

    eyex = (float) (r * sin(theta) * cos(phi));
    eyey = (float) (r * sin(theta) * sin(phi));
    eyez = (float) (r * cos(theta));

	glfwSwapInterval(1);

	// GLFW main loop, display model, swapbuffer and check for input

	while (!glfwWindowShouldClose(window)) {
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

}