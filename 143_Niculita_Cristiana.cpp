/*
Niculita Cristiana Teodora
Grupa 143
(MinGW.org GCC Build-2) 9.2.0
tutore: Stefan Eduard Deaconu
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Bilet {
protected:
    string tip_bilet; //suprafata, subteran sau tranzit
    float taxa;
public:
    Bilet() {};

    Bilet(string tip_bilet, float taxa);

    Bilet(const Bilet &b);

    ~Bilet();

    Bilet operator=(const Bilet& b);

    friend istream& operator>>(istream& is, Bilet &b);
    friend ostream& operator<<(ostream& os, const Bilet &b);

};
Bilet::Bilet(string tip_bilet, float taxa){
    tip_bilet="unknown";
    taxa=0;
}
Bilet::Bilet(const Bilet& b){
    this->tip_bilet=b.tip_bilet;
    this->taxa=b.taxa;
}
Bilet::~Bilet(){
    tip_bilet="";
    taxa=0;
}

Bilet Bilet::operator=(const Bilet &b) {
    this->tip_bilet=tip_bilet;
    this->taxa=taxa;
    return *this;
}
istream& operator>>(istream& is,Bilet &b)
{
    cout<<"Introduceti tipul de bilet (suprafata, subteran sau tranzit";
    string t;
    while(1){
        try{
            is>>t;
            if(t=="suprafata" or t=="subteran" or t=="tranzit")
                {b.tip_bilet=t;
                break;}
            else throw("invalid!");
        }
        catch(string s)
        {
            cout<<s<<endl;
        }
    }
    cout<<"Introduceti taxa";
    is>>b.taxa;
    return is;
}

ostream& operator<<(ostream& os,const Bilet &b){
    cout<<"Tipul de bilet este"<< b.tip_bilet;
    cout<<"Taxa achitata este"<<b.taxa;
    return os;
}
class Card{
private:
    const int id;
    static int id_curent;
    string tip_card; //suprafata, subteran sau tranzit
    int ora_validare;
    int minut_validare;
    vector <Bilet*> bilete;
public:
    Card() : id(++id_curent) {};
    Card(string tip_card, int ora_validare, int minut_validare, vector <Bilet*> bilete);

    Card(const Card &b);

    Card operator=(const Card &b);

    ~Card(){};

    friend istream& operator<<(istream& is,Card &b);
    friend ostream& operator>>(ostream& os, const Card &b);

    friend Bilet;
};
int Card::id_curent=0;
Card::Card(string tip_card, int ora_validare, int minut_validare, vector<Bilet *> bilete) : id(++id_curent) {
    this->tip_card="unknown";
    this->ora_validare=0;
    this->minut_validare=0;
    this->bilete={};
}
Card::Card(const Card &b): id(){
    this->tip_card=b.tip_card;
    this->ora_validare=b.ora_validare;
    this->minut_validare=b.minut_validare;
    this->bilete=b.bilete;
}

Card Card::operator=(const Card &b) {
    this->tip_card=b.tip_card;
    this->ora_validare=b.ora_validare;
    this->minut_validare=b.minut_validare;
    this->bilete=b.bilete;
    return *this;
}
istream& operator<<(istream& is, Card &b){

    cout<<"Introduceti tipul de bilet (suprafata, subteran sau tranzit";
    string t;
    while(1){
        try{
            is>>t;
            if(t=="suprafata" or t=="subteran" or t=="tranzit")
            {b.tip_card=t;
                break;}
            else throw("invalid!");
        }
        catch(string s)
        {
            cout<<s<<endl;
        }
    }
    cout<<"Ora validarii:";
    is>>b.ora_validare;
    cout<<"Minut validare:";
    is>>b.minut_validare;
    cout<<"Numarul de bilete:";
    int nr;
    is>>nr;
    for(int i=0;i<nr;i++)
    {
        cout<<"introduceti datele pentru biletul "<<i;
        is>>*b.bilete[i];
        if()
    }
    return is;
}
ostream& operator>>(ostream& os, const Card &b){
    cout<<"tipul cardului este"<<b.tip_card;
    cout<<"momentul validarii este"<<b.ora_validare<<":"<<b.minut_validare;
    for(auto i : b.bilete)
    {
        os<<i;
    }
    return os;
}
class Aparat_validare{
private:
    string locatie; ///suprafata sau subteran
    int nr_scanari;
    int ora_crt;
    int minut_crt;
public:
    Aparat_validare(){};
    Aparat_validare(string locatie, int nr_scanari,int ora_crt, int minut_crt);

    ~Aparat_validare(){};

    friend istream& operator>>(istream& is, Aparat_validare &b);
    friend ostream& operator<<(ostream& os, Aparat_validare &b);

};
istream& operator>>(istream& is, Aparat_validare &b){
    cout<<"Introduceti locatia aparatului";
    is>>b.locatie;
    cout<<"Introduceti nr de scanari";
    is>>b.nr_scanari;
    cout<<"Introduceti ora curenta";
    is>>b.ora_crt;
    cout<<"Introduceti minutul";
    is>>b.minut_crt;

    return is;
}
ostream& operator<<(ostream& os, Aparat_validare &b){
    cout<<"locatia este"<<b.locatie;
    cout<<"nr de scanari este"<<b.nr_scanari;
    cout<<"momentul validarii este"<<b.ora_crt<<":"<<b.minut_crt;
    return os;
}
Aparat_validare::Aparat_validare(string locatie, int nr_scanari, int ora_crt, int minut_crt) {
    this->locatie="unknown";
    this->nr_scanari=0;
    this->ora_crt=ora_crt;
    this->minut_crt=minut_crt;
}

class Transport{
private:
    vector <Card*> carduri;
    vector <Aparat_validare*> aparate;
public:
    Transport(){};
    ~Transport(){};

};
int main() {
    return 0;
}
