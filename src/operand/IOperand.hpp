// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IOperand.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:30:49 by mc                #+#    #+#             //
//   Updated: 2017/04/25 15:09:55 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>

typedef enum OperandType
{
	Int8 =   0,
	Int16 =  1,
	Int32 =  2,
	Float =  3,
	Double = 4,
	Unknown = 42
} eOperandType;
# define NUMBER_OF_TYPES 5

class IOperand
{
	public:
		virtual int          getPrecision( void ) const = 0;
		virtual eOperandType getType( void ) const = 0;

		virtual IOperand const *  operator+( IOperand const & rhs ) const = 0;
		virtual IOperand const *  operator-( IOperand const & rhs ) const = 0;
		virtual IOperand const *  operator*( IOperand const & rhs ) const = 0;
		virtual IOperand const *  operator/( IOperand const & rhs ) const = 0;
		virtual IOperand const *  operator%( IOperand const & rhs ) const = 0;

		virtual std::string const & toString( void ) const = 0; // String representation of the instance

		virtual ~IOperand( void ) {}
};

#endif
/*
    The pure method getPrecision from the interface IOperand allows to get the preci
sion of an operand. When an operation uses two operands from two different types, th
comparison of theirs precisions allows to figure out the result type of the operation.

	AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack o
another container that behaves like a stack is up to you. Whatever the container, it MUST
only contain pointers to the abstract type IOperand.
*/
