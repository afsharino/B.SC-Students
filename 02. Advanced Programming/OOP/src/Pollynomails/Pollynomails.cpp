#include <iostream>
using namespace std;
const int mySize = 11;

class Poly {

public:
	Poly(int = 0);//default constructor
	void set();
	void print();

	bool operator==(Poly&);
	bool operator!=(Poly&);
	Poly operator+(Poly&);
	Poly operator*(Poly&);
	int operator[](int) const;
	int& operator[](int);

private:
	int coef[mySize];
	int degree;

};

Poly::Poly(int n) {
	if (n >= 0 && n <= 10) {
		degree = n;
	}
	else {
		cout << "invalid parameter please try again buddy!" << endl;
	}
}
void Poly::set() {
	for (int i = degree; i >= 0; i--) {
		//cout << "please enter coef[" << i << "]: ";
		cin >> coef[i];
		if (i == degree) {
			if (coef[i] == 0) {
				cout << "invalid parameter please try again buddy!" << endl;
				coef[i] = 1;
			}
		}
	}
}
void Poly::print() {
	cout << coef[degree] << "x^" << degree;
	for (int i = degree - 1; i >= 0; i--) {
		if (coef[i] > 0) {
			if (i != 1 && i != 0) {
				cout << "+" << coef[i] << "x^" << i;
			}
			else if (i == 1) {
				cout << "+" << coef[i] << "x";
			}
			else if (i == 0) {
				cout << "+" << coef[i];
			}
		}
		else if (coef[i] < 0) {
			if (i != 1 && i != 0) {
				cout << coef[i] << "x^" << i;
			}
			else if (i == 1) {
				cout << coef[i] << "x";
			}
			else if (i == 0) {
				cout << coef[i];
			}
		}
	}
}
bool Poly::operator==(Poly& p2) {
	if (degree != p2.degree) {
		return (false);
	}
	for (int i = 0; i < degree; i++) {
		if (coef[i] != p2.coef[i]) {
			return (false);
		}
	}
	return (true);

}
bool Poly::operator!=(Poly& p2) {
	return (!((*this) == p2));
}
Poly Poly::operator+(Poly& p2) {
	Poly p3;
	if (degree == p2.degree) {
		for (int i = 0; i < degree; i++) {
			p3.coef[i] = coef[i] + p2.coef[i];
		}
		return (p3);
	}
	if (degree != p2.degree) {

		p3.degree = degree > p2.degree ? degree : p2.degree;
		for (int j = 0; j < (p3.degree)+1; j++) {
			p3.coef[j] = 0;
		}
		for (int k = 0; k < (degree)+1; k++) {
			p3.coef[k] = coef[k];
		}
		for (int l = 0; l < (p2.degree)+1; l++) {
			p3.coef[l] += p2.coef[l];
		}
		return (p3);
	}
}
Poly Poly::operator*(Poly& p2) {
	Poly p3;

	p3.degree = degree + p2.degree;
	for (int j = 0; j < (p3.degree) + 1; j++) {
		p3.coef[j] = 0;
	}
	for (int k = degree; k >= 0 ; k--) {
		for (int l = p2.degree; l >= 0; l--) {
			p3.coef[k + l] += coef[k] * p2.coef[l];
		}
	}

	return (p3);


}
int Poly::operator[](int index) const {
	if (index >= 0 && index <= degree) {
		return (coef[index]);
	}
	else {
		cout << "invalid parmeter buddy we show you first index instead: ";
		return (coef[0]);

	}
}
int& Poly::operator[](int index) {
	if (index >= 0 && index <= degree) {
		return (coef[index]);
	}
	else {
		cout << "invalid parmeter buddy we show you first index instead: ";
		return (coef[0]);

	}
}


int main() {
	//scan first polynomail's degree & coefs
	int degree1;
	//cout << "please enter the greatest degree of the first polynomial: ";
	cin >> degree1;
	Poly p1(degree1);
	p1.set();

	//scan second polynomail's degree & coefs
	int degree2;
	//cout << "please enter the greatest degree of the second polynomial: ";
	cin >> degree2;
	Poly p2(degree2);
	p2.set();


	int index1, index2, coef;
	//cout << "please enter an index to show you its Coefficient: ";
	cin >> index1;

	//cout << "please enter an index and coefficient that you want to change." << endl;
	//cout << "index: ";
	cin >> index2;
	//cout << "coef: ";
	cin >> coef;
	p1[index2] = coef;

	//print the polynomails
	//cout << "the first polynomail is: ";
	p1.print();
	cout << endl;

	//cout << "the second polynomail is: ";
	p2.print();
	cout << endl;
	//print the coef based on index that the user enterd!
	cout/* << "coef[" << index1 << "] is: "*/ << p1[index1] << endl;
	Poly p3 = p1 + p2;
	p3.print();
	cout << endl;
	p3 = p1 * p2;
	p3.print();
	cout << endl;
	if (p1 == p2) {
		cout << "yes" << endl;
	}
	else {
		cout << "no" << endl;
	}
	if (p1 != p2) {
		cout << "yes" << endl;
	}
	else {
		cout << "no" << endl;
	}
}
