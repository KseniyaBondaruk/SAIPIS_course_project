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
	addr.sin_port = htons(1280);//����,������� ����� ��������������� � �������
	addr.sin_family = AF_INET;//������

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "error#3" << endl;
		return 1;
	}

	cout << "client connection" << endl;
	char msg[256];
		cout << "\n1.���� ��� ���������������\n"
			"2.���� ��� �������������\n"
			"0.�����\n"
			"\n\n��� �����: ";
		cin >> msg;
		send(Connection, msg, sizeof(msg), NULL);

	
	system("pause");
	return 0;
}
