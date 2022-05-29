#include <bits/stdc++.h>
using namespace std;

// Bundled MinGw version w64 9.0
// laborant: Stefan Eduard Deaconu
//student: Militaru Mihai-Alexandru grupa 143

class Iobase{
public:
    virtual istream &read(istream &is){
        return is;
    }

    virtual ostream &write(ostream &os){
        return os;
    }

    friend istream &operator>>(istream &is, Iobase  &base){
        return base.read(is);
    }

    friend ostream &operator<<(ostream &os,Iobase &base){
        return base.write(os);
    }
};


class Bilet:public Iobase{
protected:
    double taxa;
    string moneda;

public:
    Bilet(){
        taxa=0;
        moneda="";
    }

    Bilet(double taxa, const string &moneda) : taxa(taxa), moneda(moneda) {}

    istream &read(istream &is) override {
        Iobase::read(is);
        cout<<"Pret: ";
        cin>>taxa;
        cout<<"Moneda: ";
        cin>>moneda;
        return is;

    }

    ostream &write(ostream &os) override {
        Iobase::write(os);
        cout<<"Pret: "<<taxa<<"\n";
        cout<<"Moneda: "<<moneda<<"\n";
    }

};

class BiletSuprafata: public virtual Bilet{
public:
    BiletSuprafata(){
        taxa=2;
        moneda="lei";
    }

    BiletSuprafata(double taxa, const string &moneda) : Bilet(taxa, moneda) {}

    istream &read(istream &is) override {
        return Bilet::read(is);
    }

    ostream &write(ostream &os) override {
        return Bilet::write(os);
    }

};

class BiletMetrou: public virtual Bilet{
public:
    BiletMetrou(){
        taxa=2.5;
        moneda="lei";
    }

    BiletMetrou(double taxa, const string &moneda) : Bilet(taxa, moneda) {}

    istream &read(istream &is) override {
        return Bilet::read(is);
    }

    ostream &write(ostream &os) override {
        return Bilet::write(os);
    }
};

class BiletTranzit: public virtual BiletSuprafata, public virtual BiletMetrou{
private:
    int durata;

public:
    BiletTranzit(){
        taxa=3;
        durata =90;
    }

    istream &read(istream &is) override {
        return BiletSuprafata::read(is);
    }

    ostream &write(ostream &os) override {
        return BiletSuprafata::write(os);
        cout<<"Durata: "<<durata;
    }

    int getDurata() const {
        return durata;
    }

    void setDurata(int durata) {
        BiletTranzit::durata = durata;
    }
};







class Card:public Iobase{
public:

    virtual void adaugare_bilet(){}

    istream &read(istream &is) override {
        return Iobase::read(is);
    }

    ostream &write(ostream &os) override {
        return Iobase::write(os);
    }

};

class CardSuprafata:public virtual Card{
protected:
    vector<BiletSuprafata> bilete;

public:
    CardSuprafata()=default;

    CardSuprafata(const vector<BiletSuprafata> &bilete) : bilete(bilete) {}

    void adaugare_bilet() override {
        if(bilete.size()>=8){
            BiletSuprafata b;
            cin>>b;
            bilete.push_back(b);
        }
    }

    friend CardSuprafata operator+=(CardSuprafata &c, const BiletSuprafata &b){
        c.bilete.push_back(b);
        return c;
    }

    istream &read(istream &is) override {
        Card::read(is);
        cout<<"Introudecti n bilete.\n";
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            BiletSuprafata b;
            cin>>b;
            bilete.push_back(b);
        }
        return is;

    }

    ostream &write(ostream &os) override {
        Card::write(os);
        cout<<"Biletele sunt:\n";
        for(int i=0;i<bilete.size();i++){
            cout<<bilete[i];
        }
        return os;
    }

};

class CardSubteran:public virtual Card{
protected:
    vector<BiletMetrou> bilete;

public:
    CardSubteran()=default;

    CardSubteran(const vector<BiletMetrou> &bilete) : bilete(bilete) {}

    friend CardSubteran operator+=(CardSubteran &c, const BiletMetrou &b){
        c.bilete.push_back(b);
        return c;
    }

    istream &read(istream &is) override {
        Card::read(is);
        cout<<"Introudecti n bilete.\n";
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            BiletMetrou b;
            cin>>b;
            bilete.push_back(b);
        }
        return is;

    }

    ostream &write(ostream &os) override {
        Card::write(os);
        cout<<"Biletele sunt:\n";
        for(int i=0;i<bilete.size();i++){
            cout<<bilete[i];
        }
        return os;
    }

    void adaugare_bilet() override {
        if(bilete.size()>=8){
            BiletMetrou b;
            cin>>b;
            bilete.push_back(b);
        }
    }
};

class CardTranzit:public virtual CardSubteran, public virtual CardSuprafata{
private:
    vector<BiletTranzit> bilete;

public:
    CardTranzit()=default;

    CardTranzit(const vector<BiletTranzit> &bilete) : bilete(bilete) {}



    friend CardTranzit operator+=(CardTranzit &c, const BiletTranzit &b){
        c.bilete.push_back(b);
        return c;
    }

    istream &read(istream &is) override {
        Card::read(is);
        cout<<"Introudecti n bilete.\n";
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            BiletTranzit b;
            cin>>b;
            bilete.push_back(b);
        }
        return is;

    }

    ostream &write(ostream &os) override {
        Card::write(os);
        cout<<"Biletele sunt:\n";
        for(int i=0;i<bilete.size();i++){
            cout<<bilete[i];
        }
        return os;
    }

    void adaugare_bilet() override {
        if(bilete.size()>=8){
            BiletTranzit b;
            cin>>b;
            bilete.push_back(b);
        }
    }
};

class Aparat:public Iobase{
private:
    string locatie;
    vector<shared_ptr<Card>> carduri;

public:
    Aparat()=default;



    istream &read(istream &is) override {
        Iobase::read(is);
        cout<<"Locatie: ";
        getline(cin, locatie);
        cout<<"Introduceti n carduri:\n";
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            cout<<"1.Metrou 2.Suprafata 3. Tranzit\n";
            int tip;
            cin>>tip;
            while(tip!=1 and tip!=2 and tip!=3){
                cout<<"Reintrodu tipul.\n";
                cin>>tip;
            }
            if(tip==1){
                CardSubteran c;
                cin>>c;
                carduri.push_back(make_shared<CardSubteran>(c));
            }
            if(tip==2){
                CardSuprafata c;
                cin>>c;
                carduri.push_back(make_shared<CardSuprafata>(c));
            }
            if(tip==3){
                CardTranzit c;
                cin>>c;
                carduri.push_back(make_shared<CardTranzit>(c));
            }
        }
        return is;
    }

    ostream &write(ostream &os) override {
        Iobase::write(os);
        int numar_s;
        int numar_m;
        int numar_t;
        cout<<"Locatie: "<<locatie<<"\n";
        cout<<"Numar scanari : "<<carduri.size()<<"\n";
        for(const auto& i:carduri){
            auto *s=dynamic_cast<CardSuprafata *>(i.get());
            auto *m=dynamic_cast<CardSubteran *>(i.get());
            auto *t=dynamic_cast<CardTranzit *>(i.get());

            if(s){
                cout<<*s;
            }

            if(m){
                cout<<*m;
            }

            if(t){
                cout<<*t;
            }
        }
        return os;
    }


};


int main() {
    cout << "1.Metrou 2.Suprafata 3. Tranzit\n";
    int tip;
    cin >> tip;
    while (tip != 1 and tip != 2 and tip != 3) {
        cout << "Reintrodu tipul.\n";
        cin >> tip;
    }

    if (tip == 1) {
        CardSubteran c;
        cin >> c;
        cout << c;
    } else if (tip == 2) {
        CardSuprafata c;
        cin >> c;
        cout << c;
    } else if (tip == 3) {
        CardTranzit c;
        cin >> c;
        cout << c;
    }

    //citit aparat de validare
    Aparat ap;
    cin >> ap;
    cout << ap;

    //adaugare bilet la card

    CardSubteran subt;
    CardSuprafata supr;
    CardTranzit tr;
    cout << "1.Metrou 2.Suprafata 3. Tranzit\n";
    int tip_card;
    while (tip != 1 and tip != 2 and tip != 3) {
        cout << "Reintrodu tipul.\n";
        cin >> tip_card;
    }

    if (tip_card == 1) {
        BiletMetrou b;
        cin >> b;
        subt += b;
        cout << subt;
    } else if (tip_card == 2) {
        BiletSuprafata b;
        cin >> b;
        supr += b;
        cout << supr;
    } else if (tip == 3) {
        BiletTranzit b;
        cin >> b;
        tr += b;
        cout << tr;
    }

    //Modificarea minutului curent la un bilet de tranzit;

    int minc;
    cout << "Cat timp a trecut:\n";

    cin >> minc;

    BiletTranzit b;
    int d = b.getDurata();
    if (d - minc < 0) {
        b.setDurata(0);
    } else {
        b.setDurata(d - minc);
    }


    return 0;
}


