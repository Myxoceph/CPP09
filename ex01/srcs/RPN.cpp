/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:47:49 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/20 15:36:51 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

Rpn::Rpn()
{
}

Rpn::Rpn(const std::string& input)
{
	handleInput(input);
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

void Rpn::checkInput(const std::string& input)
{
	if (input.size() == 0)
		throw std::runtime_error("Error: empty input");
	for (size_t i = 0; i < input.size(); i++)
	{
		if (!isdigit(input[i]) && input[i] != PLUS && input[i] != MINUS && input[i] != MULTIPLY && input[i] != DIVIDE && input[i] != ' ')
			throw std::runtime_error("Error: invalid character");
		if (isspace(input[i]))
			continue;
		if (isdigit(input[i]) && (input[i + 1] != ' ' && input[i + 1] != '\0'))
			throw std::runtime_error("Error: invalid input");
		else if ((input[i] == MINUS || input[i] == PLUS) && (input[i + 1] != ' ' && input[i + 1] != '\0'))
			throw std::runtime_error("Error: invalid input");
		else if ((input[i] == MULTIPLY || input[i] == DIVIDE) && (input[i + 1] != ' ' && input[i + 1] != '\0'))
			throw std::runtime_error("Error: invalid input");
	}
}

void Rpn::fillStack(const std::string& handle)
{
	std::string input = remove_whitespaces(handle);
	if (!isdigit(input[0]) || !isdigit(input[1]))
		throw std::runtime_error("Error: input does not fit Reverse Polish Notation");

	int operands = 0;
	int operators = 0;

	for (size_t i = input.size(); i > 0; i--)
	{
		if (isdigit(input[i - 1]))
		{
			stack.push(input[i - 1] - '0');
			operands++;
			continue;
		}
		switch (input[i - 1])
		{
			case PLUS:
				stack.push(PLUS);
				operators++;
				break;
			case MINUS:
				stack.push(MINUS);
				operators++;
				break;
			case MULTIPLY:
				stack.push(MULTIPLY);
				operators++;
				break;
			case DIVIDE:
				stack.push(DIVIDE);
				operators++;
				break;
			default:
				break;
		}
	}
	if (operands == 0)
		throw std::runtime_error("Error: no operands");
	else if (operands == 1)
		throw std::runtime_error("Error: too few operands");
	else if (operators == 0)
		throw std::runtime_error("Error: no operators");
	else if (operands - operators != 1)
		throw std::runtime_error("Error: invalid input");
}

void Rpn::handleInput(const std::string& handle)
{
	checkInput(handle);
	fillStack(handle);
	std::stack<int> tempStack;

	while (!stack.empty())
	{
		int value = stack.top();
		stack.pop();

		if (value >= 0 && value <= 9)
			tempStack.push(value);
		else if (value == PLUS || value == MINUS || value == MULTIPLY || value == DIVIDE)
		{
			int operand2 = tempStack.top();
			tempStack.pop();
			int operand1 = tempStack.top();
			tempStack.pop();
			switch (value)
			{
				case PLUS: 
					tempStack.push(operand1 + operand2);
					break;
				case MINUS:
					tempStack.push(operand1 - operand2);
					break;
				case MULTIPLY:
					tempStack.push(operand1 * operand2);
					break;
				case DIVIDE:
					if (operand2 == 0)
						throw std::runtime_error("Error: division by zero");
					tempStack.push(operand1 / operand2);
					break;
			}
		}
	}
	std::cout << GREEN"Result is => "WHITE << tempStack.top() << RESET << std::endl;
}
