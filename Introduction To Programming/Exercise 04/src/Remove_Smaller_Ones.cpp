#include <iostream>
using namespace std;

int length, temp , Final;

int main() {

	//cout << "please enter length of array" << endl;
	cin >> length;
	int* pArray = new int[length];//dynamic array
	for (int i = 0; i < length; i++) {

		cin >> pArray[i];
	}
	//bubble sort
	for (int i = 0; i < length; i++) {

		for (int j = i + 1; j < length - i - 1; j++) {

			if (pArray[j] > pArray[j + 1]) {

				temp = pArray[j];
				pArray[j] = pArray[j + 1];
				pArray[j + 1] = temp;
			}
		}
	}
	//print the biggest number
	Final = pArray[length - 1];
	cout << Final << endl;
	delete[] pArray;//delete array
	return 0;
}