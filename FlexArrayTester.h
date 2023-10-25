#ifndef FLEXARRAYTESTER_H_
#define FLEXARRAYTESTER_H_

class FlexArrayTester {
public:
	FlexArrayTester();

	// ctor, getsize, getcap
	void testa();
	void testb();

	// get/set
	void testc();
	void testd();

	// print
	void teste();
	void testf();

	// push/pop
	void testg();
	void testh();
	void testi();
	void testj();

	// insert/erase
	void testk();
	void testl();
	void testm();
	void testn();
	void testo();
	void testp();

	void testq();

	// resize
	void testr();
	void tests();
	void testt();

	// copy con, asg
	void testu();
	void testv();
	void testw();
	void testx();

	// mixed
	void testy();

	// unused
	void testz();

private:

	// three overloaded versions
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	void errorOut_(const std::string& errMsg, const std::string& errRes, unsigned int errBit);
	void errorOut_(const std::string& errMsg, int errRes, unsigned int errBit);
	void passOut_();

	char error_;
	std::string funcname_;
};

#endif /* FLEXARRAYTESTER_H_ */
