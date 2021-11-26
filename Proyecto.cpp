/*-----------------------------------------------------------------------------------------------*/
/* ------------------------------------- Proyecto Final------------------------------------------*/
/*-------------------------------------    2022-1   ---------------------------------------------*/
/*------------- Alumno:Padilla Reyes Miguel Alejandro  No. Cuenta: 315116742 --------------------*/
/*------------- Alumno:Ramirez Flores Eslavica Monserrat  No. Cuenta: 315096093 -----------------*/
/*------------- Alumno:Valenzuela García de León Fernando Rodrigo No. Cuenta: 315031887----------*/

#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
//agregando libreria para audio
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;



#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor *monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 90.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -0.0f);
glm::vec3 lightPositionN(0.0f, -1.0f, -0.0f);
glm::vec3 lightPositionM(0.0f, -1.0f, 0.0f);
double myVariable = 0.0,
myVariableN = 0.0,
myVariableM = 0.0,
varLuzX = 0.0,
varLuzY = 0.0,
varLuzZ = 0.0;

// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movAuto_x = -200.0f,
		movAuto_y = 0.0f,
		movAuto_z = -200.0f,
		orienta = 90.0f,
		giroLlanta = 0.0f;
int		estado = 0;
bool	animacion = false,
		animacion1 = false,
		recorrido1 = true,
		recorrido2 = false,
		recorrido3 = false,
		recorrido4 = false,
		recorrido5 = false;

//ANIMACIONES PROYECTO
//Animación 1
bool anim1 = false,
a1rec0 = true,
a1rec1 = false,
a1rec2 = true,
a1rec3 = false,
a1rec4 = true,
a1rec5 = false,
a1rec6 = true,
a1rec7 = false,
a1rec8 = true,
a1rec9 = false;
float	C1TY = 0.0f,
C3TZ = 0.0f,
C7RZ = 0.0f,
C8RX = 0.0f,
C5EY = 0.0f;
//Animación 2
bool anim2 = false,
a2rec0 = true,
a2rec1 = false,
a2rec2 = false,
a2rec3 = false,
a2rec4 = false;
float TVEY = 0.0f,
TVEX = 0.0f,
SofaTX = 0.0f,
SofaRX = 0.0f;

//Animación 3
bool anim3 = false,
a3rec0 = true,
a3rec1 = false,
a3rec2 = false,
a3rec3 = false,
a3rec4 = false,
a3rec5 = false,
a3rec6 = false,
a3rec7 = false;
float Silla0TX = 0.0f,
Silla0TZ = 0.0f,
Silla1TX = 0.0f,
Silla1TZ = 0.0f,
Silla0RY = 0.0f,
Silla1RY = 0.0f;

//Animación 4
bool anim4 = false,
a4rec0 = true,
a4rec1 = false,
a4rec2 = false,
a4rec3 = false,
a4rec4 = false,
a4rec5 = false,
a4rec6 = false,
a4rec7 = false,
a4rec8 = false,
a4rec9 = false,
a4rec10 = false;
float PelucheTZ = 0.0f,
PelucheRY = 0.0f,
PelucheTY = 0.0f;

//Animación 5
bool anim5 = false,
a5rec0 = true,
a5rec1 = false,
a5rec2 = false,
a5rec3 = false,
a5rec4 = false,
a5rec5 = false,
a5rec6 = false,
a5rec7 = false,
a5rec8 = false,
a5rec9 = false,
a5rec10 = false;
float C6TX = 0.0f,
C2TX = 0.0f,
C6E = 0.0f,
C2E = 0.0f,
C6RY = 0.0f,
C2RY = 0.0f;

//Keyframes (Manipulación y dibujo)
float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f;

float	incX = 0.0f,
		incY = 0.0f,
		incZ = 0.0f;


		

#define MAX_FRAMES 12
int i_max_steps = 60;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 10;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{
	//printf("frameindex %d\n", FrameIndex);
	std::cout << "Frame Index = " << FrameIndex << std::endl;

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;



}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

}

void animate(void)//NUNCA HACER UN CICLO DENTRO DE OTRO CICLO EN ANIMACIÓN
{
	lightPosition.x = 50.0 * cos(myVariable);
	lightPosition.z = 50.0 * sin(myVariable);
	lightPosition.z = 5.0 * tan(myVariable);
	myVariable += 0.1;

	lightPositionN.z = 50.0*cos(myVariableN);
	myVariableN += 0.1;
	lightPositionM.x = 50.0*sin(myVariableN);
	myVariableM += 0.1;

	varLuzX = 50 * sin(varLuzX);
	varLuzX += 0.002;
	varLuzY = 50 * cos(varLuzY);
	varLuzY += 0.001;
	varLuzZ = 50 * cos(varLuzZ);
	varLuzZ += 0.0005;

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				std::cout << "Animation ended" << std::endl;
				//printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;

			i_curr_steps++;
		}
	}

	//ANIMACIÓN
	
	//Vehículo
	if (animacion1)
	{
		if (recorrido1)
		{
			movAuto_x -= 3.0f;
			giroLlanta -= 9.0f;
			orienta = -90.0f;
			if (movAuto_x <= -500.0f)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			movAuto_x -= 3.0f;
			giroLlanta -= 9.0f;
			orienta = -90.0f;
			if (movAuto_x <= -250.0f)
			{
				recorrido2 = false;
				recorrido3 = true;

			}
		}
		if (recorrido3)
		{
			movAuto_z += 3.0f;
			giroLlanta += 9.0f;
			orienta = 0.0f;
			if (movAuto_z >= 200.0f)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}
		if (recorrido4)
		{
			movAuto_x += 3.0f;
			giroLlanta += 9.0f;
			orienta = -270.0f;
			if (movAuto_x >= 0.0f)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		if (recorrido5) //hace la diagonal
		{
			movAuto_x += 1.25f;
			movAuto_z += 2.0f;
			giroLlanta += 9.0f;
			orienta = 32.0f;
			if (movAuto_z >= 200.0f && movAuto_x >= 0.0f)
			{
				recorrido5 = false;
				recorrido1 = true;
			}
		}
	}


	if (anim1) {
		if (a1rec0) {
			C1TY += 3.0f;
			if (C1TY >= 10.0f)
			{
				a1rec0 = false;
				a1rec1 = true;
			}
		}
		if (a1rec1) {
			C1TY -= 3.0f;
			if (C1TY <= -10.0f)
			{
				a1rec1 = false;
				a1rec0 = true;
			}
		}
		if (a1rec2) {
			C3TZ += 3.0f;
			if (C3TZ >= 10.0f)
			{
				a1rec2 = false;
				a1rec3 = true;
			}
		}
		if (a1rec3) {
			C3TZ -= 3.0f;
			if (C3TZ <= -10.0f)
			{
				a1rec3 = false;
				a1rec2 = true;
			}
		}
		if (a1rec4) {
			C7RZ += 6.0f;
			if (C7RZ >= 90.0f)
			{
				a1rec4 = false;
				a1rec5 = true;
			}
		}
		if (a1rec5) {
			C7RZ -= 6.0f;
			if (C7RZ <= -90.0f)
			{
				a1rec5 = false;
				a1rec4 = true;
			}
		}
		if (a1rec6) {
			C8RX += 6.0f;
			if (C8RX >= 90.0f)
			{
				a1rec6 = false;
				a1rec7 = true;
			}
		}
		if (a1rec7) {
			C8RX -= 6.0f;
			if (C8RX <= -90.0f)
			{
				a1rec7 = false;
				a1rec6 = true;
			}
		}
		if (a1rec8) {
			C5EY += 1.0f;
			if (C5EY >= 5.0f)
			{
				a1rec8 = false;
				a1rec9 = true;
			}
		}
		if (a1rec9) {
			C5EY -= 1.0f;
			if (C5EY <= -5.0f)
			{
				a1rec9 = false;
				a1rec8 = true;
			}
		}
	}
	if (anim2) {
		if (a2rec0) {
			TVEY += 1.0f;
			if (TVEY >= 5.0f)
			{
				a2rec0 = false;
				a2rec1 = true;
			}
		}
		if (a2rec1) {
			TVEX += 3.0f;
			if (TVEX >= 5.0f)
			{
				a2rec1 = false;
				a2rec2 = true;
			}
		}
		if (a2rec2) {
			SofaTX += 3.0f;
			SofaRX -= 25.7143f;
			if (SofaTX >= 21.0f && SofaRX <= -180.0f)
			{
				a2rec2 = false;
				a2rec3 = true;
			}
		}
		if (a2rec3) {
			TVEY -= 1.0f;
			TVEX -= 3.0f;
			if (TVEY <= -0.0f && TVEX <= -0.0f)
			{
				a2rec3 = false;
				a2rec4 = true;
			}
		}
		if (a2rec4) {
			SofaTX -= 3.0f;
			SofaRX += 25.7143f;
			if (SofaTX <= -0.0f && SofaRX >= 0.0f)
			{
				a2rec4 = false;
				a2rec0 = true;
			}
		}
	}
	if (anim3) {
		if (a3rec0) {
			Silla0TX -= 1.0f;
			Silla0TZ += 0.5f;
			if (Silla0TX <= -17.0f && Silla0TZ >= 9.0f)
			{
				a3rec0 = false;
				a3rec1 = true;
			}
		}
		if (a3rec1) {
			Silla1TX -= 1.0f;
			Silla1TZ -= 0.5f;
			if (Silla1TX <= -17.0f && Silla1TZ <= -9.0f)
			{
				a3rec1 = false;
				a3rec2 = true;
			}
		}
		if (a3rec2) {
			Silla0RY -= 20.0f;
			if (Silla0RY <= -180.0f)
			{
				a3rec2 = false;
				a3rec3 = true;
			}
		}
		if (a3rec3) {
			Silla1RY += 20.0f;
			if (Silla1RY >= 180.0f)
			{
				a3rec3 = false;
				a3rec4 = true;
			}
		}
		
		if (a3rec4) {
			Silla0TX += 1.0f;
			Silla0TZ -= 0.5f;
			if (Silla0TX >= 0.0f && Silla0TZ <= 0.0f)
			{
				a3rec4 = false;
				a3rec5 = true;
			}
		}
		if (a3rec5) {
			Silla1TX += 1.0f;
			Silla1TZ += 0.5f;
			if (Silla1TX >= 0.0f && Silla1TZ >= 0.0f)
			{
				a3rec5 = false;
				a3rec6 = true;
			}
		}
		
		if (a3rec6) {
			Silla0RY += 20.0f;
			if (Silla0RY >= 0.0f)
			{
				a3rec6 = false;
				a3rec7 = true;
			}
		}
		if (a3rec7) {
			Silla1RY -= 20.0f;
			if (Silla1RY <= 0.0f)
			{
				a3rec7 = false;
				a3rec0 = true;
			}
		}
	}
	if (anim4) {
		if (a4rec0) {
			PelucheTZ += 3.0f;
			if (PelucheTZ >= 60.0f)
			{
				a4rec0 = false;
				a4rec1 = true;
			}
		}
		if (a4rec1) {
			PelucheRY += 10.0f;
			if (PelucheRY >= 90.0f)
			{
				a4rec1 = false;
				a4rec2 = true;
			}
		}
		if (a4rec2) {
			PelucheTY += 1.0f;
			if (PelucheTY >= 18.0f)
			{
				a4rec2 = false;
				a4rec3 = true;
			}
		}
		if (a4rec3) {
			PelucheRY += 1.0f;
			PelucheTY -= 0.05f;
			if (PelucheRY >= 100.0f)
			{
				a4rec3 = false;
				a4rec4 = true;
			}
		}
		if (a4rec4) {
			PelucheRY += 10.0f;
			PelucheTY -= 0.15f;
			if (PelucheRY >= 180.0f)
			{
				a4rec4 = false;
				a4rec5 = true;
			}
		}
		if (a4rec5) {
			PelucheRY += 35.0f;
			PelucheTY -= 0.2f;
			if (PelucheRY >= 450.0f)
			{
				a4rec5 = false;
				a4rec6 = true;
			}
		}
		if (a4rec6) {
			PelucheRY += 45.0f;
			PelucheTY += 0.75f;
			if (PelucheRY >= 1890.0f)
			{
				a4rec6 = false;
				a4rec7 = true;
			}
		}
		if (a4rec7) {
			PelucheRY -= 90.0f;
			if (PelucheRY <= -0.0f)
			{
				a4rec7 = false;
				a4rec8 = true;
			}
		}
		if (a4rec8) {
			PelucheTY -= 1.0f;
			if (PelucheTY <= 0.0f)
			{
				a4rec8 = false;
				a4rec9 = true;
			}
		}
		if (a4rec9) {
			PelucheRY += 10.0f;
			if (PelucheRY >= 0.0f)
			{
				a4rec9 = false;
				a4rec10 = true;
			}
		}
		if (a4rec10) {
			PelucheTZ -= 3.0f;
			if (PelucheTZ <= -00.0f)
			{
				a4rec10 = false;
				a4rec0 = true;
			}
		}
	}
	if (anim5) {
		if (a5rec0) {
			C6E -= 1.0f;
			C2E -= 1.0f;
			if (C6E <= -3.0f)
			{
				a5rec0 = false;
				a5rec1 = true;
			}
		}
		if (a5rec1) {
			C6TX -= 5.0f;
			if (C6TX <= -240.0f)
			{
				a5rec1 = false;
				a5rec2 = true;
			}
		}
		if (a5rec2) {
			C6RY -= 10.0f;
			if (C6RY <= -180.0f)
			{
				a5rec2 = false;
				a5rec3 = true;
			}
		}
		if (a5rec3) {
			C2RY -= 10.0f;
			if (C2RY <= -180.0f)
			{
				a5rec3 = false;
				a5rec4 = true;
			}
		}
		if (a5rec4) {
			C2TX += 5.0f;
			if (C2TX >= 240.0f)
			{
				a5rec4 = false;
				a5rec5 = true;
			}
		}
		if (a5rec5) {
			C6E += 1.0f;
			C2E += 1.0f;
			if (C6E >= 0.0f)
			{
				a5rec5 = false;
				a5rec6 = true;
			}
		}
		if (a5rec6) {
			C2TX += 5.0f;
			if (C2TX >= 0.0f)
			{
				a5rec6 = false;
				a5rec7 = true;
			}
		}
		if (a5rec7) {
			C6TX += 5.0f;
			if (C6TX >= 0.0f)
			{
				a5rec7 = false;
				a5rec8 = true;
			}
		}
		if (a5rec8) {
			C6RY += 10.0f;
			if (C6RY >= 0.0f)
			{
				a5rec8 = false;
				a5rec9 = true;
			}
		}
		if (a5rec9) {
			C2RY += 10.0f;
			if (C2RY >= 0.0f)
			{
				a5rec9 = false;
				a5rec0 = true;
			}
		}
	}

}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	PlaySound(TEXT("musica_fondo.wav"), NULL, SND_ASYNC);
	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	// -----------
	Model piso("resources/objects/piso/piso.obj");
	Model casa("resources/objects/casaModelado/casaModelado.obj");
	Model carro("resources/objects/lambo/carroceria.obj");
	Model llanta("resources/objects/lambo/Wheel.obj");
	//Model Gato("resources/objects/CAT/Gato.obj");
	Model pCama("resources/objects/pCama/Cama.obj");
	Model pHorno("resources/objects/pHorno/untitled.obj");
	Model pLavabo("resources/objects/pLavabo/untitled.obj");
	Model pLavaboBanio0("resources/objects/pLavaboBanio/untitled.obj");
	Model pLavaboBanio1("resources/objects/pLavaboBanio/untitled.obj");
	Model pLitera("resources/objects/pLitera/Litera.obj");
	Model pMesa("resources/objects/pMesa/untitled.obj");
	Model pMesaAfuera("resources/objects/pMesaAfuera/untitled.obj");
	Model pSofa("resources/objects/pSofa/untitled.obj");
	Model pToilet0("resources/objects/pToilet/untitled.obj");
	Model pToilet1("resources/objects/pToilet/untitled.obj");
	Model pArmario0("resources/objects/pArmario2/untitled.obj");
	Model pArmario1("resources/objects/pArmario2/untitled.obj");
	Model pBote("resources/objects/pBote/untitled.obj");
	Model pBoteBasura0("resources/objects/pBoteBasura/untitled.obj");
	Model pBoteBasura1("resources/objects/pBoteBasura/untitled.obj");
	Model pBoteBasura2("resources/objects/pBoteBasura/untitled.obj");
	Model pConsola("resources/objects/pJuego/Aconsole.obj");
	Model pControl("resources/objects/pJuego/joystick2.obj");
	Model pPeluche("resources/objects/pPeluche/untitled.obj");
	Model pTV("resources/objects/pTV/untitled.obj");
	Model pTina0("resources/objects/pTina/untitled.obj");
	Model pTina1("resources/objects/pTina/untitled.obj");
	Model pSilla0("resources/objects/pSilla1/untitled.obj");
	Model pSilla1("resources/objects/pSilla1/untitled.obj");
	Model C1("resources/objects/C1/abel.obj");
	Model C2("resources/objects/C2/brunoydasha.obj");
	Model C3("resources/objects/C3/sandibel.obj");
	Model C4("resources/objects/C4/Stormy.obj");
	Model C5("resources/objects/C5/HaidaHappy.obj");
	Model C6("resources/objects/C6/Kaito.obj");
	Model C7("resources/objects/C7/lm.obj");
	Model C8("resources/objects/C8/magumin.obj");
	Model pelota("resources/objects/Pelota/Pelota.obj");

	ModelAnim animacionPersonaje("resources/objects/Personaje1/PersonajeBrazo.dae");
	animacionPersonaje.initShaders(animShader.ID);

	ModelAnim ninja("resources/objects/ZombieWalk/ZombieWalk.dae");
	ninja.initShaders(animShader.ID);

	//Inicialización de KeyFrames
	/*for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;

	}*/

	KeyFrame[0].posX = 0.0f;
	KeyFrame[0].posY = 0.0f;
	KeyFrame[0].posZ = 0.0f;



	KeyFrame[1].posX = 10.0f;
	KeyFrame[1].posY = 20.0f;
	KeyFrame[1].posZ = 0.0f;


	KeyFrame[2].posX = 20.0f;
	KeyFrame[2].posY = 30.0f;
	KeyFrame[2].posZ = 0.0f;


	KeyFrame[3].posX = 30.0f;
	KeyFrame[3].posY = 20.0f;
	KeyFrame[3].posZ = 0.0f;


	KeyFrame[4].posX = 40.0f;
	KeyFrame[4].posY = 0.0f;
	KeyFrame[4].posZ = 0.0f;


	KeyFrame[5].posX = 50.0f;
	KeyFrame[5].posY = 20.0f;
	KeyFrame[5].posZ = 0.0f;



	KeyFrame[6].posX = 60.0f;
	KeyFrame[6].posY = 20.0f;
	KeyFrame[6].posZ = 0.0f;


	KeyFrame[7].posX = 70.0f;
	KeyFrame[7].posY = 30.0f;
	KeyFrame[7].posZ = 0.0f;

	KeyFrame[8].posX = 80.0f;
	KeyFrame[8].posY = 20.0f;
	KeyFrame[8].posZ = 0.0f;


	KeyFrame[9].posX = 90.0f;
	KeyFrame[9].posY = 0.0f;
	KeyFrame[9].posZ = 0.0f;

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);
		
		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPositionN);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.0000009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.00000032f);

		staticShader.setVec3("pointLight[1].position", lightPositionM);
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 0.08f);
		staticShader.setFloat("pointLight[1].linear", 0.0000009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.00000032f);

		staticShader.setVec3("pointLight[2].position", lightPosition);
		staticShader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[2].diffuse", glm::vec3(0.0*varLuzX, 0.0*varLuzY, 0.0*varLuzZ));
		staticShader.setVec3("pointLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[2].constant", 0.1f);
		staticShader.setFloat("pointLight[2].linear", 0.09f);
		staticShader.setFloat("pointLight[2].quadratic", 0.00009f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);
		

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 250.0f));
		model = glm::scale(model, glm::vec3(20.0f));
		staticShader.setMat4("model", model);
		casa.Draw(staticShader);

		/*
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(70.0f, 0.0f, -70.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f));
		staticShader.setMat4("model", model);
		Gato.Draw(staticShader);
		*/

		model = glm::translate(glm::mat4(1.0f), glm::vec3(70.0f, 9.0f, 152.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.13f));
		staticShader.setMat4("model", model);
		pCama.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-50.0f, 0.5f, 62.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(14.005f));
		staticShader.setMat4("model", model);
		pHorno.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-32.0f, 2.0f, 59.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f));
		staticShader.setMat4("model", model);
		pLavabo.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(60.0f, 3.0f, 88.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f));
		staticShader.setMat4("model", model);
		pLavaboBanio0.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-60.0f, 52.0f, 80.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f));
		staticShader.setMat4("model", model);
		pLavaboBanio1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 48.0f, 88.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.18f));
		staticShader.setMat4("model", model);
		pLitera.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-110.0f, 1.0f, 120.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.22f));
		staticShader.setMat4("model", model);
		pMesa.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-70.0f, 0.0f, -20.0f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.13f));
		staticShader.setMat4("model", model);
		pMesaAfuera.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-80.0f+SofaTX, -1.0f, 200.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(SofaRX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.018f));
		staticShader.setMat4("model", model);
		pSofa.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(112.5f, 6.0f, 120.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.6f));
		staticShader.setMat4("model", model);
		pToilet0.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(16.0f, 54.0f, 83.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.6f));
		staticShader.setMat4("model", model);
		pToilet1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 0.0f, 138.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f));
		staticShader.setMat4("model", model);
		pArmario0.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(90.0f, 0.0f, 138.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f));
		staticShader.setMat4("model", model);
		pArmario1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 1.0f, 80.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45f));
		staticShader.setMat4("model", model);
		pBote.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 0.0f, 300.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.003f));
		staticShader.setMat4("model", model);
		pBoteBasura0.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(64.0f, 1.0f, 81.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0008f));
		staticShader.setMat4("model", model);
		pBoteBasura1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-60.0f, 49.0f, 70.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.0008f));
		staticShader.setMat4("model", model);
		pBoteBasura2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-110.0f, 0.0f, 200.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		pConsola.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-105.0f, 0.0f, 200.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		pControl.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-120.0f, 48.0f+PelucheTY, 90.0f+PelucheTZ));
		model = glm::rotate(model, glm::radians(PelucheRY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(16.0f));
		staticShader.setMat4("model", model);
		pPeluche.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-128.0f, 0.0f, 200.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.5f+TVEX, 3.5f+TVEY, 3.5f));
		staticShader.setMat4("model", model);
		pTV.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(89.0f, 0.0f, 80.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.16f));
		staticShader.setMat4("model", model);
		pTina0.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0f, 48.0f, 66.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.16f));
		staticShader.setMat4("model", model);
		pTina1.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f+Silla0TX, 1.0f, 115.0f+Silla0TZ));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(Silla0RY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.14f));
		staticShader.setMat4("model", model);
		pSilla0.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f+Silla1TX, 1.0f, 125.0f+Silla1TZ));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(Silla1RY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.14f));
		staticShader.setMat4("model", model);
		pSilla1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 20.0f+C1TY, 205.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		staticShader.setMat4("model", model);
		C1.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 20.0f, 175.0f+C3TZ));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		staticShader.setMat4("model", model);
		C3.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-140.0f, 20.0f, 135.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f+ C5EY, 2.0f));
		staticShader.setMat4("model", model);
		C5.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-135.0f, 20.0f, 120.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(C7RZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		staticShader.setMat4("model", model);
		C7.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-140.0f, 20.0f, 75.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		staticShader.setMat4("model", model);
		C8.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-130.0f+C2TX, 60.0f, 220.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(C2RY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f+C2E));
		staticShader.setMat4("model", model);
		C2.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-130.0f, 60.0f, 175.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		staticShader.setMat4("model", model);
		C4.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(110.0f + C6TX, 60.0f, 220.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(C6RY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f+C6E));
		staticShader.setMat4("model", model);
		C6.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-170.0f, 3.0f, -30.0f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ)); //************************
		model = glm::scale(model, glm::vec3(5.45f));
		staticShader.setMat4("model", model);
		pelota.Draw(staticShader);


		// -------------------------------------------------------------------------------------------------------------------------
		// Carro
		// -------------------------------------------------------------------------------------------------------------------------
		
		model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(15.0f + movAuto_x, -1.0f+movAuto_y, movAuto_z));
		tmp = model = glm::rotate(model, glm::radians(orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		carro.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, 12.9f));
		model = glm::rotate(model, glm::radians(giroLlanta), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq delantera

		model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, 12.9f));
		model = glm::rotate(model, glm::radians(giroLlanta), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der delantera

		model = glm::translate(tmp, glm::vec3(-8.5f, 2.5f, -14.5f));
		model = glm::rotate(model, glm::radians(giroLlanta), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Der trasera

		model = glm::translate(tmp, glm::vec3(8.5f, 2.5f, -14.5f));
		model = glm::rotate(model, glm::radians(giroLlanta), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		staticShader.setMat4("model", model);
		llanta.Draw(staticShader);	//Izq trase
		
		//---------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//To Configure Model

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		anim1 ^= true; //XOR cambio de falso a verdadero
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		anim2 ^= true; //XOR cambio de falso a verdadero
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		anim3 ^= true; //XOR cambio de falso a verdadero
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		anim4 ^= true; //XOR cambio de falso a verdadero
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		anim5 ^= true; //XOR cambio de falso a verdadero
	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		anim1 = false;
		a1rec0 = true;
		a1rec1 = false;
		a1rec2 = true;
		a1rec3 = false;
		a1rec4 = true;
		a1rec5 = false;
		a1rec6 = true;
		a1rec7 = false;
		a1rec8 = true;
		a1rec9 = false;
		C1TY = 0.0f;
		C3TZ = 0.0f;
		C7RZ = 0.0f;
		C8RX = 0.0f;
		C5EY = 0.0f;

		anim2 = false;
		a2rec0 = true;
		a2rec1 = false;
		a2rec2 = false;
		a2rec3 = false;
		a2rec4 = false;
		TVEY = 0.0f;
		TVEX = 0.0f;
		SofaTX = 0.0f;
		SofaRX = 0.0f;

		anim3 = false;
		a3rec0 = true;
		a3rec1 = false;
		a3rec2 = false;
		a3rec3 = false;
		a3rec4 = false;
		a3rec5 = false;
		a3rec6 = false;
		a3rec7 = false;
		Silla0TX = 0.0f;
		Silla0TZ = 0.0f;
		Silla1TX = 0.0f;
		Silla1TZ = 0.0f;
		Silla0RY = 0.0f;
		Silla1RY = 0.0f;

		anim4 = false;
		a4rec0 = true;
		a4rec1 = false;
		a4rec2 = false;
		a4rec3 = false;
		a4rec4 = false;
		a4rec5 = false;
		a4rec6 = false;
		a4rec7 = false;
		a4rec8 = false;
		a4rec9 = false;
		a4rec10 = false;
		PelucheTZ = 0.0;
		PelucheRY = 0.0;
		PelucheTY = 0.0;

		anim5 = false;
		a5rec0 = true;
		a5rec1 = false;
		a5rec2 = false;
		a5rec3 = false;
		a5rec4 = false;
		a5rec5 = false;
		a5rec6 = false;
		a5rec7 = false;
		a5rec8 = false;
		a5rec9 = false;
		a5rec10 = false;
		C6TX = 0.0f;
		C2TX = 0.0f;
		C6E = 0.0f;
		C2E = 0.0f;
		C6RY = 0.0f;
		C2RY = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		posZ++;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		posZ--;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		posX--;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		posX++;
		//lightPosition.x--;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		lightDirection.x+=1.0f;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		lightDirection.x-=1.0f;

	//Car animation
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion1 ^= true; //XOR cambio de falso a verdadero
	if (key == GLFW_KEY_L && action == GLFW_PRESS && movAuto_z >= 70.0f) {
		movAuto_z = 0.0f;
		movAuto_y = 0.0f;
	}
	//To play KeyFrame animation 
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			std::cout << "Play animation" << std::endl;
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			std::cout << "Not enough Key Frames" << std::endl;
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}