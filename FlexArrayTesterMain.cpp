#include <iostream>
#include "FlexArrayTester.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
	FlexArrayTester t;
	// t.testa(); t.testb(); t.testc(); t.testd(); t.teste(); t.testf(); t.testg(); t.testh(); t.testi(); t.testj(); t.testk(); t.testl(); t.testm(); t.testn(); 
	t.testo();
	// t.testp(); t.testq(); t.testr(); t.tests(); t.testt(); t.testu(); t.testv(); t.testw(); t.testx(); t.testy(); t.testz();

	for (int i = 1; i < argc; i++) {
		switch (argv[i][0]) {
			case 'a': { FlexArrayTester t; t.testa(); } break;
			case 'b': { FlexArrayTester t; t.testb(); } break;
			case 'c': { FlexArrayTester t; t.testc(); } break;
			case 'd': { FlexArrayTester t; t.testd(); } break;
			case 'e': { FlexArrayTester t; t.teste(); } break;
			case 'f': { FlexArrayTester t; t.testf(); } break;
			case 'g': { FlexArrayTester t; t.testg(); } break;
			case 'h': { FlexArrayTester t; t.testh(); } break;
			case 'i': { FlexArrayTester t; t.testi(); } break;
			case 'j': { FlexArrayTester t; t.testj(); } break;
			case 'k': { FlexArrayTester t; t.testk(); } break;
			case 'l': { FlexArrayTester t; t.testl(); } break;
			case 'm': { FlexArrayTester t; t.testm(); } break;
			case 'n': { FlexArrayTester t; t.testn(); } break;
			case 'o': { FlexArrayTester t; t.testo(); } break;
			case 'p': { FlexArrayTester t; t.testp(); } break;
			case 'q': { FlexArrayTester t; t.testq(); } break;
			case 'r': { FlexArrayTester t; t.testr(); } break;
			case 's': { FlexArrayTester t; t.tests(); } break;
			case 't': { FlexArrayTester t; t.testt(); } break;
			case 'u': { FlexArrayTester t; t.testu(); } break;
			case 'v': { FlexArrayTester t; t.testv(); } break;
			case 'w': { FlexArrayTester t; t.testw(); } break;
			case 'x': { FlexArrayTester t; t.testx(); } break;
			case 'y': { FlexArrayTester t; t.testy(); } break;
			case 'z': { FlexArrayTester t; t.testz(); } break;
			default: { cout << "Options are a -- y." << endl; } break;
		}
	}
	return 0;
}

