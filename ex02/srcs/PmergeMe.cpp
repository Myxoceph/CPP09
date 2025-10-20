/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:42:55 by abakirca          #+#    #+#             */
/*   Updated: 2025/10/20 16:53:02 by abakirca         ###   ########.fr       */
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
	
	// Step 1: Create pairs and compare
	size_t n = c.size();
	bool hasStraggler = (n % 2 != 0);
	typename T::value_type straggler = 0;
	
	if (hasStraggler)
	{
		straggler = c.back();
		c.pop_back();
		n--;
	}
	
	// Create pairs and ensure first element of each pair is larger
	std::vector<std::pair<typename T::value_type, typename T::value_type>> pairs;
	for (size_t i = 0; i < n; i += 2)
	{
		if (c[i] > c[i + 1])
			pairs.push_back(std::make_pair(c[i], c[i + 1]));
		else
			pairs.push_back(std::make_pair(c[i + 1], c[i]));
	}
	
	// Step 2: Recursively sort the larger elements (first elements of pairs)
	if (pairs.size() > 1)
	{
		T mainChain;
		for (size_t i = 0; i < pairs.size(); i++)
			mainChain.push_back(pairs[i].first);
		
		FordJohnson(mainChain);
		
		// Rebuild pairs based on sorted main chain
		std::vector<std::pair<typename T::value_type, typename T::value_type> > sortedPairs;
		for (size_t i = 0; i < mainChain.size(); i++)
		{
			for (size_t j = 0; j < pairs.size(); j++)
			{
				if (pairs[j].first == mainChain[i])
				{
					sortedPairs.push_back(pairs[j]);
					break;
				}
			}
		}
		pairs = sortedPairs;
	}
	
	// Step 3: Build the main chain (sorted larger elements)
	c.clear();
	for (size_t i = 0; i < pairs.size(); i++)
		c.push_back(pairs[i].first);
	
	// Step 4: Insert the smaller elements using Jacobsthal sequence
	T pending;
	for (size_t i = 0; i < pairs.size(); i++)
		pending.push_back(pairs[i].second);
	
	// Insert first element of pending at the beginning
	if (!pending.empty())
	{
		c.insert(c.begin(), pending[0]);
	}
	
	// Generate Jacobsthal sequence for insertion order
	std::vector<size_t> jacobSequence;
	generateJacobsthalSequence<T>(jacobSequence, pending.size());
	
	// Insert pending elements using Jacobsthal sequence
	std::vector<bool> inserted(pending.size(), false);
	inserted[0] = true; // First element already inserted
	
	for (size_t i = 0; i < jacobSequence.size(); i++)
	{
		size_t jacobIdx = jacobSequence[i] - 1; // Adjust for 0-based indexing
		
		// Insert elements in decreasing order from current Jacobsthal number to previous
		size_t prevJacob = (i > 0) ? jacobSequence[i - 1] : 1;
		
		for (size_t j = jacobIdx; j >= prevJacob && j < pending.size(); j--)
		{
			if (!inserted[j])
			{
				// Find position where pairs[j].first is in c
				size_t searchLimit = 0;
				for (size_t k = 0; k < c.size(); k++)
				{
					if (c[k] == pairs[j].first)
					{
						searchLimit = k;
						break;
					}
				}
				
				binaryInsert(c, c.begin(), c.begin() + searchLimit + 1, pending[j]);
				inserted[j] = true;
			}
			if (j == 0)
				break;
		}
	}
	
	// Insert any remaining pending elements
	for (size_t i = 0; i < pending.size(); i++)
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
			binaryInsert(c, c.begin(), c.begin() + searchLimit + 1, pending[i]);
		}
	}
	
	// Step 5: Insert straggler if exists
	if (hasStraggler)
	{
		binaryInsert(c, c.begin(), c.end(), straggler);
	}
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
