/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:38:42 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/18 18:43:31 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << RED"Error: could not open file." << RESET << std::endl;
		return (1);
	}
	try
	{
		BitcoinExchange exchange(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED"Exception: " << e.what() << RESET << std::endl;
	}
	return (0);
}
