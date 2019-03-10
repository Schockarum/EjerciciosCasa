/*----------------------------------------------------------------------------------
-------------------------------- Pr�ctica 5 ----------------------------------------
---------------------------------- 2019-2 ------------------------------------------
------------- Computaci�n gr�fica e interacci�n humano computadora -----------------
------------------------ Esparza V�zquez Luis Mauricio -----------------------------
-------------------------------- 311078343 -----------------------------------------
---------------------------------- Gpo4 --------------------------------------------
Visual Studio 2017


Botones C�mara:
W - Arriba
A - Izquierda
S - Abajo
D - Derecha

Q - Alejar
E - Acercar

Botones de Rotaci�n:
Flecha Izq : Rotar a la izquierda
Flecha Der : Rotar a la derecha
Flecha Arr : Rotar arriba
Flecha Aba : Rotar abajo

Botones de movimiento de Brazo:
T : Hombro
Y : Antebrazo
U : Palma
I : Dedos (todos)

Shift izquierdo antes de cualquier bot�n regresa la rotaci�n
*/
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void display(void);
void getResolution(void);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotY = 0.0f,
//CLASE
angY = 0.0f,
angX = 0.0f;

//angulos de rotaciones
float angCod = 0.0f,
angPal = 0.0f,
angPul = 0.0f,
angHom = 0.0f;
void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	GLfloat vertices[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	unsigned int indices[] =	//I am not using index for this session
	{
		0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
	glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection


	//Use "projection" in order to change how we see the information
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	//projection = glm::ortho(-5.0f, 5.0f, -3.0f, 3.0f, 0.1f, 10.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));

	//CLASE AGREGAMOS EL ROTATE; (VIEW QUE AFECTA, GRADOS QUE ROTA EN RADIANES PERO CONVERTIMOS DESDE GRADOS, EL EJE EN EL QUE ROTA (X,Y,Z)) PARA ESTE CASO ROTAMOS EN Y
	view = glm::rotate(view, glm::radians(angX), glm::vec3(0, 1, 0));
	view = glm::rotate(view, glm::radians(angY), glm::vec3(1, 0, 0));
	view = glm::scale(view, glm::vec3(1.5f, 2.5f, 1.0f)); //CAMBIANDO EL TAMA�O DE LA CABEZA
	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	projectionShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO, CABEZA ROJA
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO

	//CUELLO
	model = glm::translate(model, glm::vec3(0, -0.75, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.5, 0.5, 1)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setVec3("color", glm::vec3(1.0f, 0.4f, 0.5f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//TORSO
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -3.5, 0)); //COMO LAS MATRICES SON ACUMULATIVAS, AL VOLVER A DECLARAR MODEL USARIAMOS LAS COORDENADAS ANTERIORES, POR LO QUE MEJOR EL PRIMER PAR�METRO REDIBUJAMOS LA FIGURA.
	modelTemp = model;
	model = glm::scale(model, glm::vec3(4.0, 5.0, 1.0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.0f, 0.0f, 1.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//CINTURON
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, -6.25, 0)); //COMO LAS MATRICES SON ACUMULATIVAS, AL VOLVER A DECLARAR MODEL USARIAMOS LAS COORDENADAS ANTERIORES, POR LO QUE MEJOR EL PRIMER PAR�METRO REDIBUJAMOS LA FIGURA.
	modelTemp = model;
	model = glm::scale(model, glm::vec3(4.0, 0.5, 1.0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(1.0f, 1.0f, 0.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//PIERNA DERECHA
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(1.5, -8.0, 0)); //COMO LAS MATRICES SON ACUMULATIVAS, AL VOLVER A DECLARAR MODEL USARIAMOS LAS COORDENADAS ANTERIORES, POR LO QUE MEJOR EL PRIMER PAR�METRO REDIBUJAMOS LA FIGURA.
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0, 3.0, 1.0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//ZAPATO DERECHO
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(2.75, -9.75, 0)); //COMO LAS MATRICES SON ACUMULATIVAS, AL VOLVER A DECLARAR MODEL USARIAMOS LAS COORDENADAS ANTERIORES, POR LO QUE MEJOR EL PRIMER PAR�METRO REDIBUJAMOS LA FIGURA.
	modelTemp = model;
	model = glm::scale(model, glm::vec3(4.0, 0.5, 1.0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.5f, 0.2f, 0.1f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//PIERNA IZQUIERDA
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-1.5, -8.0, 0)); //COMO LAS MATRICES SON ACUMULATIVAS, AL VOLVER A DECLARAR MODEL USARIAMOS LAS COORDENADAS ANTERIORES, POR LO QUE MEJOR EL PRIMER PAR�METRO REDIBUJAMOS LA FIGURA.
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0, 3.0, 1.0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//ZAPATO IZQUIERDO
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-2.75, -9.75, 0)); //COMO LAS MATRICES SON ACUMULATIVAS, AL VOLVER A DECLARAR MODEL USARIAMOS LAS COORDENADAS ANTERIORES, POR LO QUE MEJOR EL PRIMER PAR�METRO REDIBUJAMOS LA FIGURA.
	modelTemp = model;
	model = glm::scale(model, glm::vec3(4.0, 0.5, 1.0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.5f, 0.2f, 0.1f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//HOMBRO
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(2.5, -1.5, 0));
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("color", glm::vec3(1, 1, 0)); //CUBO INICIAL, HOMBRO
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;

	//BICEP
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	modelTemp = model; //Hacemos checkpoint de la posici�n de esta figura
	model = glm::scale(model, glm::vec3(2, 2, 2));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp; //Regresamos la escala a la original (de valor unitario)
	/*COMO LAS ESCALAS SON ACUMULATIVAS, HACEMOS UNA MATRIZ TEMPORAL PARA GUARDAR UNA ESCALA Y QUE PODAMOS TRABAJAR UNIFORMEMENTE
	CADA QUE HAGAMOS LA CREACION DE CADA CUBO (LINEAS 122, 123)
	DEBEMOS AGREGAR " model = modelTemp " PARA REGRESAR LA ESCALA A LO ESTABLECIDO EN LA MATRIZ TEMPORAL
	VIENE SIENDO ALGO PARECIDO A UN CHECKPOINT
	*/

	//ANTEBRAZO
	//COMO VAMOS A HACER UNA "ARTICULACI�N, NO NOS MOVEMOS AL CENTRO DE LA SIGUIENTE FIGURA, S�LO AL PUNTO DONDE QUIERO MI PIVOTE Y DE AH� AL CENTRO DE LA FIGURA
	//I.E.
	model = glm::translate(model, glm::vec3(1, 0, 0)); //Nos trasladamos al final del bicep de largo 2 (como partimos de la mitad, el final est� a 1) aqu� queremos el pivote
	model = glm::rotate(model, glm::radians(-angCod), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(1.5, 0, 0)); //Nos trasladamos al centro de la siguiente figura (antebrazo)
	modelTemp = model;
	model = glm::scale(model, glm::vec3(3, 1.5, 1.5)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//PALMA
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(angPal), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1, 1, 0.8)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.0f, 1.0f, 0.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO

	model = modelTemp;
	modelTemp2 = model; //Cuando acabe cada dedo, model = modelTemp2

	//PULGAR PTE1
	model = glm::translate(model, glm::vec3(-0.35, 0.5, 0));
	model = glm::rotate(model, glm::radians(angPul), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(1.0f, 0.0f, 1.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//PULGAR PTE2
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	model = glm::rotate(model, glm::radians(angPul*0.7f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(1.0f, 1.0f, 0.7f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO

	model = modelTemp2; //como acabamos el dedo, regresamos la referencia a la palma

	//INDICE PTE1
	model = glm::translate(model, glm::vec3(0.5, 0.38, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.5f, 0.4f, 1.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//INDICE PTE2
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.24, 0.27)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.4f, 0.3f, 0.9f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//INDICE PTE3
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.23, 0.24)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("aColor", glm::vec3(0.4f, 0.3f, 0.9f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO

	model = modelTemp2; //Regresamos a la referencia de la palma

	//MEDIO PTE1
	model = glm::translate(model, glm::vec3(0.5, 0.12, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(1.0f, 0.5f, 0.3f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//MEDIO PTE2
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.24, 0.27)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.9f, 0.4f, 0.2f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//MEDIO PTE3
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.23, 0.24)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.8f, 0.3f, 0.1f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO

	model = modelTemp2; //REGRESAMOS A LA PALMA

	//ANULAR PTE1
	model = glm::translate(model, glm::vec3(0.5, -0.12, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.5f, 0.7f, 1.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//ANULAR PTE2
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.24, 0.27)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.4f, 0.6f, 0.9f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//ANULAR PTE3
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.23, 0.24)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.3f, 0.5f, 0.8f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO

	model = modelTemp2; //REGRESAMOS A LA PALMA

	//ME�IQUE PTE1
	model = glm::translate(model, glm::vec3(0.5, -0.38, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.7f, 1.0f, 0.3f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//ME�IQUE PTE2
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.24, 0.27)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.6f, 0.9f, 0.2f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO
	model = modelTemp;

	//ME�IQUE PTE3
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angPul), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER ANTES DEL CHECKPOINT
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.23, 0.24)); //HACEMOS UN "MODELO" ESCALADO
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.5f, 0.8f, 0.1f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO

	//BRAZO IZQUIERDO
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-3.5, -1.35, 0)); //COMO LAS MATRICES SON ACUMULATIVAS, AL VOLVER A DECLARAR MODEL USARIAMOS LAS COORDENADAS ANTERIORES, POR LO QUE MEJOR EL PRIMER PAR�METRO REDIBUJAMOS LA FIGURA.
	model = glm::scale(model, glm::vec3(3.0, 0.7, 1.0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(0.0f, 1.0f, 0.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO

	//ANTEBRAZO DERECHO
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-4.75, -3.20, 0)); //COMO LAS MATRICES SON ACUMULATIVAS, AL VOLVER A DECLARAR MODEL USARIAMOS LAS COORDENADAS ANTERIORES, POR LO QUE MEJOR EL PRIMER PAR�METRO REDIBUJAMOS LA FIGURA.
	model = glm::scale(model, glm::vec3(0.5, 3.0, 1.0));
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("color", glm::vec3(1.0f, 0.0f, 1.0f)); //AQUI SE GENERA EL VECTOR EN RGB PARA PINTAR NUESTRO CUBO UNITARIO
	glDrawArrays(GL_QUADS, 0, 24); //DIBUJAMOS EL CUBO ESCALADO

	glBindVertexArray(0);
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 4", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Backgound color
		glClearColor(0.05f, 0.25f, 0.4f, 0.6f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi funci�n de dibujo
		display();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX -= 0.15f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX += 0.15f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movY -= 0.15f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movY += 0.15f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		movZ += 0.15f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movZ -= 0.15f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.6f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.6f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.6f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.6f;


	//Rotacion de hombro
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (angHom >= 0) {
				angHom -= 0.5f;
			}

		}
		else {
			if (angHom <= 90) {
				angHom += 0.5f;
			}
		}
	}

	//Rotacion del codo
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (angCod >= 0) {
				angCod -= 0.5f;
			}

		}
		else {
			if (angCod <= 90) {
				angCod += 0.5f;
			}
		}
	}

	//Rotacion de la mu�eca
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (angPal >= 0) {
				angPal -= 0.5f;
			}

		}
		else {
			if (angPal <= 90) {
				angPal += 0.5f;
			}
		}
	}

	//Rotacion del pulgar
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			if (angPul >= 0) {
				angPul -= 0.5f;
			}

		}
		else {
			if (angPul <= 90) {
				angPul += 0.5f;
			}
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}