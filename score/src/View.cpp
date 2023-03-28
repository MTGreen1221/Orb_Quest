#include "View.h"
#include <stdlib.h>
#include <math.h>

void View :: init_lighting_and_depth_test() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float light_Ka[] = {0.1,0.1,0.1,1.0};
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
	float light_position[] = {camerax, cameray, cameraz};
	float light_Kd[] = {0.5,0.5,0.5,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION, light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, light_Kd);
	quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
}
/** Clear screen, set background color, set up viewing box and
 * camera position */
void View:: setup_draw(float xy_aspect) {
	glClearColor(.9f, .9f, .9f, 1.0f); // set background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION); // Set up scene
	glLoadIdentity();

	// left right bottom top of virtual 2D world
	gluOrtho2D(0.0, 100.0, 0.0, 100.0); // Write on 2D surface, distance immaterial
}
void View :: draw_2D_objects() {
	/*glMatrixMode(GL_MODELVIEW); // Get READY TO DRAW
	glLoadIdentity();
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS); // draw points counter clockwise

	glVertex2f(10, 10);

	glVertex2f(30, 10);

	glVertex2f(30, 30);

	glVertex2f(10, 30);
	glEnd();
	glColor3f(0.5, 0, 0.5);
	glBegin(GL_TRIANGLES); // draw points counter clockwise

	glVertex2f(30, 30);

	glVertex2f(40, 45);

	glVertex2f(50, 30);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);

	glVertex2f(30, 30);

	glVertex2f(20, 50);

	glVertex2f(30, 70);

	glVertex2f(50, 80);

	glVertex2f(70, 70);

	glVertex2f(80, 50);

	glVertex2f(70, 30);

	glVertex2f(50, 20);
	glEnd();*/
}
void View :: draw_3D_objects()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-150,150,-150,150,-150,150);
    gluLookAt(camerax+playerx,cameray+playery,cameraz+playerz,
    playerx,playery,playerz,
    0,1,0);
    draw_shapes();
}
void View :: draw_shapes()
{
    glMatrixMode(GL_MODELVIEW);
    float material_ground[] = {0.1,1.0,0.1,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_ground);
    glPushMatrix();
    //floor
    glTranslatef(0,-50,0);
    glScalef(5,1,5);
    glNormal3f(0,1,0);
    glutSolidCube(25);
    glPopMatrix();
    //player
    float material_player[] = {0.1,0.1,1.0,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_player);
    glPushMatrix();
    glTranslatef(playerx,-21,playerz);
    gluSphere(quad, 15, 15,15);
    float material_sash[] = {1.0,0.1,0.1,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_sash);
    gluCylinder(quad, 15,15,5,15,5);
    glPopMatrix();
    glPushMatrix();
    //wall
    glTranslatef(60,13.5,0);
    glScalef(.25,4,5);
    float material_wall[] = {1.0,0.1,1.0,1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_wall);
    glNormal3f(1,0,0);
    glutSolidCube(25);
    glPopMatrix();
    glPushMatrix();
    //enemy
    glColor3f(0,0,0);
    glTranslatef(npcx,npcy,npcz);
    glRotatef(90,-1,0,0);
    gluCylinder(quad, 15,0,15,15,15);
    glPopMatrix();
    glFlush();
}
void View :: moveEnemies(){
    if(timeing < 10){
        npcx++;
        timeing++;
    }
    else if(timeing < 20){
        npcz++;
        timeing++;
    }
    else if(timeing < 30){
        npcx--;
        timeing++;
    }
    else if(timeing < 40){
        npcz--;
        timeing++;
    }
    else{
        timeing = 0;
    }
}
void View :: movePlayerx(int x){
    playerx+= x;
}
void View :: movePlayerz(int z){
    playerz+= z;
}
void View :: score_change(int i)
{
	score = score + i;
}
void View::ammo_change(int i)
{
	if (ammo + i <= 8 && ammo + i >= 0) {
		ammo = ammo + i;
	}
}
void View :: draw_score()
{

	char* buff = (char*)malloc(10 * sizeof(char)
	);

	glColor3f(0, 0, 0);

	draw_string(60, 85, 0, "Ammo:", GLUT_BITMAP_9_BY_15);

	draw_ammo();

	sprintf(buff, "Score: %d", score);

	glColor3f(0, 0, 0);

	draw_string(60, 90, 0, buff, GLUT_BITMAP_9_BY_15);
}
void View::draw_ammo() {
	glMatrixMode(GL_MODELVIEW); // Get READY TO DRAW
	glLoadIdentity();
	glColor3f(0, 0, 0);
	for (int i = 0; i < ammo; i++) {
		const GLfloat vert1[2] = { 0,0 };
		const GLfloat vert2[2] = { 2,1 };
		const GLfloat vert3[2] = { 0,2 };
		glTranslatef(75+i*3, 85, 0);//hope this counts

		glBegin(GL_TRIANGLES);

		glVertex2fv(vert1);

		glVertex2fv(vert2);

		glVertex2fv(vert3);
		glEnd();

		glTranslatef(-75-i*3, -85, 0);
	}
}
void View :: draw_string(float x, float y, float z, char* string, void* currentFont)
{
	glRasterPos3f(x, y, z);

	for (char* c = string; *c != '\0'; c++)
	{

		glutBitmapCharacter(currentFont, *c);

	}
}
void View :: cameraLeft(int x){
    camerax-= x;
}
void View :: cameraRight(int x){
    camerax+= x;
}
void View :: cameraForward(int x){
    cameraz+= x;
}
void View :: cameraBack(int x){
    cameraz-= x;
}
void View :: cameraMoveUp(int x){
    cameray+= x;
}
void View :: cameraMoveDown(int x){
    cameray-= x;
}
void View :: cameraRotateLeft(int x){
    camerax = camerax*cos(x/57.2958) + cameraz*(-sin(x/57.2958));
    cameraz = camerax*sin(x/57.2958) + cameraz*cos(x/57.2958);
}
void View :: cameraRotateRight(int x){
    camerax = camerax*cos(x/57.2958) + cameraz*sin(x/57.2958);
    cameraz = camerax*(-sin(x/57.2958)) + cameraz*cos(x/57.2958);
}
void View :: turnOnLights(){
    glEnable(GL_LIGHTING);
}
void View :: turnOffLights(){
    glDisable(GL_LIGHTING);
}
void View::draw_object(float xy_aspect, float rotationX, float rotationY) {

	setup_draw(xy_aspect);

	draw_2D_objects();

	draw_score();

	draw_3D_objects();

	glutSwapBuffers();

}
