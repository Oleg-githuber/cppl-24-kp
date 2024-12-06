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

	double convertString(std::string str);		// Преобразование строки в число

	void cutString(std::string& str);		// Обрезание строки

public:

	ini_parser(std::string fileName);	// Конструктор

	// Шаблон получения значения переменной выбранного типа
	template<typename T>
	T get_value(std::string str)
	{
		std::string strValue{};
		try
		{
			strValue = getString(str);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << '\n';
		}

		try
		{
			return static_cast<T>(convertString(strValue));
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << '\n';
		}
	}
};

