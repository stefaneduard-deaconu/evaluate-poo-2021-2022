/*
Tanasa Florin Petrisor
Deaconu Stefan Eduard
GNU g++ MinGW w64 9.0
*/

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

int OraCurenta = 0;
int MinutCurent = 0;

class IoBase{
public:
    virtual istream &read(istream &is){return is;}
    virtual ostream &write(ostream &os) const {return os;}
    friend istream& operator>>(istream &is, IoBase& base){return base.read(is);}
    friend ostream& operator<<(ostream &os, const IoBase& base){return base.write(os);}
};

template<class A> istream& operator>>(istream& is, vector<A> vector){
    cout<<"Elemente: ";
    int n;
    is>>n;
    for(int i=0;i<n;i++){
        A x;
        is>>x;
        vector.push_back(x);
    }
    return is;
}

template<class A> ostream& operator<<(ostream& os, const vector<A>& vector){
    os<<endl<<"Elemente: ";
    for(const auto &x:vector){
        os<<x<<" ";
    }
    return os;
}

class BiletSuprafata :public IoBase{
    static float TaxaSuprafata;
public:
    BiletSuprafata(){}
    ostream &write(ostream &os) const override{
        IoBase::write(os);

        cout<<"Taxa: ";
        cout<<TaxaSuprafata;

        return os;
    }
    friend ostream& operator<<(ostream &os, const BiletSuprafata& base){return base.write(os);}
};

float BiletSuprafata::TaxaSuprafata = 2;

class BiletMetrou :public IoBase{
    static float TaxaMetrou;
public:
    BiletMetrou(){}
    ostream &write(ostream &os) const override{
        IoBase::write(os);

        cout<<"Taxa: ";
        cout<<TaxaMetrou;

        return os;
    }
    friend ostream& operator<<(ostream &os, const BiletMetrou& base){return base.write(os);}
};

float BiletMetrou::TaxaMetrou = 2.5;

class BiletTranzit : public IoBase {
    static float TaxaTranzit;
    int minut;
    int ora;
public:
    BiletTranzit(){}

    istream &read(istream &is) override{
        IoBase::read(is);

        cout<<"Ora achizitiei: ";
        is>>ora;
        cout<<"Minutul achizitiei: ";
        is>>minut;

        return is;
    }

    ostream &write(ostream &os) const override{
        IoBase::write(os);

        cout<<"Taxa: ";
        os<<TaxaTranzit<<endl;
        cout<<"Ora achizitiei: ";
        os<<ora<<endl;
        cout<<"Minutul achizitiei: ";
        os<<minut<<endl;

        return os;
    }
    friend ostream& operator<<(ostream &os, const BiletTranzit& base){return base.write(os);}

    friend istream& operator>>(istream &is, BiletTranzit& base){return base.read(is);}

    int getOra(){
        return ora;
    }
    int getMinut(){
        return minut;
    }
    void setMinut(int a){
        minut=a;
    }
    void setOra(int a){
        ora = a;
    }
};

float BiletTranzit::TaxaTranzit=3;

class Card : public IoBase{
protected:
    static int ID;
    string Tip;
    int numarCalatorii;
    static int AutoGenerare;
    vector<BiletTranzit> tranzit;
public:
    Card(){}
    istream &read(istream &is) override{
        IoBase::read(is);
        AutoGenerare++;
        if(AutoGenerare == 8){
            AutoGenerare = 0;
            numarCalatorii++;
            cout<<"Felicitare! Ati primit o calatorie in plus.";
        }
        cout<<"Tipul cardului: ";
        is>>Tip;
        ID++;
        if(Tip == "tranzit") {
            cout << "Numarul calatoriilor: ";
            is >> tranzit;
        }
        else{
            cout<<"Numarul calatoriilor de suprafata: ";
            is>> numarCalatorii;
        }
        return is;
    }
    ostream &write(ostream &os) const override{
        IoBase::write(os);

        cout<<"Tip: ";
        os<<Tip;
        cout<<"Numarul de calatorii ramase este ";
        os<<numarCalatorii<<endl;
        cout<<"Numarul de calatori pana la prima gratuita ";
        os<<8-AutoGenerare<<endl;
        cout<<"ID: ";
        os<<ID<<endl;

        return os;
    }

    friend ostream& operator<<(ostream &os, const Card& base){return base.write(os);}

    friend istream& operator>>(istream &is, Card& base){return base.read(is);}

    const string &getTip(){
        return Tip;
    };

    int getID(){
        return ID;
    }

    int getNrCalatorii(){
        return numarCalatorii;
    }

    void setNrCalatorii(int a){
        numarCalatorii = a;
    }

    void AdaugareBilet(){
        if(Tip == "tranzit"){
            cout<<"Numarul biletelor de tranzit: ";
            int n;
            cin>>n;
            for(int i=0;i<n;i++){
                BiletTranzit x;
                cin>>x;
                tranzit.push_back(x);
            }
        }
        else{
            cout<<"Numarul de bilete de adaugat: ";
            int n;
            cin>>n;
            numarCalatorii = numarCalatorii + n;
        }
    }

    vector<BiletTranzit> getTranzit(){
        return tranzit;
    }
};

int Card :: ID = 0;
int Card :: AutoGenerare =0;

class Validator:public IoBase{
    static int Scanari;
    static int ID;
    string tip;
public:
    Validator() = default;
    istream &read(istream &is) override{
        IoBase::read(is);

        cout<<"Tipul validatorului: ";
        is>>tip;
        cout<<"ID: ";
        ID++;
        cout<<ID;

        return is;
    }

    ostream &write(ostream &os) const override{
        IoBase::write(os);

        cout<<"Tipul validatorului: ";
        os<<tip<<endl;
        cout<<"ID: ";
        os<<ID<<endl;
        cout<<"Numarul de scanari: ";
        os<<Scanari;

        return os;
    }

    bool Validare(Card A){
        Scanari ++;
        if(A.getTip()=="tranzit" && tip=="tranzit"){
            if(A.getNrCalatorii()>0) {
                vector<BiletTranzit> bilete = A.getTranzit();
                if(MinutCurent != 0 || OraCurenta !=0) {
                    for (auto &x: bilete) {
                        if ((OraCurenta*60+MinutCurent - x.getOra()*60 - x.getMinut())==90)
                        {
                            x.setMinut(-31);
                            x.setOra(-1);
                            return true;
                        }
                    }
                }
                else{return true;}
            }
        }
        else if(A.getTip()!="tranzit" && tip !="tranzit"){
            if(A.getNrCalatorii()>0) {
                int n = A.getNrCalatorii();
                n--;
                A.setNrCalatorii(n);
                return true;
            }
        }
        return false;
    }

    friend ostream& operator<<(ostream &os, const Validator& base){return base.write(os);}

    friend istream& operator>>(istream &is, Validator& base){return base.read(is);}

    int getID(){
        return ID;
    }
};

int Validator::ID=0;
int Validator::Scanari=0;

class BaseMenu : public IoBase{
public:
    BaseMenu() = default;
    virtual void listOptions(){}
    virtual void mainLoop(){}
    virtual int chooseOption(int first,int last){
        int numarOptiune;
        cin>>numarOptiune;
        return numarOptiune;
    }
};

class SimpleMenu:public BaseMenu{
    vector<Card> Carduri;
    vector<Validator> Validatori;
public:
    SimpleMenu() = default;
    void listOptions(){
        cout<<"1. Creare card"<<endl;
        cout<<"2. Creare aparat validare"<<endl;
        cout<<"3. Adaugare bilet card"<<endl;
        cout<<"4. Validare card"<<endl;
        cout<<"5. Modificare minut curent"<<endl;
        cout<<"6. Afisare detalii card"<<endl;
        cout<<"7. Afisare detalii validator"<<endl;
        cout<<"8. Iesire"<<endl;
    }

    int chooseOption(int first,int last) override{
        int optiune = -1;
        while(optiune<first || optiune > last){
            cout<<endl<<"Pentru a rula programul introduceti un numar intre "<<first<<" si "<<last<<endl;
            listOptions();
            cout<<endl<<"Alegere: ";
            cin>>optiune;
        }
        return optiune;
    }
    void option1(){
        Card x;
        cin>>x;
        Carduri.push_back(x);
    }
    void option2(){
        Validator x;
        cin>>x;
        Validatori.push_back(x);
    }
    void option3(){
        cout<<"Introduceti ID-ul cardului: ";
        int n;
        cin>>n;

        for(auto &x:Carduri){
            if(x.getID() == n){
                x.AdaugareBilet();
                break;
            }
        }
    }
    void option4(){
        cout<<"Introduceti ID-ul cardului: ";
        int n;
        cin>>n;

        cout<<"Introduceti ID-ul validatorului: ";
        int y;
        cin>>y;

        for(auto &x:Carduri){
            if(x.getID() == n){
                for(auto &z:Validatori){
                    if(z.getID() == y){
                        if(z.Validare(x) == true){
                            cout<<"Cardul a fost validat.";
                        }
                        else{
                            cout<<"Cardul nu a fost validat.";
                        }
                    }
                }
            }
        }
    }
    void option5(){
        cout<<"Minut curent: ";
        cin >> MinutCurent;
        cout<<"Ora curenta: ";
        cin >> OraCurenta;
    }
    void option6(){
        cout<<"Din pacate nu am avut timp sa implementez si aceasta optiune...";
    }
    void option7(){
        cout<<"Introduceti ID-ul validatorului: ";
        int n;
        cin>> n;
        for(auto &x:Validatori){
            if(x.getID() == n){
                cout<<x;
                break;
            }
        }
    }

    virtual void mainLoop() override{
        while(true) {
            int optiune = chooseOption(1, 8);
            if (optiune == 1) {
                option1();
            } else if (optiune == 2) {
                option2();
            } else if (optiune == 3) {
                option3();
            } else if (optiune == 4) {
                option4();
            } else if (optiune == 5) {
                option5();
            } else if (optiune == 6) {
                option6();
            } else if (optiune == 7) {
                option7();
            } else if (optiune == 8) {
                break;
            }
        }
        cout<<endl<<"------------------------------------"<<endl<<"Programul s-a incheiat cu succes.";
    }

};

int main(){
    SimpleMenu meniu;
    meniu.mainLoop();
}