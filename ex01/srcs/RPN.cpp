/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:47:49 by abakirca          #+#    #+#             */
/*   Updated: 2025/02/18 18:47:49 by abakirca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

Rpn::Rpn()
{
}

Rpn::Rpn(const std::string& input)
{
}

Rpn::Rpn(const Rpn &copy)
{
	*this = copy;
}

Rpn &Rpn::operator=(const Rpn &copy)
{
	if (this == &copy)
		return (*this);
	return (*this);
}

Rpn::~Rpn()
{
}
