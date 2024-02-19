/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:18:44 by pgouasmi          #+#    #+#             */
/*   Updated: 2024/02/19 14:18:44 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>

class BitcoinExchange {
private:
	BitcoinExchange();

	std::map<std::string, std::string> _datacsv;
	std::map<std::string, std::string> _datainput;
	std::ifstream _input;
	std::ifstream _csv;

public:

	BitcoinExchange(const char *arg);
	BitcoinExchange(const BitcoinExchange &obj);
	BitcoinExchange &operator=(const BitcoinExchange &obj);
	~BitcoinExchange();

	void scrapeCSV();
	void scrapeInput();
	void display();
	std::string getValue(const std::string &line, int type);


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
public:
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
