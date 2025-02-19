/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:47:17 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/19 16:51:15 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <exception>
#include <algorithm>

#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define BLUE "\033[1;34m"
#define WHITE "\033[1;37m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

class Rpn
{
	private:
			std::stack<int> stack;
			void parseInput(const std::string& input);
			std::string remove_whitespaces(const std::string &str);
	public:
			Rpn();
			Rpn(const std::string& input);
			Rpn(const Rpn &copy);
			Rpn &operator=(const Rpn &copy);
			~Rpn();
};

#endif
