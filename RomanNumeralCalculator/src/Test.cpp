#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "RomanCalculator.h"

using namespace std;


void AddTwoRomanNumeralsTest() {
	RomanCalculator RmCal;
	ASSERT_EQUAL("IV", RmCal.add("I", "III"));
	ASSERT_EQUAL("XXXI", RmCal.add("XI", "XX"));
	ASSERT_EQUAL("CMXCV", RmCal.add("XM", "VX"));
	ASSERT_EQUAL("MMDCX", RmCal.add("MM", "DCX"));
}

void SubtractTwoRomanNumeralsTest() {
	RomanCalculator RmCal;
	ASSERT_EQUAL("II", RmCal.sub("III", "I"));
	ASSERT_EQUAL("IX", RmCal.sub("XX", "XI"));
	ASSERT_EQUAL("CMLXXXV", RmCal.sub("XM", "VX"));
	ASSERT_EQUAL("MCCCXC", RmCal.sub("MM", "DCX"));
}

void CheckIfLettersAreRomanNumeralTest(){
	RomanCalculator RmCal;
	ASSERT_EQUAL(1, RmCal.Test("IV"));
	ASSERT_EQUAL(1, RmCal.Test("XI"));
	ASSERT_EQUAL(0, RmCal.Test("ABC"));
	ASSERT_EQUAL(0, RmCal.Test("123"));
	ASSERT_EQUAL(0, RmCal.Test("$#%&"));
}

void CheckIfTheResultIsEqualOrLessThanZeroTest(){
	RomanCalculator RmCal;
	ASSERT_EQUAL("Overflow", RmCal.sub("IV", "IV"));
	ASSERT_EQUAL("Overflow", RmCal.sub("I", "III"));
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(AddTwoRomanNumeralsTest));
	s.push_back(CUTE(SubtractTwoRomanNumeralsTest));
	s.push_back(CUTE(CheckIfLettersAreRomanNumeralTest));
	s.push_back(CUTE(CheckIfTheResultIsEqualOrLessThanZeroTest));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
