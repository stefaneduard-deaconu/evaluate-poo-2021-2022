// Student: Gheorghe Robert-Mihai
// Tutore laborator: Deaconu Eduard-Stefan
// Compilator: GNU G++

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class IoBase {
private:
public:
	virtual istream& read(istream& is) { 
		return is; 	
	}

	virtual ostream& write(ostream& os) const { // nu este nevoie de obiectul citit, pt ca avem this
		return os; 	
	}

	friend ostream& operator<<(ostream& os, const IoBase& base) {
		return base.write(os);
	}

	friend istream& operator>>(istream& is, IoBase& base) {
		return base.read(is);
	}
};

class Bilet : public IoBase {
protected:
	double taxa;
	virtual void setTaxa() = 0;
};

class BiletSuprafata : public Bilet {
	void setTaxa() {
		taxa = 2;
	}
public:
	friend class CardSuprafata;
	BiletSuprafata() {
		setTaxa();
	}
};

class BiletMetrou : public Bilet {
	void setTaxa() {
		taxa = 2.5;
	}
public:
	friend class CardSubteran;
	BiletMetrou() {
		setTaxa();
	}
};

class BiletTranzit: virtual public BiletSuprafata, virtual public BiletMetrou {
	void setTaxa() {
		BiletSuprafata::taxa = 3;
	}
	int minut;
public:
	friend class CardTranzit;
	BiletTranzit():minut(0){}
	BiletTranzit(int minut):minut(minut) {
		setTaxa();
	}
};

class Card: public IoBase {
protected:
	vector<shared_ptr<Bilet>> bilete;
	vector<shared_ptr<BiletTranzit>> biletetranzit;
	vector<shared_ptr<Bilet>> bilete_validate;
	vector<shared_ptr<BiletTranzit>> biletetranzit_validate;
public:
	friend class Bilet;
	friend class SingletonMenu;
};

class CardSuprafata : public Card {
public:
	ostream& write(ostream& os) {
		IoBase::write(os);
		int suma = 0;
		if (bilete.size())
			cout << "Tipul ultimului bilet validat a fost bilet de suprafata.\n";
		for (int i = bilete.size() - 1; i >= 0; i--)
		{
			int ok = 0;
			for (int j = 0; j < bilete_validate.size() - 1; i++)
				if (bilete[i] == bilete_validate[i])
					ok = 1;
			if (!ok)
				suma += dynamic_pointer_cast<BiletSuprafata>(bilete[i])->taxa;
		}
		cout << "Suma biletelor neutilizate este de " << suma << " lei\n";
		return os;
	}
};

class CardSubteran : public Card {
public:
	ostream& write(ostream& os) {
		IoBase::write(os);
		int suma = 0;
		if (bilete.size())
			cout << "Tipul ultimului bilet validat a fost bilet de subteran.\n";
		for (int i = bilete.size() - 1; i >= 0; i--)
		{
			int ok = 0;
			for (int j = 0; j < bilete_validate.size() - 1; i++)
				if (bilete[i] == bilete_validate[i])
					ok = 1;
			if (!ok)
				suma += dynamic_pointer_cast<BiletMetrou>(bilete[i])->taxa;
		}
		cout << "Suma biletelor neutilizate este de " << suma << " lei\n";
		return os;
	}
};

class CardTranzit : public Card {
public:
	ostream& write(ostream& os) {
		IoBase::write(os);
		int suma = 0;
		if (biletetranzit.size())
			cout << "Tipul ultimului bilet validat a fost bilet de tranzit.\n";
		for (int i = biletetranzit.size() - 1; i >= 0; i--)
		{
			int ok = 0;
			for (int j = 0; j < biletetranzit_validate.size() - 1; i++)
				if (biletetranzit[i] == biletetranzit_validate[i])
					ok = 1;
			if (biletetranzit[i]->minut > 90)
				cout << "Expirat\n";
			else
				cout << "Biletul mai este valid " << 90 - biletetranzit[i]->minut << " minute.\n";
			if (!ok)
				suma += dynamic_pointer_cast<BiletTranzit>(biletetranzit[i])->BiletSuprafata::taxa;
		}
		cout << "Suma biletelor neutilizate este de " << suma << " lei\n";
		return os;
	}
	~CardTranzit();
};

class SingletonMenu : public IoBase {
private:
	static SingletonMenu* instance;
	SingletonMenu() :carduri(carduri) {};
	vector<shared_ptr<Card>> carduri;
public:
	static SingletonMenu* getInstance(){
		if (instance != nullptr)
			return instance;
		SingletonMenu* instance = new SingletonMenu();
		return instance;
	}
	void mainLoop();
	void chooseOption();
	void listOptions();
};

SingletonMenu* SingletonMenu::instance = nullptr;

void SingletonMenu::mainLoop() {
	while (true)
	{
		listOptions();
		chooseOption();
	}
}

void SingletonMenu::listOptions() {
	cout << "1. Creati un nou card.\n2. Creati un aparat de validare.\n3. Adaugati un nou bilet la un card.\n4. Valideaza un card.\n5. Modifica minutul curent.\n6. Afisati detalii despre un card.\n7. Afisati detaliile unui apart de validare.\n";
}

void SingletonMenu::chooseOption() {
	int choice;
	cout << "Alegerea dumneavoastra: ";
	cin >> choice;
	switch (choice) {
	case 1:
	{
		int tip;
		do {
			cout << "Introduceti tipul cardului (0 = suprafata, 1 = subteran, 2 = tranzit): ";
			cin >> tip;
			if (tip < 0 || tip>2)
				cout << "Invalid\n";
		} while (tip < 0 || tip>2);
		switch (tip) {
		case 0:
		{
			CardSuprafata c;
			carduri.push_back(make_shared<CardSuprafata>(c));
			break;
		}
		case 1:
		{
			CardSubteran c;
			carduri.push_back(make_shared<CardSubteran>(c));
			break;
		}
		}
		cout << "Card creat cu succes!\n";
		break;
	}
	case 3:
	{
		int index;
		cout << "Introduceti indexul cardului: ";
		cin >> index;
		if (index >= carduri.size())
			cout << "Index invalid\n";
		else
		{
			if (dynamic_pointer_cast<CardSuprafata>(carduri[index]))
			{
				BiletSuprafata b;
				carduri[index]->bilete.push_back(make_shared<BiletSuprafata>(b));
				if (carduri[index]->bilete.size() % 8 == 0)
					carduri[index]->bilete.push_back(make_shared<BiletSuprafata>(BiletSuprafata()));
			}
			else if (dynamic_pointer_cast<CardSubteran>(carduri[index]))
			{
				BiletMetrou b;
				carduri[index]->bilete.push_back(make_shared<BiletMetrou>(b));
				if (carduri[index]->bilete.size() % 8 == 0)
					carduri[index]->bilete.push_back(make_shared<BiletMetrou>(BiletMetrou()));
			}
			else if (dynamic_pointer_cast<CardTranzit>(carduri[index]))
			{
				BiletTranzit b;
				carduri[index]->biletetranzit.push_back(make_shared<BiletTranzit>(b));
				if (carduri[index]->biletetranzit.size() % 8 == 0)
					carduri[index]->biletetranzit.push_back(make_shared<BiletTranzit>(BiletTranzit()));
			}
		}
		cout << "Bilet adaugat cu succes!\n";
		break;
	}
	case 4:
	{
		int index;
		cout << "Introduceti indexul cardului: ";
		cin >> index;
		if (index > carduri.size())
			cout << "Index invalid\n";
		else
			if (dynamic_pointer_cast<CardSuprafata>(carduri[index]))
			{
				BiletSuprafata b;
				int valid = 0;
				carduri[index]->bilete.push_back(make_shared<BiletSuprafata>(b));
				if (carduri[index]->bilete.size() % 8 == 0)
					carduri[index]->bilete.push_back(make_shared<BiletSuprafata>(BiletSuprafata()));
				for (int i = carduri[index]->bilete.size() - 1; i >= 0; i--)
				{
					int ok = 0;
					for (int j = 0; j < carduri[index]->bilete_validate.size() - 1; i++)
						if (carduri[index]->bilete[i] == carduri[index]->bilete_validate[i])
							ok = 1;
					if (!ok)
					{
						carduri[index]->bilete_validate.push_back(carduri[index]->bilete[i]);
						valid = 1;
					}
					if (valid)
						cout << "Card validat cu succes!\n";
					else
						cout << "Card invalid.\n";
				}
			}
			else if (dynamic_pointer_cast<CardSubteran>(carduri[index]))
			{
				BiletMetrou b;
				int valid = 0;
				carduri[index]->bilete.push_back(make_shared<BiletMetrou>(b));
				if (carduri[index]->bilete.size() % 8 == 0)
					carduri[index]->bilete.push_back(make_shared<BiletMetrou>(BiletMetrou()));
				for (int i = carduri[index]->bilete.size() - 1; i >= 0; i--)
				{
					int ok = 0;
					for (int j = 0; j < carduri[index]->bilete_validate.size() - 1; i++)
						if (carduri[index]->bilete[i] == carduri[index]->bilete_validate[i])
							ok = 1;
					if (!ok)
					{
						carduri[index]->bilete_validate.push_back(carduri[index]->bilete[i]);
						valid = 1;
					}
					if (valid)
						cout << "Card validat cu succes!\n";
					else
						cout << "Card invalid.\n";
				}
			}
			else if (dynamic_pointer_cast<CardTranzit>(carduri[index]))
			{
				BiletTranzit b;
				int valid = 0;
				carduri[index]->biletetranzit.push_back(make_shared<BiletTranzit>(b));
				if (carduri[index]->biletetranzit.size() % 8 == 0)
					carduri[index]->biletetranzit.push_back(make_shared<BiletTranzit>(BiletTranzit()));
				for (int i = carduri[index]->biletetranzit.size() - 1; i >= 0; i--)
				{
					int ok = 0;
					for (int j = 0; j < carduri[index]->biletetranzit_validate.size() - 1; i++)
						if (carduri[index]->biletetranzit[i] == carduri[index]->biletetranzit_validate[i])
							ok = 1;
					if (!ok)
					{
						carduri[index]->biletetranzit_validate.push_back(carduri[index]->biletetranzit[i]);
						valid = 1;
					}
					if (valid)
						cout << "Card validat cu succes!\n";
					else
						cout << "Card invalid.\n";
				}
			}
		break;
	}
	}
};
int main()
{
	SingletonMenu* m = SingletonMenu::getInstance();
	m->mainLoop();
	return 0;
}
