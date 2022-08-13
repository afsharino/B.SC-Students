#include <iostream>
#include <string>
using namespace std;

class Account {

public:

  //prototypes
  Account(int = 0 , string = "no name" , float = 0 );//default constructor
  //functions to set & get properties as which user wants
  void setAccount(int , string ,float);
  void setID(int);
  void setFamily(string);
  void setBalance(float);
  int getID();
  string getFamily();
  float getBalance();
  //function to print class properties
  void print();
  //functions to handle withdraw &deposit
  void withdraw(float);
  void deposit(float);

private:

  int AccountID;
  string Family;
  float Balance;
};

Account::Account(int i , string f , float b) {

  setAccount(i, f, b);
}

void Account::setAccount(int i , string f , float b) {

  if (b >= 10){

    setID(i);
    setFamily(f);
    setBalance(b);
  }
  else {
    AccountID = 0;
    Family = "no name";
    Balance = 0;
  }
}
void Account::setID(int i) {

  AccountID = i;
}
void Account::setFamily(string f) {

  Family = f;
}
void Account::setBalance(float b) {

  if(b >= 10) {

    Balance = b;
  }

}
int Account::getID() {

  return(AccountID);
}
string Account::getFamily() {

  return(Family);
}
float Account::getBalance() {

  return(Balance);
}
void Account::print() {

  cout << AccountID << endl;
  cout << Family << endl;
  cout << Balance << endl;
}
void Account::withdraw(float w) {

  if ((Balance-w) >= 10) {

    Balance -= w;
  }
}
void Account::deposit(float d) {

  if (d >= 0)  {

    Balance += d;
  }

}
int main() {

  //cout << "please enter AccountID\n";
  int id;
  cin >> id;
  //cout << "please enter Familyname\n";
  string family;
  cin >> family;
  //cout << "please enter Balance\n";
  float balance;
  cin >> balance;
  Account a1(id , family , balance);
  if(balance >= 10) {

    //cout << "please enter deposit" << endl;
    float deposit;
    cin >> deposit;
    a1.deposit(deposit);
    //cout << "please enter withdraw" << endl;
    float withdraw;
    cin >> withdraw;
    a1.withdraw(withdraw);
  }

    a1.print();
}
