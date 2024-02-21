/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:17:41 by pgouasmi          #+#    #+#             */
/*   Updated: 2024/02/20 14:17:41 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <climits>


class PmergeMe {
private:
	std::vector<int> _vec;
	std::vector<std::pair<int, int> > _pairs;
	std::pair<int, int> _lonely;
	int _elementsNb;

	PmergeMe();

	void vectorFordJohnson();
	void makePairs();
	void sortPairs(std::vector<std::pair<int, int> > &arr);
	void orderPairs();
	void reorderSmallest();

	void printPairs();
	void printVector();
	void printSmallest();
	void printBiggest();

public:
	PmergeMe(char **argv);
	PmergeMe(const PmergeMe &obj);
	PmergeMe &operator=(const PmergeMe &obj);
	~PmergeMe();

class ErrorException : public std::exception
{
	const char *what() const throw() { return ("Error"); }
};
};

const std::ostream &operator<<(const std::ostream &os, const PmergeMe &obj);


#endif
