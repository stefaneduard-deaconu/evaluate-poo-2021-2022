/* Petre Vasile-Eduard, grupa 143
 * Bundled MinGW version: w64 9.0
 * Stefan Eduard Deaconu
*/

#include<bits/stdc++.h>
using namespace std;

class IoBase{
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

template<typename T>
istream &operator>>(istream &is, vector<T> &vec) {
    vec.clear();
    int n;
    cout << "n: ";
    cin >> n;
    for (int i = 0; i < n; ++i) {
        T var;
        cin >> var;
        vec.push_back(var);
    }
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
    os << "[ ";
    for(auto& var : vec) {
        os << var << " ; ";
    }
    os << ']';
    return os;
}

class bilet: public IoBase{
protected:
    double pret;
public:
    bilet();

    bilet(double pret);

    double getPret() const;

    void setPret(double pret);

};

bilet::bilet(){}

bilet::bilet(double pret) {}

double bilet::getPret() const {
    return pret;
}

void bilet::setPret(double pret) {
    bilet::pret = pret;
}

class biletSuprafata: public bilet{
protected:
public:
    biletSuprafata();

    istream &read(istream &is) override;
};

biletSuprafata::biletSuprafata() {}

istream &biletSuprafata::read(istream &is) {
    pret=2;
    return is;
}

class biletMetrou: public bilet{
protected:
public:
    biletMetrou();

    istream &read(istream &is) override;
};

biletMetrou::biletMetrou() {}

istream &biletMetrou::read(istream &is) {
    pret=2.5;
    return is;
}

class biletTranzit: public bilet{
protected:
    int minute;
public:
    biletTranzit();
    biletTranzit(int minute);

    istream &read(istream &is) override;

};

biletTranzit::biletTranzit() {}

biletTranzit::biletTranzit(int minute): minute(90) {}

istream &biletTranzit::read(istream &is) {
    pret=3;
    return is;
}

class card: public IoBase{
protected:
    vector<shared_ptr<bilet>> bilete;
    int momentValidare;
    double suma;
public:
    card();

    card(vector<shared_ptr<bilet>> bilete, int momentValidare, double suma);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    void adaugareBilet(shared_ptr<bilet> b){
        bilete.push_back(b);
    }
};

card::card(){}

card::card(vector<shared_ptr<bilet>> bilete, int momentValidare, double suma): bilete(bilete), momentValidare(momentValidare), suma(suma) {}

istream &card::read(istream &is) {
    for(int i=0;i<bilete.size();i++){
        suma+=bilete[i]->getPret();
    }
    cout<<"Momentul validarii:";
    is>>momentValidare;
    return is;
}

ostream &card::write(ostream &os) const {
    os<<"\nSuma: "<<suma;
    os<<"\nMomentul in care a fost validat: "<<momentValidare;
    return os;
}


class cardSuprafataSubteran: public card{
protected:
public:
    cardSuprafataSubteran();

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

cardSuprafataSubteran::cardSuprafataSubteran() {}

istream &cardSuprafataSubteran::read(istream &is) {
    cout<<"Tip bilet:\n1. Bilet suprafata\n2. Bilet metrou\n";
    int optiune;
    is>>optiune;
    shared_ptr<bilet> b;
    if (optiune==1)
        b = make_shared<biletSuprafata>();
    else if (optiune==2)
        b = make_shared<biletMetrou>();
    is>>*b;
    bilete.push_back(b);
    return is;
}

ostream &cardSuprafataSubteran::write(ostream &os) const {
    os<<"\nTipul ultimului bilet: ";
    auto* x=dynamic_cast<biletSuprafata *>((bilete[bilete.size()-1]).get());
    auto* y=dynamic_cast<biletMetrou *>((bilete[bilete.size()-1]).get());
    if (x!=nullptr)
        os<<"suprafata.";
    else if (y!=nullptr)
        os<<"metrou.";
    card::write(os);
    return os;
}

class cardTranzit: public card{
protected:
    int minute;
public:
    cardTranzit();

    cardTranzit(int minute);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

cardTranzit::cardTranzit() {}

cardTranzit::cardTranzit(int minute): minute(minute) {}

istream &cardTranzit::read(istream &is) {
    shared_ptr<bilet> b;
    b = make_shared<biletTranzit>();
    is>>*b;
    bilete.push_back(b);
    return is;
}

ostream &cardTranzit::write(ostream &os) const {
    os<<"\nTipul ultimului bilet: tranzit";
    card::write(os);
    if(minute>0)
        os<<"\nMai este valid: "<<minute<<" min";
    else
        os<<"\nExpirat!";
    return os;
}


class aparatValidare: public IoBase{
private:
    static int staticNr;
protected:
    string locatie;
    const int nrScanari = staticNr;
public:
    aparatValidare();

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
};

int aparatValidare::staticNr=0;

aparatValidare::aparatValidare() {}

istream &aparatValidare::read(istream &is) {
    cout<<"Locatie validator:\n1. Suprafata\n2. Subteran\n";
    int optiune;
    is>>optiune;
    if (optiune==1)
        locatie="suprafata";
    else if (optiune==2)
        locatie="subteran";
    return is;
}

ostream &aparatValidare::write(ostream &os) const {
    os<<"\nNr validari: "<<nrScanari;
    os<<"\nLocatia aparatului: "<<locatie;
    return os;
}

class SimpleMenu {
private:
    shared_ptr<card> c;
    aparatValidare v;
public:
    void listOptions() {
        cout << "1. Crearea unui card." << '\n';
        cout << "2. Crearea unui aparat de validare." << '\n';
        cout << "3. Adaugarea unui bilet la un card." << '\n';
        cout << "4. Validarea unui card." << '\n';
        cout << "5. Modificarea minutului curent." << '\n';
        cout << "6. Afisarea detaliilor unui card." << '\n';
        cout << "7. Afisarea detaliilor unui aparat de validare." << '\n';
        cout << "8. Iesire." << "\n";
    }

    int chooseOption(int first, int last) {
        int option = -1;
        while(option < first || option > last){
            cout << '\n';
            cout << "Pentru a rula comanda, alegeti un numar intre " << first << " si " << last << '\n';
            listOptions();
            cout << "Alegere: ";
            cin >> option;
        }
        return option;
    }


    void option1(){
        cout<<"Tip card:\n1. Card suprafata/subteran\n2. Card tranzit\n";
        int optiune;
        cin>>optiune;
        if (optiune==1)
            c = make_shared<cardSuprafataSubteran>();
        else if (optiune==2)
            c = make_shared<cardTranzit>();
        cin>>*c;
    }

    void option2(){
    cin>>v;
    }

    void option3(){
        shared_ptr<bilet> b;
//        cin>>b;
        c->adaugareBilet(b);
    }

    void option4(){

    }

    void option5(){

    }

    void option6(){
        cout<<c;
    }

    void option7(){
        cout<<v;
    }

    void mainLoop() {
        while(true){
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
            } else if (option == 6) {
                option6();
            } else if (option == 7) {
                option7();
            } else if (option == 8) {
                break;
            }

        }
        cout << '\n' << "---------------------------------" << '\n' << "Programul s-a incheiat cu success";
    }
};


int main(){
    SimpleMenu menu;
    menu.mainLoop();
    return 0;
}
