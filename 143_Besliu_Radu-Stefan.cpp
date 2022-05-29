/* Besliu Radu-Stefan 143
MinGW w64 9.0
Deaconu Stefan-Eduard */

#include <bits/stdc++.h>

using namespace std;

class IoBase {
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

class Bilet : public IoBase {
protected:
    string nume;
    int zi, luna, an;
    double taxa;
public:
    virtual void setTaxa();
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

void Bilet::setTaxa() {
    taxa = 2.0;
}

istream &Bilet::read(istream &is) {
    IoBase::read(is);
    cout << "nume bilet: ";
    getline(is, nume);
    cout << "zi/lune/an: ";
    is >> zi >> luna >> an;
    setTaxa();
    return is;
}

ostream &Bilet::write(ostream &os) const {
    IoBase::write(os);
    os << "nume bilet: " << nume << '\n';
    os << "zi/luna/an: " << zi << " " << luna << " " << an << '\n';
    os << "taxa: " << taxa << '\n';
    return os;
}


class BiletSuprafata : public Bilet {
private:
    vector < string > tipTransport = {"tramvai", "autobuz"};
public:
    void setTaxa() override;
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

void BiletSuprafata::setTaxa() {
    this->taxa = 2.5;
}

istream &BiletSuprafata::read(istream &is) {
    Bilet::read(is);
    return is;
}

ostream &BiletSuprafata::write(ostream &os) const {
    Bilet::write(os);
    return os;
}

class BiletMetrou : public Bilet {
private:
    vector < string > tipTransport = {"metrou"};
public:
    void setTaxa() override;
};

void BiletMetrou::setTaxa() {
    this->taxa = 2.5;
}

class BiletTranzit : public Bilet {
private:
    int timpValabil = 90;
    vector < string > tipTransport = {"tramvai", "autobuz", "metrou"};
public:
    void setTaxa() override;
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    int getTimpValabil() const;

    void setTimpValabil(int timpValabil);
};

istream &BiletTranzit::read(istream &is) {
    Bilet::read(is);
    return is;
}

ostream &BiletTranzit::write(ostream &os) const {
    Bilet::write(os);
    os << "timp valabil: " << timpValabil << '\n';
    return os;
}

void BiletTranzit::setTaxa() {
    this->taxa = 3.0;
}

int BiletTranzit::getTimpValabil() const {
    return timpValabil;
}

void BiletTranzit::setTimpValabil(int timpValabil) {
    BiletTranzit::timpValabil = timpValabil;
}

// ============= Carduri =============
class Card : public IoBase {
protected:
    string nume;
    int zi, luna, an;
    string lastCardUsed;
    vector < shared_ptr < Bilet > > bilete;
    int nrValidate;
public:
    vector<shared_ptr<Bilet>> &getBilete();

    void setBilete(const vector<shared_ptr<Bilet>> &bilete);

    const string &getLastCardUsed() const;

    int getNrValidate() const;

    void setNrValidate(int nrValidate);

    void setLastCardUsed(const string &lastCardUsed);

    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;
};

istream &Card::read(istream &is) {
    IoBase::read(is);
    cout << "nume: ";
    getline(is, nume);
    cout << "zi/luna/an: ";
    is >> zi >> luna >> an;
    return is;
}

ostream &Card::write(ostream &os) const{
    IoBase::write(os);
    os << "nume: " << nume << '\n';
    os << "zi/luna/an: " << zi << " " << luna << " " << an << '\n';
    os << "tipul ultimului bilet folosit: " << lastCardUsed << '\n';
    for (auto const &bilet: bilete) {
        cout << *bilet << '\n';
    }
    return os;
}

vector<shared_ptr<Bilet>> &Card::getBilete() {
    return bilete;
}

void Card::setBilete(const vector<shared_ptr<Bilet>> &bilete) {
    Card::bilete = bilete;
}

const string &Card::getLastCardUsed() const {
    return lastCardUsed;
}

void Card::setLastCardUsed(const string &lastCardUsed) {
    Card::lastCardUsed = lastCardUsed;
}

int Card::getNrValidate() const {
    return nrValidate;
}

void Card::setNrValidate(int nrValidate) {
    Card::nrValidate = nrValidate;
}

class CardSuprafata : public Card {
private:
    vector < shared_ptr < Bilet > > bilete;
    string tip = "suprafata";
public:
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    const string &getTip() const;
};

istream &CardSuprafata::read(istream &is) {
    Card::read(is);
    return is;
}

ostream &CardSuprafata::write(ostream &os) const {
    Card::write(os);
    return os;
}

const string &CardSuprafata::getTip() const {
    return tip;
}

class CardSubteran : public Card {
private:
    vector < shared_ptr < Bilet > > bilete;
    string tip = "subteran";
public:
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    const string &getTip() const;
};

istream &CardSubteran::read(istream &is) {
    Card::read(is);
    return is;
}

ostream &CardSubteran::write(ostream &os) const {
    Card::write(os);
    return os;
}

const string &CardSubteran::getTip() const {
    return tip;
}

class CardTranzit : public Card {
private:
    vector < shared_ptr < Bilet > > bilete;
    string tip = "tranzit";
public:
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    const string &getTip() const;
};

istream &CardTranzit::read(istream &is) {
    Card::read(is);
    return is;
}

ostream &CardTranzit::write(ostream &os) const {
    Card::write(os);
    return os;
}

const string &CardTranzit::getTip() const {
    return tip;
}

// ============== Aparat Validare ==============
class AparatValidare : public IoBase {
private:
    string tipAparat;
    static int bileteTotal;
    int nrScanari;
public:
    istream &read(istream &is) override;
    ostream &write(ostream &os) const override;

    const string &getTipAparat() const;

    int getNrScanari() const;

    void setNrScanari(int nrScanari);
};

istream &AparatValidare::read(istream &is) {
    IoBase::read(is);
    cout << "locatie: ";
    is >> tipAparat;
    return is;
}

ostream &AparatValidare::write(ostream &os) const {
    IoBase::write(os);
    os << "locatie: " << tipAparat << '\n';
    os << "nr scanari: " << nrScanari << '\n';
    return os;
}

const string &AparatValidare::getTipAparat() const {
    return tipAparat;
}

int AparatValidare::getNrScanari() const {
    return nrScanari;
}

void AparatValidare::setNrScanari(int nrScanari) {
    AparatValidare::nrScanari = nrScanari;
}


// Meniu de tip singleton
class SingletonMenu {
private:
    vector < shared_ptr < Card > > carduri;
    vector < AparatValidare > aparate;
    SingletonMenu() = default;
public:
    void mainLoop();

    static SingletonMenu* instance;
    static SingletonMenu* getInstance() {
        if (instance != nullptr) {
            return instance;
        }
        instance = new SingletonMenu();
        return instance;
    }
};

SingletonMenu* SingletonMenu::instance = nullptr;

void SingletonMenu::mainLoop() {
    int choice = -1;
    while (true) {
        while (choice < 1 || choice > 6) {
            cout << "1. Citire card.\n";
            cout << "2. Citire aparat validare.\n";
            cout << "3. Adaugare un bilet la card.\n";
            cout << "4. Validare card.\n";
            cout << "5. Modificare minut card tranzit.\n";
            cout << "6. Iesire.\n";
            cin >> choice;
        }
        if (choice == 1) {
            int choiceCard = -1;
            while (choiceCard < 1 || choiceCard > 3) {
                cout << "1. Card Suprafata.\n";
                cout << "2. Card Subteran.\n";
                cout << "3. Card tranzit.\n";
                cin >> choiceCard;
            }
            cin.get();
            shared_ptr<Card> card;
            if (choiceCard == 1) {
                card = make_shared<CardSuprafata>(CardSuprafata());
            } else if (choiceCard == 2) {
                card = make_shared<CardSubteran>(CardSubteran());
            } else {
                card = make_shared<CardTranzit>(CardTranzit());
            }
            cin >> *card;
            carduri.emplace_back(card);
        } else if (choice == 2) {
            AparatValidare aparat;
            cin >> aparat;
            aparate.emplace_back(aparat);
        } else if (choice == 3) {
            for (auto it = carduri.begin(); it != carduri.end(); ++it) {
                cout << "ID: " << it - carduri.begin() << '\n';
                cout << **it << '\n';
            }
            int idChosen = -1;
            while (idChosen < 0 || idChosen > carduri.size() - 1) {
                cout << "Alegeti un id: ";
                cin >> idChosen;
            }
            int tipBilet = -1;
            while (tipBilet < 1 || tipBilet > 3) {
                cout << "Alegeti tip bilet (1: Bilet suprafata | 2: Bilet metrou | 3. Bilet tranzit):";
                cin >> tipBilet;
            }
            shared_ptr<Bilet> bilet;
            if (tipBilet == 1) {
                bilet = make_shared<BiletSuprafata>(BiletSuprafata());
            } else if (tipBilet == 2) {
                bilet = make_shared<BiletMetrou>(BiletMetrou());
            } else if (tipBilet == 3) {
                bilet = make_shared<BiletTranzit>(BiletTranzit());
            }
            cin >> *bilet;
            shared_ptr<Card> cardAles = carduri[idChosen];
            vector<shared_ptr<Bilet> > bilete = cardAles->getBilete();
            bilete.emplace_back(bilet);
            cardAles->setBilete(bilete);
        } else if (choice == 4) {
            cout << "Alegeti validator: \n";
            int idValidator = -1;
            int nr = 0;
            for (auto const &valid: aparate) {
                cout << "ID: " << nr++ << '\n';
                cout << valid << '\n';
            }
            cin >> idValidator;
            AparatValidare aparatAles = aparate[idValidator];
            for (auto it = carduri.begin(); it != carduri.end(); ++it) {
                cout << "ID: " << it - carduri.begin() << '\n';
                cout << **it << '\n';
            }
            int idChosen = -1;
            while (idChosen < 0 || idChosen > carduri.size() - 1) {
                cout << "Alegeti un id: ";
                cin >> idChosen;
            }
            shared_ptr<Card> cardAles = carduri[idChosen];
            if (dynamic_pointer_cast<CardSuprafata>(cardAles) && aparatAles.getTipAparat() == "suprafata") {
                cout << "Card de tip suprafata validat.\n";
                carduri[idChosen]->setLastCardUsed("suprafata");
                aparatAles.setNrScanari(aparatAles.getNrScanari() + 1);
                cardAles->setNrValidate(cardAles->getNrValidate() + 1);
            } else if (dynamic_pointer_cast<CardSubteran>(cardAles) && aparatAles.getTipAparat() == "metrou") {
                cout << "Card de tip metrou validat.\n";
                carduri[idChosen]->setLastCardUsed("metrou");
                aparatAles.setNrScanari(aparatAles.getNrScanari() + 1);
                cardAles->setNrValidate(cardAles->getNrValidate() + 1);
            } else if (dynamic_pointer_cast<CardTranzit>(cardAles)) {
                for (auto const &bilet: cardAles->getBilete()) {
                    if (dynamic_pointer_cast<BiletTranzit>(bilet)->getTimpValabil() < 0) {
                        cout << "expirat\n";
                    }
                    else {
                        cout << "Card tranzit validat. \n";
                        aparatAles.setNrScanari(aparatAles.getNrScanari() + 1);
                        cardAles->setNrValidate(cardAles->getNrValidate() + 1);
                    }
                }
            }
            if (cardAles->getNrValidate() == 8) {
                cardAles->setNrValidate(0);
                int tipBilet = -1;
                while (tipBilet < 1 || tipBilet > 3) {
                    cout << "Alegeti tip bilet (1: Bilet suprafata | 2: Bilet metrou | 3. Bilet tranzit):";
                    cin >> tipBilet;
                }
                shared_ptr<Bilet> bilet;
                if (tipBilet == 1) {
                    bilet = make_shared<BiletSuprafata>(BiletSuprafata());
                } else if (tipBilet == 2) {
                    bilet = make_shared<BiletMetrou>(BiletMetrou());
                } else if (tipBilet == 3) {
                    bilet = make_shared<BiletTranzit>(BiletTranzit());
                }
                cin >> *bilet;
                vector<shared_ptr<Bilet> > bilete = cardAles->getBilete();
                bilete.emplace_back(bilet);
                cardAles->setBilete(bilete);
            }
        } else if (choice == 5) {
            cout << "Alegeti un card de tranzit: ";
            for (auto it = carduri.begin(); it != carduri.end(); ++it) {
                cout << "ID: " << it - carduri.begin() << '\n';
                cout << **it << '\n';
            }
            int idChosen = -1;
            while (idChosen < 0 || idChosen > carduri.size() - 1) {
                cout << "Alegeti un id: ";
                cin >> idChosen;
            }
            cout << "Alegeti un bilet: ";
            int idBiletChosen = -1;
            int nr = 0;
            for (auto const &bilet: carduri[idChosen]->getBilete()) {
                cout << "ID: " << nr++ << '\n';
            }
            cin >> idBiletChosen;
            if (dynamic_pointer_cast<BiletTranzit>(carduri[idChosen]->getBilete()[idBiletChosen])) {
                cout << "Alegeti un nou timp: ";
                int timp = 0;
                cin >> timp;
                dynamic_pointer_cast<BiletTranzit>(carduri[idChosen]->getBilete()[idBiletChosen])->setTimpValabil(timp);
            } else {
                cout << "Bilet ales invalid.\n";
            }
        } else {
            break;
        }
    }
}



int main() {
    SingletonMenu* menu = SingletonMenu::getInstance();
    menu->mainLoop();
    delete SingletonMenu::instance;
    return 0;
}
