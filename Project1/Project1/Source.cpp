#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <windows.h>
#pragma warning(disable: 4996)

using namespace std;
int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	WSAData wsaData;
	WORD DDLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DDLVersion, &wsaData) != 0) {
		cout << "error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1280);//порт,который будет ассоциироваться с сокетом
	addr.sin_family = AF_INET;//всегда

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "error#3" << endl;
		return 1;
	}

	cout << "client connection" << endl;
	char msg[256];
		cout << "\n1.Вход под администратором\n"
			"2.Вход под пользователем\n"
			"0.Выход\n"
			"\n\nВаш выбор: ";
		cin >> msg;
		send(Connection, msg, sizeof(msg), NULL);

	
	system("pause");
	return 0;
}
