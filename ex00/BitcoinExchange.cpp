//
// Created by pgouasmi on 2/15/24.
//

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const char *arg)
{
	/*handling _input*/
	if (!arg)
		throw FileNonOpenableException();
	this->_input.open(arg);
	if (!this->_input.is_open())
		throw FileNonOpenableException();

	/*handling csv*/
	this->_csv.open("data.csv");
	if (!this->_csv.is_open())
		throw FileNonOpenableException();
}

BitcoinExchange::~BitcoinExchange() {}

static std::string getKey(const std::string &line, int type)
{
	std::string result;

	if (!type)
		result = line.substr(0, line.find(","));
	else
		result = line.substr(0, line.find(" | "));

	return result;
}

double BitcoinExchange::getValue(const std::string &line, int type)
{
	double result;
	std::string temp;
	char *pEnd;

	if (!type)
		temp = line.substr(line.find(",") + 1);
	else
		temp = line.substr(line.find(" | ") + 3);
	const char *arr = temp.c_str();
	result = strtod(arr, &pEnd);
	if (pEnd[0])
		throw NotANumberException();
	else if  (result < 0)
		throw NotPositiveException();
	else
		return result;
}

static bool check_first(const std::string &line, const size_t i, int type)
{
	if (i != 0)
		return true ;
	if (type == 0)
		return (line != "date,exchange_rate");
	return (line != "date | value");
}

void	BitcoinExchange::scrapeCSV()
{
//	int error = 0;
	std::string line;
	std::string key;
	double value;
	size_t i = 0;

	while (std::getline(_csv, line))
	{
		if (check_first(line, i, 0))
		{
			if (line.empty())
				break;
			key = getKey(line, 0);
			this->getValue(line, 0);

//			std::cout << key << " " << value << std::endl;

			this->_datacsv.insert(std::pair<std::string, double>(key, value));
		}
		i++;
	}
}

static double getPrevious(std::string key, std::map<std::string, double> map)
{
	std::map<std::string, double>::iterator it = map.begin();
	std::map<std::string, double>::iterator prev;

	while (it != map.end() && it->first < key)
	{
//		std::cout << it->first << std::endl;
		prev = it;
		it++;
	}
	return prev->second;
}

void	BitcoinExchange::display()
{
	size_t i = 0;
	std::string line;
	std::string key;
	double ivalue;
	double cvalue;
	double result;
//	int error = 0;

	while (std::getline(this->_input, line))
	{
		if (check_first(line, i, 1))
		{
			key = getKey(line, 1);;
			ivalue = this->getValue(line, 1);

			if (ivalue < 0)
				throw NotPositiveException();
			else if (ivalue > 1000)
				throw TooLargeException();
//			else if (error)
//				throw NotANumberException();
			else
			{
				std::cout << key << " => " << ivalue << " = ";
				if (this->_datacsv.find(key) != this->_datacsv.end())
					cvalue = this->_datacsv.at(key);
				else
					cvalue = getPrevious(key, this->_datacsv);
				result = ivalue * cvalue;
				std::cout << result << std::endl;
			}
		}
		i++;
	}
}