// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   parser.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 03:13:02 by mc                #+#    #+#             //
//   Updated: 2017/09/21 00:48:42 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "parser.hpp"

extern OperandFactory const *g_factory;

static eOperandType get_type(std::string s_type)
{
    switch (s_type[3]) {
         case '8':
             return Int8;
             break;
         case '1':
             return Int16;
             break;
         case '3':
             return Int32;
             break;
         case 'a':
             return Float;
             break;
         case 'b':
             return Double;
             break;
    }

    ERROR("Unknown Type");
    return UnknownType;
}

static eOperator get_operator(std::string s_operator)
{
    if (s_operator == "assert")
        return Assert;
    if (s_operator == "push")
        return Push;
    if (s_operator == "pop")
        return Pop;
    if (s_operator == "dump")
        return Dump;
    if (s_operator == "add")
        return Add;
    if (s_operator == "sub")
        return Sub;
    if (s_operator == "mul")
        return Mul;
    if (s_operator == "div")
        return Div;
    if (s_operator == "mod")
        return Mod;
    if (s_operator == "print")
        return Print;
    if (s_operator == "exit")
        return Exit;

    ERROR("Unknown Operator");
    return UnknownOperator;
}

IOperand const *parse_operand(std::string s_type, std::string s_value)
{
    try {
        return g_factory->createOperand(get_type(s_type), s_value);
    } catch (std::exception &e) {
        WARNING(e.what());
    }

    return NULL;
}

void parse_operator(std::string s_operator, IOperand const *operand)
{
    static void (*f[])(IOperand const *) = {
        do_assert,
        do_push,
        do_pop,
        do_dump,
        do_add,
        do_sub,
        do_mul,
        do_div,
        do_mod,
        do_print,
        do_exit,
    };

    DEBUG("Operator: " << s_operator);
    try {
        f[get_operator(s_operator)](operand);
    } catch (std::exception &e) {
        WARNING(e.what());
    }
}
