//
// Created by Nabil Alhafez on 23.05.2022.
//

#ifndef COLOCVIU_CARDURILE_H
#define COLOCVIU_CARDURILE_H

#include <vector>
#include "IoBase.h"
#include "date.h"
#include "enumerable.h"
#include "biletele.h"
#include "functions.h"

using namespace std;

class BaseCard : public IoBase {
protected:
    vector<shared_ptr<Bilet>> bilete;

public:

    ostream &write(ostream &os) const override {
        os << "Avem n= " << bilete.size() << " numarul de bilet " << endl;
        os << bilete;
        return os;


    }

    virtual void printValidBilet() const {
        cout << "Avem n= " << bilete.size() << " numarul de bilet " << endl;

        for (auto bilet: bilete) {
            if (bilet->isValidBilet())
                cout << *bilet << endl;
        }


    }


    virtual void folosescCard() {
        cout << "Enter a card id number after : ";
        printValidBilet();
        yourChoice();
        int id;
        cin >> id;
        bool index = checkIfCardIsExisted(id);
        if (index == -1) {
            cout << "Sorry we could not find the bilet " << endl;
            return;
        }

        bilete[index]->useBilet("Universitatea");
        cout << "Card used successfuly " << endl;

    }

    virtual void yourChoice() {
        cout << "Your choice: ";

    }

    int checkIfCardIsExisted(int id) {
        int index = 0;
        for (auto bilet: bilete) {
            if (bilet->getId() == id)
                return index;
            index++;
        }
        return -1;


    }
};

class SuprafataCard : public BaseCard {
protected:
    vector<shared_ptr<Bilet>> bilete;

public:
    istream &read(istream &is) override {
        BaseCard::read(is);
        cout << "Enter number of bilte: ";

        int count;
        is >> count;

        for (int i = 0; i < count; ++i) {
            shared_ptr<Bilet> m;
            switch (getUserOption(is)) {
                case 1 :
                    m = make_shared<SuprafataBilet>();
                    break;

                case 2 :
                default:
                    m = make_shared<MetrouBilet>();
                    break;
            }
            is >> *m;
        }

        return is;
    }


    int getUserOption(istream &is) {

        int option = 0;
        do {
            cout << "Enter your option please.." << endl;
            cout << "1- Bilet de suprafata." << endl;
            cout << "2- Bilet de metrou." << endl;
            cout << "your choice: " << endl;
            is >> option;

        } while (option > 3 || option < 1);
        return option;

    }


    virtual void folosescCard() {


        cout << "Enter a card id number after : ";
        printValidBilet();
        yourChoice();
        int id;
        cin >> id;
        bool index = checkIfCardIsExisted(id);
        if (index == -1) {
            cout << "Sorry we could not find the bilet " << endl;
            return;
        }

        bilete[index]->useBilet("Universitatea");
        cout << "Card used successfuly " << endl;

    }


};

class SubteranCard : public BaseCard {
protected:
    vector<shared_ptr<Bilet>> bilete;

public:
    istream &read(istream &is) override {
        BaseCard::read(is);
        cout << "Enter number of bilte: ";

        int count;
        is >> count;

        for (int i = 0; i < count; ++i) {
            shared_ptr<Bilet> m;
            switch (getUserOption(is)) {
                case 1 :
                    m = make_shared<SuprafataBilet>();
                    break;

                case 2 :
                default:
                    m = make_shared<MetrouBilet>();
                    break;

            }
            is >> *m;
        }

        return is;
    }

    int getUserOption(istream &is) {

        int option = 0;
        do {
            cout << "Enter your option please.." << endl;
            cout << "1- Bilet de suprafata." << endl;
            cout << "2- Bilet de metrou." << endl;
            cout << "3- Bilet de tranzit." << endl;
            cout << "your choice: " << endl;
            is >> option;

        } while (option > 3 || option < 1);
        return option;

    }


    virtual void folosescCard() {


        cout << "Enter a card id number after : ";
        printValidBilet();
        yourChoice();
        int id;
        cin >> id;
        bool index = checkIfCardIsExisted(id);
        if (index == -1) {
            cout << "Sorry we could not find the bilet " << endl;
            return;
        }

        bilete[index]->useBilet("Universitatea");
        cout << "Card used successfuly " << endl;

    }


};

class TranzitCard : public BaseCard {
protected:
    vector<shared_ptr<Bilet>> bilete;

public:
    istream &read(istream &is) override {
        BaseCard::read(is);
        cout << "Enter number of bilte: ";

        int count;
        is >> count;

        for (int i = 0; i < count; ++i) {
            shared_ptr<Bilet> m;
            m = make_shared<TranzitBilet>();

            is >> *m;
        }

        return is;
    }


    virtual void folosescCard() {


        cout << "Enter a card id number after : ";
        printValidBilet();
        yourChoice();
        int id;
        cin >> id;
        bool index = checkIfCardIsExisted(id);
        if (index == -1) {
            cout << "Sorry we could not find the bilet " << endl;
            return;
        }

        bilete[index]->useBilet("Universitatea");
        cout << "Card used successfuly " << endl;

    }

};


#endif //COLOCVIU_CARDURILE_H
