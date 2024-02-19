/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:15:40 by pgouasmi          #+#    #+#             */
/*   Updated: 2024/02/19 14:15:40 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

std::string BitcoinExchange::getValue(const std::string &line, int type)
{
	std::string result;

	if (!type)
		result = line.substr(line.find(",") + 1);
	else {
		result = line.substr(line.find(" | ") + 3);
		if (result.empty())
			throw BadInputException();
	}
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
	std::string line;
	std::string key;
	std::string value;
	size_t i = 0;

	while (std::getline(_csv, line))
	{
		if (check_first(line, i, 0))
		{
			if (line.empty())
				break;
			key = getKey(line, 0);
			value = this->getValue(line, 0);

//			std::cout << key << " " << value << std::endl;

			this->_datacsv.insert(std::pair<std::string, std::string>(key, value));
		}
		i++;
	}
}

static float getPrevious(std::string key, std::map<std::string, std::string> map)
{
	std::map<std::string, std::string>::iterator it = map.begin();
	std::map<std::string, std::string>::iterator prev;

//	std::cout << it->first << ", " << key << std::endl;

	if (it->first > key)
		throw BitcoinExchange::BadInputException();
	while (it != map.end() && it->first < key)
	{
//		std::cout << it->first << std::endl;
		prev = it;
		it++;
	}
	char *pEnd;
	return (strtof(prev->second.c_str(), &pEnd));
}

/*
 * 1/ recuper csv en map string string
 * 2/ gnl avec throw sur chaque ligne de l'input
 * 3/ conditions de throw : existantes + verif si dates sont correctes
 * */

void parseValue(std::string value)
{
	float res;
	char *pEnd;

	res = strtof(value.c_str(), &pEnd);
	if (res < 0)
		throw BitcoinExchange::NotPositiveException();
//	if (res > 999)
//		std::cout << std::endl << res << std::endl << std::endl;
	if (res >= 1000)
		throw BitcoinExchange::TooLargeException();
	if (pEnd[0])
		throw BitcoinExchange::BadInputException();
}

static void checkDate(std::string year, std::string month, std::string day)
{
	int monthI;
	int yearI;
	int dayI;

	yearI = atoi(year.c_str());
	monthI = atoi(month.c_str());
	dayI = atoi(day.c_str());

	if (yearI < 0 || monthI < 1 || dayI < 1)
		throw BitcoinExchange::BadInputException();

	if (monthI > 12)
		BitcoinExchange::BadInputException();
	if (monthI == 1 || monthI == 3 || monthI == 5 || monthI == 7 || monthI == 8 || monthI == 10 || monthI == 12)
	{
		if (dayI > 31)
			throw BitcoinExchange::BadInputException();
	}
	else
	{
		if (monthI == 2)
		{
			if (yearI % 4)
			{
				if (dayI > 28)
					throw BitcoinExchange::BadInputException();
			}
			else
			{
				if (!yearI % 100)
				{
					if (!yearI % 400) {
						if (dayI > 28)
							throw BitcoinExchange::BadInputException();
					}
				}
				else {
					if (dayI > 29)
						throw BitcoinExchange::BadInputException();
				}
			}

		}
		else
		{
			if (dayI > 30)
				throw BitcoinExchange::BadInputException();
		}
	}

}

static void parseKey(std::string key)
{
	size_t i;
	size_t j = 0;
	std::string day;
	std::string month;
	std::string year;


	if (key.size() != 10)
		throw BitcoinExchange::BadInputException();
	i = key.find('-', 0);
	year = key.substr(j, i - j);
	j = i + 1;
	i = key.find('-', j + 1);
	month = key.substr(j, i - j);
	j = i + 1;
	i = key.find('-', j);
	day = key.substr(j, i - j);
//	std::cout << "year: " << year << ", month: " << month << ", day: " << day << std::endl;

	//check 30-31 jours
	//check fevrier
	//check mois

	if (year.find_first_not_of("0123456789") != std::string::npos || month.find_first_not_of("0123456789") != std::string::npos || day.find_first_not_of("0123456789") != std::string::npos)
		throw BitcoinExchange::BadInputException();
	checkDate(year, month, day);
}

static void parseInput(std::string key, std::string value)
{
	(void)key;
	parseKey(key);
	parseValue(value);
}

void	BitcoinExchange::display()
{
	size_t i = 0;
	std::string line;
	std::string key;
	std::string value;
	float fvalue;
	char *pEnd;

	if (this->_datacsv.empty())
		return ;
	while (std::getline(this->_input, line))
	{
		if (check_first(line, i, 1))
		{
			try
			{
				if (line.empty())
					throw BadInputException();
				key = getKey(line, 1);;
				value = this->getValue(line, 1);
				parseInput(key, value);
				std::cout << key << " => " << value << " = ";
				if (this->_datacsv.find(key) != this->_datacsv.end())
					fvalue = strtof(this->_datacsv.at(key).c_str(), &pEnd);
				else
					fvalue = getPrevious(key, this->_datacsv);
				std::cout << fvalue * strtof(value.c_str(), &pEnd) << std::endl;
			}
			catch (BitcoinExchange::BadInputException &e)
			{
				std::cout << e.what() << line << std::endl;
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		i++;
	}
}