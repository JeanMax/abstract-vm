// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   abstract-vm.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:31:36 by mc                #+#    #+#             //
//   Updated: 2017/09/20 22:35:24 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP

# include <iostream>
# include <stack>
# include "operand/IOperand.hpp"
# include "operand/OperandFactory.hpp"

# define CLR_RED "\033[31;01m"
# define CLR_YELLOW "\033[33;01m"
# define CLR_BLUE "\033[34;01m"
# define CLR_RESET "\033[0m"


# ifdef VERBOSE
#  define ERROR(s)   std::cerr << CLR_RED    "[ERROR] "   CLR_RESET << s << std::endl
#  define WARNING(s) std::cerr << CLR_YELLOW "[WARNING] " CLR_RESET << s << std::endl
#  define DEBUG(s)   std::cout << CLR_BLUE   "[DEBUG] "   CLR_RESET << s << std::endl
# else
#  define ERROR(s)   std::cerr << s << std::endl
#  define WARNING(s) do {} while(0)
#  define DEBUG(s)   do {} while(0)
# endif

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
int             kthxbye(int status);

#endif
