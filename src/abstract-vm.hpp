// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   abstract-vm.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:31:36 by mc                #+#    #+#             //
//   Updated: 2017/09/27 14:21:08 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP

# include <iostream>
# include <stack>
# include "log.hpp"
# include "operand/IOperand.hpp"
# include "operand/OperandFactory.hpp"
# include "error/Error.template.hpp"

/*
** lexer.cpp
*/
void            lexer(char *filename);

/*
** parser.cpp
*/
IOperand const *parse_operand(std::string type, std::string value);
void            parse_operator(std::string s_operator, IOperand const *operand);

/*
** main.cpp
*/
void            kthxbye(int status);

#endif
