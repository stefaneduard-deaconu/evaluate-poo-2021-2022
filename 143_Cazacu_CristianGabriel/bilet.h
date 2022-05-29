//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#ifndef INC_143_CAZACU_CRISTIANGABRIEL_CPP_BILET_H
#define INC_143_CAZACU_CRISTIANGABRIEL_CPP_BILET_H

#include "ioBase.h"

class bilet: public ioBase{
protected:
    double taxa;
    std::string tip;
    double timp;
public:
    bilet() = default;
    bilet(const double& taxa, const std::string& tip, const double& timp = 0):taxa(taxa),tip(tip),timp(timp){}
    std::ostream& write(std::ostream&) const override;
    std::string getTip() const;

};

#endif //INC_143_CAZACU_CRISTIANGABRIEL_CPP_BILET_H
