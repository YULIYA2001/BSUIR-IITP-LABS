// https://habr.com/ru/post/582370/ - объяснение)

#include "Lab7.h"

#define IP_ADDRESS "127.0.0.1"
#define PORT 1234
#define BUFF_SIZE 1024     // max size of buffer for message


int main()
{
    // в структуру при создании загружаются данные о версии сокетов, используемых ОС
    WSADATA wsData;

    // ----- вызов функции запуска сокетов -----
    // int WSAStartup (WORD <запрашиваемая версия сокетов (старший бит - min версия, младший - max)>, 
    //                 WSADATA* <указатель на структуру, хранящую текущую версию реализации сокетов>)
    if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
    {
        printf("WSAStartup(). WinSock version initializaion error: %d\n", WSAGetLastError());
        return 1;
    }
    else
        printf("WinSock version initializaion is OK\n");

    // ----- инициализ. структ. данных SOCKET (привязка сокета к транспортной инфра-ре сети) -----
    // SOCKET socket(int <семейство используемых адресов>, int <тип сокета>, int <тип протокола>)
    // 1  параметр - IPv4, 2 - TCP, 3 - автомат.выбор
    SOCKET ServSock = socket(AF_INET, SOCK_STREAM, 0);
    if (ServSock == INVALID_SOCKET)
    {
        printf("Initialization socket error: %d\n", WSAGetLastError());
        closesocket(ServSock);      // закрыть использовавшиеся сокеты
        WSACleanup();               // деинициализировать сокеты
        return 1;
    }
    else
        printf("Server socket initialization is OK\n");

    // ----- Привязка сокета к паре IP-адрес/Порт для его нахождения -----

    // int inet_pton(int <сем-во адресов>, char[] <IP-адрес>, in_addr* <куда результат IP стр.->число>)
    in_addr ip_to_num;
    if (inet_pton(AF_INET, IP_ADDRESS, &ip_to_num) <= 0)
    {
        printf("Convert IP translation to special numeric format error\n");
        return 1;
    }

    // структура, родственной sockaddr для bind()
    sockaddr_in servInfo;
    ZeroMemory(&servInfo, sizeof(servInfo));

    servInfo.sin_family = AF_INET;        // Семейство адресов
    servInfo.sin_addr = ip_to_num;        // Вложенная структура in_addr с сетевым адресом
    servInfo.sin_port = htons(PORT);      // Порт (htons() - переупаковка для TCP)

    // int bind(SOCKET <имя сокета, к кот. привяжут адрес и порт>, 
    //          sockaddr* <дет. инф. по адресу и порту>, int <размер стр-ры, содержащей адрес и порт>)
    if (bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo)) != 0)
    {
        printf("Socket binding to server info error: %d\n", WSAGetLastError());
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }
    else
        printf("Binding socket to Server info is OK\n");

    // прослушивание (ожидание) Клиента
    if (listen(ServSock, SOMAXCONN) != 0)
    {
        printf("Can't start to listen to error: %d\n", WSAGetLastError());
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }
    else
        printf("Listening for any clients...\n");

    // ----- Подтверждение подключения к серверу -----
    sockaddr_in clientInfo;
    ZeroMemory(&clientInfo, sizeof(clientInfo));
    int clientInfo_size = sizeof(clientInfo);

    // accept(SOCKET <"слушает" на Сервере>, sockaddr* <пустая ст-ра для инф. о Клиенте>, int* <её размер>)
    SOCKET ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);
    if (ClientConn == INVALID_SOCKET)
    {
        printf("Client detected, but can't connect to a client. Error: %d\n", WSAGetLastError());
        closesocket(ServSock);
        closesocket(ClientConn);
        WSACleanup();
        return 1;
    }
    else
    {
        printf("Connection to a client established successfully\n");

        char clientIP[22];
        // Преобразование IP клиента в строку для вывода на экран
        inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);
        printf("Client connected with IP address: %s\n\n", clientIP);
    }


    // Обмен сообщений. Disconnection if a client send "xxx"
    std::vector<char> servBuff (BUFF_SIZE), clientBuff(BUFF_SIZE);
    short packet_size = 0;      // The size of sending / receiving packet in bytes

    while (true) {
        // Receiving packet from client. Program is waiting (system pause) until receive
        packet_size = recv(ClientConn, servBuff.data(), servBuff.size(), 0);
        printf("Client: %s", servBuff.data());
        printf("SERVER: ");
        fgets(clientBuff.data(), clientBuff.size(), stdin);

        // Check whether server would like to stop chatting 
        if (clientBuff[0] == 'x' && clientBuff[1] == 'x' && clientBuff[2] == 'x') {
            shutdown(ClientConn, SD_BOTH);
            closesocket(ServSock);
            closesocket(ClientConn);
            WSACleanup();
            return 0;
        }

        packet_size = send(ClientConn, clientBuff.data(), clientBuff.size(), 0);

        if (packet_size == SOCKET_ERROR) {
            printf("Can't send message to Client error: %d\n", WSAGetLastError());
            closesocket(ServSock);
            closesocket(ClientConn);
            WSACleanup();
            return 1;
        }
    }
    closesocket(ServSock);
    closesocket(ClientConn);
    WSACleanup();

    return 0;
}





























//// параметры передающиеся в функцию потока
//struct Data
//{
//    SOCKET ClientConn;
//    SOCKET ServSock;
//    HANDLE* otherThread;
//}data;
//
//
////DWORD WINAPI recieveProc(LPVOID data)
////{
////    Data* d = (Data*)data;
////    SOCKET ClientConn = (SOCKET)d->ClientConn;
////    HANDLE* otherThread = (HANDLE*)d->otherThread;
////    std::vector<char> servBuff(BUFF_SIZE);
////    short packet_size = 0;
////
////    while (recv(ClientConn, servBuff.data(), servBuff.size(), 0))
////    {
////        // Receiving packet from client. Program is waiting (system pause) until receive
////        SuspendThread(otherThread);
////        //packet_size = recv(ClientConn, servBuff.data(), servBuff.size(), 0);
////        printf("Client: %s", servBuff.data());
////        ResumeThread(otherThread);
////        Sleep(1000);
////    }
////    return true;
////}
//
//
//DWORD WINAPI sendProc(LPVOID data)
//{
//    Data* d = (Data*)data;
//    SOCKET ClientConn = d->ClientConn;
//    SOCKET ServSock = d->ServSock;
//    //HANDLE* otherThread = d->otherThread;
//    std::vector<char> clientBuff(BUFF_SIZE);
//    short packet_size;
//
//    while (true)
//    {
//        printf("SERVER: ");
//        fgets(clientBuff.data(), clientBuff.size(), stdin);
//        // Check whether server would like to stop chatting 
//        if (clientBuff[0] == 'x' && clientBuff[1] == 'x' && clientBuff[2] == 'x') {
//            shutdown(ClientConn, SD_BOTH);
//            closesocket(ServSock);
//            closesocket(ClientConn);
//            WSACleanup();
//            return 0;
//        }
//        packet_size = send(ClientConn, clientBuff.data(), clientBuff.size(), 0);
//
//        if (packet_size == SOCKET_ERROR) {
//            printf("Can't send message to Client error: %d\n", WSAGetLastError());
//            closesocket(ServSock);
//            closesocket(ClientConn);
//            WSACleanup();
//            return 1;
//        }
//        Sleep(1000);
//    }
//}