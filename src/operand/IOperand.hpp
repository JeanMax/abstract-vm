// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IOperand.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:30:49 by mc                #+#    #+#             //
//   Updated: 2017/03/20 22:45:29 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IOPERAND_HPP
# define IOPERAND_HPP


# include "../abstract-vm.hpp"

typedef enum OperandType
{
	Int8 =   0,
	Int16 =  1,
	Int32 =  2,
	Float =  3,
	Double = 4
} eOperandType;

class IOperand {

	public:

		virtual int   getPrecision( void ) const = 0; // Precision of the type of the instance

		virtual eOperandType getType( void ) const = 0;  // Type of the instance

		virtual IOperand const *  operator+( IOperand const & rhs ) const = 0; // Sum
		virtual IOperand const *  operator-( IOperand const & rhs ) const = 0; // Difference
		virtual IOperand const *  operator*( IOperand const & rhs ) const = 0; // Product
		virtual IOperand const *  operator/( IOperand const & rhs ) const = 0; // Quotient
		virtual IOperand const *  operator%( IOperand const & rhs ) const = 0; // Modulo

		virtual std::string const & toString( void ) const = 0; // String representation of the instance

		virtual ~IOperand( void ) {}
};

#endif

/*

	New operands MUST be created via a "factory method". Search Google if you don't
know what it is. This member function must have the following prototype:

 IOperand const * createOperand( eOperandType type, std::string const & value ) const;

    Depending on the enum value passed as a parameter, the member function createOperand
creates a new IOperand by calling one of the following private member functions:

 IOperand const * createInt8( std::string const & value ) const;
 IOperand const * createInt16( std::string const & value ) const;
 IOperand const * createInt32( std::string const & value ) const;
 IOperand const * createFloat( std::string const & value ) const;
 IOperand const * createDouble( std::string const & value ) const;

    In order to choose the right member function for the creation of the new IOperand,
	you MUST create and use an array (here, a vector shows little interest) of pointers on
member functions with enum values as index.


    The pure method getPrecision from the interface IOperand allows to get the preci
sion of an operand. When an operation uses two operands from two different types, th
comparison of theirs precisions allows to figure out the result type of the operation.


	AbstractVM is a stack based virtual machine. Whereas the stack is an actual stack o
another container that behaves like a stack is up to you. Whatever the container, it MUST
only contain pointers to the abstract type IOperand.

*/
