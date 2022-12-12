/// @file Test.hpp
/// @brief Scène de test.
/// @authors Patrick Singcaster, Jean-Philippe Miguel-Gagnon

#pragma once

#include <iostream>

#include "../elements/2d/CheckBox.hpp"
#include "../elements/2d/DefaultBar.hpp"
#include "../elements/2d/FPSCounter.hpp"
#include "../elements/2d/HintBox.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/ImageButton.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/ReachBar.hpp"
#include "../elements/2d/TextBox.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/ImageCounter.hpp"
#include "../elements/2d/TextCounter.hpp"
#include "../elements/2d/TimerLabel.hpp"
#include "../Timer.hpp"
#include "../elements/2d/QuickFixHoldButton.hpp"
#include "../elements/2d/RadioButtonGroup.hpp"
#include "../elements/2d/ButtonSequence.hpp"
#include "Scene.hpp"

// Types d'événement personnalisé
#define ON_HIT_BUTTON_CLICK 1
#define ON_HIT_CHECKBOX_CLICK 2
#define STOP_TIMER_BUTTON_CLICK 3
#define RESUME_TIMER_BUTTON_CLICK 4
#define RESET_TIMER_BUTTON_CLICK 5
#define TIMER_END 6
#define ON_HIT_RADIOBUTTON_CLICK 7
#define ON_BACK_BUTTON_CLICK 8

/// @class Test
/// @brief Scène de test qui contient tous les éléments graphiques.
class Test : public Scene {
private:
    Matrix44d orthographic;

    TextButton *hitButton;
    ReachBar *lifeBar;
    CheckBox *toggleButton;
    Image *image;
    Label *health;
    TextBox *textBoxAmount;
    TimerLabel *timerLabel;
    ImageCounter *imgCounter;
    TextCounter *txtCounter;
    Label *selectedLabel;
    RadioButtonGroup *radioButtonGroup;
    ButtonSequence *buttonSequence;

public:
    /// @brief Chargement de la scène.
    void load() override {
        /// TODO: Activation des interrupteurs nécessaires.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        /// TODO: Chargement des matrices de projection nécessaires.
        orthographic.loadOrthographic(size.x, size.y);

        // TODO: Ajouter tous les éléments qu'on a créer

        // Resources
        ResourcesManager::addResource("font-big", new TTFont("Side-Love.ttf", 48));
        ResourcesManager::addResource("gopher", new Texture("gopher.png"));

        // Retour au menu
        TextButton *backButton = new TextButton({size.x - 10.0, 10}, {75, 25}, "Retour", "font");
        backButton->setAnchor(TOP_RIGHT);
        backButton->setAction(back);
        bindEvent(SDL_MOUSEBUTTONUP, backButton);
        elements2D.push_back(backButton);

        // ProgressBar
        lifeBar = new ReachBar({25, 120}, {175, 20}, 100, 100, 25);
        elements2D.push_back(lifeBar);

        // Button
        hitButton = new TextButton({25, 175}, {100, 50}, "Hit me!");
        hitButton->setAction(hit);
        hitButton->setButtonColor(COLOR_PRIMARY);
        bindEvent(SDL_MOUSEBUTTONUP, hitButton);
        elements2D.push_back(hitButton);

        // Labels
        health = new Label({25, 100}, "Health: ");
        elements2D.push_back(health);

        Label *title = new Label({25, 25}, "Test Scene Please Ignore", "font-big");
        elements2D.push_back(title);

        Label *toggleLabel = new Label({150, 150}, "Damage?");
        elements2D.push_back(toggleLabel);

        Label *amountLabel = new Label({25, 250}, "Amount");
        elements2D.push_back(amountLabel);

        // Timer avec boutton pour contrôler
        timerLabel = new TimerLabel({900, 50}, 15, "Timer baby: ");
        timerLabel->setAction(timerEnd);
        elements2D.push_back(timerLabel);

        TextButton* stopTimerButton = new TextButton({790, 100}, {100, 50}, "Stop");
        stopTimerButton->setAction(stopTimer);
        bindEvent(SDL_MOUSEBUTTONUP, stopTimerButton);
        elements2D.push_back(stopTimerButton);

        TextButton* resumeTimerButton = new TextButton({900, 100}, {100, 50}, "Resume");
        resumeTimerButton->setAction(resumeTimer);
        bindEvent(SDL_MOUSEBUTTONUP, resumeTimerButton);
        elements2D.push_back(resumeTimerButton);

        TextButton* resetTimerButton = new TextButton({1020, 100}, {100, 50}, "Reset");
        resetTimerButton->setAction(resetTimer);
        bindEvent(SDL_MOUSEBUTTONUP, resetTimerButton);
        elements2D.push_back(resetTimerButton);

        // CheckBox
        toggleButton = new CheckBox({150, 175}, {50, 50}, true);
        toggleButton->setAction(hitCheck);
        bindEvent(SDL_MOUSEBUTTONDOWN, toggleButton);
        elements2D.push_back(toggleButton);

        // Image
        image = new Image({150, 50}, {50, 50}, "gopher");
        elements2D.push_back(image);

        // TextBox
        textBoxAmount = new TextBox({25, 275}, "1");
        bindEvent(SDL_MOUSEBUTTONDOWN, textBoxAmount);
        bindEvent(SDL_KEYDOWN, textBoxAmount);
        elements2D.push_back(textBoxAmount);

        bindEvent(SDL_USEREVENT, this);

        // Counters
        imgCounter = new ImageCounter("missing", {500, 500, 0}, {50, 50, 0});
        elements2D.push_back(imgCounter);
        txtCounter = new TextCounter("Compteur", {625, 512, 0});
        elements2D.push_back(txtCounter);

        // QuickFixHoldButton
        QuickFixHoldButton *quickFixHoldButton = new QuickFixHoldButton({25, 400}, 10);
        bindEvent(SDL_KEYDOWN, quickFixHoldButton);
        bindEvent(SDL_KEYUP, quickFixHoldButton);
        elements2D.push_back(quickFixHoldButton);

        // RadioButtons

        CheckBox *radioButton1 = new CheckBox({25, 500}, {25, 25}, true);
        Label *radioButtonLabel1 = new Label({75, 500}, "Radio 1");
        elements2D.push_back(radioButton1);
        elements2D.push_back(radioButtonLabel1);

        CheckBox *radioButton2 = new CheckBox({25, 550}, {25, 25}, false);
        Label *radioButtonLabel2 = new Label({75, 550}, "Radio 2");
        elements2D.push_back(radioButton2);
        elements2D.push_back(radioButtonLabel2);

        CheckBox *radioButton3 = new CheckBox({25, 600}, {25, 25}, false);
        Label *radioButtonLabel3 = new Label({75, 600}, "Radio 3");
        elements2D.push_back(radioButton3);
        elements2D.push_back(radioButtonLabel3);

        radioButtonGroup = new RadioButtonGroup();
        radioButtonGroup->addToGroup("first", radioButton1);
        radioButtonGroup->addToGroup("second", radioButton2);
        radioButtonGroup->addToGroup("third", radioButton3);
        radioButtonGroup->setAction(checkRadioButtons);
        bindEvent(SDL_MOUSEBUTTONUP, radioButtonGroup);

        selectedLabel = new Label({25, 650}, "Selected: ");
        elements2D.push_back(selectedLabel);

        // Hintbox
        HintBox *hintbox = new HintBox({400, 200}, "Voici un hintbox vraiment cool\nEn réalité, c'est plus un text box, mais c'est pas encore sur\nI love gopher");
        hintbox->setBackgroundColor(COLOR_PRIMARY);
        elements2D.push_back(hintbox);

        buttonSequence = new ButtonSequence({400, 400}, "ASDFGHJKL");
        bindEvent(SDL_KEYUP, buttonSequence);
        elements2D.push_back(buttonSequence);
    }

    void unload() {
        // Events
        clearEvents();

        // Drawables 2D
        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        // Resources
        ResourcesManager::removeResource("font-big", true);
        ResourcesManager::removeResource("gopher", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            case ON_HIT_BUTTON_CLICK:
                if (lifeBar->getValue()) {
                    const string input = textBoxAmount->getText();
                    try {
                        int amount = stoi(input);
                        lifeBar->removeValue(amount);
                        health->setText("Health: " + (lifeBar->getValue() ? to_string((int) lifeBar->getValue()) : "Dead"));
                    }
                    catch (...) {
                        textBoxAmount->setText("Bad amount!");
                    }
                }
                // Monte les compteurs
                imgCounter->increase(1);
                txtCounter->increase(1);
                break;

            case ON_HIT_CHECKBOX_CLICK:
                if (toggleButton->isChecked()) {
                    hitButton->setButtonColor(COLOR_PRIMARY);
                    hitButton->setText("Hit me!");
                    hitButton->setEnabled(true);
                }
                else {
                    hitButton->setButtonColor(COLOR_DARK_GRAY);
                    hitButton->setText("Disabled");
                    hitButton->setEnabled(false);
                }
                // Descend les compteurs
                imgCounter->decrease(1);
                txtCounter->decrease(1);
                break;

            case STOP_TIMER_BUTTON_CLICK:
                timerLabel->stop();
                break;

            case RESUME_TIMER_BUTTON_CLICK:
                timerLabel->resume();
                break;

            case RESET_TIMER_BUTTON_CLICK:
                timerLabel->reset();
                break;

            case TIMER_END:
                timerLabel->setPrefix("Timer ended! ");
                break;

            case ON_HIT_RADIOBUTTON_CLICK:
                selectedLabel->setText("Selected: " + radioButtonGroup->getSelectedValue());
                break;

            case ON_BACK_BUTTON_CLICK:
                Application::getInstance().swapScene(SCENE_MENU);
                break;
        }
    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
    }

    /// @brief Affichage de la scène.
    void handleDraw() override {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(orthographic.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto element: elements2D) {
            element->draw();
        }
    }

    static void back() {
        Event::pushCustomEvent(ON_BACK_BUTTON_CLICK);
    }

    static void hit() {
        Event::pushCustomEvent(ON_HIT_BUTTON_CLICK);
    }

    static void hitCheck() {
        Event::pushCustomEvent(ON_HIT_CHECKBOX_CLICK);
    }

    static void stopTimer() {
        Event::pushCustomEvent(STOP_TIMER_BUTTON_CLICK);
    }

    static void resumeTimer() {
        Event::pushCustomEvent(RESUME_TIMER_BUTTON_CLICK);
    }

    static void resetTimer() {
        Event::pushCustomEvent(RESET_TIMER_BUTTON_CLICK);
    }

    static void timerEnd() {
        Event::pushCustomEvent(TIMER_END);
    }

    static void checkRadioButtons() {
        Event::pushCustomEvent(ON_HIT_RADIOBUTTON_CLICK);
    }
};
