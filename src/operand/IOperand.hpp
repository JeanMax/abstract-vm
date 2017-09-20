// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IOperand.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:30:49 by mc                #+#    #+#             //
//   Updated: 2017/09/20 23:47:26 by mc               ###   ########.fr       //
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
        virtual int                 getPrecision(void) const = 0;
        virtual eOperandType        getType(void) const = 0;

        virtual IOperand const *    operator+(IOperand const &rhs) const = 0;
        virtual IOperand const *    operator-(IOperand const &rhs) const = 0;
        virtual IOperand const *    operator*(IOperand const &rhs) const = 0;
        virtual IOperand const *    operator/(IOperand const &rhs) const = 0;
        virtual IOperand const *    operator%(IOperand const &rhs) const = 0;

        virtual std::string const & toString(void) const = 0;

        virtual ~IOperand(void) {}
};

#endif
