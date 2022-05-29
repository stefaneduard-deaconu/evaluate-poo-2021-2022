//
// Created by Nabil Alhafez on 23.05.2022.
//

#ifndef COLOCVIU_DATE_H
#define COLOCVIU_DATE_H

#include "IoBase.h"

class Date : public IoBase {
private:
    static Date zero;
    static Date today;
protected:
    int zi, luna, an;


public :
    Date() {
        zi = 0;
        luna = 0;
        an = 0;
    };


    Date(int zi, int luna, int an);

    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "Enter an: ";
        is >> an;
        cout << "Enter luna: ";
        is >> luna;
        cout << "Enter zi: ";
        is >> zi;


        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << "Date(";
        cout << "an: " << an;
        cout << ", luna: " << luna;
        cout << ", an: " << an;
        cout << ")";


        return os;
    }

    bool checkDateIfLessThanOrEqual(const Date &date) {
        return zi >= date.zi
               &&
               luna >= date.luna &&
               an >= date.an;


    }

    static bool checkDateIfZero(const Date &date) {
        return date.an == zero.an &&
               date.luna == zero.luna &&
               date.zi == zero.zi;

    }

    static Date getTodayDate() {
        // current date of today for comparison;
//        int zi = 23;
//        int luna = 5;
//        int an = 2022;
        return Date(23, 5, 2022);

    }
};


Date  Date::zero = Date();

Date::Date(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}

#endif //COLOCVIU_DATE_H
