#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Missing Port no.\n";
    }
    int port = atoi(argv[1]);
    char message[1500];

    sockaddr_in serverSocket;
    serverSocket.sin_family = AF_INET;
    serverSocket.sin_port = htons(port);
    serverSocket.sin_addr.s_addr = htonl(INADDR_ANY);

    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketID < 0)
    {
        cerr << "Not succefsul\n";
        exit(0);
    }

    int bindStatus = bind(serverSocketID, (struct sockaddr *)&serverSocket, sizeof(serverSocket));
    if (bindStatus < 0)
    {
        cerr << "Not  succesful bind.\n";
        exit(0);
    }

    cout << "Waiting for client\n";

    listen(serverSocketID, 1);

    sockaddr_in newSocket;
    socklen_t newSocketLen = sizeof(newSocket);

    int newSocketID = accept(serverSocketID, (sockaddr *)&newSocket, &newSocketLen);

    if (newSocketID < 0)
    {
        cerr << "Not succesfull accept()\n";
        exit(0);
    }
    cout << "client connected sucessfull\n";

    while (1)
    {
        cout << "waiting for message from client \n";
        recv(newSocketID, (char *)&message, sizeof(message), 0);
        if (!strcmp(message, "exit"))
        {
            cout << "Session Terminated\n";
            break;
        }

        cout << message << endl;
        string data;
        cin >> data;

        strcpy(message, data.c_str());

            if (data == "exit")
        {
            cout << "session terminated\n";
            break;
        }
        send(newSocketID, (char *)&message, sizeof(message), 0);
    }
    close(newSocketID);
    close(serverSocketID);
}
