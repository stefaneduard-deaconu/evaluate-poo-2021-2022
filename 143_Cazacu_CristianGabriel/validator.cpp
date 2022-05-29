//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#include "validator.h"

std::istream& validator::read(std::istream &is) {
    std::cout<<"\nTipul validatorului suprafata/subteran: ";
    is >> tip;
    while(tip != "suprafata" && tip!= "subteran")
    {
        std::cout<<"Varianta invalida, reintroduceti: ";
        is >> tip;
    }
    std::cout<<"Carduri: ";
    is >> carduri;
    return is;
}

void validator::valideaza() {
    std::cout<<"\nIntrodu id-ul cardului: ";
    unsigned int id;
    bool valid = false;
    for(auto& card: carduri)
        if(card.getId() == id)
        {
            valid = true;
            std::vector<bilet>& bilete = card.getBilete();
            int index = -1;
            for(int j=0; j<bilete.size(); j++)
            {
                if(bilete[j].getTip() == tip || bilete[j].getTip()=="tranzit") {
                    index = j;
                    break;
                }
            }
            if(index != -1)
                bilete.erase(bilete.begin() + index);
            else
                std::cout<<"\nNu exista bilete pentru tipul aceasta de trasport.";
            break;
        }
}

std::ostream& validator::write(std::ostream &os) const {
    std::cout<<"\nAfisare detalii validator: \nLocatie: "<<tip<<"\nScanari: "<<scanari;
    return os;
}