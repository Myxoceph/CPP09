/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:42:55 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/20 18:32:28 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PMergeMe::PMergeMe()
{
}

PMergeMe::PMergeMe(const std::string& input)
{
}

PMergeMe::PMergeMe(const PMergeMe &copy)
{
	*this = copy;
}

PMergeMe &PMergeMe::operator=(const PMergeMe &copy)
{
	return (*this);
}

PMergeMe::~PMergeMe()
{
}
