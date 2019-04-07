//
//  main.cpp
//  solarsystem
#include <GL/glut.h>
#include "solarsystem.hpp"

SolarSystem solarsystem;


void onDisplay(void) {
  solarsystem.onDisplay();
}
void onUpdate(void) {
  solarsystem.onUpdate();
}
void onKeyboard(unsigned char key, int x,. int y) {
  solarsystem.onKeyboard(key, x, y);
}



int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowPosition(WINDOW_X_POS, WINDOWS_Y_POS);
  glutCreateWindow("SolarSysten at Wan Chen");
	
  glutDisplayFunc();
  glutIdleFunc();
  glutKeyboardFunc();
  glutMainLoop();
	
  return 0;

}
