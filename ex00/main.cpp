#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	(void)argc;

	BitcoinExchange *handler;

	try {
		handler = new BitcoinExchange(argv[1]);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	try {
		handler->scrapeCSV();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try {
		handler->display();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	delete handler;

}