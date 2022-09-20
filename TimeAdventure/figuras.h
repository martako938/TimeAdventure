//#include <windows.h>  //Solo para Windows
//#include <GL/gl.h>     // The GL Header File
//#include <stdio.h>

//#include <math.h>
#include "Main.h"


class CFiguras
{
	public:

	float text_der;
	float text_izq;

	void esfera(GLfloat radio, int meridianos, int paralelos, GLuint text); //Funcíon creacion esfera
	void cilindro(float radio, float altura, int resolucion, GLuint text);	//Funcíon creacion cilindro
	void cono(float altura, float radio, int resolucion, GLuint text);		//Funcíon creacion cono
	void prisma_anun (GLuint text, GLuint text2);							//Funcíon creacion movimiento
	void prisma (float altura, float largo, float profundidad, GLuint text);//Funcíon creacion prisma
	void prisma2 (GLuint text, GLuint text2);
	void skybox(float largo, float altura, float profundidad, GLuint text1, GLuint text2, GLuint text3, GLuint text4);	//Funcion creacion cielo
	void skybox2 (float altura, float largo, float profundidad, GLuint text);
	void renderSphere( float cx, float cy, float cz, float r, int p, GLuint text );
	void prismaBMO (float altura, float largo, float profundidad, GLuint t1, GLuint t2, GLuint t3, GLuint t4);//Funcíon creacion prisma BMO
	

	//void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos, GLuint text );
	void torus(GLfloat radioM, GLfloat radiom, int meridianos, int paralelos);
	//void elipsoide (float uiStacks, float uiSlices, float fA, float fB, float fC, GLuint text);

	void dibujaDomoCielo(float radio, int paralelos, int meridianos, int modoRender);

	void tecla (float altura, float largo, float profundidad, GLuint text);

};
