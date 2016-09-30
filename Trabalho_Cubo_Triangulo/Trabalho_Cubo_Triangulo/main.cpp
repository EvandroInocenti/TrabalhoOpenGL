#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float angulo, aspecto;			 //gluPerspective
float zNear = 0.1, zFar = 500;   //gluPerspective
int posX = 0, posY = 0, posZ = 300; //Parâmetros da gluLookAt
float transladaX = 0, transladaY = 0, transladaZ = 0;
float rotacionaX = 0, rotacionaY = 0, rotacionaZ = 0;
float escala = 1;

float angRotacao = 10;

void visualizacao() {
	glMatrixMode(GL_PROJECTION);	//Matriz de projeção
	glLoadIdentity();				//Zera transformações
	//Configura perspectiva
	gluPerspective(angulo, aspecto, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);		//Muda p/matriz de visualização
	glLoadIdentity();				//Zera transformações
	gluLookAt(posX, posY, posZ,		//Configura câmera
		0, 0, 0,	//Para onde a câmera aponta na cena
		0, 1, 0);	//Vetor 'up'
}
void teclado(unsigned char key, int x, int y) {

	switch (key) {
		case 27:	//Tecla ESC
			exit(0);
			break;
		case 'a':
			//move para a direita
			transladaX += 1.5;
			break;
		case 'd':
			//move para a esquerda
			transladaX -= 1.5;
			break;
		case 's':
			//move para a cima
			transladaY += 1.5;
			break;
		case 'w':
			//move para baixo
			transladaY -= 1.5;
			break;
		case 'z':
			if (escala >= 0.0)
				escala += 0.1;
			break;
		case 'x':
			escala -= 0.1;
			if (escala <= 0)
			escala = 0.0;
			break;
		default:
			break;
	}
	visualizacao();			//Método que aplica os novos parâmetros
	glutPostRedisplay();	//Força redesenho
}

void teclasEspeciais(int tecla, int x, int y){
	switch (tecla){
		case GLUT_KEY_UP:
			rotacionaX = 1;
			rotacionaY = 0;
			rotacionaZ = 0;
			angRotacao += 10.0;
			break;
		case GLUT_KEY_DOWN:
			rotacionaX = 1;
			rotacionaY = 0;
			rotacionaZ = 0;
			angRotacao -= 10.0;
			printf("\n o valor da translacao e %.2f\n", rotacionaY);
			break;
		case GLUT_KEY_LEFT:
			rotacionaX = 0;
			rotacionaY = 1;
			rotacionaZ = 0;
			angRotacao += 10.0;
			break;
		case GLUT_KEY_RIGHT:
			rotacionaX = 0;
			rotacionaY = 1;
			rotacionaZ = 0;
			angRotacao -= 10.0;
		default:
			break;
	}	
	visualizacao();
	glutPostRedisplay();
}

void tamanhoJanela(int w, int h) { //w: width (comprimento)|h: height (altura)
	if (h == 0) { h = 1; }	//Evita divisão por zero
	glViewport(0, 0, w, h);	//Redefine o viewport para o tamanho da janela
	aspecto = (float)w / (float)h;	//Calcula o 'aspect ratio'
	visualizacao();			//Aplica os novos parâmetros de visualização
}

void cubo(){
	glPushMatrix(); // salva as transformações atuais na pilha
	glTranslatef(50, 0, 0);
	glRotated(angRotacao, rotacionaX, rotacionaY, rotacionaZ);
	glColor3f(0.3, 0.3, 0.6);
	glBegin(GL_QUADS);
	/*## Verso EHGF ##*/
	glVertex3i(80, 40, -40);
	glVertex3i(80, -40, -40);
	glVertex3i(0, -40, -40);
	glVertex3i(0, 40, -40);

	/*## Direita DCHE ##*/
	glVertex3i(80, 40, 40);
	glVertex3i(80, -40, 40);
	glVertex3i(80, -40, -40);
	glVertex3i(80, 40, -40);
	
	/*## Esquerda FGBA ##*/
	glVertex3i(0, 40, -40);
	glVertex3i(0, -40, -40);
	glVertex3i(0, -40, 40);
	glVertex3i(0, 40, 40);

	/*## superior ADEF ##*/
	glVertex3i(0, 40, 40);
	glVertex3i(80, 40, 40);
	glVertex3i(80, 40, -40);
	glVertex3i(0, 40, -40);

	/*## Inferior BCHG ##*/
	glVertex3i(0, -40, 40);
	glVertex3i(80, -40, 40);
	glVertex3i(80, -40, -40);
	glVertex3i(0, -40, -40);
	
	/*## Frente ABCD ##*/
	glVertex3i(0, 40, 40);
	glVertex3i(0, -40, 40);
	glVertex3i(80, -40, 40);
	glVertex3i(80, 40, 40);
	glEnd();
	glPopMatrix(); // restaura as transformações anteriores
}

void triangulo(){

	glPushMatrix();
	glTranslatef(transladaX -50, transladaY, transladaZ);
	//glRotated(angRotacao, rotacionaX, rotacionaY, rotacionaZ);

	glBegin(GL_TRIANGLES);
	/*### Verso ABC ##*/
	glColor3f(1.0f, 0.0f, 0.0f); //Vermelho
	glVertex3i(-20, 40, 0);
	glColor3f(0.0f, 0.0f, 1.0f); //Azul
	glVertex3i(-40, -20, -20);
	glColor3f(0.0f, 1.0f, 0.0f); //Verde
	glVertex3i(0, -20, -20);

	/*### Lateral Esquerda ABE ##*/
	glColor3f(1.0f, 0.0f, 0.0f); //Vermelho
	glVertex3i(-20, 40, 0);
	glColor3f(0.0f, 0.0f, 1.0f); //Azul
	glVertex3i(-40, -20, -20);
	glColor3f(0.0f, 1.0f, 0.0f); //Verde
	glVertex3i(-40, -20, 20);

	/*### Lateral direita ACD ##*/
	glColor3f(1.0f, 0.0f, 0.0f); //Vermelho
	glVertex3i(-20, 40, 0);
	glColor3f(0.0f, 1.0f, 0.0f); //Verde
	glVertex3i(0, -20, -20);
	glColor3f(0.0f, 0.0f, 1.0f); //Azul
	glVertex3f(0, -20, 20);

	/*### Frente AED ##*/
	glColor3f(1.0f, 0.0f, 0.0f); //vermelho
	glVertex3i(-20, 40, 0);
	glColor3f(0.0f, 1.0f, 0.0f); //Verde
	glVertex3i(-40, -20, 20);
	glColor3f(0.0f, 0.0f, 1.0f); //Azul
	glVertex3f(0, -20, 20);
	glEnd();
	glPopMatrix();
}

void desenha() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0);//Define cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);		//Limpa tela
	glScalef(escala, escala, escala);
	cubo();
	triangulo();
	glutSwapBuffers();					//Renderiza
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);			//Inicializa biblioteca GLUT
	glutInitWindowSize(1200,800);	//Define tamanho da janela
	glutInitWindowPosition(50, 50);	//Define posição inicial da janela
	glutCreateWindow("CG - Trabalho Cubo/Triângulo");//Cria janela
	angulo = 45;	//Campo de visão (eixo y) inicial é de 45 graus
	glutDisplayFunc(desenha);		//Função callback de redesenho
	glutReshapeFunc(tamanhoJanela);	//Callback quando tamanho janela alterado
	glutKeyboardFunc(teclado);		//Callback para tratamento de teclado
	glutSpecialFunc(&teclasEspeciais); 
	glutMainLoop();					//Loop do GLUT
}