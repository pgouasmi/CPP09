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
#include <list>
#include <climits>
#include <sys/time.h>


class PmergeMe {
private:
	PmergeMe();

	/*common data*/
	std::pair<int, int> _lonely;
	std::vector<size_t> _jacobstahl;
	int _elementsNb;
	std::pair<struct timeval, struct timeval> _timer;

	/*common methods*/
	std::pair<size_t, size_t > getJacobsthal();
	template<typename T>
	void orderPairs(T &c);
	template<typename T>
	void sendFirst(T &c);
	void startTimer();
	double stopTimer();


	/*prints*/
	template<typename T>
	void printPairs(const T &c);
	template<typename T>
	void printSimpleContainer(const T & c);
	template<typename T>
	void printPairsFirstElement(const T &c);


	//VECTOR
	/*vector related methods*/
	void vectorFordJohnson();
	void makePairsV();
	void vectorMerge(std::vector<std::pair<int, int> > &arr);
	void vectorInsert();
	std::vector<std::pair<int,int> >::iterator vectorBinarySearch(std::vector<std::pair<int,int> >::iterator begin, std::vector<std::pair<int,int> >::iterator end, int toInsert);


	/*vector related data*/
	std::vector<int> _vec;
	std::vector<std::pair<int, int> > _vPairs;
	//VECTOR



	//LIST
	/*list related data*/
	std::list<int> _lst;
	std::list<std::pair<int, int> > _lPairs;

	/*list related methods*/
	void listFordJohnson();
	void makePairsL();
	void listMerge(std::list<std::pair<int, int> > &lst);
	void listInsert();
	std::list<std::pair<int,int> >::iterator listBinarySearch(std::list<std::pair<int,int> >::iterator begin, std::list<std::pair<int,int> >::iterator end, int toInsert);
	//LIST


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
