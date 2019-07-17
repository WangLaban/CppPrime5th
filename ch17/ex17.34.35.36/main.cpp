#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	cout << unitbuf;  //17.34
	cout << boolalpha << (5 < 4 ? true : false) << noboolalpha << endl;
	cout << showpos << showbase << hex << 1024 << " " << oct << 1024
		<< " " << dec << 1024 << noshowbase << noshowpos << endl;
	cout << uppercase << showbase << 3.14159 << " " << hex << 1024 << dec
		<< noshowbase << nouppercase << endl;
	cout << setfill('#') << setw(10) << internal << showpos << 1024
		<< noshowpos << nounitbuf << ends << endl << flush;
	cout << setw(12) << left <<fixed<< 3.14 << " " << right
		<<scientific<< 3.14 << endl;
	cout << hexfloat << 3.14159 << endl;
	cout << setprecision(3) << 3.14159 << setprecision(6) << endl;
	cout << setbase(8) << 1024 << endl;
	char ch;
	cin >> noskipws;
	while (cin >> ch&&ch != 'q')
		cout << ch;
	cin >> skipws;
	cout << endl;

	cout << uppercase;  //17.35
	cout << "default format: " << 100 * sqrt(2.0) << '\n'
		<< "scientific: " << scientific << 100 * sqrt(2.0) << '\n'
		<< "fixed decimal: " << fixed << 100 * sqrt(2.0) << '\n'
		<< "hexidecimal: " << hexfloat << 100 * sqrt(2.0) << '\n'
		<< "use defaults: " << defaultfloat << 100 * sqrt(2.0)
		<< endl;
 
	cout << setfill(' ');  //17.36
	cout << left << setw(20) << "default format:" << setw(25) << right << 100 * sqrt(2.0) << '\n'
		<< left << setw(20) << "scientific:" << scientific << setw(25) << right << 100 * sqrt(2.0) << '\n'
		<< left << setw(20) << "fixed decimal:" << setw(25) << fixed << right << 100 * sqrt(2.0) << '\n'
		<< left << setw(20) << "hexidecimal:" << setw(25) << uppercase << hexfloat << right << 100 * sqrt(2.0) << '\n'
		<< left << setw(20) << "use defaults:" << setw(25) << defaultfloat << right << 100 * sqrt(2.0)
		<< "\n\n";

	return 0;
}
