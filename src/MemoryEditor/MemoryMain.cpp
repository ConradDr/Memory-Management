/**
 * Main File.
 * 
 * Project for learning windows API and memory manipulation
 * 
*/


#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#define CHAR_ARRAY_SIZE 128

using namespace std;

/**
 * Function
 * Read arrChar from other process
 * 
*/
char* ReadArrCharrMem(){}


/**
 * Function
 * Read String from other process
 * 
*/
string ReadStrMem(HANDLE hProcess){
    string strRead = "";

    // Get Memory Address from user 
    uintptr_t memAddressStr = 0x0; // Store Memory Address
    cout << "String: Mem Address to read (in hex): 0x";
    cin >> hex >> memAddressStr;
    cout << "Reading 0x" << hex << uppercase << memAddressStr << "..." << endl;


    // memory read and error check
    BOOL rpmReturn2 = ReadProcessMemory(hProcess, (LPCVOID)memAddressStr, &strRead, sizeof(strRead), NULL);
    if(rpmReturn2 == FALSE){
        cout << "ReadProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return "NULL";
    }

    return strRead;
}


/**
 * Function
 * Read Pointer from other process
 * 
*/
// Read Pointer Func
int ReadPtrMem(HANDLE hProcess){
    int ptrRead = 0;

    // Get Memory Address from user 
    uintptr_t memAddressPtr = 0x0; // Store Memory Address
    cout << "ptr: Mem Address to read (in hex): 0x";
    cin >> hex >> memAddressPtr;
    cout << "Reading 0x" << hex << uppercase << memAddressPtr << "..." << endl;



    // memory read and error check
    BOOL rpmReturn2 = ReadProcessMemory(hProcess, (LPCVOID)memAddressPtr, &ptrRead, sizeof(ptrRead), NULL);
    if(rpmReturn2 == FALSE){
        cout << "ReadProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }

    return ptrRead;
}



/**
 * Function
 * Read Integer from other process
 * 
*/
// Read Integer Func
int ReadIntMem(HANDLE hProcess){
    int intRead = 0; // Store contents of int from other process

    // Get Memory Address from user 
    uintptr_t memAddress = 0x0; // Store Memory Address
    cout << "int: Mem Address to read (in hex): 0x";
    cin >> hex >> memAddress;
    cout << "Reading 0x" << hex << uppercase << memAddress << "..." << endl;



    // memory read and error check
    BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memAddress, &intRead, sizeof(int), NULL);
    if(rpmReturn == FALSE){
        cout << "ReadProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }


    return intRead;
}



/**
 * Function
 * Main Function
 * 
*/
int main(){

    int intRead = 0;
    int ptrRead = 0;
    string strRead = "";

    // Get PID from user input
    DWORD pid = 0; // PID of target
    cout << "PID: ";
    cin >> dec >> pid;

    // Open Process
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pid);
    if(hProcess == NULL){ // Fails to get process
        cout << "OpenProcess Failed. Get last Error = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }


    // Get data type to read
    DWORD toRead = 0;
    cout << "| What type of data do you want to read?  | " << endl;
    cout << "| 1:Int | 2:ptr | 3:String | 4:Char Array | " << endl;
    cin >> dec >> toRead;


    // Read address and display variable
    switch(toRead){
        case 1:
            intRead = ReadIntMem(hProcess);
            cout << "intRead = " << dec << intRead << endl;
            break;
        case 2:
            ptrRead = ReadPtrMem(hProcess);
            cout << "ptrRead = " << hex << ptrRead << endl;
            break;
        case 3:
            strRead = ReadStrMem(hProcess);
            cout << "strRead = " << hex << strRead << endl;
            break;
        case 4:
            //
            //cout << "arrChar = " << hex << arrChar << endl;
            break;
        default:
            return EXIT_FAILURE;

    }

    CloseHandle(hProcess);
    cout << "Press ENTER to quit." << endl;
    system("pause");

    return EXIT_SUCCESS;


}