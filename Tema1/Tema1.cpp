#include <iostream>
using namespace std;

class Autobuz {
private:
	static int nrAutobuze;
	const int idAutobuz;
	int capacitate;
	int nrPersoaneImbarcate;
	char* producator;

public:
	Autobuz():idAutobuz(++nrAutobuze) {
		this->capacitate = 0;
		this->nrPersoaneImbarcate = 0;
		this->producator = nullptr;
	}

	Autobuz(int capcaitate, int nrPersoaneImbarcate, char* producator):idAutobuz(++nrAutobuze) {
		this->capacitate = capcaitate;

		if (nrPersoaneImbarcate > capacitate) {
			cout << "Autobuzul cu ID " << this->idAutobuz << ". Nr persoane imbarcate nu poate fi mai pare decat capacitatea!\n";
			throw 400;
		}
		else {
			this->nrPersoaneImbarcate = nrPersoaneImbarcate;
		}

		this->producator = producator;
	}

	Autobuz(const Autobuz& a):idAutobuz(++nrAutobuze) {
		this->capacitate = a.capacitate;
		this->nrPersoaneImbarcate = a.nrPersoaneImbarcate;

		if (a.producator != nullptr)
		{
			int lungimeProducator = strlen(a.producator);
			this->producator = new char[lungimeProducator];
			strcpy(this->producator, a.producator);
		}
	}

	~Autobuz() {
		if (this->producator != nullptr) {
			//nu stiu de ce, dar imi da eroare daca las linia asta sa ruleze
			//delete[] this->producator; 
		}
	}

	int getCapacitate() {
		return this->capacitate;
	}

	void setCapacitate(int capacitate) {
		this->capacitate = capacitate;
	}

	int getNrPersoaneImbarcate() {
		return this->nrPersoaneImbarcate;
	}

	void setNrPersoaneImbarcate(int nrPersoaneImbarcate) {
		if (nrPersoaneImbarcate > this->capacitate) {
			cout << "Nr persoane imbarcate nu poate fi mai mare decat capacitatea!\n";
			throw 400;
		}
		else 
		{
			this->nrPersoaneImbarcate = nrPersoaneImbarcate;
		}
	}

	const Autobuz& operator=(const Autobuz& a) {
		if (this == &a) {
			return *this;
		}

		this->capacitate = a.capacitate;
		this->nrPersoaneImbarcate = a.nrPersoaneImbarcate;
		
		if (this->producator != nullptr) {
			delete[] this->producator;
		}

		int lungimeProducator = strlen(a.producator);
		this->producator = new char[lungimeProducator];
		strcpy(this->producator, a.producator);

		return *this;
	}

	friend ostream& operator<<(ostream& os, const Autobuz& a);

	int getNumarLocuriLibere() {
		return capacitate - nrPersoaneImbarcate;
	}

	operator int() const {
		return this->nrPersoaneImbarcate;
	}

	bool operator>(const Autobuz& a) const {
		return this->capacitate > a.capacitate;
	}
};

ostream& operator<<(ostream& os, const Autobuz& a) {
	os << a.idAutobuz << "; " << a.capacitate << "; " << a.nrPersoaneImbarcate << "; ";
	if (a.producator == nullptr) {
		os << "nedefinit";
	}
	else {
		os << a.producator;
	}
	return os;
}

int Autobuz::nrAutobuze = 0;

int main() {
	char producator1[] = "Producator 1";
	Autobuz a1(10, 5, producator1);
	Autobuz a2(a1);
	Autobuz a3;
	a3 = a1;
	cout << "a1: " << a1 << "\n";
	cout << "a2: " << a2 << "\n";
	cout << "a3: " << a3 << "\n";

	a1.setCapacitate(4);
	cout << "capacitate a1: " << a1.getCapacitate() << "\n";
	a1.setNrPersoaneImbarcate(2);
	cout << "persoane imbarcate a1: " << a1.getNrPersoaneImbarcate() << "\n";
	cout << "nr locuri libere a1: " << a1.getNumarLocuriLibere() << "\n";

	int nrPersoaneImbarcate_a1 = a1;
	cout << "persoane imbarcate a1: " << nrPersoaneImbarcate_a1 << "\n";

	char producator2[] = "Producator 2";
	Autobuz a4(11, 5, producator2);

	bool x = a1 > a4;
	cout << "a1 > a4: " << x << "\n";
}
