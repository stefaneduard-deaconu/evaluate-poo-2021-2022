/* Ghetoiu Gheorgh-Laurentiu, grupa 143
  GNU g++, Bundled MinGW,  Version: w64 9.0
  Tutore: Deaconu Stefan-Eduard */

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// clasa de baza Bilete
class Bilet {
protected:
    double pret;
    bool valid;
    int minut;
public:
    Bilet(): valid(true), minut(90) {

    }

    Bilet(double pret) : pret(pret) {

    }
    virtual ~Bilet(){

    };
    bool isValid() const{
        return valid;
    }
    void  valideaza(){
        valid = false;
    }
    virtual int getMinut(){
        return 0;
    }
    virtual void setMinut(int nr) {
        minut -= nr;
    }
};

class BiletSuprafata : public Bilet {
private:
public:
    BiletSuprafata() : Bilet(2) {}
};

class BiletSubteran : public Bilet {
private:
public:
    BiletSubteran() : Bilet(2.5) {}
};

class BiletTranzit : public Bilet {
private:

public:
    BiletTranzit() : Bilet(3){}
    int getMinut() const{
        return minut;
    }
};
// clasa de baza Carduri
class Card {
protected:
    static int ID; //ID pentru unicitate
    int idCurent;
    string tipUltimBilet;
    int minut;
    int moment;
    vector<shared_ptr<Bilet>> bilete;

public:
    virtual ostream& writeCard(ostream &os){
        bool val =0;
        os<<"Tip ultim bilet:"<<tipUltimBilet<<endl;
        os<<"Moment validar: "<<moment<<endl;
        for(auto b:bilete){
            if(b->isValid()){
                if(dynamic_pointer_cast<BiletTranzit>(b))
                    val+=2;
                else if(dynamic_pointer_cast<BiletSubteran>(b))
                    val+=2.5;
                else if(dynamic_pointer_cast<BiletTranzit>(b))
                    val+=3;
            }
        }
        os<<"Valoare: "<<val<<endl;
        return os;
    }
    friend ostream& operator<<(ostream &os, Card b){
        return b.writeCard(os);
    }
    Card() {
        ID++;
        idCurent = ID;
        tipUltimBilet = "nefolosit";
        minut = 0;
    }
    virtual ~Card(){}

    virtual void adaugaBilet() {};

    int getId() const{
        return idCurent;
    }
    vector<shared_ptr<Bilet>> getBilete(){
        return bilete;
    }
    void valideaza(){
        cout<<"Tipul de bilet pe care vreti sa il validati:\n 1.Suprafata\n 2.Subteran\n 3.Tranzit\n";
        int opt;
        cin>>opt;
        cin.get();
        for(auto b: bilete){
            if(opt==1){
                if(dynamic_pointer_cast<BiletSuprafata>(b) && b->isValid()){
                    b->valideaza();
                    tipUltimBilet = "Bilet Suprafata\n";
                    moment = minut;
                    break;

                }
            }
            else if(opt==2){
                if(dynamic_pointer_cast<BiletSubteran>(b) && b->isValid()){
                    b->valideaza();
                    tipUltimBilet = "Bilet Subteran\n";
                    moment = minut;
                    break;
                }
            }
            if(opt==3){
                if(dynamic_pointer_cast<BiletTranzit>(b) && b->isValid() && b->getMinut()>0){
                    b->valideaza();
                    tipUltimBilet = "Bilet Tranzit\n";
                    moment = minut;
                    break;
                }
            }
        }

    }

};

int Card::ID = 0;

class CardSuprafata :public Card {
private:
public:
    void adaugaBilet();
};
void CardSuprafata::adaugaBilet() {
    cout<<"Alegeti tipul de bilet cu care vreti sa incarcati:\n 1.Suprafata\n 2.Subteran\n";
    cout<<"Optiune: ";
    int opt;
    cin>>opt;
    cin.get();
    shared_ptr<Bilet> b;
    if(opt == 1){
        b = make_shared<BiletSuprafata>();
    }
    else if(opt==2)
        b = make_shared<BiletSubteran>();
    bilete.push_back(b);
}

class CardSubteran :public Card {
private:
public:
    void adaugaBilet();
};
void CardSubteran::adaugaBilet() {
    cout<<"Alegeti tipul de bilet cu care vreti sa incarcati:\n 1.Suprafata\n 2.Subteran\n";
    cout<<"Optiune: ";
    int opt;
    cin>>opt;
    cin.get();
    shared_ptr<Bilet> b;
    if(opt == 1){
        b = make_shared<BiletSuprafata>();
    }
    else if(opt==2)
        b = make_shared<BiletSubteran>();
    bilete.push_back(b);
}
class CardTranzit : public Card {
private:
    int minute;
public:
    CardTranzit();
    void adaugaBilet();
    virtual ostream& writeCard(ostream &os){
        Card::writeCard(os);
        if(minut>0)
        os<<minute<<endl;
        else
            os<<"Expirat\n";
        return os;
    }
};
void CardTranzit::adaugaBilet() {
    cout<<"Tipul biletului a fost ales automat: Tranzit\n";
    shared_ptr<Bilet> b;
    b = make_shared<BiletTranzit>();
    bilete.push_back(b);
}
CardTranzit ::CardTranzit(): minute(90) {}

class AparatValidare {
private:
    static int ID;
    int idCurent;
    string locatie;
    int nrScanari;
public:
    AparatValidare();
    int getId() const{
        return idCurent;
    }
    friend istream& operator>>(istream &is, AparatValidare a);
    friend ostream& operator<<(ostream &os, AparatValidare a);
    void adScanare(){
        nrScanari++;
    }
};
int AparatValidare::ID = 0;
istream& operator>>(istream &is, AparatValidare a){
    cout<<"Locatie: ";
    while(true) {
        try {

            getline(is, a.locatie);
            if (a.locatie != "suprafata" && a.locatie != "subteran")
                throw string("Locatie poate sa fie doar suprafata/subteran, introduceti din nou: ");
            else
                break;

        }

        catch (string s) {
            cout << s;
        }
    }

    return is;
}
ostream& operator<<(ostream &os, AparatValidare a){
    os<<"Lcoatie: "<<a.locatie<<endl;
    os<<"Nr scanari: "<<a.nrScanari<<endl;
    return os;
}

AparatValidare::AparatValidare(): nrScanari(0) {
    ID++;
    idCurent = ID;
}

// clasa meniu singleton
class Meniu{
private:
    static Meniu *instanta;
    Meniu(){
        minuteTrecute = 0;
    }
    vector<shared_ptr<Card>> carduri;
    vector<AparatValidare> aparate;
    int minuteTrecute;
public:
    Meniu *instantiaza(){
        if(instanta == nullptr)
            instanta = new Meniu();
        return instanta;
    }
    void afiseazaOptiuni(){
        cout<<"0. Exit\n";
        cout<<"1. Creeaza un card\n";
        cout<<"2. Creeaza un aparat de validare\n";
        cout<<"3. Adauga un bilet la un card\n";
        cout<<"4. Valideaza un card\n";
        cout<<"5. Modifica minutul curent\n";
        cout<<"6. Afiseaza detaliile unui card\n";
        cout<<"7. Afiseaza detaliile unui aparat de validare\n";
    }
    void mainLoop();

};
void Meniu:: mainLoop(){
    while(true) {
        afiseazaOptiuni();
        cout << "Alegeti una dintre optiunile de mai sus introducand indicele: ";
        int opt;
        cin>>opt;
        cin.get();
        if(opt==0){
            break;
        }
        else if(opt==1){
            cout<<"Alegeti tipul de card pe care vreti sa il creati:\n 1.Card pentru suprafata\n 2.Card pentru subteran\n 3. Card tranzit\n ";
            int optiune;
            cout<<"optiune";
            cin>>optiune;
            cin.get();
            shared_ptr<Card> c;
            if(optiune == 1){
                c = make_shared<CardSuprafata>();
                cout<<"Cardul pentru suprafata a fost creat cu succes si are ID-ul: "<<c->getId()<<endl;
            }
            if(optiune == 2){
                c = make_shared<CardSubteran>();
                cout<<"Cardul pentru subteran a fost creat cu succes si are ID-ul: "<<c->getId()<<endl;
            }
            if(optiune == 3){
                c = make_shared<CardTranzit>();
                cout<<"Cardul pentru tranzit a fost creat cu succes si are ID-ul: "<<c->getId()<<endl;
            }
            carduri.push_back(c);
        }
        else if(opt==2){
            AparatValidare a;
            cin>>a;
            aparate.push_back(a);
            cout<<"Aparatul a fost creat cu succes\n";
        }
        else if(opt==3){
            cout<<"ID : ";
            int id;
            cin>>id;
            cin.get();
            for(auto c: carduri){
                cout<<"altceva";
                if(c->getId() == id)
                    cout<<"ceva";
                c->adaugaBilet();
            }
        }
        else if(opt==4){
            cout<<"ID-ul aparatului pentru care vreti sa validati cardul: ";
            int idAparat, idCard;
            cin>>idAparat;
            cin.get();
            cout<<"ID-ul cardului pe care vreti sa il validati: ";
            cin>>idCard;
            cin.get();
            for(auto a:aparate){
                if(a.getId() == idAparat)
                    for(auto c:carduri){
                        if(c->getId() == idCard){
                            c->valideaza();
                        }
                    }
                a.adScanare();
            }
        }
        else if(opt==5){
            cout<<"Numarul de minute care au trecut: ";
            int min;
            cin>>min;
            cin.get();
            minuteTrecute+= min;
            for(auto c:carduri){
                for(auto b: c->getBilete())
                    if(dynamic_pointer_cast<BiletTranzit>(c)){
                        b->setMinut(min);
                    }
            }
        }
        else if(opt==6){
            for(auto c:carduri){
                cout<<*c;
            }

        }
        else if(opt==7){
            cout<<"ID aparat de validare: ";
            int id;
            cin>>id;
            cin.get();
            for(auto a: aparate){
                if(a.getId() == id)
                    cout<<a<<endl;
            }
        }
    }
}
Meniu *Meniu:: instanta = nullptr;
int main() {
    Meniu *m = m->instantiaza();
    m->mainLoop();
    return 0;
}
