#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

std::vector<GLuint> compiledPrograms;

struct GameObject {

	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 rotation = glm::vec3(0.f);
	glm::vec3 scale = glm::vec3(1.f);
};

GLuint VAO_cubo, VBO_cubo, EBO_cubo;
GLuint VAO_ortoedro, VBO_ortoedro, EBO_ortoedro;
GLuint VAO_piramide, VBO_piramide, EBO_piramide;

struct ShaderProgram {

	GLuint vertexShader = 0;
	GLuint geometryShader = 0;
	GLuint fragmentShader = 0;
};

struct Camera
{
	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 localVectorUp = glm::vec3(0.f);
	glm::vec3 offset = glm::vec3(1.f);

	float fFov = 45.f;
	float fNear = 0.1f;
	float fFar = 10.f;
};

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	//Definir nuevo tamaño del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);

	glUniform2f(glGetUniformLocation(compiledPrograms[0], "windowSize"), iFrameBufferWidth, iFrameBufferHeight);

}

//Funcion que genera una matriz de escalado representada por un vector
glm::mat4 GenerateScaleMatrix(glm::vec3 scaleAxis) {

	return glm::scale(glm::mat4(1.0f), scaleAxis);
}

//Funcion que genera una matriz de rotacion dado un angulo y un vector
glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees) {

	return glm::rotate(glm::mat4(1.0f), glm::radians(fDegrees), glm::normalize(axis));
}

//Funcion que genera una matriz de traslacion representada por un vector
glm::mat4 GenerateTranslationMatrix(glm::vec3 translation) {

	return glm::translate(glm::mat4(1.0f), translation);
}

//Funcion que devolvera una string con todo el archivo leido
std::string Load_File(const std::string& filePath) {

	std::ifstream file(filePath);

	std::string fileContent;
	std::string line;

	//Lanzamos error si el archivo no se ha podido abrir
	if (!file.is_open()) {
		std::cerr << "No se ha podido abrir el archivo: " << filePath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//Leemos el contenido y lo volcamos a la variable auxiliar
	while (std::getline(file, line)) {
		fileContent += line + "\n";
	}

	//Cerramos stream de datos y devolvemos contenido
	file.close();

	return fileContent;
}

GLuint LoadFragmentShader(const std::string& filePath) {

	// Crear un fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Usamos la funcion creada para leer el fragment shader y almacenarlo 
	std::string sShaderCode = Load_File(filePath);
	const char* cShaderSource = sShaderCode.c_str();

	//Vinculamos el fragment shader con su código fuente
	glShaderSource(fragmentShader, 1, &cShaderSource, nullptr);

	// Compilar el fragment shader
	glCompileShader(fragmentShader);

	// Verificar errores de compilación
	GLint success;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	//Si la compilacion ha sido exitosa devolvemos el fragment shader
	if (success) {

		return fragmentShader;

	}
	else {

		//Obtenemos longitud del log
		GLint logLength;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

		//Obtenemos el log
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(fragmentShader, logLength, nullptr, errorLog.data());

		//Mostramos el log y finalizamos programa
		std::cerr << "Se ha producido un error al cargar el fragment shader:  " << errorLog.data() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}


GLuint LoadGeometryShader(const std::string& filePath) {

	// Crear un vertex shader
	GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

	//Usamos la funcion creada para leer el vertex shader y almacenarlo 
	std::string sShaderCode = Load_File(filePath);
	const char* cShaderSource = sShaderCode.c_str();

	//Vinculamos el vertex shader con su código fuente
	glShaderSource(geometryShader, 1, &cShaderSource, nullptr);

	// Compilar el vertex shader
	glCompileShader(geometryShader);

	// Verificar errores de compilación
	GLint success;
	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

	//Si la compilacion ha sido exitosa devolvemos el vertex shader
	if (success) {

		return geometryShader;

	}
	else {

		//Obtenemos longitud del log
		GLint logLength;
		glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &logLength);

		//Obtenemos el log
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(geometryShader, logLength, nullptr, errorLog.data());

		//Mostramos el log y finalizamos programa
		std::cerr << "Se ha producido un error al cargar el vertex shader:  " << errorLog.data() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

GLuint LoadVertexShader(const std::string& filePath) {

	// Crear un vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Usamos la funcion creada para leer el vertex shader y almacenarlo 
	std::string sShaderCode = Load_File(filePath);
	const char* cShaderSource = sShaderCode.c_str();

	//Vinculamos el vertex shader con su código fuente
	glShaderSource(vertexShader, 1, &cShaderSource, nullptr);

	// Compilar el vertex shader
	glCompileShader(vertexShader);

	// Verificar errores de compilación
	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	//Si la compilacion ha sido exitosa devolvemos el vertex shader
	if (success) {

		return vertexShader;

	}
	else {

		//Obtenemos longitud del log
		GLint logLength;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

		//Obtenemos el log
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(vertexShader, logLength, nullptr, errorLog.data());

		//Mostramos el log y finalizamos programa
		std::cerr << "Se ha producido un error al cargar el vertex shader:  " << errorLog.data() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

//Función que dado un struct que contiene los shaders de un programa generara el programa entero de la GPU
GLuint CreateProgram(const ShaderProgram& shaders) {

	//Crear programa de la GPU
	GLuint program = glCreateProgram();

	//Verificar que existe un vertex shader y adjuntarlo al programa
	if (shaders.vertexShader != 0) {
		glAttachShader(program, shaders.vertexShader);
	}

	if (shaders.geometryShader != 0) {
		glAttachShader(program, shaders.geometryShader);
	}

	if (shaders.fragmentShader != 0) {
		glAttachShader(program, shaders.fragmentShader);
	}

	// Linkear el programa
	glLinkProgram(program);

	//Obtener estado del programa
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	//Devolver programa si todo es correcto o mostrar log en caso de error
	if (success) {

		//Liberamos recursos
		if (shaders.vertexShader != 0) {
			glDetachShader(program, shaders.vertexShader);
		}

		//Liberamos recursos
		if (shaders.geometryShader != 0) {
			glDetachShader(program, shaders.geometryShader);
		}

		//Liberamos recursos
		if (shaders.fragmentShader != 0) {
			glDetachShader(program, shaders.fragmentShader);
		}

		return program;
	}
	else {

		//Obtenemos longitud del log
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		//Almacenamos log
		std::vector<GLchar> errorLog(logLength);
		glGetProgramInfoLog(program, logLength, nullptr, errorLog.data());

		std::cerr << "Error al linkar el programa:  " << errorLog.data() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void main() {

	//Definir semillas del rand según el tiempo
	srand(static_cast<unsigned int>(time(NULL)));

	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	//Configuramos la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	//Asignamos función de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_BACK);

	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {

		Camera camera;
		GameObject object;

		//Compilar shaders
		ShaderProgram myFirstProgram;
		myFirstProgram.vertexShader = LoadVertexShader("VertexShader.glsl");
		myFirstProgram.geometryShader = LoadGeometryShader("GeometryShader.glsl");
		myFirstProgram.fragmentShader = LoadFragmentShader("FragmentShader.glsl");

		//Compilar programa
		compiledPrograms.push_back(CreateProgram(myFirstProgram));

		//Definimos color para limpiar el buffer de color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		GLfloat verticeCubo[] = {
			-0.5f, +0.5f, -0.5f,  // 0
			+0.5f, +0.5f, -0.5f,  // 1
			+0.5f, -0.5f, -0.5f,  // 2
			-0.5f, -0.5f, -0.5f,  // 3
			-0.5f, +0.5f, +0.5f,  // 4
			+0.5f, +0.5f, +0.5f,  // 5
			+0.5f, -0.5f, +0.5f,  // 6
			-0.5f, -0.5f, +0.5f   // 7
		};

		GLuint indiceCubo[] = {
			0,1,2, 0,2,3, // cara trasera
			4,6,5, 4,7,6, // cara delantera
			4,5,1, 4,1,0, // cara superior
			3,2,6, 3,6,7, // cara inferior
			4,0,3, 4,3,7, // cara izquierda
			1,5,6, 1,6,2  // cara derecha
		};

		GLfloat verticeOrtoedro[] = {
			-0.25f, +0.5f, -0.25f,  // 0
			+0.25f, +0.5f, -0.25f,  // 1
			+0.25f, -0.5f, -0.25f,  // 2
			-0.25f, -0.5f, -0.25f,  // 3
			-0.25f, +0.5f, +0.25f,  // 4
			+0.25f, +0.5f, +0.25f,  // 5
			+0.25f, -0.5f, +0.25f,  // 6
			-0.25f, -0.5f, +0.25f   // 7
		};

		GLuint indiceOrtoedro[] = {
			0,1,2, 0,2,3,
			4,6,5, 4,7,6,
			4,5,1, 4,1,0,
			3,2,6, 3,6,7,
			4,0,3, 4,3,7,
			1,5,6, 1,6,2
		};

		GLfloat verticePiramide[] = {
			-0.5f, -0.5f, -0.5f,  // 0 base
			+0.5f, -0.5f, -0.5f,  // 1 base
			+0.5f, -0.5f, +0.5f,  // 2 base
			-0.5f, -0.5f, +0.5f,  // 3 base
			 0.0f, +0.5f,  0.0f   // 4 ápice
		};

		GLuint indicePiramide[] = {
			0,2,1, 0,3,2, // base
			0,1,4,        // cara frontal
			1,2,4,        // cara derecha
			2,3,4,        // cara trasera
			3,0,4         // cara izquierda
		};

		//CUBO
		glGenVertexArrays(1, &VAO_cubo);
		glGenBuffers(1, &VBO_cubo);
		glGenBuffers(1, &EBO_cubo);

		glBindVertexArray(VAO_cubo);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_cubo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticeCubo), verticeCubo, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_cubo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indiceCubo), indiceCubo, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		//ORTOEDRO
		glGenVertexArrays(1, &VAO_ortoedro);
		glGenBuffers(1, &VBO_ortoedro);
		glGenBuffers(1, &EBO_ortoedro);

		glBindVertexArray(VAO_ortoedro);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_ortoedro);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticeOrtoedro), verticeOrtoedro, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ortoedro);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indiceOrtoedro), indiceOrtoedro, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		//PIRÁMIDE
		glGenVertexArrays(1, &VAO_piramide);
		glGenBuffers(1, &VBO_piramide);
		glGenBuffers(1, &EBO_piramide);

		glBindVertexArray(VAO_piramide);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_piramide);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticePiramide), verticePiramide, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_piramide);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicePiramide), indicePiramide, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		//Indicar a la tarjeta GPU que programa debe usar
		glUseProgram(compiledPrograms[0]);

		camera.position = glm::vec3(0.0f, 0.0f, 5.0f);
		camera.localVectorUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 viewMatrix = glm::lookAt(camera.position, glm::vec3(0.0f, 0.0f, 0.0f), camera.localVectorUp);
		glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera.fFov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, camera.fNear, camera.fFar);

		// Asignar valores iniciales al programa
		glUniform2f(glGetUniformLocation(compiledPrograms[0], "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
		glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));


		bool bWireframe = false;
		bool bKey1Pressed = false;

		float rotacionFigura = 0.0f;
		float posicionFigura = 0.0f;
		float movimientoFigura = 0.01f;
		float limiteArriba = 1;
		float limiteAbajo = -1;

		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) {

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();

			rotacionFigura += 1.f;
			posicionFigura += movimientoFigura;

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			glUseProgram(compiledPrograms[0]);


			if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !bKey1Pressed) 
			{
				bKey1Pressed = true;
				bWireframe = !bWireframe;
				glPolygonMode(GL_FRONT_AND_BACK, bWireframe ? GL_LINE : GL_FILL);
			}
			if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE) 
			{
				bKey1Pressed = false;
			}

			glm::mat4 modelCubo = glm::translate(glm::mat4(1.0f), glm::vec3(-1.8f, posicionFigura, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotacionFigura), glm::vec3(0.0, 1.0, 0.0));

			if (posicionFigura >= limiteArriba)
			{
				movimientoFigura -= 0.01;
			}
			if (posicionFigura <= limiteAbajo)
			{
				movimientoFigura += 0.01;
			}

			glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "Model"), 1, GL_FALSE, glm::value_ptr(modelCubo));
			glBindVertexArray(VAO_cubo);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

			glm::mat4 modelOrtoedro = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotacionFigura), glm::vec3(0.0, 0.0, 1.0));
			glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "Model"), 1, GL_FALSE, glm::value_ptr(modelOrtoedro));
			glBindVertexArray(VAO_ortoedro);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

			glm::mat4 modelPiramide = glm::translate(glm::mat4(1.0f), glm::vec3(1.8f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotacionFigura), glm::vec3(1.0, 1.0, 0.0));
			glUniformMatrix4fv(glGetUniformLocation(compiledPrograms[0], "Model"), 1, GL_FALSE, glm::value_ptr(modelPiramide));
			glBindVertexArray(VAO_piramide);
			glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

			//Dejamos de usar el VAO indicado anteriormente
			glBindVertexArray(0);

			//Cambiamos buffers
			glFlush();
			glfwSwapBuffers(window);
		}

		//Desactivar y eliminar programa
		glUseProgram(0);
		glDeleteProgram(compiledPrograms[0]);

	}
	else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}

	//Finalizamos GLFW
	glfwTerminate();

}