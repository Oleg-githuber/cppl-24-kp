#pragma once

#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#define LOW_DIGITAL_BOUND 48
#define HIGH_DIGITAL_BOUND (LOW_DIGITAL_BOUND + 9)

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

	std::string varList(std::string sectionName);	// Вывод на экран списка переменных определенной секции

	std::string cutString(std::string& str);		// Обрезание строки

	/// <summary>
	/// Запрет неявного преобразования числа с плавающей точкой в целое
	/// </summary>
	/// <param name="str"></param>
	void checkFloatingPointInNumber(std::string& str);
	/// <summary>
	/// Проверка на содержание символов, отличных от цыфр
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="str"></param>
	/// <returns></returns>
	void checDigitsInString(std::string& str);

public:

	ini_parser(std::string fileName);	// Конструктор

	// Шаблон получения значения переменной выбранного типа
	
	template<typename T>
	T get_value(std::string str)
	{
		//static_assert(sizeof(T) == -1, "Not implemented type for get_value!");
		throw std::exception("Type of get_value() is not correct!");
	} 

	// Специализации шаблона

	template<>
	double get_value(std::string str)
	{
		std::string strValue{ getString(str) };
		checDigitsInString(strValue);
		return std::stod(strValue);
	}

	template<>
	float get_value(std::string str)
	{
		std::string strValue{ getString(str) };
		checDigitsInString(strValue);
		return std::stof(strValue);
	}

	template<>
	int get_value(std::string str)
	{
		std::string strValue{ getString(str) };
		checDigitsInString(strValue);
		checkFloatingPointInNumber(strValue);
		return std::stoi(strValue);
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
		std::string strValue{ getString(str) };
		checDigitsInString(strValue);
		checkFloatingPointInNumber(strValue);
		return std::stol(strValue);
	}

	template<>
	unsigned long get_value(std::string str)
	{
		long number{ get_value<long>(str) };
		if (number < 0)
		{
			throw std::exception("Value is not unsigned!");
		}
		return static_cast<unsigned long>(number);
	}

	template<>
	long long get_value(std::string str)
	{
		std::string strValue{ getString(str) };
		checDigitsInString(strValue);
		checkFloatingPointInNumber(strValue);
		return std::stoll(strValue);
	}

	template<>
	unsigned long long get_value(std::string str)
	{
		long long number{ get_value<long long>(str) };
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

