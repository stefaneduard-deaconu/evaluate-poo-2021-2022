#include <bits/stdc++.h>

using namespace std;

/*
 * Nume: Crînganu Denis-Florin
 * Tutore Laborator : Deaconu Stefan Eduard
 * Compilator : BUNDLED MINGW w64 v9.0
 */

template <typename T>
istream& operator>>(istream& is, vector<T> &v){
    int n;
    T temp;
    cout << "Numarul de elemente = ";
    is >> n;
    for(int i = 0; i < n; i++){
        cout << "Elementul " << i << ":";
        is >> *temp;
        v.push_back(temp);
    }

    return is;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &v){
    os << "Numarul de elemente = " << v.size() << '\n';
    for(int i = 0; i < v.size(); i++)
        os << "Elementul " << i << ":\n" << *v[i];

    return os;
}

class IOBase{
public:
    int chooseOption(int first, int last) const;

    void readString(istream &, string &);

    virtual istream &read(istream &is){
        return is;
    }

    virtual ostream &write(ostream &os) const{
        return os;
    }

    friend ostream &operator<<(ostream &os, const IOBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IOBase &base) {
        return base.read(is);
    }
};


class Bilet : public IOBase{
    static int currentID;

protected:
    const int ID = currentID++;
    double pret;

public:
    Bilet() { }

    Bilet(const double &p) : pret(p) { }

    virtual ~Bilet() = default;

    istream &read(istream &is) override {
        IOBase::read(is);

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Pret:" << pret << '\n';

        return os;
    }
};

int Bilet::currentID = 1;

class BiletSuprafata : virtual public Bilet {

public:
    BiletSuprafata() : Bilet(2) { }

    virtual ~BiletSuprafata() = default;

    istream &read(istream &is) override {
        Bilet::read(is);
        pret = 2;

        return is;
    }

    ostream &write(ostream &os) const override {
        cout << "Bilet de tipul suprafat!\n";
        Bilet::write(os);

        return os;
    }
};

class BiletMetrou : virtual public Bilet {

public:
    BiletMetrou() : Bilet(2.5) { }

    virtual ~BiletMetrou() { }

    istream &read(istream &is) override {
        Bilet::read(is);
        pret = 2.5;

        return is;
    }

    ostream &write(ostream &os) const override {
        cout << "Bilet de tipul subteran!\n";
        Bilet::write(os);

        return os;
    }
};

class BiletTranzit : public BiletSuprafata, public BiletMetrou {
public:
    BiletTranzit() : Bilet(3) { }

    virtual ~BiletTranzit() = default;

    istream &read(istream &is) override {
        Bilet::read(is);
        pret = 3;

        return is;
    }

    ostream &write(ostream &os) const override {
        cout << "Bilet de tipul tranzit!\n";
        Bilet::write(os);

        return os;
    }
};

class Card : public IOBase{
protected:
    vector <shared_ptr<Bilet> > listaBilete;

public:
    Card() { }

    Card(const vector <shared_ptr<Bilet> > &v) : listaBilete(v) { }

    virtual ~Card() = default;

    istream &read(istream &is) override {
        IOBase::read(is);

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);

        return os;
    }

    virtual bool incearcaSaAdaugi(shared_ptr<Bilet> temp){
        return false;
    }

    virtual void popLastElement(){
        return;
    }

    int getSizeOfNrBilete() const {
        return listaBilete.size();
    }

    void adaugaBilet(shared_ptr<Bilet> temp);
};

void Card::adaugaBilet(shared_ptr<Bilet> temp) {
    listaBilete.push_back(temp);
}

class CardTransportSuprafata : public Card {
public:
    CardTransportSuprafata() { }

    CardTransportSuprafata(const vector <shared_ptr<Bilet> > &v) : Card(v) { }

    virtual ~CardTransportSuprafata() = default;

    istream &read(istream &is) override {
        Card::read(is);

        return is;
    }

    ostream &write(ostream &os) const override {
        cout << "Card de tipul transport de suprafata!\n";
        Card::write(os);
        os << "Lista biletelor este:\n" << listaBilete << '\n';

        return os;
    }

    bool incearcaSaAdaugi(shared_ptr<Bilet> temp) override{
        try{
            BiletTranzit *tempTranzit = dynamic_cast<BiletTranzit*>(temp.get());
            if(tempTranzit != nullptr)
                throw invalid_argument("Nu se poate adauga acest tip de bilet la acest card!\n");

            return true;
        } catch (invalid_argument) {
            cout << "Nu se poate adauga acest tip de bilet la acest card!\n";
            return false;
        }
    }

    void popLastElement() override {
        listaBilete.pop_back();
    }
};

class CardTransportMetrou : public Card {
public:
    CardTransportMetrou() { }

    CardTransportMetrou(const vector <shared_ptr<Bilet> > &v) : Card(v) { }

    virtual ~CardTransportMetrou() = default;

    istream &read(istream &is) override {
        Card::read(is);

        return is;
    }

    ostream &write(ostream &os) const override {
        cout << "Card de tipul transport pe subteran!\n";
        Card::write(os);
        os << "Lista biletelor este:\n" << listaBilete << '\n';

        return os;
    }

    bool incearcaSaAdaugi(shared_ptr<Bilet> temp) override{
        try{
            BiletTranzit *tempTranzit = dynamic_cast<BiletTranzit*>(temp.get());
            if(tempTranzit != nullptr)
                throw invalid_argument("Nu se poate adauga acest tip de bilet la acest card!\n");

            return true;
        } catch (invalid_argument) {
            cout << "Nu se poate adauga acest tip de bilet la acest card!\n";
            return false;
        }
    }

    void popLastElement() override {
        listaBilete.pop_back();
    }
};

class CardTransportTranzit : public Card {
    int timpRamas;
public:
    CardTransportTranzit() { }

    CardTransportTranzit(const vector <shared_ptr<Bilet> > &v) : Card(v) { }

    virtual ~CardTransportTranzit() = default;

    istream &read(istream &is) override {
        Card::read(is);

        return is;
    }

    ostream &write(ostream &os) const override {
        cout << "Card de tipul tranzit!\n";
        Card::write(os);
        os << "Timpul ramas al cardului este:" << timpRamas << '\n';
        os << "Lista biletelor este:\n" << listaBilete << '\n';

        return os;
    }

    bool incearcaSaAdaugi(shared_ptr<Bilet> temp) override{
        try{
            BiletTranzit *tempTranzit = dynamic_cast<BiletTranzit*>(temp.get());
            if(tempTranzit == nullptr)
                throw invalid_argument("Nu se poate adauga acest tip de bilet la acest card!\n");

            return true;
        } catch (invalid_argument) {
            cout << "Nu se poate adauga acest tip de bilet la acest card!\n";
            return false;
        }
    }

    int getTimpRamas() const {
        return timpRamas;
    }

    void scadeTimpRamas(int n) {
        timpRamas -= n;
        if(timpRamas < 0)
            timpRamas = 0;
    }

    void popLastElement() override {
        listaBilete.pop_back();
        timpRamas = 90;
    }
};

class AparateValidare {
    int nrAparateSuprafata, nrAparateSubteran;

public:
    AparateValidare() { }

    AparateValidare(const int &x, const int &y) : nrAparateSuprafata(x), nrAparateSubteran(y) { }

    virtual ~AparateValidare() = default;

    int getNrAparateSuprafata() const {
        return nrAparateSuprafata;
    }

    int getNrAparateSubteran() const {
        return nrAparateSubteran;
    }

    void incNrAparateSuprafata(){
        nrAparateSuprafata++;
    }

    void incNrAparateSubteran(){
        nrAparateSubteran++;
    }
};

class BaseMenu {
public:
    virtual void listOptions(int optiune) = 0;

    virtual int chooseOption(int first, int last) const = 0;

    virtual void mainLoop() = 0;
};

class Menu : public BaseMenu {
    static Menu *uniqueMenu;

    Menu() { }

    vector<shared_ptr<Card> > listaCarduri;
    AparateValidare aparate;

public:
    static Menu *instance(){
        if(uniqueMenu == NULL)
            uniqueMenu = new Menu();
        return uniqueMenu;
    }

    void readString(istream &, string &);

    void listOptions(int optiune) override;

    int chooseOption(int first, int last) const override;

    void mainLoop() override;

    void adaugaCardNou();

    void creareAparatValidare();

    void printCard();

    void adaugaBilet();

    void validareCard();

    void modificareTimp();

    bool validareCardCuIndexul(int);

    shared_ptr<Card> &operator[](int idx){
        try{
            if(idx < 0 || idx >= listaCarduri.size())
                throw out_of_range("Index invalid!\n");

            return listaCarduri[idx];
        } catch (out_of_range) {
            cout << "Index invalid!\n";
        }
    }
};

Menu* Menu::uniqueMenu = NULL;

void Menu::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0)
        getline(is, s);
}

void Menu::listOptions(int optiune) {
    if(optiune == 0)
        return;
    else if(optiune == 1)
        adaugaCardNou();
    else if(optiune == 2)
        creareAparatValidare();
    else if(optiune == 3)
        adaugaBilet();
    else if(optiune == 4)
        validareCard();
    else if(optiune == 5)
        modificareTimp();
}

int Menu::chooseOption(int first, int last) const {
    int optiune = first - 1;
    while(optiune < first || optiune > last){
        cout << "Optiunea aleasa:"; cin >> optiune;
        if(optiune < first || optiune > last)
            cout << "Optiune invalida!\n";
    }
    return optiune;
}

void Menu::mainLoop() {
    int optiune = -1;
    while(optiune != 0){
        cout << "0. Exit\n"
             << "1. Creare card nou\n"
             << "2. Crearea unui aparat de validare\n"
             << "3. Adaugare bilet la un card\n"
             << "4. Validarea unui card\n"
             << "5. Modificarea minutului curent\n";
        optiune = chooseOption(0, 5);
        listOptions(optiune);
    }
}

void Menu::adaugaCardNou() {
    cout << "Tipul de card:\n1. Card de transport de suprafata\n2. Card de transport de subteran\n3. Card de tranzit\n";
    int optiune = chooseOption(1, 3);
    shared_ptr<Card> temp;

    if(optiune == 1)
        temp = make_shared<CardTransportSuprafata>();
    else if(optiune == 2)
        temp = make_shared<CardTransportMetrou>();
    else if(optiune == 3)
        temp = make_shared<CardTransportTranzit>();

    cin >> *temp;
    listaCarduri.push_back(temp);
}

void Menu::creareAparatValidare() {
    cout << "Tipul de aparat de validare!\n1. Aparat de validare transport suprafata\n2. Aparat de validare transport subteran\n";
    int optiune = chooseOption(1, 2);
}

void Menu::printCard() {
    cout << "Lista cardurilor disponibile este:\n" << listaCarduri << '\n';
}

void Menu::adaugaBilet() {
    cout << "Tipul de bilet!\n1. Bilet de suprafata\n2. Bilet de metrou\n3. Bilet de tranzit\n";
    int optiune = chooseOption(1, 3);

    shared_ptr<Bilet> temp;
    if(optiune == 1)
        temp = make_shared<BiletSuprafata>();
    else if(optiune == 2)
        temp = make_shared<BiletMetrou>();
    else if(optiune == 3)
        temp = make_shared<BiletTranzit>();

    cin >> *temp;
    printCard();
    bool repeat = false;
    while(!repeat){
        repeat = false;

        cout << "Alege indexul cardului la care vrei sa adaugi biletul sau alege -1 pentru exit!\n";
        int idx;
        while(true){
            try{
                cout << "Index:"; cin >> idx;
                if(idx == -1)
                    return;
                if(idx < 0 || idx >= listaCarduri.size())
                    throw out_of_range("Invalid index!\n");
                break;
            } catch (out_of_range) {
                cout << "Invalid index\n";
            }
        }

        shared_ptr<Card> it = listaCarduri[idx];
        repeat = it->incearcaSaAdaugi(temp);

        if(repeat)
            it->adaugaBilet(temp);
    }
}

void Menu::validareCard() {
    printCard();
    int idx;
    try{
        cout << "Alege indexul cardului pe care vrei sa-l validezi:"; cin >> idx;
        if(idx < 0 || idx >= listaCarduri.size())
            throw out_of_range("Invalid index!\n");
    } catch (out_of_range) {
        cout << "Invalid index - exit!\n";
        return;
    }
    if(validareCardCuIndexul(idx))
        cout << "Cardul este valid!\n";
    else cout << "Cardul nu este valid!\n";
}

bool Menu::validareCardCuIndexul(int idx){
    auto it = listaCarduri[idx];

    CardTransportMetrou *tempMetrou = dynamic_cast<CardTransportMetrou*>(it.get());
    if(tempMetrou != nullptr){
        if(it->getSizeOfNrBilete() <= 0){
            cout << "Cardul nu mai are bilete valide!\n";
            return false;
        }
        if(aparate.getNrAparateSubteran() <= 0){
            cout << "Nu exista aparate de validat in subteran!\n";
            return false;
        }
        tempMetrou->popLastElement();
    }

    CardTransportSuprafata *tempSuprafata = dynamic_cast<CardTransportSuprafata*>(it.get());
    if(tempSuprafata != nullptr){
        if(it->getSizeOfNrBilete() <= 0){
            cout << "Cardul nu mai are bilete valide!\n";
            return false;
        }
        if(aparate.getNrAparateSuprafata() <= 0){
            cout << "Nu exista aparate de validat pe suprafata!\n";
            return false;
        }
        tempSuprafata->popLastElement();
    }

    CardTransportTranzit *tempTranzit = dynamic_cast<CardTransportTranzit*>(it.get());
    if(tempTranzit != nullptr){
        if(it->getSizeOfNrBilete() <= 0){
            cout << "Cardul nu mai are bilete valide!\n";
            return false;
        }
        if(aparate.getNrAparateSuprafata() <= 0 && aparate.getNrAparateSubteran() <= 0){
            cout << "Nu exista aparate de validat in subteran sau suprafata!\n";
            return false;
        }
        if(tempTranzit->getTimpRamas() <= 0)
            tempSuprafata->popLastElement();
    }

    return true;
}

void Menu::modificareTimp() {
    int n;
    cout << "Modifica timp cu:"; cin >> n;
    int idx = 0;
    for(auto it : listaCarduri){
        CardTransportTranzit *tempTranzit = dynamic_cast<CardTransportTranzit*>(it.get());
        if(tempTranzit != nullptr){
            tempTranzit->scadeTimpRamas(n);
            if(validareCardCuIndexul(idx))
                cout << "Cardul cu indexul "<< idx << " este valid!\n";
            else cout << "Cardul cu indexul " << idx << " nu este valid!\n";
        }
        ++idx;
    }
}

int main() {

    Menu *menu = Menu::instance();
    menu->mainLoop();

    return 0;
}
