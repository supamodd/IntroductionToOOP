#include<iostream>
using namespace std;
#define delimiter "-------------------------------"

class String
{
	int size;	//Размер строки в Байтах
	char* str;	//Указатель на строку в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}

	//								Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstructor:\t" << this << endl;
	}
	String(const char str[])
	{
		while (str[size++]);
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++)this->str[i] = str[i];
		cout << "Constructor:\t\t" << this << endl;
	}
	String(const String& other)
	{
		//Конструктор копирования должен DeepCopy(Побитовое копирование)
		//т.е. выделять динамическую память под обьект и побитово (поэлементно)
		//копировать содержимое динамической памяти из существующего обьекта в создаваемый
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	} 
	~String()
	{
		delete[] str;
		this->str = nullptr;
		this->size = 0;
		cout << "Destructor:\t\t" << this << endl;
	}
	//								Operators:
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment\t\t" << this << endl;
	}

	String operator+(const String& other) const
	{
		String result(size + other.size - 1);
		strcpy_s(result.str, result.size, this->str);
		strcat_s(result.str, result.size, other.str);
		return result;
	}

	String& operator+=(const String& other)
	{
		size += other.size - 1;
		char* new_str = new char[size] {};

		strcpy_s(new_str, size, this->str);
		strcat_s(new_str, size, other.str);

		delete[] this->str;

		this->str = new_str;

		return *this;
	}

	//									Methods:
	void info()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
	friend ostream& operator<<(ostream& os, const String& obj);
	friend istream& operator>>(istream& is, String& obj);
};

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

istream& operator>>(istream& is, String& obj)
{
	const int SIZE = 256; // Максимальный размер вводимой строки
	char buffer[SIZE] = {};
	is.getline(buffer, SIZE);	// Считат строку из входного потока
	//вместо создания нового обьекта создаем временый и присваиваем его существующему
	String temp(buffer);
	obj = temp;
	return is;
}

void main()
{
	setlocale(LC_ALL, "");
	String str1(5);	//explicit-конструктор нельзя вызвать оператором присвоить, но всегда можно вызвать при помощи круглых скобок
	str1.info();
	cout << str1 << endl;

	String str2 = "Hello";
	cout << str2 << endl;

	String str3 = str2;		//CopyConstructor
	cout << str3 << endl;

	String str4;
	str4 = str3;
	cout << str4 << endl;

	cout << delimiter << endl;
	String str5 = "World";
	String str6 = str2 + str5;
	cout << str6 << endl;

	cout << delimiter << endl;
	str2 += str5;
	cout << str2 << endl;

	cout << delimiter << endl;
	String str7;
	cout << "Введите строку: "; cin >> str7;
	cout << str7 << endl;
}