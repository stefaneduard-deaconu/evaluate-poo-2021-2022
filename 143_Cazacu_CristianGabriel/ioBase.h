//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#ifndef INC_143_CAZACU_CRISTIANGABRIEL_CPP_IOBASE_H
#define INC_143_CAZACU_CRISTIANGABRIEL_CPP_IOBASE_H

#include <iostream>

class ioBase{
public:
    virtual std::istream& read(std::istream&);
    virtual std::ostream& write(std::ostream&) const;
    friend std::istream& operator>>(std::istream&, ioBase&);
    friend std::ostream& operator<<(std::ostream&, const ioBase&);

};

#endif //INC_143_CAZACU_CRISTIANGABRIEL_CPP_IOBASE_H
