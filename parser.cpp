// parser.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "ini_parser.h"

int main()
{
	try
	{
		ini_parser parser("file.ini");
		auto a = parser.get_value<int>("Section1.var1");
		std::cout << a << '\n';
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
	}

    return EXIT_SUCCESS;
}

