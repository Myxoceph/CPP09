/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:47:49 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/19 17:23:45 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

Rpn::Rpn()
{
}

Rpn::Rpn(const std::string& input)
{
	parseInput(input);
}

Rpn::Rpn(const Rpn &copy)
{
	*this = copy;
}

Rpn &Rpn::operator=(const Rpn &copy)
{
	if (this != &copy)
	{
		stack = copy.stack;
	}
	return (*this);
}
Rpn::~Rpn()
{
}

std::string Rpn::remove_whitespaces(const std::string &str)
{
	std::string result = str;
	result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
	return (result);
}

void Rpn::parseInput(const std::string& parse)
{
	std::string input = remove_whitespaces(parse);
	for(size_t i = 0; i < input.size(); i++)
	{
		if (isdigit(input[i]))
	}
}


// void Rpn::parseInput(const std::string& input)
// {
// 	std::string::const_iterator it = input.begin();
// 	std::string::const_iterator ite = input.end();
// 	while (it != ite)
// 	{
// 		if (isdigit(*it))
// 			stack.push(*it - '0');
// 		else if (*it == '+' || *it == '-' || *it == '*' || *it == '/')
// 		{
// 			if (stack.size() < 2)
// 				throw std::runtime_error("Error: too few operands");
// 			int a = stack.top();
// 			stack.pop();
// 			int b = stack.top();
// 			stack.pop();
// 			if (*it == '+')
// 				stack.push(a + b);
// 			else if (*it == '-')
// 				stack.push(a - b);
// 			else if (*it == '*')
// 				stack.push(a * b);
// 			else if (*it == '/')
// 			{
// 				if (b == 0)
// 					throw std::runtime_error("Error: division by zero");
// 				stack.push(a / b);
// 			}
// 		}
// 		else if (*it != ' ')
// 			throw std::runtime_error("Error: invalid character");
// 		it++;
// 	}
// 	if (stack.size() != 1)
// 		throw std::runtime_error("Error: too many operands");
// 	std::cout << GREEN"Result is => "WHITE << stack.top() << RESET << std::endl;
// }
