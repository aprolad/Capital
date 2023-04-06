#include "Visualization.h"
MainMenuScene Visualization::m = MainMenuScene();
MainGameScene Visualization::mm = MainGameScene();
SettingsMenuScene  Visualization :: a;
int Visualization::choosenScene = 0;
bool Visualization::fullscreen = true;
//void (*scene::change_scene) () = 0;
int* Scene::choosen_scene = 0;
std::vector<Scene*> Visualization::scene;

simulation Visualization::simulation = ::simulation();