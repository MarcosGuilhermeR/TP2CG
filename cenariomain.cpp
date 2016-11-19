

#include "GL/glut.h"
#include "soil/SOIL.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define MAX_TEX 23    //numero de texturas que serao usadas no vetor de texturas

#define CEU 0
#define GRAMA 1


float angulo = 0.0f, rota_paquito = 0, controle = 1, controle2 = 1;
float xcamera = 0.0f, ycamera = 5.0f, zcamera = 30.0f;     //posicao da camera
float dxcamera = 0.0f, dycamera = 0.0f, dzcamera = -1.0f;  //direção ao deslocar a camera

float quant = 0.4f, cmenu = 0;  //quant é o valor das coordenas rgb da luz difusa da camera

GLuint texturas[MAX_TEX]; //vetor de texturas

//função que configura a direção da camera
void OrientaCamera(float ang) {
	dxcamera = sin(ang);
	dzcamera = -cos(ang);
	glLoadIdentity();
	gluLookAt(xcamera, ycamera, zcamera, xcamera + dxcamera, ycamera + dycamera, zcamera + dzcamera, 0.0f, 1.0f, 0.0f);
}

//função que configura a posição da camera
void MoveCamera(int direcao) {
	if (xcamera>90.0f) {
		if (direcao*(dxcamera)*0.7 < 0)
			xcamera = xcamera + direcao*(dxcamera)*0.7;
	}
	if (xcamera<-90.0f) {
		if (direcao*(dxcamera)*0.7 > 0)
			xcamera = xcamera + direcao*(dxcamera)*0.7;
	}
	if (xcamera>-90.0f && xcamera<90.0f)
		xcamera = xcamera + direcao*(dxcamera)*0.7;

	if (zcamera>90.0f) {
		if (direcao*(dzcamera)*0.7 < 0)
			zcamera = zcamera + direcao*(dzcamera)*0.7;
	}
	if (zcamera<-90.0f) {
		if (direcao*(dzcamera)*0.7 > 0)
			zcamera = zcamera + direcao*(dzcamera)*0.7;
	}
	
	glLoadIdentity();
	gluLookAt(xcamera, ycamera, zcamera, xcamera + dxcamera, ycamera + dycamera, zcamera + dzcamera, 0.0f, 1.0f, 0.0f);
	GLfloat posicaocamera[4] = { xcamera,ycamera,zcamera,1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, posicaocamera);
}

//função que trata eventos do teclado normal
void TeclasNormais(unsigned char key, int x, int y) {

	key = tolower(key);

	GLfloat luzdifusa[4] = { quant, quant, quant, 1.0 };
	if (cmenu != 0) {
		switch (key) {
		case 27:
			exit(0);
			break;
		case 'j':
			angulo -= 0.1f;
			break;
		case 's':
			MoveCamera(-1);
			break;
		case 'w':
			MoveCamera(1);
			break;
		case 'a':
			angulo -= 0.1f;
			OrientaCamera(angulo);
			break;
		case 'd':
			angulo += 0.1f;
			OrientaCamera(angulo);
			break;
		case 'r':
			angulo = 0.0f;
			rota_paquito = 0.0f;
			xcamera = 0.0f;
			ycamera = 5.0f;
			zcamera = 30.0f;
			dxcamera = 0.0f;
			dycamera = 0.0f;
			dzcamera = -20.0f;
			quant = 0.4f;
			MoveCamera(1);
			luzdifusa[0] = quant;
			luzdifusa[1] = quant;
			luzdifusa[2] = quant;
			glLightfv(GL_LIGHT1, GL_DIFFUSE, luzdifusa);
			break;
		case 'o':
			glEnable(GL_LIGHT1);
			break;
		case 'p':
			glDisable(GL_LIGHT1);
			break;
		case 43:  
			quant += 0.1f;
			if (quant>1.0) quant = 1.0f;
			glLightfv(GL_LIGHT1, GL_DIFFUSE, luzdifusa);
			break;
		case 45:  
			quant -= 0.1f;
			if (quant>-2.2) quant = -2.1f;
			glLightfv(GL_LIGHT1, GL_DIFFUSE, luzdifusa);
			break;
		}
	}
	else {
		switch (key) {
		case 27:
			exit(0);
			break;
		default:
			angulo = 0.0f;
			rota_paquito = 0.0f;
			xcamera = 0.0f;
			ycamera = 5.0f;
			zcamera = 30.0f;
			dxcamera = 0.0f;
			dycamera = 0.0f;
			dzcamera = -20.0f;
			quant = 0.4f;
			cmenu = 1;
			MoveCamera(1);
			GLfloat luzdifusa[4] = { quant, quant, quant, 1.0 };
			luzdifusa[0] = quant;
			luzdifusa[1] = quant;
			luzdifusa[2] = quant;
			glLightfv(GL_LIGHT1, GL_DIFFUSE, luzdifusa);
		}
	}
}

//função que trata os eventos de teclas especiais
void TeclasEspeciais(int key, int x, int y) {
	if (cmenu != 0) {
		switch (key) {
		case GLUT_KEY_UP:
			ycamera += 1.0f;
			if (ycamera == 41) ycamera = 40;
			MoveCamera(0);
			break;
		case GLUT_KEY_DOWN:
			ycamera -= 1.0f;
			if (ycamera == 0) ycamera = 1.0f;
			MoveCamera(0);
			break;
		}
	}
}

//função que configura o redimensionamento de janela
void AlteraTamanho(int largura, int altura) {
	if (altura == 0) altura = 1;
	int taxa = 1.0f * largura / altura;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, largura, altura);
	gluPerspective(45.0, taxa, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (cmenu == 0) {
		gluLookAt(xcamera, ycamera, zcamera, xcamera + dxcamera, ycamera + dycamera, zcamera + dzcamera, 0.0f, 1.0f, 0.0f);
		angulo = 0.6f;
		OrientaCamera(angulo);
		int i;
		cmenu = 1;
		for (i = 0; i<1000; i++) {
			MoveCamera(-1);
			TeclasEspeciais(GLUT_KEY_UP, 0, 0);
		}
		cmenu = 0;
	}
	else {
		gluLookAt(xcamera, ycamera, zcamera, xcamera + dxcamera, ycamera + dycamera, zcamera + dzcamera, 0.0f, 1.0f, 0.0f);
	}
}

//função que inicializa o programa, nela são configuradas as luzes do programa e as texturas que serão utilizadas
void Inicializa() {

	GLfloat luzAmbiente[4] = { 1.0, 1.0, 1.0, 1.0 };                         //vetores que armazenam dados a serem utilizados na configuracao de luzes
	GLfloat luzEmissiva[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat luzdifusa[4] = { quant,quant,quant,1.0 };
	GLfloat luzemissivaposicao[4] = { 0.0, 30.0, -80.0, 1.0 };
	GLfloat posicaoLuz[4] = { 0.0, 20.0, 0.0, 1.0 };
	GLfloat posicaocamera[4] = { xcamera,ycamera,zcamera,1.0 };
	GLfloat posicaoLuzespecular[4] = { 0.0, 20.0, 80.0, 1.0 };
	glShadeModel(GL_SMOOTH);                                               //sombreamento suavizado

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);                   //configura luz ambiente

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);                         //configura as diversas luzes do programa
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzdifusa);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaocamera);
	glLightfv(GL_LIGHT2, GL_SPECULAR, luzAmbiente);
	glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuzespecular);
	glLightfv(GL_LIGHT3, GL_EMISSION, luzEmissiva);
	glLightfv(GL_LIGHT3, GL_POSITION, luzemissivaposicao);

	glEnable(GL_COLOR_MATERIAL);                                           //habilita o uso de configuração de materiais
	glEnable(GL_LIGHTING);                      						   //habilita iluminação
	glEnable(GL_LIGHT0);												   //habilita as diversas luzes
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_DEPTH_TEST);                                               //habilita teste de profundidade

	glEnable(GL_TEXTURE_2D);                                            //habilita texturas 2d e elas são configuradas
	glGenTextures(1, texturas);

	texturas[CEU] = SOIL_load_OGL_texture("textura/ceu.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[GRAMA] = SOIL_load_OGL_texture("textura/grama.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

}

//função que desenha o cenário, modelada atraves de quadrica
void cenarioEsfera() {
	glBindTexture(GL_TEXTURE_2D, texturas[CEU]);       //esfera modelada atraves de quadrica
	glPushMatrix();
	GLUquadricObj *quad3;
	quad3 = gluNewQuadric();
	gluQuadricNormals(quad3, GLU_SMOOTH);
	gluQuadricTexture(quad3, GL_TRUE);
	glTranslatef(0.0f, 1.0f, 0.0f);
	gluSphere(quad3, 200, 20.0, 20.0);
	glPopMatrix();
}

//função que configura os materiais dos objetos que serao chamados para serem desenhados
void Desenha() {

	GLfloat espec_grama[4] = { 0.7, 0.7, 0.7, 1.0 };
	GLint especMaterial = 100;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glBindTexture(GL_TEXTURE_2D, texturas[GRAMA]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-400.0f, 0.0f, -400.0f);
	glTexCoord2f(0.0f, 80.0f); glVertex3f(400.0f, 0.0f, -400.0f);
	glTexCoord2f(80.0f, 80.0f); glVertex3f(400.0f, 0.0f, 400.0f);
	glTexCoord2f(80.0f, 0.0f); glVertex3f(-400.0f, 0.0f, 400.0f);
	glEnd();
	espec_grama[0] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	espec_grama[1] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	cenarioEsfera();
	espec_grama[2] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	espec_grama[0] = 0.0;
	espec_grama[2] = 0.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	espec_grama[1] = 0.5;
	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	espec_grama[0] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	espec_grama[0] = 0.5;
	espec_grama[1] = 0.5;
	espec_grama[2] = 0.5;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	espec_grama[0] = 0.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	espec_grama[2] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	espec_grama[1] = 0.3;
	espec_grama[2] = 0.2;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	espec_grama[0] = 0.1;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glBindTexture(GL_TEXTURE_2D, texturas[GRAMA]);
	espec_grama[3] = 0.7;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glutSwapBuffers();
}

//função principal do programa
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Holanda do Batman");

	Inicializa();
	glutKeyboardFunc(TeclasNormais);
	glutSpecialFunc(TeclasEspeciais);

	glutDisplayFunc(Desenha);
	glutIdleFunc(Desenha);
	glutFullScreen();
	glutReshapeFunc(AlteraTamanho);

	glutMainLoop();

	return(0);
}



