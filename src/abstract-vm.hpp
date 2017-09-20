// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   abstract-vm.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:31:36 by mc                #+#    #+#             //
//   Updated: 2017/09/20 15:41:57 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP

// # include <exception>
# include <iostream>
# include <stack>
# include "operand/IOperand.hpp"
# include "operand/OperandFactory.hpp"

# define VERBOSE 0
# define DEBUG(s) do { \
	if (VERBOSE) { std::cout << s << std::endl; } \
	} while (0)

/*
** lexer.cpp
*/
void lexer(char *filename);

/*
** parser.cpp
*/
IOperand const *parse_operand(std::string type, std::string value);
void parse_operator(std::string s_operator, IOperand const *operand);

/*
** main.cpp
*/
int kthxbye(int status);


#endif
