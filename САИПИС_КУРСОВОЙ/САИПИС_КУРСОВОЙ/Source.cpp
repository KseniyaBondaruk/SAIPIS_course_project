/*Программное средство для ранжирования проектов методом последовательных сравнений (на примере телстудии)*/

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

int id = 0;//счётчик для определения порядкового номера
const int MAXEM = 6;//максимальное число видов телепередач

void adminMenu();
void userMenu();
int checkAdmin();
int checkUser();
void mainMenu();
void workWithUsers();
void addUsers();
void deleteUsers();

void newHandler() {//не удалось выделить память
	cout << "Вызвана newHandler: ";
	throw bad_alloc();
}

class MyException : public exception
{
public:
	const char * what() const throw () {
		return "C++ Exception";
	}
};

class INFO_BASE {//базовый абстрактный класс
public:
	virtual void viewing() = 0;
};

class PRESUMED_INFO :public INFO_BASE {//прогнозы (предполагаемая информация)
public:
	int program_length;//предполагаемая длина телепередачи (в минутах)
	double tvr;//предполагаемый рейтинг 
	string airtime;//предпочтительное эфирное время
	void getdata()
	{
		cout << " Введите предполагаемую длину телепередачи в минутах: "; cin >> program_length;
		try {
			if (program_length <= 0) throw MyException();
		}
		catch (MyException& e) {
			cout << "Длина телепередачи не может быть меньше нуля" << endl;
		}
		cout << " Введите предполагаемай рейтинг: "; cin >> tvr;
		try {
			if (tvr <= 0 || tvr>100) throw MyException();//ошибка ввода
		}
		catch (MyException& e) {
			cout << "Рейтинг введён неверно" << endl;
		}
		cout << " Введите предпочтительное эфирное время: "; cin >> airtime;
	}
	void putdata()
	{
		cout << "\n Предполагаемая длина: " << program_length;
		cout << "\n Предполагаемай рейтинг: " << tvr;
		cout << "\n Предпочтительное эфирное время: " << airtime;
	}
	void viewing1()
	{
		cout << "|" << setw(9) << program_length << "|" << setw(7) << tvr << "|" << setw(13) << airtime << "|" ;
		cout << "\n|--------------------------------------------------------------------------|" << endl;
	}
	
};

class AUDIENCE_INFO :public INFO_BASE {//информация о целевой аудитории
public:
	string category;//возрастная категория
	int men;//процент зрителей мужского пола
	int women;//процент зрителей женского пола
	void getdata()
	{
		cout << " Введите возрастную категорию: "; cin >> category;
		cout << " Введите процент зрителей мужского пола: "; cin >> men;
		cout << " Введите процент зрителей женского пола: "; cin >> women;
		try {
			if (!women || !men) throw MyException();//ошибка ввода
		}
		catch (MyException& e) {
			cout << "MyException caught" <<endl;
			cout << e.what() << endl;
		}
	}
	void putdata()
	{
		cout << "\n Возрастная категория: " << category;
		cout << "\n Процент зрителей мужского пола: " << men;
		cout << "\n Процент зрителей женского пола: " << women;
	}
	void viewing2()
	{
		cout << "|" << setw(20) << category << "|" << setw(19) << men << "|" << setw(19) << women << "|" ;
		cout << "\n|-------------------------------------------------------------------------------------------------------|" << endl;
	}
	
};

class DECORATIONS_INFO :public INFO_BASE {//информация о декорациях
public:
	int prodaction;//срок изготовления декораций (в неделях)
	int cost;//стоимость декораций
	void getdata()
	{
		cout << " Введите срок изготовления декораций (в неделях): "; cin >> prodaction;
		try {
			if (!prodaction) throw MyException();//ошибка ввода
		}
		catch (MyException& e) {
			cout << "MyException caught" << endl;
			cout << e.what() << endl;
		}
		cout << " Введите стоимость декораций: "; cin >> cost;
		try //используемое значение вне допустимого диапазона
		{
			if (cost <= 0.0)
				throw MyException();//ошибка ввода
		}
		catch (MyException& e) {
			cout << "Стоимость декораций не может быть меньше нуля" << endl;
		}
	}
	void putdata()
	{
		cout << "\n Срок изготовления декораций (в неделях): " << prodaction;
		cout << "\n Стоимость декораций: " << cost;
	}
	void viewing3()
	{
		cout << "|"  << setw(21 ) << prodaction << "|" << setw(18) << cost << "|";
		cout << "\n|-----------------------------------------------------------------------------------|" << endl;
	}
	
};

class BROADCAST_INFO :public  PRESUMED_INFO , public AUDIENCE_INFO, public DECORATIONS_INFO{//информация о телепередаче
public:
	int serial_number;//порядковый номер
	string type;//вид телепередачи
	int anchormen;//количество ведущих
	string viewers;//наличие зрителей в студии (да/нет)
	int estimate;//экспертная оценка
	static int n; // текущее число проектов
	static BROADCAST_INFO* arrap[]; //массив указателей на класс информации о телепередаче
	void getdata()
	{
		serial_number = id;
		cout << " Введите вид телепередачи: "; cin >> type;
		cout << " Введите количество ведущих: "; cin >> anchormen;
		cout << " В студии будут находиться зрители?: "; cin >> viewers;
		PRESUMED_INFO::getdata();
		AUDIENCE_INFO::getdata();
		DECORATIONS_INFO::getdata();
	}
	void getestimation()
	{
		cout << "\n ВВЕДИТЕ ЭКСПЕРТНУЮ ОЦЕНКУ: "; cin >> estimate;
		try {
			if (!estimate) throw MyException();//ошибка ввода
		}
		catch (MyException& e) {
			cout << "MyException caught" << endl;
			cout << e.what() << endl;
		}
	}
	void putdata()
	{
		cout << "Вид телепередачи: " << type;
		cout << "\n Количество ведущих: " << anchormen;
		cout << "\n Наличие зрителей в студии: " << viewers;
		PRESUMED_INFO::putdata();
		AUDIENCE_INFO::putdata();
		DECORATIONS_INFO::putdata();
	}
	static void expert(); // ранжирование
	static void add(); // добавление
	static void display(); // вывод отчета
	static void del();// удаление
	static void edit(); // редактирование
	static void read(); // чтение из файла
	friend void view();// просмотр
	static void write(); // запись в файл
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

int BROADCAST_INFO::n; // текущее число проектов
BROADCAST_INFO* BROADCAST_INFO::arrap[MAXEM]; // массив указателей на класс информации о телепередаче

class users//пользователи
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
		mp[arrap[i]->estimate] = i;  // добавляем новые элементы
	}

	map <int, int> ::iterator it = mp.begin();
	for (int i = 0; it != mp.end(); it++, i++) {  // выводим их
		cout << i+1 << ") оценка " << it->first << ", вид " << it->second + 1<< endl;
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
					cout << array[i] << "+" << array[j] << endl << "Согласны? (1-да, 2-нет)" << endl;
					cin >> agree.agreement;
					if (agree.agreement == 2) { 
						map <int,int> ::iterator full_name;
					full_name = mp.find(array[index - 1]); 
					int sec = full_name->second;
						cout << " Скорректируйте оценку: "; 
						cin >> array[index - 1]; 
						mp.emplace(array[index - 1], sec);
						mp.erase(full_name);
					}
				}
		cout << endl;
	}

	cout << "По возрастанию: " << endl;
	map <int, int> ::iterator itt = mp.begin();
	for (int i = 1; itt != mp.end(); itt++, i++) {  // выводим их
		cout << i << ") вид " << itt->second + 1 << " - ";
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
			cout << "\n1-продолжить вводить данные, 2-выход в меню 2-го уровня\n";
			cin >> ch;
		} while (ch != '2'); 
} 

void BROADCAST_INFO::del()
{
	system("cls");
	int flag;
	BROADCAST_INFO r; r.view_all();
	cout << "\nВведите порядковый номер телпередачи, которую требуется удалить:";
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
			cout << "\nвведите инвентарный номер периодического издания, сведения о котором вы хотите изменить:";
			int num;  cin >> num;
			char choise; string s; int t; arrap[n] = new BROADCAST_INFO;
			do {
				cout << "Какое поле вы хотите отредактировать?:"
					"\n'1' - вид телепередачи"
					"\n'2' - количество ведущих"
					"\n'3' - наличие зрителей в студии"
					"\n'4' - предполагаемая длина"
					"\n'5' - предполагаемый рейтинг"
					"\n'6' - предпочтительное эфирное время"
					"\n'7' - возрастная категория"
					"\n'8' - процент зрителей мужского пола"
					"\n'9' - процент зрителей женского пола"
					"\n'10' - срок изготовления декораций"
					"\n'11' - стоимость декораций"
					"\n'0' - выход в меню 2-го уровня"
					"\nВаш выбор: ";
				cin >> choise;
				switch (choise) {
				case '1': {cout << "Введите вид телепередачи:";
					cin >> s;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->type = s; }break;
				case '2': {cout << "Введите количество ведущих:";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
						((BROADCAST_INFO *)arrap[i])->anchormen = t; }break;
				case '3': {cout << "В студии будут находиться зрители?:";
					cin >> s;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->viewers = s;
				}break;
				case '4': {cout << "Введите предполагаемую длину (в минутах):";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->program_length = t; }break;
				case '5': {cout << "Введите предполагаемый рейтинг:";
					double h; cin >> h;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->tvr = h;
				}break;
				case '6': {cout << "Введите предпочтительное эфирное время:";
					cin >> s;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->airtime = s;
				}break;
				case '7': {cout << "Введите возрастную категорию:";
					cin >> s;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->category = s;
				}break;
				case '8': {cout << "Введите процент зрителей мужского пола:";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->men = t;
				}break;
				case '9': {cout << "Введите процент зрителей женского пола:";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->women = t;
				}break;
				case '10': {cout << "Введите срок изготовления декораций:";
					cin >> t;
					for (int i = 0; i < n; i++)
						if (((BROADCAST_INFO *)arrap[i])->serial_number == num)
							((BROADCAST_INFO *)arrap[i])->prodaction = t; }break;
				case '11': {cout << "Введите стоимость декораций:";
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
		"\n|Порядковый номер|Вид телепередачи         |Количество ведущих|Наличие зрителей|"
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
		"\n|Порядковый номер|Вид телепередачи         |Срок изготовления,нед|Стоимость,бел.руб.|"
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
		"\n|Порядковый номер|Вид телепередачи         |Возрастная категория|Мужская аудитория,%|Женская аудитория,%|"
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
		"\n|Порядковый номер|Вид телепередачи         |Длина,мин|Рейтинг|Эфирное время|"
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
		cout << "\nПросмотреть таблицу:"
			"\n'1' - видов телепередач"
			"\n'2' - информации о декорациях"
			"\n'3' - информации о целевой аудитории"
			"\n'4' - предполагаемой информации"
			"\n'0' - выход в меню 2-го уровня"
			"\nВаш выбор: ";
		cin >> ch;
		switch (ch)
		{
		case '1': {i.view_all(); } break;
		case '2': {i.view_decorations(); }break;
		case '3': {i.view_audience(); }break;
		case '4': {i.view_presume(); }break;
		case '0':system("cls"); return; break;
		default: printf("\nДанного пункта меню не существует!\n");
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

}//сортировка телепередач по рейтингу

void BROADCAST_INFO::read()
{
	int size; // размер объекта
	ifstream inf; // открыть ifstream в двоичном виде
	inf.open("C:\\Users\\ThinkPad\\source\\repos\\САИПИС_КУРСОВОЙ\\maindata.dat", ios::in | ios::binary);
	if (!inf)
	{
		cout << "\nНевозможно открыть файл\n"; return;
	}
	n = 0; // В памяти поступлений нет
	while (true)
	{ 
		if (inf.eof()) // выход из цикла по EOF
			break;
		if (!inf) // ошибка чтения типа
		{
			cout << "\nНевозможно чтение типа\n"; return;
		}
		
			arrap[n] = new BROADCAST_INFO;
			size = sizeof(BROADCAST_INFO);
			for (int i = 0; i < n; i++)
				id = ((BROADCAST_INFO *)arrap[i])->serial_number;
			id++;
			
		inf.read((char*)arrap[n], size);
		if (!inf) // ошибка, но не EOF
		{
			cout << "\nЧтение данных из файла невозможно\n"; return;
		}
		//id = n;
		n++; // счетчик поступлений увеличить
	} //end while
	inf.close();
	cout << "Идет чтение " << n << " телепередач\n";
}

void BROADCAST_INFO::display()
{
	for (int j = 0; j < n; j++)
	{
		cout << arrap[j]->serial_number << ". ";
		arrap[j]->putdata(); // Вывод данных
		cout << endl;
	}
}

void BROADCAST_INFO::write()
{
	int size;
	cout << "Идет запись " << n << " телепередач.\n";
	ofstream ouf; // открыть ofstream в двоичном виде
	ouf.open("C:\\Users\\ThinkPad\\source\\repos\\САИПИС_КУРСОВОЙ\\maindata.dat", ios::out | ios::ate | ios::binary);
	if (!ouf)
	{
		cout << "\nНевозможно открыть файл\n"; return;
	}
	for (int j = 0; j < n; j++) // Для каждого объекта
	{ size = sizeof(BROADCAST_INFO);
		 
		ouf.write((char*)(arrap[j]), size);//запись объекта в файл
		if (!ouf)
		{
			cout << "\nЗапись в файл невозможна\n"; return;
		}
	}
	ouf.close();
}

//---------------------------------------------------------
//функция проверки логина и пароля для администратора
int checkAdmin()

{
	char login[20], password[20], rightLogin[20], rightPassword[20];
	ifstream fin("C:\\Users\\ThinkPad\\source\\repos\\САИПИС_КУРСОВОЙ\\admindata.txt", ios::in); // Открытие файла для чтения
	if (!fin.is_open()) cout << "Указанный файл не существует!" << endl;
	else
	{
		while (!fin.eof())
		{
			fin >> rightLogin >> rightPassword;
		}
	}
	for (int i = 0; i < strlen(rightPassword); i++)
		rightPassword[i] -= 3;
	cout << "Введите логин: ";
	cin >> login;
	cout << "Введите пароль: ";
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
		fin.close(); //Закрытие файла
		return 1;
	}
	fin.close();
	return 0;
}
//---------------------------------------------------------
//функция проверки логина и пароля для пользователя
int checkUser()
{
	char login[20], password[20];
	ifstream inf;
	int i, n = 0;
	users *p;
	inf.open("C:\\Users\\ThinkPad\\source\\repos\\САИПИС_КУРСОВОЙ\\userdata.txt", ios::in | ios::ate);
	if (!inf) { cout << "\nНевозможно открыть файл\n"; return 0; }
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

	cout << "Введите логин: ";
	cin >> login;
	cout << "Введите пароль: ";
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
//активирование(добавление) пользователей
void addUsers()
{

	char ch;
	ifstream inf;
	inf.open("C:\\Users\\ThinkPad\\source\\repos\\САИПИС_КУРСОВОЙ\\userdata.txt", ios::in);
	if (!inf) { cout << "\nНевозможно открыть файл\n"; return; }
	while (true)
	{
		inf.read((char*)&USER, sizeof(USER));
		if (inf.eof()) // выход из цикла по EOF
			break;
	}
	inf.close();
	ofstream ouf;
	ouf.open("C:\\Users\\ThinkPad\\source\\repos\\САИПИС_КУРСОВОЙ\\userdata.txt", ios::out | ios::app);
	if (!ouf) { cout << "\nНевозможно открыть файл\n"; return; }
	do
	{
		cout << "\nlogin для нового пользователя: ";
		cin >> USER.login;
		cout << "\npassword для нового пользователя: ";
		cin >> USER.password;
		for (int i = 0; i < strlen(USER.password); i++)
			USER.password[i] += 3;
		ouf.write((char*)&USER, sizeof(USER));
		printf("\n1-продолжить вводить данные, 2-выход в меню управления пользователями");
		cin >> ch;
	} while (ch != '2');
	ouf.close();

}
//---------------------------------------------------------
//блокировка(удаление) пользователя
void deleteUsers()
{
	ifstream inf;
	int i, j = 1, n = 0;
	char flag[20];
	users *p, buff;
	inf.open("C:\\Users\\ThinkPad\\source\\repos\\САИПИС_КУРСОВОЙ\\userdata.txt", ios::in | ios::ate);
	if (!inf) { cout << "\nНевозможно открыть файл\n"; return; }
	n = inf.tellg() / sizeof(USER);
	inf.seekg(0);
	p = new users[n * sizeof(USER)];
	cout << "\n|ЛОГИН        |"
		"\n|-------------|";
	for (i = 0; i < n; ++i)
	{
		inf.read((char*)&USER, sizeof(USER));
		p[i] = USER;
		cout << "\n|" << setw(13) << p[i].login << "|";
	}
	cout << "\n|-------------|";
	inf.close();
	cout << "\nВведите логин пользователя, которого хотите удалить";
	cin >> flag;
	ofstream ouf;
	ouf.open("C:\\Users\\ThinkPad\\source\\repos\\САИПИС_КУРСОВОЙ\\userdata.txt", ios::out | ios::ate);
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
//меню управления пользователями
void workWithUsers()
{
	system("cls");
	char choise;
	do
	{
		cout << "'1' – Добавить пользователей"
			"\n'2' - Удалить пользователя"
			"\n'0' - Выход в меню администратора"
			"\nВаш выбор: ";
		cin >> choise;
		switch (choise)
		{
		case '1': system("cls"); addUsers();  break;
		case '2': system("cls"); deleteUsers(); break;
		case '0': system("cls"); return; break;
		default: cout << "\nДанного пункта меню не существует!\n";
		}
	} while (choise != '0');
}

void userMenu()
{
	system("cls");
	char ch;
	while (true)
	{
		cout << "\n'1' - вывод отчёта о видах телепередач"
			"\n'2' - просмотр данных в табличной форме"
			"\n'3' – ранжирование видов телепередач методом последовательных сравнений"
			"\n'4' – прочитать все данные из файла"
			"\n'5' – сортировка телепередач по рейтингу"
			"\n'0' - выход"
			"\nВаш выбор: ";
		cin >> ch;
		switch (ch)
		{
		case '1': // вывести все сведения
			BROADCAST_INFO::display(); break;
		case '2': // просмотр необходимой информации
			view(); break;
		case '3': // вызов меню сортировок, поисков и фильтраций
			BROADCAST_INFO::expert(); break;
		case '4': // чтение всех данных из файла
			BROADCAST_INFO::read(); break;
		case '5': // чтение всех данных из файла
			BROADCAST_INFO::sort(); break;
		case '0': system("cls"); return; break; // выход
		default: cout << "\nНеизвестная команда";
		} //end switch
	} //end while

}

void adminMenu()
{
	//system("cls");
	char ch;
	while (true)
	{
		cout << "'1' – добавление сведений о виде телепередачи"
			"\n'2' - вывод отчёта о видах телепередач"
			"\n'3' - просмотр данных в табличной форме"
			"\n'4' - редактирование данных"
			"\n'5' - удаление данных"
			"\n'6' – записать все данные в файл"
			"\n'7' – прочитать все данные из файла"
			"\n'8' – yправление пользователями"
			"\n'9' – ранжирование видов телепередач методом последовательных сравнений"
			"\n'0' - выход"
			"\nВаш выбор: ";
		cin >> ch;
		switch (ch)
		{
		case '1': // записать новое поступление
			system("cls"); BROADCAST_INFO::add(); system("cls"); break;
		case '2': // вывести все сведения
			system("cls"); BROADCAST_INFO::display(); system("cls"); break;
		case '3': // просмотр необходимой информации
			view(); system("cls"); break;
		case '4': // редактирование данных
			BROADCAST_INFO::edit(); system("cls"); break;
		case '5': // удаление данных
			BROADCAST_INFO::del(); system("cls"); break;
		case '6': // запись в файл
			BROADCAST_INFO::write(); break;
		case '7': // чтение всех данных из файла
			BROADCAST_INFO::read(); break;
		case '8': // 
			workWithUsers(); system("cls"); break;
		case '9': // чтение всех данных из файла
			system("cls"); BROADCAST_INFO::expert(); break;
		case '0': system("cls"); return; break; // выход
		default: cout << "\nНеизвестная команда";
		} //end switch
	} //end while

}

void mainMenu()
{
	WSAData wsaData;
	WORD DDLVersion = MAKEWORD(2, 1);//определяет max номер версии WinSock
	if (WSAStartup(DDLVersion, &wsaData) != 0) {
		cout << "error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//физический IP-адрес компьютера
	addr.sin_port = htons(1280);//порт,который будет ассоциироваться с сокетом
	addr.sin_family = AF_INET;//всегда
	cout << "Start listenin at port " << ntohs(addr.sin_port) << endl;
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);//домен-адреса Интернет,тип-//сокет потока и протокол
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));//связывание адреса с сокетом
	listen(sListen, SOMAXCONN);//соединение с клиентом-сокет в //сост.прослушивания;запросы

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);//открытие //соединения при получении запроса клиента 
	if (newConnection == 0) {
		cout << "error #2" << endl;
		exit(1);
	}
	else {
		cout << "connection is established\n";
		cout << "New Client " << inet_ntoa(addr.sin_addr) << endl;
		char choise[256];
			recv(newConnection, choise, sizeof(choise), NULL);//приём данных через сокет потока
			int x = atoi(choise);
			if (x == 1) {
				if (checkAdmin() == 0)
					cout << "\nошибка входа\n";
				else
				{
					system("cls"); cout << "ВЫ ВОШЛИ КАК АДМИНИСТРАТОР\n";
					adminMenu();
				}
			}
			if (x == 2) {
				if (checkUser() == 0)
					cout << "\nошибка входа\n";
				else
				{
					system("cls"); cout << "ВЫ ВОШЛИ КАК ПОЛЬЗОВАТЕЛЬ\n";
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
