/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:39:14 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/18 17:08:42 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define BLUE "\033[1;34m"
#define WHITE "\033[1;37m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

class BitcoinExchange
{
	private:
			std::map<std::string, float> data;
			void parse_data(const std::string& data);
			void parse_input(const std::string& input);
			int check_header(const std::string& input);
			bool is_valid_date(const std::string& date);
			void print_data(const std::string& date , const float& value);
			std::string remove_whitespaces(const std::string &str);
			int check_integrity(const std::string& input);
	public:
			BitcoinExchange();
			BitcoinExchange(const std::string& input);
			BitcoinExchange(const BitcoinExchange &copy);
			BitcoinExchange &operator=(const BitcoinExchange &copy);
			~BitcoinExchange();
};

#endif
