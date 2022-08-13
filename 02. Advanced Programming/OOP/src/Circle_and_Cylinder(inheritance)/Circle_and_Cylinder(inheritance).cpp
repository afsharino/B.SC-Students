#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

//********************* Base class *********************

class Circle {

public:

	Circle(double r = 1.0);
	~Circle();
	void setRadius(double);
	double getRadius() { return (radius); }
	double Area();
	double Pier();
	void print();

private:

	double radius;
};

Circle::Circle(double r ) {

	cout << "Circle constructor is called!" << endl;

	setRadius(r);

}
Circle::~Circle() {

	cout << "Circle destructor is called!" << endl;

}
void Circle::setRadius(double r) {

	if (r >= 0) {

		radius = r;

	}
	else {

		cout << "invalid parameter, try again buddy!" << endl;

	}

}
double Circle::Area() {

	double area = ( M_PI * (radius * radius) );
	return (area);

}
double Circle::Pier() {

	double pier = M_PI * (2 * radius);
	return(pier);

}
void Circle::print() {

	cout << "Radius is: " << radius << endl;

}

//********************* Derived class *********************

class Cylinder : public Circle {

	friend ostream& operator<<(ostream&, Cylinder&);
	friend istream& operator>>(istream&, Cylinder&);

public:

	Cylinder(double = 1.0, double = 1.0);
	~Cylinder();
	double getHeight() { return (height); }
	double Area();
	double volume();

private:

	double height;
};

Cylinder::Cylinder(double r, double h) : Circle(r) {

	cout << "Cylinder constructor is called!" << endl;

	if (h >= 0) {

		height = h;

	}
	else {

		cout << "invalid parameter, try again buddy!" << endl;
	}

}

Cylinder::~Cylinder() {

	cout << "Cylinder destructor is called!" << endl;

}
double Cylinder::Area() {

	//#1st way: formula: (( pi * (2 * radius) ) * height) + ( 2 * pi * r^2) .
	double r = getRadius();
	double sideArea = M_PI * (2 * r) * height;
	double headsArea = M_PI * 2 * (r * r);
	double area = sideArea + headsArea;
	return (area);

	/*#2nd way: formula: (Pier * height) + (2 * Area).
	sideArea = Pier() * height;
	headsArea = Circle::Area() * 2;
	area = sideArea + headsArea;
	return (area);*/

}
double Cylinder::volume() {

	//#1st way: formula: ( pi * (radius * radius) ) * height.
	double r = getRadius();
	double volume = M_PI * (r * r) * height;
	return(volume);

	/*#2nd way: formula: Area() * height.
	volume = Circle::Area() * height;
	return (volume);*/
}
ostream& operator<<(ostream& out, Cylinder& c1) {

	out << "radius of cylinder is: " << c1.getRadius() << endl;
	out << "height of cylinder is: " << c1.height << endl;
	return (out);

}
istream& operator>>(istream& in, Cylinder& c1) {

	double r, h;
	cout << "please enter radius of cylinder: ";
	in >> r;
	c1.setRadius(r);
	cout << "please enter height of cylinder: ";
	in >> c1.height;
	return(in);

}


int main() {

	Circle cir;
	Cylinder cyl;
	double radiuss;

	cout << "please enter radius of circle: ";
	cin >> radiuss;
	cir.setRadius(radiuss);

	cin >> cyl;
	cout << cyl;

	cout << "the area of circle is: " << cir.Area() << endl;
	cout << "the volume of cylinder is: " << cyl.volume() << endl;



	Circle* ptrcir = &cir;
	Cylinder* ptrcyl = &cyl;


	cout << "the area of circle is: " << ptrcir->Area() << endl;
	cout << "the volume of cylinder is: " << ptrcyl->volume() << endl;
}