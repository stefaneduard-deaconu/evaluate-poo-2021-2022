/*Lung Alexandra
 * Grupa 143
 * Compilator:(mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64)6.0
 * Tutore de laborator:Stefan Eduard Deaconu
 * */
#include <bits/stdc++.h>
using namespace std;
class CitireScriere{
public:
    // metoda citire
    virtual istream &read(istream &is) {
        return is;
    }

    // metoda scriere
    virtual ostream &write(ostream &os) const {
        return os;
    }

    //redefinire operator  <<
    friend ostream &operator<<(ostream &os, const CitireScriere &base) {
        return base.write(os);
    }
    //redefinire operator  >>
    friend istream &operator>>(istream &is, CitireScriere &base) {
        return base.read(is);
    }
};
//creare clasa bilet
class Bilet:public CitireScriere{
protected:
    double pret;
};

//creare clasa bilet supraf
class BiletSupraf:public Bilet{

public:
    BiletSupraf(){
        pret = 2;
    }
};

//creare clasa bilet metrou
class BiletMetrou:public Bilet{

public:
    BiletMetrou(){
        pret = 2.5;
    }
};

//creare clasa bilet tranzit
class BiletTranzit:public Bilet{
protected:
    int timp;
public:
    BiletTranzit(){
    pret = 3;
    timp = 90;
}
};

//creare clasa card
class Card:public CitireScriere{
protected:
    static int id;
    int id_c;
public:
    Card() {
        id_c = id++;
    }
    int getIdc();
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};
int Card::getIdc() {
    return id_c;
}
istream &Card :: read(istream &is){
    return is;
}
ostream &Card ::write(ostream &os) const {
    return os;
}

int Card::id =1;


//creare clasa card suprafata
class CardSupraf:public Card{
protected:
vector<Bilet*> bilete;

vector<bool> validare;
public:
CardSupraf():Card(){}
CardSupraf(vector<Bilet*> bilete):bilete(bilete){}
void validare1();
istream &read(istream &is) override;
ostream &write(ostream &os) const override;

    void setBilete(const vector<Bilet *> &bilete);

    const vector<Bilet *> &getBilete() const;
};
void CardSupraf:: validare1(){
    for(int i=0;i<validare.size();++i)
        if(validare[i]==false) {
            validare[i] = true;
            break;
        }
    int nr=0;
    for(int i=0;i<validare.size();++i)
        if(validare[i]==true) {
        nr++;
        }
    if(nr%8==0) {
        BiletSupraf *x = new BiletSupraf();
        bilete.push_back(x);
    }
}
istream &CardSupraf ::read(istream &is){
    cout<<"Introdu numarul de bilete de pe card:";
    int n;
    cin >> n;
    bilete.resize(n);
    for(int i=0;i<n;++i){
        cout<<"Alege tipul biletului:\n";
        cout<<"1.Bilet suprafata\n";
        cout<<"2.Bilet subteran\n";
        int opt;
        cin >>opt;
        if(opt ==1){
            BiletSupraf *x = new BiletSupraf();
            bilete.push_back(x);
        }
      else  if(opt ==2){
            BiletMetrou *x = new BiletMetrou();
            bilete.push_back(x);
        }

    }
    return is;
}
ostream &CardSupraf ::write(ostream &os) const {
    cout<<"Id card:"<<id_c <<"\n";
    cout<<"Avem " <<bilete.size() << "bilete pe acest card";
    return os;
}

const vector<Bilet *> &CardSupraf::getBilete() const {
    return bilete;
}

void CardSupraf::setBilete(const vector<Bilet *> &bilete) {
    CardSupraf::bilete = bilete;
}

//creare clasa card subteran
class CardSubteran:public Card{
protected:
    vector<Bilet*> bilete;
    vector<bool> validare;
public:
    CardSubteran():Card(){

    }
    CardSubteran(vector<Bilet*> bilete):bilete(bilete){}
    void validare1();
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    void setBilete(const vector<Bilet *> &bilete);

    const vector<Bilet *> &getBilete() const;
};
void CardSubteran:: validare1(){
    for(int i=0;i<validare.size();++i)
        if(validare[i]==false) {
            validare[i] = true;
            break;
        }
    int nr=0;
    for(int i=0;i<validare.size();++i)
        if(validare[i]==true) {
            nr++;
        }
    if(nr%8==0) {
        BiletMetrou *x=new BiletMetrou();
        bilete.push_back(x);
    }
}
istream &CardSubteran ::read(istream &is){
    cout<<"Introdu numarul de bilete de pe card:";
    int n;
    cin >> n;
    bilete.resize(n);
    for(int i=0;i<n;++i)
    {
        cout<<"Alege tipul biletului:\n";
        cout<<"1.Bilet suprafata\n";
        cout<<"2.Bilet subteran\n";
        int opt;
        cin >>opt;
        if(opt ==1){
            BiletSupraf *x = new BiletSupraf();
            bilete.push_back(x);
        }
        else  if(opt ==2){
            BiletMetrou *x = new BiletMetrou();
            bilete.push_back(x);
        }

    }
    return is;
}
ostream &CardSubteran ::write(ostream &os) const {
    cout<<"Id card:"<<id_c <<"\n";
    cout<<"Avem " <<bilete.size() << "bilete pe acest card";
    return os;
}

const vector<Bilet *> &CardSubteran::getBilete() const {
    return bilete;
}

void CardSubteran::setBilete(const vector<Bilet *> &bilete) {
    CardSubteran::bilete = bilete;
}

//creare clasa card tranzit
class CardTranzit:public Card{
protected:
    vector<BiletTranzit> bilete;
    vector<bool> validare;
public:
    CardTranzit():Card(){

    }
    CardTranzit(vector<BiletTranzit> bilete):bilete(bilete){}
    void validare1();
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    void setBilete(const vector<BiletTranzit> &bilete);

    const vector<BiletTranzit> &getBilete() const;
};
void CardTranzit:: validare1(){
    for(int i=0;i<validare.size();++i)
        if(validare[i]==false) {
            validare[i] = true;
            break;
        }
    int nr=0;
    for(int i=0;i<validare.size();++i)
        if(validare[i]==true) {
            nr++;
        }
    if(nr%8==0) {
        BiletTranzit x;
        bilete.push_back(x);
    }
}
istream &CardTranzit ::read(istream &is){
    cout<<"Introdu numarul de bilete de pe card:";
    int n;
    cin >> n;
    bilete.resize(n);
    for(int i=0;i<n;++i)
    {
        BiletTranzit x;
        bilete.push_back(x);
    }
    return is;
}
ostream &CardTranzit ::write(ostream &os) const {
    cout<<"Id card:"<<id_c <<"\n";
    cout<<"Avem " <<bilete.size() << "bilete pe acest card";
    return os;
}


const vector<BiletTranzit> &CardTranzit::getBilete() const {
    return bilete;
}

void CardTranzit::setBilete(const vector<BiletTranzit> &bilete) {
    CardTranzit::bilete = bilete;
}

//creare clasa aparat
class Aparat: public CitireScriere{
private:
    static int id;
    int id_ap;
    int nr_scanari;
    string locatie;
public:
    Aparat(){id_ap  = id ++ ;nr_scanari = 0;}
    Aparat(string locatie):locatie(locatie) { }
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
    int GetIdAp();
};
int Aparat::GetIdAp() {
    return id_ap;
}
istream &Aparat ::read(istream &is){
    cout<<"Introdu locatie aparat:";
    is>> locatie;
    return is;
}
int Aparat::id =1;
ostream &Aparat::write(ostream &os) const {
    os<<"Locatie aparat:";
    os << locatie<<"\n";
    os<<"Numar scanari " << nr_scanari <<"\n";
    return os;
}

//creare meniu basic
class BaseMenu {
public:
    virtual void listOptions() = 0;

    virtual int chooseOption(int first, int last) = 0;

    virtual void mainLoop() = 0;


};
//creare meniu interactiv
class Menu : public BaseMenu {
private:
    Menu() = default;
vector<Card*> carduri;
vector<Aparat> aparate;
    static Menu *menu;

public:

    static Menu *getMenu() {
        if (menu != nullptr) {
            return menu;
        }
        menu = new Menu();
        return menu;
    }


    void listOptions() override {
        cout << "1.Creare card"<<"\n";
        cout << "2.Creare aparat validare"<<"\n";
        cout << "3.Adaugare Bilet card"<<"\n";
        cout << "4.Validare Card"<<"\n";
        cout << "5.Modificare minut curent"<<"\n";
        cout << "6.Afisare detalii card"<<"\n";
        cout << "7.Afisare detalii aparat"<<"\n";

    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeti un numar intre " << first << " si " << last << '\n';
            listOptions();
            cout << "Alegere:";
            cin >> option;
        }
        return option;
    }

    void option1() {
        cout<<"Alege tip card:\n";
        cout<<"1.Card Suprafata\n";
        cout<<"2.Card Subteran\n";
        cout<<"3.Card Tranzit\n";
        int opt;
        cin >> opt;
        if(opt == 1){
            CardSupraf *x = new CardSupraf();
            cin >>*x;
            carduri.push_back(x);
        }else if(opt==2){
            CardSubteran *x = new CardSubteran();
            cin >>*x;
            carduri.push_back(x);
        }else {
            CardTranzit *x = new CardTranzit();
            cin >>*x;
            carduri.push_back(x);
        }
        /*carduri adaugate
        for(int i=0;i<carduri.size();++i)
            cout<<*carduri[i]<<"\n";
        */
    }

    void option2() {
        Aparat x;
        cin >> x;
        aparate.push_back(x);
    }

    void option3() {
        cout<<"Introdu id card:";
        string tip;
        int x, ok=0;
        cin>>x;
        cout<<"Introdu tip card(suparafata, trsanzit, subteran):";
        cin >> tip;
        for(int  i=0;i<carduri.size();++i)
            if(carduri[i]->getIdc() == x){
                if(tip == "tranzit") {ok=1;
                    auto *y = dynamic_cast<CardTranzit *>(carduri[i]);
                   vector<BiletTranzit> z = y->getBilete();
                    BiletTranzit x;
                    z.push_back(x);
                    y->setBilete(z);
                }
                if(tip ==  "suprafata") {ok=1;
                    auto *d  = dynamic_cast<CardSupraf*>(carduri[i]);
                    vector<Bilet*> z = d->getBilete();
                    cout<<"Alege tipul biletului:\n";
                        cout<<"1.Bilet suprafata\n";
                        cout<<"2.Bilet subteran\n";
                        int opt;
                        cin >>opt;
                        if(opt ==1){
                            BiletSupraf *x = new BiletSupraf();
                            z.push_back(x);
                        }
                        else  if(opt ==2){
                            BiletMetrou *x = new BiletMetrou();
                            z.push_back(x);
                        }
                    d->setBilete(z);
                }
                 if(tip == "subteran"){ok=1;
                     auto *x  = dynamic_cast<CardSubteran*>(carduri[i]);
                     vector<Bilet*> z = x->getBilete();
                     cout<<"Alege tipul biletului:\n";
                     cout<<"1.Bilet suprafata\n";
                     cout<<"2.Bilet subteran\n";
                     int opt;
                     cin >>opt;
                     if(opt ==1){
                         BiletSupraf *x = new BiletSupraf();
                         z.push_back(x);
                     }
                     else  if(opt ==2){
                         BiletMetrou *x = new BiletMetrou();
                         z.push_back(x);
                     }
                     x->setBilete(z);
                 }
                }
        if(ok==0)
            cout<<"Nu exista cardul introdus\n";

    }

    void option4() {
        cout<<"Introdu id card:";
        string tip;
        int x, ok=0;
        cin>>x;
        cout<<"Introdu tip card(suparafata, trsanzit, subteran):";
        cin >> tip;
        for(int  i=0;i<carduri.size();++i)
            if(carduri[i]->getIdc() == x) {
                if (tip == "tranzit") {
                    ok = 1;
                    auto *y = dynamic_cast<CardTranzit *>(carduri[i]);
                   y->validare1();
                   cout<<"card validat\n";

                }
                if (tip == "suprafata") {
                    ok = 1;
                    auto *d = dynamic_cast<CardSupraf *>(carduri[i]);
                  d->validare1();
                    cout<<"card validat\n";

                }
                if (tip == "subteran") {
                    ok = 1;
                    auto *x = dynamic_cast<CardSubteran *>(carduri[i]);
                    x->validare1();
                    cout<<"card validat\n";
                }
            }
        if(ok==0)
            cout<<"Nu exista cardul introdus\n";
    }
    void option5() {

    }
    void option6() {
        cout<<"Introdu id card:";
        string tip;
        int x, ok=0;
        cin>>x;
        cout<<"Introdu tip card(suparafata, trsanzit, subteran):";
        cin >> tip;
        for(int  i=0;i<carduri.size();++i)
            if(carduri[i]->getIdc() == x) {
                if (tip == "tranzit") {
                    ok = 1;
                    auto *y = dynamic_cast<CardTranzit *>(carduri[i]);
                    vector<BiletTranzit> z = y->getBilete();
                    cout << z[z.size() - 1] ;
                }
                if (tip == "suprafata") {
                    ok = 1;
                    auto *d = dynamic_cast<CardSupraf *>(carduri[i]);
                    vector<Bilet *> z = d->getBilete();
                    cout << *z[z.size() - 1];
                }
                if (tip == "subteran") {
                    ok = 1;
                    auto *x = dynamic_cast<CardSubteran *>(carduri[i]);
                    vector<Bilet *> z = x->getBilete();
                    cout << *z[z.size() - 1];
                }
            }
        if(ok==0)
            cout<<"Nu exista cardul introdus\n";
    }
    void option7() {
        cout<<"Introdu id aparat:";
        int x, ok=0;
        cin>>x;
        for(int i=0;i<aparate.size();++i)
            if(aparate[i].GetIdAp() == x){
                ok=1;
                cout << aparate[i] <<"\n";
            }
        if(ok==0)
            cout<<"Nu exista\n";
    }


    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 8);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            } else if (option == 4) {
                option4();
            } else if (option == 5) {
                option5();
            }else if (option == 6) {
                option6();
            }
            else if (option == 7) {
                option7();
            }
            else if (option == 8) {
                break;
            }
        }
        cout << '\n' << "---------------------------------" << '\n' << "Programul s-a incheiat cu success";
    }



};

Menu *Menu::menu = nullptr;


int main() {
    Menu *meniu = Menu::getMenu();
    meniu->mainLoop();
    return 0;
}
