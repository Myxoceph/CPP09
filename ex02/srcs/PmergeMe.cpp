/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:42:55 by abakirca          #+#    #+#             */
/*   Updated: 2025/10/23 12:21:37 by abakirca         ###   ########.fr       */
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
size_t PMergeMe::generateJacobsthal(size_t n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	size_t a = 0;
	size_t b = 1;
	size_t result = 0;
	for (size_t i = 2; i <= n; i++)
	{
		result = b + 2 * a;
		a = b;
		b = result;
	}
	return result;
}

template <typename T>
void PMergeMe::generateJacobsthalSequence(std::vector<size_t> &seq, size_t len)
{
	seq.clear();
	if (len == 0)
		return;
	
	size_t idx = 3;
	while (true)
	{
		size_t jacob = generateJacobsthal<T>(idx);
		if (jacob >= len)
			break;
		seq.push_back(jacob);
		idx++;
	}
}

template <typename T>
typename T::iterator PMergeMe::binaryInsert(T &c, typename T::iterator begin, typename T::iterator end, typename T::value_type value)
{
	typename T::iterator left = begin;
	typename T::iterator right = end;
	
	while (left < right)
	{
		typename T::iterator mid = left + std::distance(left, right) / 2;
		if (*mid < value)
			left = mid + 1;
		else
			right = mid;
	}
	return c.insert(left, value);
}

template <typename T>
void PMergeMe::FordJohnson(T &c) 
{
	if (c.size() <= 1)
		return;
	size_t n = c.size();
	bool isOdd;
	if (n % 2 == 0)
		isOdd = false;
	else
		isOdd = true;
	typename T::value_type odd = 0;

	if (isOdd)
	{
		odd = c.back();
		c.pop_back();
		n--;
	}

	std::vector<std::pair<typename T::value_type, typename T::value_type> > pairs;
	for (size_t i = 0; i < n; i += 2)
	{
		if (c[i] > c[i + 1])
			pairs.push_back(std::make_pair(c[i], c[i + 1]));
		else
			pairs.push_back(std::make_pair(c[i + 1], c[i]));
	}
	if (pairs.size() > 1)
	{
		T main;
		for (size_t i = 0; i < pairs.size(); i++)
			main.push_back(pairs[i].first);
		
		FordJohnson(main);

		std::vector<std::pair<typename T::value_type, typename T::value_type> > sortedPairs;
		for (size_t i = 0; i < main.size(); i++)
		{
			for (size_t j = 0; j < pairs.size(); j++)
			{
				if (pairs[j].first == main[i])
				{
					sortedPairs.push_back(pairs[j]);
					break;
				}
			}
		}
		pairs = sortedPairs;
	}

	c.clear();
	for (size_t i = 0; i < pairs.size(); i++)
		c.push_back(pairs[i].first);
	T small;
	for (size_t i = 0; i < pairs.size(); i++)
		small.push_back(pairs[i].second);
	if (!small.empty())
	{
		c.insert(c.begin(), small[0]);
	}
	std::vector<size_t> jacobsthal;
	generateJacobsthalSequence<T>(jacobsthal, small.size());
	std::vector<bool> inserted(small.size(), false);
	inserted[0] = true;
	for (size_t i = 0; i < jacobsthal.size(); i++)
	{
		size_t jacobIdx = jacobsthal[i] - 1;
		size_t prevJacob = (i > 0) ? jacobsthal[i - 1] : 1;
		
		for (size_t j = jacobIdx; j >= prevJacob && j < small.size(); j--)
		{
			if (!inserted[j])
			{
				size_t searchLimit = 0;
				for (size_t k = 0; k < c.size(); k++)
				{
					if (c[k] == pairs[j].first)
					{
						searchLimit = k;
						break;
					}
				}
				binaryInsert(c, c.begin(), c.begin() + searchLimit + 1, small[j]);
				inserted[j] = true;
			}
			if (j == 0)
				break;
		}
	}
	for (size_t i = 0; i < small.size(); i++)
	{
		if (!inserted[i])
		{
			size_t searchLimit = 0;
			for (size_t k = 0; k < c.size(); k++)
			{
				if (c[k] == pairs[i].first)
				{
					searchLimit = k;
					break;
				}
			}
			binaryInsert(c, c.begin(), c.begin() + searchLimit + 1, small[i]);
		}
	}
	if (isOdd)
		binaryInsert(c, c.begin(), c.end(), odd);
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
