/* Pasare Roxana-Francisca, grupa 143.
// Compilator: Bundled MinGW-W64 9.0
// Tutore de laborator:  STEFAN-EDUARD DEACONU*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "math.h"
using  namespace std;
class Citire{
private:
public:
    virtual istream &read(istream &is){
        return is;
    }

    friend istream &operator>>(istream &is, Citire &ob){
        return ob.read(is);
    }

    virtual ostream &print(ostream &os) const{
        return os;
    }

    friend ostream &operator<<(ostream &os, const Citire &ob){
        return ob.print(os);
    }
};


class Bilet: public Citire{
protected:
    double taxa;
public:
      Bilet()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Bilet::read(istream &is) {
    Citire::read(is);
    return is;
}

ostream &Bilet::print(ostream &os) const {
    Citire::print(os);
    os<<"Taxa: "<<taxa<<"\n";
    return os;
}

class Bilet_suprafata:public Bilet{
private:
    string tip_transport;
public:
    Bilet_suprafata()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Bilet_suprafata::read(istream &is) {
    Bilet::read(is);
    taxa=2;
    cout<<"Introduceti tipul de transport:tramvai/autobuz\n";
    is>>tip_transport;
    return is;
}

ostream &Bilet_suprafata::print(ostream &os) const {
    Bilet::print(os);
    os<<"Tip transport: "<<tip_transport<<"\n";
    return os;
}

class Bilet_metrou:public Bilet{
private:
public:
    Bilet_metrou()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Bilet_metrou::read(istream &is) {
     Bilet::read(is);
     taxa=2.5;
     return is;
}

ostream &Bilet_metrou::print(ostream &os) const {
    Bilet::print(os);
    return os;
}

class Bilet_tranzit:public Bilet{
private:
    string tip_suprafata;
    int durata;
public:
    int getDurata(){
        return durata;
    }
    Bilet_tranzit()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Bilet_tranzit::read(istream &is) {
    Bilet::read(is);
    taxa=3;
    cout<<"Introduceti tipul suprafetei:suprafata/metrou\n";
    is>>tip_suprafata;
    cout<<"Introduceti minutul in care a fost cumparat biletul:\n";
    is>>durata;
    return is;
}

ostream &Bilet_tranzit::print(ostream &os) const {
    Bilet::print(os);
    os<<"Tip suprafata: "<<tip_suprafata<<"\n";
    os<<"Durata: "<<durata<<"\n";
}

class Card:public Citire{
protected:
    vector<shared_ptr<Bilet>> bilete;
public:
    const vector<shared_ptr<Bilet>> &getBilete(){
        return bilete;
    }

    Card()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Card::read(istream &is) {
    Citire::read(is);
    return is;
}

ostream &Card::print(ostream &os) const {
    Citire::print(os);
    return os;
}

class Card_suprafata:public Card{
private:
public:
    Card_suprafata()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Card_suprafata::read(istream &is) {
    Card::read(is);
    int nr;
    cout<<"Introduceti numarul de bilete:\n";
    is>>nr;
    cout<<"Bilete:\n";
    for(int i=0; i<nr; i++){
        cout<<"Introduceti tipul biletului:1-metrou, 2-suprafata\n";
        int tip;
        is>>tip;
        if(tip==1){
            Bilet_metrou b;
            is>>b;
            bilete.emplace_back(make_shared<Bilet_metrou>(b));
        }else if(tip==2){
            Bilet_suprafata b;
            is>>b;
            bilete.emplace_back(make_shared<Bilet_suprafata>(b));
        }
    }
    return is;
}

ostream &Card_suprafata::print(ostream &os) const {
    Card::print(os);
    os<<"Bilete:\n";
    for(int i=0; i<bilete.size(); i++)
        os<<*bilete[i]<<"\n";
    return os;
}

class Card_subteran:public Card{
private:
public:
    Card_subteran()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Card_subteran::read(istream &is) {
    Card::read(is);
    int nr;
    cout<<"Introduceti numarul de bilete:\n";
    is>>nr;
    cout<<"Bilete:\n";
    for(int i=0; i<nr; i++){
        cout<<"Introduceti tipul biletului:1-metrou, 2-suprafata\n";
        int tip;
        is>>tip;
        if(tip==1){
            Bilet_metrou b;
            is>>b;
            bilete.emplace_back(make_shared<Bilet_metrou>(b));
        }else if(tip==2){
            Bilet_suprafata b;
            is>>b;
            bilete.emplace_back(make_shared<Bilet_suprafata>(b));
        }
    }
    return is;
}

ostream &Card_subteran::print(ostream &os) const {
    Card::print(os);
    os<<"Bilete:\n";
    for(int i=0; i<bilete.size(); i++)
        os<<*bilete[i]<<"\n";
    return os;
}

class Card_tranzit:public Card{
private:
public:
    Card_tranzit()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Card_tranzit::read(istream &is) {
    Card::read(is);
    int nr;
    cout<<"Introduceti numarul de bilete:\n";
    is>>nr;
    cout<<"Bilete:\n";
    for(int i=0; i<nr; i++){
        cout<<"Introduceti tipul biletului:1-tranzit\n";
        int tip;
        is>>tip;
        if(tip==1){
            Bilet_tranzit b;
            is>>b;
            bilete.emplace_back(make_shared<Bilet_tranzit>(b));
        }
    }
    return is;
}

ostream &Card_tranzit::print(ostream &os) const {
    Card::print(os);
    os<<"Bilete:\n";
    for(int i=0; i<bilete.size(); i++)
        os<<*bilete[i]<<"\n";
    return os;
}

class Validare:public Citire{
protected:
    int minut;
    shared_ptr<Card> card;
    shared_ptr<Bilet> bilet;
    int validat;
public:
    Validare()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Validare::read(istream &is) {
    Citire::read(is);
    cout<<"Introduceti minutul in care a fost validat cardul/biletul:\n";
    is>>minut;
    cout<<"Introduceti tipul de card:1-suprafata, 2-subteran, 3-tranzit\n";
    int tip;
    is>>tip;
    if(tip==1){
        card= make_shared<Card_suprafata>();
        is>>*card;
    }else if(tip==2){
        card= make_shared<Card_subteran>();
        is>>*card;
    }else if(tip==3){
        card= make_shared<Card_tranzit>();
        is>>*card;
    }
    return is;
}

ostream &Validare::print(ostream &os) const {
    Citire::print(os);
    auto *asCardSuprafata=dynamic_cast<Card_suprafata*>(card.get());
    auto *asCardSubteran=dynamic_cast<Card_subteran*>(card.get());
    auto *asCardTranzit=dynamic_cast<Card_tranzit*>(card.get());
    int ok=1;
    if(asCardTranzit){
        for(int i=0; i<asCardTranzit->getBilete().size(); i++) {
            Bilet_tranzit b;
            *asCardTranzit->getBilete()[i] = b;
            if (minut - b.getDurata() < 0)
                ok = 0;
        }
        if(ok==1)
            cout<<"Card valid:\n";
        else
            cout<<"Card invalid:\n";
    }else if(asCardSubteran){
        ok=1;
        for(int i=0; i<asCardSubteran->getBilete().size(); i++){
            auto *asBilettranzit=dynamic_cast<Bilet_tranzit*>(asCardSubteran->getBilete()[i].get());
            if(asBilettranzit){
                if(minut-asBilettranzit->getDurata()<0)
                    ok=0;
            }
        }
        if(ok==1)
            cout<<"Card valid:\n";
        else
            cout<<"Card invalid:\n";
    }else if(asCardSuprafata) {
        ok = 1;
        for (int i = 0; i < asCardSuprafata->getBilete().size(); i++) {
            auto *asBilettranzit = dynamic_cast<Bilet_tranzit *>(asCardSuprafata->getBilete()[i].get());
            if (asBilettranzit) {
                if (minut - asBilettranzit->getDurata() < 0)
                    ok = 0;
            }
        }
        if (ok == 1)
            cout << "Card valid:\n";
        else
            cout << "Card invalid:\n";
    }
}

class Validare_suprafata:public Validare{
private:
public:
    Validare_suprafata()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Validare_suprafata::read(istream &is) {
    Validare::read(is);
    cout<<"Bilet:\n";
    cout<<"Introduceti bilet:1-suprafata, 2-tranzit\n";
    int tip;
    is>>tip;
    validat=0;
    if(tip==1){
        bilet=make_shared<Bilet_suprafata>();
        is>>*bilet;
        validat=1;
    } else if(tip==2){
        bilet=make_shared<Bilet_tranzit>();
        is>>*bilet;
    }
    return is;
}

ostream &Validare_suprafata::print(ostream &os) const {
    Validare::print(os);
    cout<<"Bilet:\n"<<bilet<<"\n";
    auto *asBilettranzit=dynamic_cast<Bilet_tranzit*>(bilet.get());
    auto *asBiletsuprafata=dynamic_cast<Bilet_suprafata*>(bilet.get());
    if(asBilettranzit) {
        Bilet_tranzit b;
        *bilet = b;
        if (minut - b.getDurata() > 0)
            cout << "Bilet valid:\n";
        else
            cout << "Bilet invalid:\n";
    }else if(asBiletsuprafata) {
        if (validat == 1)
            os << "Bilet valid:\n";
        else os << "Bilet invalid:\n";
    }
    return os;
}

class Validare_subterana:public Validare{
private:
public:
    Validare_subterana()=default;
    istream &read(istream &is) override;
    ostream &print(ostream &os) const override;
};

istream &Validare_subterana::read(istream &is) {
    Validare::read(is);
    cout<<"Bilet:\n";
    cout<<"Introduceti bilet:1-subteran, 2-tranzit\n";
    int tip;
    is>>tip;
    validat=0;
    if(tip==1){
        bilet=make_shared<Bilet_metrou>();
        is>>*bilet;
        validat=1;
    }else if(tip==2){
        bilet=make_shared<Bilet_tranzit>();
        is>>*bilet;
    }
    return is;
}

ostream &Validare_subterana::print(ostream &os) const {
    Validare::print(os);
    cout<<"Bilet:\n"<<bilet<<"\n";
    auto *asBilettranzit=dynamic_cast<Bilet_tranzit*>(bilet.get());
    auto *asBiletsubteran=dynamic_cast<Bilet_metrou*>(bilet.get());
    if(asBilettranzit) {
        Bilet_tranzit b;
        *bilet = b;
        if (minut - b.getDurata() > 0)
            cout << "Bilet valid:\n";
        else
            cout << "Bilet invalid:\n";
    }else if(asBiletsubteran) {
        if (validat == 1)
            os << "Bilet valid:\n";
        else os << "Bilet invalid:\n";
    }

}
int main(){
    shared_ptr<Card> card;
    cout<<"Introduceti tipul cardului:1-tranzit, 2-subteran, 3-suprafata:\n";
    int tip;
    cin>>tip;
    if(tip==1) {
        card = make_shared<Card_tranzit>();
        cin>>*card;
    }else if(tip==2){
        card= make_shared<Card_subteran>();
        cin>>*card;
    }else if(tip==3){
        card= make_shared<Card_suprafata>();
        cin>>*card;
    }
    cout<<"Card:\n"<<*card<<"\n";
    shared_ptr<Validare> v;
    cout<<"Introduceti tipul de validare:1-subterana/2-suprafata:\n";
    tip=0;
    cin>>tip;
    if(tip==1){
        v= make_shared<Validare_subterana>();
        cin>>*v;
    }else if(tip==2){
        v= make_shared<Validare_suprafata>();
        cin>>*v;
    }
    cout<<"Validare:\n"<<*v<<"\n";
    return 0;
}
