//Deaconu Stefan  cLion
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class bilet{
protected:
    double pret;
    string tipBilet;
public:
    bilet();
    bilet(double pret, const string &tipBilet) : pret(pret) , tipBilet(tipBilet) {}

    friend ostream &operator<<(ostream &os, bilet &bilet);
    friend istream &operator>>(istream &is, bilet &bilet);

    double getPret() const;

    void setPret(double pret);

    const string &getTipBilet() const;

    void setTipBilet(const string &tipBilet);
};

bilet::bilet() {
    pret = 0;
    tipBilet = "";
}

ostream &operator<<(ostream &os, bilet &bilet) {
    os<<"Pretul biletului: "<<bilet.pret<<endl;
    os<<"Tipul biletului: "<<bilet.tipBilet<<endl;
}

istream &operator>>(istream &is, bilet &bilet) {
    cout<<"Introduceti pretul biletului: "<<endl;
    is>>bilet.pret;
    is.get();
    cout<<"Introduceti tipul biletului: "<<endl;
    is>>bilet.tipBilet;
    is.get();
}

double bilet::getPret() const {
    return pret;
}

void bilet::setPret(double pret) {
    bilet::pret = pret;
}

const string &bilet::getTipBilet() const {
    return tipBilet;
}

void bilet::setTipBilet(const string &tipBilet) {
    bilet::tipBilet = tipBilet;
}

class card : public bilet{
protected:
    string tipCard;
    static int belete;
    int numatBilSuprafata, numarBilSubteran, numarBilTranzit;
    vector<bilet*> bilete;
public:

    card();

    card(double pret, const string &tipBilet, const string &tipCard, const vector<bilet *> &bilete);

    const string &getTipCard() const {
        return tipCard;
    }
    void setTipCard(const string &tipCard) {
        card::tipCard = tipCard;
    }
    static int getBelete() {
        return belete;
    }
    static void setBelete(int belete) {
        card::belete = belete;
    }

    void adaugaBilet(bilet *bilet1, card &card1);

    int getNumarBileteSuprafata(){
        int nr = 0;
        for(int i = 0; i < bilete.size(); i++){
            if(bilete[i]->getTipBilet()== "suprafata")
                nr++;
        }
        return nr;
    }

    void modificaNrSuprafata(){
        numatBilSuprafata--;
    }
    void modificaNrSubteran(){
        numarBilSubteran--;
    }
    void modificaNrTranzit(){
        numarBilTranzit--;
    }

    int getNumarBileteSubteran(){
        int nr = 0;
        for(int i = 0; i < bilete.size(); i++){
            if(bilete[i]->getTipBilet() == "subteran"){
                nr++;
            }
        }
        return nr;
    }

    int getNumarBileteSuTranzit(){
        int nr = 0;
        for(int i = 0; i < bilete.size(); i++){
            if(bilete[i]->getTipBilet() == "tranzit")
                nr++;
        }
        return nr;
    }

    friend ostream &operator<<(ostream &os, card &card);
    friend istream &operator>>(istream &is, card &card);

};


card::card(){
    tipCard = "";
    belete = 0;
    numarBilSubteran = 0;
    numatBilSuprafata = 0;
    numarBilTranzit = 0;
}

int card::belete = 0;

ostream &operator<<(ostream &os, card &card) {
    os<<"Tipul cardului este: "<<card.tipCard;
}

istream &operator>>(istream &is, card &card) {
    cout<<"Introduceti tipul cardului: "<<endl;
    getline(is, card.tipCard);
    cout<<"Introduceti numarul de bilete:"<<endl;
    int numar;
    is >> numar;
    is.get();
    for(int i = 1; i <= numar; i++){
        cout<<"Biletul numarul "<<i<<"este de tipul:"<<endl;
        string tip;
        getline(is, tip);
        if(tip == "suprafata" && (card.tipCard == "suprafata" || card.tipCard == "subteran")){
            card.numatBilSuprafata++;
        }
        else if(tip == "subteran" && (card.tipCard == "suprafata" || card.tipCard == "subteran")){
            card.numarBilSubteran++;
        }
        else if(tip == "tranzit" && card.tipCard == "tranzit"){
            card.numarBilTranzit++;
        }
    }
    return is;
}

card::card(double pret, const string &tipBilet, const string &tipCard, const vector<bilet *> &bilete) : bilet(pret,
                                                                                                              tipBilet),
                                                                                                        tipCard(tipCard),
                                                                                                        bilete(bilete) {}

void card::adaugaBilet(bilet *bilet1, card &card1) {
    if(bilet1->getTipBilet() == "suprafata"){
        card1.numatBilSuprafata++;
    }
    else if(bilet1->getTipBilet() == "subteran"){
        card1.numarBilSubteran++;
    }
    else if(bilet1->getTipBilet() == "tranzit"){
        card1.numarBilTranzit++;
    }
}

class validator{
private:
    string loc;
public:
    validator();

    validator(const string &loc);

    void validareCard(card &card){
        if(loc == "suprafata"){
            if(card.getNumarBileteSuprafata() == 0){
                cout<<"Nu mai exista bilete"<<endl;
            } else{
                card.modificaNrSuprafata();
            }
        }
        else if(loc == "subteran"){
            if(card.getNumarBileteSubteran() == 0){
                cout<<"Nu mai exista bilete"<<endl;
            } else{
                card.modificaNrSubteran();
            }
        }
        else if(loc == "tranzit"){
            if(card.getNumarBileteSuTranzit() == 0){
                cout<<"Nu mai exista bilete"<<endl;
            } else{
                card.modificaNrTranzit();
            }
        }
    }

    friend ostream &operator<<(ostream &os,  validator &validator1);
    friend istream &operator>>(istream &is, validator &validator1);

};



ostream &operator<<(ostream &os, validator &validator1) {
    cout<<"Biletul";
}

istream &operator>>(istream &is, validator &validator1){
    cout<<"Tipul de validare:"<<endl;
    getline(is, validator1.loc);

}

validator::validator() {
    loc = "";
}

validator::validator(const string &loc) : loc(loc) {}


int main()
{
    validator vl;
    cin >> vl;
    bilet *bl;
    cin >> *bl;
    card *cl;
    cin >> *cl;
    card crd;
    cin >> crd;
    cl->adaugaBilet(bl, crd);
    return 0;
}
