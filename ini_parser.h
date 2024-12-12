#pragma once

#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>

class ini_parser
{
private:
	std::map<std::string, std::map<std::string, std::string>> myMap;	// map для хранения данных
	unsigned int stringCounter{};	// Счётчик строк ini файла
	std::ifstream file;		// Файл

	void readFile(std::string fileName);	// Чтение данных из файла

	std::string readSection(std::string& tempString, int& i);	// Чтение имени секции

	std::string readVarName(std::string& tempString, int& i);	// Чтение имени переменной

	std::string readValue(std::string& tempString, int& i);		// Чтение значения переменной

	std::string getString(std::string str);		// Получение значения переменной в виде строки

	void printVarList(std::string sectionName);	// Вывод на экран списка переменных определенной секции

	std::string cutString(std::string& str);		// Обрезание строки

public:

	ini_parser(std::string fileName);	// Конструктор

	void checkFloatingPointInNumber(std::string& str);

	// Шаблон получения значения переменной выбранного типа
	
	template<typename T>
	T get_value(std::string str)
	{
		//static_assert(sizeof(T) == -1, "Not implemented type for get_value!");
		if (sizeof(T) == -1)
		{
			throw std::exception("Not implemented type for get_value!");
		}
		throw std::exception("Type of get_value() is not correct!");
	} 

	template<>
	double get_value(std::string str)
	{
		double number{};
		if (number = std::stod(getString(str)))
		{
			return number;
		}
		throw std::exception("Value is not double!");
	}

	template<>
	float get_value(std::string str)
	{
		float number{};
		if (number = std::stof(getString(str)))
		{
			return number;
		}
		throw std::exception("Value is not float!");
	}

	template<>
	int get_value(std::string str)
	{
		int number{};
		std::string str1{ getString(str) };
		if (number = std::stoi(str1))
		{
			// Запрет неявного преобразования числа с плавающей точкой в целое
			checkFloatingPointInNumber(str);
			return number;
		}
		throw std::exception("Value is not integer!");
	}

	template<>
	unsigned int get_value(std::string str)
	{
		int number{ get_value<int>(str)};
		if (number < 0)
		{
			throw std::exception("Value is not unsigned!");
		}
		return static_cast<unsigned int>(number);
	}

	template<>
	long get_value(std::string str)
	{
		long number{};
		if (number = std::stol(getString(str)))
		{
			checkFloatingPointInNumber(str);
			return number;
		}
		throw std::exception("Value is not long!");
	}

	template<>
	unsigned long get_value(std::string str)
	{
		long number{ std::stol(getString(str)) };
		if (number < 0)
		{
			throw std::exception("Value is not unsigned!");
		}
		return static_cast<unsigned long>(number);
	}

	template<>
	long long get_value(std::string str)
	{
		long long number{};
		if (number = std::stoll(getString(str)))
		{
			checkFloatingPointInNumber(str);
			return number;
		}
		throw std::exception("Value is not long long!");
	}

	template<>
	unsigned long long get_value(std::string str)
	{
		long long number{ std::stoll(getString(str)) };
		if (number < 0)
		{
			throw std::exception("Value is not unsigned!");
		}
		return static_cast<unsigned long long>(number);
	}

	template<>
	std::string get_value(std::string str)
	{
		return getString(str);
	}
};

