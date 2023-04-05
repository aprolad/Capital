#include "Visualization.h"
mainMenuScene Visualization::m = mainMenuScene();
mainGameScene Visualization::mm = mainGameScene();
int Visualization::choosenScene = 0;
bool Visualization::fullscreen = true;
//void (*scene::change_scene) () = 0;
int* scene::choosen_scene = 0;
std::vector<scene*> Visualization::scene;

simulation Visualization::simulation = ::simulation();