// Student: Florea Mădălin-Alexandru, grupa 143
// Tutore laborator: Deaconu Eduard-Ștefan
// Compilator: Bundled MinGW, Version w64 9.0


#include <bits/stdc++.h>
using namespace std;





// Clasa de baza pentru citire si afisare
class InOutBase {
public:
    // citire
    virtual istream &read(istream &is) {
        return is;
    }

    friend ostream &operator<<(ostream &os, const InOutBase &InOutBase) {
        return InOutBase.write(os);
    }

    // afisare
    virtual ostream &write(ostream &os) const {
        return os;
    }

    friend istream &operator>>(istream &is, InOutBase &InOutBase) {
        return InOutBase.read(is);
    }
};





// clasa pentru a retine momentul validarii
class Moment : public InOutBase{
private:
    int zi, luna, an, ora, minut;
public:
    Moment();

    Moment(int zi, int luna, int an, int ora, int minut);

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};

Moment::Moment() : zi(0), luna(0), an(0), ora(0), minut(0) {}

Moment::Moment(int zi, int luna, int an, int ora, int minut) :
        zi(zi), luna(luna), an(an), ora(ora), minut(minut) {}

istream &Moment::read(istream &is) {
    InOutBase::read(is);

    cout << "zi:"; is >> zi;
    while (zi < 1 || zi > 31) {
        cout << "Zi invalida, incearca din nou:";
        is >> zi;
    }

    cout << "luna:"; is >> luna;
    while (luna < 1 || luna > 12){
        cout << "Luna invalida, incearca din nou:";
        is >> luna;
    }

    cout << "an:"; is >> an;
    while (an < 1 || an > 2022){
        cout << "An invalid, incearca din nou:";
        is >> an;
    }

    cout << "ora:"; is >> ora;
    while (ora < 0 || ora > 23){
        cout << "Ora invalida, incearca din nou:";
        is >> ora;
    }

    cout << "minut:"; is >> minut;
    while (minut < 0 || minut > 59){
        cout << "Minut invalid, incearca din nou:";
        is >> minut;
    }

    return is;
}

ostream &Moment::write(ostream &os) const {
    InOutBase::write(os);
    os << zi << "/" << luna << "/" << an << ", ora " << ora << ":" << minut;
    return os;
}





class Bilet : public InOutBase{
protected:
    double taxa;
    bool utilizat;
    string tipBilet;
    Moment momentUtilizare;
public:
    Bilet() : taxa(0), utilizat(false) {}

    Bilet(const string &tipBilet);


    void setUtilizat(bool util){
        utilizat = util;
    }

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};


Bilet :: Bilet(const string &tipBilet):
    utilizat(false), tipBilet(tipBilet) {

    if (tipBilet == "suprafata")
        taxa = 2;
    if (tipBilet == "metrou")
        taxa = 2.5;
    if (tipBilet == "tranzit")
        taxa = 3;
}

istream &Bilet::read(istream &is) {
    InOutBase::read(is);
    cout << "Tip bilet:";

    getline(is, tipBilet);

    if (tipBilet == "suprafata")
        taxa = 2;
    if (tipBilet == "metrou")
        taxa = 2.5;

    return is;
}

ostream &Bilet::write(ostream &os) const {
    InOutBase::write(os);
    os << "Tip bilet: " << tipBilet << ", Taxa: " << taxa;
    if (utilizat)
        os << ", Moment utilizare: " << momentUtilizare;
    else
        os << ", Neutilizat";

    return os;
}




//clasa pentru biletele de tranzit
class BiletTranzit : public Bilet{
private:
    int minuteRamase;
public:
    BiletTranzit() : Bilet("tranzit"), minuteRamase(90) {}

    //nu e nevoie de citire, se face totul in constructor dupa citirea tipului in afara clasei

    // afisare
    ostream &write(ostream &os) const override;
};

ostream &BiletTranzit::write(ostream &os) const {
    Bilet::write(os);
    if (utilizat){
        os << ", Minute ramase: " << minuteRamase;
    }
    return os;
}





class Validator : public InOutBase{
private:
    Moment momentCurent;
    int nrScanari;
    static int nrScanariStatic;
    string locatie;
public:
    Validator() = default;
    Validator(Moment &momentCurent, string &locatie) : nrScanari(0), locatie(locatie), momentCurent(momentCurent) {}

    // citire
    istream &read(istream &is) override;

    // afisare
    ostream &write(ostream &os) const override;
};

int Validator::nrScanariStatic = 0;



int main(){
    string type;
    cout << "Tip bilet: ";
    getline(cin, type);
    if (type == "suprafata" || type == "metrou") {
        Bilet bilet(type);
        cout << bilet;
    }
    else if (type == "tranzit"){
        BiletTranzit bilet;
        //bilet.setUtilizat(true);
        cout <<bilet;
    }
    else{
        cout << "Bilet invalid";
    }


    return 0;
}