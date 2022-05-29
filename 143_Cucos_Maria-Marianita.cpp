/* Cucos Maria-Marianita, grupa 143
Compilator: MinGW, version: w64 9.0
Tutore de laborator: Deaconu Eduard Stefan
 */

#include<bits/stdc++.h>
using namespace std;

class IO {
private:
public:
    virtual istream &read(istream &is) {
        return is;
    }
    virtual ostream &write(ostream &os) const {
        return os;
    }
    friend istream &operator>>(istream &is, IO &base) {
        return base.read(is);
    }
    friend ostream &operator<<(ostream &os, const IO &base) {
        return base.write(os);
    }
};
class Bilet_tranzit;

class Ora {
private:
    int ora;
    int minute;
public:
    friend class Bilet;
    Ora(){
        ora=0;
        minute=0;
    }
    Ora(int _ora, int _minute);
    const Ora &operator=(const Ora& ob);
    int getOra() const;
    int getMinute() const;
    void setOra(int _ora);
    void setMinute(int _min);
};
Ora::Ora(int _ora, int _minute) {
    ora=_ora;
    minute=_minute;
}
int Ora::getMinute() const {
    return minute;
}
int Ora::getOra() const {
    return ora;
}
void Ora::setMinute(int _min) {
    minute=_min;
}
void Ora::setOra(int _ora) {
    ora=_ora;
}
const Ora &Ora::operator=(const Ora &ob) {
    minute=ob.minute;
    ora=ob.ora;
    return *this;
}



class Bilet : public IO{
protected:
//    int pret;
    bool validat;
    Ora validare;

public:
    Bilet(){validat= false;}
    Bilet( bool _validat, Ora _validare);

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

};

istream &Bilet::read(istream &is) {
    IO::read(is);
//    cout<<"validat: (1-true, 0-false)";
    validat= false;
//
//    cout<<"introduceti ora curenta(ora minute): ";
//    is>>validare.ora>>validare.minute;
    return is;
}

ostream &Bilet::write(ostream &os) const {
    IO::write(os);
    os<<endl<<"este validat? "<<validat;
    if(validat)
        os<<endl<<"ora validare: "<<validare.ora<<" : "<<validare.minute;
    return os;
}

Bilet::Bilet( bool _validat, Ora _validare) {

    validare=_validare;
    validat=_validat;
}


class Bilet_suprafata: virtual public Bilet{
protected:
    const double pret_supr=2;
public:
    Bilet_suprafata(){}

    const double getPretSupr() const;

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

istream &Bilet_suprafata::read(istream &is) {
    Bilet::read(is);
    return is;
}

ostream &Bilet_suprafata::write(ostream &os) const {
    Bilet::write(os);
    return os;
}

const double Bilet_suprafata::getPretSupr() const {
    return pret_supr;
}


class Bilet_metrou : virtual public Bilet{
protected:
    const double pret_metrou=2.5;
public:
    Bilet_metrou(){}

    const double getPretMetrou() const ;

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

istream &Bilet_metrou::read(istream &is) {
    Bilet::read(is);
    return is;
}

ostream &Bilet_metrou::write(ostream &os) const {
    Bilet::write(os);
    return os;
}

const double Bilet_metrou::getPretMetrou() const {
    return pret_metrou;
}

class Bilet_tranzit : public Bilet_suprafata, public Bilet_metrou{
public:
    Bilet_tranzit(){}

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

private:
    const double pret_tranzit=3;
    Ora ora_sfarsit;
public:

};

istream &Bilet_tranzit::read(istream &is) {
    Bilet_suprafata::read(is);
    return is;
}

ostream &Bilet_tranzit::write(ostream &os) const {
    Bilet_suprafata::write(os);
    return os;
}


class Card : public IO{
protected:
    static int ID_card;     //nu pot fi clonate
public:
    Card() {++ID_card;}
    virtual ~Card(){
        --ID_card;
    }

    static int getIdCard();
    static void setIdCard(int _idCard);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

};

istream &Card::read(istream &is) {
    IO::read(is);
    return is;
}

ostream &Card::write(ostream &os) const {
    IO::write(os);
    return os;
}

int Card::ID_card=0;

int Card::getIdCard() {
    return ID_card;
}
void Card::setIdCard(int _idCard) {
    ID_card = _idCard;
}

class Card_suprafata: public Card, public IO{
private:
    bool b_supraf;
    bool b_metrou;
    vector<Bilet_suprafata> bilete_suprafata;
    vector<Bilet_metrou> bilete_metrou;
public:
    Card_suprafata(bool _bSupraf, bool _bMetrou, const vector<Bilet_suprafata> &_bileteSuprafata,
                   const vector<Bilet_metrou> &_bileteMetrou);
    Card_suprafata(){}

    bool getBSupraf() const;
    void setBSupraf(bool _bSupraf);
    bool getBMetrou() const;
    void setBMetrou(bool _bMetrou);
    const vector<Bilet_suprafata> &getBileteSuprafata() const;
    void setBileteSuprafata(const vector<Bilet_suprafata> &bileteSuprafata);
    const vector<Bilet_metrou> &getBileteMetrou() const;
    void setBileteMetrou(const vector<Bilet_metrou> &bileteMetrou);

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;



//    functie adaugare bilet dupa 8 validate

};


istream &Card_suprafata::read(istream &is) {
    Card::read(is);
    cout<<"exista bilete de suprafata? ";
    is>>b_supraf;
    if(b_supraf){
        cout<<"cate: ";
        int m;
        is>>m;
        for(int i = 0;i < m; ++i){
            Bilet_suprafata bilet;
            is>>bilet;
            bilete_suprafata.push_back(bilet);}

    }
    cout<<"exista bilete de metrou? ";
    is>>b_metrou;
    if(b_metrou){
        cout<<"cate: ";
        int m;
        is>>m;
        for(int i = 0;i < m; ++i){
            Bilet_metrou b;
            is>>b;
            bilete_metrou.push_back(b);
        }
    }

    return is;
}
//
//ostream &Card_suprafata::write(ostream &os) const {
//    IO::write(os);
//
//    return os;
//}

Card_suprafata::Card_suprafata(bool _bSupraf, bool _bMetrou, const vector<Bilet_suprafata > &_bileteSuprafata,
                               const vector<Bilet_metrou > &_bileteMetrou):bilete_metrou(_bileteMetrou), bilete_suprafata(_bileteSuprafata) {
    b_supraf=_bSupraf;
    b_metrou=_bMetrou;
}

const vector<Bilet_suprafata> &Card_suprafata::getBileteSuprafata() const {
    return bilete_suprafata;
}
void Card_suprafata::setBileteSuprafata(const vector<Bilet_suprafata> &bileteSuprafata) {
    bilete_suprafata = bileteSuprafata;
}
const vector<Bilet_metrou> &Card_suprafata::getBileteMetrou() const {
    return bilete_metrou;
}
void Card_suprafata::setBileteMetrou(const vector<Bilet_metrou> &bileteMetrou) {
    bilete_metrou = bileteMetrou;
}
bool Card_suprafata::getBSupraf() const {
    return b_supraf;
}
void Card_suprafata::setBSupraf(bool _bSupraf) {
    b_supraf = _bSupraf;
}
bool Card_suprafata::getBMetrou() const {
    return b_metrou;
}
void Card_suprafata::setBMetrou(bool _bMetrou) {
    b_metrou = _bMetrou;
}


class Card_subteran : public Card, public IO{

private:
    bool b_supraf;
    bool b_metrou;
    vector<Bilet_suprafata> bilete_suprafata;
    vector<Bilet_metrou> bilete_metrou;
public:
    Card_subteran(){}

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
    //    functie adaugare bilet dupa 8 validate

};

istream &Card_subteran::read(istream &is) {
    Card::read(is);
    cout<<"exista bilete de suprafata? ";
    is>>b_supraf;
    if(b_supraf){
        cout<<"cate: ";
        int m;
        is>>m;
        for(int i = 0;i < m; ++i){
            Bilet_suprafata bilet;
            is>>bilet;
            bilete_suprafata.push_back(bilet);}

    }
    cout<<"exista bilete de metrou? ";
    is>>b_metrou;
    if(b_metrou){
        cout<<"cate: ";
        int m;
        is>>m;
        for(int i = 0;i < m; ++i){
            Bilet_metrou b;
            is>>b;
            bilete_metrou.push_back(b);
        }
    }
    return is;
}

//ostream &Card_subteran::write(ostream &os) const {
//    IO::write(os);
//
//    return os;
//}

class Card_tranzit : public Card, public IO{
public:
    istream &read(istream &is) override;


    //    functie adaugare bilet dupa 8 validate
private:
    vector<Bilet_tranzit> bilete_tranzit;



};

istream &Card_tranzit::read(istream &is) {
    Card::read(is);
    cout<<"bilete de metrou? ";

    cout << "cate: ";
    int m;
    is >> m;
    for (int i = 0; i < m; ++i) {
        Bilet_metrou b;
        is >> b;
//        bilete_tranzit.push_back(b);
    }
    return is;
}



class Aparat{
private:
    int nr_scanari;
    bool locatie_suprafata;
    bool locatie_metrou;

public:
    Aparat() {}

};



class Meniu {
private:
    Meniu(){}
    static Meniu *instanta;
    vector<Card*> carduri;


public:
    static Meniu *getInstanta(){
        if(instanta== nullptr)
            instanta = new Meniu();
        return instanta;
    }

    static void delInstanta(){
        if(instanta != nullptr)
            delete instanta;
        instanta= nullptr;

    }

    void afiseazaOptiuni();
    int optiune();
    void mainLoop();

};
Meniu *Meniu::instanta= nullptr;

void Meniu::afiseazaOptiuni() {
    cout<<endl;
    cout << "1.Crearea unui card. \n";
    cout << "2. \n";
    cout << "3. \n";
    cout << "4. \n";

    cout << "5.Stop\n";
}

int Meniu::optiune() {
    int opt;
    cout << "optiune: ";
    cin >> opt;
    cin.get();
    return opt;
}

void Meniu::mainLoop() {
    while (true) {
        afiseazaOptiuni();
        int opt = optiune();

        if (opt == 1) {
            cout<<"numar: ";
            int m; cin>>m;
            for(int i = 0;i < m; ++i){
                int tip;
                Card *p = nullptr;
                while(true){
                    try{
                        cout<<"Tipul: (1=suprafata, 2=metrou, 3=tranzit):";
                        cin>>tip;
                        if(tip == 1){
                            p = new Card_suprafata;
                            break;
                        }
                        else if(tip == 2){
                            p = new Card_subteran;
                            break;}
                        else if(tip == 3){
                            p = new Card_tranzit;
                            break;}
                        else throw string("Tip incorect!");
                    }
                    catch(string s){
                        cout << s << '\n';
                    }
                }
                cin >> *p;
                carduri.push_back(p);
            }

        }
        if (opt == 2) {

        }
        if (opt == 3) {

        }
        if (opt == 4) {

        }
        if (opt == 5)
            break;
    }
}


int main() {

    Meniu* m = m->getInstanta();
    m->mainLoop();
    m->delInstanta();
    return 0;
}






















