#include<glm/glm.hpp>
#include<iostream>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
void resizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int modifier);
GLuint createProgram();
GLuint createProgram1();
void drawtriangle();
void init();
void triangle2();
GLuint VBO[2];
GLuint VAO[2];
GLuint EBO[1];
GLuint programs[2];
float angle = 10;
glm::vec3 lightPosition(2.0, 1.0, -3.0);
int main(int argc, char** argv) {

	if (!glfwInit()) {
		std::cout << "Could not initialize glfw" << std::endl;
		exit(1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!gladLoadGL()) {
		std::cout << "Could not initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	//

	float vertices[] = {
		// positions // normals // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};


	//
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	init();
	//triangle2();
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {

		

		



		glClearColor(0.5, 0.3, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//


		GLuint cubeVBO;
		glGenBuffers(1, &cubeVBO);

		//vao
		GLuint cubeVAO;
		glGenVertexArrays(1, &cubeVAO);


		//vbo
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(cubeVAO);


		//get location of attribute
		GLuint program = createProgram();
		programs[0] = program;
		glm::mat4 model = glm::mat4(1.0);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 view = glm::mat4(1.0);
		view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0f));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);

		glm::vec3 lightSource(1.0, 1.0, 1.0);
		glm::vec3 objectColor(1.0, 0.5, 0.31);

		unsigned int modelLocation = glGetUniformLocation(programs[0], "model");
		unsigned int viewLocation = glGetUniformLocation(programs[0], "view");
		unsigned int projectionLocation = glGetUniformLocation(programs[0], "projection");
		GLuint objectColorLocation = glGetUniformLocation(programs[0], "objectColor");
		GLuint lightColorLocation = glGetUniformLocation(programs[0], "lightColor");
		GLuint lightPosLocation = glGetUniformLocation(programs[0], "lightPos");

		glUseProgram(programs[0]);

		glUniform3fv(objectColorLocation, 1, glm::value_ptr(objectColor));
		glUniform3fv(lightColorLocation, 1, glm::value_ptr(lightSource));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(lightPosLocation, 1, glm::value_ptr(lightPosition));
		


		GLint aPos = glGetAttribLocation(programs[0], "aPos");
		//configure vertex data
		glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(aPos);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0);
		model = glm::translate(model, lightPosition);
		model = glm::scale(model, glm::vec3(0.4));
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5, 0.0, 0.0));
		glm::vec3 lightPos = model * glm::vec4(lightPosition, 1.0f);
		
		GLuint lightVAO;
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);
		GLuint program1 = createProgram1();
		
		
		int modelLocation1 = glGetUniformLocation(program1, "model");
		unsigned int viewLocation1 = glGetUniformLocation(program1, "view");
		unsigned int projectionLocation1 = glGetUniformLocation(program1, "projection");
		GLuint objectColorLocation1 = glGetUniformLocation(program1, "objectColor");
		

		//configure vertex data
		glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(aPos);


		
		glUseProgram(program1);
		glUniform3fv(objectColorLocation1,1,glm::value_ptr(glm::vec3(1.0,1.0,1.0)));
		glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLocation1, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLocation1, 1, GL_FALSE, glm::value_ptr(projection));


		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//
		


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;

}

void resizeCallback(GLFWwindow* window, int width, int height)
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int modifier)
{

	if (key == GLFW_KEY_EQUAL && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		angle += 1;
	}
	else if (key == GLFW_KEY_MINUS && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		angle -= 1;
	}
	else {
		return;
	}
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(angle), 800.0f / 600.0f, 1.0f, 100.0f);

	GLuint projectionLocation = glGetUniformLocation(programs[0], "projection");
	glUseProgram(programs[0]);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
	std::cout << "angle: " << angle << std::endl;
}

GLuint createProgram()
{
	const char* vertexSource = "#version 330 core\n"
		"in vec3 aPos;\n"
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"layout (location = 1) in vec3 aNormal;"
		"out vec3 Normal;"
		"out vec3 fragPos;"
		"void main(){\n"
		"gl_Position= projection * view * model * vec4(aPos,1.0);"
		"Normal=aNormal;"
		"fragPos=vec3(model*vec4(aPos,1.0));"
		"\n}\0";
	const char* fragmentSource = "#version 330 core\n"
		"out vec4 fragColor;"
		"uniform vec3 objectColor;"
		"uniform vec3 lightColor;"
		"uniform vec3 lightPos;"
		"in vec3 Normal;"
		"in vec3 fragPos;"
		"void main()\n{"
		"float ambientStrength=0.3;"
		"vec3 ambient= ambientStrength * lightColor;"
		"vec3 norm=normalize(Normal);"
		"vec3 lightDir=normalize(lightPos-fragPos);"
		"float diff=max(dot(lightPos,norm),0.0);"
		"vec3 diffuse=diff*lightDir;"
		"vec3 result=(ambient+diffuse)*objectColor;"
		"fragColor=vec4(result,1.0);"
		"\n}\0";

	//create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	//check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error compiling vertex shader : " << infoLog << std::endl;
	}
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	//check for errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "Error compiling fragment shader: " << infoLog << std::endl;
	}

	//create program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	programs[0] = program;

	//check for errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Error linking program: " << infoLog << std::endl;
	}
	return program;
}

GLuint createProgram1()
{
	const char* vertexSource = "#version 330 core\n"
		"in vec3 aPos;\n"
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"void main(){\n"
		"gl_Position= projection * view * model * vec4(aPos,1.0);"
		"\n}\0";
	const char* fragmentSource = "#version 330 core\n"
		"out vec4 fragColor;"
		"uniform vec3 objectColor;"
		"void main()\n{"
		"fragColor=vec4(objectColor,1.0);"
		"\n}\0";

	//create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	//check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error compiling vertex shader : " << infoLog << std::endl;
	}
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	//check for errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "Error compiling fragment shader: " << infoLog << std::endl;
	}

	//create program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	programs[0] = program;

	//check for errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Error linking program: " << infoLog << std::endl;
	}
	return program;

}

void drawtriangle()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(programs[0]);
	glBindVertexArray(VAO[0]);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//glBindVertexArray(VAO[1]);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

}

void init()
{
	float vertices[] = {
-0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, 0.5f, -0.5,
0.5f, 0.5f, -0.5f,
-0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,

-0.5f, -0.5f, 0.5f,
0.5f, -0.5f, 0.5f,
0.5f, 0.5f, 0.5f,
0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,

-0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, 0.5f,
-0.5f, 0.5f, 0.5f,

0.5f, 0.5f, 0.5f,
0.5f, 0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, -0.5f, 0.5f,
0.5f, 0.5f, 0.5f,

-0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5,
0.5f, -0.5f, 0.5f,
0.5f, -0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,
-0.5f, -0.5f, -0.5f,

-0.5f, 0.5f, -0.5f,
0.5f, 0.5f, -0.5f,
0.5f, 0.5f, 0.5f,
0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, -0.5f,
	};

	glGenBuffers(2, VBO);

	//vao
	GLuint cubeVAO;
	glGenVertexArrays(2, VAO);
	

	//vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO[0]);


	//get location of attribute
	programs[0] = createProgram();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.0, 0.1, 0.0));

	glm::mat4 view = glm::mat4(1.0);
	view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);

	glm::vec3 lightSource(1.0, 1.0, 1.0);
	glm::vec3 objectColor(1.0, 0.5, 0.31);

	unsigned int modelLocation = glGetUniformLocation(programs[0], "model");
	unsigned int viewLocation = glGetUniformLocation(programs[0], "view");
	unsigned int projectionLocation = glGetUniformLocation(programs[0], "projection");
	GLuint objectColorLocation = glGetUniformLocation(programs[0], "objectColor");
	GLuint lightColorLocation = glGetUniformLocation(programs[0], "lightColor");

	glUseProgram(programs[0]);

	glUniform3fv(objectColorLocation, 1, glm::value_ptr(objectColor));
	glUniform3fv(lightColorLocation, 1, glm::value_ptr(lightSource));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));


	GLint aPos = glGetAttribLocation(programs[0], "aPos");
	//configure vertex data
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(aPos);
	
	/*programs[1] = createProgram();
	glGenVertexArrays(1, &VAO[1]);
	glBindVertexArray(VAO[1]);
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.8, 0, 0.0));
	model = glm::scale(model, glm::vec3(0.2));
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0, 0.0));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	//configure vertex data
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(aPos);
	*/
	

	

}

void triangle2()
{
	float vertices[] = {
 -0.5f, -0.5f, -0.5f,
 0.5f, -0.5f, -0.5f,
 0.5f, 0.5f, -0.5,
 0.5f, 0.5f, -0.5f,
 -0.5f, 0.5f, -0.5f,
 -0.5f, -0.5f, -0.5f,

 -0.5f, -0.5f, 0.5f,
 0.5f, -0.5f, 0.5f,
 0.5f, 0.5f, 0.5f,
 0.5f, 0.5f, 0.5f,
 -0.5f, 0.5f, 0.5f,
 -0.5f, -0.5f, 0.5f,

 -0.5f, 0.5f, 0.5f,
 -0.5f, 0.5f, -0.5f,
 -0.5f, -0.5f, -0.5f,
 -0.5f, -0.5f, -0.5f,
 -0.5f, -0.5f, 0.5f,
 -0.5f, 0.5f, 0.5f,

 0.5f, 0.5f, 0.5f,
 0.5f, 0.5f, -0.5f,
 0.5f, -0.5f, -0.5f,
 0.5f, -0.5f, -0.5f,
 0.5f, -0.5f, 0.5f,
 0.5f, 0.5f, 0.5f,

 -0.5f, -0.5f, -0.5f,
 0.5f, -0.5f, -0.5,
 0.5f, -0.5f, 0.5f,
 0.5f, -0.5f, 0.5f,
 -0.5f, -0.5f, 0.5f,
 -0.5f, -0.5f, -0.5f,

 -0.5f, 0.5f, -0.5f,
 0.5f, 0.5f, -0.5f,
 0.5f, 0.5f, 0.5f,
 0.5f, 0.5f, 0.5f,
 -0.5f, 0.5f, 0.5f,
 -0.5f, 0.5f, -0.5f,
	};
	
	//second cube
	glBindVertexArray(VAO[1]);

	//vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//get location of attribute
	programs[1] = createProgram1();
	glm::mat4 model1 = glm::mat4(1.0);
	model1 = glm::rotate(model1, glm::radians(-55.0f), glm::vec3(0.0, 0.1, 0.0));
	model1 = glm::scale(model1, glm::vec3(0.5, 0.5, 0.5));
	glm::mat4 view1 = glm::mat4(1.0);
	view1 = glm::translate(view1, glm::vec3(0.0, 0.8, -3.0f));

	glm::mat4 projection1;
	projection1 = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);

	glm::vec3 lightSource1(1.0, 1.0, 1.0);
	glm::vec3 objectColor1(1.0, 0.5, 0.31);

	unsigned int modelLocation1 = glGetUniformLocation(programs[1], "model");
	unsigned int viewLocation1 = glGetUniformLocation(programs[1], "view");
	unsigned int projectionLocation1 = glGetUniformLocation(programs[1], "projection");
	GLuint objectColorLocation1 = glGetUniformLocation(programs[1], "objectColor");
	GLuint lightColorLocation1 = glGetUniformLocation(programs[1], "lightColor");

	glUseProgram(programs[1]);

	glUniform3fv(objectColorLocation1, 1, glm::value_ptr(objectColor1));
	glUniform3fv(lightColorLocation1, 1, glm::value_ptr(lightSource1));
	glUniformMatrix4fv(modelLocation1, 1, GL_FALSE, glm::value_ptr(model1));
	glUniformMatrix4fv(viewLocation1, 1, GL_FALSE, glm::value_ptr(view1));
	glUniformMatrix4fv(projectionLocation1, 1, GL_FALSE, glm::value_ptr(projection1));


	GLint aPos1 = glGetAttribLocation(programs[1], "aPos");
	//configure vertex data
	glVertexAttribPointer(aPos1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(aPos1);

}
