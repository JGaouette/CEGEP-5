/// @file TextBox.hpp
/// @brief Controle Visuel: TextBox
/// @author Bryan <driftxadon@gmail.com>
#pragma once

//Defines
#define MAX_CHAR 20
#define ON_TEXTBOX_ENTER 10
#define ON_TEXTBOX_TAB 11
#define ON_TEXTBOX_RIGHT_ARROW 12
#define ON_TEXTBOX_LEFT_ARROW 13
#define ON_TEXTBOX_DOWN_ARROW 14
#define ON_TEXTBOX_UP_ARROW 15

#if 0
  #include <iostream>
  #define dLog(tag, val) std::cout << tag << " : " << val << std::endl
#else
  #define dLog(tag, val)
#endif

#include <SDL2/SDL.h>
#include <string>

#include "../../Event.hpp"
#include "../../Rectangle.hpp"
#include "../../ResourcesManager.hpp"
#include "../../TTFont.hpp"
#include "../../Texture.hpp"
#include "../../Vector3d.hpp"
#include "Drawable2d.hpp"

/// @class TextBox
/// @brief Classe pour les entrées de textes
using namespace std;
class TextBox : public Drawable2d{
private:
    Vector3d size; ///< Dimensions du TextBox
    Vector3d textSize; ///< Dimensions du texte du TextBox

    string inputText; ///< Texte dans l'entrée de texte
    unsigned char charLimit; ///< Valeur maximale d'entrée

    TTFont *font; ///< Resource pointeur TTF
    Texture *textTexture; ///< Texture du texte

    bool isFocused; ///< Si le TextBox est focused
    SDL_Color textColor; ///< Couleur du texte

public:
    //TODO: A voir qu'est-ce qu'on pourrait ajouter d'autre parametres d'utiles
    /// @brief Creation d'un instance TextBox
    /// @param startText Texte qui s'affiche par defaut
    /// @param limit Limite d'entree possible
    /// @param color Couleur du texte
    TextBox(Vector3d position, const char *inputText, const char *fontName = DEFAULT_FONT, SDL_Color color = COLOR_BLACK, unsigned char limit = MAX_CHAR) {
        this->inputText = inputText;
        textColor = color;

        this->position = position;

        this->charLimit = limit;

        font = ResourcesManager::getResource<TTFont>(fontName);

        //Obtenir taille maximale possible
        SDL_Point size = font->getSize("W");
        this->size = Vector3d((size.x * charLimit), size.y, 0);

        //Empèche le segmentation fault si le texte est vide
        if (this->inputText.size() == 0){
            this->inputText = " ";
        }

        textTexture = new Texture(font->renderTextBlended(this->inputText.c_str(), color));
        textSize.x = textTexture->getWidth();
        textSize.y = textTexture->getHeight();

        isFocused = false;

        anchor = TOP_LEFT;
    }

    ~TextBox(){
        delete textTexture;
    }

    /// @brief Répondre à l'événement
    void notification() override{
        auto mousePos = Event::getMousePosition();

        if(Event::getType() == SDL_MOUSEBUTTONDOWN){
          isFocused = (mousePos.x >= position.x &&
                       mousePos.x <= position.x + size.x &&
                       mousePos.y >= position.y &&
                       mousePos.y <= position.y + size.y);
          return;
        }

        if(!isFocused){
            return;
        }

        char eventChar = (char)Event::getKey();

        dLog("Event#", eventChar);
        if (eventChar >= 32 && eventChar <= 126 && inputText.size() < charLimit){
            if(inputText.size() < charLimit){
                if (eventChar >= 79 && eventChar <= 82){
                    switch (eventChar){
                        case 79:
                        Event::pushCustomEvent(ON_TEXTBOX_RIGHT_ARROW);
                        break;
                        case 80:
                        Event::pushCustomEvent(ON_TEXTBOX_LEFT_ARROW);
                        break;
                        case 81:
                        Event::pushCustomEvent(ON_TEXTBOX_DOWN_ARROW);
                        break;
                        case 82:
                        Event::pushCustomEvent(ON_TEXTBOX_UP_ARROW);
                        break;
                    }
                }
#ifdef __APPLE__
                // Check if SDLK_LSHIFT is pressed
                else if (SDL_GetModState() == KMOD_LSHIFT || SDL_GetModState() == KMOD_RSHIFT ){
                    switch (eventChar){
                        //#
                        case 35:
                            inputText += '|';
                            break;
                        //1
                        case 49:
                            inputText += '!';
                            break;
                        //2
                        case 50:
                            inputText += '"';
                            break;
                        //3
                        case 51:
                            inputText += '/';
                            break;
                        //4
                        case 52:
                            inputText += '$';
                            break;
                        //5
                        case 53:
                            inputText += '%';
                            break;
                        //6
                        case 54:
                            inputText += '?';
                            break;
                        //7
                        case 55:
                            inputText += '&';
                            break;
                        //8
                        case 56:
                            inputText += '*';
                            break;
                        //9
                        case 57:
                            inputText += '(';
                            break;
                        //0
                        case 48:
                            inputText += ')';
                            break;
                        //-
                        case 45:
                            inputText += '_';
                            break;
                        //=
                        case 61:
                            inputText += '+';
                            break;
                        //;
                        case 59:
                            inputText += ':';
                            break;
                        //<
                        case 60:
                            inputText += '>';
                            break;
                        //,
                        case 44:
                            inputText += '\'';
                            break;
                        default:
                            inputText += toupper(eventChar);
                            break;
                    }
                }

#endif
                // Pour l'instant, shift marche seulement sur Windows
#ifdef _WIN32
                else if (GetKeyState(VK_SHIFT) == -127 || GetKeyState(VK_SHIFT) == -128){
                    //Fait lorsque maintien shift fait le bon char, si peut être optimisé please do
                    //basé sur clavier du cégep, si vous voulez les changer go ahead
                    switch (eventChar){
                        //#
                        case 35:
                            inputText += '|';
                        break;
                        //1
                        case 49:
                            inputText += '!';
                        break;
                        //2
                        case 50:
                            inputText += '"';
                        break;
                        //3
                        case 51:
                            inputText += '/';
                        break;
                        //4
                        case 52:
                            inputText += '$';
                        break;
                        //5
                        case 53:
                            inputText += '%';
                        break;
                        //6
                        case 54:
                            inputText += '?';
                        break;
                        //7
                        case 55:
                            inputText += '&';
                        break;
                        //8
                        case 56:
                            inputText += '*';
                        break;
                        //9
                        case 57:
                            inputText += '(';
                        break;
                        //0
                        case 48:
                            inputText += ')';
                        break;
                        //-
                        case 45:
                            inputText += '_';
                        break;
                        //=
                        case 61:
                            inputText += '+';
                        break;
                        //;
                        case 59:
                            inputText += ':';
                        break;
                        //<
                        case 60:
                            inputText += '>';
                        break;
                        //,
                        case 44:
                            inputText += '\'';
                        break;
                        default:
                            inputText += toupper(eventChar);
                        break;
                    }
                } else if (GetKeyState(18) == -127 || GetKeyState(18) == -128){
                    //Fait lorsque maintien alt fait le bon char, si peut être optimisé please do
                    switch (eventChar){
                        //#
                        case 35:
                            inputText += '\\';
                        break;
                        //2
                        case 50:
                            inputText += '@';
                        break;
                        /* cédille existe pas en ascii
                        //^
                        case 94:
                            inputText += '[';
                        break;
                        //¸
                        case '¸':
                            inputText += ']';
                        break;
                        //`
                        */
                        case 96:
                            inputText += '{';
                        break;
                        //<
                        case 60:
                            inputText += '}';
                        break;
                        //;
                        case 59:
                            inputText += '~';
                        break;
                    }
                }
#endif
                else {
                    inputText += eventChar;
                }
            }
        } else if (eventChar == 8 && inputText.size() > 0){
            if(inputText.size() == 1){
                inputText.erase();

                //Ceci previent un segment fault (null)
                inputText.append(" ");
            }
            else{
                inputText.pop_back();
            }
        } else if (inputText.size() > 0 && (eventChar == 13 || eventChar == SDL_SCANCODE_RETURN)){
            Event::pushCustomEvent(ON_TEXTBOX_ENTER);
        } else if (inputText.size() > 0 && eventChar == 9){
            Event::pushCustomEvent(ON_TEXTBOX_TAB);
        }

        delete textTexture;
        textTexture = new Texture(
          font->renderTextBlended(inputText.c_str(), textColor)
        );

        textSize.x = textTexture->getWidth();
        textSize.y = textTexture->getHeight();
    }

    /// @brief Afficher le TextBox
    void draw() override{
        //Background
        if(isFocused){
          Rectangle::drawColor(position, size, {255, 255, 255, 255}, anchor);
        }else{
          Rectangle::drawColor(position, size, {255, 255, 255, 100}, anchor);
        }

        //Texte
        Rectangle::drawTexture(position, textSize, *textTexture);
    }

    /// @brief Recevoir le texte entrée
    /// @return Text dans l'entrée
    const char* getText(){
        return inputText.c_str();
    }

    /// @brief Affecter le texte de depart
    /// @param text Texte a affecter
    void setText(const string& text) {
        inputText = text;

        delete textTexture;
        textTexture = new Texture(font->renderTextBlended(inputText.c_str(), textColor));

        textSize.x = textTexture->getWidth();
        textSize.y = textTexture->getHeight();

    }

    /// @brief Recevoir le nombre de characteres dans le texte entrée
    /// @return Taille du texte
    unsigned char getTextLength(){
        return inputText.size();
    }

    /// @brief Obtenir les dimensions
    /// @return Dimensions
    const Vector3d &getSize(){
        return size;
    }
};
