//
// Created by pgouasmi on 2/15/24.
//

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>

class BitcoinExchange {
public:

	BitcoinExchange(const char *arg);
	BitcoinExchange(const BitcoinExchange &obj);
	BitcoinExchange &operator=(const BitcoinExchange &obj);
	~BitcoinExchange();

	void scrapeCSV();
	void scrapeInput();
	void display();
	double getValue(const std::string &line, int type);





private:
	BitcoinExchange();

	std::map<std::string, double> _datacsv;
	std::map<std::string, double> _datainput;
	std::ifstream _input;
	std::ifstream _csv;


class FileNonOpenableException : public std::exception
{
	const char *what() const throw() { return ("Error: could not open file."); }
};

class NotPositiveException : public std::exception
{
	const char *what() const throw() { return ("Error: not a positive number."); }
};

class BadInputException : public std::exception
{
	const char *what() const throw() { return ("Error: bad input => "); }
};

class TooLargeException : public std::exception
{
	const char *what() const throw() { return ("Error: too large a number."); }
};

class NotANumberException : public std::exception{
	const char *what() const throw() { return ("Error: not a number."); }
};






};


#endif
