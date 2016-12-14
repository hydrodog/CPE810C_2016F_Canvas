#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double num1;
	int num2, num3;
	cout << "Enter the number: " << endl;
	cin >> num1;
	cout << "The integer portion: " << static_cast<int>(num1) << endl;
	num3 = static_cast<int>(num1);
	cout << "The new integer: " << num3 << endl;
	cout << "The number with two decimal: " << setiosflags(ios::fixed | ios::showpoint) << setprecision(2) << num1 << endl;
	num2 = num3 % 2;
	cout << "Odd(1) or even(0): " << num2 << endl;
	cout << "Name: LAN CHANG" << endl;
	return 0;
}