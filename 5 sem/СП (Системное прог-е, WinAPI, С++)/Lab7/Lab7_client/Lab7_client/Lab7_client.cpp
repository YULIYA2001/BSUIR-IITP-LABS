// https://habr.com/ru/post/582370/ - объяснение)

#include "Lab7_client.h"

#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT 1234
#define BUFF_SIZE 1024     // max size of buffer for message


int main()
{
    WSADATA wsData;

    // ----- вызов функции запуска сокетов -----
    if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
    {
        printf("WSAStartup(). WinSock version initializaion error: %d\n", WSAGetLastError());
        return 1;
    }
    else
        printf("WinSock version initializaion is OK\n");

    // ----- инициализ. структ. данных SOCKET (привязка сокета к транспортной инфра-ре сети) -----
    SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);
    if (ClientSock == INVALID_SOCKET) 
    {
        printf("Initialization socket error: %d\n", WSAGetLastError());
        closesocket(ClientSock);    // закрыть использовавшиеся сокеты
        WSACleanup();               // деинициализировать сокеты
        return 1;
    }
    else
        printf("Client socket initialization is OK\n");


    // ----- Связь с сервером (Lab7.cpp) -----

    in_addr ip_to_num;
    if (inet_pton(AF_INET, SERVER_IP_ADDRESS, &ip_to_num) <= 0)       // то же, что у сервера
    {
        printf("Convert IP translation to special numeric format error\n");
        return 1;
    }

    sockaddr_in servInfo;
    ZeroMemory(&servInfo, sizeof(servInfo));

    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;	  // Server's IPv4 after inet_pton() function
    servInfo.sin_port = htons(SERVER_PORT);

    //int connect(SOCKET <инициализ. сокет>, sockaddr* <стр-ра с IP и Портом сервера>, int <её размер>)
    if (connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo)) != 0) 
    {
        printf("Connection to Server error: %d\n: ", WSAGetLastError());
        closesocket(ClientSock);
        WSACleanup();
        return 1;
    }
    else
        printf("Connection established SUCCESSFULLY. Ready to send a message to Server\n\n");

    // Обмен сообщений. Disconnection if a Client send "xxx"

    std::vector<char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);							
    short packet_size = 0;				// The size of sending / receiving packet in bytes

    while (true) {

        printf("CLIENT: ");
        fgets(clientBuff.data(), clientBuff.size(), stdin);

        // Check whether client like to stop chatting 
        if (clientBuff[0] == 'x' && clientBuff[1] == 'x' && clientBuff[2] == 'x') {
            shutdown(ClientSock, SD_BOTH);
            closesocket(ClientSock);
            WSACleanup();
            return 0;
        }

        packet_size = send(ClientSock, clientBuff.data(), clientBuff.size(), 0);

        if (packet_size == SOCKET_ERROR) {
            printf("Can't send message to Server error: %d\n", WSAGetLastError());
            closesocket(ClientSock);
            WSACleanup();
            return 1;
        }

        packet_size = recv(ClientSock, servBuff.data(), servBuff.size(), 0);

        if (packet_size == SOCKET_ERROR) {
            printf("Can't receive message from Server error: %d\n", WSAGetLastError());
            closesocket(ClientSock);
            WSACleanup();
            return 1;
        }
        else
            printf("Server: %s", servBuff.data());

    }

    closesocket(ClientSock);
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
//        printf(": ");
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