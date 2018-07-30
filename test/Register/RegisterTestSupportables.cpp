
#include "RegisterTestSupportables.h"

std::string getNumberedRegisterName()
{
	static int number = 1;

	return ( "TestReg" + std::to_string(number++) );
}
