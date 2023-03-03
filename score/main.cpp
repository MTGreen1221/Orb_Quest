
// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "View.h"
float xy_aspect;
int last_x, last_y;
float rotationX = 0.0, rotationY = 0.0;
int main_window;View v;
void myGlutKeyboard(unsigned char Key, int x, int y){
	switch (Key) {
	// A few keys here to test the sync_live capability.
        case 'q':
            v.cameraLeft();
            break;
        case 'e':
            v.cameraRight();
            break;
        case 'a':
            v.movePlayerx(-1);
            break;
        case 'd':
            v.movePlayerx(1);
            break;
        case 'w':
            v.movePlayerz(1);
            break;
        case 's':
            v.movePlayerz(-1);
			break;
		case 'j':
			v.score_change(1);
			v.ammo_change(-1);
			break;
		case 'z':
			v.ammo_change(-1);
			break;
		case 'x':
			v.ammo_change(1);
			break;
        case 'k':
            if(glIsEnabled(GL_LIGHTING)){
                v.turnOffLights();
            }
            else{
                v.turnOnLights();
            }
			break;
		//case 'w':
			// Toggle wireframe mode
			//wireframe = !wireframe;
			//GLUI_Master.sync_live_all();
			break;
		case 27:
		case 'p':
			exit(0);
			break;
	};
	glutPostRedisplay();
	// call draw function
}
/***************************************** myGlutMenu() ***********/
void myGlutMenu(int value){
	myGlutKeyboard(value, 0, 0);
}
/***************************************** myGlutMouse() **********/
void myGlutMouse(int button, int button_state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN) {
		last_x = x; last_y = y;
	}
}
/***************************************** myGlutMotion() **********/
void myGlutMotion(int x, int y){
	rotationX += (float)(y - last_y);
	rotationY += (float)(x - last_x);
	last_x = x;
	last_y = y;
	glutPostRedisplay();
}
/**************************************** myGlutReshape() *************/
void myGlutReshape(int x, int y){
	printf("window dimensions x %d y %d", x, y);
	xy_aspect = (float)x / (float)y;
	glViewport(0, 0, x, y); glutPostRedisplay();
}
/***************************************** myGlutDisplay() *****************/
void myGlutDisplay(){
	v.draw_object(xy_aspect, rotationX, rotationY);
}
void myIdle(){
    v.moveEnemies();
    glutPostRedisplay();
}
int main(int argc, char* argv[]){
	/****************************************/
	/* Initialize GLUT and create window */
	/****************************************/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(300, 300);
	main_window = glutCreateWindow("2D Virtual World With Flat Colors");
	glutDisplayFunc(myGlutDisplay);
	glutReshapeFunc(myGlutReshape);
	glutKeyboardFunc(myGlutKeyboard);
	glutMotionFunc(myGlutMotion);
	glutMouseFunc(myGlutMouse);
	glutIdleFunc(myIdle);
	/****************************************/
	/* Set up OpenGL lights */
	/* Enable z-buferring */
	/****************************************/
	v.init_lighting_and_depth_test();
	glutMainLoop();
	return EXIT_SUCCESS;
}
