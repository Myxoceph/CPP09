/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:44:49 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/20 15:44:50 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>

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
			
	public:
			PMergeMe();
			PMergeMe(const std::string& input);
			PMergeMe(const PMergeMe &copy);
			PMergeMe &operator=(const PMergeMe &copy);
			~PMergeMe();
};

#endif
