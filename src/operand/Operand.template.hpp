// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operand.template.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/23 00:18:53 by mc                #+#    #+#             //
//   Updated: 2017/04/25 16:08:52 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERAND_TEMPLATE_HPP
# define OPERAND_TEMPLATE_HPP

# include "../abstract-vm.hpp"
# include "OperandFactory.hpp"

# include <cmath> //fmod

# define DEBUG_TYPE(t) (!t ? "int8" : (t == 1 ? "int16" : (t == 2 ? "int32" : (t == 3 ? "float" : "double"))))

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
				this->_precision = OPERAND_TYPE;
				this->_type = OPERAND_TYPE;
				// this->_value = STR_TO_TYPE(str, 0); //catch errors
				if (!factory) {
					this->_factory = new OperandFactory;
				}

				DEBUG("Operand constructor: "
					  << DEBUG_TYPE(this->_type) << "(" << str <<")");
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
			DEBUG("Operand destructor: "
				  << DEBUG_TYPE(this->_type) << "(" << this->_str <<")");
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

			IOperand const *op_tmp = this->_factory->createOperand(
				rhs.getType(),
				this->_str
			);
			IOperand const *op_new;
			switch(op) {
				case OP_ADD:
					op_new = *op_tmp + rhs;
					break;
				case OP_SUB:
					op_new = *op_tmp - rhs;
					break;
				case OP_MUL:
					op_new = *op_tmp * rhs;
					break;
				case OP_DIV:
					op_new = *op_tmp / rhs;
					break;
				case OP_MOD:
					op_new = *op_tmp % rhs;
					break;
			}
			delete op_tmp;

			return op_new;
			//TODO: catch error
		}
};

#endif
