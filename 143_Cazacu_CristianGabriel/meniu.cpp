//CAZACU CRISTIAN-GABRIEL 143
//GNU g++ MinGW w64 9.0
//STEFAN EDUARD DEACONU

#include "meniu.h"

meniu* meniu::instance = nullptr;

meniu* meniu::getInstance() {
    if(instance == nullptr)
        instance = new meniu;
    return instance;
}

void meniu::showOptions() {
    std::cout<<"\nPentru a continua, alege una dintre variante(1-5): \n1. Adaugare card.\n2. Creare aparat validare.\n3. Adaugare bilet la un card.\n4. Validare card.\n5. Afisare detalii validator.\n6. Iesire.\nAlegere: ";
}

void meniu::selectOption(const int &opt) {
    switch (opt) {
        case 1: {
            std::cout<<"\nSe adauga un card: ";
            card c;
            std::cin >> c;
            carduri.push_back(c);
            break;
        }
        case 2: {
            std::cout<<"Se introduce un validator: ";
            validator v;
            std::cin>>v;
            validatoare.push_back(v);
            break;
        }
        case 3: {
            std::cout<<"\nIntroduceti id-ul cardului: ";
            int id; std::cin >> id;
            bool valid = false;
            for(auto& card: carduri)
                if(card.getId() == id)
                {
                 valid = true;
                 card.addBilet();
                }
            if(!valid)
                std::cout<<"\nCardul nu a fost gasit. ";
            break;
        }
        case 4: break;
        case 5: {
            std::cout<<"\nSe afiseaza detaliile unui validator: ";
            if(validatoare.empty())
                std::cout<<"\nNu exista un validator.";
            else {
                std::cout << "\nIndex validator: ";
                int index;
                std::cin >> index;
                while (index < 0 || index > validatoare.size()) {
                    std::cout << "Valoare invalida, reintroduceti: ";
                    std::cin >> index;
                }
                std::cout << validatoare[index];
            }
            break;
        }
        case 6: std::cout<<"\n\n------------------------------\nIesirea a fost realizata cu succes.";
        default: std::cout<<"\nVarianta invalida, reintroduceti: ";
    }
}

void meniu::mainLoop(){
    int opt =1;
    while(opt !=5){
        showOptions();
        std::cin>>opt;
        selectOption(opt);
    }
}