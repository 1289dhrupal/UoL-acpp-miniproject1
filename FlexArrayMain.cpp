#include <iostream>
#include "FlexArray.h"
using namespace std;

int _main() {

	FlexArray a;
	a.push_back(1);
	cout << a.print() << endl;
	cout << a.printAll() << endl;
	a.push_front(2);
	cout << a.print() << endl;
	cout << a.printAll() << endl;
	a.insert(1, 3);
	cout << a.print() << endl;
	cout << a.printAll() << endl;
	a.set(1, 99);
	cout << a.get(1) << endl;
	cout << a.print() << endl;
	cout << a.printAll() << endl;
	a.erase(1);
	cout << a.print() << endl;
	cout << a.printAll() << endl;

	cout << "------------------" << endl;

	int arr[]{ 0,1,2,3,4,5,6,7,8,9 };
	FlexArray b{ arr,10 };
	for (int i = 1; i <= 10; i++) {
		if (i % 2 == 0) b.pop_back();
		else b.pop_front();
		cout << b.print() << endl;
		cout << b.printAll() << endl;
	}
	cout << std::boolalpha << b.pop_front() << endl;

	b = a;
	cout << b.print() << endl;
	cout << b.printAll() << endl;
	cout << b.getSize() << endl;
	cout << b.getCapacity() << endl;

	return 0;
}
