//
// Created by pgouasmi on 2/19/24.
//

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstring>


class RPN {
private:
	std::stack<double> _mystack;
	RPN();
	void calculate(std::string op);

public:
	RPN(std::string &input);
	RPN(const RPN &obj);
	RPN &operator=(const RPN &obj);
	~RPN();


class DivisionByZeroException : public std::exception
{
	const char *what() const throw() { return ("Division by 0 detected"); }
};

class BadInputException : public std::exception
{
	const char *what() const throw() { return ("Wrong input detected"); }
};

};


#endif //CPP09_RPN_HPP
