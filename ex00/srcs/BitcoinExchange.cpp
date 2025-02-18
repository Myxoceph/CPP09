/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:39:30 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/18 18:39:23 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	parse_data("data.csv");
	parse_input("input.txt");
}

BitcoinExchange::BitcoinExchange(const std::string& input)
{
	parse_data("data.csv");
	parse_input(input);
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

int BitcoinExchange::check_integrity(const std::string& input)
{
	int pipe_count = 0;
	int dot_count = 0;
	std::string line = input;
	size_t pos = 0;

	line = remove_whitespaces(line);
	for(size_t i = 0; i < line.size(); i++)
		if (line[i] == '|')
			pipe_count++;
	if (pipe_count == 0)
	{
		if (input.empty())
			return (std::cout << RED"Error: bad input => empty date."RESET << std::endl, 1);
		return (std::cout << RED"Error: bad input => " << line << RESET << std::endl, 1);
	}
	else if (pipe_count != 1)
		return (std::cout << RED"Error: invalid format."RESET << std::endl, 1);
	pos = line.find('|');
	pos++;
	if (pos == line.size())
		return (std::cout << RED"Error: invalid format."RESET << std::endl, 1);
	while (pos != line.size())
	{
		if (isdigit(line[pos]) || line[pos] == '.' || line[pos] == '-' || line[pos] == '+')
			{
				if (line[pos] == '.')
					dot_count++;
			}
		else
			return (std::cout << RED"Error: invalid format."RESET << std::endl, 1);
		pos++;
	}
	if (dot_count > 1)
		return (std::cout << RED"Error: invalid format."RESET << std::endl, 1);
	return (0);
}

std::string BitcoinExchange::remove_whitespaces(const std::string &str)
{
	std::string result = str;
	result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
	return (result);
}

void BitcoinExchange::print_data(const std::string& date , const float& value)
{
	std::multimap<std::string, float>::iterator it;
	it = this->data.upper_bound(date);
	if (it == this->data.end())
		std::cout << RED"Error: old as fuck date."RESET << std::endl;
	else
	{
		if (it != this->data.begin())
			it--;
		std::cout << WHITE << date << " => " << value << " = " << (it->second * value) << RESET << std::endl;
	}
}

static bool	is_leap_year(int year)
{
	if (year % 4 == 0 && year % 100 != 0)
		return (true);
	if (year % 400 == 0)
		return (true);
	return (false);
}

static bool	is_valid_format(const std::string &date, int &year, int &month, int &day)
{
	char	dash1;
	char	dash2;
	std::istringstream	ss(date);

	if (!(ss >> year >> dash1 >> month >> dash2 >> day))
		return (false);
	if (dash1 != '-' || dash2 != '-')
		return (false);
	return (true);
}

bool	BitcoinExchange::is_valid_date(const std::string &date)
{
	int		year;
	int		month;
	int		day;
	int		days_in_month[12] = {31, 28, 31, 30, 31, 30, 
								31, 31, 30, 31, 30, 31};

	if (!is_valid_format(date, year, month, day))
		return (false);
	if (month < 1 || month > 12)
		return (false);
	if (is_leap_year(year))
		days_in_month[1] = 29;
	if (day < 1 || day > days_in_month[month - 1])
		return (false);
	return (true);
}

int BitcoinExchange::check_header(const std::string& input)
{
	std::string key;
	std::string value;
	std::stringstream ss(input);
	std::getline(ss, key, '|');
	ss >> value;
	if (key != "date " || value != "value")
		return (1);
	return (0);
}

void BitcoinExchange::parse_data(const std::string& data)
{
	std::ifstream dbase;
	std::string line;

	dbase.open(data.c_str());
	if (!dbase.is_open())
		throw std::runtime_error("File could not be opened.");
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
		throw std::runtime_error("File could not be opened.");
	std::getline(dbase, line);
	if (check_header(line))
		throw std::runtime_error("Invalid header.");
	while (std::getline(dbase, line))
	{
		std::string key;
		float value;
		if (check_integrity(line))
			continue;
		std::stringstream ss(line);
		std::getline(ss, key, '|');
		key = remove_whitespaces(key);
		ss >> value;
		if (!is_valid_date(key))
		{
			if (key.empty())
				key = "empty date.";
			std::cout << RED"Error: bad input => " << key << RESET << std::endl;
			continue;
		}
		if (value < 1)
		{
			std::cout << RED"Error: not a positive number."RESET << std::endl;
			continue;
		}
		else if (value > 999)
		{
			std::cout << RED"Error: too large a number."RESET << std::endl;
			continue;
		}
		print_data(key, value);
	}
	dbase.close();
}
