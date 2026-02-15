/*
Owner: Uri Naor
Date: Feb, 10 2024
*/

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

/* Changed UL to ULL (Unsigned Long Long) to ensure the compiler treats this as a 64-bit literal on Windows */
#define MAX_UNSIGNED_LONG 18446744073709551615ULL 
#define HEX_TEST 0x4000020004000400

#include <stdio.h> /* printf */
#include <string.h> /* string */
#include "bitarr.h" /* bit_array */

/******************** FORWARD DECLARATIONS ********************/

/* Changed result and expected from long unsigned int to size_t to match bitarr_t */
static void RunTest(const char* test, size_t result, size_t expected);
static void TestBitArrSetAll();
static void TestBitArrResetAll();
static void TestBitArrSetOn();
static void TestBitArrSetOff();
static void TestBitArrSetBit();
static void TestBitArrGetBit();
static void TestBitArrFlipBit();
static void TestBitArrMirror();
static void TestBitArrRotateRight();
static void TestBitArrRotateLeft();
static void TestBitArrCountOn();
static void TestBitArrCountOff();
static void TestBitArrToString();
static void TestBitArrMirrorLut();
static void TestBitArrCountOnLut();

/******************** MAIN ********************/
int main()
{
	TestBitArrSetAll();
    TestBitArrResetAll();
    TestBitArrSetOn();
    TestBitArrSetOff();
    TestBitArrSetBit();
    TestBitArrGetBit();
    TestBitArrFlipBit();
    TestBitArrMirror();
    TestBitArrRotateRight();
    TestBitArrRotateLeft();
    TestBitArrCountOn();
    TestBitArrCountOff();
    TestBitArrToString();
    TestBitArrMirrorLut();
    TestBitArrCountOnLut();
	return 0;
}

/******************** TEST FUNCTIONS ********************/
static void RunTest(const char* test, size_t result, size_t expected)
{
    printf("%s: %s\n", test, result == expected ? PASS : FAIL);
}

static void TestBitArrSetAll()
{   
	printf("\nTest BitArrSetAll:\n");
    RunTest("case 64 bit hex", BitArrSetAll(HEX_TEST), MAX_UNSIGNED_LONG);
    RunTest("case 0", BitArrSetAll(0), MAX_UNSIGNED_LONG);
    RunTest("case 255", BitArrSetAll(255), MAX_UNSIGNED_LONG);
}

static void TestBitArrResetAll()
{   
    printf("\nTest BitArrResetAll:\n");
    RunTest("case 64 bit hex", BitArrResetAll(HEX_TEST), 0);
    RunTest("case 0", BitArrResetAll(0), 0);
    RunTest("case 255", BitArrResetAll(255), 0);
}

static void TestBitArrSetOn()
{   
    printf("\nTest BitArrSetOn:\n");
    /* Added ULL suffix to large constants below to prevent 32-bit truncation */
    RunTest("case 64 bit hex index 2", BitArrSetOn(HEX_TEST, 2), 
    4611688217517753348ULL);
    RunTest("case 64 bit hex index 63", BitArrSetOn(HEX_TEST, 63), 
    13835060254372529152ULL);
    RunTest("case 72 index 2", BitArrSetOn(72, 2), 76);
    RunTest("case 0 index 3", BitArrSetOn(0, 3), 8);
    RunTest("case 128 index 7", BitArrSetOn(128, 7), 128);
    RunTest("case 0 index 0", BitArrSetOn(0, 0), 1);
    RunTest("case 255 index 0", BitArrSetOn(255, 0), 255);
}

static void TestBitArrSetOff()
{   
    printf("\nTest BitArrSetOff:\n");
    RunTest("case 64 bit hex index 10", BitArrSetOff(HEX_TEST, 10), 
    4611688217517752320ULL);
    RunTest("case 64 bit hex index 62", BitArrSetOff(HEX_TEST, 62), 
    2199090365440ULL);
    RunTest("case 72 index 0", BitArrSetOff(72, 0), 72);
    RunTest("case 0 index 3", BitArrSetOff(0, 3), 0);
    RunTest("case 255 index 7", BitArrSetOff(255, 7), 127);
    RunTest("case 8 index 3", BitArrSetOff(8, 3), 0);
    RunTest("case 0 index 0", BitArrSetOff(0, 0), 0);
}

static void TestBitArrSetBit()
{   
    printf("\nTest BitArrSetBit:\n");
    RunTest("case 64 bit hex index 2", BitArrSetBit(HEX_TEST, 2, 1), 
    4611688217517753348ULL);
    RunTest("case 64 bit hex index 63", BitArrSetBit(HEX_TEST, 63, 1), 
    13835060254372529152ULL);
    RunTest("case 72 index 0", BitArrSetBit(72, 0, 1), 73);
    RunTest("case 0 index 3", BitArrSetBit(0, 3, 1), 8);
    RunTest("case 8 index 3", BitArrSetBit(8, 3, 0), 0);
    RunTest("case 0 index 0", BitArrSetBit(0, 0, 1), 1);
}

static void TestBitArrGetBit()
{   
    printf("\nTest BitArrGetBit:\n");
    RunTest("case 64 bit hex index 2", BitArrGetBit(HEX_TEST, 2), 0);
    RunTest("case 64 bit hex index 62", BitArrGetBit(HEX_TEST, 62), 1);
}

static void TestBitArrFlipBit()
{   
    printf("\nTest BitArrFlipBit:\n");
    RunTest("case 64 bit hex index 2", BitArrFlipBit(HEX_TEST, 2), 
    4611688217517753348ULL);
    RunTest("case 64 bit hex index 62", BitArrFlipBit(HEX_TEST, 62),
    2199090365440ULL);
    RunTest("case 72 index 0", BitArrFlipBit(72, 0), 73);
    RunTest("case 0 index 3", BitArrFlipBit(0, 3), 8);
    RunTest("case 8 index 3", BitArrFlipBit(8, 3), 0);
    RunTest("case 0 index 0", BitArrFlipBit(0, 0), 1);
}


static void TestBitArrMirror()
{   
    printf("\nTest BitArrMirror:\n");
    RunTest("case 64 bit hex", BitArrMirror(HEX_TEST), 9007336697888770ULL);
}

static void TestBitArrRotateRight()
{
    printf("\nTest BitArrRotateRight:\n");
    RunTest("case 64 bit hex 2 moves", BitArrRotateRight(HEX_TEST, 2), 
    1152922054379438336ULL);
   	RunTest("case 64 bit hex 42 moves", BitArrRotateRight(HEX_TEST, 42), 
   	9223653516127502336ULL);
}

static void TestBitArrRotateLeft()
{
    printf("\nTest BitArrRotateLeft:\n");
    RunTest("case 64 bit hex 2 moves", BitArrRotateLeft(HEX_TEST, 2), 
    8796361461761ULL);
    RunTest("case 64 bit hex 42 moves", BitArrRotateLeft(HEX_TEST, 42), 
    4504699139522576ULL);
}

static void TestBitArrCountOn()
{   
    printf("\nTest BitArrCountOn:\n");
    RunTest("case 64 bit hex", BitArrCountOn(HEX_TEST), 4);
}

static void TestBitArrCountOff()
{   
    printf("\nTest BitArrCountOff:\n");
    RunTest("case 64 bit hex", BitArrCountOff(HEX_TEST), 60);
}

static void TestBitArrToString()
{   
    char str[66];
    printf("\nTest BitArrToString:\n");

    BitArrToString(HEX_TEST , str);
    RunTest("case 64 bit hex", strcmp(str, 
   "0100000000000000000000100000000000000100000000000000010000000000") == 0, 1);
}

static void TestBitArrMirrorLut()
{   
    printf("\nTest BitArrMirrorLut:\n");
    RunTest("case 64 bit hex", BitArrMirrorLut(HEX_TEST), 9007336697888770ULL);
}


static void TestBitArrCountOnLut()
{   
    printf("\nTest BitArrCountOnLut:\n");
    RunTest("case 64 bit hex", BitArrCountOnLut(HEX_TEST), 4);
}
