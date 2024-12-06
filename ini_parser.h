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

	double convertString(std::string str);		// �������������� ������ � �����

	void cutString(std::string& str);		// ��������� ������

public:

	ini_parser(std::string fileName);	// �����������

	// ������ ��������� �������� ���������� ���������� ����
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

