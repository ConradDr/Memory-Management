/**
 * Dummy program for storing information.
 * Used for testing.
 * 
*/

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#define CHAR_ARRAY_SIZE 128

using namespace std;

int main(){

    //// Initialize vars
    int varInt = 123456;
    string varString = "DefaultString";
    char arrChar[CHAR_ARRAY_SIZE] = "Long char array right there ->";
    int* ptr2int = &varInt;
    int** ptr2ptr = &ptr2int;
    int*** ptr2ptr2 = &ptr2ptr;


    //// Infinite loop, yes this is jank
    for( ; ; ){
        cout << endl;
        cout << "------------------------------------\n";
        cout << endl;
        cout << "Process ID:    " << GetCurrentProcessId() << "\n";
        cout << endl;
        cout << "varInt:         (0x" << hex << uppercase << (uintptr_t)&varInt    << ")     = " << dec << varInt    << endl;
        cout << "varString:      (0x" << hex << uppercase << (uintptr_t)&varString << ")     = " << dec << varString << endl;
        cout << "varChar:        (0x" << hex << uppercase << (uintptr_t)&arrChar   << ")     = " << dec << arrChar   << endl;
        cout << endl;
        cout << "ptr2int         (0x" << hex << uppercase << (uintptr_t)&ptr2int   << ")     = 0x" << dec << ptr2int   << endl;
        cout << "ptr2ptr         (0x" << hex << uppercase << (uintptr_t)&ptr2ptr   << ")     = 0x" << dec << ptr2ptr   << endl;
        cout << "ptr2ptr2        (0x" << hex << uppercase << (uintptr_t)&ptr2ptr2  << ")     = 0x" << dec << ptr2ptr2  << endl;
        cout << endl;
        cout << "Press ENTER to print again.\n";
        cout << endl;
        cout << "------------------------------------\n";

        system("pause > null");
    };

}