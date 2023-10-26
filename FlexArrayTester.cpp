#include <iostream>
#include "FlexArrayTester.h"
#include "FlexArray.h"

using namespace std;

FlexArrayTester::FlexArrayTester() : error_(false), funcname_("") {}

// def ctor
void FlexArrayTester::testa() {
	funcname_ = "FlexArrayTester::testa";
	{

		FlexArray a;
		if (a.getSize() != 0)
			errorOut_("def ctor wrong size: ", a.getSize(), 1);
		if (a.getCapacity() != FlexArray::INITIALCAP)
			errorOut_("def ctor wrong cap: ", a.getCapacity(), 2);

	}
	passOut_();
}

// param ctor
// also in case anyone used 0 or -1 to mark boundaries...
void FlexArrayTester::testb() {
	funcname_ = "FlexArrayTester::testb";
	{

		int arr[10] = { 0,1,2,3,4,5,6,7,8,-1 };
		FlexArray a(arr, 10);
		if (a.getSize() != 10)
			errorOut_("param ctor wrong size: ", a.getSize(), 1);
		if (a.getCapacity() != 30)
			errorOut_("param ctor wrong cap: ", a.getCapacity(), 2);

	}
	passOut_();
}

// get/set (from param ctor only)
void FlexArrayTester::testc() {
	funcname_ = "FlexArrayTester::testc";
	{

		int arr[]{ 0,1,2,3,4,3,2,1,0,-1 };
		FlexArray a{ arr,10 };
		int v;
		for (int i = 0; i < 10; i++) {
			v = a.get(i);
			if (v != arr[i])
				errorOut_("get wrong at i=" + std::to_string(i) + ": ", v, 1);
		}

		for (int i = 0; i < 10; i++)
			a.set(i, 10 * arr[i]);
		for (int i = 0; i < 10; i++) {
			v = a.get(i);
			if (v != 10 * arr[i])
				errorOut_("set wrong at i=" + std::to_string(i) + ": ", v, 2);
		}

	}
	passOut_();
}

// set ret val
void FlexArrayTester::testd() {
	funcname_ = "FlexArrayTester::testd";
	{

		int arr[]{ 1,2,3,4,5,6,7,8,9 };
		FlexArray a{ arr,9 };
		bool b;
		for (int i = 0; i < 9; i++) {
			b = a.set(i, 10 * arr[i]);
			if (!b) errorOut_("set returned false when in bounds", 1);
		}
		b = a.set(-1, 0);
		if (b) errorOut_("set returned true when out of bounds -1", 2);
		b = a.set(10, 0);
		if (b) errorOut_("set returned true when out of bounds 10", 2);

		// empty so even 0 is out of bounds
		FlexArray e;
		b = e.set(0, 0);
		if (b) errorOut_("set returned true when out of bounds 0", 2);

	}
	passOut_();
}

// print (from ctor only)
void FlexArrayTester::teste() {
	funcname_ = "FlexArrayTester::teste";
	{

		FlexArray a;
		string s = a.print();
		if (s != "[]")
			errorOut_("print empty FlexArray wrong: ", s, 1);

		int arr[]{ 1,2,-3,40,500,-60,7099 };
		FlexArray b{ arr,7 };
		s = b.print();
		if (s != "[1, 2, -3, 40, 500, -60, 7099]")
			errorOut_("print FlexArray b wrong: ", s, 2);

	}
	passOut_();
}

// printall (from ctor only)
void FlexArrayTester::testf() {
	funcname_ = "FlexArrayTester::testf";
	{

		FlexArray a;
		string s = a.printAll();
		if (s != "[X, X, X, X, X]")
			errorOut_("printall empty FlexArray wrong: ", s, 1);

		int arr[]{ 0,-1,2,3002,-42 };
		FlexArray b{ arr,5 };
		s = b.printAll();
		if (s != "[X, X, X, X, X, 0, -1, 2, 3002, -42, X, X, X, X, X]")
			errorOut_("printall FlexArray b wrong: ", s, 2);

	}
	passOut_();
}

// pushback
void FlexArrayTester::testg() {
	funcname_ = "FlexArrayTester::testg";
	{

		// def ctor
		FlexArray a;
		for (int i = 0; i < 3; i++) {
			a.push_back(i);
			if (a.getSize() != i + 1)
				errorOut_("Push_back wrong size at i=" + std::to_string(i) + ": ", a.getSize(), 1);
		}
		for (int i = 0; i < 3; i++) {
			if (a.get(i) != i)
				errorOut_("Push_back wrong value at i=" + std::to_string(i) + ": ", a.get(i), 2);
		}

		// need printall to check if using tailroom correctly
		string s = a.printAll();
		if (s != "[X, X, 0, 1, 2]")
			errorOut_("push_back printall wrong: ", s, 2);

	}
	passOut_();
}

// pushfront
void FlexArrayTester::testh() {
	funcname_ = "FlexArrayTester::testh";
	{

		// param ctor this time
		int arr[]{ 1,2,3,4,5,11,12,13 };
		FlexArray a{ arr,5 };
		for (int i = 0; i < 3; i++) {
			a.push_front(arr[i + 5]);
			if (a.getSize() != i + 6)
				errorOut_("Push_front wrong size at i=" + std::to_string(i) + ": ", a.getSize(), 1);
		}
		for (int i = 0; i < 3; i++) {
			if (a.get(i) != arr[7 - i])
				errorOut_("Push_front wrong value at i=" + std::to_string(i) + ": ", a.get(i), 2);
		}
		string s = a.printAll();
		if (s != "[X, X, 13, 12, 11, 1, 2, 3, 4, 5, X, X, X, X, X]")
			errorOut_("push_front printall wrong: ", s, 2);

	}
	passOut_();
}

// popback
void FlexArrayTester::testi() {
	funcname_ = "FlexArrayTester::testi";
	{

		int arr[]{ 1,2,3,4,5,6 };
		FlexArray a{ arr,6 };
		bool b;
		for (int i = 0; i < 3; i++) {
			b = a.pop_back();
			if (a.getSize() != 5 - i)
				errorOut_("Pop_back wrong size at i=" + std::to_string(i) + ": ", a.getSize(), 1);
			if (!b) errorOut_("Pop_back returned false when not empty", 2);
		}
		for (int i = 0; i < 3; i++) {
			if (a.get(i) != arr[i])
				errorOut_("Pop_back wrong value at i=" + std::to_string(i) + ": ", a.get(i), 1);
		}
		string s = a.printAll();
		if (s != "[X, X, X, X, X, X, 1, 2, 3, X, X, X, X, X, X, X, X, X]")
			errorOut_("pop_back printall wrong: ", s, 1);

		for (int i = 0; i < 3; i++) a.pop_back(); // now empty
		b = a.pop_back();
		if (b) errorOut_("Pop_back returned true when empty", 2);

	}
	passOut_();
}

// popfront
void FlexArrayTester::testj() {
	funcname_ = "FlexArrayTester::testj";
	{

		int arr[]{ 4,5,6,7,8,9 };
		FlexArray a{ arr,6 };
		bool b;
		for (int i = 0; i < 3; i++) {
			b = a.pop_front();
			if (a.getSize() != 5 - i)
				errorOut_("Pop_front wrong size at i=" + std::to_string(i) + ": ", a.getSize(), 1);
			if (!b) errorOut_("Pop_front returned false when not empty", 2);
		}
		for (int i = 0; i < 3; i++) {
			if (a.get(i) != arr[3 + i])
				errorOut_("Pop_front wrong value at i=" + std::to_string(i) + ": ", a.get(i), 1);
		}
		string s = a.printAll();
		if (s != "[X, X, X, X, X, X, X, X, X, 7, 8, 9, X, X, X, X, X, X]")
			errorOut_("pop_front printall wrong: ", s, 1);

		for (int i = 0; i < 3; i++) a.pop_front(); // now empty
		b = a.pop_front();
		if (b) errorOut_("Pop_front returned true when empty", 2);

	}
	passOut_();

}

// simple insert, check correct side
void FlexArrayTester::testk() {
	funcname_ = "FlexArrayTester::testk";
	{

		// shift right
		int arr[]{ 10,20,30 };
		FlexArray a{ arr,3 };
		a.insert(2, 90);
		if (a.get(0) != 10) errorOut_("a get0 wrong: ", a.get(0), 1);
		if (a.get(1) != 20) errorOut_("a get1 wrong: ", a.get(1), 1);
		if (a.get(2) != 90) errorOut_("a get2 wrong: ", a.get(2), 1);
		if (a.get(3) != 30) errorOut_("a get3 wrong: ", a.get(3), 1);
		if (a.getSize() != 4) errorOut_("a size wrong: ", a.getSize(), 1);
		string s = a.printAll();
		if (s != "[X, X, X, 10, 20, 90, 30, X, X]")
			errorOut_("a printall wrong: ", s, 1);

		// shift left
		FlexArray b{ arr,3 };
		b.insert(1, 90);
		if (b.get(0) != 10) errorOut_("b get0 wrong: ", b.get(0), 2);
		if (b.get(1) != 90) errorOut_("b get1 wrong: ", b.get(1), 2);
		if (b.get(2) != 20) errorOut_("b get2 wrong: ", b.get(2), 2);
		if (b.get(3) != 30) errorOut_("b get3 wrong: ", b.get(3), 2);
		if (b.getSize() != 4) errorOut_("b size wrong: ", b.getSize(), 2);
		s = b.printAll();
		if (s != "[X, X, 10, 90, 20, 30, X, X, X]")
			errorOut_("b printall wrong: ", s, 2);

	}
	passOut_();
}

// simple erase, check correct side
void FlexArrayTester::testl() {
	funcname_ = "FlexArrayTester::testl";
	{

		// shift right
		int arr[]{ 10,20,30,40 };
		FlexArray a{ arr,4 };
		a.erase(2);
		if (a.get(0) != 10) errorOut_("a get0 wrong: ", a.get(0), 1);
		if (a.get(1) != 20) errorOut_("a get1 wrong: ", a.get(1), 1);
		if (a.get(2) != 40) errorOut_("a get2 wrong: ", a.get(2), 1);
		if (a.getSize() != 3) errorOut_("a size wrong: ", a.getSize(), 1);
		string s = a.printAll();
		if (s != "[X, X, X, X, 10, 20, 40, X, X, X, X, X]")
			errorOut_("a printall wrong: ", s, 1);

		// shift left
		FlexArray b{ arr,4 };
		b.erase(1);
		if (b.get(0) != 10) errorOut_("b get0 wrong: ", b.get(0), 2);
		if (b.get(1) != 30) errorOut_("b get1 wrong: ", b.get(1), 2);
		if (b.get(2) != 40) errorOut_("b get2 wrong: ", b.get(2), 2);
		if (b.getSize() != 3) errorOut_("b size wrong: ", b.getSize(), 2);
		s = b.printAll();
		if (s != "[X, X, X, X, X, 10, 30, 40, X, X, X, X]")
			errorOut_("b printall wrong: ", s, 2);

	}
	passOut_();
}

// insert/erase at ends
void FlexArrayTester::testm() {
	funcname_ = "FlexArrayTester::testm";
	{

		int arr[]{ 10,20,30,40 };
		FlexArray a{ arr,3 };

		a.insert(0, 90);
		string s = a.printAll();
		if (s != "[X, X, 90, 10, 20, 30, X, X, X]")
			errorOut_("insert at head wrong: ", s, 1);
		a.insert(4, 100);
		s = a.printAll();
		if (s != "[X, X, 90, 10, 20, 30, 100, X, X]")
			errorOut_("insert at tail wrong: ", s, 1);

		FlexArray b{ arr,4 };
		b.erase(0);
		s = b.printAll();
		if (s != "[X, X, X, X, X, 20, 30, 40, X, X, X, X]")
			errorOut_("erase at head wrong: ", s, 2);
		b.erase(2);
		s = b.printAll();
		if (s != "[X, X, X, X, X, 20, 30, X, X, X, X, X]")
			errorOut_("erase at tail wrong: ", s, 2);

	}
	passOut_();
}

// ins/erase ret val, chk that no changes made
void FlexArrayTester::testn() {
	funcname_ = "FlexArrayTester::testn";
	{

		int arr[]{ 10,20,30 };
		FlexArray a{ arr,3 };
		bool b;
		b = a.insert(3, 80);
		if (!b) errorOut_("insert returned false when in bounds", 1);
		b = a.insert(5, 90);
		if (b) errorOut_("insert returned true when out of bounds 5", 1);
		b = a.insert(-1, 90);
		if (b) errorOut_("insert returned true when out of bounds -1", 1);
		if (a.getSize() != 4) errorOut_("insert wrong size after out of bounds", 1);

		FlexArray a2{ arr,3 };
		b = a2.erase(1);
		if (!b) errorOut_("erase returned false when in bounds", 2);
		b = a2.erase(2);
		if (b) errorOut_("erase returned true when out of bounds 2", 2);
		b = a2.erase(-1);
		if (b) errorOut_("erase returned true when out of bounds -1", 2);
		if (a2.getSize() != 2) errorOut_("erase wrong size after out of bounds", 2);
		a2.erase(0);
		a2.erase(0); // now empty
		b = a2.erase(0);
		if (b) errorOut_("erase returned true when empty", 2);
		if (a2.getSize() != 0) errorOut_("erase wrong size after empty", 2);

	}
	passOut_();
}

// insert shift other side
void FlexArrayTester::testo() {
	funcname_ = "FlexArrayTester::testo";
	{

		// no space in tail
		int arr[]{ 10,20 };
		FlexArray a{ arr,2 };
		a.insert(2, 80);
		a.insert(3, 90); // [X X 10 20 80 90]
		a.insert(3, 99);
		if (a.get(3) != 99)
			errorOut_("a get3 wrong: ", a.get(3), 1);
		if (a.getSize() != 5)
			errorOut_("a size wrong: ", a.getSize(), 1);
		string s = a.printAll();
		if (s != "[X, 10, 20, 80, 99, 90]")
			errorOut_("a printall wrong: ", s, 1);

		// no space in head
		FlexArray b{ arr,2 };
		b.insert(0, 80);
		b.insert(0, 90); // [90 80 10 20 X X]
		b.insert(1, 99);
		if (b.get(1) != 99)
			errorOut_("b get1 wrong: ", b.get(1), 2);
		if (b.getSize() != 5)
			errorOut_("b size wrong: ", b.getSize(), 2);
		s = b.printAll();
		if (s != "[90, 99, 80, 10, 20, X]")
			errorOut_("b printall wrong: ", s, 2);

	}
	passOut_();
}

// insert/erase tie-breaking
void FlexArrayTester::testp() {
	funcname_ = "FlexArrayTester::testp";
	{

		// insert
		int arr[]{ 10,20 };
		FlexArray a{ arr,2 };
		a.insert(1, 90);
		if (a.get(0) != 10) errorOut_("a get0 wrong: ", a.get(0), 1);
		if (a.get(1) != 90) errorOut_("a get1 wrong: ", a.get(1), 1);
		if (a.get(2) != 20) errorOut_("a get2 wrong: ", a.get(2), 1);
		if (a.getSize() != 3) errorOut_("a size wrong: ", a.getSize(), 1);
		string s = a.printAll();
		if (s != "[X, X, 10, 90, 20, X]")
			errorOut_("a printall wrong: ", s, 1);

		// erase
		int arr2[]{ 10,20,30 };
		FlexArray b{ arr2,3 };
		b.erase(1);
		if (b.get(0) != 10) errorOut_("b get0 wrong: ", b.get(1), 2);
		if (b.get(1) != 30) errorOut_("b get1 wrong: ", b.get(1), 2);
		if (b.getSize() != 2) errorOut_("b size wrong: ", b.getSize(), 2);
		s = b.printAll();
		if (s != "[X, X, X, 10, 30, X, X, X, X]")
			errorOut_("b printall wrong: ", s, 2);

	}
	passOut_();
}

// push pop / ins erase re-center after empty
void FlexArrayTester::testq() {
	funcname_ = "FlexArrayTester::testq";
	{

		// initially at center
		FlexArray a;
		a.push_front(1); // also tests head decr issue
		string s = a.printAll();
		if (s != "[X, X, 1, X, X]")
			errorOut_("not initially at center: ", s, 1);

		// after pop
		a.push_back(2);
		a.push_back(3); // [x x 1 2 3]
		a.pop_front();
		a.pop_front(); // [x x x x 3]
		a.pop_front(); // now empty
		a.push_back(4);
		s = a.printAll();
		if (s != "[X, X, 4, X, X]")
			errorOut_("push after empty wrong: ", s, 2);

		// after erase
		int arr[]{ 1,2 };
		FlexArray b{ arr,2 };
		b.insert(2, 3);
		b.insert(3, 4); // [x x 1 2 3 4]
		b.erase(1); // [x x x 1 3 4]
		b.erase(1); // [x x x 1 4 x]
		b.erase(0); // [x x x x 4 x]
		b.erase(0); // now empty
		b.insert(0, 5);
		s = b.printAll();
		if (s != "[X, X, 5, X, X, X]")
			errorOut_("insert after empty wrong: ", s, 2);

	}
	passOut_();
}

// resize after push
void FlexArrayTester::testr() {
	funcname_ = "FlexArrayTester::testr";
	{

		// oppo def/param ctor from case g,h
		// push back
		int arr[]{ 1,2 };
		FlexArray a{ arr,2 };
		a.push_back(3); a.push_back(4);
		string s = a.printAll();
		if (s != "[X, X, 1, 2, 3, 4]")
			errorOut_("a b4 resize wrong: ", s, 1);
		a.push_back(5);
		s = a.printAll();
		if (s != "[X, X, X, X, 1, 2, 3, 4, 5, X, X, X]")
			errorOut_("a after resize wrong: ", s, 1);

		// push front
		FlexArray b;
		b.push_front(1); b.push_front(2); b.push_front(3);
		s = b.printAll();
		if (s != "[3, 2, 1, X, X]")
			errorOut_("b b4 resize wrong: ", s, 2);
		b.push_front(4);
		s = b.printAll();
		if (s != "[X, X, 4, 3, 2, 1, X, X, X]")
			errorOut_("b after resize wrong: ", s, 2);

	}
	passOut_();
}

// resize after insert
// check no resize if oppo end free
void FlexArrayTester::tests() {
	funcname_ = "FlexArrayTester::tests";
	{

		FlexArray a;
		a.insert(0, 1);
		a.insert(1, 2);
		a.insert(1, 3); // [x x 1 3 2]
		a.insert(2, 4); // [x 1 3 4 2]
		a.insert(3, 5); // [1 3 4 5 2]
		string s = a.printAll();
		if (s != "[1, 3, 4, 5, 2]")
			errorOut_("a b4 resize wrong: ", s, 1);
		a.insert(2, 6);
		s = a.printAll();
		if (s != "[X, X, X, X, 1, 3, 6, 4, 5, 2, X, X, X, X, X]")
			errorOut_("a after resize wrong: ", s, 2);

		// opposite end
		int arr[]{ 1,2 };
		FlexArray b{ arr,2 };
		b.insert(0, 3); // [x 3 1 2 x x]
		b.insert(1, 4); // [3 4 1 2 x x]
		b.insert(1, 5); // [3 5 4 1 2 x]
		b.insert(1, 6); // [3 6 5 4 1 2]
		s = b.printAll();
		if (s != "[3, 6, 5, 4, 1, 2]")
			errorOut_("b b4 resize wrong: ", s, 1);
		b.insert(4, 7);
		s = b.printAll();
		if (s != "[X, X, X, X, X, X, 3, 6, 5, 4, 7, 1, 2, X, X, X, X, X]")
			errorOut_("b after resize wrong: ", s, 2);

	}
	passOut_();
}

// resize after pop/erase
void FlexArrayTester::testt() {
	funcname_ = "FlexArrayTester::testt";
	{

		// pops
		int arr[]{ 1,2,3,4,5,6,7,8,9,10 };
		FlexArray a{ arr,10 };
		a.pop_back();
		a.pop_front();
		a.pop_back();
		a.pop_front();
		a.pop_back(); // size 5 cap 30, no resize
		if (a.getCapacity() != 30)
			errorOut_("a wrong cap b4 resize: ", a.getCapacity(), 1);
		a.pop_front(); // size 4 cap 30, should resize
		if (a.getSize() != 4)
			errorOut_("a wrong size: ", a.getSize(), 1);
		if (a.getCapacity() != 12)
			errorOut_("a wrong cap: ", a.getCapacity(), 1);
		string s = a.printAll();
		if (s != "[X, X, X, X, 4, 5, 6, 7, X, X, X, X]")
			errorOut_("a wrong printall: ", s, 1);

		// erase
		FlexArray b{ arr,9 };
		while (b.getSize() > 4) b.erase(0);
		if (b.getCapacity() != 27) // size 4 cap 27, no resize
			errorOut_("b wrong cap b4 resize: ", b.getCapacity(), 2);
		b.erase(0); // size 3 cap 27, should resize
		if (b.getCapacity() != 9)
			errorOut_("b wrong cap after 1st resize: ", b.getCapacity(), 2);
		s = b.printAll();
		if (s != "[X, X, X, 7, 8, 9, X, X, X]")
			errorOut_("b wrong printall after 1st resize: ", s, 2);

		while (b.getSize() > 2) b.erase(0); // size 2 cap 9, no resize
		if (b.getCapacity() != 9)
			errorOut_("b wrong cap b4 2nd resize: ", b.getCapacity(), 2);
		b.erase(0); // size 1 cap 9, should resize
		if (b.getCapacity() != 3)
			errorOut_("b wrong cap after 2nd resize: ", b.getCapacity(), 2);
		s = b.printAll();
		if (s != "[X, 9, X]")
			errorOut_("b wrong printall after 2nd resize: ", s, 2);

		// no resize when become empty
		b.erase(0);
		if (b.getCapacity() != 3)
			errorOut_("b wrong cap after empty: ", b.getCapacity(), 2);

	}
	passOut_();
}

// basic copy con
void FlexArrayTester::testu() {
	funcname_ = "FlexArrayTester::testu";
	{

		int arr[]{ 0,1,2,3,4 };
		FlexArray a{ arr,5 };
		FlexArray b(a);
		if (b.getSize() != 5)
			errorOut_("copy wrong size: ", b.getSize(), 1);
		if (b.getCapacity() != 15)
			errorOut_("copy wrong cap: ", b.getCapacity(), 1);

		// need to check printall since head/tailroom need to be same
		string s = b.printAll();
		if (s != "[X, X, X, X, X, 0, 1, 2, 3, 4, X, X, X, X, X]")
			errorOut_("copy wrong printall: ", s, 1);

		// damaged org?
		if (a.getSize() != 5)
			errorOut_("org wrong size: ", a.getSize(), 2);
		if (a.getCapacity() != 15)
			errorOut_("org wrong cap: ", a.getCapacity(), 2);
		for (int i = 0; i < 5; i++)
			if (a.get(i) != arr[i])
				errorOut_("org wrong value at i=" + std::to_string(i) + ": ", a.get(i), 2);

	}
	passOut_();
}

// basic copy asg
void FlexArrayTester::testv() {
	funcname_ = "FlexArrayTester::testv";
	{

		int arr[]{ 4,3,2,1 };
		FlexArray a{ arr,4 };
		FlexArray b;
		b.push_back(1);
		b = a;
		if (b.getSize() != 4)
			errorOut_("copy wrong size: ", b.getSize(), 1);
		if (b.getCapacity() != 12)
			errorOut_("copy wrong cap: ", b.getCapacity(), 1);
		string s = b.printAll();
		if (s != "[X, X, X, X, 4, 3, 2, 1, X, X, X, X]")
			errorOut_("copy wrong printall: ", s, 1);

		// damaged org?
		if (a.getSize() != 4)
			errorOut_("org wrong size: ", a.getSize(), 2);
		if (a.getCapacity() != 12)
			errorOut_("org wrong cap: ", a.getCapacity(), 2);
		for (int i = 0; i < 4; i++)
			if (a.get(i) != arr[i])
				errorOut_("org wrong value at i=" + std::to_string(i) + ": ", a.get(i), 2);

	}
	passOut_();
}

// sticky copy con/asg
void FlexArrayTester::testw() {
	funcname_ = "FlexArrayTester::testw";
	{

		// copy con
		int arr[]{ 0,1,2,3,4,5,6,7,8,9 };
		FlexArray a{ arr,10 };
		FlexArray b(a);

		// org affect new?
		a.set(4, 40);
		a.push_back(10);
		a.pop_front();
		a.insert(1, 11);
		if (b.getSize() != 10)
			errorOut_("b size wrong: ", a.getSize(), 1);
		for (int i = 0; i < 10; i++)
			if (b.get(i) != arr[i])
				errorOut_("b get wrong at i=" + std::to_string(i) + ": ", b.get(i), 1);

		// new affect org?
		FlexArray c{ arr,10 };
		FlexArray d(c);
		d.set(2, 20);
		d.pop_back();
		d.push_front(10);
		d.erase(7);
		if (c.getSize() != 10)
			errorOut_("c size wrong: ", c.getSize(), 1);
		for (int i = 0; i < 10; i++)
			if (c.get(i) != arr[i])
				errorOut_("c get wrong at i=" + std::to_string(i) + ": ", c.get(i), 1);

		// copy asg
		FlexArray e{ arr,10 };
		FlexArray f{ arr,2 };
		f = e;

		// org affect new?
		e.set(4, 40);
		e.push_back(10);
		e.pop_front();
		e.insert(1, 11);
		if (f.getSize() != 10)
			errorOut_("f size wrong: ", f.getSize(), 2);
		if (f.getCapacity() != 30)
			errorOut_("f cap wrong: ", f.getCapacity(), 2);
		for (int i = 0; i < 10; i++)
			if (f.get(i) != arr[i])
				errorOut_("f get wrong at i=" + std::to_string(i) + ": ", f.get(i), 2);

		// new affect org?
		FlexArray g{ arr,10 };
		FlexArray h;
		h = g;
		h.set(2, 20);
		h.pop_back();
		h.push_front(10);
		h.erase(7);
		if (g.getSize() != 10)
			errorOut_("g size wrong: ", g.getSize(), 2);
		if (g.getCapacity() != 30)
			errorOut_("g cap wrong: ", g.getCapacity(), 2);
		for (int i = 0; i < 10; i++)
			if (g.get(i) != arr[i])
				errorOut_("g get wrong at i=" + std::to_string(i) + ": ", g.get(i), 2);

	}
	passOut_();
}

// self-assign
void FlexArrayTester::testx() {
	funcname_ = "FlexArrayTester::testx";
	{

		FlexArray a;
		a = a;
		if (a.getSize() != 0)
			errorOut_("a wrong size after self-assign: ", a.getSize(), 1);
		if (a.getCapacity() != FlexArray::INITIALCAP)
			errorOut_("a wrong cap after self-assign: ", a.getCapacity(), 1);

		// with some actions b4/after self-asign
		int arr[]{ 0,1,2,3 };
		FlexArray b{ arr,4 };
		b.push_back(10);
		b.push_back(11);
		b = b;
		b.pop_front();
		b.set(0, 99);
		b = b;
		if (b.getSize() != 5)
			errorOut_("b wrong size after self-assign: ", b.getSize(), 2);
		if (b.getCapacity() != 12)
			errorOut_("b wrong cap after self-assign: ", b.getCapacity(), 2);
		if (b.print() != "[99, 2, 3, 10, 11]")
			errorOut_("b wrong print after self-assign: ", b.print(), 2);

	}
	passOut_();
}

// mixed cases:
// insert at edge of arr and at edge of int array;
// resize + copy
void FlexArrayTester::testy() {
	funcname_ = "FlexArrayTester::testy";
	{

		FlexArray a;
		for (int i = 0; i < 10; i++) a.push_back(i);
		if (a.getCapacity() != 18)
			errorOut_("wrong cap after pushback: ", a.getCapacity(), 1);
		// x x x x x x 0 1 2 3 4 5 6 7 8 9 x x

		for (int i = 10; i < 20; i++) a.push_front(i);
		if (a.getCapacity() != 48)
			errorOut_("wrong cap after pushfront: ", a.getCapacity(), 1);
		// x x x x x x x x x x x x 19 18 17 16 15 14 13 12 11 10 0 1 2 3 4 5 6 7 8 9 x x x x x x x x x x x x x x x x

		FlexArray b;
		for (int i = 0; i < 10; i++) b.insert(i, i);
		if (b.getCapacity() != 15)
			errorOut_("wrong cap after insert: ", b.getCapacity(), 1);
		// x x x x x 0 1 2 3 4 5 6 7 8 9

		b = a;

		for (int i = 0; i < 13; i++) b.pop_front();
		if (b.getCapacity() != 48)
			errorOut_("wrong cap after popfront: ", b.getCapacity(), 2);
		// x x x x x x x x x x x x x x x x x x x x x x x x x 3 4 5 6 7 8 9 x x x x x x x x x x x x x x x x

		b.erase(6);
		if (b.getCapacity() != 18)
			errorOut_("wrong cap after erase: ", b.getCapacity(), 2);
		// x x x x x x 3 4 5 6 7 8 x x x x x x

		a = b;

		for (int i = 0; i < 4; i++) a.pop_back();
		if (a.getCapacity() != 6)
			errorOut_("wrong cap after popback: ", a.getCapacity(), 2);
		// x x 3 4 x x

	}
	passOut_();
}

// reserved for new test cases
void FlexArrayTester::testz() {
	funcname_ = "FlexArrayTester::testz";
	{


	}
	passOut_();
}

void FlexArrayTester::errorOut_(const string& errMsg, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << endl;
	error_ |= (1 << errBit);
	cerr << std::flush;
}

void FlexArrayTester::errorOut_(const string& errMsg, const string& errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << errResult << endl;
	error_ |= (1 << errBit);
	cerr << std::flush;
}

void FlexArrayTester::errorOut_(const string& errMsg, int errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << std::to_string(errResult) << endl;
	error_ |= (1 << errBit);
	cerr << std::flush;
}

void FlexArrayTester::passOut_() {

	if (!error_) {
		cerr << funcname_ << ":" << " pass" << endl;
	}
	cerr << std::flush;
}
