#pragma once

#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>

class ini_parser
{
private:
	std::map<std::string, std::map<std::string, std::string>> myMap;	// map ��� �������� ������
	unsigned int stringCounter{};	// ������� ����� ini �����
	std::ifstream file;		// ����

	void readFile(std::string fileName);	// ������ ������ �� �����

	std::string readSection(std::string& tempString, int& i);	// ������ ����� ������

	std::string readVarName(std::string& tempString, int& i);	// ������ ����� ����������

	std::string readValue(std::string& tempString, int& i);		// ������ �������� ����������

	std::string getString(std::string str);		// ��������� �������� ���������� � ���� ������

	void printVarList(std::string sectionName);	// ����� �� ����� ������ ���������� ������������ ������

	std::string cutString(std::string& str);		// ��������� ������

public:

	ini_parser(std::string fileName);	// �����������

	void checkFloatingPointInNumber(std::string& str);

	// ������ ��������� �������� ���������� ���������� ����
	
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
			// ������ �������� �������������� ����� � ��������� ������ � �����
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

