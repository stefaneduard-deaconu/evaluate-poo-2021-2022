/* nume: Nechita Maria-Ilinca
   grupa: 143
   compilator: MinGW w64 9.0
   nume tutore laborator: Deaconu Stefan-Eduard
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//3 tipuri de bilete
//3 tipuri de carduri

class Bilet{
protected:
    static int id;
    bool valid;
    int zi, luna, an;
    int ora,minut;
public:
    Bilet(bool _valid, int _zi, int _luna, int _an, int _ora, int _minut){++id; valid=_valid; luna=_luna; zi=_zi; an=_an; ora=_ora;minut=_minut;}

    bool getValid(){return valid;}
    void setValid(bool _valid){valid=_valid;}

    int getAn(){return an;}
    void setAn(int _an){an=_an;}

    int getLuna(){return luna;}
    void setLuna(int _luna){luna=_luna;}

    int getZi(){return zi;}
    void setZi(int _zi){zi=_zi;}

    int getOra() {return ora;}
    void setOra(int _ora){ora=_ora;}

    int getMinut () {return minut;}
    void setMinut (int _minut) {minut=_minut;}

    Bilet (const Bilet&ob)
    {
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
    }

    Bilet();

    Bilet &operator= (const Bilet&ob)
    {
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        valid=ob.valid;
        return *this;
    }

    friend istream &operator >> (istream &is, Bilet&b);
    friend ostream &operator << (ostream &os, Bilet&b);


};

//Bilet::Bilet id=0;
// daca nu exista data, biletul nu e valid

istream &operator >> (istream &is, Bilet&b){
    cout << "Introduceti data:\n";
    bool bisect=0;
    is >> b.an;
    if (b.an%4==0)
        bisect =1;
    int date[]={31,28,31,30,31,30,31,31,30,31,30,31};
    try {
        is >> b.luna;
        if (b.luna<0 || b.luna>12)
            throw("Luna invalida!");
        else
        {
            is >> b.zi;
            if (!((b.zi != date[b.luna]) || (bisect==1 && b.luna==2 && b.zi==29 )))
                throw("Data invalida!");
            else
                b.valid=true;
            {
                is >> b.ora;
                is >> b.minut;
            }
        }
    }
    catch (string s)
    { cout << s << '\n';}

    return is;
}


Bilet::Bilet() {}

class BiletSuprafata: public Bilet
{
private:
    double pret;
public:
    BiletSuprafata()=default;
    BiletSuprafata(bool valid, double _pret) : Bilet() { pret=_pret;}
    double getPret(){return pret;}
    void  setPret(double _pret){pret=_pret;}

    BiletSuprafata (const BiletSuprafata&ob)
    {
        valid=ob.valid;
     zi=ob.zi;
     luna=ob.luna;
      an=ob.an;
    }

    BiletSuprafata &operator=(const BiletSuprafata&ob)
    {
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
    }

};

class BiletMetrou : public Bilet{
private:
    double pret;
public:
    BiletMetrou() = default;
    BiletMetrou(double _pret): Bilet() { pret = _pret; }
    double getPret() { return pret; }
    void setPret(double _pret) { pret = _pret; }

    BiletMetrou (const BiletMetrou&ob)
    {
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        pret=ob.pret;
    }

    BiletMetrou &operator=(const BiletMetrou&ob)
    {
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        pret=ob.pret;
    }

};
class BiletTranzit:public Bilet {
private:
    double pret;
public:
    BiletTranzit() = default;

    BiletTranzit(double _pret) : Bilet() { pret = _pret; }

    double getPret() { return pret; }
    void setPret(double _pret) { pret = _pret; }


    BiletTranzit (const BiletTranzit&ob)
    {
        pret=ob.pret;
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
    }

    BiletTranzit &operator=(const BiletTranzit&ob)
    {
        pret=ob.pret;
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        return *this;
    }
    friend istream &operator << (istream &is,BiletTranzit&b);
    friend ostream &operator >> (ostream&os,BiletTranzit&b);
};

//istream &operator >> (istream &is, BiletTranzit&b){
//    cout << "Introduceti data:\n";
//    is >> b->pret;
//    bool bisect=0;
//    is >> b.an;
//    if (b.an%4==0)
//        bisect =1;
//    int date[]={31,28,31,30,31,30,31,31,30,31,30,31};
//    try {
//        is >> b.luna;
//        if (b.luna<0 || b.luna>12)
//            throw("Luna invalida!");
//        else
//        {
//            is >> b.zi;
//            if (!((b.zi != date[b.luna]) || (bisect==1 && b.luna==2 && b.zi==29 )))
//                throw("Data invalida!");
//            else
//                b.valid=true;
//        }
//    }
//    catch (string s)
//    { cout << s << '\n';}
//
//
//    return is;
//}


ostream &operator << (ostream &os, Bilet&b)
{
    os << "Data: " << b.an << b.luna << b.zi;
    return os;
}



class  Card:public Bilet{
protected:
    static int idCard;
    bool clone;
public:
    Card(const Bilet &ob, bool _clone) : Bilet(ob) {++idCard; clone=_clone;}
    Card (const Card&c)
    {
        clone=c.clone;
    }
    Card &operator=(const Card&c)
    {
        clone=c.clone;
        return *this;
    }

   friend istream &operator >> (istream &is, Card&c);
    friend ostream &operator << (ostream &os, Card&c);
};

istream &operator >> (istream &is, Card&c){
    cout << "Introduceti data:\n";
    bool bisect=0;
    is >> c.an;
    if (c.an%4==0)
        bisect =1;
    int date[]={31,28,31,30,31,30,31,31,30,31,30,31};
    try {
        is >> c.luna;
        if (c.luna<0 || c.luna>12)
            throw("Luna invalida!");
        else
        {
            is >> c.zi;
            if (!((c.zi != date[c.luna]) || (bisect==1 && c.luna==2 && c.zi==29 )))
                throw("Data invalida!");
            else
                c.valid=true;
        }
    }
    catch (string s)
    { cout << s << '\n';}
    return is;
}


ostream &operator << (ostream &os, Card&c)
{
    os << "Data: " << c.an << c.luna << c.zi;
    return os;
}

// to do-implementare card



class CardSuprafata :public Bilet {
    private:
        double pret;
    public:
    CardSuprafata() = default;
    CardSuprafata(double _pret): Bilet() { pret = _pret; }
        double getPret() { return pret; }
        void setPret(double _pret) { pret = _pret; }

    CardSuprafata (const CardSuprafata&ob)
        {
            valid=ob.valid;
            zi=ob.zi;
            luna=ob.luna;
            an=ob.an;
            pret=ob.pret;
        }

    CardSuprafata &operator=(const CardSuprafata&ob)
        {
            valid=ob.valid;
            zi=ob.zi;
            luna=ob.luna;
            an=ob.an;
            pret=ob.pret;
        }
};

class CardSubteran:public Bilet{
private:
    double pret;
public:
    CardSubteran() = default;
    CardSubteran(double _pret): Bilet() { pret = _pret; }
    double getPret() { return pret; }
    void setPret(double _pret) { pret = _pret; }

    CardSubteran (const CardSubteran&ob)
    {
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        pret=ob.pret;
    }

    CardSubteran &operator=(const CardSubteran&ob)
    {
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        pret=ob.pret;
    }
};


class CardTranzit :public Bilet{
private:
    double pret;
public:
    CardTranzit() = default;
    CardTranzit(double _pret): Bilet() { pret = _pret; }
    double getPret() { return pret; }
    void setPret(double _pret) { pret = _pret; }

    CardTranzit (const CardTranzit&ob)
    {
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        pret=ob.pret;
    }

    CardTranzit &operator=(const CardTranzit&ob)
    {
        valid=ob.valid;
        zi=ob.zi;
        luna=ob.luna;
        an=ob.an;
        pret=ob.pret;
    }
};

// aparate pentru validarea cardurilor
class Aparat{
private:
    vector <Bilet*> bilete;
public:
    void eliberarebilete();
};

void Aparat::eliberarebilete() {
    Bilet *bil;
    cin >> *bil;
//    if (BiletSuprafata*b=dynamic_cast<BiletSuprafata*>bil)
//        bilete.push_back(new BiletSuprafata);
//    if (BiletMetrou*b=dynamic_cast<BiletMetrou*>bil)
//        bilete.push_back(new BiletSuprafata);
//    if (BiletTranzit*b=dynamic_cast<BiletSuprafata*>bil)
//        bilete.push_back(new BiletTranzit);
}


class MeniuInteractiv{
private:
    vector <Bilet*> bilete;
    vector <Aparat*> achizitii;
    MeniuInteractiv* instance;
    MeniuInteractiv()=default;
    MeniuInteractiv(const MeniuInteractiv&m)=default;
public:
    MeniuInteractiv getInstance()
    {
        if (instance==nullptr)
            instance=new MeniuInteractiv;
        return reinterpret_cast<const MeniuInteractiv &>(instance);
    }

    void deleteInstance()
    {
        if (instance!=nullptr)
            instance= nullptr;
    }
    void creareaparat();
    void crearecard();
    void modificareminut();
};

void MeniuInteractiv::creareaparat() {
    Aparat *a=new Aparat;
    achizitii.push_back(a);
}

void MeniuInteractiv::crearecard() {
    Bilet *b=new Bilet;
    bilete.push_back(b);
    if (bilete.size()>0 && bilete.size()%8==0)
        for (int i=1;i<=bilete.size();i++) {
//            if (BiletSuprafata*b=dynamic_cast<BiletSuprafata*>bil)
//                bilete.push_back(new CardSuprafata);
//            if (BiletMetrou*b=dynamic_cast<BiletMetrou*>bil)
//                bilete.push_back(new CardTranzit);
//            if (BiletTranzit*b=dynamic_cast<BiletSuprafata*>bil)
//                bilete.push_back(new BiletTranzit);
        }

}

void MeniuInteractiv:: modificareminut(){
    int i;
    for(i=0;i<bilete.size();i++)
        if (bilete[i]->getMinut()<30)
         bilete[i]->setMinut(59);
};


//MeniuInteractiv::MeniuInteractiv *instance=nullptr;

int main() {
    MeniuInteractiv *m;
    m->getInstance();
    int choice;
    while (true) {
        cout << "1. Crearea unui card.\n";
        cout << "2. Crearea unui aparat. \n";
        cout << "3. Adaugarea unui bilet la card. \n";
        cout << "4. Validarea unui card. \n ";
        cout << " 5. Modificarea minutului curent.\n";
        try {
            cin >> choice;
            if (choice < 0 && choice > 5)
                throw ("Optiune invalida!");
            switch(choice)
            {
                case 1:
                    m->crearecard();
                case 2:
                    m->creareaparat();
                case 3:
                    //
                case 4:
                    //
                case 5:
                    cout << " ";
                    //


            }
        }

        catch(string s){
            cout << s << '\n';
    }
    }
    m->deleteInstance();
    return 0;
}
