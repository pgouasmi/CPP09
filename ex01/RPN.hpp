/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:36:58 by pgouasmi          #+#    #+#             */
/*   Updated: 2024/03/15 10:36:58 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


#endif
