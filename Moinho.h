void moinho() {

	//Cilindro Base do moinho
	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj *quad;
	quad = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texturas[AREIA]);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);
	gluCylinder(quad, 1.2, 0.9, 15.0, 10.0, 10.0);
	glPopMatrix();


	//Cone do moinho
	glPushMatrix();
	glTranslatef(0, 15.0f, 0.0f);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj *quad2;
	quad2 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texturas[GUARDASOL]);
	gluQuadricNormals(quad2, GLU_SMOOTH);
	gluQuadricTexture(quad2, GL_TRUE);
	glutSolidCone(1.5, 1, 15, 15);
	glPopMatrix();

	//Cilindro Eixo das pás do moinho
	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj *quad3;
	quad3 = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, texturas[PLACA]);
	gluQuadricNormals(quad3, GLU_SMOOTH);
	gluQuadricTexture(quad3, GL_TRUE);
	gluCylinder(quad, 1.2, 0.9, 15.0, 10.0, 10.0);
	glPopMatrix();




}
#pragma once
