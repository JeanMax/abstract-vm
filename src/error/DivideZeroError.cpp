// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   DivideZeroError.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/20 17:22:58 by mc                #+#    #+#             //
//   Updated: 2017/09/20 19:21:28 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "DivideZeroError.hpp"

/*
** constructor
*/
DivideZeroError::DivideZeroError(void) throw() :
    std::domain_error("DivideZeroError"),
    _what("Divide Zero Error")
{
	DEBUG("DivideZeroError constructor");
}

DivideZeroError::DivideZeroError(DivideZeroError const &copy) throw() : std::domain_error("DivideZeroError")
{
	*this = copy;
	DEBUG("DivideZeroError copy");
}


/*
** destructor
*/
DivideZeroError::~DivideZeroError(void) throw()
{
	DEBUG("DivideZeroError destructor");
}


/*
** operator overload
*/
DivideZeroError const &DivideZeroError::operator=(DivideZeroError const &copy) throw()
{
	(void)copy; //TODO
	return *this;
}


/*
** public
*/
const char* DivideZeroError::what() const throw()
{
    return this->_what.c_str();
}
