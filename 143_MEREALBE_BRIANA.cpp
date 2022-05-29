//MEREALBE BRIANA 143
//GNU g++ MinGW w64 9.0
//Stefan Eduard Deaconu


#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class IoBase {
private:
public:
    // metoda citire
    virtual istream &read(istream &is) {
        return is;
    }
    // metoda scriere
    virtual ostream &write(ostream &os) {
        return os;
    }

    friend ostream &operator<<(ostream &os, IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};

class Bilet : public IoBase{
protected:
    double taxa;
public:
    Bilet();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
    double getTaxa();
};
Bilet::Bilet() {}

double Bilet::getTaxa() {
    return taxa;
}
istream &Bilet::read(istream &is) {
    return IoBase::read(is);
}

ostream &Bilet::write(ostream &os) {
    return IoBase::write(os);
}

class BiletSuprafata : virtual public Bilet{
private:
public:
    BiletSuprafata();
    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
};
BiletSuprafata::BiletSuprafata() {
    taxa = 2;
}

istream &BiletSuprafata::read(istream &is) {
    Bilet::read(is);
    cout << "taxa pentru acest bulet este de 2lei si poate fi folosit doar pentru tramvaie si autobuze\n";
    return is;
}

ostream &BiletSuprafata::write(ostream &os) {
    Bilet::write(os);
    os << "taxa: 2lei\n";
    return os;
}


class BiletMetrou : virtual public Bilet{
private:
public:

    BiletMetrou();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

};

BiletMetrou::BiletMetrou() {
    taxa = 2.5;
}

istream &BiletMetrou::read(istream &is) {
    Bilet::read(is);
    cout << "taxa pentru acest bilet este de 2.5lei si este valabil doar pentru metrou\n";
    return is;
}

ostream &BiletMetrou::write(ostream &os) {
    Bilet::write(os);
    os << "taxa: 2.5\n";
    return os;
}
//biletul de tranzit se foloseste atat la suparafata cat si la metrou deci mosteneste ambele tipuri de bilete
class BiletTranzit : public BiletSuprafata, public BiletMetrou{
private:
    double durata;
public:
    BiletTranzit();
    double getDurata();
    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

};

double BiletTranzit::getDurata() {
    return durata;
}
BiletTranzit::BiletTranzit() {
    taxa = 3;
    durata = 90;
}

istream &BiletTranzit::read(istream &is) {
    Bilet::read(is);
    cout << "taxa pentru acest bilet este de 3lei si poate fi folosit timp de 90 de min atat la suprafata cat si la metrou\n";
    return is;
}

ostream &BiletTranzit::write(ostream &os) {
    Bilet::write(os);
    os << "taxa: 3lei\n";
    os << "durata: " << durata;
    return os;

}

class Card : public IoBase{
private:
public:
    Card();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
};
Card::Card() {}

istream &Card::read(istream &is) {
    return IoBase::read(is);
}

ostream &Card::write(ostream &os) {
    return IoBase::write(os);
}


class CardSuprafataSubteran : public Card{
private:
    vector<shared_ptr<Bilet>> bilete;
public:
    CardSuprafataSubteran();

    const vector<shared_ptr<Bilet>> &getBilete() const;

    void setBilete(const vector<shared_ptr<Bilet>> &bilete);

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;
};
CardSuprafataSubteran::CardSuprafataSubteran() {}

istream &CardSuprafataSubteran::read(istream &is) {
    Card::read(is);
    cout << "ati ales un card de suprafata/subteran\n";
    cout << "cate bilete introduceti?\n";
    int nr;
    int tip;
    is >> nr;
    for (int i = 0; i < nr; ++i) {
        cout << "1 pentru bilet de suprafata si 2 pentru bilet de metrou\n";
        is >> tip;
        if(tip == 1){
            BiletSuprafata b;
            is >> b;
            bilete.push_back(make_shared<BiletSuprafata>(b));
        }else if(tip == 2){
            BiletMetrou b;
            is >> b;
            bilete.push_back(make_shared<BiletMetrou>(b));
        }
    }
    return is;
}

ostream &CardSuprafataSubteran::write(ostream &os) {
    Card::write(os);
    os << "card suprafata/subteran\n";
    os << "are in total " << bilete.size() << " bilete\n";
    for (const auto &i: bilete) {
        shared_ptr<BiletSuprafata> b1 = dynamic_pointer_cast<BiletSuprafata>(i);
        shared_ptr<BiletMetrou> b2 = dynamic_pointer_cast<BiletMetrou>(i);
        if(b1) cout << *b1;
        else
            if(b2) cout << *b2;
    }
    return os;
}

const vector<shared_ptr<Bilet>> &CardSuprafataSubteran::getBilete() const {
    return bilete;
}

void CardSuprafataSubteran::setBilete(const vector<shared_ptr<Bilet>> &bilete) {
    CardSuprafataSubteran::bilete = bilete;
}

class CardTranzit : public Card {
private:
    vector<BiletTranzit *> bileteTranzit;
public:
    CardTranzit();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

    const vector<BiletTranzit *> &getBileteTranzit() const;

    void setBileteTranzit(const vector<BiletTranzit *> &bileteTranzit);
};
CardTranzit::CardTranzit() : bileteTranzit() {}

istream &CardTranzit::read(istream &is) {
    Card::read(is);

}

ostream &CardTranzit::write(ostream &os) {
    Card::write(os);
    os << "bilete:\n";
    for (int i = 0; i < bileteTranzit.size(); ++i) {
        os << i+1 << *bileteTranzit[i] << "\n";
    }
    return os;
}

const vector<BiletTranzit *> &CardTranzit::getBileteTranzit() const {
    return bileteTranzit;
}

void CardTranzit::setBileteTranzit(const vector<BiletTranzit *> &bileteTranzit) {
    CardTranzit::bileteTranzit = bileteTranzit;
}

class Aparat : public IoBase{
private:
    string locatie;
    vector<shared_ptr<Card>> carduri;
    vector<pair<string, int>> validare;
public:
    Aparat();

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

};

Aparat::Aparat() {}

istream &Aparat::read(istream &is) {
    IoBase::read(is);
    cout << "in ce locatie se afla aparatul?\n";
    is.get();
    getline(is,locatie);
    return is;
}

ostream &Aparat::write(ostream &os) {
    IoBase::write(os);
    os << "aparatul din locatia " << locatie << "\n";
}

class Aplicatie{
private:
    vector<shared_ptr<Card> > carduri;
    int minut;
    vector<Aparat*> aparate;
    static Aplicatie* instance;
    Aplicatie()=default;
public:
    static Aplicatie* getInstance() {
        if (instance == nullptr) return new Aplicatie();
        return instance;
    }

    void creareCardcuBilete();
    void creareAparat();
    void validareCard();
    void modificareMinut();
    void detaliiCard();
    void detaliiAparat();

    ~Aplicatie(){}
};

Aplicatie* Aplicatie::instance = nullptr;

void Aplicatie::creareCardcuBilete() {
    int nr;
    int tip1;
    cout << "Ce fel de card doriti? 1 pt card suprafata/subteran si 2 pentru tranzit\n";
        cin >> tip1;
        if (tip1 == 1){
            CardSuprafataSubteran c;
            cin >> c;
            carduri.push_back(make_shared<CardSuprafataSubteran>(c));
        }else if(tip1 == 2){
            CardTranzit c;
            cin >> c;
            carduri.push_back(make_shared<CardTranzit>(c));
        }
    }


void Aplicatie::creareAparat() {
    Aparat *a = new Aparat;
    cin >> *a;
    aparate.push_back(a);

}

void Aplicatie::validareCard() {

    for(const auto &i: carduri){
        shared_ptr<CardSuprafataSubteran> s = dynamic_pointer_cast<CardSuprafataSubteran>(i);
        shared_ptr<CardTranzit> t = dynamic_pointer_cast<CardTranzit>(i);
        if(s){
            if(s->getBilete().size() == 0)
                cout << "niciun bilet de validat\n";
            else
                cout << "bilete validate\n";
        }
        else if(t) {
            if(t->getBileteTranzit().size() == 0)
                cout << "niciun bilet de validat\n";
            else
                cout << "bilete validate\n";
        }
    }
}

void Aplicatie::modificareMinut() {
    cout<<"coming soon";
}

void Aplicatie::detaliiCard() {
    for(const auto &i: carduri){
        shared_ptr<CardSuprafataSubteran> s = dynamic_pointer_cast<CardSuprafataSubteran>(i);
        shared_ptr<CardTranzit> t = dynamic_pointer_cast<CardTranzit>(i);
        if(s)
            cout << *s;
        else if(t) cout << *t;
    }
}

void Aplicatie::detaliiAparat(){
    for (int i = 0; i < aparate.size(); ++i) {
        cout << *aparate[i] << "\n";
    }
}

int main()
{
    Aplicatie* A = A->getInstance();
    int var;
    while (true){
        cout << "1. creare card\n";
        cout << "2. creare aparat\n";
        cout << "3. validare carduri\n";
        cout << "4. modificare minut\n";
        cout << "5. afisare carduri\n";
        cout << "6. afisare aparate\n";
        cout << "7. gata\n";
        cin >> var;
        if (var == 1) A->creareCardcuBilete();
        else if (var == 2) A->creareAparat();
        else if (var == 3) A->validareCard();
        else if(var == 4) A->modificareMinut();
        else if(var == 5) A->detaliiCard();
        else if(var == 6) A->detaliiAparat();
        else {
            cout << "Programul s-a incheiat cu succes!\n";
            cout << "----------------------------------------------------------\n";
            break;
        }
    }
    return 0;
}







