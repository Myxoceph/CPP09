/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:42:55 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/24 18:10:31 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PMergeMe::PMergeMe()
{
}

PMergeMe::PMergeMe(char **input)
{
	checkInput(input);
	print(input);
}

PMergeMe::PMergeMe(const PMergeMe &copy)
{
	*this = copy;
}

PMergeMe &PMergeMe::operator=(const PMergeMe &copy)
{
	if (this != &copy)
	{
		vecarr = copy.vecarr;
		deqarr = copy.deqarr;
	}
	return (*this);
}

PMergeMe::~PMergeMe()
{
}

template <typename T>
void PMergeMe::mergeSort(T &c, const T &left, const T &right) 
{
	c.clear();
	size_t i = 0
	size_t j = 0;
	while (i < left.size() && j < right.size())
	{
		if (left[i] <= right[j])
			c.push_back(left[i++]);
		else
			c.push_back(right[j++]);
	}
	while (i < left.size())
		c.push_back(left[i++]);
	while (j < right.size())
		c.push_back(right[j++]);
}

template <typename T>
void PMergeMe::insertionSort(T &c) 
{
	for (size_t i = 1; i < c.size(); ++i)
	{
		typename T::value_type key = c[i];
		int j = i - 1;
		while (j >= 0 && c[j] > key)
		{
			c[j + 1] = c[j];
			j--;
		}
		c[j + 1] = key;
	}
}

template <typename T>
void PMergeMe::FordJohnson(T &c) 
{
	if (c.size() <= 1)
		return;
	if (c.size() == 2)
	{
		if (c[0] > c[1])
			std::swap(c[0], c[1]);
		return;
	}
	if (c.size() <= 16)
	{
		insertionSort(c);
		return;
	}
	T left(c.begin(), c.begin() + c.size() / 2);
	T right(c.begin() + c.size() / 2, c.end());

	FordJohnson(left);
	FordJohnson(right);

	mergeSort(c, left, right); 
}

void PMergeMe::checkInput(char **av)
{
	int i = 1;

	while (av[i])
	{
		std::string str(av[i]);
		for (size_t j = 0; j < str.size(); j++)
		{
			if (!isdigit(str[j]))
			{
				throw std::invalid_argument("Invalid input");
			}
		}
		long num = std::strtol(str.c_str(), NULL, 10);
		if (num > std::numeric_limits<int>::max())
			throw std::invalid_argument("Invalid input");
		vecarr.push_back(num);
		deqarr.push_back(num);
		i++;
	}
}

void PMergeMe::print(char **input)
{
	clock_t vecstart = clock();
	FordJohnson(vecarr);
	clock_t vecend = clock();
	clock_t deqstart = clock();
	FordJohnson(deqarr);
	clock_t deqend = clock();
	double vecduration = (double)(vecend - vecstart) * 1e6 / CLOCKS_PER_SEC;
	double deqduration = (double)(deqend - deqstart) * 1e6 / CLOCKS_PER_SEC;
	std::cout << GREEN << "Before	: "WHITE;
	for (int i = 1; input[i]; i++)
	{
		std::cout << input[i];
		if (input[i + 1])
			std::cout << " ";
	}
	std::cout << RESET << std::endl;
	std::cout << GREEN << "After	: "WHITE;
	for (size_t i = 0; i < vecarr.size(); i++)
	{
		std::cout << vecarr[i];
		if (i + 1 < vecarr.size())
			std::cout << " ";
	}
	std::cout << RESET << std::endl;
	std::cout << CYAN"Time to process a range of " << vecarr.size() << " elements with std::<vector>	: "WHITE << vecduration << " µs" << RESET << std::endl;
	std::cout << CYAN"Time to process a range of " << deqarr.size() << " elements with std::<deque> 	: "WHITE << deqduration << " µs" << RESET << std::endl;
	return ;
}
