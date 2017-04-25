// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   abstract-vm.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:31:36 by mc                #+#    #+#             //
//   Updated: 2017/03/23 01:16:47 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP

// # include <exception>
# include <iostream>

# define VERBOSE 1
# define DEBUG(s) do { \
	if (VERBOSE) { std::cout << s << std::endl; } \
	} while (0)

# define MAX(x, y) ((x) > (y) ? (x) : (y))

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

/*
** lexer.cpp
*/
void lexer(char *filename);

/*
** parser.cpp
*/
void parse_operand(std::string type, std::string value);

#endif
