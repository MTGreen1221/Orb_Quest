#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <string.h>

#ifndef VIEW_H
#define VIEW_H

class View {

public:
    //float material_Kd;
    int timeing = 0;
	int score = 0;
	int ammo = 8;
	GLUquadric * quad;
	int npcx = 0;
	int npcy = 0;
	int npcz = 0;
	int playerx = 0;
	int playery = 0;
	int playerz = 0;
	float camerax = -20;
	float cameray = 10;
	float cameraz = 20;
	void score_change(int x);
	void ammo_change(int x);
	void draw_string(float x, float y, float z, char* string, void* currentFont);
	void init_lighting_and_depth_test();
	void setup_draw(float xy_aspect);
	void draw_2D_objects();
	void draw_object(float xy_aspect, float rotationX, float rotationY);
	void draw_3D_objects();
	void draw_shapes();
	void draw_score();
	void draw_ammo();
	void cameraLeft(int x);
	void cameraRight(int x);
	void cameraMoveUp(int x);
	void cameraMoveDown(int x);
	void cameraForward(int x);
	void cameraBack(int x);
	void cameraRotateLeft(int x);
	void cameraRotateRight(int x);
	void moveEnemies();
	void movePlayerx(int x);
	void movePlayerz(int z);
	void turnOnLights();
	void turnOffLights();
};

#endif
