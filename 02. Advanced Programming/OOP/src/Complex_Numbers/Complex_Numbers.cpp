#include <iostream>
#include <math.h>
using namespace std;

//class of complex numbers
class Complex {
public:
	//prototypes
	Complex(double = 12, double = 12);//default constructor
	~Complex();//destructor
	void setComplex(double, double);//function to set values
	void Convert();//function to convert complex number to polar form
	Complex AddComplex(Complex);//function to add two complex numbers with each other
	Complex SubComplex(Complex);//function to subtract two complex numbers with each other
	Complex MulComplex(Complex);//function to multiply two complex numbers with each other
	Complex DivComplex(Complex);//function to divide two complex numbers to each other
	void printCartesian();//function to display complex numbers in cartesian form
	void printPolar();//function to display complex numbers in polar form

private:
	//class properties
	double RealPart;
	double ImagPart;
	double r;
	double theta;
};

Complex::Complex(double r, double i) {
	setComplex(r, i);
}
Complex::~Complex() {
}
void Complex::setComplex(double r, double i) {
	RealPart = r;
	ImagPart = i;
}
void Complex::Convert() {
	r = sqrt(pow(RealPart, 2) + pow(ImagPart, 2));
	theta = atan(ImagPart / RealPart);
}
Complex Complex::AddComplex( Complex c2) {
	Complex c3;
	c3.RealPart = RealPart + c2.RealPart;
	c3.ImagPart = ImagPart + c2.ImagPart;
	return c3;
}
Complex Complex::SubComplex(Complex c2) {
	Complex c3;
	c3.RealPart = RealPart - c2.RealPart;
	c3.ImagPart = ImagPart - c2.ImagPart;
	return c3;
}
Complex Complex::MulComplex(Complex c2) {
	//(a + bi)(c + di) = (ac – bd) + (ad + bc)i
	//The solution is copied from Faradars.org
	Complex c3;
	c3.RealPart = ((RealPart) * (c2.RealPart) - (ImagPart) * (c2.ImagPart));
	c3.ImagPart = ((RealPart) * (c2.ImagPart) + (ImagPart) * (c2.RealPart));
	return c3;
}
Complex Complex::DivComplex(Complex c2) {
	/*(a + bi)/(c + di) = ( (ac – bd) + (ad + bc)i ) / (c^2 + d^2)
	The solution is obtained from Faradars.org
	the following code is use cartesian form
	RealPart = ( (c1.RealPart) * (c2.RealPart) - (c1.ImagPart) * (c2.ImagPart) ) / ( pow(c2.RealPart , 2) , pow(c2.ImagPart , 2) );
	ImagPart = ( (c1.RealPart) * (c2.ImagPart) + (c1.ImagPart) * (c2.RealPart) ) / ( pow(c2.RealPart , 2) , pow(c2.ImagPart , 2) );*/
	/*******************************************************************************************************************************/
	//the following code is use polar form
	Complex c3;
	Convert();
	c2.Convert();
	c3.r = r / c2.r;
	c3.theta = (theta) - (c2.theta);
	return c3;
}
void Complex::printCartesian() {
	//cout << "the complex number in the form of cartesian" << endl;
	if (RealPart == 0) {
		cout << ImagPart << "i" << endl;

	}
	if (ImagPart == 0) {
		cout << ImagPart << "i" << endl;
	}
	if (RealPart != 0 && ImagPart != 0) {
		cout << RealPart << " + " << ImagPart << "i" << endl;
	}
}
void Complex::printPolar() {
	//cout << "the complex number in polar form" << endl;
	cout << r << " * " << "e^" << "(i * " << theta << ")" << endl;

}


int main() {
	//cout << "please enter real & imaginary numbers for first coplex number" << endl;
	double real1;
	cin >> real1;
	double imag1;
	cin >> imag1;
	//cout << "please enter real & imaginary numbers for second coplex number" << endl;
	double real2;
	cin >> real2;
	double imag2;
	cin >> imag2;
	//declare objects
	Complex c1(real1, imag1);
	Complex c2(real2, imag2);
	Complex c3;

	c3 = c1.AddComplex(c2);
	c3.printCartesian();
	c3 = c1.SubComplex(c2);
	c3.printCartesian();
	c3 = c1.MulComplex(c2);
	c3.printCartesian();
	c3 = c1.DivComplex(c2);
	c3.printPolar();
}
