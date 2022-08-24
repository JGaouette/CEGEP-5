/*
TODO Rappel des pointeurs
*Pointeur
    !Déclaration:
        ?int* pEntier   //Pointeur
        ?int& rEntier   //Référence (Constante des pointeurs)
        ?int entier     //Valeur

    !Implémentation:
        ?entier = entier      //Vas chercher valeur de entier
        ?pEntier = &entier    //Vas chercher adresse de entier
        ?entier = *pEntier    //Vas chercher valeur d'un pointeur
*/

#include <iostream>
using namespace std;

//!Rappel classe
#pragma region Rappel_Classe

class Entier {
private:
    int* pEntier;

public:
    Entier() { // contructeur par défaut
        pEntier = new int(0);
    }

    Entier(int entier) { // construsteur surcharge
        pEntier = new int(entier);
    }

    Entier(const Entier& entier) { //Constructeur de copie
        pEntier = new int(*entier.pEntier);
    }
    
    ~Entier(){ // destructeur

    }
};

#pragma endregion

//!Rappel dérivation
#pragma region Rappel_Derivation

class ClasseBase {
private:
    int donneeA;

protected:
    int donneeB;

public:
    ClasseBase(int donneeA, int donneeB) {
        this->donneeA = donneeA;
        this->donneeB = donneeB;
    }
};

class ClasseBonus {
protected:
    int donneeD;
};

class ClasseDerivee : public ClasseBase, public ClasseBonus {
private:
    int donneeC;
protected:

public:
    ClasseDerivee(int donneeA, int donneeB, int donneeC) : ClasseBase(donneeA, donneeB) {
        this->donneeC = donneeC;
    }
};

#pragma endregion

//!Rappel static (propre à une classe)
#pragma region Rappel_Static

class Classe {
private:
    static int instanceCount;

public:
    Classe() {
        instanceCount++;
    }

    ~Classe() {
        instanceCount--;
    }

    static int getInstanceCount() {
        return instanceCount;
    }
};

int Classe::instanceCount = 0;

#pragma endregion

//!Polymorphisme
#pragma region Rappel_Polymorphisme

class ClasseA {
public:
    virtual void afficher() { cout << "Afficher de ClasseA" << endl;}
};

class ClasseB : public ClasseA {
public:
    void afficher() { cout << "Afficher de ClasseB" << endl;}
};

class ClasseC : public ClasseB {
public:
    void afficher() { cout << "Afficher de ClasseC" << endl;}
};

#pragma endregion

//! Classe abstraite
#pragma region Rappel_Abstrait
class Piece {
public:
    virtual bool isValid() = 0; //Méthode virtuel pure
};

class Pawn : public Piece {
public:
    bool isValid(){
        return true;
    }
};
#pragma endregion 


int main(int argc, char* argv[]){
    ClasseA* instanceA = new ClasseA();
    ClasseA* instanceB = new ClasseB();
    ClasseA* instanceC = new ClasseC();

    Classe::getInstanceCount();

    ClasseDerivee classeDerivee(1, 2, 3);

    Entier entier1(42);
    Entier entier2 = entier1;
    return 0;
}