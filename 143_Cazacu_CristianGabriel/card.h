//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#ifndef INC_143_CAZACU_CRISTIANGABRIEL_CPP_CARD_H
#define INC_143_CAZACU_CRISTIANGABRIEL_CPP_CARD_H

#include "ioBase.h"
#include <vector>
#include <memory>
#include "bilet.h"

template<class A>std::istream& operator>>(std::istream& is, std::vector<A>& vec){
    std::cout<<"\nNumar de elemente: ";
    int n; is >> n;
    for(int i=0 ;i<n; ++i){
        A obj;
        std::cin>>obj;
        vec.push_back(obj);
    }
    return is;
}

template<class A>std::ostream & operator<<(std::ostream& os, const std::vector<A>& vec){
    std::cout<<"\nElemente: ";
    for(const auto& elem: vec)
        std::cout<<elem<<" ";
    return os;
}

class card: public ioBase{
protected:
    static unsigned int ID;
    const unsigned int id;
    std::vector<bilet> bilete;
    std::string tip;
public:
    card();
    std::istream& read(std::istream&) override;
    std::ostream& write(std::ostream&) const override;
    unsigned int getId() const;
    void addBilet();
    std::vector<bilet>& getBilete();
};



#endif //INC_143_CAZACU_CRISTIANGABRIEL_CPP_CARD_H
