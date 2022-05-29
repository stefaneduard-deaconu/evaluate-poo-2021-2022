/*
    Dilirici Mihai
    Grupa 143
    Compilator: MinGW version: w64 9.0
    C++ 14
    Tutore : Stefan Eduard - Deaconu
 */

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

//template-uri citire/afisarre vector

template <typename T> istream &operator>>(istream &is, vector<T> &v){
    v.clear();
    int n;
    cout << "nr elemente= ";
    cin >> n;
    for (int i = 0 ; i < n; i ++) {
        T x;
        cin >> x;
        v.push_back(x);
    }
    return is;
}

template <typename T> ostream &operator<<(ostream &os,const vector<T> &v){
    for (auto &element : v){
        os << element << " ";
    }
    os << endl;
    return os;
}


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

class Bilet : public IoBase{
protected:
    int tip;
    float pret;
    int minute;
public:
    Bilet() {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "introduceti tipul biletului(1 pentru suprafata, 2 pentru subteran si 3 pentru tranzit): ";
        cin >> tip;
        if (tip == 1)
            this->pret =2;
        if (tip == 2)
            this->pret =2.5;
        if (tip == 3)
            this->pret =3;
        return is;
    }

    ostream &write(ostream &os) const override {
        cout << "Biletul este de tip: ";
        if (this->tip == 1)
            cout << "suprafata\n";
        else if (this->tip == 2)
            cout << "subteran\n";
        if (this->tip == 3)
            cout << "tranzit\n";
        IoBase::write(os);
        return os;
    }

    int getTip() const;

    float getPret() const;
};

int Bilet::getTip() const {
    return tip;
}

float Bilet::getPret() const {
    return pret;
}

class Aparat : public IoBase{
protected:
    int numarScanari, minutCurent = 0;
    bool locatie; // true = suprafata, false = subteran
    int id = 0, nrScanari = 0;
public:
    Aparat() {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "introduceti locatia(1 pentru suprafata, 0 pentru subteran): ";
        cin >> locatie;
        id ++;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << "Aparatul se situeaza la ";
        if (locatie)
            cout << "suprafata\n";
        else if (!locatie)
            cout << "subteran\n";
        cout << "Minutul curent: " << minutCurent;
        cout << "Numarul de scanari: " << nrScanari << endl;
        return os;
    }
    void incrementTime(){
        this->minutCurent+= 10; // vom creste minutul la fiecare validare cu 10 (presupunem ca se valideaza un bilet la fiecare 10 minute ca sa avem retinut timpul)
    }
    void incrementScanari(){
        this->nrScanari ++;
    }
};

class Card : public IoBase{
protected:
    vector<Bilet> bilete, bileteFolosite;
    int bileteValidate = 0, minuteDeLaValidare = 90, tip;
public:
    Card() {}
    istream &read(istream &is) override {
        IoBase::read(is);
        bileteFolosite.clear();
        cout << "introduceti tipul cardului(1 pentru suprafata, 2 pentru subteran si 3 pentru tranzit): ";
        cin >> tip;
        cout << "introduceti biletele: ";
        cin >> bilete;
        if (tip == 3){
            while (verificaBilete())
                cin >> bilete;
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << "Cardul este de tip: ";
        if (this->tip == 1)
            cout << "suprafata\n";
        else if (this->tip == 2)
            cout << "subteran\n";
        if (this->tip == 3)
            cout << "tranzit\n";
        cout << "Biletele dvs: \n";
        cout << bilete;
        return os;
    }
    bool verificaBilete();
    void adaugaBilet();
    void validareCard(Aparat &a);
    void detaliiCard();
};
void Card::detaliiCard() {
    float pretTotal = 0;
    cout << "ultimul bilet folosit: " << bileteFolosite.back();
    for (auto &bilet : bilete){
        pretTotal += bilet.getPret();
    }
    cout << "suma tuturor biletelor ramase este de : " << pretTotal << " lei,\n";
}
void Card::validareCard(Aparat &a) {
    if (bilete.size()== 0){
        cout << "Nu mai aveti bilete pe card! Va rugam mergeti la ghiseu si cumparati un bilet! \n";
    }
//    if (bileteFolosite.back().getTip() == 3) {
//        if (this->minuteDeLaValidare < 90) {
//            cout << "\nAveti un bilet de tranzit inca activ! \nCalatorie placuta!\n\n";
//            a.incrementTime();
//            return;
//        }
//    }
    if (tip == 3)
    {
        this->minuteDeLaValidare = 0;
        cout << "Aveti la dispozitie 90 minute sa folositi orice tip de transport!\n";
    }
    cout << "\nCalatorie placuta!\n\n";
    bileteFolosite.push_back(bilete.back());
    bilete.pop_back();
    a.incrementTime();
    a.incrementScanari();
}
void Card::adaugaBilet() {
    Bilet a;
    cin >> a;
    bilete.push_back(a);
}
bool Card::verificaBilete(){
    for (auto b : bilete){
        if (b.getTip() != 3)
        {
            cout << "Poti introduce doar bielte de tip tranzit!\n";
            cout << "Reintrodu biletele";
            return 1;
        }
    }
    return 0;
}

int main() {
    Aparat a;
    cin >> a;
    cout << a;
    Card carrd;
    cin >> carrd;
    cout << carrd;
    carrd.adaugaBilet();
    cout << carrd;
    carrd.validareCard(a);
    cout << carrd;
    carrd.validareCard(a);
    cout << carrd;
    cout << a;
    carrd.detaliiCard();
    return 0;
}
