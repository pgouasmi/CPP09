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

static void vectorFusion(std::vector<std::pair<int, int> > &arr, std::vector<std::pair<int, int> > &left, std::vector<std::pair<int, int> > &right)
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

void PmergeMe::vectorMerge(std::vector<std::pair<int, int> >& arr)
{
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
		vectorMerge(left);
		vectorMerge(right);
		vectorFusion(arr, left, right);
	}
}

static void listFusion(std::list<std::pair<int, int> > &lst, std::list<std::pair<int, int> > &left, std::list<std::pair<int, int> > &right)
{
	std::list<std::pair<int, int > >::iterator lit = left.begin();
	std::list<std::pair<int, int > >::iterator rit = right.begin();
	std::list<std::pair<int, int > >::iterator ait = lst.begin();
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

void PmergeMe::listMerge(std::list<std::pair<int, int> > &lst)
{
	size_t i = 0;
	size_t middle = lst.size() / 2;
	std::list<std::pair<int, int> > left;
	std::list<std::pair<int, int> > right;

	if (lst.size() > 1) {
		for (std::list<std::pair<int, int> >::iterator it = lst.begin(); it != lst.end(); ++it) {
			if (i < middle)
				left.push_back(*it);
			else
				right.push_back(*it);
			i++;
		}
		listMerge(left);
		listMerge(right);
		listFusion(lst, left, right);
	}
}

template<typename T>
void PmergeMe::orderPairs(T &c)
{
	for (typename T::iterator it = c.begin() ; it != c.end() ; ++it)
	{
		if (it->first < it->second)
		{
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

void PmergeMe::makePairsV()
{
	std::vector<int>::iterator inputIterator = this->_vec.begin();
	while (inputIterator != this->_vec.end())
	{
		std::vector<int>::iterator next = inputIterator;
		++next;
		std::vector<std::pair<int, int> > temp;
		if (next != this->_vec.end())
			this->_vPairs.push_back(std::pair<int, int>(*inputIterator,* next));
		else
			this->_vPairs.push_back(std::pair<int, int>(*inputIterator, -1));
		++inputIterator;
		if (inputIterator != this->_vec.end())
			++inputIterator;
	}
	this->_vec.clear();
	this->orderPairs(this->_vPairs);
	std::pair<int, int> last = this->_vPairs.back();
	if (last.second == -1)
	{
		this->_lonely = last;
		this->_vPairs.pop_back();
	}
}

template <typename T>
void PmergeMe::sendFirst(T &c)
{
	c.insert(c.begin(), std::pair<int, int>(c.begin()->second, -1));
	typename T::iterator it = c.begin();
	++it;
	it->second = -1;
}

void PmergeMe::vectorInsert()
{
	std::vector<std::pair<int, int> >::iterator it = this->_vPairs.begin();
	it += 2;
	while (it != this->_vPairs.end())
	{
		std::pair<size_t, size_t> temp = this->getJacobsthal();
		size_t range = temp.second - temp.first;
		std::vector<std::pair<int, int> >::iterator last = it;

		if (range <= static_cast<size_t>(std::distance(last, this->_vPairs.end()))) {
			last += range - 1;
		}
		else {
			last = this->_vPairs.end();
			--last;
		}
		if (last == this->_vPairs.end())
			--last;
		std::vector<std::pair<int, int> >::iterator upper = last;
		std::vector<std::pair<int , int > >::iterator prev = it;
		--prev;
		while (last != prev)
		{
			std::pair<int, int> toAdd;
			if (last->second != -1)
			{
				toAdd = std::pair<int, int>(last->second, -1);
				last->second = -1;
				std::vector<std::pair<int, int> >::iterator placeToInsert = this->vectorBinarySearch(this->_vPairs.begin(), upper, toAdd.first);
				this->_vPairs.insert(placeToInsert, toAdd);
			}
			if (last->second == -1) {
				last--;
			}
		}
		last--;
		while (range && it != this->_vPairs.end())
		{
			range--;
			it++;
		}
	}
	if (this->_lonely.first != -1)
		this->_vPairs.insert(this->vectorBinarySearch(this->_vPairs.begin(), this->_vPairs.end(), this->_lonely.first),
							std::pair<int, int>(this->_lonely.first, -1));
}

std::vector<std::pair<int,int> >::iterator PmergeMe::vectorBinarySearch(std::vector<std::pair<int,int> >::iterator begin, std::vector<std::pair<int,int> >::iterator end, int toInsert)
{
	size_t distance = std::distance(begin, end);
	std::vector<std::pair<int,int> >::iterator middle;
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

void PmergeMe::listInsert()
{
	std::list<std::pair<int, int> >::iterator it = this->_lPairs.begin();
	++it;
	++it;
	while (it != this->_lPairs.end())
	{
		std::pair<size_t, size_t> temp = this->getJacobsthal();
		size_t range = temp.second - temp.first;
		std::list<std::pair<int, int> >::iterator last = it;

		if (range <= static_cast<size_t>(std::distance(last, this->_lPairs.end()))) {
			for (size_t j = 1; j < range; ++j)
			++last;
		}
		else {
			last = this->_lPairs.end();
			--last;
		}
		if (last == this->_lPairs.end())
			--last;
		std::list<std::pair<int, int> >::iterator upper = last;
		std::list<std::pair<int , int > >::iterator prev = it;
		--prev;
		while (last != prev)
		{
			std::pair<int, int> toAdd;
			if (last->second != -1)
			{
				toAdd = std::pair<int, int>(last->second, -1);
				last->second = -1;
				std::list<std::pair<int, int> >::iterator placeToInsert = this->listBinarySearch(this->_lPairs.begin(), upper, toAdd.first);
				this->_lPairs.insert(placeToInsert, toAdd);
			}
			if (last->second == -1) {
				last--;
			}
		}
		last--;
		while (range && it != this->_lPairs.end())
		{
			range--;
			it++;
		}
	}
	if (this->_lonely.first != -1)
		this->_lPairs.insert(this->listBinarySearch(this->_lPairs.begin(), this->_lPairs.end(), this->_lonely.first),
							 std::pair<int, int>(this->_lonely.first, -1));
}

std::list<std::pair<int,int> >::iterator PmergeMe::listBinarySearch(std::list<std::pair<int,int> >::iterator begin, std::list<std::pair<int,int> >::iterator end, int toInsert)
{
	size_t distance = std::distance(begin, end);
	std::list<std::pair<int,int> >::iterator middle;
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

std::pair<size_t, size_t > PmergeMe::getJacobsthal()
{
	std::vector<size_t >::iterator end = --this->_jacobstahl.end();
	std::vector<size_t >::iterator prev = end;

	--prev;
	this->_jacobstahl.push_back((2 * *prev) + *end);
	end = --this->_jacobstahl.end();
	prev = end;
	--prev;
	return (std::pair<size_t, size_t>(*prev, *end));
}

void	PmergeMe::vectorFordJohnson()
{
	this->_vPairs.reserve(this->_elementsNb + 1);
	this->makePairsV();
	this->vectorMerge(this->_vPairs);
	this->sendFirst(this->_vPairs);
	this->vectorInsert();
}

void PmergeMe::makePairsL()
{
	std::list<int>::iterator inputIterator = this->_lst.begin();
	while (inputIterator != this->_lst.end())
	{
		std::list<int>::iterator next = inputIterator;
		++next;
		std::list<std::pair<int, int> > temp;
		if (next != this->_lst.end())
			this->_lPairs.push_back(std::pair<int, int>(*inputIterator,* next));
		else
			this->_lPairs.push_back(std::pair<int, int>(*inputIterator, -1));
		++inputIterator;
		if (inputIterator != this->_lst.end())
			++inputIterator;
	}
	this->_lst.clear();
	this->orderPairs(this->_lPairs);
	std::pair<int, int> last = this->_lPairs.back();
	if (last.second == -1)
	{
		this->_lonely = last;
		this->_lPairs.pop_back();
	}
}

void	PmergeMe::listFordJohnson()
{
	this->makePairsL();
	this->listMerge(this->_lPairs);
	this->sendFirst(this->_lPairs);
	this->listInsert();
}

void PmergeMe::startTimer()
{
	gettimeofday(&this->_timer.first, NULL);
}

double PmergeMe::stopTimer()
{
	gettimeofday(&this->_timer.second, NULL);

//	long sec = this->_timer.second.tv_sec - _timer.first.tv_sec;
//	long micro = this->_timer.second.tv_usec - _timer.first.tv_usec;
//	return (sec + micro*1e-6);
	return ((static_cast<double>(this->_timer.second.tv_sec) * 1000000LL + static_cast<double>(this->_timer.second.tv_usec)) - (static_cast<double>(this->_timer.first.tv_sec) * 1000000LL + static_cast<double>(this->_timer.first.tv_usec)));
}

PmergeMe::PmergeMe(char **argv)
{
	/*FIRST CONTAINER*/
	{
		//init time
		this->startTimer();

		this->_elementsNb = 0;
		std::string temp;
		this->_lonely.first = -1;
		this->_lonely.second = -1;
		this->_jacobstahl.push_back(1);
		this->_jacobstahl.push_back(1);

		for (size_t i = 1; argv[i]; ++i) {
			std::string s = argv[i];
			isArgCorrect(s);

			char *pEnd;
			long long nb = strtoll(argv[i], &pEnd, 10);
			isNbCorrect(nb, pEnd);
			this->_elementsNb++;
			this->_vec.push_back(static_cast<int>(nb));
		}
		if (this->_elementsNb == 1)
			throw PmergeMe::ErrorException();
		std::cout << "Before: " << std::flush;
		this->printSimpleContainer(this->_vec);
		this->vectorFordJohnson();
		this->stopTimer();
		std::cout << "After: " << std::flush;
		this->printPairsFirstElement(this->_vPairs);
		std::cout << "Time to process " << this->_elementsNb << " elements with std::vector : " << this->stopTimer() << " us" << std::endl;
	}

	/*SECOND CONTAINER*/

	{
		//init time
		this->startTimer();

		this->_elementsNb = 0;
		std::string temp;
		this->_lonely.first = -1;
		this->_lonely.second = -1;
		this->_jacobstahl.push_back(1);
		this->_jacobstahl.push_back(1);

		for (size_t i = 1; argv[i]; ++i) {
			std::string s = argv[i];
			isArgCorrect(s);

			char *pEnd;
			long long nb = strtoll(argv[i], &pEnd, 10);
			isNbCorrect(nb, pEnd);
			this->_elementsNb++;
			this->_lst.push_back(static_cast<int>(nb));
		}
		if (this->_elementsNb == 1)
			throw PmergeMe::ErrorException();
		this->listFordJohnson();
		this->stopTimer();
		std::cout << "Time to process " << this->_elementsNb << " elements with std::list : " << this->stopTimer() << " us" << std::endl;
	}
}

template<typename T>
void PmergeMe::printPairsFirstElement(const T &c)
{
	for (typename T::const_iterator it = c.begin() ; it != c.end() ; ++it)
	{
		std::cout << " " << it->first;
	}
	std::cout << std::endl;
}

template <typename T>
void PmergeMe::printSimpleContainer(const T &c)
{
	for (typename T::const_iterator it = c.begin(); it != c.end() ; ++it) {
		std::cout << " " << *it << std::flush;
	}
	std::cout << std::endl;
}

template<typename T>
void PmergeMe::printPairs(const T &c)
{
	for (typename T::const_iterator it = c.begin();  it != c.end() ; ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << std::endl;
}
