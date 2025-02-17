/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:39:30 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/17 18:47:21 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	parse_data("data.csv");
	parse_input("input.txt");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	*this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	if (this == &copy)
		return (*this);
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

int BitcoinExchange::check_pipe(const std::string& input)
{
	if (input.find('|') != std::string::npos)
		{
			if (input.find('|') != input.rfind('|'))
				return (1);
			else if (input.find('|') == 0 || input.rfind('|') == input.size() - 1)
				return (1);
			else
				return (0);
		}
	return (1);
}

void BitcoinExchange::parse_data(const std::string& data)
{
	std::ifstream dbase;
	std::string line;

	dbase.open(data.c_str());
	if (!dbase.is_open())
		throw std::runtime_error("Error: File could not be opened.");
	std::getline(dbase, line);
	while (std::getline(dbase, line))
	{
		std::string key;
		float value;
		std::stringstream ss(line);
		std::getline(ss, key, ',');
		ss >> value;
		this->data.insert(std::pair<std::string, float>(key, value));
	}
	dbase.close();
}

void BitcoinExchange::parse_input(const std::string& input)
{
	std::ifstream dbase;
	std::string line;

	dbase.open(input.c_str());
	if (!dbase.is_open())
		throw std::runtime_error("Error: File could not be opened.");
	std::getline(dbase, line);
	while (std::getline(dbase, line))
	{
		std::string key;
		float value;
		if (check_pipe(line))
		{
			key = "INVALID";
			value = 0;
			this->input.insert(std::pair<std::string, float>(key, value));
			continue;
		}
		std::stringstream ss(line);
		std::getline(ss, key, '|');
		std::cout << "Key -> " << key << std::endl;
		ss >> value;
		std::cout << "Value -> " << value << std::endl;
		this->input.insert(std::pair<std::string, float>(key, value));
	}
	dbase.close();
}
