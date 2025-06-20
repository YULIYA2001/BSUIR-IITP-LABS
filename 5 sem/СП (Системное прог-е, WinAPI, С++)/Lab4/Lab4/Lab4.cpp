#include "Lab4.h"

#define SIZE 10001

HANDLE hFile;


void ReadAsync(LPCSTR fileName)
{
    hFile = CreateFileA(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("Error in open file");
        exit(-1);
    }

    OVERLAPPED ovr = { 0 };                 // структура для асинхронного чтения
    DWORD bytesReaded = 1;
    DWORD bytesReadedProcessing = 1;
    CHAR dataBuffer[SIZE] = { 0 };
    CHAR dataBufferProcessing[SIZE] = { 0 };
    int aCount = 0;
    DWORD beginTime = GetTickCount64();     // время, пошедшее с запуска программы

    // читаем первый кусок файла
    ReadFile(hFile, dataBuffer, sizeof(dataBuffer) - 1, NULL, &ovr);
    if (GetLastError() != 997) //  997 - ERROR_IO_PENDING
    {
        printf("Error in read file");
        exit(-1);
    }
    //DWORD t = GetLastError();
    GetOverlappedResult(hFile, &ovr, &bytesReaded, TRUE);       // ждем пока закончится чтение
    strcpy_s(dataBufferProcessing, dataBuffer);                 // копируем прочитанное для обработки
    bytesReadedProcessing = bytesReaded;                        //         -//-
    ovr.Offset += bytesReaded;                                  // добавляем смещение для файла

    while (bytesReaded == sizeof(dataBuffer)-1)
    {
        ReadFile(hFile, dataBuffer, sizeof(dataBuffer) - 1, NULL, &ovr);
        if (GetLastError() != 997) //  997 - ERROR_IO_PENDING
        {
            printf("Error in read file");
            exit(-1);
        }
        GetOverlappedResult(hFile, &ovr, &bytesReaded, FALSE);
        //printf("%s", dataBufferProcessing);
        for (int i = 0; i < bytesReadedProcessing; i++)
            if ((int)dataBufferProcessing[i] == -32)
                aCount++;
        GetOverlappedResult(hFile, &ovr, &bytesReaded, TRUE);
        dataBuffer[bytesReaded] = '\0';
        ovr.Offset += bytesReaded;
        strcpy_s(dataBufferProcessing, dataBuffer);
        bytesReadedProcessing = bytesReaded;
    }
    for (int i = 0; i < bytesReadedProcessing; i++)
        if ((int)dataBufferProcessing[i] == -32)
            aCount++;
    DWORD endTime = GetTickCount64() - beginTime;

    printf("\nВремя считывания в асинхронном режиме: %d мс\n", endTime);
    CloseHandle(hFile);
    printf("'a' count in text: %d\n", aCount);
    _getch();
}



void ReadSync(LPCSTR fileName)
{
    hFile = CreateFileA(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("Error in open file");
        exit(-1);
    }

    DWORD bytesReaded = 1;
    int aCount = 0;
    CHAR dataBuffer[SIZE] = { 0 };

    //...........................................................................
    // искусственно сделать работу в синхронной и асинхронной функциях одинаковой
    DWORD bytesReadedProcessing = 1;
    CHAR dataBufferProcessing[SIZE] = { 0 };
    //...........................................................................

    DWORD beginTime = GetTickCount64();

    while (bytesReaded != 0)
    {        
        if (ReadFile(hFile, dataBuffer, sizeof(dataBuffer)-1, &bytesReaded, NULL) == FALSE)
        {
            printf("Error in read file");
            exit(-1);
        }
        dataBuffer[bytesReaded] = '\0';
        //printf("%s", dataBuffer);
        for (int i = 0; i < bytesReaded; i++)
            if ((int)dataBuffer[i] == -32)
                aCount++;

        //...........................................................................
        // искусственно сделать работу в синхронной и асинхронной функциях одинаковой 
        dataBuffer[bytesReaded] = '\0';
        strcpy_s(dataBufferProcessing, dataBuffer);
        bytesReadedProcessing = bytesReaded;
        //...........................................................................
    }
    DWORD endTime = GetTickCount64() - beginTime; 

    printf("\nВремя считывания в синхронном режиме: %d мс\n", endTime);
    CloseHandle(hFile);
    printf("'a' count in text: %d\n", aCount);
    _getch();
}


int main()
{
    setlocale(LC_ALL, "Russian");

    while (true) 
    {
        ReadAsync("123.txt");
        ReadSync("123.txt");
        ReadSync("Poem.txt");
        ReadAsync("Poem.txt");
    }
    
    return 0;
}
