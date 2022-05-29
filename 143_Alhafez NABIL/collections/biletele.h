//
// Created by Nabil Alhafez on 23.05.2022.
//

#ifndef COLOCVIU_BILETELE_H
#define COLOCVIU_BILETELE_H

#include "IoBase.h"
#include "date.h"
#include "enumerable.h"

using namespace std;

class Bilet : public IoBase {
protected:
    int codeUnique;
    int taxa;
    Date usingDate;
    Date validDate;
    bool isUsed;
    string locationOfUse;

public:
    istream &read(istream &is) override {

        IoBase::read(is);

        codeUnique = Enumerable().getId();
        cout << "Enter taxa: ";
        is >> taxa;

        cout << "Does it have a validation date (Y/N): ";
        char ans;
        is >> ans;

        if (ans == 'y' || ans == 'Y') {
            cout << "Enter validDate: ";
            is >> validDate;
        }

        isUsed = false;
        locationOfUse = "";

        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << "taxa: " << taxa;
        cout << "taxa: " << taxa;
        cout << ", usingDate: " << usingDate;
        cout << ", validDate: " << validDate;
        cout << ", locationOfUse: " << locationOfUse;

        return os;
    }

    virtual bool isValidBilet() {
        return !isUsed && !Date::checkDateIfZero(usingDate);
    }

    virtual int getUsedMint() const {
        return 0;
    }

    virtual void useBilet(string location) {

        ///  IMPORTANT
        /// for ease I assume the date in the function i will not pass it.....
        auto d = Date(22, 5, 2022);
        usingDate = d;

        this->locationOfUse = location;
        isUsed = true;
    }

    inline virtual int getId() const {
        return codeUnique;
    }
};

class SuprafataBilet : public Bilet {


};

class MetrouBilet : public Bilet {


};

class TranzitBilet : public Bilet {
private:
    static int OriginalMint;

protected:
    int usedMint = 0;


public:
    void useBilet(string location) override;

    bool isValidBilet() override {

        bool isValid = Bilet::isValidBilet() &&
                       checkDateIfLessThanOrEqualOfToday() &&
                       maiSuntMinuteInBilet();


        return isValid;
    }

private:
    bool checkDateIfLessThanOrEqualOfToday() {

        bool res = validDate.checkDateIfLessThanOrEqual(Date::getTodayDate());
        return res;

    }

    bool maiSuntMinuteInBilet() const {
        return usedMint < OriginalMint;
    }

};

int TranzitBilet::OriginalMint = 90;

void TranzitBilet::useBilet(string location) {
    Bilet::useBilet(location);
    cout << "how much minute: ";
    int minutes = 0;
    cin >> minutes;
    usedMint -= minutes;

}


#endif //COLOCVIU_BILETELE_H
