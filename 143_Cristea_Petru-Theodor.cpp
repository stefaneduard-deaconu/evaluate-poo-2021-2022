/*
 * Cristea Petru-Theodor grupa 143
 * MinGW w64 9.0
 * Profesor de laborator: Stefan Deaconu
 */

#include <bits/stdc++.h>

using namespace std;

class iobase{
private:
public:
    virtual istream &read(istream &is){
        return is;
    }

    virtual ostream &write(ostream &os) const{
        return os;
    }

    friend istream &operator>>(istream &is, iobase &base){
        return base.read(is);
    }

    friend ostream &operator<<(ostream &os, const iobase &base){
        return base.write(os);
    }
};

template<typename T>
istream &operator>>(istream &is, vector<T> &v){
    v.clear();
    cout<<"Cate elemente?";
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        T variabila;
        is>>variabila;
        v.push_back(variabila);
    }
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, vector<T> &v) {
    for(auto &x: v){
        os<<x<<" ";
    }
    return os;
}

class Bilet: public iobase{
    protected:
        float pret_bilet;
    public:
        Bilet();
        Bilet(int p);

    virtual ~Bilet();
//    istream &read(istream &is) override {
//        cout<<"Pretul biletului: ";
//        is>>pret_bilet;
//        return is;
//    }
//
//    ostream &write(ostream &os) const override {
//        os<<"\nPret bilet: "<<pret_bilet<<endl;
//        return os;
//    }
};

Bilet::Bilet():pret_bilet(0){}
Bilet::Bilet(int p): pret_bilet(p){}

Bilet::~Bilet()=default;

class BiletSuprafata: public Bilet {
protected:
    float pret;
    bool ok;
public:
    BiletSuprafata(): pret(2), ok(1){}

    virtual ~BiletSuprafata()=default;

    ostream &write(ostream &os) const override {
        cout<<"Bilet de suprafata, pret 2lei, poate fi folosit pentru tramvaie si autobuze";
    }
};

class BiletMetrou: public Bilet{
protected:
    float pret;
    bool ok;
public:
    BiletMetrou(): pret(2.5), ok(1){}

    virtual ~BiletMetrou()=default;

    ostream &write(ostream &os) const override {
        cout<<"Bilet de metrou, pret 2.5lei, poate fi folosit pentru metrou";
    }
};

class BiletTranzit: public Bilet{
protected:
    float pret;
public:
    BiletTranzit(): pret(3){}

    virtual ~BiletTranzit()=default;

    ostream &write(ostream &os) const override {
        cout<<"Bilet de tranzit, pret 3lei, poate fi folosit 90de atat la suprafata cat si la metrou";
    }
};


class Card: public iobase {
protected:
public:
    Card();
};

Card::Card() {}

class Card_transport_suprafata: public Card{
private:
    vector<BiletSuprafata> biletesuprafata;
    vector<BiletMetrou> biletemetrou;
public:
    Card_transport_suprafata();
    istream &read(istream &is) override{
        cout<<"Cate bilete de suprafata adaugati pe card?";
        int n;
        cin>>n;
        for(int i=1; i<=n; i++){
           BiletSuprafata b;
           biletesuprafata.push_back(b);
           if(i%8==0)
               biletesuprafata.push_back(b);
        }
        cout<<"Cate bilete de metrou adaugati pe card?";
        cin>>n;
        for(int i=1; i<=n; i++){
            BiletMetrou b;
            biletemetrou.push_back(b);
            if(i%8==0)
                biletemetrou.push_back(b);
        }
        return is;
    }

    ostream &write(ostream &os) const override;

    int getNumarBileteMetrou(){
        return biletemetrou.size();
    }
    int getNumarBileteSuprafata(){
        return biletesuprafata.size();
    }

    void setBiletesuprafata(const vector<BiletSuprafata> &biletesuprafata);

    void setBiletemetrou(const vector<BiletMetrou> &biletemetrou);

};

Card_transport_suprafata::Card_transport_suprafata() {}

ostream &Card_transport_suprafata::write(ostream &os) const {
    os<<"Cardul contine "<<biletesuprafata.size()<<" bilete de suprafata si "<<biletemetrou.size()<<" bilete de metrou";
    return os;
}

void Card_transport_suprafata::setBiletesuprafata(const vector<BiletSuprafata> &biletesuprafata) {
    Card_transport_suprafata::biletesuprafata = biletesuprafata;
}

void Card_transport_suprafata::setBiletemetrou(const vector<BiletMetrou> &biletemetrou) {
    Card_transport_suprafata::biletemetrou = biletemetrou;
}

class Card_transport_subteran: public Card{
private:
    vector<BiletSuprafata> biletesuprafata;
    vector<BiletMetrou> biletemetrou;
public:
    Card_transport_subteran(){}

    virtual ~Card_transport_subteran()=default;

    istream &read(istream &is) override{
        cout<<"Cate bilete de suprafata adaugati pe card?";
        int n;
        cin>>n;
        for(int i=1; i<=n; i++){
            BiletSuprafata b;
            biletesuprafata.push_back(b);
            if(i%8==0)
                biletesuprafata.push_back(b);
        }
        cout<<"Cate bilete de metrou adaugati pe card?";
        cin>>n;
        for(int i=1; i<=n; i++){
            BiletMetrou b;
            biletemetrou.push_back(b);
            if(i%8==0)
                biletemetrou.push_back(b);
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        os<<"Cardul contine "<<biletesuprafata.size()<<" bilete de suprafata si "<<biletemetrou.size()<<" bilete de metrou";
        return os;
    }
    int getNumarBileteMetrou(){
        return biletemetrou.size();
    }
    int getNumarBileteSuprafata(){
        return biletesuprafata.size();
    }

    void setBiletesuprafata(const vector<BiletSuprafata> &biletesuprafata) {
        Card_transport_subteran::biletesuprafata = biletesuprafata;
    }

    void setBiletemetrou(const vector<BiletMetrou> &biletemetrou) {
        Card_transport_subteran::biletemetrou = biletemetrou;
    }
};

class Card_tranzit: public Card{
protected:
    vector<BiletTranzit> bilete;
public:
    Card_tranzit(){}

    istream &read(istream &is) override {
        cout<<"Cate bilete de tranzit adaugati pe card?";
        int n;
        cin>>n;
        for(int i=1; i<=n; i++){
            BiletTranzit b;
            bilete.push_back(b);
            if(i%8==0)
                bilete.push_back(b);
        }

        return is;
    }

    ostream &write(ostream &os) const override {
        os<<"Cardul contine: "<<bilete.size()<<" bilete de tranzit";
        return os;
    }
    int getNumarBileteTranzit(){
        return bilete.size();
    }

    void setBilete(const vector<BiletTranzit> &bilete) {
        Card_tranzit::bilete = bilete;
    }
};

shared_ptr<Card> citeste_card(){
    int opt;
    cout<<"\n1. Card suprafata\n2. Card metrou\n3. Card tranzit";
    cin>>opt;
    shared_ptr<Card> b;
    if(opt==1){
        b = make_shared<Card_transport_suprafata>();
    }else if(opt==2){
        b = make_shared<Card_transport_subteran>();
    }else if(opt==3){
        b = make_shared<Card_tranzit>();
    }
    cin>>*b;
    return b;
}

class AparatValidare: public iobase{
private:
    string locatie;
    int numar_scanari;
public:
    AparatValidare(): numar_scanari(0){}
    AparatValidare(string l): locatie(l), numar_scanari(0){}

    istream &read(istream &is) override {
        cout<<"Introduceti locatia: "; is>>locatie;
        return is;
    }

    ostream &write(ostream &os) const override {
        os<<"\nAparatul de validare se afla: "<<locatie<<endl;
        return os;
    }

    int valideazaCard(shared_ptr<Card> c){
        numar_scanari++;
        auto *metrou = dynamic_cast<Card_transport_subteran*>(c.get());
        auto *suprafata = dynamic_cast<Card_transport_suprafata*>(c.get());
        auto *tranzit = dynamic_cast<Card_tranzit*>(c.get());
        if(metrou != nullptr || suprafata != nullptr){
            int nr_metrou, nr_suprafata;
            nr_metrou = metrou->getNumarBileteMetrou()-1;
            nr_suprafata = metrou->getNumarBileteSuprafata()-1;
            return nr_metrou, nr_suprafata;
        }else if(tranzit != nullptr){
            int nr_tranzit;
            nr_tranzit = tranzit->getNumarBileteTranzit()-1;
            return nr_tranzit;
        }
    }
};

class Menu{
private:
    vector<shared_ptr<Card>> c;
    vector<AparatValidare> a;
public:
    void listopt(){
        cout<<"\n1. Creeaza card";
        cout<<"\n2. Creaza aparat validare";
        cout<<"\n3. Adauga bilet la un card";
        cout<<"\n4. Afisarea detaliilor unui card";
        cout<<"\n5. Afiseaza carduri";
    }
    void run() {
        listopt();
        int opt;
        cin >> opt;
        while (true) {
            if (opt == 1) {
                c.push_back(citeste_card());
            } else if (opt == 2) {
                AparatValidare x;
                cin >> x;
                a.push_back(x);
            } else if (opt == 3) {
                cout << "Dati index";
                int index;
                cin >> index;
                try {
                    if (index < c.size()) {
                        auto *metrou = dynamic_cast<Card_transport_subteran*>(c[index].get());
                        auto *suprafata = dynamic_cast<Card_transport_suprafata*>(c[index].get());
                        auto *tranzit = dynamic_cast<Card_tranzit*>(c[index].get());
                        cout << "Ce bilet doriti sa adaugati? 1-suprafata, 2-metrou, 3-tranzit";
                        int opt;
                        cin >> opt;
                        if(metrou!= nullptr) {
                            if (opt == 1) {
                                BiletSuprafata b1;
                                vector<BiletSuprafata> b;
                                for(int i =0; i<metrou->getNumarBileteSuprafata()+1; i++)
                                    b.push_back(b1);
                                metrou->setBiletesuprafata(b);
                            }else if(opt==2){
                                BiletMetrou b1;
                                vector<BiletMetrou> b;
                                for(int i =0; i<metrou->getNumarBileteSuprafata()+1; i++)
                                    b.push_back(b1);
                                metrou->setBiletemetrou(b);
                            }
                        }
                    } else throw out_of_range("out");
                }
                catch (out_of_range) {
                    cout << "Out of range !!!";
                }
            }else if(opt==4){
                int index;
                cin>>index;
                try {
                    if (index < c.size()) {
                        cout<<*c[index];
                    } else throw out_of_range("out");
                }
                catch (out_of_range) {
                    cout << "Out of range !!!";
                }

            }else if(opt==5){
                int i=0;
                for(auto x: c){
                    cout<<"Cardul "<<i<<" "<<*x<<endl;
                    i++;
                }
            } else break;
            listopt();
            cin>>opt;
        }
    }

};

int main()
{
    Menu m;
    m.run();
}
