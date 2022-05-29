//Tutore Laborator: Stefan Eduard Deaconu
//Student Nafornita Adrian-Valentin @ 143 INFO an1
//MinGW 64 9.0

#include "iostream"
#include "algorithm"
#include "cstring"
#include "vector"
#include "bits/stdc++.h"

using namespace std;

template <typename T>
istream &operator>> (istream &is, vector<T> &v){
    v.clear();
    int nr_elem;
    cout<<"numar_elem:";
    cin>>nr_elem;
    for (int i = 0; i < nr_elem; i++){
        T mine;
        cin >> mine;
        v.push_back(mine);
    }
    return is;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v){
    os<< "[ ";
    for (auto i: v){
        os<<i<<' ';
    }
    os<<"]";
    return os;
}

class IO{
public:
    virtual istream &read(istream &is){
        return is;
    }
    virtual ostream &write(ostream &os)const{
        return os;
    }
    friend istream &operator>>(istream &is, IO &baza){
        return baza.read(is);
    }
    friend ostream &operator<< (ostream &os, const IO &baza){
        return baza.write(os);
    }

};

int timpul = 3600;
// timpul e universal

class suprafata{
protected:
    double pret = 2;

};

class metrou{
protected:
    double pret = 2.5;
};
class tranzit{
protected:
    double pret = 3;
    int time = 90;
public:
    void updtime(int a){
        time -= a;
    }
    int getime(){
        return time;
    }
};

class transp_supr:public IO{
protected:
    vector<suprafata> one;
    vector<metrou> two;
    int ramase_bonus = 8;// trateaza la o validare bonusul
public:
    transp_supr(const vector<suprafata> &one, const vector<metrou> &two) : one(one), two(two) {}
    transp_supr() = default;

    void addmetrou(){
        metrou any;
        two.push_back(any);
    }
    void addsupr(){
        suprafata any;
        one.push_back(any);
    }

    virtual ~transp_supr() {
    one.clear();
    two.clear();
    }
    void validez(string a){
        bool allright = 0;
        if(a == "metrou" && two.size()>0){
            two.pop_back();
            allright = 1;
        }

        if(a == "suprafata"&&one.size()>0){
            one.pop_back();
            allright = 1;
        }
            if(allright){
        ramase_bonus--;
        if(!ramase_bonus){
            ramase_bonus = 8;
            suprafata x;// final intreaba in consola daca e suprafata sau metrou posib alegere
            one.push_back(x);
        }}
            else cout<<"\nCeva nu este in regula, verificati input sau numar de calatorii\n";
    }
    ostream &write(ostream &os) const override{
        os<<"suprafata ramase: ";
        os<<one.size();
        os<<"\nmetrou ramase: ";
        os<<two.size();
        os<<"\nRamase pana la bonus:"<<ramase_bonus;
        return os;
    }
};

class tranzit_card:public IO{
protected:
    vector<tranzit> one;
    vector<bool> validate;
    int ramase_bonus = 8;// iarasi, trateaza validare
public:
    tranzit_card(const vector<tranzit> &one) : one(one) {}
    tranzit_card()= default;
    virtual ~tranzit_card() {
        one.clear();
    }
    void setvalid(){
        for (auto i: one);
        validate.push_back(0);
    }
    void addtranz(){
        tranzit any;
        one.push_back(any);
        validate.push_back(0);
    }
    ostream &write (ostream&os) const override{
        IO::write(os);
        cout<<"calatorii ramase: "<<one.size();
        cout<<"\nTimpii aferenti calatoriilor din card:\n";
        for (auto i: one)
            os<<i.getime()<<'\n';
        return os;
    }

    void time_passed(int a){
        timpul += a;
        for(int i = 0; i < one.size(); i++){
            if(validate[i])one[i].updtime(a);
            if (one[i].getime() <= 0) {
                one.erase(one.begin()+i);
                validate.erase(validate.begin()+i);
            }
        }
    }
    void validez(){
        for(int i = validate.size()-1 ; i >=0; i++) {
            if (validate[i] == 0){
                validate[i] = 1;
                break;
                }
        }
        if(ramase_bonus == 0){
            ramase_bonus = 8;
            tranzit M;
            one.push_back(M);
            validate.push_back(0);
        }

    }
};

class ghiseu:public IO{
protected:
    vector<transp_supr> X;
    vector<tranzit_card> Y;
    string locatie;
public:
    string getloc(){
        return locatie;
    }
    ghiseu(const vector<transp_supr> &x, const vector<tranzit_card> &y) : X(x), Y(y){}
    ghiseu() = default;
    virtual ~ghiseu() {
    X.clear();
    Y.clear();
    }
    void modifytime(int a){
        for(auto i: Y)
            i.time_passed(a);
            timpul += a;
    }
    void addcard(string a){
        if(a == "metrou" || a == "suprafata"){
            transp_supr one;
            X.push_back(one);
        }
    }
    void addbilet(string a, int ord){
        bool ok = 0;
        if(a =="metrou") {
            if (ord < X.size()) {
                X[ord].addmetrou();
                ok = 1;
            }
        }
            if(a =="suprafata"){
                if(ord<X.size()){
                    X[ord].addsupr();
                    ok = 1;
                }
            }
        if(a =="tranzit"){
            if(ord<Y.size()){
                Y[ord].addtranz();
                ok = 1;
            }
        }
        if (!ok)cout<<"\nNumarul de card nu este inregistrat\n";
    }
    ostream &write(ostream &os) const override{
        IO::write(os);
        os<<X<<'\n';
        os<<Y;
        return os;
    }
};

int main() {
    /*suprafata a;
    suprafata b;
    metrou c;
    vector<suprafata> x;
    vector<metrou> y;

    x.push_back(a);
    x.push_back(b);
    y.push_back(c);
    transp_supr cartelaverde(x,y);
    cout<<mine;
    mine.validez("metrou");
    cout<<mine;
    mine.validez("metrou");
    tranzit one;
    tranzit two;
    vector<tranzit> alabala;
    tranzit_card cartelalbastra(alabala);
    mine.push_back(one);
    mine.push_back(two);
    tranzit_card stb(alabala);
    stb.setvalid();
    stb.validez();
    // va scurge timp doar din calatoriile ce au fost activate
    stb.time_passed(45);
    cout<<stb;
    stb.validez();
    stb.time_passed(45);
    cout<<stb;
    ghiseu basarab(cartelaverde, cartelalbastra);
    cout<<basarab.getloc();
*/
    suprafata one;
    metrou two;
    vector<suprafata> X;
    X.push_back(one);
    vector<metrou> Y;
    Y.push_back(two);
    // de completat realizare card suprafata, tranzit, creare ghiseu , demonstrare adauga card, elapsed time
    //functii din clase realizate
    return 0;
}
