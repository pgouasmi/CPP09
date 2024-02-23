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
//	std::cout << "Before sorting pairs 2: " << std::endl;
//	this->printPairs();
	this->_vec.clear();
	this->orderPairs();
	std::pair<int, int> last = this->_pairs.back();
	if (last.second == -1)
	{
		this->_lonely = last;
		this->_pairs.pop_back();
	}
//	std::cout << "After sorting pairs 2: " << std::endl;
//	this->printPairs();
}

void PmergeMe::sendFirst()
{

	this->_pairs.insert(this->_pairs.begin(), std::pair<int, int>(this->_pairs.begin()->second, -1));
	std::vector<std::pair<int, int> >::iterator it = this->_pairs.begin();
	++it;
	it->second = -1;

//	std::vector<std::pair<int, int> >::iterator it = this->_pairs.begin();
//	while (it != this->_pairs.end())
//	{
//		this->_vec.push_back(it->first);
//		it++;
//	}
//	it = this->_pairs.begin();
//	this->_vec.insert(this->_vec.begin(), it->second);
//	this->_pairs.erase(this->_pairs.begin());
//
//	std::cout << "Pairs after popping first" << std::endl;
//	this->printPairs();
}

void PmergeMe::merge()
{
	std::vector<std::pair<int, int> >::iterator it = this->_pairs.begin();
	++it;
	++it;
	while (it != this->_pairs.end())
	{
		std::pair<size_t, size_t> temp = this->getJacobsthal();
		size_t range = temp.second - temp.first;
		std::vector<std::pair<int, int> >::iterator last = it;

		std::cout << "/*0*/" << std::endl;
		std::cout << "range = " << range<< std::endl;
		std::cout << "distance between last et end = " << std::distance(last, this->_pairs.end()) << std::endl;
		std::cout << "it = " << it->first << std::endl;
		std::cout << "last =" << last->first << std::endl << std::endl;


		if (range <= static_cast<size_t>(std::distance(last, this->_pairs.end()))) {
			std::cout << "got  in range ok" << std::endl;
			last += range - 1;
		}
		else {
			last = this->_pairs.end();
			--last;
		}
		std::vector<std::pair<int, int> >::iterator lower = this->_pairs.begin();
		if (last == this->_pairs.end())
			--last;

		std::cout << "/*1*/" << std::endl;
		std::cout << "range =" << range <<  std::endl;
		std::cout << "it = " << it->first << std::endl;
		std::cout << "last = " << last->first << std::endl;
		std::cout << "distance from it =" << std::distance(it, last) << std::endl << std::endl;
		this->printPairs();

		std::vector<std::pair<int, int> >::iterator upper = last;
		std::vector<std::pair<int , int > >::iterator prev = it;
		--prev;

		while (last != prev)
		{
			std::pair<int, int> toAdd;
			if (last->second != -1)
			{
				if (last->second == 32)
					std::cout << "32 FOUNDDDDDDDDDDDDDDD" << std::endl;
				std::cout << "/*2*/" << std::endl;
				std::cout << "it = " << it->first << std::endl;
				std::cout << "prev = " << prev->first << std::endl;
				std::cout << "lower = " << lower->first << std::endl;
				std::cout << "upper = " << upper->first << std::endl;
				std::cout << "last = " << last->first << std::endl << std::endl;
				this->printPairs();
//				std::cout << std::endl;
//				this->printPairs();
//				if (last == it)
//					throw PmergeMe::ErrorException();
				toAdd = std::pair<int, int>(last->second, -1);
				last->second = -1;
				std::vector<std::pair<int, int> >::iterator placeToInsert = this->binarySearch(this->_pairs.begin(), upper, toAdd.first);
				this->_pairs.insert(placeToInsert, toAdd);
				std::cout << "inserted " << toAdd.first << std::endl;
				std::cout << "new pair:" << std::endl;
				this->printPairs();
//				lower = placeToInsert;
//				lower++;
			}
			if (last->second == -1) {
				std::cout << "last = " << last->first << std::endl;
				std::cout << "LAST--" << std::endl;
				last--;
				std::cout << "NEW LAST =" << last->first << last->second << std::endl;
			}
		}
		std::cout << "/*3*/" << std::endl;
		std::cout << "last = " << last->first << std::endl << std::endl;
		last--;
		this->printPairs();
		std::cout << "/4/\nin increment it, initial: " << it->first << std::endl;
		while (range && it != this->_pairs.end())
		{
			std::cout << "decrementing range" << std::endl;

//			if (it == this->_pairs.end()) {
//				std::cout << "END FOUND FOR ITTTTTTTTTTTTTTTTT" << std::endl;
//				break;
//			}
			range--;
			it++;
		}
		if (it != this->_pairs.end())
			std::cout << "/4/\nin increment it, FINAL: " << it->first << std::endl << std::endl;
//		if (static_cast<size_t>(std::distance(it, this->_pairs.end())) <= range)
//			it = this->_pairs.end();
//		else
//			std::advance(it, range);
////		if (++it == this->_pairs.end())
////		++it;
	}
	if (this->_lonely.first != -1)
		this->_pairs.insert(this->binarySearch(this->_pairs.begin(), this->_pairs.end(), this->_lonely.first),
							std::pair<int, int>(this->_lonely.first, -1));
}

std::pair<size_t, size_t > PmergeMe::getJacobsthal()
{
	std::vector<size_t >::iterator end = --this->_jacobstahl.end();
	std::vector<size_t >::iterator prev = end;
	--prev;
	this->_jacobstahl.push_back((2 * *prev) + *end);

	end = --this->_jacobstahl.end();
	prev = end;
	--prev;
//	std::cout << "jacob : first = " << *prev << " second: " << *end << std::endl;
	return (std::pair<size_t, size_t>(*prev, *end));
}

std::vector<std::pair<int, int> >::iterator PmergeMe::binarySearch(std::vector<std::pair<int, int> >::iterator begin, std::vector<std::pair<int, int> >::iterator end, int toInsert)
{
//	std::cout << "bf all, begin: " << *begin << " end:" << *end << std::endl;
	size_t distance = std::distance(begin, end);
	std::vector<std::pair<int, int> >::iterator middle;
	while (distance > 1)
	{
		middle = begin;
		size_t i = 0;
		while (i < distance/2)
		{
			++middle;
			i++;
		}
		if (middle->first > toInsert)
			end = middle;
		else
			begin = middle;
		distance = std::distance(begin, end);
	}
	if (toInsert < begin->first)
		return begin;
	return (end);
}

void	PmergeMe::vectorFordJohnson()
{
	this->_pairs.reserve(this->_elementsNb + 1);
	this->makePairs();
	this->sortPairs(this->_pairs);

//	std::cout << "After merge sort:" << std::endl;
//	this->printPairs();
//
	this->sendFirst();
	std::cout << "after send to final" << std::endl;
//	this->printVector();

	this->printPairs();

	this->merge();
//	int toAdd = 89;
//	std::cout << "to add " << toAdd << " need to insert it before " << this->binarySearch(this->_pairs.begin(), --this->_pairs.end(), toAdd)->first;

	std::cout << "final: " << std::endl;
	this->printPairs();

}

PmergeMe::PmergeMe(char **argv)
{
	//init time
	this->_elementsNb = 0;
	std::string temp;
	this->_lonely.first = -1;
	this->_lonely.second = -1;
	this->_jacobstahl.push_back(1);
	this->_jacobstahl.push_back(1);

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
