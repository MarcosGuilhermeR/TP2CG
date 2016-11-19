

#include <GL/glut.h>
#include <soil/SOIL.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEX 23    //numero de texturas que serao usadas no vetor de texturas

#define AREIA 0       //posiÃ§Ãµes do vetor de texturas que armazenam determinadas texturas
#define TRAVE 1
#define REDE 2
#define LINHA 3
#define CEU 4
#define CEU2 5
#define CEU3 6
#define BOLA 7
#define ARQUIBANCADA 8
#define PUBLICIDADE 9
#define PLACA 10
#define CADEIRA 11
#define PAQUITO1 12
#define PAQUITO2 13
#define PLACAR 14
#define GUARDASOL 15
#define VERDE 16
#define AZUL 17
#define MENU1 18
#define MENU2 19
#define MENU3 20
#define OPCAO 21
#define SNOW 22

char MUSICA[] = "c.mp3";         //armazena o nome da musica durante o programa

float angulo = 0.0f, rota_paquito = 0, controle = 1, controle2 = 1;
float xcamera = 0.0f, ycamera = 5.0f, zcamera = 30.0f;     //posicao da camer
float dxcamera = 0.0f, dycamera = 0.0f, dzcamera = -1.0f;  //direÃ§Ã£o ao deslocar a camera

int mostramenu = MENU1, antemusica = 0, amusica = 0;     //variaveis para o menu

float quant = 0.4f, cmenu = 0;  //quant Ã© o valor das coordenas rgb da luz difusa da camera

GLuint texturas[MAX_TEX]; //vetor de texturas

						  //funÃ§Ã£o que configura o menu
void menu() {
	glBindTexture(GL_TEXTURE_2D, texturas[mostramenu]);//passa tipoda textura(GL_TEXTURE_2D) e a texturas[mostramenu]->fala qual textura sera usada na prox renderizaÃ§Ã£o do plano
	glPushMatrix();//tira sistema de coordenadas do topo da pilha
	glTranslatef(xcamera + 17.0, ycamera - 5, zcamera - 24.7);
	glRotatef(-0.6 * 57, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -5.0f, 0.0f);//casa textura
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f, -5.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f, 15.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();
}

//funÃ§Ã£o que configura a musica a ser tocada
void toca() {
	//musica removida
}

//funÃ§Ã£o que configura a direÃ§Ã£o da camera
void OrientaCamera(float ang) {
	dxcamera = sin(ang);
	dzcamera = -cos(ang);
	glLoadIdentity();
	gluLookAt(xcamera, ycamera, zcamera, xcamera + dxcamera, ycamera + dycamera, zcamera + dzcamera, 0.0f, 1.0f, 0.0f);
}

//funÃ§Ã£o que configura a posiÃ§Ã£o da camera
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
	if (zcamera<90.0f && zcamera>-90.0f)
		zcamera = zcamera + direcao*(dzcamera)*0.7;
	if (antemusica != 0) {
		if (amusica == 0) {
			controle2 = 1;
			amusica = 1;
		}
		if (xcamera>-45 && xcamera<45 && zcamera<75 && zcamera>-75) {
			controle = 1;
			if (strcmp(MUSICA, "b.mp3") == 0)
				controle2 = 1;
		}
		else {
			controle = 2;
			if (strcmp(MUSICA, "a.mp3") == 0)
				controle2 = 1;
		}
		if (controle == 1)
			strcpy(MUSICA, "a.mp3");
		else
			strcpy(MUSICA, "b.mp3");
		toca();
	}
	glLoadIdentity();
	gluLookAt(xcamera, ycamera, zcamera, xcamera + dxcamera, ycamera + dycamera, zcamera + dzcamera, 0.0f, 1.0f, 0.0f);
	GLfloat posicaocamera[4] = { xcamera,ycamera,zcamera,1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, posicaocamera);
}

//funÃ§Ã£o que trata eventos do teclado normal
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
		case 43:  //+
			quant += 0.1f;
			if (quant>1.0) quant = 1.0f;
			glLightfv(GL_LIGHT1, GL_DIFFUSE, luzdifusa);
			break;
		case 45:  //-
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
			antemusica = 1;
			MoveCamera(1);
			GLfloat luzdifusa[4] = { quant, quant, quant, 1.0 };
			luzdifusa[0] = quant;
			luzdifusa[1] = quant;
			luzdifusa[2] = quant;
			glLightfv(GL_LIGHT1, GL_DIFFUSE, luzdifusa);
			/*case 13 :
			switch (mostramenu){
			case MENU1:
			angulo=0.0f;
			rota_paquito=0.0f;
			xcamera=0.0f;
			ycamera=5.0f;
			zcamera=30.0f;
			dxcamera=0.0f;
			dycamera=0.0f;
			dzcamera=-20.0f;
			quant=0.4f;
			cmenu = 1;
			antemusica=1;
			MoveCamera(1);
			luzdifusa[0] =quant;
			luzdifusa[1] =quant;
			luzdifusa[2] =quant;
			glLightfv(GL_LIGHT1, GL_DIFFUSE, luzdifusa);

			break;
			case MENU2:
			mostramenu = OPCAO;
			menu();
			glutSwapBuffers();
			break;
			case MENU3:
			exit(0);
			break;
			case OPCAO:
			mostramenu = MENU1;
			menu();
			glutSwapBuffers();
			break;
			}
			break;
			case 'q':
			if(mostramenu==OPCAO){
			mostramenu=MENU1;
			menu();
			glutSwapBuffers();
			}*/
		}
	}
}

//funÃ§Ã£o que trata os eventos de teclas especiais
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
	}/*else{
	 switch (key){
	 case GLUT_KEY_UP :
	 if(mostramenu == MENU2)
	 mostramenu = MENU1;
	 if(mostramenu == MENU3)
	 mostramenu = MENU2;
	 menu();
	 glutSwapBuffers();
	 break;
	 case GLUT_KEY_DOWN :
	 if(mostramenu == MENU2)
	 mostramenu = MENU3;
	 if(mostramenu == MENU1)
	 mostramenu = MENU2;
	 menu();
	 glutSwapBuffers();
	 break;
	 }
	 }*/
}

//funÃ§Ã£o que configura o redimensionamento de janela
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

//funÃ§Ã£o que inicializa o programa, nela sÃ£o configuradas as luzes do programa e as texturas que serÃ£o utilizadas
void Inicializa() {
	toca();

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

	glEnable(GL_COLOR_MATERIAL);                                           //habilita o uso de configuraÃ§Ã£o de materiais
	glEnable(GL_LIGHTING);                      						   //habilita iluminaÃ§Ã£o
	glEnable(GL_LIGHT0);												   //habilita as diversas luzes
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_DEPTH_TEST);                                               //habilita teste de profundidade

	glEnable(GL_TEXTURE_2D);                                            //habilita texturas 2d e elas sÃ£o configuradas
	glGenTextures(1, texturas);

	texturas[AREIA] = SOIL_load_OGL_texture("textura/areia.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[TRAVE] = SOIL_load_OGL_texture("textura/branco.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[REDE] = SOIL_load_OGL_texture("textura/rede.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[LINHA] = SOIL_load_OGL_texture("textura/branco.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[CEU] = SOIL_load_OGL_texture("textura/ceu.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[CEU2] = SOIL_load_OGL_texture("textura/ceu2.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[CEU3] = SOIL_load_OGL_texture("textura/ceu3.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[BOLA] = SOIL_load_OGL_texture("textura/arquibancada.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[ARQUIBANCADA] = SOIL_load_OGL_texture("textura/arquibancada.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[PUBLICIDADE] = SOIL_load_OGL_texture("textura/adboard.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[PLACA] = SOIL_load_OGL_texture("textura/placa.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[CADEIRA] = SOIL_load_OGL_texture("textura/cadeira.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[PAQUITO1] = SOIL_load_OGL_texture("textura/paquito1.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[PAQUITO2] = SOIL_load_OGL_texture("textura/paquito2.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[PLACAR] = SOIL_load_OGL_texture("textura/placar.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[GUARDASOL] = SOIL_load_OGL_texture("textura/guardasol.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[VERDE] = SOIL_load_OGL_texture("textura/verde.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[AZUL] = SOIL_load_OGL_texture("textura/azul.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[MENU1] = SOIL_load_OGL_texture("textura/menu1.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[MENU2] = SOIL_load_OGL_texture("textura/menu2.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[MENU3] = SOIL_load_OGL_texture("textura/menu3.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[OPCAO] = SOIL_load_OGL_texture("textura/opcao.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	texturas[SNOW] = SOIL_load_OGL_texture("textura/snow.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

}

//funÃ§Ã£o que desenha o gol, modelado atraves de quadricas e planos
void gol() {
	glPushMatrix();                                                //cilindros que sÃ£o as traves do gol
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj *quad;
	quad = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texturas[TRAVE]);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);
	gluCylinder(quad, 0.5, 0.5, 15.0, 10.0, 10.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.0f, 0.0f, 0.0f);
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj *quad2;
	quad2 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texturas[TRAVE]);
	gluQuadricNormals(quad2, GLU_SMOOTH);
	gluQuadricTexture(quad2, GL_TRUE);
	gluCylinder(quad2, 0.5, 0.5, 15.0, 10.0, 10.0);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.0f, 14.5f, 0.0f);
	glRotatef(90, 0.0, 1.0, 0.0);
	GLUquadricObj *quad3;
	quad3 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texturas[TRAVE]);
	gluQuadricNormals(quad3, GLU_SMOOTH);
	gluQuadricTexture(quad3, GL_TRUE);
	gluCylinder(quad3, 0.5, 0.5, 20.0, 10.0, 10.0);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texturas[REDE]);
	//planos que modelam a rede do gol
	glPushMatrix();
	glTranslatef(-10.0f, 15.0f, -3.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, 0.0f, -3.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, 0.0f, 3.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, 0.0f, 3.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, 0.0f, -3.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 15.0f, -6.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -12.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 15.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 15.0f, -6.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -12.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -12.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-20.0f, 0.0f, -12.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-20.0f, 15.0f, -6.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 15.0f, -6.0f);
	glEnd();
	glPopMatrix();
}

//funÃ§Ã£o que desenha as linhas que definem o campo de jogo
void campo() {
	glBindTexture(GL_TEXTURE_2D, texturas[LINHA]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, 59.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-40.0f, 0.1f, 59.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-40.0f, 0.1f, 60.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, 60.5f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0f, 0.1f, -59.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-40.0f, 0.1f, -59.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-40.0f, 0.1f, -60.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.1f, -60.5f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(39.0f, 0.1f, -60.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(40.0f, 0.1f, -60.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(40.0f, 0.1f, 60.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(39.0f, 0.1f, 60.0f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-39.0f, 0.1f, -60.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-40.0f, 0.1f, -60.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-40.0f, 0.1f, 60.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-39.0f, 0.1f, 60.0f);
	glEnd();
}

//funÃ§Ã£o que desenha o cenario, ceu e mar
void cenario() {
	glBindTexture(GL_TEXTURE_2D, texturas[CEU]);             //planos que definem os "horizontes" da cena
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-400.0f, 0.0f, -400.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-400.0f, 1000.0f, -400.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(400.0f, 1000.0f, -400.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(400.0f, 0.0f, -400.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texturas[CEU3]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-400.0f, 0.0f, 400.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-400.0f, 1000.0f, 400.0f);
	glTexCoord2f(0.5f, 1.0f); glVertex3f(400.0f, 1000.0f, 400.0f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(400.0f, 0.0f, 400.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texturas[CEU2]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-400.0f, 0.0f, 400.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-400.0f, 1000.0f, 400.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-400.0f, 1000.0f, -400.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-400.0f, 0.0f, -400.0f);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(400.0f, 0.0f, 400.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(400.0f, 1000.0f, 400.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(400.0f, 1000.0f, -400.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(400.0f, 0.0f, -400.0f);
	glEnd();
}

//funÃ§Ã£o que desenha a arquibancada, modelada atraves varios planos
void arquibancada() {
	glBindTexture(GL_TEXTURE_2D, texturas[ARQUIBANCADA]);         //varios planos que definem o formato da arquibancada
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 4.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 4.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 4.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 4.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 8.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 8.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 8.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 8.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 12.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 12.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 12.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 12.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 4.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 4.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0f, 4.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 4.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 4.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.0f, 8.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 4.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 4.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 12.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 12.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 4.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 4.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 8.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 8.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 12.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 12.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 10.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 4.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 4.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 8.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 8.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(4.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 12.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 12.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();
}

//funÃ§Ã£o que desenha a bola, modelada atraves de quadrica
void jabulani() {
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

//funÃ§Ã£o que desenha as placas publicitarias, modeladas atraves de varios planos
/*void publicidade(){
glBindTexture(GL_TEXTURE_2D, texturas[PUBLICIDADE]);              //varios planos seguidos que contem as faces externas e internas das placas de publicidade
glPushMatrix();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(1.0f, 0.0f); glVertex3f(45.0f, 0.0f, 75.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(45.0f, 3.0f, 75.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(45.0f, 3.0f,-75.0f);
glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, 0.0f, -75.0f);
glEnd();
glPopMatrix();
glPushMatrix();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, 0.0f, 75.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-45.0f, 3.0f, 75.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-45.0f, 3.0f, 5.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.0f, 0.0f, 5.0f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, 0.0f, -5.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-45.0f, 3.0f, -5.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-45.0f, 3.0f,-75.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.0f, 0.0f, -75.0f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.0f, 0.0f, 75.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-45.0f, 3.0f, 75.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(45.0f, 3.0f, 75.0f);
glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, 0.0f, 75.0f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, 0.0f, -75.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-45.0f, 3.0f, -75.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(45.0f, 3.0f, -75.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(45.0f, 0.0f, -75.0f);
glEnd();
glPopMatrix();
glPopMatrix();glBindTexture(GL_TEXTURE_2D, texturas[PLACA]);
glPushMatrix();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(1.0f, 0.0f); glVertex3f(45.01f, 0.0f, 75.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(45.01f, 3.0f, 75.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(45.01f, 3.0f,-75.0f);
glTexCoord2f(0.0f, 0.0f); glVertex3f(45.01f, 0.0f, -75.0f);
glEnd();
glPopMatrix();
glPushMatrix();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.01f, 0.0f, 75.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-45.01f, 3.0f, 75.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-45.01f, 3.0f, 5.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.01f, 0.0f, 5.0f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.01f, 0.0f, -5.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-45.01f, 3.0f, -5.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-45.01f, 3.0f,-75.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.01f, 0.0f, -75.0f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-45.0f, 0.0f, 75.01f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-45.0f, 3.0f, 75.01f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(45.0f, 3.0f, 75.01f);
glTexCoord2f(0.0f, 0.0f); glVertex3f(45.0f, 0.0f, 75.01f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-45.0f, 0.0f, -75.01f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-45.0f, 3.0f, -75.01f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(45.0f, 3.0f, -75.01f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(45.0f, 0.0f, -75.01f);
glEnd();
glPopMatrix();
}*/

//funÃ§Ã£o que desenha o placar, modelado atraves de quadricas e plano
/*void placar(){
glBindTexture(GL_TEXTURE_2D, texturas[PLACA]);     //2 cilindros que sÃ£o a base do placar
glPushMatrix();
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad;
quad = gluNewQuadric();
gluQuadricNormals(quad, GLU_SMOOTH);
gluQuadricTexture(quad, GL_TRUE);
gluCylinder( quad, 0.5, 0.5, 40.0, 10.0, 10.0);
glPopMatrix();
glPushMatrix();
glTranslatef(-30.0f, 0.0f, 0.0f);
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad2;
quad2 = gluNewQuadric();
gluQuadricNormals(quad2, GLU_SMOOTH);
gluQuadricTexture(quad2, GL_TRUE);
gluCylinder( quad2, 0.5, 0.5, 40.0, 10.0, 10.0);
glPopMatrix();
glBindTexture(GL_TEXTURE_2D, texturas[PLACAR]);         //planos que contem a parte da frente e de tras do placar
glPushMatrix();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-30.0f, 20.0f, 0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-30.0f, 40.0f, 0.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 40.0f, 0.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 20.0f, 0.0f);
glEnd();
glPopMatrix();
glBindTexture(GL_TEXTURE_2D, texturas[PLACA]);
glPushMatrix();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-30.0f, 20.0f, -0.01f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-30.0f, 40.0f, -0.01f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 40.0f, -0.01f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 20.0f, -0.01f);
glEnd();
glPopMatrix();
}*/

//funÃ§Ã£o que desenha o outdoor do paquito que fica girando, modelado atraves de quadricas e plano
/*void paquito(){
glBindTexture(GL_TEXTURE_2D, texturas[PLACA]);     //cilindro que Ã© a base do outdoor
glPushMatrix();
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad;
quad = gluNewQuadric();
gluQuadricNormals(quad, GLU_SMOOTH);
gluQuadricTexture(quad, GL_TRUE);
gluCylinder( quad, 0.25, 0.25, 20.0, 10.0, 10.0);
glPopMatrix();
glPushMatrix();
glRotatef(rota_paquito, 0.0, 1.0, 0.0);
rota_paquito+=0.05;
if(rota_paquito > 360) rota_paquito=0;
glBindTexture(GL_TEXTURE_2D, texturas[PAQUITO1]);          //planos que contem as duas fotos de paquito
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-15.0f, 20.0f, 0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-15.0f, 40.0f, 0.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 40.0f, 0.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 20.0f, 0.0f);
glEnd();
glBindTexture(GL_TEXTURE_2D, texturas[PAQUITO2]);
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-15.0f, 20.0f, 0.01f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-15.0f, 40.0f, 0.01f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0f, 40.0f, 0.01f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0f, 20.0f, 0.01f);
glEnd();
glPopMatrix();
}*/

//funÃ§Ã£o que desenha o guarda sol, modelado atraves de quadricas e 6 triangulos
/*void guardasol(){
glBindTexture(GL_TEXTURE_2D, texturas[PLACA]);	    //cilindro que Ã© o eixo do guarda sol
glPushMatrix();
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad;
quad = gluNewQuadric();
gluQuadricNormals(quad, GLU_SMOOTH);
gluQuadricTexture(quad, GL_TRUE);
gluCylinder( quad, 0.05, 0.05, 10.0, 10.0, 10.0);
glPopMatrix();
glBindTexture(GL_TEXTURE_2D, texturas[GUARDASOL]);	    //varios triangulos que modelam o guarda sol
glBegin(GL_TRIANGLES);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(2.6f, 8.0f, 1.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(2.6f, 8.0f, -1.5f);
glEnd();
glBegin(GL_TRIANGLES);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(2.6f, 8.0f, 1.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 8.0f, 3.0f);
glEnd();
glBegin(GL_TRIANGLES);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.6f, 8.0f, 1.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 8.0f, 3.0f);
glEnd();
glBegin(GL_TRIANGLES);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.6f, 8.0f, 1.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.6f, 8.0f, -1.5f);
glEnd();
glBegin(GL_TRIANGLES);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 8.0f, -3.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-2.6f, 8.0f, -1.5f);
glEnd();
glBegin(GL_TRIANGLES);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 10.0f, 0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 8.0f, -3.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(2.6f, 8.0f, -1.5f);
glEnd();
}*/

//funÃ§Ã£o que desenha o toldo que cobre as cadeiras dos reservas, modelado atraves de quadricas e plano
/*void toldo(){
glPushMatrix();
glScalef(1,1,3.7);                          //planos que formam o objeto 3d que o toldo
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 10.0f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 10.0f, -4.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 10.0f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 10.0f, 0.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 10.3f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 10.3f, -4.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 10.3f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 10.3f, 0.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 10.3f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 10.0f, 0.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 10.0f, 0.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 10.3f, 0.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 10.3f, -4.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 10.0f, -4.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 10.0f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 10.3f, -4.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 10.3f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 10.0f, 0.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 10.0f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 10.3f, -4.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(3.5f, 10.3f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(3.5f, 10.0f, 0.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 10.0f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 10.3f, -4.5f);
glEnd();
glPopMatrix();
glBindTexture(GL_TEXTURE_2D, texturas[PLACA]);		//dois cilindros que sustentam o toldo
glPushMatrix();
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad;
quad = gluNewQuadric();
gluQuadricNormals(quad, GLU_SMOOTH);
gluQuadricTexture(quad, GL_TRUE);
gluCylinder( quad, 0.1, 0.1, 10.0, 10.0, 10.0);
glPopMatrix();
glPushMatrix();
glTranslatef(0.0f, 0.0f, -15.0f);
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad2;
quad2 = gluNewQuadric();
gluQuadricNormals(quad2, GLU_SMOOTH);
gluQuadricTexture(quad2, GL_TRUE);
gluCylinder( quad2, 0.1, 0.1, 10.0, 10.0, 10.0);
glPopMatrix();
}*/

//funÃ§Ã£o que desenha a cadeira, modelada atraves de quadricas e planos
/*void cadeira(){
glBindTexture(GL_TEXTURE_2D, texturas[CADEIRA]);    //sÃ£o desenhadas quatro cilindros que serao os pes da cadeira e tambem o "encosto"
glPushMatrix();
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad;
quad = gluNewQuadric();
gluQuadricNormals(quad, GLU_SMOOTH);
gluQuadricTexture(quad, GL_TRUE);
gluCylinder( quad, 0.05, 0.05, 4.0, 10.0, 10.0);
glPopMatrix();
glPushMatrix();
glTranslatef(1.0f, 0.0f, 0.0f);
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad2;
quad2 = gluNewQuadric();
gluQuadricNormals(quad2, GLU_SMOOTH);
gluQuadricTexture(quad2, GL_TRUE);
gluCylinder( quad2, 0.05, 0.05, 2.0, 10.0, 10.0);
glPopMatrix();
glPushMatrix();
glTranslatef(0.0f, 0.0f, -1.0f);
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad3;
quad3 = gluNewQuadric();
gluQuadricNormals(quad3, GLU_SMOOTH);
gluQuadricTexture(quad3, GL_TRUE);
gluCylinder( quad3, 0.05, 0.05, 4.0, 10.0, 10.0);
glPopMatrix();
glPushMatrix();
glTranslatef(1.0f, 0.0f, -1.0f);
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad4;
quad4 = gluNewQuadric();
gluQuadricNormals(quad4, GLU_SMOOTH);
gluQuadricTexture(quad4, GL_TRUE);
gluCylinder( quad4, 0.05, 0.05, 2.0, 10.0, 10.0);
glPopMatrix();
glBegin(GL_QUADS);                                  //planos que sÃ£o o assento e o encosto da cadeira
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f, 2.0f, 0.1f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, 2.0f, -1.1f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(1.1f, 2.0f, -1.1f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(1.1f, 2.0f, 0.1f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 3.0f, 0.1f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 3.0f, -1.1f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 4.0f, -1.1f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 4.0f, 0.1f);
glEnd();
}*/

//funÃ§Ã£o que desenha a mesa, modelada atraves de quadricas e planos
/*void mesa(){
glBindTexture(GL_TEXTURE_2D, texturas[GUARDASOL]);
glPushMatrix();
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad;
quad = gluNewQuadric();
gluQuadricNormals(quad, GLU_SMOOTH);
gluQuadricTexture(quad, GL_TRUE);
gluCylinder( quad, 0.1, 0.1, 3.0, 10.0, 10.0);
glPopMatrix();
glPushMatrix();
glTranslatef(3.0f, 0.0f, 0.0f);
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad2;
quad2 = gluNewQuadric();
gluQuadricNormals(quad2, GLU_SMOOTH);
gluQuadricTexture(quad2, GL_TRUE);
gluCylinder( quad2, 0.1, 0.1, 3.0, 10.0, 10.0);
glPopMatrix();
glPushMatrix();
glTranslatef(0.0f, 0.0f, -4.0f);
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad3;
quad3 = gluNewQuadric();
gluQuadricNormals(quad3, GLU_SMOOTH);
gluQuadricTexture(quad3, GL_TRUE);
gluCylinder( quad3, 0.1, 0.1, 3.0, 10.0, 10.0);
glPopMatrix();
glPushMatrix();
glTranslatef(3.0f, 0.0f, -4.0f);
glRotatef(90, 0.0, 1.0, 0.0);
glRotatef(-90, 1.0, 0.0, 0.0);
GLUquadricObj *quad4;
quad4 = gluNewQuadric();
gluQuadricNormals(quad4, GLU_SMOOTH);
gluQuadricTexture(quad4, GL_TRUE);
gluCylinder( quad4, 0.1, 0.1, 3.0, 10.0, 10.0);
glPopMatrix();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 3.0f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 3.0f, -4.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 3.0f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 3.0f, 0.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 3.3f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 3.3f, -4.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 3.3f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 3.3f, 0.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 3.3f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 3.0f, 0.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 3.0f, 0.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 3.3f, 0.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 3.3f, -4.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 3.0f, -4.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 3.0f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 3.3f, -4.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 3.3f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 3.0f, 0.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 3.0f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 3.3f, -4.5f);
glEnd();
glBegin(GL_QUADS);
glNormal3f(0, 1, 0);
glTexCoord2f(0.0f, 0.0f); glVertex3f(3.5f, 3.3f, 0.5f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(3.5f, 3.0f, 0.5f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(3.5f, 3.0f, -4.5f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(3.5f, 3.3f, -4.5f);
glEnd();
}*/

//funÃ§Ã£o que configura os materiais dos objetos que serao chamados para serem desenhados
void Desenha() {

	GLfloat espec_grama[4] = { 0.7, 0.7, 0.7, 1.0 };
	GLint especMaterial = 100;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glBindTexture(GL_TEXTURE_2D, texturas[VERDE]);
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
	glPushMatrix();
	glTranslatef(7.0f, 0.0f, -60.0f);
	glScalef(0.7, 0.7, 0.7);
	//gol();
	glPopMatrix();
	espec_grama[1] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(-7.0f, 0.0f, 60.0f);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.7, 0.7, 0.7);
	//gol();
	glPopMatrix();
	//campo();
	cenario();//TIRAR DEPOIS
	jabulani();
	espec_grama[2] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(50.0f, 0.0f, 0.0f);
	glScalef(1, 1, 5);
	//arquibancada();
	glPopMatrix();
	//publicidade();
	espec_grama[0] = 0.0;
	espec_grama[2] = 0.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(15.0f, 0.0f, -80.0f);
	//placar();
	glPopMatrix();
	espec_grama[1] = 0.5;
	glMaterialfv(GL_FRONT, GL_AMBIENT, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 80.0f);
	//paquito();
	glPopMatrix();
	double z = 0, i;
	for (i = 0; i<10; i++) {
		glPushMatrix();
		glTranslatef(-50.0f, 0.0f, z + -10.0f);
		//cadeira();
		glPopMatrix();
		z -= 2.5;
	}
	z = 0;

	for (i = 0; i<10; i++) {
		glPushMatrix();
		glTranslatef(-50.0f, 0.0f, z + 11.1f);
		//cadeira();
		glPopMatrix();
		z += 2.5;
	}
	espec_grama[0] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(-55.0f, 0.0f, 2.0f);
	//mesa();
	glPopMatrix();
	espec_grama[0] = 0.5;
	espec_grama[1] = 0.5;
	espec_grama[2] = 0.5;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(-57.0f, 0.0f, -0.5f);
	//cadeira();
	glPopMatrix();
	espec_grama[0] = 0.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(-57.0f, 0.0f, 1.5f);
	//cadeira();
	glPopMatrix();
	espec_grama[2] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(-53.5f, 0.0f, 0.0f);
	glScalef(1.7, 1, 1.7);
	//guardasol();
	glPopMatrix();
	espec_grama[1] = 0.3;
	espec_grama[2] = 0.2;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glBindTexture(GL_TEXTURE_2D, texturas[AZUL]);
	glPushMatrix();
	glTranslatef(-51.0f, 0.0f, 31.0f);
	glScalef(1, 1, 1.55);
	//toldo();
	glPopMatrix();
	espec_grama[0] = 0.1;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glBindTexture(GL_TEXTURE_2D, texturas[VERDE]);
	glPushMatrix();
	glTranslatef(-51.0f, 0.0f, -8.0f);
	glScalef(1, 1, 1.55);
	//toldo();
	glPopMatrix();
	espec_grama[3] = 0.7;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(-70.0f, 0.0f, -27.0f);
	glRotatef(180, 0, 1, 0);
	glScalef(1, 1, 2);
	//arquibancada();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, espec_grama);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glPushMatrix();
	glTranslatef(-70.0f, 0.0f, 27.0f);
	glRotatef(180, 0, 1, 0);
	glScalef(1, 1, 2);
	//arquibancada();
	glPopMatrix();
	//if(cmenu==0){
	//glBindTexture(GL_TEXTURE_2D, texturas[PLACAR]);
	//menu();
	//}
	glutSwapBuffers();

}

//funÃ§Ã£o principal do programa
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



