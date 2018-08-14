/*
 * main.cpp
 *
 *  Created on: 22.07.2018
 *      Author: aaron
 */

#define TESTING

#include "gtest/gtest.h"
#include "Register/RegisterAllocator.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
