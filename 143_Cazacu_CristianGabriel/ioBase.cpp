//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#include "ioBase.h"

std::istream& ioBase::read(std::istream &is) {
    return is;
}

std::ostream& ioBase::write(std::ostream &os) const {
    return os;
}

std::istream& operator>>(std::istream& is, ioBase& b){
    return b.read(is);
}

std::ostream& operator<<(std::ostream& os, const ioBase& b)
{
    return b.write(os);

}

