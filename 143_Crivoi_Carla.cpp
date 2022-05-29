//Crivoi Carla 143
//Bundled MinGW w64 9.0
//gcc (GCC) 4.4.0
//Deaconu Stefan

#include <iostream>
#include <vector>
using namespace std;
class IoBase {
private:
public:
    virtual istream& read(istream& is) {
        return is;
    }
    virtual ostream& write(ostream& os) const {
        return os;
    }
    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }
    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};
//BILET
class Bilet:public IoBase{
protected:
    int tip; //0-suprafata,1-metrou,2-tarnzit
    double pret;
public:
    Bilet(int tip, double pret);
    Bilet(){
        tip=pret=0;
    }
    ~Bilet(){
        tip=pret=0;
    }
    virtual istream &read(istream &is);
    virtual ostream &write(ostream &os) const;
    int getTip(){
        return tip;
    }

};

Bilet::Bilet(int tip, double pret) : tip(tip), pret(pret) {
    this->tip=tip;
    this->pret=pret;
}

istream &Bilet::read(istream &is) {
    IoBase::read(is);
    cout<<"Tipul de bilet: 0-suprafata,1-metrou,2-tarnzit: ";
    while(true){
        try{
            is>>tip;
            if(tip!=1 and tip!=0 and tip!=2) throw string("Numar invalid! Tipul de bilet: 0-suprafata,1-metrou,2-tarnzit");
            else break;
        }
        catch(string s){
            cout << s << '\n';
        }
    }
    if(tip==0) pret=2;
    else if(tip==1) pret=2.5;
    else if(tip==3) pret=3;

    return is;
}

ostream &Bilet::write(ostream &os) const {
   IoBase::write(os);
   cout<<"Biletul este de tip ";
    if(tip==0) os<<"suprafata ";
    else if(tip==1) os<<"metrou ";
    else if(tip==3) os<<"tranzit ";
    os<<" si pretul este de "<<pret<<endl;
    return os;
}


//Card
class Card: public IoBase{
protected:
    static int ids;
    int id,nrBileteValidate;
public:
    Card(){
        id=0;
        nrBileteValidate=0;
    }
    ~Card(){
        id=nrBileteValidate=0;
    }
    Card(int id, const vector<Bilet> &bilete);
    virtual istream &read(istream &is);
    virtual ostream &write(ostream &os) const;

    int getId();

     void setId(int id);

};

Card::Card(int id, const vector<Bilet> &bilete) : id(id) {
    this->id=id;
}

istream &Card::read(istream &is) {
     IoBase::read(is);
    return is;
}

ostream &Card::write(ostream &os) const {
    IoBase::write(os);
    os<<" Cardul are id-ul "<<id<<endl;
    return os;
}

int Card::getId() {
    return id;
}

void Card::setId(int id) {
    Card::id = id;
}

// Card suprafata
class CardSuprafata:virtual public Card{
protected:
    vector<Bilet> bilete;
public:
    CardSuprafata(int id, const vector<Bilet> &bilete, const vector<Bilet> &bilete1) : Card(id, bilete),bilete(bilete1) {}
    CardSuprafata(){

    }

    virtual ~CardSuprafata() {
bilete.clear();
    }
    void AddBil(){
        Bilet b;
        while(true){
            try{
                cin>>b;
                if(b.getTip()==2) throw string("Adaugati un bilet de tranzit!");
                else break;
            }
            catch(string s){
                cout << s << '\n';
            }
        }
        bilete.push_back(b);
    };

    virtual istream &read(istream &is) {
         Card::read(is);
         int n;
         cout<<"Nr de bilete de pe card? "; is>>n;
         if(n!=0){
             for(int i=0;i<n;i++){
                 Bilet b;
                 while(true){
                     try{
                         cin>>b;
                         if(b.getTip()==2) throw string("Adaugati un bilet de suprafata sau de metrou!");
                         else break;
                     }
                     catch(string s){
                         cout << s << '\n';
                     }
                 }
                 bilete.push_back(b);
             }
         }
         return is;
    }

    virtual ostream &write(ostream &os) const {
        Card::write(os);
        cout<<"Aveti "<<bilete.size()<<" bilete pe card"<<endl;
        if(bilete.size()!=0){
            cout<<" Aveti urmatoarele bilete: ";
            for(auto b:bilete){
                os<<b<<endl<<".................."<<endl;
            }
        }
        return os;
    }
};

//Card metrou
class CardMetrou: virtual public Card{
protected:
    vector<Bilet> bilete;
public:
    CardMetrou(int id, const vector<Bilet> &bilete, const vector<Bilet> &bilete1);
    CardMetrou(){

    }
    virtual ~CardMetrou(){
        bilete.clear();
    }
    void AddBil(){
        Bilet b;
        while(true){
            try{
                cin>>b;
                if(b.getTip()==2) throw string("Adaugati un bilet de tranzit!");
                else break;
            }
            catch(string s){
                cout << s << '\n';
            }
        }
        bilete.push_back(b);
    };
    virtual istream &read(istream &is) {
        Card::read(is);
        int n;
        cout<<"Nr de bilete de pe card? "; is>>n;
        if(n!=0){
            for(int i=0;i<n;i++){
                Bilet b;
                while(true){
                    try{
                        cin>>b;
                        if(b.getTip()==2) throw string("Adaugati un bilet de suprafata sau de metrou!");
                        else break;
                    }
                    catch(string s){
                        cout << s << '\n';
                    }
                }
                bilete.push_back(b);
            }
        }
        return is;
    }

    virtual ostream &write(ostream &os) const {
        Card::write(os);
        cout<<"Aveti "<<bilete.size()<<" bilete pe card"<<endl;
        if(bilete.size()!=0){
            cout<<" Aveti urmatoarele bilete: ";
            for(auto b:bilete){
                os<<b<<endl<<".................."<<endl;
            }
        }
        return os;
    }
};

CardMetrou::CardMetrou(int id, const vector<Bilet> &bilete, const vector<Bilet> &bilete1) : Card(id, bilete),bilete(bilete1) {}

// CCard tranzit
class CardTranzit: public CardMetrou,public CardSuprafata{
private:
    vector<Bilet> bilete;
    int minut;
public:
    CardTranzit(){
        minut=0;
    }
    ~CardTranzit(){
        bilete.clear();
        minut=0;
    }

    CardTranzit(int id, const vector<Bilet> &bilete, const vector<Bilet> &bilete1, int id1,
                const vector<Bilet> &bilete2, const vector<Bilet> &bilete11, const vector<Bilet> &bilete3, int minut);
    void AddBil(){
        Bilet b;
        while(true){
            try{
                cin>>b;
                if(b.getTip()!=2) throw string("Adaugati un bilet de tranzit!");
                else break;
            }
            catch(string s){
                cout << s << '\n';
            }
        }
        bilete.push_back(b);
    };
    virtual istream &read(istream &is) {
        int n;
        cout<<"Nr de bilete de pe card? "; is>>n;
        if(n!=0){
            for(int i=0;i<n;i++){
                Bilet b;
                while(true){
                    try{
                        cin>>b;
                        if(b.getTip()!=2) throw string("Adaugati un bilet de tranzit!");
                        else break;
                    }
                    catch(string s){
                        cout << s << '\n';
                    }
                }
                bilete.push_back(b);
            }
        }
        return is;
    }

    virtual ostream &write(ostream &os) const {
        Card::write(os);
        cout<<"Aveti "<<bilete.size()<<" bilete pe card"<<endl;
        if(bilete.size()!=0){
            cout<<" Aveti urmatoarele bilete: ";
            for(auto b:bilete){
                os<<b<<endl<<".................."<<endl;
            }
        }
        return os;
    }

};

CardTranzit::CardTranzit(int id, const vector<Bilet> &bilete, const vector<Bilet> &bilete1, int id1,  const vector<Bilet> &bilete2, const vector<Bilet> &bilete11, const vector<Bilet> &bilete3, int minut) : CardMetrou(id, bilete, bilete1), CardSuprafata(id1, bilete2, bilete11),bilete(bilete3), minut(minut) {}


//aparatv de validare
class AparatValidare:public IoBase{
private:
    int nrScanari;
    int tipLocatie;//0-suprafata,1-metrou,
public:
    AparatValidare(){
        nrScanari=tipLocatie=0;
    }
    ~AparatValidare(){
        nrScanari=tipLocatie=0;
    }
    virtual istream &read(istream &is);
    virtual ostream &write(ostream &os) const;
    AparatValidare(int nrScanari, int tipLocatie);
};


istream &AparatValidare::read(istream &is) {
    IoBase::read(is);
    cout<<"Tipul aparatului de scanari: 0-suprafata,1-metrou";
    is>>tipLocatie;
    return is;
}

ostream &AparatValidare::write(ostream &os) const {
    IoBase::write(os);
    cout<<" Este aparat  ";
    if(tipLocatie==1) os<<"subteran";
    else os<<" de suprafata";
    os<<" si are "<< nrScanari<<" de scanari. ";
    return os;
}

AparatValidare::AparatValidare(int nrScanari, int tipLocatie) : nrScanari(nrScanari), tipLocatie(tipLocatie) {
    this->nrScanari=nrScanari;
    this->tipLocatie=tipLocatie;
}

class BaseMenu {
public:
    virtual void listOptions() {}
    virtual int chooseOption(int first, int last) {}
    virtual void mainLoop() {}
};

class SimpleMenu : public BaseMenu {
public:
    void listOptions() override {
        cout << "1.Creare de Card" << endl;
        cout << "2.Creare de aparat de validare" << endl;
        cout << "3.Adaugare bilet pe card" << endl;
        cout << "4.Afisare Card " << endl;
        cout << "5.Validare card" << endl;
        cout << "6. Iesire." <<endl;
    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeti un numar intre "
                 << first << " si " << last << '\n';
            listOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
    }

    void option1() ;
    void option2() ;
    void option3() ;
    void option4() ;
    void option5() ;
    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 5);
            if (option == 1) {
                option1();
            }
            else if (option == 2) {
                option2();
            }
            else if (option == 3) {
                option3();
            }
            else if (option == 4) {
                option4();
            }
            else if (option == 5) {
                option5();
            }
            else if (option == 6) {
                break;
            }
        }
        cout << '\n'
             << "---------------------------------"
             << '\n'
             << "Programul s-a încheiat cu success";
    }

};
vector<Card*> carduri;
vector<AparatValidare> aparate;
int idCard=0;
void SimpleMenu::option1() {
    int tip;
    Card *c= nullptr;
   cout<<" Tipul cardului  0-suprafata,1-metrou,2-tranzit  :";
   cin>>tip;
   if(tip==0){
       c= new CardSuprafata;
   }
   else if(tip==1){
       c=new CardMetrou;
   }
   else{
       c=new CardTranzit;
   }
   cin>>*c;
   cout<<*c;
   idCard++;
   c->setId(idCard);
   carduri.push_back(c);// si adaugare card
}

void SimpleMenu::option2() {
    AparatValidare apval;
    cin>>apval;
    cout<<apval;
    aparate.push_back(apval);
}

void SimpleMenu::option3() {
    cout<<"Alegeti cardul: ";
    for(auto c:carduri){
        cout<<*c;
    }
    int id1;
    cout<<"Alegeti id-ul: ";
    cin>>id1;
    if(id1<carduri.size()){
        auto c= dynamic_cast<CardTranzit*>(carduri[id1]);
        auto c1= dynamic_cast<CardSuprafata*>(carduri[id1]);
        auto c2= dynamic_cast<CardMetrou*>(carduri[id1]);
        if(c){
            c->AddBil();
        }
        else if(c1){
            c1->AddBil();
        }
        else if(c2){
            c2->AddBil();
        }

    }
        else cout<<"Nr incorect!"<<endl;
}
void SimpleMenu::option4() {
    cout<<"Cardurile sunt: ";
    for(auto c:carduri){
        cout<<*c;
    }

}
void SimpleMenu::option5() {
    cout<<"Aparate sunt: ";
    for(auto c:aparate){
        cout<<c;cout<<"Cardurile sunt: ";
        for(auto c:carduri){
            cout<<*c;
        }
    }
}
int main() {
    SimpleMenu menu;
    menu.mainLoop();
}


