// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operand.template.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/23 00:18:53 by mc                #+#    #+#             //
//   Updated: 2017/04/25 13:35:44 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERAND_TEMPLATE_HPP
# define OPERAND_TEMPLATE_HPP

# include "IOperand.hpp"
# include "OperandFactory.hpp"
# include <cmath> //fmod

typedef int    t_int8;
typedef int    t_int16;
typedef int    t_int32;

typedef enum Operator
{
	OP_ADD = 0,
	OP_SUB = 1,
	OP_MUL = 2,
	OP_DIV = 3,
	OP_MOD = 4
} eOperator;
# define NUMBER_OF_OPERATORS 5

template <eOperandType OPERAND_TYPE, typename TYPENAME, TYPENAME (*STR_TO_TYPE)(std::string const &, std::size_t *)>
class Operand : public IOperand
{
	private:
		std::string  _str;
		int          _precision;
		eOperandType _type;
		// TYPENAME     _value;
		OperandFactory  const *_factory;

	public:
		/*
		** constructor
		*/
		Operand(std::string const &str = "0",
				OperandFactory  const *factory = NULL) : _str(str),
														 _factory(factory)
		{
				DEBUG("Operand constructor");

				this->_precision = OPERAND_TYPE;
				this->_type = OPERAND_TYPE;
				// this->_value = STR_TO_TYPE(str, 0); //catch errors
				if (!factory) {
					this->_factory = new OperandFactory;
				}
		}

		Operand(Operand const &copy) : IOperand(copy)
		{
				DEBUG("Operand copy");

				*this = copy;
		}


		/*
		** destructor
		*/
		~Operand(void)
		{
			DEBUG("Operand destructor");
		}


		/*
		** operator overload
		*/
		Operand const &operator=(Operand const &copy) const
		{
			*this = copy; //TODO?
			return *this;
		}

		IOperand const *  operator+(IOperand const & rhs) const
		{
			return this->do_op(rhs, OP_ADD);
		}

		IOperand const *  operator-(IOperand const & rhs) const
		{
			return this->do_op(rhs, OP_SUB);
		}

		IOperand const *  operator*(IOperand const & rhs) const
		{
			return this->do_op(rhs, OP_MUL);
		}

		IOperand const *  operator/(IOperand const & rhs) const
		{
			return this->do_op(rhs, OP_DIV);
		}

		IOperand const *  operator%(IOperand const & rhs) const
		{
			return this->do_op(rhs, OP_MOD);
		}


		/*
		** public
		*/
		std::string const & toString(void) const
		{
			return this->_str;
		}

		int               getPrecision(void) const
		{
			return this->_precision;
		}

		eOperandType      getType(void) const
		{
			return this->_type;
		}

		// TYPENAME          getValue(void) const
		// {
		// 	return this->_value;
		// }

		// void              setValue(TYPENAME value)
		// {
		// 	this->_value = value;
		// 	this->_str = std::to_string(value);
		// }


		/*
		** private
		*/
		std::string          getNewValue(std::string const & rhs_str, eOperator op) const
		{
			TYPENAME ret = STR_TO_TYPE(this->_str, 0);
			TYPENAME rhs = STR_TO_TYPE(rhs_str, 0);

			switch(op) {
			case OP_ADD:
				ret += rhs;
				break;
			case OP_SUB:
				ret -= rhs;
				break;
			case OP_MUL:
				ret *= rhs;
				break;
			case OP_DIV:
				ret /= rhs;
				break;
			case OP_MOD:
				ret = static_cast<TYPENAME>(fmod(static_cast<double>(ret), static_cast<double>(rhs))); //TODO
				break;
			}

			return std::to_string(ret);
			//TODO: catch error
		}

		IOperand const *  do_op(IOperand const & rhs, eOperator op) const
		{
			if (rhs.getType() <= this->_type) {
				return this->_factory->createOperand(
					this->_type,
					this->getNewValue(rhs.toString(), op)
				);
			}
			//TODO: else



			return NULL;
			//TODO: catch error
		}
};

#endif



/*
** private
*/
// Operand const * toInt8(IOperand const & op)
// {
// 	Operand const *ret;

// 	switch (op.getType()) {
// 	case Int8:
// 		return new Operand(static_cast<Operand const &>(op));
// 		break;
// 	case Int16:
// 		break;
// 	case Int32:
// 		break;
// 	case Float:
// 		break;
// 	case Double:
// 		break;
// 	default:
// 	}

// 	return ret;
// }
