//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#ifndef INC_143_CAZACU_CRISTIANGABRIEL_CPP_VALIDATOR_H
#define INC_143_CAZACU_CRISTIANGABRIEL_CPP_VALIDATOR_H

#include "card.h"

class validator: public ioBase{
    std::string tip;
    unsigned int scanari = 0;
    std::vector<card> carduri;
public:
    validator() = default;
    std::istream& read(std::istream&) override;
    void valideaza();
    std::ostream& write(std::ostream&) const override;
//    void valideaza();
};

#endif //INC_143_CAZACU_CRISTIANGABRIEL_CPP_VALIDATOR_H
