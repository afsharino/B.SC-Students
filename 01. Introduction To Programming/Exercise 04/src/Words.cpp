
#include <iostream>
using namespace std;

int length;

int main()
{
	
	//cout << "please enter length of array" << endl;
	cin >> length;
	char* pArray = new char[length];
	for (int i = 0 ; i < length ; i++) {

		cin >> pArray[i];
	}

	cout << "{" << " ";
	for (int i = 0; i < length; i++) {

		if (pArray[i] == 'R' || pArray[i] == 'r' || pArray[i] == 'O' || pArray[i] == 'o' || pArray[i] == 'Y' || pArray[i] == 'y' || pArray[i] == 'A' || pArray[i] == 'a') {
	
			cout << "*" << " ";

		}
		else {

			cout << pArray[i] << " ";
		}

		
	}
	cout << "}";
	delete[] pArray;
	return 0;
}

