/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:44:49 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/24 18:00:27 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <limits>
#include <exception>
#include <cstdlib>
#include <ctime>

#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define BLUE "\033[1;34m"
#define WHITE "\033[1;37m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

class PMergeMe
{
	private:
			std::vector<int> vecarr;
			std::deque<int> deqarr;
	public:
			PMergeMe();
			PMergeMe(char **input);
			PMergeMe(const PMergeMe &copy);
			PMergeMe &operator=(const PMergeMe &copy);
			~PMergeMe();
			template <typename T>
			void FordJohnson(T &c);
			template <typename T>
			void mergeSort(T &c, const T &left, const T &right);
			template <typename T>
			void insertionSort(T &c);
			void checkInput(char **av);
			void print(char **input);
};

#endif
