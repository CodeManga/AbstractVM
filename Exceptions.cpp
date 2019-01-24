/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 23:43:08 by hmthimun          #+#    #+#             */
/*   Updated: 2018/07/30 12:34:36 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.hpp"

Exceptions::Exceptions(void)
{
    return ;
}

Exceptions::Exceptions(std::string const &msg) throw()
{
    _msg = msg;
}

Exceptions::Exceptions(Exceptions const &ref)
{
    *this = ref;
}

Exceptions::~Exceptions() throw()
{
    return ;
}

Exceptions  & Exceptions::operator=(Exceptions const &ref)
{
    this->_msg = ref._msg;
    return (*this);
}

const char  *Exceptions::what(void) const throw()
{
    return (_msg.c_str());
}