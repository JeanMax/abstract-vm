// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operand.template.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/23 00:18:53 by mc                #+#    #+#             //
//   Updated: 2017/09/27 13:29:10 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERAND_TEMPLATE_HPP
# define OPERAND_TEMPLATE_HPP

# include "../abstract-vm.hpp"
# include "../error/Error.template.hpp"
# include "OperandFactory.hpp"

# include <cmath> //fmod
# include <sstream>

# define DEBUG_TYPE(t) (!t ? "int8" : (t == 1 ? "int16" : (t == 2 ? "int32" : (t == 3 ? "float" : "double"))))
# define DEBUG_OP(o) (!o ? "+" : (o == 1 ? "-" : (o == 2 ? "*" : (o == 3 ? "/" : "%"))))

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

template <
    eOperandType OPERAND_TYPE,
    typename     TYPENAME,
    TYPENAME     (*STR_TO_TYPE)(std::string const &, std::size_t *)
>
class Operand : public IOperand
{
    private:
        std::string           _str;
        int                   _precision;
        eOperandType          _type;
        OperandFactory const *_factory;

    public:
        /*
        ** constructor
        */
        Operand(std::string const &str = "0",
                OperandFactory  const *factory = NULL) : _factory(factory)
        {
            std::stringstream ss;
            TYPENAME          tmp;

            this->_precision = OPERAND_TYPE;
            this->_type = OPERAND_TYPE;

            if (!factory) {
                this->_factory = new OperandFactory;
            }

            try {
                tmp = STR_TO_TYPE(str, 0);
                ss << tmp;
            } catch (std::out_of_range &e) {
                // delete this; //TODO
                throw Error<std::out_of_range>(
                    *(str.c_str()) == '-' ? "Underflow Error" : "Overflow Error"
                );
            }

            if (tmp > this->getMax()) {
                // delete this; //TODO
                throw Error<std::out_of_range>("Overflow Error");
            }
            if (tmp < this->getMin()) {
                // delete this; //TODO
                throw Error<std::out_of_range>("Underflow Error");
            }

            this->_str = ss.str();

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
        Operand const &     operator=(Operand const &copy) const
        {
            *this = copy;
            return *this;
        }

        IOperand const *    operator+(IOperand const &rhs) const
        {
            return this->do_op(rhs, OP_ADD);
        }

        IOperand const *    operator-(IOperand const &rhs) const
        {
            return this->do_op(rhs, OP_SUB);
        }

        IOperand const *    operator*(IOperand const &rhs) const
        {
            return this->do_op(rhs, OP_MUL);
        }

        IOperand const *    operator/(IOperand const &rhs) const
        {
            return this->do_op(rhs, OP_DIV);
        }

        IOperand const *    operator%(IOperand const &rhs) const
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

        int                 getPrecision(void) const
        {
            return this->_precision;
        }

        eOperandType        getType(void) const
        {
            return this->_type;
        }


        /*
        ** private
        */
        TYPENAME            getMin() const
        {
            return static_cast<TYPENAME>(
                this->_factory->getMin(static_cast<eOperandType>(this->_precision))
            );
        }

        TYPENAME            getMax() const
        {
            return static_cast<TYPENAME>(
                this->_factory->getMax(static_cast<eOperandType>(this->_precision))
            );
        }


        std::string         getNewValue(std::string const &rhs_str, eOperator op) const
        {
            TYPENAME lhs_val = STR_TO_TYPE(this->_str, 0);
            TYPENAME rhs_val = STR_TO_TYPE(rhs_str, 0);
            std::stringstream ss;

            DEBUG(lhs_val << " " << DEBUG_OP(op) << " " << rhs_val);
            DEBUG("max: " << this->getMax() << " min: " << this->getMin());

            switch(op) {
                case OP_ADD:
                    if (lhs_val > 0 && rhs_val > 0
                        && lhs_val > this->getMax() - rhs_val) {
                        // delete this; //TODO
                        throw Error<std::out_of_range>("Add Overflow Error");
                    }
                    if (lhs_val < 0 && rhs_val < 0
                        && lhs_val < this->getMin() - rhs_val) {
                        // delete this; //TODO
                        throw Error<std::out_of_range>("Add Underflow Error");
                    }
                    lhs_val += rhs_val;
                    break;

                case OP_SUB:
                    if (lhs_val > 0 && rhs_val < 0
                        && lhs_val > this->getMax() + rhs_val) {
                        // delete this; //TODO
                        throw Error<std::out_of_range>("Substract Overflow Error");
                    }
                    if (lhs_val < 0 && rhs_val > 0
                        && lhs_val < this->getMin() + rhs_val) {
                        // delete this; //TODO
                        throw Error<std::out_of_range>("Substract Underflow Error");
                    }
                    lhs_val -= rhs_val;
                    break;

                case OP_MUL:
                    if (((lhs_val > 0 && rhs_val > 1) || (lhs_val < 0 && rhs_val < 1))
                        && lhs_val > this->getMax() / rhs_val) {
                        // delete this; //TODO
                        throw Error<std::out_of_range>("Multiply Overflow Error");
                    }
                    if (((lhs_val > 0 && rhs_val < 1) || (lhs_val < 0 && rhs_val > 1))
                        && lhs_val < this->getMin() / rhs_val) {
                        // delete this; //TODO
                        throw Error<std::out_of_range>("Multiply Underflow Error");
                    }
                    lhs_val *= rhs_val;
                    break;

                case OP_DIV:
                    if (((lhs_val > 0 && rhs_val > 0) || (lhs_val < 0 && rhs_val < 0))
                        && lhs_val > this->getMax() * rhs_val) {
                        // delete this; //TODO
                        throw Error<std::out_of_range>("Divide Overflow Error");
                    }
                    if (((lhs_val > 0 && rhs_val < 0) || (lhs_val < 0 && rhs_val > 0))
                        && lhs_val < this->getMin() * rhs_val) {
                        // delete this; //TODO
                        throw Error<std::out_of_range>("Divide Underflow Error");
                    }
                    if (!static_cast<bool>(rhs_val)) {
                        // delete this; //TODO
                        throw Error<std::domain_error>("Zero Divide Error");
                    }
                    lhs_val /= rhs_val;
                    break;

                case OP_MOD:
                    if (!static_cast<bool>(rhs_val)) {
                        // delete this; //TODO
                        throw Error<std::domain_error>("Zero Modulo Error");
                    }
                    lhs_val = static_cast<TYPENAME>(
                        fmod(static_cast<double>(lhs_val), static_cast<double>(rhs_val))
                    ); //TODO: test with integers
                    break;
            }

            DEBUG("= " << lhs_val);
            ss << lhs_val;
            return ss.str();
        }

        IOperand const *     do_op(IOperand const &rhs, eOperator op) const
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
        }
};

#endif
