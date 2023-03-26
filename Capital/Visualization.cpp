#include "Visualization.h"
mainMenuScene Visualization::m = mainMenuScene();
mainGameScene Visualization::mm = mainGameScene();
 int Visualization::choosenScene = 0;
//void (*scene::change_scene) () = 0;
int* scene::choosen_scene = 0;
std::vector<scene*> Visualization::scene;