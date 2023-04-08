#include "Visualization.h"
MainMenuScene Visualization::m = MainMenuScene();
MainGameScene Visualization::mm = MainGameScene();
SettingsMenuScene  Visualization :: a;
int Visualization::choosenScene = 0;
bool Visualization::fullscreen = true;
glm::vec2 Visualization::window_resolution = glm::vec2(0,0);
//void (*scene::change_scene) () = 0;
int* Scene::choosen_scene = 0;
std::vector<Scene*> Visualization::scene;

//Simulation Visualization::simulation = ::Simulation();