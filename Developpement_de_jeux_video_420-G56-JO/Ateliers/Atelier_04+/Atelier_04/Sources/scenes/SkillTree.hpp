 /// @file SkillTree.hpp
/// @brief Classe des arbes a competences
/// @author Bryan <1672406@etu.cegep-lanaudiere.qc.ca> Olivier Savoie <1908527@etu.cegep-lanaudiere.qc.ca>
#pragma once

#include <string>
#include <map>

#include "../Matrix44d.hpp"
#include "Scene.hpp"

#include "../elements/2d/Drawable2d.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/HintBox.hpp"
#include "Mio.hpp"

//TestStuff
#define PREDEFINED_SKILL_LOCKED

//Layout (Modifiable)
#define MARGIN_LEFT size.x * 0.03
#define MARGIN_TOP size.y * 0.09
#define SPACING_HORIZONTAL size.x * 0.203
#define SPACING_VERTICAL size.y * 0.1666
#define IMAGE_LABEL_MARGIN size.y * 0.0138
#define IMAGE_SIZE_X size.x * 0.039
#define IMAGE_SIZE_Y size.y * 0.0694
#define IMAGE_OFFSET_XY 10
#define BTN_SIZE_X size.x * 0.0976
#define BTN_SIZE_Y size.y * 0.0694
#define FONT_SIZE size.x * 0.02

//Just defines (facilite peut-etre la lecture)
#define NO_INDEX -1
#define IMAGE_GOPHER "gopher.png"

//Images
#define SKILL_BACKGROUND "SkillBackground.png"
#define IMAGE_SIZE {IMAGE_SIZE_X, IMAGE_SIZE_Y}
#define IMAGE_LABEL_MARGIN_X IMAGE_SIZE_X + IMAGE_LABEL_MARGIN
#define IMAGE_LABEL_MARGIN_Y IMAGE_SIZE_Y + IMAGE_LABEL_MARGIN
#define BTN_SIZE {BTN_SIZE_X, BTN_SIZE_Y}

//Position du premier image
#define IMAGE_START_X MARGIN_LEFT + IMAGE_OFFSET_XY
#define IMAGE_START_Y MARGIN_LEFT + IMAGE_OFFSET_XY

/// @class SkillTree
/// @brief Classe pour les arbes a competences
class SkillTree : public Scene{
private:
    map<int, ImageButton*> images;              ///< Positions d'images avec leurs indices
    map<ImageButton*, bool> imagesUnlocked;     ///< Map qui indique si un competence est verrouillé ou non
    map<unsigned char, string> imagesName;      ///< Map qui contient les chemins des images
    Texture *background;                        ///< Arriere plan du Scene
    TextButton *btn;                            ///< Bouton pour aller à Post-Quart

    string hintDesc[13];                        ///< Liste de texte pour les hintbox
    Matrix44d projection;                       ///< Projection Orthogonale

    //Hintbox
    HintBox *hintBoxDescriptor;                 ///< Hintbox décrivant les competences
    char hintIndex;                             ///< Index de l'image
    unsigned char opacity = 0;                  ///< Valeur de transparence pour le hintbox

    //TODO: A voir comment on va avoir les stats du joueur (sa peut peut-etre attendre?)
//    PlayerStats *playerStats;

    /// @brief Calculer indice du image selon la souris
    /// @param pt Point x,y de la souris
    char getIndexFromMouse(const SDL_Point &pt){
        for(int index = 0; index < (int)images.size(); index++){
            Vector3d pos = AnchorUtils::getCenterPosition(images[index + 1]->position, IMAGE_SIZE, BOTTOM_RIGHT);

            //Souris est-il entre les bordures de l'image
            if(pt.x >= pos.x && pt.x <= pos.x + IMAGE_SIZE_X &&
               pt.y >= pos.y && pt.y <= pos.y + IMAGE_SIZE_Y){
                return index;
            }
        }

        return NO_INDEX;
    }

    /// @brief Fonction gérant l'action de SDL_MOUSEMOTION
    void eventMouseMotion(){
        SDL_Point mousePos = Event::getMousePosition();

        char oldIndex = hintIndex;
        hintIndex = getIndexFromMouse(mousePos);
        if(hintIndex != NO_INDEX){
            if(hintIndex != oldIndex){
              delete hintBoxDescriptor;
              hintBoxDescriptor = new HintBox({0,0},
                                            hintDesc[hintIndex], "labels", COLOR_BLACK, COLOR_GRAY);
            }

            //Ajustement position
            if(mousePos.x > size.x / 2.0)
                mousePos.x -= hintBoxDescriptor->getWidth();

            if(mousePos.y > size.y / 2.0)
                mousePos.y -= hintBoxDescriptor->getHeight();

            hintBoxDescriptor->setPosition({(double)mousePos.x, (double)mousePos.y});
        }
    }

    /// @brief Debloquer une competence
    /// @param type Type de competence
    /// @param lvl Niveau de competence
    /// @return True, si competence peut etre debloquer
    bool unblockSkill(char type, char lvl){
        unsigned char indexOfSkill = (type * 3) + lvl;
        //TODO: Verification
        //TODO: Debloquer Competence
        return false;
    }

public:
    enum SKILL_TYPE{
      MOVE_SPEED = 0, SMELL = 1, TIME = 2, FIXING_SPEED = 3
    };

    enum SKILL_LEVEL{
      STUDENT = 0, TRAINEE = 1, TECHNICIAN = 2, BENJAMIN = 3
    };

    ///TODO: Voir si sa prends des & ou *
    /// @brief Debloquer une competence (Redirection au methode prive)
    /// @param type Type de competence
    /// @param lvl Niveau de competence
    /// @return True, si competence peut etre debloquer
    bool unblockSkill(SKILL_TYPE type, SKILL_LEVEL lvl){
        return unblockSkill((char) type, (char) lvl);
    }

    //OVERRIDES-----------------------------------------------------------------
    //TODO: Mettre un indication que le competence est debloquer ou nn
    //TODO: Changer de scene lors du clique de bouton
    void load() override{
        bindEvent(SDL_USEREVENT, this);
        bindEvent(SDL_MOUSEMOTION, this);

        //Init
        projection.loadOrthographic(size.x, size.y);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(projection.elements);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        hintIndex = NO_INDEX;

        //Chargement textures
        ResourcesManager::addResource("SkillBackground", new Texture(SKILL_BACKGROUND));
        ResourcesManager::addResource("gopher", new Texture(IMAGE_GOPHER));
        ResourcesManager::addResource("labels", new TTFont(DEFAULT_FONT, FONT_SIZE));
        ResourcesManager::addResource("guru", new Texture("guru.png"));
        imagesName[0] = "guru";
        ResourcesManager::addResource("manrunning", new Texture("runningman.png"));
        imagesName[1] = "manrunning";
        ResourcesManager::addResource("drip", new Texture("drip.webp"));
        imagesName[2] = "drip";
        ResourcesManager::addResource("axe", new Texture("axe.png"));
        imagesName[3] = "axe";
        ResourcesManager::addResource("febreze", new Texture("febreeze.png"));
        imagesName[4] = "febreze";
        ResourcesManager::addResource("fan", new Texture("fan.png"));
        imagesName[5] = "fan";
        ResourcesManager::addResource("sapin", new Texture("sapin.png"));
        imagesName[6] = "sapin";
        ResourcesManager::addResource("clock", new Texture("clock.png"));
        imagesName[7] = "clock";
        ResourcesManager::addResource("lofi", new Texture("lofi.png"));
        imagesName[8] = "lofi";
        ResourcesManager::addResource("warudo", new Texture("bonhomme.png"));
        imagesName[9] = "warudo";
        ResourcesManager::addResource("manual", new Texture("manual.png"));
        imagesName[10] = "manual";
        ResourcesManager::addResource("hammer", new Texture("marteau.png"));
        imagesName[11] = "hammer";
        ResourcesManager::addResource("india", new Texture("India.png"));
        imagesName[12] = "india";
        ResourcesManager::addResource("locked", new Texture("locked.png"));
        imagesName[13] = "locked";

        background = ResourcesManager::getResource<Texture>("SkillBackground");

        hintBoxDescriptor = new HintBox({0, 0}, "Hi, i'm a placeholder!");

        //Nom de labels + fichiers image
        string labels[8];
        //Niveaux
        labels[0] = "Etudiant";
        labels[1] = "Stagiere";
        labels[2] = "Technicien";
        labels[3] = "Benjamin";
        //Type de competences
        labels[4] = "Vitesse Deplacement";
        labels[5] = "Odeur";
        labels[6] = "Temps";
        labels[7] = "Reparation";

        //Titres en dessus d'image
        string imageLbl[13];
        imageLbl[0] = "Guru";
        imageLbl[1] = "Cardio";
        imageLbl[2] = "Drip";
        imageLbl[3] = "Affiche";
        imageLbl[4] = "Febreeze";
        imageLbl[5] = "Ventilateur";
        imageLbl[6] = "Sapin";
        imageLbl[7] = "Temps";
        imageLbl[8] = "Lofi";
        imageLbl[9] = "ZA WARUDO";
        imageLbl[10] = "Instructions";
        imageLbl[11] = "HammerTime";
        imageLbl[12] = "Tutoriel Indien";

        //HintBox image descriptions
        hintDesc[0] = "L’élève boit une boisson énergétique avant\nson quart de travail et se déplace légèrement\nplus vite pendant un certain temps.\nPrix:";
        hintDesc[1] = "Comme un bon élève, il a un meilleur cardio\net peut donc courir.\nPrix:";
        hintDesc[2] = "Le joueur a trop de style en dépensant une\nfortune sur des souliers, il peut sauter\nsur les obstacles.\nPrix:";
        hintDesc[3] = "Installe un poster dans la classe qui rappelle\naux personnes de mettre du déodorant et de\nprendre des douches afin de réduire les odeurs.\nPrix:";
        hintDesc[4] = "Le joueur dépense de l’argent à la COOP pour\nune bonne canette de Febreze pour réduire\nles odeurs plus rapidement.\nPrix:";
        hintDesc[5] = "L’administration peut enfin se permettre d’installer \nun ventilateur dans la classe.\nPrix:";
        hintDesc[6] = "Grâce à une subvention du gouvernement on peut\nse permettre de mettre un gros sapin sent\nbon dans la classe.\nPrix:";
        hintDesc[7] = "L’étudiant envoie un MIO à Philippe pour avoir\nun extension de temps.\nPrix:";
        hintDesc[8] = "L’étudiant peut se concentrer grâce à de la\nlo-fi.\nPrix:";
        hintDesc[9] = "Le joueur est très relaxe et bénéficie de beaucoup\nde temps.\nPrix:";
        hintDesc[10] = "Utilisation de Github plutôt que des documents\nword datant de 2003, lui permettant de réparer\nplus facilement.\nPrix:";
        hintDesc[11] = "Le joueur possède maintenant un marteau et\npeut réparer les objets.\nPrix:";
        hintDesc[12] = "L’élève a regardé des vidéos d’indiens sur\nYoutubelui permettant de comprendre plus\nrapidement comment réparer les objets.\nPrix:";

        //Titre
        Label *title = new Label({size.x / 2.0, MARGIN_TOP / 2}, "Arbre des competences");
        title->setAnchor(Anchor::MIDDLE_CENTER);
        elements2D.push_back(title);

        //Bouton d'action
        btn = new TextButton({size.x - MARGIN_LEFT, size.y - MARGIN_TOP}, BTN_SIZE, "Continuer", "labels");
        btn->setAnchor(Anchor::MIDDLE_RIGHT);
        btn->setAction([]() {
            Mio *preQuart = new Mio();
            preQuart->setMio("Philippe Girard", "Toi", "Un jour en 2030", "CAI semaine 1", "Bonjour à toi cher technicien du CAI, cette semaine on s'attend à une hausse de personnes\nà la bibliothèque qui feront leur travaux. Attend toi à devoir aider plus de personnes.\nOn a aussi reçu une nouvelle imprimante mais elle nous fait défaut et devra surement être\nréparé. N'hésite pas a regarder un tutoriel en ligne pour savoir comment la réparer.\n \nBonne chance et bonne journée, Philippe.", "Quart");
            Application::getInstance().removeScene("Mio");
            Application::getInstance().addScene("Mio", preQuart);
            Application::getInstance().swapScene("Mio");
        });
        bindEvent(SDL_MOUSEBUTTONUP, btn);
        elements2D.push_back(btn);

        //Iteration affichant les elements selon des parametres d'espace/taille etc.
        for(unsigned char xIndex = 0; xIndex < 4; xIndex++){
            //Horizontale
            Label *lvlHeader = new Label({MARGIN_LEFT + SPACING_HORIZONTAL * (xIndex + 1.0), MARGIN_TOP}, labels[xIndex], "labels");
            lvlHeader->setAnchor(Anchor::TOP_CENTER);
            elements2D.push_back(lvlHeader);

            //Verticale
            Label *skillType = new Label({MARGIN_LEFT, IMAGE_START_Y + SPACING_VERTICAL * (xIndex + 1.0)}, labels[xIndex+4], "labels");
            skillType->setAnchor(Anchor::MIDDLE_LEFT);
            elements2D.push_back(skillType);

            //Horizontale
            for(unsigned char yIndex = 0; yIndex < 4; yIndex++){
                unsigned char index = ((xIndex * 3) + 1) + yIndex;

                //Enlever ceux qui n'ont pas de
                if((xIndex == 2 || xIndex == 3) && yIndex == 0){
                    continue;
                }else if(xIndex == 0 && yIndex == 3){
                    continue;
                }

                Vector3d pos({IMAGE_START_X + SPACING_HORIZONTAL * (yIndex + 1.0), IMAGE_START_Y + SPACING_VERTICAL * (xIndex + 1.0)});

                ImageButton *skillImg = new ImageButton(pos, IMAGE_SIZE, imagesName[13]);
                skillImg->setAnchor(Anchor::MIDDLE_CENTER);
                images[index] = skillImg;
                elements2D.push_back(skillImg);

                #ifdef PREDEFINED_SKILL_LOCKED
                    //TESTER
                    if(xIndex > 1 && yIndex > 1){
                        imagesUnlocked[skillImg] = false;
                    }
                    else{
                        imagesUnlocked[skillImg] = true;
                    }

                    dLog("UNLOCKED", imagesUnlocked[skillImg]);
                    //======
                #endif

                //Labels pour images
                //TODO: A verifier couleur n'est pas correct
                SDL_Color unlockedColor = COLOR_BLUE;
                if(imagesUnlocked[skillImg]){
                    unlockedColor = COLOR_GREEN;
                }

                Label *imageLabel = new Label({(double)pos.x,
                                               (double)pos.y + IMAGE_LABEL_MARGIN_Y},
                                                imageLbl[index - 1], "labels", unlockedColor);
                imageLabel->setAnchor(Anchor::BOTTOM_CENTER);
                elements2D.push_back(imageLabel);
            }
        }
    }

    void unload() override{
        unbindEvent(SDL_MOUSEMOTION, this);
        unbindEvent(SDL_USEREVENT, this);

        delete hintBoxDescriptor;

        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        ResourcesManager::removeResource("SkillBackground");
        ResourcesManager::removeResource("gopher");
        ResourcesManager::removeResource("labels");
        for (auto image : imagesName) {
            ResourcesManager::removeResource(image.second);
        }

    }

    void notification() override{
        if(Event::getType() == SDL_MOUSEMOTION){
            eventMouseMotion();
        }
        else{
            //Evenement personalise
            //TODO: Soit rendre une fonction debloquer public, ou un evenement?
//          switch (Event::getCustomCode()) {
//              case SDL_MOUSEMOTION:
//                  break;
//              default:
//                  break;
//          }
        }
    }

    void handleUpdate(const double& deltaTime) override{}

    void handleDraw() override{
        //Background
        Rectangle::drawTexture({0,0}, {(double)size.x, (double)size.y}, *background);

        //Fleches
        Vector3d center;
        Vector3d startArrow;
        Vector3d endArrow;
        Vector3d endPoint;

        Vector3d centerright;
        Vector3d centerleft;
        Vector3d right;
        Vector3d left;
        Vector3d end;

        centerright = AnchorUtils::getCenterPosition(images[1]->position, IMAGE_SIZE, MIDDLE_CENTER);
        centerleft = AnchorUtils::getCenterPosition(images[2]->position, IMAGE_SIZE, MIDDLE_CENTER);
        
        

        right = Vector3d(centerright.x + (IMAGE_SIZE_X / 2.0), centerright.y);
        left = Vector3d(centerleft.x - (IMAGE_SIZE_X / 2.0), centerleft.y);

        int middle = ((left.x - right.x) / 2.0);

        for (size_t index = 1; index < 4; index++) {
            end = AnchorUtils::getCenterPosition(images[11]->position, IMAGE_SIZE, MIDDLE_CENTER);
            
            centerright = AnchorUtils::getCenterPosition(images[index]->position, IMAGE_SIZE, MIDDLE_CENTER);
            right = Vector3d(centerright.x + (IMAGE_SIZE_X / 2.0), centerright.y);
            Vector3d lecenter = Vector3d(right.x + middle, right.y - 30);
            end = Vector3d(lecenter.x, end.y + 70);
            Rectangle::drawLine(lecenter, end, COLOR_ORANGE_RED, 2);
            

            Vector3d pos(lecenter.x, lecenter.y - 15);
            Image *lock = new Image(pos, {20, 20}, "locked");
            lock->setAnchor(Anchor::MIDDLE_CENTER);
            elements2D.push_back(lock);
        }

        //Dessiner les lignes qui lient les compétences
        for (size_t index = 1; index < 13; index++){
            if(index != 3 && index != 7 && index != 10){
                center = AnchorUtils::getCenterPosition(images[index]->position, IMAGE_SIZE, MIDDLE_CENTER);
                startArrow = Vector3d(center.x + (IMAGE_SIZE_X / 2.0), center.y);
                center = AnchorUtils::getCenterPosition(images[index + 1]->position, IMAGE_SIZE, MIDDLE_CENTER);
                endArrow = Vector3d(center.x - (IMAGE_SIZE_Y / 2.0), center.y);
                if (index == 1 || index == 2){
                    Rectangle::drawLine(startArrow, endArrow, COLOR_LIGHT_BLUE, 3);
                }
                else if (index == 4 || index == 5 || index == 6){
                    Rectangle::drawLine(startArrow, endArrow, COLOR_LIGHT_GREEN, 3);
                }
                else if (index == 8 || index == 9){
                    Rectangle::drawLine(startArrow, endArrow, COLOR_YELLOW, 3);
                }
                else if (index == 11 || index == 12){
                    Rectangle::drawLine(startArrow, endArrow, COLOR_ORANGE_RED, 3);
                }

                //diagonale line 1
                startArrow = endArrow;
                endPoint = Vector3d(center.x - 35, center.y + 7);
                if (index == 1 || index == 2){
                    Rectangle::drawLine(startArrow, endPoint, COLOR_LIGHT_BLUE, 3);
                }
                else if (index == 4 || index == 5 || index == 6){
                    Rectangle::drawLine(startArrow, endPoint, COLOR_LIGHT_GREEN, 3);
                }
                else if (index == 8 || index == 9){
                    Rectangle::drawLine(startArrow, endPoint, COLOR_YELLOW, 3);
                }
                else if (index == 11 || index == 12){
                    Rectangle::drawLine(startArrow, endPoint, COLOR_ORANGE_RED, 3);
                }

                //diagonale line2
                startArrow = endArrow;
                endPoint = Vector3d(center.x - 35, center.y - 7);
                if (index == 1 || index == 2){
                    Rectangle::drawLine(startArrow, endPoint, COLOR_LIGHT_BLUE, 3);
                }
                else if (index == 4 || index == 5 || index == 6){
                    Rectangle::drawLine(startArrow, endPoint, COLOR_LIGHT_GREEN, 3);
                }
                else if (index == 8 || index == 9){
                    Rectangle::drawLine(startArrow, endPoint, COLOR_YELLOW, 3);
                }
                else if (index == 11 || index == 12){
                    Rectangle::drawLine(startArrow, endPoint, COLOR_ORANGE_RED, 3);
                }
            }
        }

        //Elements
        for(Drawable2d *element: elements2D){
            element->draw();
        }

        //HintBox
        if(hintIndex != NO_INDEX){
            if(opacity < 253){
                opacity += 3;
                hintBoxDescriptor->setBackgroundColor({128,128,128, (Uint8)opacity});
            }
            hintBoxDescriptor->draw();
        }
        else{
            opacity = 0;
        }
    }
    //FIN_OVERRIDES-------------------------------------------------------------
};
