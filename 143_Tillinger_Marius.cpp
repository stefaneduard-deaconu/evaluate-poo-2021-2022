//Nume: Tillinger Marius Petru grupa 143
//Compilator: MinGW64-W64 version 8.1.0 C++ 20
//Nume laborant: Deaconu Stefan-Eduard

#include<bits/stdc++.h>
using namespace std;

class iobase {      //clasa folosita ca un template pentru a usura operatii de IO
    public: 
        virtual istream &read(istream &in) {
            return in;
        }

        virtual ostream &write(ostream &out) const {
            return out;
        }

        friend istream &operator>> (istream &in, iobase &base) {
            return base.read(in);
        }

        friend ostream &operator<< (ostream &out, iobase &base) {
            return base.write(out);
        }
};

class Bilet : public iobase {

    public:
        
        istream &read(istream&in) {
            iobase::read(in);
            return in;
        }

        ostream &write(ostream&out) const {
            iobase::write(out);
            return out;
        }
};

class BiletS : virtual public Bilet {       //bilet suprafata
    
    public:

        istream &read(istream &in) {
            Bilet::read(in);

            return in;
        }

        ostream &write( ostream &out) const {
            Bilet::write(out);

            return out;
        }
};

class BiletM : virtual public Bilet {       //bilet metrou

    public: 
        istream &read(istream &in) {
            Bilet::read(in);

            return in;
        }

        ostream &write( ostream &out) const {
            Bilet::write(out);

            return out;
        }

};

class BiletT : public BiletS, public BiletM {       //bilet tranzit
    private:
        int timp;
    public: 

        BiletT() {
            timp = 90;
        }

        istream &read(istream &in) {
            BiletS::read(in);

            return in;
        }

        ostream &write( ostream &out) const {
            BiletS::write(out);

            return out;
        }
};

class Card {};

class CardS : public Card{       //card suprafata
    private:
        vector < BiletS > bileteS;
        float pret;
        string pentru;
        
    public: 

        CardS (vector <BiletS> vec1 = {}) : bileteS(vec1) {
            pret = 2;
            pentru = "suprafata";
        }

        void adaugareAutomata(); 
        string getPentru();

        void nouBilet() {
            BiletS b;

            if ( bileteS.size() % 8 != 0)
                bileteS.push_back(b);
            else
                adaugareAutomata();
        }
        
};

string CardS::getPentru() {
    return pentru;
}

void CardS::adaugareAutomata() {
    if (bileteS.size() % 8 == 0) {
        BiletS b;
        bileteS.push_back(b);
    }
}

class CardM : public Card{       //card metrou
    private:
        vector < BiletM > bileteM;
        float pret;
        string pentru;
        
    public: 
        CardM (vector <BiletM> vec1 = {}) : bileteM(vec1) {
            pret = 2.5;
            pentru = "metrou";
        } 

        void adaugareAutomata();
        string getPentru();

        void nouBilet() {
            BiletM b;

            if (bileteM.size() % 8 != 0) 
                bileteM.push_back(b);
            else 
                adaugareAutomata();
        }
};

string CardM::getPentru() {
    return pentru;
}

void CardM::adaugareAutomata() {
    if (bileteM.size() % 8 == 0) {
        BiletM b;
        bileteM.push_back(b);
    }
}

class CardT : public Card {       //card tranzit
    private:
        vector < BiletT > bileteT;
        float pret;
        string pentru;

    public: 
        CardT (vector <BiletT> vec1 = {}) : bileteT(vec1) {
            pret = 3;
            pentru = "metrou/suprafata";
        } 

        void adaugareAutomata();
        string getPentru();

        void nouBilet() {
            BiletT b;

            if ( bileteT.size() % 8 != 0) {
                bileteT.push_back(b);
            }
            else
            {
                adaugareAutomata();
            }
        }
    
};

string CardT::getPentru() {
    return pentru;
}

void CardT::adaugareAutomata() {
    if (bileteT.size() % 8 == 0) {
        BiletT b;
        bileteT.push_back(b);
    }
}

class Validator : public iobase {
    protected:
        string pentru;
    
    public:
};


class Menu {        //classa dedicata meniului
    protected:
       Card* card;
    public:
        void listeazaOp();      //listam optiunile posibile
        int alegeOp();      //alegem una din optiuni
        void run();     //incepem rularea meniului
        void adaugaCard();
        void adaugaBilet();
};

void Menu::adaugaCard() {
    string pentru;
    cin >> pentru;

    cin >> pentru;

    while ( pentru == "suprafata" || pentru == "metrou" || pentru == "metrou/suprafata") {
        if ( pentru == "suprafata" ) {
            Card* card = new CardS();
        } else if ( pentru == "metrou" ) {
            Card* card = new CardM();
        } else if ( pentru == "metrou/suprafata") {
            Card* card = new CardT();
        } else {
            break;
        }
    }
}

void Menu::adaugaBilet() {
    string pentru;
    cin >> pentru;

    cin >> pentru;

    while ( pentru == "suprafata" || pentru == "metrou" || pentru == "metrou/suprafata") {
        if ( pentru == "suprafata" ) {
            Card* card = new CardS();
        } else if ( pentru == "metrou" ) {
            Card* card = new CardM();
        } else if ( pentru == "metrou/suprafata") {
            Card* card = new CardT();
        }
    }
}

int Menu::alegeOp() {
    int op;

    cin >> op;

    return op;
}

void Menu::listeazaOp() {
    cout << "\nAlegeti optiunile: ";
}

void Menu::run() {
    int op;

    while(1) {
        listeazaOp();
        op = alegeOp();

    }
}

int main () {
    return 0;
}
