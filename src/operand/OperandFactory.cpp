// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 18:17:40 by mc                #+#    #+#             //
//   Updated: 2017/04/25 13:35:56 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OperandFactory.hpp"
#include "Operand.template.hpp"

/*
** constructor
*/
OperandFactory::OperandFactory(void)
{
	DEBUG("OperandFactory constructor");
}

OperandFactory::OperandFactory(OperandFactory const &copy)
{
	*this = copy;
	DEBUG("OperandFactory copy");
}


/*
** destructor
*/
OperandFactory::~OperandFactory(void)
{
	DEBUG("OperandFactory destructor");
}


/*
** operator overload
*/
OperandFactory const &OperandFactory::operator=(OperandFactory const &copy)
{
	(void)copy;
	// *this = copy; //TODO
	return *this;
}


/*
** private
*/
static int stoi_base10(std::string const &s, std::size_t *pos = 0)
{
	return std::stoi(s, pos);
}

IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
	return new Operand<Int8, t_int8, &stoi_base10>(value);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const
{
	return new Operand<Int16, t_int16, &stoi_base10>(value);
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const
{
	return new Operand<Int32, t_int32, &stoi_base10>(value);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
	return new Operand<Float, float, &std::stof>(value);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
	return new Operand<Double, double, &std::stod>(value);
}


/*
** public
*/
IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	static IOperand const *(OperandFactory::*f[])(std::string const &) const = {
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble,
		NULL
	};

	return (this->*f[type])(value);
}
