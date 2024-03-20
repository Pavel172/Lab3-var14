#include <iostream>
#include <string>
using namespace std;

class Bank //базовый класс
{
protected:
	string FIO;
	int sum;
	int deposit_rate;
	int years;
public:
	Bank() //пустой конструктор
	{
		FIO = "";
		sum = 0;
		deposit_rate = 0;
		years = 0;
	}
	Bank(string FIO, int sum, int deposit_rate, int years) //конструктор с начальными значениями
	{
		this->FIO = FIO;
		this->sum = sum;
		this->deposit_rate = deposit_rate;
		this->years = years;
	}
	double virtual sum_after_a_time() //функция подсчёта конечной суммы вклада и для демонстрации динамического полиморфизма
	{
		double temp = sum;
		for (int i = 0; i < years; ++i)
		{
			temp += temp * (deposit_rate * 0.01); //начисление процентов
		}
		return temp;
	}
	void print() //функция печати
	{
		cout << "ФИО: " << FIO << endl;
		cout << "Начальная сумма счёта: " << sum << endl;
		cout << "Ставка вклада(в %): " << deposit_rate << endl;
		cout << "Время существования вклада(в годах): " << years << endl;
	}
	~Bank() {} //деструктор
};

class preferred_Bank : public Bank //производный класс
{
protected:
	int credit;
public:
	preferred_Bank(): Bank() //пустой конструктор производного класса
	{
		credit = 0;
	}
	preferred_Bank(string FIO, int sum, int deposit_rate, int years, int credit) : Bank(FIO, sum, deposit_rate, years) //конструктор производного класса с начальными значениями
	{
		this->credit = credit;
	}
	double sum_after_a_time() //функция подсчёта конечной суммы вклада с учётом процентов кредита
	{
		double temp = Bank::sum_after_a_time(); //берём конечную сумму вклада
		temp += temp * (credit * 0.01); //начисляем процент кредита
		return temp;
	}
	void print() //функция печати производного класса
	{
		Bank::print();
		cout << "Процент кредита(в %): " << credit << endl;
	}
	~preferred_Bank() {} //деструктор производного класса
};

int main()
{
	setlocale(LC_ALL, "Rus");
	Bank* contrib = new Bank("FIO", 1000, 10, 3); //создание указателя на базовый класс с начальными значениями
	//Bank contrib("FIO", 1000, 10, 3); //создание базового класса
	double Sum1 = contrib->sum_after_a_time(); //сумма вклада после начисления всех % и демонстрация динамического полиморфизма
	contrib->print(); //демонстрация статического полиморфизма
	cout << "Сумма по окончании вклада (обычный счёт): " << Sum1 << endl << endl;
	preferred_Bank* contrib_pref = new preferred_Bank("FIO", 1000, 10, 3, 20);
	//preferred_Bank contrib_pref("FIO", 1000, 10, 3, 20); //создание производного класса
	double Sum2 = contrib_pref->sum_after_a_time(); //сумма вклада с кредитом после начисления всех %
	contrib_pref->print();
	cout << "Сумма по окончании вклада (привилегированный счёт): " << Sum2 << endl;
	return 0;
}