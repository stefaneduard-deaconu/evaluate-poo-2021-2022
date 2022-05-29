#include <iostream>
#include <string>
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

class Card_Suprafata: public IoBase{
private:
    int nrbilete=0;
    int nrbilete_subteran=0;
    int nrbilete_suprafata=0;
    int nrbilete_validate=0;
    string tipul_ub;
public:
    Card_Suprafata(int nrbilete,int nrbilete_subteran,int nrbilete_suprafata,int nrbilete_validate,string tipul_ub):nrbilete(nrbilete),
    nrbilete_subteran(nrbilete_subteran),nrbilete_suprafata(nrbilete_suprafata),nrbilete_validate(nrbilete_validate),tipul_ub(tipul_ub){}
    Card_Suprafata():nrbilete(0),nrbilete_suprafata(0),nrbilete_subteran(0),nrbilete_validate(0),tipul_ub(""){}

    int getnrbilete_validate(){
        return nrbilete_validate;
    }

    void setnrbilete_validate(int _nrbilvalidate){
        nrbilete_validate=_nrbilvalidate;
    }

    string gettipub(){
        return tipul_ub;
    }
    void settipup(string _tipub){
        tipul_ub=_tipub;
    }
    int getnrbilete(){
        return nrbilete;
    }
    int getnrbilete_subteran(){
        return nrbilete_subteran;
    }
    int getnrbilete_suprafata(){
        return nrbilete_suprafata;
    }
    void setnrbilete(int _nrbilete){
        nrbilete=_nrbilete;
    }
    void setnrbilete_subteran(int _nrbiletesubteran){
        nrbilete_subteran=_nrbiletesubteran;
    }
    void setnrbilete_suprafata(int _nrbiletesuprafata){
        nrbilete_suprafata=_nrbiletesuprafata;
    }
    void addbilet(){
        cout<<"Adaugam un bilet!"<<'\n';
        nrbilete+=1;

    }
    void addbilet_subteran(){
        cout<<"Adaugam un bilet de metrou!"<<'\n';
        nrbilete+=1;
        nrbilete_subteran+=1;

    }
    void addbilet_suprafata(){
        cout<<"Adaugam un bilet de suprafata!"<<'\n';
        nrbilete+=1;
        nrbilete_suprafata+=1;

    }

    istream &read(istream &is) override{
        IoBase::read(is);
        cout<<"Numar bilete: ";
        is>>nrbilete;
        cout<<"Numar bilete suprafata: ";
        is>>nrbilete_suprafata;
        cout<<"Numar bilete subteran: ";
        is>>nrbilete_subteran;
        cout<<"Numar bilete validate: ";
        is>>nrbilete_validate;
        return is;
    }

    ostream &write(ostream &os) const override{
        IoBase::write(os);
        cout<<"Numar bilete: "<<nrbilete<<'\n';
        cout<<"Numar bilete suprafata: "<<nrbilete_suprafata<<'\n';
        cout<<"Numar bilete subteran: "<<nrbilete_subteran<<'\n';
        cout<<"Numar bilete validate: "<<nrbilete_validate<<'\n';
        return os;

    }

};

class Card_Subteran: public IoBase{
private:
    int nrbilete=0;
    int nrbilete_subteran=0;
    int nrbilete_suprafata=0;
    int nrbilete_validate=0;
    string tipul_ub;

public:
    Card_Subteran(int nrbilete,int nrbilete_subteran,int nrbilete_suprafata,int nrbilete_validate,string tipul_ub):nrbilete(nrbilete),
                                                                              nrbilete_subteran(nrbilete_subteran),
                                                                              nrbilete_suprafata(nrbilete_suprafata),
                                                                              nrbilete_validate(nrbilete_validate),tipul_ub(tipul_ub){}
    Card_Subteran():nrbilete(0),nrbilete_suprafata(0),nrbilete_subteran(0),nrbilete_validate(0),tipul_ub(""){}

    int getnrbilete_validate(){
        return nrbilete_validate;
    }
    void setnrbilete_validate(int _nrbilvalidate){
        nrbilete_validate=_nrbilvalidate;
    }

    string gettipub(){
        return tipul_ub;
    }
    void settipup(string _tipub){
        tipul_ub=_tipub;
    }

    int getnrbilete(){
        return nrbilete;
    }
    int getnrbilete_subteran(){
        return nrbilete_subteran;
    }
    int getnrbilete_suprafata(){
        return nrbilete_suprafata;
    }
    void setnrbilete(int _nrbilete){
        nrbilete=_nrbilete;
    }
    void setnrbilete_subteran(int _nrbiletesubteran){
        nrbilete_subteran=_nrbiletesubteran;
    }
    void setnrbilete_suprafata(int _nrbiletesuprafata){
        nrbilete_suprafata=_nrbiletesuprafata;
    }
    void addbilet(){
        cout<<"Adaugam un bilet!"<<'\n';
        nrbilete+=1;

    }
    void addbilet_subteran(){
        cout<<"Adaugam un bilet de metrou!"<<'\n';
        nrbilete+=1;
        nrbilete_subteran+=1;

    }
    void addbilet_suprafata(){
        cout<<"Adaugam un bilet de suprafata!"<<'\n';
        nrbilete+=1;
        nrbilete_suprafata+=1;

    }

    istream &read(istream &is) override{
        IoBase::read(is);
        cout<<"Numar bilete: ";
        is>>nrbilete;
        cout<<"Numar bilete suprafata: ";
        is>>nrbilete_suprafata;
        cout<<"Numar bilete subteran: ";
        is>>nrbilete_subteran;
        cout<<"Numar bilete validate: ";
        is>>nrbilete_validate;
        return is;
    }

    ostream &write(ostream &os) const override{
        IoBase::write(os);
        cout<<"Numar bilete: "<<nrbilete<<'\n';
        cout<<"Numar bilete suprafata: "<<nrbilete_suprafata<<'\n';
        cout<<"Numar bilete subteran: "<<nrbilete_subteran<<'\n';
        cout<<"Numar bilete validate: "<<nrbilete_validate<<'\n';
        return os;

    }


};

class Card_Tranzit: public IoBase{
private:
    int nrbilete=0;
    int minute=0;
    int nrbilete_validate=0;
    string tipul_ub="tranzit";
public:
    Card_Tranzit(int nrbilete,int minute,int nrbilete_validate,string tipul_ub):nrbilete(nrbilete),minute(minute),
    nrbilete_validate(nrbilete_validate),tipul_ub(tipul_ub){}
    Card_Tranzit():nrbilete(0){}

    int getnrbilete(){
        return nrbilete;
    }

    int getnrbilete_validate(){
        return nrbilete_validate;
    }
    void setnrbilete_validate(int _nrbilvalidate){
        nrbilete_validate=_nrbilvalidate;
    }

    void setnrbilete(int _nrbilete){
        nrbilete=_nrbilete;
    }
    void addbilet(){
        cout<<"Adaugam un bilet de tranzit!"<<'\n';
        nrbilete+=1;
    }
    void setminute(int _minute){
        minute=_minute;
    }
    int getminute(){
        return minute;
    }

    istream &read(istream &is) override{
        IoBase::read(is);
        cout<<"Numar bilete: ";
        is>>nrbilete;
        cout<<"Minute: ";
        is>>minute;
        cout<<"Numar bilete validate: ";
        is>>nrbilete_validate;
        return is;
    }

    ostream &write(ostream &os) const override{
        IoBase::write(os);
        cout<<"Numar bilete: "<<nrbilete<<'\n';
        cout<<"Minute: "<<minute<<'\n';
        cout<<"Numar bilete validate: "<<nrbilete_validate<<'\n';
        cout<<"Tipul ultimului bilet folosit: "<<tipul_ub<<'\n';
        return os;

    }
};

class Aparat_Validare{
public:
    Card_Suprafata validare_card_suprafata(Card_Suprafata sup){
        if(sup.getnrbilete()>0){
            cout<<"Cardul tau de Suprafata este valid!"<<'\n';
            sup.setnrbilete(sup.getnrbilete()-1);
            sup.setnrbilete_suprafata(sup.getnrbilete_suprafata()-1);
            sup.setnrbilete_validate(sup.getnrbilete_validate()+1);
            if(sup.getnrbilete_validate()%8==0){
                sup.setnrbilete(sup.getnrbilete()+1);
                sup.setnrbilete_suprafata(sup.getnrbilete_suprafata()+1);
            }
            return sup;
        }

    }
    Card_Subteran validare_card_subteran(Card_Subteran sub){
        if(sub.getnrbilete()>0){
            cout<<"Cardul tau de Subteran este valid!"<<'\n';
            sub.setnrbilete(sub.getnrbilete()-1);
            sub.setnrbilete_subteran(sub.getnrbilete_subteran()-1);
            sub.setnrbilete_validate(sub.getnrbilete_validate()+1);
            if(sub.getnrbilete_validate()%8==0){
                sub.setnrbilete(sub.getnrbilete()+1);
                sub.setnrbilete_subteran(sub.getnrbilete_subteran()+1);
            }
            return sub;
        }
    }
    Card_Tranzit validare_card_tranzit(Card_Tranzit t){
        if(t.getminute()>0){
            cout<<"Cardul tau de Suprafata este valid!"<<'\n';
            t.setnrbilete(t.getnrbilete()-1);
            t.setnrbilete_validate(t.getnrbilete_validate()+1);
            t.setminute(90);
            if(t.getnrbilete_validate()%8==0){
                t.setnrbilete(t.getnrbilete()+1);
            }
            return t;
        }

    }

};

int main() {
    Card_Subteran c;
    Aparat_Validare a;
   /*c.addbilet_subteran();
    c.addbilet_subteran();
    c.addbilet_subteran();
    c.addbilet_subteran();
    c.addbilet_subteran();
    c.addbilet_subteran();
    c.addbilet_subteran();
    c.addbilet_subteran();
    nrbilete=c.getnrbilete();*/
    cin>>c;
    c.addbilet_subteran();
    cout<<c;
    c=a.validare_card_subteran(c);
    cout<<c;


}
