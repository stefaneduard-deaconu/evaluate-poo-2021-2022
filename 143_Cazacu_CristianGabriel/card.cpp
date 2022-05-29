//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#include "card.h"

unsigned int card::ID = 0;

card::card():id(ID++){}

std::istream& card::read(std::istream &is) {
    std::cout<<"\nTipul cardului suprafata/subteran/tranzit: ";
    is >> tip;
    while(tip != "suprafata" && tip!= "subteran" && tip!= "tranzit")
    {
        std::cout<<"Valoare invalida, reintroduceti: ";
        is >>tip;
    }
    std::cout<<"Cate bilete se adauga: ";
    int n; is >> n;
    for(int i=0; i<n; ++i)
    {
        std::cout<<"\nCare este tipul biletului: \n1. Suprafata.\n2. Subteran. \n3. Tranzit.\nAlegere: ";
        int opt; is >> opt;
        while(opt < 1 || opt > 3)
        {
            std::cout<<"Valoare invalida, reintroduceti: ";
            is >> opt;
        }
        bilet b;
        switch (opt) {
            case 1: b = bilet(2,"suprafata");break;
            case 2: b = bilet(2.5, "subteran");break;
            case 3: b = bilet(3,"tranzit",90); break;
            default: std::cout<<"Valoare invalida.";
        }
        bilete.push_back(b);
    }
    return is;
}


std::ostream&card::write(std::ostream &os) const {
    std::cout<<"\n\nTipul cardului: "<<tip<<"\nLista de bilete: "<<bilete;
    return os;
}

unsigned int card::getId() const {
    return id;
}

void card::addBilet() {
    std::cout<<"\nDetaliile biletului: ";
    bilet b;
    std::cout<<"\nCare este tipul biletului: \n1. Suprafata.\n2. Subteran. \n3. Tranzit.\nAlegere: ";
    int opt; std::cin >> opt;
    while(opt < 1 || opt > 3)
    {
        std::cout<<"Valoare invalida, reintroduceti: ";
        std::cin >> opt;
    }
    switch (opt) {
        case 1: b = bilet(2,"suprafata");break;
        case 2: b = bilet(2.5, "subteran");break;
        case 3: b = bilet(3,"tranzit",90); break;
        default: std::cout<<"Valoare invalida.";
    }
    bilete.push_back(b);
}

std::vector<bilet>& card::getBilete(){
    return bilete;
}