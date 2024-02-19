/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:19:15 by pgouasmi          #+#    #+#             */
/*   Updated: 2024/02/19 14:19:15 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

void RPN::calculate(std::string op)
{

	if (this->_mystack.size() < 2)
		throw BadInputException();

	double res;
	double first = this->_mystack.top();
	this->_mystack.pop();
	double second = this->_mystack.top();
	this->_mystack.pop();
	if (op == "+")
		res = first + second;
	else if (op == "-")
		res = second - first;
	else if (op == "*")
		res = first * second;
	else {
		if (!first)
			throw DivisionByZeroException();
		res = second / first;
	}
	this->_mystack.push(res);
}

RPN::RPN(std::string &input)
{
	char *pEnd;

	if (input.find_first_not_of("0123456789 -+*/") != std::string::npos ||input.empty())
		throw BadInputException();
	size_t i = input.find_first_not_of(' ');
	while (i != std::string::npos)
	{
		std::string temp = input.substr(i, 1);
		if (temp.find_first_of("-+*/") == std::string::npos)
			this->_mystack.push(strtod(temp.c_str(), &pEnd));
		else
			this->calculate(temp);
		i++;
		i = input.find_first_not_of(' ', i);
	}
	if (this->_mystack.size() > 1)
		throw BadInputException();
	if (!this->_mystack.empty())
		std::cout << this->_mystack.top() << std::endl;
}

RPN::RPN(const RPN &obj)
{
	*this = obj;
}

RPN &RPN::operator=(const RPN &obj)
{
	this->_mystack = obj._mystack;
	return *this;
}

RPN::~RPN() {}
