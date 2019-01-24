/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 04:59:13 by hmthimun          #+#    #+#             */
/*   Updated: 2018/07/30 05:01:57 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

std::ostream    &operator<<(std::ostream &o, IOperand const &rhs){
    o << rhs.toString();
    return (o);
}