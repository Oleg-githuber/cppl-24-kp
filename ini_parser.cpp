#include "ini_parser.h"

/// <summary>
/// �����������
/// </summary>
/// <param name="fileName">��� �����</param>
ini_parser::ini_parser(std::string fileName): stringCounter{}
{
	readFile(fileName);
}

/// <summary>
/// ������ ������ �� �����
/// </summary>
/// <param name="fileName">��� �����</param>
void ini_parser::readFile(std::string fileName)
{
	file.open(fileName);
	if (!file.is_open())
	{
		throw std::exception("File not found!");
	}
	std::string tempString{};
	std::string sectionName{};
	char ch{};

	while (!file.eof())
	{
		std::string varName{};
		std::string value{};
		std::getline(file, tempString);
		++stringCounter;

		for (int i{}; i < tempString.length(); ++i)
		{
			ch = tempString[i];
			if (ch == ';')
			{
				break;
			}
			if ((ch == ' ') || (ch == '\t'))
			{
				continue;
			}
			if (ch == '[')
			{
				sectionName = readSection(tempString, i);
				continue;
			}
			if (ch == ']')
			{
				std::string str{ "Expected \"[\" before \"]\"! Line " + std::to_string(stringCounter) };
				throw std::exception(str.c_str());
			}
			if (ch != ';')
			{
				varName = readVarName(tempString, i);
				value = readValue(tempString, i);
			}
		}

		// ������ �� ��������������� ����������
		if (myMap.find(sectionName) != myMap.end())
		{
			if (!myMap[sectionName].empty())
			{
				if (myMap[sectionName].find(varName) != myMap[sectionName].end())
				{
					std::string str{ "Duplicate of variable! Line " + std::to_string(stringCounter) };
					throw std::exception(str.c_str());
				}
			}
		}

		if (!varName.empty() && !value.empty())
		{
			myMap[sectionName].insert(std::pair<std::string, std::string>(varName, value));
		}
	}
	file.close();
}

/// <summary>
/// ������ ����� ������
/// </summary>
/// <param name="tempString">������ �� ini-�����</param>
/// <param name="i">����� ������� �� �����</param>
/// <returns></returns>
std::string ini_parser::readSection(std::string& tempString, int& i)
{
	char ch{};
	std::string sectionName{};
	++i;
	while (i < tempString.length())
	{
		ch = tempString[i];
		if (ch == ']')
		{
			break;
		}
		if ((ch == '\n') || (ch == ' ') || (ch == '\t') || (ch == ';'))
		{
			std::string str{ "Incorrect section name! Line " + std::to_string(stringCounter) };
			throw std::exception(str.c_str());
		}
		if (i == tempString.length() - 1)
		{
			std::string str{ "Expected \"]\"! Line " + std::to_string(stringCounter) };
			throw std::exception(str.c_str());
		}
		sectionName = sectionName + ch;
		++i;
	}
	return sectionName;
}

/// <summary>
/// ������ ����� ����������
/// </summary>
/// <param name="tempString">������ �� ini-�����</param>
/// <param name="i">����� ������� � ������</param>
/// <returns></returns>
std::string ini_parser::readVarName(std::string& tempString, int& i)
{
	bool doWaitEqual{};
	std::string varName{};
	char ch{};
	while (i < tempString.length())
	{
		ch = tempString[i];

		if (ch == '=')
		{
			return varName;
		}
		if (!doWaitEqual && ((ch == ' ') || (ch == '\t')))
		{
			doWaitEqual = true;
			++i;
			continue;
		}
		if (doWaitEqual && ((ch != ' ') || (ch != '\t')))
		{
			std::string str{ "Name of variable can not contain space!! Line " + std::to_string(stringCounter) };
			throw std::exception(str.c_str());
		}
		if (!doWaitEqual)
		{
			varName = varName + ch;
		}
		++i;
	}
	std::string str{ "Name of variable can not contain space!! Line " + std::to_string(stringCounter) };
	throw std::exception(str.c_str());
}

/// <summary>
/// ������ �������� ����������
/// </summary>
/// <param name="tempString">������ �� ini-�����</param>
/// <param name="i">����� ������� � ������</param>
/// <returns></returns>
std::string ini_parser::readValue(std::string& tempString, int& i)
{
	std::string value{};
	char ch{};
	++i;
	while (i < tempString.length())
	{
		ch = tempString[i];
		if (ch == ';')
		{
			if (value.empty())
			{
				std::string str{ "Empty value!! Line " + std::to_string(stringCounter) };
				throw std::exception(str.c_str());
			}
			i = static_cast<int>(tempString.length());
			return value;
		}
		value = value + ch;
		++i;
	}
	if ((i >= tempString.length()) && (value.empty()))
	{
		std::string str{ "Empty value!! Line " + std::to_string(stringCounter) };
		throw std::exception(str.c_str());
	}
	cutString(value);
	return value;
}

/// <summary>
/// ��������� �������� ���������� � ���� ������
/// </summary>
/// <param name="str">���_������.���_����������</param>
/// <returns>�������� ����������</returns>
std::string ini_parser::getString(std::string str)
{
	std::string sectionName{};
	std::string varName{};
	bool isVarName{};
	for (int i{}; i < str.length(); ++i)
	{
		if (!isVarName)
		{
			if (str[i] == '.')
			{
				isVarName = true;
				continue;
			}
			sectionName = sectionName + str[i];
		}
		if (isVarName)
		{
			if (str[i] == '.')
			{
				throw std::exception("Incorrect parameter of function get_value()!");
			}
			varName = varName + str[i];
		}
	}
	if (myMap.find(sectionName) == myMap.end())
	{
		throw std::exception("Incorrect section name!");
	}
	if (myMap[sectionName].find(varName) == myMap[sectionName].end())
	{
		std::cout << "You entered incorrect variable name. You need to enter one of the list:\n";
		printVarList(sectionName);
		throw std::exception("Incorrect parameter!");
	}
	return myMap[sectionName][varName];
}

/// <summary>
/// ����� �� ����� ���� ���������� ��������� ������
/// </summary>
/// <param name="sectionName">��� ������</param>
void ini_parser::printVarList(std::string sectionName)
{
	std::map<std::string, std::string>::iterator it{ myMap[sectionName].begin() };
	while (it != myMap[sectionName].end())
	{
		std::cout << it->first << '\n';
	}
}

/// <summary>
/// ��������� �������� � ������ � � ����� ������
/// </summary>
/// <param name="str">������</param>
std::string ini_parser::cutString(std::string& str)
{
	size_t startLetter{};
	size_t finalLetter{};
	for (size_t i{}; i < str.length(); ++i)
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			startLetter = i;
		}
	}
	for (size_t i{str.length() - 1}; i < str.length(); --i)
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			finalLetter = i;
		}
	}
	return str.substr(startLetter, str.length() - finalLetter);
}

void ini_parser::checkFloatingPointInNumber(std::string& str)
{
	for (char c : str)
	{
		if (c == '.')
		{
			throw std::exception("Value has floating point!");
		}
	}
}