/* Totolici Alexandru - Gabriel grupa 143
 * Deaconu Stefan
 * MinGW w64 9.0 */
#include <bits/stdc++.h>
#include <memory>
#include <vector>
using namespace std;
class Baza{
    public:
        virtual istream &read(istream &is) {
            return is;
        }

        virtual ostream &write(ostream &os) const {
            return os;
        }

        friend ostream &operator<<(ostream &os, const Baza &base) {
            return base.write(os);
        }

        friend istream &operator>>(istream &is, Baza &base) {
            return base.read(is);
        }
};

class Bilet : public Baza {
    protected:
        unsigned int ID;
        static unsigned int staticID;
    public:
        istream &read(istream &is) override;
        ostream &write(ostream &os) const override;
        Bilet();
        virtual float getTaxa();

    };
unsigned int Bilet::staticID=0;
Bilet::Bilet() : ID(++staticID){}
istream &Bilet::read(istream &is) {
    Baza::read(is);
    return is;
}

ostream &Bilet::write(ostream &os) const {
    Baza::write(os);
    cout << "ID: ";
    os << ID;
    return os;
}
class BiletSuprafata : public Bilet {
protected:
    float taxa;
public:
    BiletSuprafata();
    BiletSuprafata(float taxa);
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
    float getTaxa() override;

};

float BiletSuprafata::getTaxa() {
    return taxa;
}
BiletSuprafata::BiletSuprafata() : taxa(2) {}
BiletSuprafata::BiletSuprafata(float taxa) : taxa(2){}

istream &BiletSuprafata::read(istream &is) {
    Bilet::read(is);
    taxa = 2.0;
    return is;
}

ostream &BiletSuprafata::write(ostream &os) const {
    Bilet::write(os);
    cout << "Taxa : ";
    os << taxa << endl;
    return os; }

//
class BiletMetrou : public Bilet {
protected:
    float taxa;
public:
    BiletMetrou();
    BiletMetrou(float taxa);
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
    float getTaxa() override;

};

float BiletMetrou::getTaxa() {
    return taxa;
}
BiletMetrou::BiletMetrou() : taxa(2.5) {}
BiletMetrou::BiletMetrou(float taxa) : taxa(2.5) {}

istream &BiletMetrou::read(istream &is) {
    Bilet::read(is);
    taxa = 2.5;
    return is;
}

ostream &BiletMetrou::write(ostream &os) const {
    Bilet::write(os);
    cout << "Taxa : ";
    os << taxa << endl;
    return os;
}

//
class BiletTranzit : public BiletSuprafata, public BiletMetrou {
private:
    float taxa;
public:
    BiletTranzit();
    BiletTranzit(float taxa);
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
    float getTaxa() override;

};

float BiletTranzit::getTaxa() {
    return taxa;
}
BiletTranzit::BiletTranzit() {}
BiletTranzit::BiletTranzit(float taxa) : taxa(3.0) {}


istream &BiletTranzit::read(istream &is) {
    BiletSuprafata::read(is);
    taxa = 3.0;
    return is;
}

ostream &BiletTranzit::write(ostream &os) const {
    BiletSuprafata::write(os);
    cout << "Taxa : ";
    os << taxa << endl;
    return os;
}

shared_ptr<Bilet> citireBilet(){
    shared_ptr<Bilet> x;
    int option;
    cin >> option;
    cout << "Alegeti tipul de bilet : \n1.Bilet Suprafata\n2.Bilet metrou\nBilet tranzit";
    if(option == 1)
        x = make_shared<BiletSuprafata>();
    else if(option == 2)
        x = make_shared<BiletMetrou>();
    else if(option == 3){
        x = make_shared<BiletSuprafata>();
//        x = make_shared<BiletTranzit>();
    }
    else return nullptr;
    cin >> *x;
    return x;

}

class Card : public Baza {
protected:
    vector<shared_ptr<Bilet>> bilete;
public:
    Card();
    Card(const vector<shared_ptr<Bilet>> &bilete);

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

};
Card::Card() {
}

Card::Card(const vector<shared_ptr<Bilet>> &bilete) : bilete(bilete) {}

istream &Card::read(istream &is) {
    Baza::read(is);
    cout << "Introduceti nr bilete : ";
    int n; cin >> n;
    for(int i=0;i<n;i++)
        bilete.push_back(citireBilet());
    return is;
}

ostream &Card::write(ostream &os) const {
    Baza::write(os);
    cout << "Bilete : ";
    for(int i=0;i<bilete.size();i++)
        os << *bilete[i];
    return os;
}

class CardSuprafata : public Card{
private:
public:
    CardSuprafata();
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};
CardSuprafata::CardSuprafata() {}
istream &CardSuprafata::read(istream &is) {
    Card::read(is);
    return is;
}

ostream &CardSuprafata::write(ostream &os) const {
    Card::write(os);
    return os;
}
class CardSubteran : public Card{
private:
public:
    CardSubteran();
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

CardSubteran::CardSubteran() {}
istream &CardSubteran::read(istream &is) {
    Card::read(is);
    return is;
}

ostream &CardSubteran::write(ostream &os) const {
    Card::write(os);
    return os;
}

class CardTranzit : public Card{
private:
public:
    CardTranzit();
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};
CardTranzit::CardTranzit() {}
istream &CardTranzit::read(istream &is) {
    Card::read(is);
    return is;
}

ostream &CardTranzit::write(ostream &os) const {
    Card::write(os);
    return os;
}

shared_ptr<Card> citireCard(){
    shared_ptr<Card> y;
    int option;
    cin >> option;
    cout << "Alegeti tipul de bilet : \n1.Card Suprafata\n2.Card subteran\nCard tranzit";
    if(option == 1)
        y = make_shared<CardSuprafata>();
    else if(option == 2)
        y = make_shared<CardSubteran>();
    else if(option == 3)
        y = make_shared<CardTranzit>();
    else return nullptr;
    cin >> *y;
    return y;
}

class Aparat : public Baza {
public:
    vector <shared_ptr<Card>> carduri;
    string locatie;
    int nrScanari;
private:
    Aparat();
    Aparat(const vector<shared_ptr<Card>> &carduri, const string &locatie, int nrScanari);
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

};

Aparat::Aparat() {}
Aparat::Aparat(const vector<shared_ptr<Card>> &carduri,const string &locatie, int nrScanari) : carduri(carduri),locatie(locatie), nrScanari(nrScanari){}
istream &Aparat::read(istream &is) {
    Baza::read(is);
    cout << "Introduceti nr de carduri : ";
    int n; cin >> n;
    for(int i=0;i<n;i++)
        carduri.push_back(citireCard());
    return is;
}

ostream &Aparat::write(ostream &os) const {
    Baza::write(os);
    cout << "Carduri : ";
    for(int i=0;i<carduri.size();i++)
        os << *carduri[i];
    return os;
}

//class Meniu : public Baza {
//private:
//    vector<shared_ptr<Card>> carduri;
//    vector<shared_ptr<Aparat>> aparate;
//public:
//    void optiuni() {
//        cout << "Alegeti Optiunea\n1.Creare card\n2.Creare aparat de validare\n3.Adaugare bilet la card\nValidare Card";
//    }
//
//    void run() {
//        int optiune;
//        cin >> optiune;
//        optiuni();
//        while (optiune > 0 && optiune < 5) {
//            if (optiune == 1)
//                creareCard();
//            else if (optiune == 2)
//                creareAparat();
//            optiuni();
//            cin >> optiune;
//        }
//
//    }
//
//    void creareCard() {
//        cout << "Introduceti nr de carduri : ";
//        int nr;
//        cin >> nr;
//        for (int i = 0; i < nr; i++)
//            carduri.push_back(citireBilet());
//
//    }
//
//    void creareAparat() {
//        cout << "Introduceti nr de carduri : ";
//        int nr;
//        cin >> nr;
//        for (int i = 0; i < nr; i++) {
//            aparate.push_back(citireCard());
//        }
//    }
//
//};
int main()
{
//    Meniu m;
//    m.run();
//    return 0;

    vector <shared_ptr<Card>> carduri;
    vector <shared_ptr<Aparat>> aparate;

    cout << "Introduceti nr de aparate : ";
    int nr;
    cin >> nr;
    for (int i = 0; i < nr; i++){
            carduri.push_back(citireCard());
        }
//    cout << "Introduceti nr de carduri : ";
//    int nr2;
//    cin >> nr2;
//    for (int i = 0; i < nr2; i++){
//        carduri.push_back(citireBilet());
//    }



}