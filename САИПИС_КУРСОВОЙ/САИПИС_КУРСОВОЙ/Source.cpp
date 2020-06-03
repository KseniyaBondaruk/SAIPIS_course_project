/*����������� �������� ��� ������������ �������� ������� ���������������� ��������� (�� ������� ���������)*/

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include<iostream>
#include<string>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <process.h> 
#include <conio.h>
#include <map>
#pragma warning(disable: 4996)


using namespace std;

int id = 0;//������� ��� ����������� ����������� ������
const int MAXEM = 6;//������������ ����� ����� �����������

void adminMenu();
void userMenu();
int checkAdmin();
int checkUser();
void mainMenu();
void workWithUsers();
void addUsers();
void deleteUsers();

void newHandler() {//�� ������� �������� ������
	cout << "������� newHandler: ";
	throw bad_alloc();
}

class MyException : public exception
{
public:
	const char * what() const throw () {
		return "C++ Exception";
	}
};

class INFO_BASE {//������� ����������� �����
public:
	virtual void viewing() = 0;
};

class PRESUMED_INFO :public INFO_BASE {//�������� (�������������� ����������)
public:
	int program_length;//�������������� ����� ������������ (� �������)
	double tvr;//�������������� ������� 
	string airtime;//���������������� ������� �����
	void getdata()
	{
		cout << " ������� �������������� ����� ������������ � �������: "; cin >> program_length;
		try {
			if (program_length <= 0) throw MyException();
		}
		catch (MyException& e) {
			cout << "����� ������������ �� ����� ���� ������ ����" << endl;
		}
		cout << " ������� �������������� �������: "; cin >> tvr;
		try {
			if (tvr <= 0 || tvr>100) throw MyException();//������ �����
		}
		catch (MyException& e) {
			cout << "������� ����� �������" << endl;
		}
		cout << " ������� ���������������� ������� �����: "; cin >> airtime;
	}
	void putdata()
	{
		cout << "\n �������������� �����: " << program_length;
		cout << "\n �������������� �������: " << tvr;
		cout << "\n ���������������� ������� �����: " << airtime;
	}
	void viewing1()
	{
		cout << "|" << setw(9) << program_length << "|" << setw(7) << tvr << "|" << setw(13) << airtime << "|" ;
		cout << "\n|--------------------------------------------------------------------------|" << endl;
	}
	
};

class AUDIENCE_INFO :public INFO_BASE {//���������� � ������� ���������
public:
	string category;//���������� ���������
	int men;//������� �������� �������� ����
	int women;//������� �������� �������� ����
	void getdata()
	{
		cout << " ������� ���������� ���������: "; cin >> category;
		cout << " ������� ������� �������� �������� ����: "; cin >> men;
		cout << " ������� ������� �������� �������� ����: "; cin >> women;
		try {
			if (!women || !men) throw MyException();//������ �����
		}
		catch (MyException& e) {
			cout << "MyException caught" <<endl;
			cout << e.what() << endl;
		}
	}
	void putdata()
	{
		cout << "\n ���������� ���������: " << category;
		cout << "\n ������� �������� �������� ����: " << men;
		cout << "\n ������� �������� �������� ����: " << women;
	}
	void viewing2()
	{
		cout << "|" << setw(20) << category << "|" << setw(19) << men << "|" << setw(19) << women << "|" ;
		cout << "\n|-------------------------------------------------------------------------------------------------------|" << endl;
	}
	
};

class DECORATIONS_INFO :public INFO_BASE {//���������� � ����������
public:
	int prodaction;//���� ������������ ��������� (� �������)
	int cost;//��������� ���������
	void getdata()
	{
		cout << " ������� ���� ������������ ��������� (� �������): "; cin >> prodaction;
		try {
			if (!prodaction) throw MyException();//������ �����
		}
		catch (MyException& e) {
			cout << "MyException caught" << endl;
			cout << e.what() << endl;
		}
		cout << " ������� ��������� ���������: "; cin >> cost;
		try //������������ �������� ��� ����������� ���������
		{
			if (cost <= 0.0)
				throw MyException();//������ �����
		}
		catch (MyException& e) {
			cout << "��������� ��������� �� ����� ���� ������ ����" << endl;
		}
	}
	void putdata()
	{
		cout << "\n ���� ������������ ��������� (� �������): " << prodaction;
		cout << "\n ��������� ���������: " << cost;
	}
	void viewing3()
	{
		cout << "|"  << setw(21 ) << prodaction << "|" << setw(18) << cost << "|";
		cout << "\n|-----------------------------------------------------------------------------------|" << endl;
	}
	
};

class BROADCAST_INFO :public  PRESUMED_INFO , public AUDIENCE_INFO, public DECORATIONS_INFO{//���������� � ������������
public:
	int serial_number;//���������� �����
	string type;//��� ������������
	int anchormen;//���������� �������
	string viewers;//������� �������� � ������ (��/���)
	int estimate;//���������� ������
	static int n; // ������� ����� ��������
	static BROADCAST_INFO* arrap[]; //������ ���������� �� ����� ���������� � ������������
	void getdata()
	{
		serial_number = id;
		cout << " ������� ��� ������������: "; cin >> type;
		cout << " ������� ���������� �������: "; cin >> anchormen;
		cout << " � ������ ����� ���������� �������?: "; cin >> viewers;
		PRESUMED_INFO::getdata();
		AUDIENCE_INFO::getdata();
		DECORATIONS_INFO::getdata();
	}
	void getestimation()
	{
		cout << "\n ������� ���������� ������: "; cin >> estimate;
		try {
			if (!estimate) throw MyException();//������ �����
		}
		catch (MyException& e) {
			cout << "MyException caught" << endl;
			cout << e.what() << endl;
		}
	}
	void putdata()
	{
		cout << "��� ������������: " << type;
		cout << "\n ���������� �������: " << anchormen;
		cout << "\n ������� �������� � ������: " << viewers;
		PRESUMED_INFO::putdata();
		AUDIENCE_INFO::putdata();
		DECORATIONS_INFO::putdata();
	}
	static void expert(); // ������������
	static void add(); // ����������
	static void display(); // ����� ������
	static void del();// ��������
	static void edit(); // ��������������
	static void read(); // ������ �� �����
	friend void view();// ��������
	static void write(); // ������ � ����
	void viewing()
	{
		cout << "|" << setw(16) << serial_number << "|" << setw(25) << type << "|" << setw(18) << anchormen << "|" << setw(16) << viewers << "|";
		cout << "\n|------------------------------------------------------------------------------|" << endl;
	}
	void view_all();
	void view_decorations();
	void view_audience();
	void view_presume();
	static void sort();
};

int BROADCAST_INFO::n; // ������� ����� ��������
BROADCAST_INFO* BROADCAST_INFO::arrap[MAXEM]; // ������ ���������� �� ����� ���������� � ������������

class users//������������
{
public:
	char login[20], password[20];
}USER;

template <typename T>
class consent {
public:	
	T agreement;
	consent(T agreement) : agreement(agreement)
	{ }
	T getagreement() {
		return agreement;
	}
};

void BROADCAST_INFO::expert()
{
	map <int, int> mp;
	int array[MAXEM];
	consent <int> agree(1);

	for (int i = 0; i < n; i++) {
		arrap[i]->putdata();
		arrap[i]->getestimation();
	}

	for (int i = 0; i < n; i++) {
		mp[arrap[i]->estimate] = i;  // ��������� ����� ��������
	}

	map <int, int> ::iterator it = mp.begin();
	for (int i = 0; it != mp.end(); it++, i++) {  // ������� ��
		cout << i+1 << ") ������ " << it->first << ", ��� " << it->second + 1<< endl;
		array[i] = it->first;
	}

	for (int index = n; index > 1; index--)
	{
		for (int i = index - 2; i >= 0; i--)
			for (int j = i - 1; j >= 0; j--)
				if (j < i)
				{
					cout << array[index - 1];
					if (array[index - 1] > array[i] + array[j]) cout << " > ";
					if (array[index - 1] < array[i] + array[j]) cout << " < ";
					if (array[index - 1] == array[i] + array[j]) cout << " = ";
					cout << array[i] << "+" << array[j] << endl << "��������? (1-��, 2-���)" << endl;
					cin >> agree.agreement;
					if (agree.agreement == 2) { 
						map <int,int> ::iterator full_name;
					full_name = mp.find(array[index - 1]); 
					int sec = full_name->second;
						cout << " �������������� ������: "; 
						cin >> array[index - 1]; 
						mp.emplace(array[index - 1], sec);
						mp.erase(full_name);
					}
				}
		cout << endl;
	}

	cout << "�� �����������: " << endl;
	map <int, int> ::iterator itt = mp.begin();
	for (int i = 1; itt != mp.end(); itt++, i++) {  // ������� ��
		cout << i << ") ��� " << itt->second + 1 << " - ";
		for (int i = 0; i < n; i++)
			if (itt->second + 1 == arrap[i]->serial_number) cout << arrap[i]->type << endl;
	}
	
}

void BROADCAST_INFO::add()
{
	set_new_handler(newHandler);
	char ch;
		do {
			try { arrap[n] = new BROADCAST_INFO; id++; arrap[n++]->getdata(); }
			catch (bad_alloc& e) { cout << e.what() << endl; }
			cout << "\n1-���������� ������� ������, 2-����� � ���� 2-�� ������\n";
			cin >> ch;
		} while (ch != '2'); 
} 

void BROADCAST_INFO::del()
{
	system("cls");
	int flag;
	BROADCAST_INFO r; r.view_all();
	cout << "\n������� ���������� ����� �����������, ������� ��������� �������:";
	cin >> flag;
	BROADCAST_INFO *buff; arrap[n] = new BROADCAST_INFO;

	for (int i = 0; i < n; i++)
		if (((BROADCAST_INFO *)arrap[i])->serial_number == flag)
		{
			buff = arrap[i];
			arrap[i] = arrap[i + 1];
			arrap[i + 1] = buff;
		}
	n--;
	for (int i = 1; i <= n; i++)
	{
		((BROADCAST_INFO *)arrap[i - 1])->serial_number = i;
	}
	id--;
}

void BROADCAST_INFO::edit()
{
	system("cls");
	BROADCAST_INFO p; p.view_all();
			cout << "\n������� ����������� ����� �������������� �������, �������� � ������� �� ������ ��������:";
			int num;  cin >> num;
			char choise; string s; int t; arrap[n] = new BROADCAST_INFO;
			do {
				cout << "����� ���� �� ������ ���������������?:"
					"\n'1' - ��� ������������"
					"\n'2' - ���������� �������"
					"\n'3' - ������� �������� � ������"
					"\n'4' - �������������� �����"
					"\n'5' - �������������� �������"
					"\n'6' - ���������������� ������� �����"
					"\n'7' - ���������� ���������"
					"\n'8' - ������� �������� �������� ����"
					"\n'9' - ������� �������� �������� ����"
					"\n'10' - ���� ������������ ���������"
					"\n'11' - ��������� ���������"
					"\n'0' - ����� � ���� 2-�� ������"
					"\n��� �����: ";
				cin >> choise;
				switch (choise) {
				case '1': {cout << "������� ��� ������������:";
					cin >> s;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->type = s; }break;
				case '2': {cout << "������� ���������� �������:";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
						((BROADCAST_INFO *)arrap[i])->anchormen = t; }break;
				case '3': {cout << "� ������ ����� ���������� �������?:";
					cin >> s;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->viewers = s;
				}break;
				case '4': {cout << "������� �������������� ����� (� �������):";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->program_length = t; }break;
				case '5': {cout << "������� �������������� �������:";
					double h; cin >> h;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->tvr = h;
				}break;
				case '6': {cout << "������� ���������������� ������� �����:";
					cin >> s;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->airtime = s;
				}break;
				case '7': {cout << "������� ���������� ���������:";
					cin >> s;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->category = s;
				}break;
				case '8': {cout << "������� ������� �������� �������� ����:";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->men = t;
				}break;
				case '9': {cout << "������� ������� �������� �������� ����:";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->women = t;
				}break;
				case '10': {cout << "������� ���� ������������ ���������:";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->prodaction = t; }break;
				case '11': {cout << "������� ��������� ���������:";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->cost = t; }break;
				}

			} while (choise != '0'); 
}

void BROADCAST_INFO::view_all()
{
	system("cls");
	cout << "\n|------------------------------------------------------------------------------|"
		"\n|���������� �����|��� ������������         |���������� �������|������� ��������|"
		"\n|------------------------------------------------------------------------------|" << endl;
	for (int j = 0; j < n; j++)
	{
		arrap[j]->viewing();
	}
}

void BROADCAST_INFO::view_decorations()
{
	system("cls");
	cout << "\n|-----------------------------------------------------------------------------------|"
		"\n|���������� �����|��� ������������         |���� ������������,���|���������,���.���.|"
		"\n|-----------------------------------------------------------------------------------|" << endl;
	for (int j = 0; j < n; j++)
	{
		cout << "|" << setw(16) << arrap[j]->serial_number << "|" << setw(25) << arrap[j]->type;
		arrap[j]->viewing3();
	}
}

void BROADCAST_INFO::view_audience()
{
	system("cls");
	cout << "\n|-------------------------------------------------------------------------------------------------------|"
		"\n|���������� �����|��� ������������         |���������� ���������|������� ���������,%|������� ���������,%|"
		"\n|-------------------------------------------------------------------------------------------------------|" << endl;
	for (int j = 0; j < n; j++)
	{
		cout << "|" << setw(16) << arrap[j]->serial_number << "|" << setw(25) << arrap[j]->type;
		arrap[j]->viewing2();
	}
}

void BROADCAST_INFO::view_presume()
{
	system("cls");
	cout << "\n|--------------------------------------------------------------------------|"
		"\n|���������� �����|��� ������������         |�����,���|�������|������� �����|"
		"\n|--------------------------------------------------------------------------|" << endl;
	for (int j = 0; j < n; j++)
	{
		cout << "|" << setw(16) << arrap[j]->serial_number << "|" << setw(25) << arrap[j]->type;
		arrap[j]->viewing1();
	}
}

void view()
{
	system("cls"); BROADCAST_INFO i;
	char ch;
	do
	{
		cout << "\n����������� �������:"
			"\n'1' - ����� �����������"
			"\n'2' - ���������� � ����������"
			"\n'3' - ���������� � ������� ���������"
			"\n'4' - �������������� ����������"
			"\n'0' - ����� � ���� 2-�� ������"
			"\n��� �����: ";
		cin >> ch;
		switch (ch)
		{
		case '1': {i.view_all(); } break;
		case '2': {i.view_decorations(); }break;
		case '3': {i.view_audience(); }break;
		case '4': {i.view_presume(); }break;
		case '0':system("cls"); return; break;
		default: printf("\n������� ������ ���� �� ����������!\n");
		}
	} while (ch != '0');
}

template<class T>
int shublon(T a, T b) {
	if (a > b) {
		return 1;
	}
	return 0;
}
void BROADCAST_INFO::sort()
{
	system("cls");
	arrap[n] = new BROADCAST_INFO;
	int x, y;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			x = ((BROADCAST_INFO *)arrap[i])->tvr;
			y = ((BROADCAST_INFO *)arrap[j])->tvr;
			if (shublon<double>(x, y) == 1)
				swap(arrap[i], arrap[j]);
		}
	}

	BROADCAST_INFO::display();

}//���������� ����������� �� ��������

void BROADCAST_INFO::read()
{
	int size; // ������ �������
	ifstream inf; // ������� ifstream � �������� ����
	inf.open("C:\\Users\\ThinkPad\\source\\repos\\������_��������\\maindata.dat", ios::in | ios::binary);
	if (!inf)
	{
		cout << "\n���������� ������� ����\n"; return;
	}
	n = 0; // � ������ ����������� ���
	while (true)
	{ 
		if (inf.eof()) // ����� �� ����� �� EOF
			break;
		if (!inf) // ������ ������ ����
		{
			cout << "\n���������� ������ ����\n"; return;
		}
		
			arrap[n] = new BROADCAST_INFO;
			size = sizeof(BROADCAST_INFO);
			for (int i = 0; i < n; i++)
				id = ((BROADCAST_INFO *)arrap[i])->serial_number;
			id++;
			
		inf.read((char*)arrap[n], size);
		if (!inf) // ������, �� �� EOF
		{
			cout << "\n������ ������ �� ����� ����������\n"; return;
		}
		//id = n;
		n++; // ������� ����������� ���������
	} //end while
	inf.close();
	cout << "���� ������ " << n << " �����������\n";
}

void BROADCAST_INFO::display()
{
	for (int j = 0; j < n; j++)
	{
		cout << arrap[j]->serial_number << ". ";
		arrap[j]->putdata(); // ����� ������
		cout << endl;
	}
}

void BROADCAST_INFO::write()
{
	int size;
	cout << "���� ������ " << n << " �����������.\n";
	ofstream ouf; // ������� ofstream � �������� ����
	ouf.open("C:\\Users\\ThinkPad\\source\\repos\\������_��������\\maindata.dat", ios::out | ios::ate | ios::binary);
	if (!ouf)
	{
		cout << "\n���������� ������� ����\n"; return;
	}
	for (int j = 0; j < n; j++) // ��� ������� �������
	{ size = sizeof(BROADCAST_INFO);
		 
		ouf.write((char*)(arrap[j]), size);//������ ������� � ����
		if (!ouf)
		{
			cout << "\n������ � ���� ����������\n"; return;
		}
	}
	ouf.close();
}

//---------------------------------------------------------
//������� �������� ������ � ������ ��� ��������������
int checkAdmin()

{
	char login[20], password[20], rightLogin[20], rightPassword[20];
	ifstream fin("C:\\Users\\ThinkPad\\source\\repos\\������_��������\\admindata.txt", ios::in); // �������� ����� ��� ������
	if (!fin.is_open()) cout << "��������� ���� �� ����������!" << endl;
	else
	{
		while (!fin.eof())
		{
			fin >> rightLogin >> rightPassword;
		}
	}
	for (int i = 0; i < strlen(rightPassword); i++)
		rightPassword[i] -= 3;
	cout << "������� �����: ";
	cin >> login;
	cout << "������� ������: ";
	char c;
	int k = 0;
	while ((c = _getch()) != '\r')
	{
		password[k++] = c;
		_putch('*');
	}
	password[k] = '\0';
	if (strcmp(login, rightLogin) == 0 && strcmp(password, rightPassword) == 0)
	{
		fin.close(); //�������� �����
		return 1;
	}
	fin.close();
	return 0;
}
//---------------------------------------------------------
//������� �������� ������ � ������ ��� ������������
int checkUser()
{
	char login[20], password[20];
	ifstream inf;
	int i, n = 0;
	users *p;
	inf.open("C:\\Users\\ThinkPad\\source\\repos\\������_��������\\userdata.txt", ios::in | ios::ate);
	if (!inf) { cout << "\n���������� ������� ����\n"; return 0; }
	n = inf.tellg() / sizeof(USER);
	inf.seekg(0);
	p = new users[n * sizeof(USER)];
	for (i = 0; i < n; ++i)
	{
		inf.read((char*)&USER, sizeof(USER));
		for (int i = 0; i < strlen(USER.password); i++)
			USER.password[i] -= 3;
		p[i] = USER;
	}

	cout << "������� �����: ";
	cin >> login;
	cout << "������� ������: ";
	char c;
	int k = 0;
	while ((c = _getch()) != '\r')
	{
		password[k++] = c;
		_putch('*');
	}
	password[k] = '\0';
	for (i = 0; i < n; i++)
	{
		if (strcmp(p[i].login, login) == 0 && strcmp(p[i].password, password) == 0)
		{
			delete p;
			inf.close();
			return 1;
		}
	}
	delete p;
	inf.close();
	return 0;

}
//---------------------------------------------------------
//�������������(����������) �������������
void addUsers()
{

	char ch;
	ifstream inf;
	inf.open("C:\\Users\\ThinkPad\\source\\repos\\������_��������\\userdata.txt", ios::in);
	if (!inf) { cout << "\n���������� ������� ����\n"; return; }
	while (true)
	{
		inf.read((char*)&USER, sizeof(USER));
		if (inf.eof()) // ����� �� ����� �� EOF
			break;
	}
	inf.close();
	ofstream ouf;
	ouf.open("C:\\Users\\ThinkPad\\source\\repos\\������_��������\\userdata.txt", ios::out | ios::app);
	if (!ouf) { cout << "\n���������� ������� ����\n"; return; }
	do
	{
		cout << "\nlogin ��� ������ ������������: ";
		cin >> USER.login;
		cout << "\npassword ��� ������ ������������: ";
		cin >> USER.password;
		for (int i = 0; i < strlen(USER.password); i++)
			USER.password[i] += 3;
		ouf.write((char*)&USER, sizeof(USER));
		printf("\n1-���������� ������� ������, 2-����� � ���� ���������� ��������������");
		cin >> ch;
	} while (ch != '2');
	ouf.close();

}
//---------------------------------------------------------
//����������(��������) ������������
void deleteUsers()
{
	ifstream inf;
	int i, j = 1, n = 0;
	char flag[20];
	users *p, buff;
	inf.open("C:\\Users\\ThinkPad\\source\\repos\\������_��������\\userdata.txt", ios::in | ios::ate);
	if (!inf) { cout << "\n���������� ������� ����\n"; return; }
	n = inf.tellg() / sizeof(USER);
	inf.seekg(0);
	p = new users[n * sizeof(USER)];
	cout << "\n|�����        |"
		"\n|-------------|";
	for (i = 0; i < n; ++i)
	{
		inf.read((char*)&USER, sizeof(USER));
		p[i] = USER;
		cout << "\n|" << setw(13) << p[i].login << "|";
	}
	cout << "\n|-------------|";
	inf.close();
	cout << "\n������� ����� ������������, �������� ������ �������";
	cin >> flag;
	ofstream ouf;
	ouf.open("C:\\Users\\ThinkPad\\source\\repos\\������_��������\\userdata.txt", ios::out | ios::ate);
	while (j)
	{
		j = 0;
		for (i = 0; i < n - 1; i++)
		{
			if (strcmp(p[i].login, flag) == 0)
			{
				buff = p[i];
				p[i] = p[i + 1];
				p[i + 1] = buff;
				j = 1;
			}
		}
	}
	for (i = 0; i < n - 1; ++i)
		ouf.write((char*)&p[i], sizeof(USER));
	delete p;
	ouf.close();

}
//---------------------------------------------------------
//���� ���������� ��������������
void workWithUsers()
{
	system("cls");
	char choise;
	do
	{
		cout << "'1' � �������� �������������"
			"\n'2' - ������� ������������"
			"\n'0' - ����� � ���� ��������������"
			"\n��� �����: ";
		cin >> choise;
		switch (choise)
		{
		case '1': system("cls"); addUsers();  break;
		case '2': system("cls"); deleteUsers(); break;
		case '0': system("cls"); return; break;
		default: cout << "\n������� ������ ���� �� ����������!\n";
		}
	} while (choise != '0');
}

void userMenu()
{
	system("cls");
	char ch;
	while (true)
	{
		cout << "\n'1' - ����� ������ � ����� �����������"
			"\n'2' - �������� ������ � ��������� �����"
			"\n'3' � ������������ ����� ����������� ������� ���������������� ���������"
			"\n'4' � ��������� ��� ������ �� �����"
			"\n'5' � ���������� ����������� �� ��������"
			"\n'0' - �����"
			"\n��� �����: ";
		cin >> ch;
		switch (ch)
		{
		case '1': // ������� ��� ��������
			BROADCAST_INFO::display(); break;
		case '2': // �������� ����������� ����������
			view(); break;
		case '3': // ����� ���� ����������, ������� � ����������
			BROADCAST_INFO::expert(); break;
		case '4': // ������ ���� ������ �� �����
			BROADCAST_INFO::read(); break;
		case '5': // ������ ���� ������ �� �����
			BROADCAST_INFO::sort(); break;
		case '0': system("cls"); return; break; // �����
		default: cout << "\n����������� �������";
		} //end switch
	} //end while

}

void adminMenu()
{
	//system("cls");
	char ch;
	while (true)
	{
		cout << "'1' � ���������� �������� � ���� ������������"
			"\n'2' - ����� ������ � ����� �����������"
			"\n'3' - �������� ������ � ��������� �����"
			"\n'4' - �������������� ������"
			"\n'5' - �������� ������"
			"\n'6' � �������� ��� ������ � ����"
			"\n'7' � ��������� ��� ������ �� �����"
			"\n'8' � y��������� ��������������"
			"\n'9' � ������������ ����� ����������� ������� ���������������� ���������"
			"\n'0' - �����"
			"\n��� �����: ";
		cin >> ch;
		switch (ch)
		{
		case '1': // �������� ����� �����������
			system("cls"); BROADCAST_INFO::add(); system("cls"); break;
		case '2': // ������� ��� ��������
			system("cls"); BROADCAST_INFO::display(); system("cls"); break;
		case '3': // �������� ����������� ����������
			view(); system("cls"); break;
		case '4': // �������������� ������
			BROADCAST_INFO::edit(); system("cls"); break;
		case '5': // �������� ������
			BROADCAST_INFO::del(); system("cls"); break;
		case '6': // ������ � ����
			BROADCAST_INFO::write(); break;
		case '7': // ������ ���� ������ �� �����
			BROADCAST_INFO::read(); break;
		case '8': // 
			workWithUsers(); system("cls"); break;
		case '9': // ������ ���� ������ �� �����
			system("cls"); BROADCAST_INFO::expert(); break;
		case '0': system("cls"); return; break; // �����
		default: cout << "\n����������� �������";
		} //end switch
	} //end while

}

void mainMenu()
{
	WSAData wsaData;
	WORD DDLVersion = MAKEWORD(2, 1);//���������� max ����� ������ WinSock
	if (WSAStartup(DDLVersion, &wsaData) != 0) {
		cout << "error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//���������� IP-����� ����������
	addr.sin_port = htons(1280);//����,������� ����� ��������������� � �������
	addr.sin_family = AF_INET;//������
	cout << "Start listenin at port " << ntohs(addr.sin_port) << endl;
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);//�����-������ ��������,���-//����� ������ � ��������
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));//���������� ������ � �������
	listen(sListen, SOMAXCONN);//���������� � ��������-����� � //����.�������������;�������

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);//�������� //���������� ��� ��������� ������� ������� 
	if (newConnection == 0) {
		cout << "error #2" << endl;
		exit(1);
	}
	else {
		cout << "connection is established\n";
		cout << "New Client " << inet_ntoa(addr.sin_addr) << endl;
		char choise[256];
			recv(newConnection, choise, sizeof(choise), NULL);//���� ������ ����� ����� ������
			int x = atoi(choise);
			if (x == 1) {
				if (checkAdmin() == 0)
					cout << "\n������ �����\n";
				else
				{
					system("cls"); cout << "�� ����� ��� �������������\n";
					adminMenu();
				}
			}
			if (x == 2) {
				if (checkUser() == 0)
					cout << "\n������ �����\n";
				else
				{
					system("cls"); cout << "�� ����� ��� ������������\n";
					userMenu();
				}
			}
			if (x == 0) {
				return;
			}
			
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout.setf(ios::left);

	


	mainMenu();

	system("pause");
	return 0;
}
