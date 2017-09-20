// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   parser.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 03:13:31 by mc                #+#    #+#             //
//   Updated: 2017/09/20 23:53:11 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PARSER_HPP
# define PARSER_HPP

# include <cstring>
# include "../abstract-vm.hpp"

typedef enum Operator
{
    Assert = 0,
    Push =   1,
    Pop =    2,
    Dump =   3,
    Add =    4,
    Sub =    5,
    Mul =    6,
    Div =    7,
    Mod =    8,
    Print =  9,
    Exit =   10,
    UnknownOperator =   42
} eOperator;
# define NUMBER_OF_OPERATORS 11

/*
** operators.cpp
*/
void do_assert(IOperand const *operand);
void do_push(IOperand const *operand);
void do_pop(IOperand const *operand);
void do_dump(IOperand const *operand);
void do_add(IOperand const *operand);
void do_sub(IOperand const *operand);
void do_mul(IOperand const *operand);
void do_div(IOperand const *operand);
void do_mod(IOperand const *operand);
void do_print(IOperand const *operand);
void do_exit(IOperand const *operand);

#endif
