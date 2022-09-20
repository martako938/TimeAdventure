//--------------------------UNIVERIDAD NACIONAL AUTÓNOMA DE MÉXICO----------------------------------------- //
//--------------------------------INGENIERÍA EN COMPUTACIÓN------------------------------------------------//
//----------------------------------COMPUTACIÓN GRÁFICA---------------------------------------------------//
//---------------------------------  Semestre 2016-1 ----------------------------------------------------//
//------------------------------------PROYECTO FINAL----------------------------------------------------//
//-----------------------------------------------------------------------------------------------------//
// -------------------------ALUMNOS: CABRERA LÓPEZ BRAYAN RAÚL-----------------------------------------//
//----------------------------------GARRIDO GONZÁLEZ INGRID NOEMI-------------------------------------//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito
CFiguras miFigura;


//NEW// Keyframes
float posX =0, posY = 2.5, posZ =-3.5, rotRodIzq = 0;
float giroMonito = 0;
float giroBrazo = 0;

float var = 0.0;
float bmoangle=0.0;
float bmoangle2=0.0;
float bmoangle3=0.0;
float giro = 0.0;

#define MAX_FRAMES 90
int i_max_steps = 4;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float rotInc;
	float giroMonito;
	float giroMonitoInc;

	float giroBrazo;
	float giroBrazoInc;


	//BMO
float bmoangle;
float inc1;
float bmoangle2;
float inc2;
float bmoangle3;
float inc3;
float angleY;
float incangleY;
float transX;
float transY;
float transZ;
float incX;		//Variable para IncrementoX
float incY;		//Variable para IncrementoY
float incZ;

	
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex=5;			//introducir datos
bool play=false;
int playIndex=0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame=0,time,timebase=0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font=(int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };	// Light Position



CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01

//BMO
CTexture cuerpoBMO;
CTexture letrasBMO;
CTexture atrasBMO;

//ICE
CTexture nieve;
CTexture nievep;
CTexture nievem;
CTexture lluvian;

//cielos
CTexture icesky;
CTexture skypasto;
CTexture dulcesky;
CTexture otrosky;

//Dulce reino
CTexture ventana_1;
CTexture pared_1;
CTexture helado_1;
CTexture piso_d;
CTexture refresco;

//Campo
CTexture piso_v;


CTexture tree;
CTexture edificio;

CFiguras cubo;
CFiguras sky;

//END NEW//////////////////////////////////////////


CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito

//hora de aventura
CFiguras bmo; //cuerpo BMO
CFiguras montana;
CFiguras arbolm;
CFiguras tronco;

//Figuras de 3D Studio
CModel kit;
CModel llanta;
CModel casita;
CModel oldhouse;
CModel carro;

//modelos 3ds
CModel candy;
CModel chocolate;


//Animación del coche
float angRot = 0.0;
float movKitX = 0.0;
float movKitZ = 0.0;
float movKitXFinal = 0.0;
float movKitZFinal = 0.0;
float movKitXInc = 0.0;
float movKitZInc = 0.0;
float rotKit = 0.0;
float rotTires = 0.0;
bool g_fanimacion = false;
bool g_avanza = true;

bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;


//ANIMACIÓN BMO
float transZ = 0.0f;
float transX = 0.0f;
float transY = 0.0f;
float angleY = 0.0f;
float angleX = 0.0f;

int timer = 0;


void pigu ()

{

	//PINGU
  glPushMatrix();
  
  glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0, 0,-25);
		glRotatef(180, 0, 1.0, 0.0);
		glScalef(0.2, 0.2, 0.2);

	glPushMatrix();
		//glScalef(5.0, 8.0, 1.0);
		glColor3f(0.4, 0.7450, 0.6509);
		bmo.prismaBMO(6.0, 5.0, 4.0, cuerpoBMO.GLindex,letrasBMO.GLindex,atrasBMO.GLindex,letrasBMO.GLindex);// Cuerpo
	glPopMatrix();
	

		//Brazo D
	glPushMatrix();
			glTranslatef(4.0, -1.0, 0.0);
			glColor3f(0.0, 0.0,0.0);
			bmo.prisma(0.75, 0.75, 0.75, 0); //brazo D	
	glPopMatrix();

		//Brazo I
		glPushMatrix();
			glTranslatef(4.0, -1.0, 0.0);
			glColor3f(0.0, 0.0,0.0);
			bmo.prisma(0.75, 0.75, 0.75, 0); //brazo D	
	glPopMatrix();

		//Pie I
		glPushMatrix();
			glTranslatef(-2.0, -4.5, 0.0);
			glColor3f(1.0, 1.0, 0.0);
			bmo.prisma(3.0, 0.7, 0.75, 0); //pie I
			glPushMatrix();
			glTranslatef(0.0, -1.125, 0.75);
			glColor3f(1.0, 1.0, 0.0);
			bmo.prisma(0.75, 0.75, 2.0, 0);//piecito
			glPopMatrix();
		glPopMatrix();

		//Pie D
		glPushMatrix();
			glTranslatef(2.0, -4.5, 0.0);
			//glScalef(1.0, 4.0, 1.0);
			//glRotatef(180,0.0,1.0, 0.0);
			glColor3f(1.0, 1.0, 0.0);
			bmo.prisma(3.0, 0.75, 0.75, 0); //pie D
			glPushMatrix();
			glTranslatef(0.0, -1.125, 0.75);
			glColor3f(1.0, 1.0, 0.0);
			bmo.prisma(0.75, 0.75, 2.0, 0);//piecito
			glPopMatrix();
		glPopMatrix();

glPopMatrix(); //FIN pingu


}

void pino ()
{
	glEnable(GL_COLOR_MATERIAL);
	glPushMatrix();//pino 1
			//glTranslatef(-25,0, -25);
			glPushMatrix();
				glTranslatef(0,3,0);
					glPushMatrix();
						glTranslatef(0,3,0);
						glPushMatrix();
							glTranslatef(0,3,0);
							glColor3f(0, 0.533, 0.082);
							arbolm.cono(5,1,10,0);
						glPopMatrix();
					glColor3f(0, 0.533, 0.082);
					arbolm.cono(5,3,10,0);
					glPopMatrix();
			glColor3f(0, 0.533, 0.082);
			arbolm.cono(5,4,10,0);
			glPopMatrix();
			glColor3f(0.274, 0.184, 0.113);
		arbolm.cilindro(1,6,10,0);
		glColor3f(1.0, 1.0, 1.0);
		glPopMatrix();


		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_COLOR_MATERIAL);
}
void barda_a(){

glPushMatrix(); // inicio barda
				
				glPushMatrix(); //plano a
					glTranslatef(0, -0.5, 20);
					glRotatef(11,0.0,1.0, 0.0);   //gira 11 grados el primer plano que está a la derecha 
					//glBindTexture(GL_TEXTURE_2D, lluvian.GLindex);
					glBegin(GL_QUADS);
						glColor3f(1.0, 1.0, 1.0);
						glNormal3f(0.0, 0.0, 1.0);
						glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
						glTexCoord2f(1.0, 0.0); glVertex3f(7.8, 0, 0.0);
						glTexCoord2f(1.0, 1.0); glVertex3f(7.8, 4, 0.0);
						glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 4, 0.0);
					glEnd();
					glPushMatrix(); //plano b
						glTranslatef(7.8, 0, 0);
						glRotatef(23,0.0,1.0, 0.0);   //gira 11 grados el primer plano 
						//glBindTexture(GL_TEXTURE_2D, lluvian.GLindex);
						glBegin(GL_QUADS);
							glColor3f(1.0, 1.0, 1.0);
							glNormal3f(0.0, 0.0, 1.0);
							glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
							glTexCoord2f(1.0, 0.0); glVertex3f(7.8, 0, 0.0);
							glTexCoord2f(1.0, 1.0); glVertex3f(7.8, 4, 0.0);
							glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 4, 0.0);
						glEnd();
						glPushMatrix(); //plano c
							glTranslatef(7.8, 0, 0);
							glRotatef(22,0.0,1.0, 0.0);   //gira 11 grados el primer plano 
							//glBindTexture(GL_TEXTURE_2D, lluvian.GLindex);
							glBegin(GL_QUADS);
								glColor3f(1.0, 1.0, 1.0);
								glNormal3f(0.0, 0.0, 1.0);
								glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
								glTexCoord2f(1.0, 0.0); glVertex3f(7.8, 0, 0.0);
								glTexCoord2f(1.0, 1.0); glVertex3f(7.8, 4, 0.0);
								glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 4, 0.0);
							glEnd();
								glPushMatrix(); //plano d
								glTranslatef(7.8, 0, 0);
								glRotatef(22.5,0.0,1.0, 0.0);   //gira 11 grados el primer plano 
								//glBindTexture(GL_TEXTURE_2D, lluvian.GLindex);
								glBegin(GL_QUADS);
									glColor3f(1.0, 1.0, 1.0);
									glNormal3f(0.0, 0.0, 1.0);
									glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
									glTexCoord2f(1.0, 0.0); glVertex3f(7.8, 0, 0.0);
									glTexCoord2f(1.0, 1.0); glVertex3f(7.8, 4, 0.0);
									glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 4, 0.0);
								glEnd();
							glPopMatrix();//fin plano d
						glPopMatrix();//fin plano c
					glPopMatrix(); //fin plano b
				glPopMatrix();// fin plano a

			glPopMatrix();//fin barda


}
void barda_completa(){
			glPushMatrix();
				barda_a();
				glPushMatrix();
					glRotatef(90,0.0,1.0, 0.0);
					glTranslatef(0.0, 0.0, 0.0);
					barda_a();
				glPopMatrix();
				glPushMatrix();
					glRotatef(180,0.0,1.0, 0.0);
					glTranslatef(0.0, 0.0, 0.0);
					barda_a();
				glPopMatrix();
				glPushMatrix();
					glRotatef(270,0.0,1.0, 0.0);
					glTranslatef(0.0, 0.0, 0.0);
					barda_a();
				glPopMatrix();
			glPopMatrix();
}
void seccion_rio(){

glPushMatrix(); // inicio rio
				
				glPushMatrix(); //plano a
					glTranslatef(0, -0.5, 20);
					glRotatef(11,0.0,1.0, 0.0);   //gira 11 grados el primer plano que está a la derecha 

					glDisable(GL_LIGHTING);
					glEnable(GL_BLEND); ///activa transparecia
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//transparencia
					glBindTexture(GL_TEXTURE_2D, refresco.GLindex);
					glBegin(GL_QUADS);
						glColor3f(1.0, 1.0, 1.0);
						glNormal3f(0.0, 0.0, 1.0);

						glTexCoord2f(0.0 - var, 0.0 ); glVertex3f(0.0, 0.0, 0.0);
						glTexCoord2f(1.0 - var, 0.0 ); glVertex3f(7.8, 0, 0.0);
						glTexCoord2f(1.0 - var, 1.0 ); glVertex3f(7.8, 4, 0.0);
						glTexCoord2f(0.0 - var, 1.0 ); glVertex3f(0.0, 4, 0.0);
					glEnd();
					glPushMatrix(); //plano b
						glTranslatef(7.8, 0, 0);
						glRotatef(23,0.0,1.0, 0.0);   //gira 11 grados el primer plano 
						
						glBegin(GL_QUADS);
							
							glNormal3f(0.0, 0.0, 1.0);
							glTexCoord2f(0.0 - var, 0.0 ); glVertex3f(0.0, 0.0, 0.0);
							glTexCoord2f(1.0 - var, 0.0 ); glVertex3f(7.8, 0, 0.0);
							glTexCoord2f(1.0 - var, 1.0 ); glVertex3f(7.8, 4, 0.0);
							glTexCoord2f(0.0 - var, 1.0 ); glVertex3f(0.0, 4, 0.0);
						glEnd();
						glPushMatrix(); //plano c
							glTranslatef(7.8, 0, 0);
							glRotatef(22,0.0,1.0, 0.0);   //gira 11 grados el primer plano 
							
							glBegin(GL_QUADS);
								
								glNormal3f(0.0, 0.0, 1.0);
								glTexCoord2f(0.0 - var, 0.0 ); glVertex3f(0.0, 0.0, 0.0);
								glTexCoord2f(1.0 - var, 0.0 ); glVertex3f(7.8, 0, 0.0);
								glTexCoord2f(1.0 - var, 1.0 ); glVertex3f(7.8, 4, 0.0);
								glTexCoord2f(0.0 - var, 1.0 ); glVertex3f(0.0, 4, 0.0);
							glEnd();
								glPushMatrix(); //plano d
								glTranslatef(7.8, 0, 0);
								glRotatef(22.5,0.0,1.0, 0.0);   //gira 11 grados el primer plano 
								
								glBegin(GL_QUADS);
									
									glNormal3f(0.0, 0.0, 1.0);
									glTexCoord2f(0.0 - var, 0.0 ); glVertex3f(0.0, 0.0, 0.0);
									glTexCoord2f(1.0 - var, 0.0 ); glVertex3f(7.8, 0, 0.0);
									glTexCoord2f(1.0 - var, 1.0 ); glVertex3f(7.8, 4, 0.0);
									glTexCoord2f(0.0 - var, 1.0 ); glVertex3f(0.0, 4, 0.0);
								glEnd();
							glPopMatrix();//fin plano d
						glPopMatrix();//fin plano c
					glPopMatrix(); //fin plano b
				glPopMatrix();// fin plano a
				glDisable(GL_BLEND); ///desactiva transparecia
				glEnable(GL_LIGHTING);
			glPopMatrix();//fin barda


}
void rio_comp(){
			glPushMatrix();
				seccion_rio();
				glPushMatrix();
					glRotatef(90,0.0,1.0, 0.0);
					glTranslatef(0.0, 0.0, 0.0);
					seccion_rio();
				glPopMatrix();
			glPopMatrix();
}
void castillo(){

glPushMatrix(); //GRAN PUSH

		glPushMatrix(); //Inicio castillo
			glTranslatef(25.0, -0.5, 0.0);
			//glScalef(1.0, 4.0, 1.0);
			//glRotatef(180,0.0,1.0, 0.0);
			glColor3f(1, 1, 1);
			miFigura.cilindro(2.0,24.0,20,ventana_1.GLindex);  //cilindro principal

			//Secciones de la barda
			barda_completa();

			glPushMatrix(); //rio
				glPushMatrix();
				glTranslatef(0.0, 8.0, 0.0);
				glRotatef(90,0.0,0.0, 1.0);
				glRotatef(45,1.0,0.0, 0.0);
				glScalef(0.5, 0.55, 0.5);
				rio_comp();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.0, 8.0, 0.0);
				glRotatef(90,0.0,0.0, 1.0);
				glRotatef(115,1.0,0.0, 0.0);
				glScalef(0.5, 0.55, 0.5);
				rio_comp();
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();   //base 1
				glColor3f(1.0,1.0,1.0);
				miFigura.cilindro(6,16.0,20,pared_1.GLindex);
			glPopMatrix();
			glPushMatrix();   //base2
				glColor3f(1.0,1.0,1.0);
				miFigura.cilindro(10,8.0,20,pared_1.GLindex);
				glPushMatrix();   //columna1
					glTranslatef(0.0, 0.0, 15.0);
					glColor3f(1.0,1.0,1.0);
					miFigura.cilindro(1,8.0,20,pared_1.GLindex);
					glPushMatrix();			//esfera1
						glTranslatef(0.0, 8.0, 0.0);
						miFigura.esfera(1.0,20,20,pared_1.GLindex);
					glPopMatrix();
					glRotatef(90,0.0,1.0, 0.0);
					glPushMatrix();   //columnahor
						glTranslatef(4.0, 8.0, 0.0);
						glRotatef(90,0.0,0.0, 1.0);
						miFigura.cilindro(1,4.0,20,pared_1.GLindex);
						glPushMatrix();  //esfera2
							miFigura.esfera(1.0,20,20,pared_1.GLindex);
							glRotatef(-90,0.0,0.0, 1.0);
							miFigura.cilindro(1,4.0,20,pared_1.GLindex);
							glTranslatef(0.0, 4.0, 0.0);
							miFigura.cono(3.0,1.5,10,helado_1.GLindex);  //cono superior
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
				glPushMatrix();   //columna2
					glTranslatef(0.0, 0.0, -15.0);
					glColor3f(1.0,1.0,1.0);
					miFigura.cilindro(1,8.0,20,pared_1.GLindex);
					glPushMatrix();			//esfera1
						glTranslatef(0.0, 8.0, 0.0);
						miFigura.esfera(1.0,20,20,pared_1.GLindex);
					glPopMatrix();
					glRotatef(-90,0.0,1.0, 0.0);
					glPushMatrix();   //columnahor
						glTranslatef(4.0, 8.0, 0.0);
						glRotatef(90,0.0,0.0, 1.0);
						
						miFigura.cilindro(1,4.0,20,pared_1.GLindex);
						glPushMatrix();  //esfera2
							miFigura.esfera(1.0,20,20,pared_1.GLindex);
							glRotatef(-90,0.0,0.0, 1.0);
							
							miFigura.cilindro(1,4.0,20,pared_1.GLindex);
							glTranslatef(0.0, 4.0, 0.0);
							miFigura.cono(3.0,1.5,10,helado_1.GLindex);  //cono superior
						glPopMatrix();
					glPopMatrix();

				glPopMatrix();
				glPushMatrix();   //columna3
					glTranslatef(-15.0, 0.0, 0.0);
					glColor3f(1.0,1.0,1.0);
					miFigura.cilindro(1,8.0,20,pared_1.GLindex);
					glPushMatrix();			//esfera1
						glTranslatef(0.0, 8.0, 0.0);
						miFigura.esfera(1.0,20,20,pared_1.GLindex);
					glPopMatrix();
					glPushMatrix();   //columnahor
						glTranslatef(4.0, 8.0, 0.0);
						glRotatef(90,0.0,0.0, 1.0);
						
						miFigura.cilindro(1,4.0,20,pared_1.GLindex);
						glPushMatrix();  //esfera2
							miFigura.esfera(1.0,20,20,pared_1.GLindex);
							glRotatef(-90,0.0,0.0, 1.0);
							
							miFigura.cilindro(1,4.0,20,pared_1.GLindex);
							glTranslatef(0.0, 4.0, 0.0);
							miFigura.cono(3.0,1.5,10,helado_1.GLindex);  //cono superior
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
				glPushMatrix();   //columna4
					glTranslatef(15.0, 0.0, 0.0);
					glColor3f(1.0,1.0,1.0);
					miFigura.cilindro(1,8.0,20,pared_1.GLindex);
					glPushMatrix();			//esfera1
						glTranslatef(0.0, 8.0, 0.0);
						miFigura.esfera(1.0,20,20,pared_1.GLindex);
					glPopMatrix();
					glRotatef(180,0.0,1.0, 0.0);
					glPushMatrix();   //columnahor
						glTranslatef(4.0, 8.0, 0.0);
						glRotatef(90,0.0,0.0, 1.0);
						
						miFigura.cilindro(1,4.0,20,pared_1.GLindex);
						glPushMatrix();  //esfera2
							miFigura.esfera(1.0,20,20,pared_1.GLindex);
							glRotatef(-90,0.0,0.0, 1.0);
							
							miFigura.cilindro(1,4.0,20,pared_1.GLindex);
							glTranslatef(0.0, 4.0, 0.0);
							miFigura.cono(3.0,1.5,10,helado_1.GLindex);  //cono superior
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();		

			//dona
			/*glPushMatrix();
				glTranslated(0,0,0);
				glColor3f(1.0,1.0,0.0);
				miFigura.torus(20,19,16, 16);
			glPopMatrix();
			*/

			
		glPopMatrix();

glPopMatrix(); //FIN CASTILLO

}
void seccion_hoja(){
	glPushMatrix();
				glPushMatrix(); //plano a
					glTranslatef(0, -0.5, 20);
					glRotatef(11,0.0,1.0, 0.0);   //gira 11 grados el primer plano que está a la derecha 
					//glBindTexture(GL_TEXTURE_2D, lluvian.GLindex);
					glBegin(GL_QUADS);
						glColor3f(0, 0.533, 0.082);
						glNormal3f(0.0, 0.0, 1.0);
						glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
						glTexCoord2f(1.0, 0.0); glVertex3f(7.8, 0, 0.0);
						glTexCoord2f(1.0, 1.0); glVertex3f(7.8, 4, 0.0);
						glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 4, 0.0);
					glEnd();
					glPushMatrix(); //plano b
						glTranslatef(7.8, 0, 0);
						glRotatef(23,0.0,1.0, 0.0);   //gira 11 grados el primer plano 
						//glBindTexture(GL_TEXTURE_2D, lluvian.GLindex);
						glBegin(GL_QUADS);
							glColor3f(0, 0.533, 0.082);
							glNormal3f(0.0, 0.0, 1.0);
							glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
							glTexCoord2f(1.0, 0.0); glVertex3f(7.8, 0, 0.0);
							glTexCoord2f(1.0, 1.0); glVertex3f(7.8, 4, 0.0);
							glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 4, 0.0);
						glEnd();
						glPushMatrix(); //plano c
							glTranslatef(7.8, 0, 0);
							glRotatef(22,0.0,1.0, 0.0);   //gira 11 grados el primer plano 
							//glBindTexture(GL_TEXTURE_2D, lluvian.GLindex);
							glBegin(GL_QUADS);
								glColor3f(0, 0.533, 0.082);
								glNormal3f(0.0, 0.0, 1.0);
								glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
								glTexCoord2f(1.0, 0.0); glVertex3f(7.8, 0, 0.0);
								glTexCoord2f(1.0, 1.0); glVertex3f(7.8, 4, 0.0);
								glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 4, 0.0);
							glEnd();
								glPushMatrix(); //plano d
								glTranslatef(7.8, 0, 0);
								glRotatef(22.5,0.0,1.0, 0.0);   //gira 11 grados el primer plano 
								//glBindTexture(GL_TEXTURE_2D, lluvian.GLindex);
								glBegin(GL_QUADS);
									glColor3f(0, 0.533, 0.082);
									glNormal3f(0.0, 0.0, 1.0);
									glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
									glTexCoord2f(1.0, 0.0); glVertex3f(7.8, 0, 0.0);
									glTexCoord2f(1.0, 1.0); glVertex3f(7.8, 4, 0.0);
									glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 4, 0.0);
								glEnd();
							glPopMatrix();//fin plano d
						glPopMatrix();//fin plano c
					glPopMatrix(); //fin plano b
				glPopMatrix();// fin plano a

			glPopMatrix();//fin barda

}
void hojas_comp(){
			glPushMatrix();
				seccion_hoja();
				glPushMatrix();
					glRotatef(90,0.0,1.0, 0.0);
					glTranslatef(0.0, 0.0, 0.0);
					seccion_hoja();
				glPopMatrix();
				glPushMatrix();
					glRotatef(180,0.0,1.0, 0.0);
					glTranslatef(0.0, 0.0, 0.0);
					seccion_hoja();
				glPopMatrix();
				glPushMatrix();
					glRotatef(270,0.0,1.0, 0.0);
					glTranslatef(0.0, 0.0, 0.0);
					seccion_hoja();
				glPopMatrix();
			glPopMatrix();

}
void copa(){
glPushMatrix();   //copa esfera
		glTranslatef(0.0, 24.0, 0.0);
		glColor3f(0, 0.533, 0.082);
		miFigura.esfera(8.0,20,20,0);
		//hojas
		glPushMatrix();
			glTranslatef(0.0, -8.0, 0.0);
			glScalef(0.405,2.0,0.405);
			//glColor3f(0.0,1.0,0.0);
			hojas_comp();
			//barda_completa();
		glPopMatrix();
glPopMatrix();
}
void arbol_c(){
	glPushMatrix();
		glTranslatef(7.0, 0.0, 0.0); 
		glColor3f(0.274, 0.184, 0.113);
		miFigura.cilindro(2.0,14.0,20,0);   
		glTranslatef(0.0, 5.0, 0.0); 
		glScalef(0.5,0.5,0.5);
		copa();
	glPopMatrix();
}
void casa_arbol(){


glPushMatrix();
	glTranslatef(-30.0, -0.5, 45.0);  //origen en el arbol
	glColor3f(0.274, 0.184, 0.113);
	miFigura.cono(20.0,6.0,10,0);

	glPushMatrix();
		glTranslatef(0.0, 7.0, 0.0);  
		glColor3f(0.274, 0.184, 0.113);
		miFigura.cilindro(3.89,13.0,20,0);   //arriba del tronco
	glPopMatrix();

	copa();   //copa arboles

	arbol_c();  //1er arbol

	glPushMatrix();  //segundo arbol
		glTranslatef(-7.0, -0.5, 0.0);
		glColor3f(0.274, 0.184, 0.113);
		miFigura.cilindro(2.0,10.0,20,0);
		glTranslatef(0.0, 1.0, 0.0); 
		glScalef(0.5,0.5,0.5);
		copa();
	glPopMatrix();
	
	
glPopMatrix();
}

void ciudad ()
{
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0, 1.0, 1.0);
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix(); //Pasto
		//glColor3f(0, 0.533, 0.082);
			glTranslatef(0.0,-1.0,50.0);
			glScalef(150,0.1,50);
			glDisable(GL_LIGHTING);
			fig4.prisma2(piso_v.GLindex, 0);
			glEnable(GL_LIGHTING);
			glColor3f(1.0, 1.0, 1.0);
		glPopMatrix();

		glPushMatrix(); //Pasto rosa
		//glColor3f(1.0, 1.0, 1.0);
		glColor3f(1.0, 0.5098, 0.6705);
			glTranslatef(0.0,-1.0,0.0);
			glScalef(150,0.1,50);
			glDisable(GL_LIGHTING);
			fig4.prisma2(text5.GLindex, 0);
			//fig4.prisma2(piso_d.GLindex, 0);
			glEnable(GL_LIGHTING);
			glColor3f(1.0, 1.0, 1.0);
		glPopMatrix();

		glPushMatrix(); //Pasto nieve
		//glColor3f(0.5, 0.9, 0.98);
			glTranslatef(0.0,-1.0,-50.0);
			glScalef(150,0.1,50);
			glDisable(GL_LIGHTING);
			fig4.prisma2(nievep.GLindex, 0);
			glEnable(GL_LIGHTING);
			glColor3f(1.0, 1.0, 1.0);
		glPopMatrix();

		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_COLOR_MATERIAL);
}





GLuint createDL() 
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL,GL_COMPILE);
	// call the function that contains 
	// the rendering commands
		ciudad();
		//monito();
	// endList
	glEndList();

	return(ciudadDL);
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
    

	//BMO


	cuerpoBMO.LoadTGA("cuerpBMO.tga");
	cuerpoBMO.BuildGLTexture();
	cuerpoBMO.ReleaseImage();

	letrasBMO.LoadTGA("letrasBMO.tga");
	letrasBMO.BuildGLTexture();
	letrasBMO.ReleaseImage();

	atrasBMO.LoadTGA("atrasBMO.tga");
	atrasBMO.BuildGLTexture();
	atrasBMO.ReleaseImage();

	//ice
	nieve.LoadTGA("nieve.tga");
	nieve.BuildGLTexture();
	nieve.ReleaseImage();

	nievep.LoadTGA("nievep.tga");
	nievep.BuildGLTexture();
	nievep.ReleaseImage();

	nievem.LoadTGA("montana.tga");
	nievem.BuildGLTexture();
	nievem.ReleaseImage();

	lluvian.LoadTGA("lluvia.tga");
	lluvian.BuildGLTexture();
	lluvian.ReleaseImage();

	icesky.LoadTGA("icesky.tga");
	icesky.BuildGLTexture();
	icesky.ReleaseImage();

	skypasto.LoadTGA("skypasto.tga");
	skypasto.BuildGLTexture();
	skypasto.ReleaseImage();

	dulcesky.LoadTGA("candysky.tga");
	dulcesky.BuildGLTexture();
	dulcesky.ReleaseImage();

	otrosky.LoadTGA("otrosky.tga");
	otrosky.BuildGLTexture();
	otrosky.ReleaseImage();

	ventana_1.LoadTGA("ventana1.tga");
	ventana_1.BuildGLTexture();
	ventana_1.ReleaseImage();

	pared_1.LoadTGA("pared1.tga");
	pared_1.BuildGLTexture();
	pared_1.ReleaseImage();

	helado_1.LoadTGA("helado1.tga");
	helado_1.BuildGLTexture();
	helado_1.ReleaseImage();

	piso_d.LoadTGA("pisod.tga");
	piso_d.BuildGLTexture();
	piso_d.ReleaseImage();

	piso_v.LoadTGA("pisov.tga");
	piso_v.BuildGLTexture();
	piso_v.ReleaseImage();

	refresco.LoadTGA("refresco.tga");
	refresco.BuildGLTexture();
	refresco.ReleaseImage();

	//modelos 3ds
	candy._3dsLoad("DL3D_Christmas Cane.3ds");
	chocolate._3dsLoad("chocolate bar.3ds");


	//END NEW//////////////////////////////

	objCamera.Position_Camera(0,2.5f,35, 0,2.5f,0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for(int i=0; i<MAX_FRAMES; i++)
	{
		KeyFrame[0].transX =0;
		KeyFrame[0].transY =0;
		KeyFrame[0].transZ =0;
		KeyFrame[0].bmoangle =0;
		KeyFrame[0].bmoangle2 =0;
		KeyFrame[0].bmoangle3 =0;
		KeyFrame[0].angleY =20;


		KeyFrame[1].transX =-6.0;
		KeyFrame[1].transY =0;
		KeyFrame[1].transZ =0;
		KeyFrame[1].bmoangle =0;
		KeyFrame[1].bmoangle2 =0;
		KeyFrame[1].bmoangle3 =0;
		KeyFrame[1].angleY = -96,0;

		KeyFrame[2].transX =-9.0;
		KeyFrame[2].transY =0;
		KeyFrame[2].transZ =6;
		KeyFrame[2].bmoangle =0;
		KeyFrame[2].bmoangle2 =0;
		KeyFrame[2].bmoangle3 =0;
		KeyFrame[2].angleY =-96.0;

		KeyFrame[3].transX =-6.0;
		KeyFrame[3].transY =0;
		KeyFrame[3].transZ =6.0;
		KeyFrame[3].bmoangle =72;
		KeyFrame[3].bmoangle2 =0;
		KeyFrame[3].bmoangle3 =0;
		KeyFrame[3].angleY =-96;

		KeyFrame[4].transX =-5-0;
		KeyFrame[4].transY =0;
		KeyFrame[4].transZ =6.0;
		KeyFrame[4].bmoangle =72.0;
		KeyFrame[4].bmoangle2 =-54;
		KeyFrame[4].bmoangle3 =149;
		KeyFrame[4].angleY =-96;

		KeyFrame[5].transX =-4.0;
		KeyFrame[5].transY =0;
		KeyFrame[5].transZ =6.0;
		KeyFrame[5].bmoangle =39;
		KeyFrame[5].bmoangle2 =62;
		KeyFrame[5].bmoangle3 =149;
		KeyFrame[5].angleY =2;
	}
	//NEW//////////////////NEW//////////////////NEW//////////////////

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}



void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
		
	glPushMatrix();
		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();
			glPushMatrix(); //Creamos cielo
			glDisable(GL_LIGHTING);
			glTranslatef(0, 60, 0);
			fig1.skybox(130.0, 130.0, 130.0, skypasto.GLindex, dulcesky.GLindex, icesky.GLindex, otrosky.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

			glPushMatrix();
				glEnable ( GL_COLOR_MATERIAL );
					glColor3f(1, 1, 1);
					glCallList(ciudad_display_list);
				glDisable ( GL_COLOR_MATERIAL );
			glPopMatrix();


glPushMatrix();		//CAMPO
glEnable(GL_COLOR_MATERIAL);
			//BMO
  glPushMatrix();
  
  glColor3f(1.0, 1.0, 1.0);
		glTranslatef(transX, transY+0.7, transZ+35);
		//glRotatef(180, 0, 1.0, 0.0);
		glRotatef(angleY, 0.0, 1.0, 0.0);
		glRotatef(angleX, 1.0, 0.0, 0.0);
		glScalef(0.2, 0.2, 0.2);

	glPushMatrix();
		//glScalef(5.0, 8.0, 1.0);
		glColor3f(0.4, 0.7450, 0.6509);
		bmo.prismaBMO(6.0, 5.0, 4.0, cuerpoBMO.GLindex,letrasBMO.GLindex,atrasBMO.GLindex,letrasBMO.GLindex);// Cuerpo texturizado
	glPopMatrix();
	

		//Brazo D
	glPushMatrix();
			glTranslatef(3.25, -1.0, 0.0);
				glPushMatrix();
					glTranslatef(0.75, 0.0, 0.0);
					glRotatef(bmoangle, 0.0, 0.0, 1.0);
					glTranslatef(0.75, 0.0, 0.0);
					glPushMatrix();
						glTranslatef(0.75, 0.0, 0.0);
						glRotatef(bmoangle2, 0.0, 1.0, 0.0);
						glTranslatef(0.5, 0.0, 0.0);
						glColor3f(0.3882, 0.6745, 0.7019);
						bmo.prisma(1.0, 1.0,0.75,0);
					glPopMatrix();
					glColor3f(0.3882, 0.6745, 0.7019);
					bmo.prisma(0.75, 1.5, 0.75, 0); 
				glPopMatrix();
			glColor3f(0.3882, 0.6745, 0.7019);
			bmo.prisma(0.75, 1.5, 0.75, 0); //brazo D	
	glPopMatrix();

		//Brazo I
		glPushMatrix();
			glTranslatef(-4.0, -1.0, 0.0);
			//glScalef(3.0, 1.0, 1.0);
			//glRotatef(180,0.0,1.0, 0.0);
			glColor3f(0.3882, 0.6745, 0.7019);
			bmo.prisma(0.75, 3.0, 0.75, 0); //brazo I
		glPopMatrix();

		//Pie I
		glPushMatrix();
			glTranslatef(-2.0, -4.5, 0.0);
			//glScalef(1.0, 4.0, 1.0);
			//glRotatef(180,0.0,1.0, 0.0);
			glColor3f(0.3882, 0.6745, 0.7019);
			bmo.prisma(3.0, 0.7, 0.75, 0); //pie I
			
			glPushMatrix();
				glTranslatef(0.0, -1.5, 0.0);
				glRotatef(bmoangle3, 1.0, 0.0, 0.0);
				glTranslatef(0.0, -0.375, 0.75);;
				bmo.prisma(0.75, 0.75, 2.0, 0);//piecito
			glPopMatrix();
		glPopMatrix();

		//Pie D
		glPushMatrix();
			glTranslatef(2.0, -4.5, 0.0);
			//glScalef(1.0, 4.0, 1.0);
			//glRotatef(180,0.0,1.0, 0.0);
			glColor3f(0.3882, 0.6745, 0.7019);
			bmo.prisma(3.0, 0.75, 0.75, 0); //pie D
			glPushMatrix();
				glTranslatef(0.0, -1.5, 0.0);
				glRotatef(bmoangle3, 1.0, 0.0, 0.0);
				glTranslatef(0.0, -0.375, 0.75);;
				bmo.prisma(0.75, 0.75, 2.0, 0);//piecito
			glPopMatrix();
		glPopMatrix();

glPopMatrix(); //FIN BMO

		// CASA ARBOL	
		glPushMatrix();
		casa_arbol();
		 //arboles a
			glTranslatef(-30.0, -0.5, 45.0);  //origen en casa arbol
			glPushMatrix();			//arbol 1
					glTranslatef(65.0, -0.5, 0.0); 
					glScalef(0.2,0.2,0.2);
					arbol_c();		
			glPopMatrix();
			glPushMatrix();			//arbol 2
					glTranslatef(45.0, -0.5, -10.0); 
					glScalef(0.2,0.2,0.2);
					arbol_c();		
			glPopMatrix();
			glPushMatrix();			//arbol 3
					glTranslatef(25.0, -0.5, 5.0); 
					glScalef(0.2,0.2,0.2);
					arbol_c();		
			glPopMatrix();
			glPushMatrix();			//arbol 4
					glTranslatef(-15.0, -0.5, -15.0); 
					glScalef(0.2,0.2,0.2);
					arbol_c();		
			glPopMatrix();
			glPushMatrix();			//arbol 5
					glTranslatef(-35.0, -0.5, 0.0); 
					glScalef(0.2,0.2,0.2);
					arbol_c();		
			glPopMatrix();
		glPopMatrix();

		
glPopMatrix();			

glPushMatrix(); // DULCE REINO

	//CASTILLO
	glPushMatrix();
		castillo();
	glPopMatrix();

		//bastónes de dulce
		glPushMatrix();
			glTranslatef( -5.0, -0.5, 0.0);
			glRotatef(180,0,1,0);
			glScalef(0.04, 0.04, 0.04);
			glColor3f(1.0, 0.0, 0.0);
			candy.GLrender(NULL,_SHADED, 1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef( -15.0, -0.5, 0.0);
			glRotatef(180,0,1,0);
			glScalef(0.04, 0.04, 0.04);
			glColor3f(1.0, 1.0, 1.0);
			candy.GLrender(NULL,_SHADED, 1);
		glPopMatrix();

		//Barras de chocolate
		glPushMatrix();
			glTranslatef( -20.0, -0.5, 0.0);
			glRotatef(180,0,1,0);
			glScalef(0.04, 0.04, 0.04);
			glColor3f(0.533, 0.262, 0.184);
			chocolate.GLrender(NULL,_SHADED, 1);
		glPopMatrix();
	// arboles
	glPushMatrix();  //arboles a
		glTranslatef(0.0, -0.5, -5.0); 
		glPushMatrix();			//arbol 1
				glScalef(0.2,0.2,0.2);
				arbol_c();		
		glPopMatrix();
		glPushMatrix();			//arbol 2
				glTranslatef(-10.0, 0.0, 0.0); 
				glScalef(0.2,0.2,0.2);
				arbol_c();	
		glPopMatrix();
		glPushMatrix();			//arbol 3
				glTranslatef(-20.0, 0.0, 0.0); 
				glScalef(0.2,0.2,0.2);
				arbol_c();	
		glPopMatrix();
		glPushMatrix();			//arbol 4
				glTranslatef(-30.0, 0.0, 0.0); 
				glScalef(0.2,0.2,0.2);
				arbol_c();	
		glPopMatrix();
		glPushMatrix();			//arbol 5
				glTranslatef(-40.0, 0.0, 0.0); 
				glScalef(0.2,0.2,0.2);
				arbol_c();	
		glPopMatrix();


	glPopMatrix();

		glPushMatrix();  //arboles b
		glTranslatef(0.0, -0.5, 5.0); 
		glPushMatrix();			//arbol 1
				glScalef(0.2,0.2,0.2);
				arbol_c();		
		glPopMatrix();
		glPushMatrix();			//arbol 2
				glTranslatef(-10.0, 0.0, 0.0); 
				glScalef(0.2,0.2,0.2);
				arbol_c();	
		glPopMatrix();
		glPushMatrix();			//arbol 3
				glTranslatef(-20.0, 0.0, 0.0); 
				glScalef(0.2,0.2,0.2);
				arbol_c();	
		glPopMatrix();
		glPushMatrix();			//arbol 4
				glTranslatef(-30.0, 0.0, 0.0); 
				glScalef(0.2,0.2,0.2);
				arbol_c();	
		glPopMatrix();
		glPushMatrix();			//arbol 5
				glTranslatef(-40.0, 0.0, 0.0); 
				glScalef(0.2,0.2,0.2);
				arbol_c();	
		glPopMatrix();

	glPopMatrix();

glPopMatrix();//Fin dulce reino
		
			
glPushMatrix(); //REINO HIELO
		glPushMatrix();//montaña principal
			glTranslatef(0.0, 0, -50.0);

			glPushMatrix(); //montaña1 izq
			glTranslatef(-25.0, 0, 0.0);

			glPushMatrix(); //montaña2 izq
			glTranslatef(-25.0, 0, 0.0);
			glColor3f(1.0, 1.0, 1.0);
			montana.cono(70.0, 20.0, 5, nieve.GLindex);
			glPopMatrix(); //fin montaña2 izq

			glColor3f(1.0, 1.0, 1.0);
			montana.cono(75.0, 20.0, 5, nieve.GLindex);
			glPopMatrix(); //fin montaña1 izq


			glPushMatrix(); //montaña1 der
			glTranslatef(30.0, 0, 0.0);

			glPushMatrix(); //montaña2 der
			glTranslatef(25.0, 0, 0.0);
			glColor3f(1.0, 1.0, 1.0);
			montana.cono(70.0, 20.0, 5, nieve.GLindex);
			glPopMatrix(); //fin montaña2 der

			glColor3f(1.0, 1.0, 1.0);
			montana.cono(75.0, 20.0, 5, nieve.GLindex);
			glPopMatrix(); //fin montaña1 der


			glColor3f(1.0, 1.0, 1.0);
			montana.cono(85.0, 20.0, 5, nievem.GLindex);
		glPopMatrix(); //Fin montaña principal


		//pinos
		glPushMatrix();
			glTranslatef(-25,-1, -28);
			pino();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(40,-1, -28);
			pino();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-60,-1, -30);
			glScalef(2.0, 2.0, 2.0);
			pino();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(60,-1, -30);
			glScalef(0.8, 0.8, 0.8);
			pino();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(10,-1, -33);
			glScalef(0.7, 0.7, 0.7);
			pino();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(20,-1, -30);
			glScalef(0.7, 0.7, 0.7);
			pino();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-40,-1, -30);
			glScalef(0.9, 0.9, 0.9);
			pino();
		glPopMatrix();

/*
		//PINGU
  glPushMatrix();
  
  glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0, 0,-25);
		glRotatef(180, 0, 1.0, 0.0);
		glScalef(0.2, 0.2, 0.2);

	glPushMatrix();
		//glScalef(5.0, 8.0, 1.0);
		glColor3f(0.4, 0.7450, 0.6509);
		bmo.prismaBMO(6.0, 5.0, 4.0, cuerpoBMO.GLindex,letrasBMO.GLindex,atrasBMO.GLindex,letrasBMO.GLindex);// Cuerpo
	glPopMatrix();
	

		//Brazo D
	glPushMatrix();
			glTranslatef(4.0, -1.0, 0.0);
			glColor3f(0.0, 0.0,0.0);
			bmo.prisma(0.75, 0.75, 0.75, 0); //brazo D	
	glPopMatrix();

		//Brazo I
		glPushMatrix();
			glTranslatef(4.0, -1.0, 0.0);
			glColor3f(0.0, 0.0,0.0);
			bmo.prisma(0.75, 0.75, 0.75, 0); //brazo D	
	glPopMatrix();

		//Pie I
		glPushMatrix();
			glTranslatef(-2.0, -4.5, 0.0);
			glColor3f(1.0, 1.0, 0.0);
			bmo.prisma(3.0, 0.7, 0.75, 0); //pie I
			glPushMatrix();
			glTranslatef(0.0, -1.125, 0.75);
			glColor3f(1.0, 1.0, 0.0);
			bmo.prisma(0.75, 0.75, 2.0, 0);//piecito
			glPopMatrix();
		glPopMatrix();

		//Pie D
		glPushMatrix();
			glTranslatef(2.0, -4.5, 0.0);
			//glScalef(1.0, 4.0, 1.0);
			//glRotatef(180,0.0,1.0, 0.0);
			glColor3f(1.0, 1.0, 0.0);
			bmo.prisma(3.0, 0.75, 0.75, 0); //pie D
			glPushMatrix();
			glTranslatef(0.0, -1.125, 0.75);
			glColor3f(1.0, 1.0, 0.0);
			bmo.prisma(0.75, 0.75, 2.0, 0);//piecito
			glPopMatrix();
		glPopMatrix();

glPopMatrix(); //FIN pingu
*/



		glPushMatrix(); // plano nieve
	
		glTranslatef(-65, 0, -31);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND); ///activa transparecia
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//transparencia
		glBindTexture(GL_TEXTURE_2D, lluvian.GLindex);
			glBegin(GL_QUADS);
			glColor3f(1.0, 1.0, 1.0);
			glNormal3f(0.0, 0.0, -1.0);
			glTexCoord2f(0.0, 0.0 + var); glVertex3f(0.0, 0.0, 0.0);
			glTexCoord2f(1.0, 0.0 + var); glVertex3f(130.0, 0, 0.0);
			glTexCoord2f(1.0, 1.0 + var); glVertex3f(130.0, 130.0, 0.0);
			glTexCoord2f(0.0, 1.0 + var); glVertex3f(0.0, 130, 0.0);
		glEnd();
		glDisable(GL_BLEND); ///desactiva transparecia
		glEnable(GL_LIGHTING);
		glPopMatrix();



glPopMatrix(); //FIN REINO DE HIELO

glDisable(GL_COLOR_MATERIAL);
			/*
			glPushMatrix(); //Flecha
				glScalef(7,0.1,7);
				glDisable(GL_LIGHTING);
				fig3.prisma_anun(text3.GLindex, 0);
				glEnable(GL_LIGHTING);
			glPopMatrix();
			*/

			glEnable ( GL_COLOR_MATERIAL );
			

			glColor3f(1.0,1.0,1.0);

		glPopMatrix(); 

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
			glColor3f(1.0,0.0,0.0);
			pintaTexto(-0.25,0.23,-0.25,(void *)font,"Adventure Time");
			//pintaTexto(-0.25,0.19,-0.25,(void *)font,s);
			glColor3f(1.0,1.0,1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	fig3.text_izq-= 0.01;
	fig3.text_der-= 0.01;
	if(fig3.text_izq<-1)
		fig3.text_izq=0;
	if(fig3.text_der<0)
		fig3.text_der=1;

	var += 0.01;

	//Movimiento del coche
	if(g_fanimacion)
	{
		/*if(g_avanza)
		{
			movKitZ +=1.0;
			rotTires -= 10;
			if(movKitZ>130)
				g_avanza = false;
		}
		else
		{
			movKitZ -=1.0;
			rotTires += 10;
			if(movKitZ<0)
				g_avanza = true;
		}
	}

	if(circuito)
	{
		if(recorrido1)
		{
			rotKit = 0;
			rotKitX = 0;
			movKitZ--;
			if(movKitZ<-155)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if(recorrido2)
		{
			rotKit = -90;
			movKitX++;
			if(movKitX > 125)
			{
				recorrido2 = false;
				recorrido3 = true;
				
			}
		}
		if(recorrido3)
		{
			rotKit = 160;
			movKitZ++;
			movKitX-=0.4;
			
			if(movKitZ > 155)
			{
				recorrido3 = false;
				recorrido4 = true;
				
			}
		}
		if(recorrido4)
		{
			rotKit = 0;
			rotKitX = -35.75;
			movKitY += 0.72;
			movKitZ --;

			if(movKitY>40)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		
		if(recorrido5)
		{
			rotKit = 0;
			rotKitX = 0;
			movKitZ --;
			if(movKitZ<-90)
			{
				recorrido5 = false;
				recorrido6 = true;
			}
		}
		if(recorrido6)
		{
			rotKit = 0;
			rotKitX = 31.59;
			movKitY -= 0.615;
			movKitZ --;
			if(movKitY<=0)
			{
				recorrido6 = false;
				recorrido1 = true;
			}
		}*/
	}


	//Movimiento del monito
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation

			KeyFrame[playIndex].incX=(KeyFrame[playIndex+1].transX-KeyFrame[playIndex].transX)/i_max_steps;			//100 frames
			KeyFrame[playIndex].incY=(KeyFrame[playIndex+1].transY-KeyFrame[playIndex].transY)/i_max_steps;			//100 frames
			KeyFrame[playIndex].incZ=(KeyFrame[playIndex+1].transZ-KeyFrame[playIndex].transZ)/i_max_steps;			//100 frames

			KeyFrame[playIndex].inc1=(KeyFrame[playIndex+1].bmoangle-KeyFrame[playIndex].bmoangle)/i_max_steps;		//100 frames
			KeyFrame[playIndex].inc2=(KeyFrame[playIndex+1].bmoangle2-KeyFrame[playIndex].bmoangle2)/i_max_steps;	//100 frames
			KeyFrame[playIndex].inc3=(KeyFrame[playIndex+1].bmoangle3-KeyFrame[playIndex].bmoangle3)/i_max_steps;		//100 frames
			KeyFrame[playIndex].incangleY=(KeyFrame[playIndex+1].angleY-KeyFrame[playIndex].angleY)/i_max_steps;	

			}
		}
		else
		{	//Draw information
			transX+=KeyFrame[playIndex].incX;
			transY+=KeyFrame[playIndex].incY;
			transZ+=KeyFrame[playIndex].incZ;
			bmoangle+=KeyFrame[playIndex].inc1;
			bmoangle2+=KeyFrame[playIndex].inc2;
			bmoangle3+=KeyFrame[playIndex].inc3;
			angleY+=KeyFrame[playIndex].incangleY;

			i_curr_steps++;
		}

	}

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
		timebase = time;		
		frame = 0;
	}

	glutPostRedisplay();
}


void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	//glOrtho(-70,70,-70,70,0.1,20);
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 170.0);


	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

/*void mouse( int mov, int x, int y ){
	switch (mov) {
	case MOUSEEVENTF_MOVE:
		objCamera.Move_Camera( CAMERASPEED+0.2 );
	break;
	case MOUSE_EVENT:
		objCamera.Move_Camera( -(CAMERASPEED+0.2) );
	break;
	}
}*/

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {

		
		case 't':   //Movimientos de camara
			objCamera.Move_Camera( CAMERASPEED+0.1 );
			break;

		case 'g':
			objCamera.Move_Camera(-(CAMERASPEED+0.1));
			break;

		case 'f':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.1));
			break;

		case 'h':
			objCamera.Strafe_Camera((CAMERASPEED+0.1));
			break;

			 //Movimientos de camara
		case 'i':  
			g_lookupdown -= 1.0f;
			break;

		case 'k':
			g_lookupdown += 1.0f;
			break;

		case 'j':
			objCamera.Rotate_View(-CAMERASPEED);
			break;

		case 'l':
			objCamera.Rotate_View( CAMERASPEED);
			break;

		case 'w':   //Movimientos de BMO
		case 'W':
			transZ --;
			printf( "Z: %f \n", transZ);
			break;

		case 'S':
		case 's':
			transZ ++;
			printf( "Z: %f \n", transZ);
			break;

		case 'd':
		case 'D':
			transX ++;
			printf( "x: %f \n", transX);
			break;

		case 'a':
		case 'A':
			transX --;
			printf( "x: %f \n", transX);
			break;

		case 'q':
			bmoangle ++;
			printf( "bmoangle: %f \n", bmoangle);
			
			break;

		case 'Q':
			bmoangle --;
			printf( "bmoangle: %f \n", bmoangle);
			break;

		case 'e':
			bmoangle2 ++;
			printf( "bmoangle2: %f \n", bmoangle2);
			break;
	
		case 'E':
			bmoangle2 --;
			printf( "bmoangle2: %f \n", bmoangle2);
			break;

		case 'z':
			bmoangle3 ++;
			printf( "bmoangle3: %f \n", bmoangle3);
			break;

		case 'Z':
			bmoangle3 --;
			printf( "bmoangle3: %f \n", bmoangle3);
			break;

		//vista fija

		case 'C':
			objCamera.Position_Camera(55,1.0,55,-25,1,-5,0,1,0);
		break;
		case 'c':
			objCamera.Position_Camera(55,55,5,0,20,-5,0,1,0);
		break;
	/*
		case 'O':		//  
		case 'o':
				g_fanimacion^= true; //Activamos/desactivamos la animacíon
				circuito = false;
			break;

		case 'i':		//  
		case 'I':
				circuito^= true; //Activamos/desactivamos la animacíon
				g_fanimacion = false;
			break;

		case 'k':		//
		case 'K':
			if(FrameIndex<MAX_FRAMES)
			{
				printf("frameindex %d\n",FrameIndex);

				KeyFrame[FrameIndex].posX=posX;
				KeyFrame[FrameIndex].posY=posY;
				KeyFrame[FrameIndex].posZ=posZ;

				KeyFrame[FrameIndex].rotRodIzq=rotRodIzq;
				KeyFrame[FrameIndex].giroMonito=giroMonito;
				KeyFrame[FrameIndex].giroBrazo=giroBrazo;
			
				FrameIndex++;
			}
			
			break;
			*/
		case 'm':						
		case 'M':
			if(play==false && (FrameIndex>1))
			{
				transX=KeyFrame[0].transX;
				transY=KeyFrame[0].transY;
				transZ=KeyFrame[0].transZ;
				bmoangle=KeyFrame[0].bmoangle;
				bmoangle2=KeyFrame[0].bmoangle2;
				bmoangle3=KeyFrame[0].bmoangle3;
				angleY=KeyFrame[0].angleY;

				play=true;
				playIndex=0;
			}
			else
			{
				play=false;
			}
			break;
/*
		case 'y':						
		case 'Y':
			posZ++;
			//printf("%f \n", posZ);
			break;

		case 'g':						
		case 'G':
			posX--;
			//printf("%f \n", posX);
			break;

		case 'h':						
		case 'H':
			posZ--;
			//printf("%f \n", posZ);
			break;

		case 'j':						
		case 'J':
			posX++;
			//printf("%f \n", posX);
			break;

		case 'b':						
			rotRodIzq++;
			//printf("%f \n", rotRodIzq);
			break;

		case 'B':						
			rotRodIzq--;
			//printf("%f \n", rotRodIzq);
			break;

		case 'p':						
			giroMonito++;
			//printf("%f \n", giroMonito);
			break;

		case 'P':						
			giroMonito--;
			//printf("%f \n", giroMonito);
			break;

		case 'm':   //Movimientos de brazo
			giroBrazo--;
			break;

		case 'M':   //Movimientos de brazo
			giroBrazo++;
			break;
			*/
		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		//g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		//g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		//objCamera.Rotate_View(-CAMERASPEED);
		angleY += 2.0;
		printf( "angleY: %f \n", angleY);
		break;

	case GLUT_KEY_RIGHT:
		//objCamera.Rotate_View( CAMERASPEED);
		angleY -= 2.0;
		printf( "angleY: %f \n", angleY);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

void menuKeyFrame( int id)
{
	switch (id)
	{
		case 0:
			if(FrameIndex<MAX_FRAMES)
			{
				printf("frameindex %d\n",FrameIndex);

				KeyFrame[FrameIndex].posX=posX;
				KeyFrame[FrameIndex].posY=posY;
				KeyFrame[FrameIndex].posZ=posZ;

				KeyFrame[FrameIndex].rotRodIzq=rotRodIzq;
				KeyFrame[FrameIndex].giroMonito=giroMonito;
			
				FrameIndex++;
			}
			
		
			break;

		case 1:
			if(play==false && FrameIndex >1)
			{
				posX=KeyFrame[0].posX;
				posY=KeyFrame[0].posY;
				posZ=KeyFrame[0].posZ;

				rotRodIzq=KeyFrame[0].rotRodIzq;
				giroMonito=KeyFrame[0].giroMonito;

				play=true;
				playIndex=0;
			}
			else
			{
				play=false;
			}
			break;

	}
}


void menu( int id)
{
	switch (id)
	{
		case 1:
			g_fanimacion^= true; //Activamos/desactivamos la animacíon
			break;


	}
}



int main ( int argc, char** argv )   // Main Function
{
  int submenu;
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("AdventureTime"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  submenu = glutCreateMenu	  ( menuKeyFrame );
  glutAddMenuEntry	  ("Guardar KeyFrame", 0);
  glutAddMenuEntry	  ("Reproducir Animacion", 1);
  glutCreateMenu	  ( menu );
  glutAddSubMenu	  ("Animacion Monito", submenu);
  //glutAddMenuEntry	  ("Animacion Carro", 1);
 
  glutAttachMenu	  (GLUT_RIGHT_BUTTON);

  glutMainLoop        ( );          // 

  return 0;
}
