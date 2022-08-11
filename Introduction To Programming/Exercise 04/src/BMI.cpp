#include <iostream>
#include <cstdio>
using namespace std;

struct BMI {

	float height;
	float weight;

};
//prototype
float calculateBMI(float , float );
//my vars
float bmi = 0;
float finalBMI;

int main() {

	BMI bmi;
	BMI &bmiRefrence = bmi;//Reference variable
	BMI *bmiPtr = &bmi;//pointer
	//cout << "please enter your height" << endl;
	cin >> (*bmiPtr).height;
	//cout << "please enter your weight" << endl;
	cin >> (*bmiPtr).weight;
	//calling function
	finalBMI = calculateBMI(bmiRefrence.height, bmiRefrence.weight);
	//cout << "your Body Mass index is :" << endl;
	printf("%.2lf", finalBMI);
}
//fuction to calculating BMI
float calculateBMI(float h, float w) {

	bmi = w / (h * h);
	return bmi;
}