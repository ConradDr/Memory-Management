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
 * Get memory address to access
*/
uintptr_t GetMemAddress(){
    uintptr_t memAddress = 0x0; // Store Memory Address

    cout << "Memory Address to read(in hex): 0x";
    cin >> hex >> memAddress;
    cout << "Reading 0x" << hex << uppercase << memAddress << "..." << endl;

    return memAddress;
}

/**
 * Function
 * Get memory address to access for writing
*/
uintptr_t GetMemAddressWrite(){
    uintptr_t memAddress = 0x0; // Store Memory Address

    cout << "Memory Address to edit(in hex): 0x";
    cin >> hex >> memAddress;

    return memAddress;
}



/**
 * Function
 * Read arrChar from other process
 * 
*/
void ReadCharMem(HANDLE hProcess, uintptr_t memAddress){

    DWORD bufferReadSize;
    char buffer[CHAR_ARRAY_SIZE]{};

    cout << "How many bytes do you want to read?";
    cin >> bufferReadSize;
    cout << "Ready to read " << bufferReadSize << " bytes" << endl;


    // memory read and error check
    BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memAddress, &buffer, bufferReadSize, NULL);
    if(rpmReturn == FALSE){
        cout << "ReadProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
    }
    cout << "char buffer: " << buffer << endl;
}




/**
 * Function
 * Read String from other process
 * 
*/
string ReadStrMem(HANDLE hProcess, uintptr_t memAddressStr){
    string strRead = "";

    // memory read and error check
    BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memAddressStr, &strRead, sizeof(strRead), NULL);
    if(rpmReturn == FALSE){
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
int ReadPtrMem(HANDLE hProcess, uintptr_t memAddressPtr){
    int ptrRead = 0;

    // memory read and error check
    BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memAddressPtr, &ptrRead, sizeof(ptrRead), NULL);
    if(rpmReturn == FALSE){
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
int ReadIntMem(HANDLE hProcess, uintptr_t memAddress){
    int intRead = 0; // Store contents of int from other process

    // memory read and error check
    BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memAddress, &intRead, sizeof(intRead), NULL);
    if(rpmReturn == FALSE){
        cout << "ReadProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }

    return intRead;
}

/**
 * Function
 * Write Integer to other process
 * 
*/
void WriteIntMem(HANDLE hProcess, uintptr_t memAddress){
    int intWrite = 0; // Store contents of int from other process

    cout << "What data do you want to write to buffer? ";
    cin >> dec >> intWrite;

    // memory read and error check
    BOOL wpmReturn = WriteProcessMemory(hProcess, (LPVOID)memAddress, &intWrite, sizeof(intWrite), NULL);
    if(wpmReturn == FALSE){
        cout << "ReadProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return;
    } else {
        cout << "Int Writte Successful" << endl;
    }

    return;
}


/**
 * Function
 * Write pointer to other process
 * 
*/
void WritePtrMem(HANDLE hProcess, uintptr_t memAddress){
    int ptrWrite = 0x0; // Store contents of int from other process

    cout << "What data do you want to write to buffer? 0x0";
    cin >> hex >> ptrWrite;

    // memory read and error check
    BOOL wpmReturn = WriteProcessMemory(hProcess, (LPVOID)memAddress, &ptrWrite, sizeof(ptrWrite), NULL);
    if(wpmReturn == FALSE){
        cout << "ReadProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return;
    } else {
        cout << "Ptr Writte Successful" << endl;
    }

    return;
}

/**
 * Function
 * Write string to other process
 * 
*/
void WriteStrMem(HANDLE hProcess, uintptr_t memAddress){
    string strWrite = ""; // Store contents of int from other process

    cout << "What data do you want to write to buffer? ";
    cin >> strWrite;

    // memory read and error check
    BOOL wpmReturn = WriteProcessMemory(hProcess, (LPVOID)memAddress, &strWrite, sizeof(strWrite), NULL);
    if(wpmReturn == FALSE){
        cout << "ReadProcess failed. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return;
    } else {
        cout << "Str Writte Successful" << endl;
    }

    return;
}





/**
 * Function
 * Main Function
 * 
*/
int main(){

    int intEdit = 0;
    int ptrEdit = 0;
    string strEdit = "";
    char arrChar[CHAR_ARRAY_SIZE] = "";
    int memInteractionType = 0;
    HANDLE hProcess = NULL;

    // Get PID from user input
    DWORD pid = 0; // PID of target
    
    cout << "PID: ";
    cin >> dec >> pid;

    cout << "Do you wish to Read (1) or Write (2)? ";
    cin >> dec >> memInteractionType;


    if(memInteractionType == 1){
        // Open Process
        HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pid);
        if(hProcess == NULL){ // Fails to get process
            cout << "OpenProcess Failed. Get last Error = " << dec << GetLastError() << endl;
            system("pause");
            return EXIT_FAILURE;
        }


        // Get data type to read
        DWORD toRead = 0;
        cout << "|-----------------------------------------| " << endl;
        cout << "| What type of data do you want to read?  | " << endl;
        cout << "| 1:Int | 2:ptr | 3:String | 4:Char Array | " << endl;
        cout << "|-----------------------------------------| " << endl;
        cin >> dec >> toRead;


        // Read address and display variable
        switch(toRead){
            case 1:
                intEdit = ReadIntMem(hProcess, GetMemAddress());
                cout << "intRead = " << dec << intEdit << endl;
                break;
            case 2:
                ptrEdit = ReadPtrMem(hProcess, GetMemAddress());
                cout << "ptrRead = " << hex << ptrEdit << endl;
                break;
            case 3:
                strEdit = ReadStrMem(hProcess, GetMemAddress());
                cout << "strRead = " << hex << strEdit << endl;
                break;
            case 4:
                ReadCharMem(hProcess, GetMemAddress());
                break;
            default:
                return EXIT_FAILURE;
        }

    } else if(memInteractionType == 2){
        // Open Process
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
        //HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
        if(hProcess == NULL){ // Fails to get process
            cout << "OpenProcess Failed. Get last Error = " << dec << GetLastError() << endl;
            system("pause");
            return EXIT_FAILURE;
        }

        // Get data type to read
        DWORD toWrite = 0;
        cout << "|-----------------------------------------| " << endl;
        cout << "| What type of data do you want to write? | " << endl;
        cout << "| 1:Int | 2:ptr | 3:String | 4:Char Array | " << endl;
        cout << "|-----------------------------------------| " << endl;
        cin >> dec >> toWrite;


        // Read address and display variable
        switch(toWrite){
            case 1:
                WriteIntMem(hProcess, GetMemAddressWrite());
                break;
            case 2:
                WritePtrMem(hProcess, GetMemAddressWrite());
                break;
            case 3:// NEED TO FIX
                WriteStrMem(hProcess, GetMemAddressWrite());
                break;
            case 4:// NEED TO FIX
                //WriteCharMem(hProcess, GetMemAddressWrite());
                break;
            default:
                return EXIT_FAILURE;
        }








    }



    


    CloseHandle(hProcess);
    cout << "Press ENTER to quit." << endl;
    system("pause");

    return EXIT_SUCCESS;


}