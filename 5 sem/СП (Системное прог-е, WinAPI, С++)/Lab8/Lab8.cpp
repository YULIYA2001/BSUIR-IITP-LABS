#include "Lab8.h"

#define MAX_BUFF 1000

void getProcArchit(char** buffer, WORD procArchit);
void getSysVersion(char** buffer, OSVERSIONINFOEXW osInfo);



void main()
{
    int len = MAX_BUFF;
    char* buffer;

    printf("\tHardware Configuration:\n\t-----------------------\n");
    // void GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
    SYSTEM_INFO sysInf;
    ZeroMemory(&sysInf, sizeof(SYSTEM_INFO));
    GetSystemInfo((LPSYSTEM_INFO)&sysInf);
    
    getProcArchit(&buffer, sysInf.wProcessorArchitecture);
    printf("Processor architecture: %s\n", buffer);
    printf("Page size: %d\n", sysInf.dwPageSize);
    printf("Number of processors: %d\n", sysInf.dwNumberOfProcessors);

    // int GetKeyboardType(int nTypeFlag);
    switch (GetKeyboardType(0))
    {
    case 4:
        buffer = (char*)"Enhanced 101 - or 102 - key keyboards(and compatibles)";
        break;
    case 7:
        buffer = (char*)"Japanese Keyboard";
        break;
    case 8:
        buffer = (char*)"Korean Keyboard";
        break;
    case 51:
        buffer = (char*)"Unknown type or HID keyboard";
        break;
    }
    printf("Keyboard type: %s\n", buffer);
    printf("Number of function keys: %d\n", GetKeyboardType(2));

    printf("\n\t Operating System Configuration:\n\t---------------------------------\n");
    buffer = (char*)malloc(len + 1);
    // BOOL GetComputerNameA(LPSTR lpBuffer, LPDWORD nSize);
    if (GetComputerNameA(buffer, (LPDWORD)&len) == 0)
        printf("GetComputerName error: %d\n", GetLastError());
    else
        printf("Computer name: %s\n", buffer);

    // BOOL GetUserNameA(LPSTR   lpBuffer, LPDWORD pcbBuffer);
    if (GetUserNameA(buffer, (LPDWORD)&len) == 0)
        printf("GetUserName error: %d\n", GetLastError());
    else
        printf("User name: %s\n", buffer);
    free(buffer);

    
    NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);
    OSVERSIONINFOEXW osInfo;
    *(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");
    if (NULL != RtlGetVersion)
    {
        osInfo.dwOSVersionInfoSize = sizeof(osInfo);
        RtlGetVersion(&osInfo);
        getSysVersion(&buffer, osInfo);
    }
    printf("Major version: %d\n", osInfo.dwMajorVersion);
    printf("Minor version: %d\n", osInfo.dwMinorVersion);
    printf("Build number of the operating system: %d\n", osInfo.dwMinorVersion);
    printf("System version: %s\n", buffer);
    
    // GetWindowsDirectoryA(LPSTR lpBuffer, UINT uSize);
    buffer = (char*)malloc(MAX_PATH + 1);
    len = GetWindowsDirectoryA(buffer, MAX_PATH+1);
    if (len == 0)
        printf("GetWindowsDirectory error: %d\n", GetLastError());
    else
    {
        printf("Windows directory: %s\n", buffer);
    }

    // UINT GetSystemDirectoryA(LPSTR lpBuffer, UINT uSize);
    len = GetSystemDirectoryA(buffer, MAX_PATH + 1);
    if (len == 0)
        printf("GetSystemDirectory error: %d\n", GetLastError());
    else
    {
        printf("System directory: %s\n", buffer);
    }
    free(buffer);
}



void getSysVersion(char** buffer, OSVERSIONINFOEXW osInfo)
{
    int minor = osInfo.dwMinorVersion;
    int major = osInfo.dwMajorVersion;
    int prodType = osInfo.wProductType;

    if (major == 10 && minor == 0 )
    {
        if (prodType == VER_NT_WORKSTATION)
            *buffer = (char*)"Windows 10";
        else
            *buffer = (char*)"Windows Server 2016 or 2019";
    }
    else if (major == 6 && minor == 3)
    {
        if (prodType == VER_NT_WORKSTATION)
            *buffer = (char*)"Windows 8.1";
        else
            *buffer = (char*)"Windows Server 2012 R2";
    }
    else if (major == 6 && minor == 2)
    {
        if (prodType == VER_NT_WORKSTATION)
            *buffer = (char*)"Windows 8";
        else
            *buffer = (char*)"Windows Server 2012";
    }
    else if (major == 6 && minor == 1)
    {
        if (prodType == VER_NT_WORKSTATION)
            *buffer = (char*)"Windows 7";
        else
            *buffer = (char*)"Windows Server 2008 R2";
    }
    else if (major == 6 && minor == 0)
    {
        if (prodType == VER_NT_WORKSTATION)
            *buffer = (char*)"Windows Vista";
        else
            *buffer = (char*)"Windows Server 2008";
    }
    else if (major == 5 && minor == 2)
    {
        if (prodType == VER_NT_WORKSTATION)
            *buffer = (char*)"Windows XP Professional x64 Editio";
        else if (prodType == VER_SUITE_WH_SERVER)
            *buffer = (char*)"Windows Home Server";
        else
            *buffer = (char*)"Windows Server 2003";
    }
    else if (major == 5 && minor == 1)
    {
       *buffer = (char*)"Windows XP";
    }
    else if (major == 5 && minor == 0)
    {
        *buffer = (char*)"Windows 2000";
    }
}




void getProcArchit(char **buffer, WORD procArchit)
{
    switch (procArchit)
    {
    case 9:
        *buffer = (char*)"x64 (AMD или Intel)";
        break;
    case 5:
        *buffer = (char*)"ARM";
        break;
    case 12:
        *buffer = (char*)"ARM64";
        break;
    case 6:
        *buffer = (char*)"Intel Itanium-based";
        break;
    case 0:
        *buffer = (char*)"x86";
        break;
    default:
        *buffer = (char*)"Unknown architecture";
    }
}




































//#define MAX_KEY_LENGTH 255
//#define MAX_VALUE_NAME 16383
//
//void QueryKey(HKEY hKey, LPCWSTR recursiveInfo)
//{
//    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
//    DWORD    cbName;                   // size of name string 
//    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
//    DWORD    cchClassName = MAX_PATH;  // size of class string 
//    DWORD    cSubKeys = 0;               // number of subkeys 
//    DWORD    cbMaxSubKey;              // longest subkey size 
//    DWORD    cchMaxClass;              // longest class string 
//    DWORD    cValues;              // number of values for key 
//    DWORD    cchMaxValue;          // longest value name 
//    DWORD    cbMaxValueData;       // longest value data 
//    DWORD    cbSecurityDescriptor; // size of security descriptor 
//    FILETIME ftLastWriteTime;      // last write time 
//
//    DWORD i, retCode;
//
//    TCHAR  achValue[MAX_VALUE_NAME];
//    DWORD cchValue = MAX_VALUE_NAME;
//
//    // Get the class name and the value count. 
//    retCode = RegQueryInfoKey(
//        hKey,                    // key handle 
//        achClass,                // buffer for class name 
//        &cchClassName,           // size of class string 
//        NULL,                    // reserved 
//        &cSubKeys,               // number of subkeys 
//        &cbMaxSubKey,            // longest subkey size 
//        &cchMaxClass,            // longest class string 
//        &cValues,                // number of values for this key 
//        &cchMaxValue,            // longest value name 
//        &cbMaxValueData,         // longest value data 
//        &cbSecurityDescriptor,   // security descriptor 
//        &ftLastWriteTime);       // last write time 
//
//    // Enumerate the subkeys, until RegEnumKeyEx fails.
//
//    TCHAR outputPath[1024];
//    int numberOfTabs = 0;
//    if (lstrlen(recursiveInfo) == 0)
//        printf("\nHKEY_CURRENT_CONFIG:\n");
//    else {
//        printf("\n");
//        swprintf_s(outputPath, L"HKEY_CURRENT_CONFIG\\%s:\n", recursiveInfo);
//        for (int i = 0; outputPath[i] != '\0'; i++) {
//            if (outputPath[i] == '\\')
//                numberOfTabs++;
//        }
//        for (int _ = 0; _ < numberOfTabs; _++)
//            printf("\t");
//        printf("HKEY_CURRENT_CONFIG\\%s:\n", recursiveInfo);
//
//    }
//    if (cSubKeys)
//    {
//        printf("\n");
//        for (int _ = 0; _ < numberOfTabs; _++)
//            printf("\t");
//        printf("Number of subkeys: %d\n", cSubKeys);
//
//        for (i = 0; i < cSubKeys; i++)
//        {
//            cbName = MAX_KEY_LENGTH;
//            retCode = RegEnumKeyEx(hKey, i,
//                achKey,
//                &cbName,
//                NULL,
//                NULL,
//                NULL,
//                &ftLastWriteTime);
//            if (retCode == ERROR_SUCCESS)
//            {
//                for (int _ = 0; _ < numberOfTabs; _++)
//                    printf("\t");
//                printf("(%d) %s\n", i + 1, achKey);
//            }
//        }
//    }
//
//    // Enumerate the key values. 
//
//    if (cValues)
//    {
//        printf("\n");
//        for (int _ = 0; _ < numberOfTabs; _++)
//            printf("\t");
//        printf("Number of values: %d\n", cValues);
//
//        for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
//        {
//            cchValue = MAX_VALUE_NAME;
//            achValue[0] = '\0';
//            retCode = RegEnumValue(hKey, i,
//                achValue,
//                &cchValue,
//                NULL,
//                NULL,
//                NULL,
//                NULL);
//
//            if (retCode == ERROR_SUCCESS)
//            {
//                for (int _ = 0; _ < numberOfTabs; _++)
//                    printf("\t");
//                printf("(%d) %s\n", i + 1, achValue);
//            }
//        }
//    }
//
//    if (cSubKeys) {
//        for (i = 0; i < cSubKeys; i++)
//        {
//            cbName = MAX_KEY_LENGTH;
//            retCode = RegEnumKeyEx(hKey, i,
//                achKey,
//                &cbName,
//                NULL,
//                NULL,
//                NULL,
//                &ftLastWriteTime);
//            if (retCode == ERROR_SUCCESS)
//            {
//                HKEY hTestKey;
//
//                TCHAR recursivePath[1024];
//                int len = lstrlen(recursiveInfo);
//                if (len == 0) {
//                    swprintf_s(recursivePath, L"%s", achKey);
//                }
//                else {
//                    swprintf_s(recursivePath, L"%s\\%s", recursiveInfo, achKey);
//                }
//
//                if (RegOpenKeyEx(HKEY_CURRENT_CONFIG,
//                    recursivePath,
//                    0,
//                    KEY_READ,
//                    &hTestKey) == ERROR_SUCCESS
//                    )
//                {
//                    QueryKey(hTestKey, recursivePath);
//                }
//
//                RegCloseKey(hTestKey);
//            }
//        }
//    }
//
//}
//
//void main(void)
//{
//    HKEY hTestKey;
//
//    if (RegOpenKeyEx(HKEY_CURRENT_CONFIG,
//        TEXT(""),
//        0,
//        KEY_READ,
//        &hTestKey) == ERROR_SUCCESS
//        )
//    {
//        QueryKey(hTestKey, L"");
//    }
//
//    RegCloseKey(hTestKey);
//}