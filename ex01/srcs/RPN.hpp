/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:47:17 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/20 13:34:42 by abakirca         ###   ########.fr       */
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

#define PLUS 43
#define MINUS 45
#define MULTIPLY 42
#define DIVIDE 47

class Rpn
{
	private:
			std::stack<int> stack;
			void handleInput(const std::string& handle);
			std::string remove_whitespaces(const std::string &str);
			void checkInput(const std::string& input);
			void fillStack(const std::string& handle);
	public:
			Rpn();
			Rpn(const std::string& input);
			Rpn(const Rpn &copy);
			Rpn &operator=(const Rpn &copy);
			~Rpn();
};

#endif
