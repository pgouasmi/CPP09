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

//void PmergeMe::sortPairs()
//{
//	for (std::vector<std::vector<std::pair<int, size_t> > >::iterator it = this->_pairs.begin(); it != this->_pairs.end(); ++it)
//	{
//		if (it->size() > 1) {
//			std::vector<std::pair<int, size_t > >::iterator B = it->begin();
//			std::vector<std::pair<int, size_t > >::iterator E = it->end();
//			--E;
//			if (*E > *B && E != B) {
//				std::pair<int, size_t> temp;
//				temp = *E;
//				*E = *B;
//				*B = temp;
//			}
//		}
//	}
//	std::cout << "After: " << std::endl;
//	this->printPairs();
//}

static void fusion(std::vector<std::pair<int, size_t> > arr, std::vector<std::pair<int, size_t> > left, std::vector<std::pair<int, size_t> > right)
{
	std::vector<std::pair<int, size_t > >::iterator lit = left.begin();
	std::vector<std::pair<int, size_t > >::iterator rit = right.begin();
	std::vector<std::pair<int, size_t > >::iterator ait = arr.begin();
	++lit;
	++rit;
	++ait;
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
	for (std::vector<std::pair<int, size_t> >::iterator it = arr.begin() ; it != arr.end() ; ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << std::endl;
}

void PmergeMe::sortPairs(std::vector<std::pair<int, size_t> > arr)
{
	size_t	i = 0;
	size_t middle = arr.size() / 2;
	std::vector<std::pair<int, size_t> > left;
	std::vector<std::pair<int, size_t> > right;

	if (arr.size() > 1) {
		for (std::vector<std::pair<int, size_t> >::iterator it = arr.begin(); it != arr.end(); ++it) {
			if (i < middle)
				left.push_back(*it);
			else
				right.push_back(*it);
			i++;
		}
		sortPairs(left);
		sortPairs(right);
	}
	else
		fusion(arr, left, right);
//	for (std::vector<std::pair<int, size_t> >::iterator it = arr.begin() ; it != arr.end() ; ++it)
//	{
//		std::cout << it->first << " " << it->second << std::endl;
//	}
}

//void PmergeMe::printLargest()
//{
//	std::cout << "largest:" << std::endl;
//	for (std::vector<std::pair<int, size_t> >::iterator it;  it != this->_largest.end() ; ++it)
//	{
//		std::cout << it->first << " " << it->second << std::endl;
//	}
//}
//
//void PmergeMe::printSmallest()
//{
//	std::cout << "smallest:" << std::endl;
//	for (std::vector<std::pair<int, size_t> >::iterator it;  it != this->_smallest.end() ; ++it)
//	{
//		std::cout << it->first << " " << it->second << std::endl;
//	}
//}

void PmergeMe::splitPairs()
{
	for (std::vector<std::vector<std::pair<int, size_t> > >::iterator it = this->_pairs.begin() ; it != this->_pairs.end() ; ++it)
	{
		std::pair<int, size_t> first = it->front();
		std::pair<int, size_t> second = it->back();

//		std::cout << "first = " << first.first << " " << first.second << std::endl;
//		std::cout << "second = " << second.first << " " << second.second << std::endl;

		if (first.first > second.first)
		{
			this->_largest.push_back(first);
			this->_smallest.push_back(second);
		}
		else
		{
			this->_largest.push_back(second);
			this->_smallest.push_back(first);
		}
	}
//	this->printLargest();
//	this->printSmallest();
}

void PmergeMe::makePairs()
{
	std::vector<int>::iterator inputIterator = this->_vec.begin();
	size_t i = 1;
	while (inputIterator != this->_vec.end())
	{
		std::vector<std::pair<int, size_t> > temp;
		temp.push_back(std::pair<int, size_t>(*inputIterator, i));
		++inputIterator;
		if (inputIterator == this->_vec.end())
		{
			this->_pairs.push_back(temp);
			break ;
		}
		temp.push_back(std::pair<int, size_t>(*inputIterator, i));
		this->_pairs.push_back(temp);
		++inputIterator;
		i++;
	}
//	std::cout << "Before: " << std::endl;
//	this->printPairs();
	this->_vec.clear();
	this->splitPairs();
}

void	PmergeMe::vecFJ()
{
	this->makePairs();
	this->sortPairs(this->_largest);
	for (std::vector<std::pair<int, size_t> >::iterator it = this->_largest.begin() ; it != this->_largest.end() ; ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
}

PmergeMe::PmergeMe(char **argv)
{
	this->_elementsNb = 0;
	std::string temp;

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
	this->vecFJ();
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
	for (std::vector<std::vector<std::pair<int, size_t> > >::iterator it = this->_pairs.begin();  it != this->_pairs.end() ; ++it)
	{
		for (std::vector<std::pair<int, size_t> >::iterator that = it->begin(); that != it->end() ; ++that)
		{
			std::cout << that->first << " " << that->second << std::endl;
		}
		std::cout << std::endl;
	}
}
