/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:39:14 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/17 18:51:37 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange
{
	private:
	public:
			BitcoinExchange();
			BitcoinExchange(const BitcoinExchange &copy);
			BitcoinExchange &operator=(const BitcoinExchange &copy);
			~BitcoinExchange();
			std::multimap<std::string, float> data;
			std::multimap<std::string, float> input;
			void parse_data(const std::string& data);
			void parse_input(const std::string& data);
			int check_pipe(const std::string& data);
};

#endif
