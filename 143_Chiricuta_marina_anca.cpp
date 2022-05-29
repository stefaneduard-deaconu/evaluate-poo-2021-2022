//Chiricuta Marina Anca
//Deaconu Stefan Eduard
//Bundled MinGW Version: w64 9.0

#include <iostream>
#include <vector>

using namespace std;

class Bilet {

protected:
    string tipBilet;
    int pret;
    float pretF; // taxa biletului de metrou
    int zi;
    int luna;
    int an;
    int ora;
    int minut;
    int secunde;


public:
    Bilet()
    {
        zi=0;
        luna=0;
        an=2000;
        ora=0;
        minut=0;
        secunde=0;

    }
    Bilet(string tipBilet, int pret, float pretF,int zi, int luna, int an,int ora,int minut, int secunde)
    {
        this->tipBilet=tipBilet;
        this->pret=pret;
        this->pretF=pretF;
        this->zi=zi;
        this->luna=luna;
        this->an=an;
        this->ora=ora;
        this->minut=minut;
        this->secunde=secunde;

    }

    const string &getTipBilet() const {
        return tipBilet;
    }.
    void setTipBilet(const string &tipBilet) {
        Bilet::tipBilet = tipBilet;
    }
    int getPret() const {
        return pret;
    }
    void setPret(int pret) {
        Bilet::pret = pret;
    }
    float getPretF() const {
        return pretF;
    }
    void setPretF(float pretF) {
        Bilet::pretF = pretF;
    }
    int getZi() const {
        return zi;
    }
    void setZi(int zi) {
        Bilet::zi = zi;
    }
    int getLuna() const {
        return luna;
    }
    void setLuna(int luna) {
        Bilet::luna = luna;
    }
    int getAn() const {
        return an;
    }
    void setAn(int an) {
        Bilet::an = an;
    }
    int getOra() const {
        return ora;
    }
    void setOra(int ora) {
        Bilet::ora = ora;
    }
    int getMinut() const {
        return minut;
    }
    void setMinut(int minut) {
        Bilet::minut = minut;
    }
    int getSecunde() const {
        return secunde;
    }
    void setSecunde(int secunde) {
        Bilet::secunde = secunde;
    }
    friend  ostream& operator<<(ostream& out, const Bilet& bilet )
    {
        out<<bilet.tipBilet<<" "<<bilet.pret<<" "<<bilet.pretF<<" "<<bilet.zi<<" "<<bilet.luna<<" "<<bilet.an<<" "<<bilet.ora<<" "<<bilet.minut<<" "<<bilet.secunde;
        return out;
    };

};

class Card:virtual public Bilet{
private:
    string tipCard;
    vector <string> Tipbilete;
    vector <int> nrBilete;
    int contor;   // retine nr de bilete validate

public:
    Card(){
        tipCard=" ";
    }
    Card(string tipCard)

    {
        this->tipCard=tipCard;
    }
    const string &getTipCard() const {
        return tipCard;
    }
    void setTipCard(const string &tipCard) {
        Card::tipCard = tipCard;
    }

    const vector<string> &getTipbilete() const {
        return Tipbilete;
    }

    void setTipbilete(const vector<string> &tipbilete) {
        Tipbilete = tipbilete;
    }

    const vector<int> &getNrBilete() const {
        return nrBilete;
    }

    void setNrBilete(const vector<int> &nrBilete) {
        Card::nrBilete = nrBilete;
    }

    int getContor() const {
        return contor;
    }

    void setContor(int contor) {
        Card::contor = contor;
    }

};
class AparatValidare : public Bilet, public Card {



};

int main() {

return 0;
}
