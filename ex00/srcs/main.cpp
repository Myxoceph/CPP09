/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:38:42 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/17 17:00:08 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(void)
{
	try
	{
		BitcoinExchange exchange;
		std::map<std::string, float>::iterator it;
		// for (it = exchange.data.begin(); it != exchange.data.end(); it++)
		// {
		// 	std::cout << it->first << " " << it->second << std::endl;
		// }
		for (it = exchange.input.begin(); it != exchange.input.end(); it++)
		{
			std::cout << it->first << " " << it->second << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}
