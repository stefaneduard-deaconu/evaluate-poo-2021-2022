//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#ifndef INC_143_CAZACU_CRISTIANGABRIEL_CPP_MENIU_H
#define INC_143_CAZACU_CRISTIANGABRIEL_CPP_MENIU_H

#include "validator.h"

class meniu{
private:
    meniu() = default;
    static meniu* instance;
    std::vector<card> carduri;
    std::vector<validator> validatoare;
public:
    static meniu* getInstance();
    void showOptions();
    void selectOption(const int&);
    void mainLoop();
};

#endif //INC_143_CAZACU_CRISTIANGABRIEL_CPP_MENIU_H
