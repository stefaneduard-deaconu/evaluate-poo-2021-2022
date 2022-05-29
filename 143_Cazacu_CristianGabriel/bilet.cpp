//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#include "bilet.h"

std::ostream& bilet::write(std::ostream &os) const {
    std::cout<<"\n\nTip: "<<tip<<"\nTaxa: "<<taxa;
    if(timp)
        std::cout<<"\nTimp: "<<timp;
    return os;
}

std::string bilet::getTip() const {
    return tip;
}