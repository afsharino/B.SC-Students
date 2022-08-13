#include <iostream>
#include <cstring>
using namespace std;
const int mySize = 20;


class Course {
public:
	Course(char* = "Advprog", int = 4, float = 19);//default contructor
	~Course();
	void setCourse(char*, int, float);
	int getUnit() { return unit; }
	float getGrade() { return grade; }
	void printCourse();

private:
	char courseName[mySize];
	int unit;
	float grade;

};

Course::Course(char* cN, int u, float g) {
	setCourse(cN, u, g);
}

Course::~Course() {
}

void Course::setCourse(char* cN, int u, float g) {

	if (u > 0 && g <= 20 && g >= 0) {
		strcpy(courseName, cN);
		unit = u;
		grade = g;

	}
}

void Course::printCourse() {
	cout << courseName << ' ';
	cout << unit << ' ';
	cout << grade << endl;

}



class Student {
public:
	Student(int = 1);
	~Student();
	void setStudent(char*, long long int, Course*, int);
	float getAverage();
	void printStudent();

private:
	int coursesnumber;
	char stuName[mySize];
	long long int id;
	Course* courseList;

};

Student::Student(int numOfcourses) {

	if (numOfcourses >= 0) {
		coursesnumber = numOfcourses;
		courseList = new Course[coursesnumber];

	}
	else {
		cout << "invalid parameter we set to default" << endl;
		coursesnumber = mySize;
		courseList = new Course[coursesnumber];

	}
}

Student::~Student() { delete[] courseList; }//destructor to delete dynamic array

void Student::setStudent(char* sN, long long int i, Course* cL, int cn) {

	if (cn >= 0 && i > 0) {
	    if(cn != coursesnumber) {
            coursesnumber = cn;
            delete[] courseList;
            courseList = new Course[cn];
	    }
		strcpy(stuName, sN);
		id = i;

		for (int i = 0; i < coursesnumber; i++) {
			courseList[i] = cL[i];

		}
	}
	else {
        cout << "invalid course number" << endl;
	}
}
float Student::getAverage() {
	float SumOfgrades = 0, average = 0;
	int sumOfunits = 0;
	for (int i = 0; i < coursesnumber; i++) {
		SumOfgrades += (courseList[i].getGrade()) * (courseList[i].getUnit());
	}
	for (int j = 0; j < coursesnumber; j++) {
		sumOfunits += (courseList[j].getUnit());
	}

	average = SumOfgrades / sumOfunits;
	return average;

}
void Student::printStudent() {
	//cout << "student's Name is: ";
	cout << stuName << endl;
	//cout << "student's id is: ";
	cout << id << endl;
	for (int i = 0; i < coursesnumber; i++) {
		courseList[i].printCourse();
	}
	cout << "average = " << getAverage() << endl;
}



int main() {
	char name[mySize];
	//cout << "please Enter student's name: ";
	cin >> name;

	long long int Id;
	//cout << "please Enter student's id: ";
	cin >> Id;

	int number;
	//cout << "please Enter number of courses: ";
	cin >> number;

	Student s1(number);

	char courseName[mySize];
	int Unit;
	float Grade;
	Course* c1 = new Course[number];
	for (int i = 0; i < number; i++) {
		//cout << "please Enter course name: ";
		cin >> courseName;
		//cout << "please Enter unit: ";
		cin >> Unit;
		//cout << "please Enter grade: ";
		cin >> Grade;
		//cout << endl;
		c1[i].setCourse(courseName, Unit, Grade);

	}

	s1.setStudent(name, Id, c1, number);
	s1.printStudent();
}