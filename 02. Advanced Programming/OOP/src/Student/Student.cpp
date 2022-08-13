#include <iostream>
#include <cstring>
using namespace std;

class Student {
public:
	//prototypes
	Student(int = 0 , char* =  "No Name" , float = 0 );
	~Student();
	void setStudent(int , char* , float);
	void printStudent();
	float getAverage();
	void gradeAstudents();

private:
    //class properties
	int id;
	char family[20];
	float average;
};

Student::Student(int i , char* f , float a) {
    setStudent(i , f , a);
}

Student::~Student() {

	cout << "distructor is called" << endl;
}
void Student::setStudent(int i, char* f, float a) {
	if (i >= 0) {
		if (0 <= a && a <= 20) {
			id = i;
			strcpy(family , f);
			average = a;
		}
	}
}
void Student::printStudent() {
	cout << id << endl;
	cout << family << endl;
	cout << average << endl;
}
float Student::getAverage() {
	return average;
}
void Student::gradeAstudents() {
	cout << id << endl;
	cout << family << endl;
}

const int mySize=10;
int main()
{
	int studentsNumber;
	//cout << "please enter number of the students" << endl;
	cin >> studentsNumber;
    //dynamic array of class
	Student* studentArray = new Student[studentsNumber];
	//entries that user should input
	int Id;
	char* Family = new char[20];
	float Average;
	for (int i = 0 ; i < studentsNumber ; i++) {

		//cout << "please enter student's id" << endl;
		cin >> Id;
		//cout << "please enter student's Family name" << endl;
		cin >> Family;
		//cout << "please enter student's average" << endl;
		cin >> Average;
		studentArray[i].setStudent(Id, Family, Average);
	}
    //print grad A students
	for (int i = 0; i < studentsNumber; i++) {
		if (studentArray[i].getAverage() > 17) {

			studentArray[i].gradeAstudents();
		}
	}
}