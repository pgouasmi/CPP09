/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:23:03 by pgouasmi          #+#    #+#             */
/*   Updated: 2024/02/20 13:23:03 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &obj)
{
	*this = obj;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
	this->_elementsNb = obj._elementsNb;
	this->_vec = obj._vec;

	return *this;
}

static void isArgCorrect(std::string s)
{
	if (s.find_first_not_of("0123456789") != std::string::npos)
		throw PmergeMe::ErrorException();
}

static void isNbCorrect(long long nb, char *pEnd)
{
	if (pEnd[0] || nb < 0 || nb > INT_MAX)
		throw PmergeMe::ErrorException();
}

static void fusion(std::vector<std::pair<int, int> > &arr, std::vector<std::pair<int, int> > &left, std::vector<std::pair<int, int> > &right)
{
	std::vector<std::pair<int, int > >::iterator lit = left.begin();
	std::vector<std::pair<int, int > >::iterator rit = right.begin();
	std::vector<std::pair<int, int > >::iterator ait = arr.begin();
	while (lit != left.end() && rit != right.end())
	{
		if (lit->first < rit->first) {
			ait->first = lit->first;
			ait->second = lit->second;
			lit++;
		}
		else
		{
			ait->first = rit->first;
			ait->second = rit->second;
			rit++;
		}
		ait++;
	}
	while (lit != left.end())
	{
		ait->first = lit->first;
		ait->second = lit->second;
		lit++;
		ait++;
	}
	while (rit != right.end())
	{
		ait->first = rit->first;
		ait->second = rit->second;
		rit++;
		ait++;
	}
}

void PmergeMe::sortPairs(std::vector<std::pair<int, int> >& arr) {
	size_t i = 0;
	size_t middle = arr.size() / 2;
	std::vector<std::pair<int, int> > left;
	std::vector<std::pair<int, int> > right;

	if (arr.size() > 1) {
		for (std::vector<std::pair<int, int> >::iterator it = arr.begin(); it != arr.end(); ++it) {
			if (i < middle)
				left.push_back(*it);
			else
				right.push_back(*it);
			i++;
		}
		sortPairs(left);
		sortPairs(right);
		fusion(arr, left, right);
	}
}

void PmergeMe::orderPairs()
{
	for (std::vector<std::pair<int, int> >::iterator it = this->_pairs.begin() ; it != this->_pairs.end() ; ++it)
	{
		if (it->first < it->second)
		{
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

void PmergeMe::makePairs()
{
	std::vector<int>::iterator inputIterator = this->_vec.begin();
	while (inputIterator != this->_vec.end())
	{
		std::vector<int>::iterator next = inputIterator;
		++next;
		std::vector<std::pair<int, int> > temp;
		if (next != this->_vec.end())
			this->_pairs.push_back(std::pair<int, int>(*inputIterator,* next));
		else
			this->_pairs.push_back(std::pair<int, int>(*inputIterator, -1));
		++inputIterator;
		if (inputIterator != this->_vec.end())
			++inputIterator;
	}
	std::cout << "Before sorting pairs 2: " << std::endl;
	this->printPairs();
	this->_vec.clear();
	this->orderPairs();
	std::pair<int, int> last = this->_pairs.back();
	if (last.second == -1)
	{
		this->_lonely = last;
		this->_pairs.pop_back();
	}
	std::cout << "After sorting pairs 2: " << std::endl;
	this->printPairs();
}

void	PmergeMe::vectorFordJohnson()
{
	this->makePairs();
	this->sortPairs(this->_pairs);

	std::cout << "After merge sort:" << std::endl;
	this->printPairs();
}

PmergeMe::PmergeMe(char **argv)
{
	//init time
	this->_elementsNb = 0;
	std::string temp;
	this->_lonely.first = -1;
	this->_lonely.second = -1;

	for (size_t i = 1; argv[i] ; ++i)
	{
		std::string s = argv[i];
		isArgCorrect(s);

		char *pEnd;
		long long nb = strtoll(argv[i], &pEnd, 10);
		isNbCorrect(nb, pEnd);
		this->_elementsNb++;
		this->_vec.push_back(static_cast<int>(nb));
	}
//	this->printVector();
	this->vectorFordJohnson();

	//print time
	//init time

	//algo list FJ

	//print

}

void PmergeMe::printVector()
{
	for (std::vector<int>::iterator it = this->_vec.begin(); it != this->_vec.end() ; ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;
	std::cout << "number of elements: " << this->_elementsNb << std::endl;
}


void PmergeMe::printPairs()
{
	for (std::vector<std::pair<int, int>  >::iterator it = this->_pairs.begin();  it != this->_pairs.end() ; ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << std::endl;
}
