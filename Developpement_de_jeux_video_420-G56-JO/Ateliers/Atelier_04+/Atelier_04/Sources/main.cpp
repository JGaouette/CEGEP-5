/// @file main.cpp
/// @brief Fichier principal.

#include "Application.hpp"
#include "scenes/Test.hpp"
#include "scenes/Cours.hpp"

#include "scenes/MainMenu.hpp"
#include "scenes/OptionMenu.hpp"
#include "scenes/Save.hpp"
#include "scenes/NewGame.hpp"
#include "scenes/Mio.hpp"
#include "scenes/MioPostQuart.hpp"
#include "scenes/GameOver.hpp"
#include "scenes/PaperBall.hpp"
#include "scenes/EscapeGame.hpp"
#include "scenes/NetworkArchitecture.hpp"
#include "scenes/SkillTree.hpp"
#include "scenes/ChairRace.hpp"
#include "scenes/Quart.hpp"
#include "scenes/Terminal.hpp"

int main(int argc, char *argv[]) {
    Application::getInstance().addScene(SCENE_COURS, new Cours());
    Application::getInstance().addScene(SCENE_TEST, new Test());

    Application::getInstance().addScene(SCENE_MENU, new MainMenu());
    Application::getInstance().addScene(SCENE_OPTIONS, new OptionMenu());
    Application::getInstance().addScene(SCENE_SAVE, new Save());
    Application::getInstance().addScene(SCENE_NEW_GAME, new NewGame());
    Application::getInstance().addScene(SCENE_MIO, new Mio());
    Application::getInstance().addScene(SCENE_POST_QUART, new MioPostQuart());
    Application::getInstance().addScene(SCENE_GAME_OVER, new GameOver());
    Application::getInstance().addScene(SCENE_PAPER_BALL, new PaperBall());
    Application::getInstance().addScene(SCENE_ESCAPE_GAME, new EscapeGame());
    Application::getInstance().addScene(SCENE_NETWORK, new NetworkArchitecture());
    Application::getInstance().addScene(SCENE_SKILL_TREE, new SkillTree());
    Application::getInstance().addScene(SCENE_RACE, new ChairRace());
    Application::getInstance().addScene(SCENE_QUART, new Quart());
    Application::getInstance().addScene(SCENE_TERMINAL, new Terminal());

    Application::getInstance().swapScene(SCENE_COURS);
    Application::getInstance().start();

    return 0;
}
