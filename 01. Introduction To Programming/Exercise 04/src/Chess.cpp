#include <iostream>
using namespace std;

int rows , columns , x , y;

int main() {
	
	//scan entries
	cin >> rows;
	cin >> columns;
	cin >> x;
	cin >> y;
	//declare 2dimensional dynamic array
	int** pArray = new int*[rows];
	for (int i = 0; i < rows; ++i) {

		pArray[i] = new int[columns];
	}
	//pointer to store address of enterd cordinate by the user
	int* ptr = &pArray[x][y];

	if (x > rows || y > columns) {

		cout << "not exist" << endl;
	}
	else {

		cout << ptr << endl;
	}
		
}