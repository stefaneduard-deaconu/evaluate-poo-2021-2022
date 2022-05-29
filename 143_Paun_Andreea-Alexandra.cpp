/* Nume Prenume Grupa: Păun Andreea-Alexandra, Grupa 143
Compilator: CLion GNU g++ MinGW w64 9.0
Tutore de laborator: Ștefan Eduard Deaconu */



#include <iostream>

using namespace std;

class IoBase {
private:
public:
    virtual istream &read(istream &is) {
        return is;
    }

    virtual ostream &write(ostream &os) const {
        return os;
    }


    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};



class Bilet: public IoBase{
    protected:
       string tip;
       float taxa;
       int ora;
       int minute;

    public:
    const string &getTip() const;

    float getTaxa() const;

    int getOra() const;

    int getMinute() const;

    Bilet(const Bilet &ob);

    Bilet(const string &tip);

    virtual ~Bilet();

    Bilet(const string &tip, float taxa, int ora, int minute);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    void setTip(const string &tip);

    void setTaxa(float taxa);

    void setOra(int ora);

    void setMinute(int minute);

    Bilet(){
     tip="";
     ora=0;
     minute=0;
     taxa=0;
    }

};


Bilet::Bilet(const Bilet &ob)
{  tip=ob.tip;
    taxa=ob.taxa;
    ora=ob.ora;
    minute=ob.minute;
}



istream &Bilet::read(istream &is) {
    IoBase::read(is);
    cout<<"Introduceti tipul biletului: \n";
    is.get();
    getline(is, tip);
    if (tip=="suprafata")
    {cout<<"Pretul unui bilet de suprafata este de: ";
        taxa=2;
        cout<<taxa<<"\n";
    }
    else if (tip=="metrou")
    {cout<<"Pretul unui bilet de metrou este de: ";
        taxa=2.5;
        cout<<taxa<<"\n";
    }
    else if (tip=="tranzit")
    {cout<<"Pretul unui bilet de tranzit este de: ";
        taxa=2.5;
        cout<<taxa<<"\n";
    }
    cout << "Introduceti ora\n";
    int ora;
    while(true){
        try {
            is >> ora;
            is.get();
            if(ora < 0 || ora > 24)
                throw string("Ora invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->ora=ora;
    cout << "Introduceti minutul\n";
    int minut;
    while(true){
        try {
            is >> minut;
            is.get();
            if(minut < 0 || minut > 59)
                throw string("Minut invalid!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->minute=minut;
}

ostream &Bilet::write(ostream &os) const {
    IoBase::write(os);
    os<<"Tip bilet: "<<tip<<"\n";
    os<<"Taxa bilet: "<<taxa<<"\n";
    os<<"Ora: "<<ora<<"/"<<minute<<"\n";
}

Bilet::Bilet(const string &tip) : tip(tip) {}

Bilet::Bilet(const string &tip, float taxa, int ora, int minute) : tip(tip), taxa(taxa), ora(ora), minute(minute) {}

const string &Bilet::getTip() const {
    return tip;
}

float Bilet::getTaxa() const {
    return taxa;
}

int Bilet::getOra() const {
    return ora;
}

int Bilet::getMinute() const {
    return minute;
}

void Bilet::setTip(const string &tip) {
    Bilet::tip = tip;
}

void Bilet::setTaxa(float taxa) {
    Bilet::taxa = taxa;
}

void Bilet::setOra(int ora) {
    Bilet::ora = ora;
}

void Bilet::setMinute(int minute) {
    Bilet::minute = minute;
}


class Card: public IoBase{
 protected:
    string tip;
    int ora;
    int minute;
    string ultim_bilet;
    int suma;
 public:
    Card(){
        tip="";
        ora=0;
        minute=0;
        ultim_bilet="";
        suma=0;
    }

    const string &getTip() const;

    int getOra() const;

    int getMinute() const;

    virtual ~Card();

    void setTip(const string &tip);

    void setOra(int ora);

    void setMinute(int minute);

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;



};


istream &Card::read(istream &is) {
    IoBase::read(is);
    cout<<"Introduceti tipul cardului: \n";
    is.get();
    getline(is, tip);
    cout << "Introduceti ora:\n";
    int ora;
    while(true){
        try {
            is >> ora;
            is.get();
            if(ora < 0 || ora > 24)
                throw string("Ora invalida!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->ora=ora;
    cout << "Introduceti minutul:\n";
    int minut;
    while(true){
        try {
            is >> minut;
            is.get();
            if(minut < 0 || minut > 59)
                throw string("Minut invalid!");
            else break;
        }
        catch (string s){
            cout << s << '\n';
        }
    }
    this->minute=minut;

}


    ostream &Card::write(ostream &os) const {
        IoBase::write(os);
    }

    const string &Card::getTip() const {
        return tip;
    }
    int Card::getOra() const {
        return ora;
    }
    int Card::getMinute() const {
        return minute;
    }

void Card::setTip(const string &tip) {
    Card::tip = tip;
}

void Card::setOra(int ora) {
    Card::ora = ora;
}

void Card::setMinute(int minute) {
    Card::minute = minute;
}




class Aparat_validare: public virtual Bilet, public virtual Card {
protected:
    string locatie;
    int numar_scanari;
public:
    Aparat_validare() =default;

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    ~Aparat_validare() override;

    void setLocatie(const string &locatie);

    void setNumarScanari(int numarScanari);

    const string &getLocatie() const;

    int getNumarScanari() const;


};




Aparat_validare::~Aparat_validare() {
    locatie="";
    numar_scanari=0;

}

istream &Aparat_validare::read(istream &is) {
    Card::read(is);
    cout<<"Locatia aparatului de validare este:\n";
    is>>locatie;
    cout<<"Numarul de scanari este:\n";
    numar_scanari=0;
    while(true){
        try{
            cout<<"Numarul de scanari este:\n";
            is>>numar_scanari;
            if(numar_scanari<0)
                throw string ("Nu e bine!");
            else
                break;
        }
        catch (string s){
            cout<<s<<"\n";
        }
    }

}

ostream &Aparat_validare::write(ostream &os) const {
    Card::write(os);
    os<<locatie<<"\n";
    os<<numar_scanari<<"\n";

}

void Aparat_validare::setLocatie(const string &locatie) {
    Aparat_validare::locatie = locatie;
}

void Aparat_validare::setNumarScanari(int numarScanari) {
    numar_scanari = numarScanari;
}

const string &Aparat_validare::getLocatie() const {
    return locatie;
}

int Aparat_validare::getNumarScanari() const {
    return numar_scanari;
}


//class BaseMenu {
//public:
//    virtual void listOptions() {}
//
//    virtual int chooseOption(int first, int last) {}
//
//    virtual void mainLoop() {}
//};
//
//

//
//class SimpleMenu : public BaseMenu {
//private:
////    vector<Bilet *> bilete;
////    vector<Card *> carduri;
//public:
//    void listOptions() override {
//        cout << "1. Adauga card." << '\n';
//        cout << "2. Creeaza aparat de validare." << '\n';
//        cout << "3. Adauga un bilet la un card" << '\n';
//        cout << "4. Valideaza card." << '\n';
//        cout << "5. Modifica minutul curent." << '\n';
//        cout << "6. Afiseaza detalii card." << '\n';
//        cout << "7. Afiseaza detalii aparat de validare." << '\n';
//    }
//    int chooseOption(int first, int last) override {
//        int option = -1;
//        while (option < first || option > last) {
//            cout << '\n';
//            cout << "Pentru a rula comanda, alegeti un numar intre "
//                 << first << " si " << last << '\n';
//            listOptions();
//            cout << "Alegere: ";
//            cin >> option;
//        }
//        return option;
//    }
//
//    void option1();
//
//    void option2();
//
//    void option3();
//
//    void option4();
//
//    void option5();
//
//    void option6();
//
//    void option7();
//
//
//    void mainLoop() override {
//        while (true) {
//            int option = chooseOption(1, 7);
//            if (option == 1) {
//                option1();
//            } else if (option == 2) {
//                option2();
//            } else if (option == 3) {
//                option3();
//            }else if (option == 4) {
//                option4();
//            }else if (option == 5) {
//                break;
//            }
//            else if (option == 6) {
//                break;
//            }
//            else if (option == 7) {
//                break;
//            }
//        }
//        cout << '\n'
//             << "---------------------------------"
//             << '\n'
//             << "Programul s-a incheiat cu success";
//    }
//
//};
//
//
//int main() {
//    SimpleMenu menu;
//    menu.mainLoop();
//}