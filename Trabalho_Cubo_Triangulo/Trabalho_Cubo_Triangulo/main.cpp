#include <gl/freeglut.h>

float angulo, aspecto;			 //gluPerspective
float zNear = 0.1, zFar = 500;   //gluPerspective
int posX = 0, posY = 0, posZ = 400; //Parâmetros da gluLookAt
int transladaX = 0, transladaY = 0, transladaZ = 0;

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
		exit(0); break;

	case 'a':
		//move para a direita
		transladaX = +1.5;
		transladaY = 0;
		break;
	case 'd':
		//move para a esquerda
		transladaX = -1.5;
		transladaY = 0;
		break;
	case 's':
		//move para a cima
		transladaY = +1.5;
		transladaX = 0;
		break;
	case 'w':
		//move para baixo
		transladaY = -1.5;
		transladaX = 0;
		break;
	}
	visualizacao();			//Método que aplica os novos parâmetros
	glutPostRedisplay();	//Força redesenho
}

void teclasEspeciais(int tecla, int x, int y){


}

void tamanhoJanela(int w, int h) { //w: width (comprimento)|h: height (altura)
	if (h == 0) { h = 1; }	//Evita divisão por zero
	glViewport(0, 0, w, h);	//Redefine o viewport para o tamanho da janela
	aspecto = (float)w / (float)h;	//Calcula o 'aspect ratio'
	visualizacao();			//Aplica os novos parâmetros de visualização
}

void cubo(){

	glColor3f(0.3, 0.3, 0.6);
	glBegin(GL_QUADS);
	glVertex3f(30, -20, 30);
	glVertex3f(30, 50, 30);
	glVertex3f(110, 50, 30);
	glVertex3f(110, -20, 30);
	glEnd();
}

void triangulo(){

	glPopMatrix();
	glTranslatef(transladaX, transladaY, transladaZ);
	glBegin(GL_TRIANGLES);
	/*###  AED ##*/
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3i(0, 50, 0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3i(-30, -20, 0);
	glColor3f(0.0f, 0.0f, 1.0f);     
	glVertex3f(30, -20, 0);
	
	/*###  ADC ##*/
	glColor3f(1.0f, 0.0f, 0.0f);     
	glVertex3i(0, 50, 0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3i(30, -20, 0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3i(20, 10, -10);
	
	/*###  ACB ##*/
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3i(0, 50, 0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3i(20, 10, -10);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3i(-40, 10, -10);
	
	/*###  ABE ##*/
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3i(0, 50, 0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3i(-40, 10, -10);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3i(-30, -20, 0);
	glEnd();
	glPushMatrix();
}

void desenha() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0);//Define cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);		//Limpa tela
	//cubo();
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
	glutKeyboardFunc(&teclado);		//Callback para tratamento de teclado
	glutSpecialFunc(&teclasEspeciais); 
	glutMainLoop();					//Loop do GLUT
}