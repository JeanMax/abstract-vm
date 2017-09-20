// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   abstract-vm.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:31:36 by mc                #+#    #+#             //
//   Updated: 2017/09/20 23:43:34 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP

# include <iostream>
# include <stack>
# include "operand/IOperand.hpp"
# include "operand/OperandFactory.hpp"


# define CLR_BLACK   "\033[30;01m"
# define CLR_RED     "\033[31;01m"
# define CLR_GREEN   "\033[32;01m"
# define CLR_YELLOW  "\033[33;01m"
# define CLR_BLUE    "\033[34;01m"
# define CLR_MAGENTA "\033[35;01m"
# define CLR_CYAN    "\033[36;01m"
# define CLR_WHITE   "\033[37;01m"
# define CLR_RESET   "\033[0m"


# ifdef VERBOSE
#  define MSG(s)     std::cout << CLR_BLUE    "[MSG] "     CLR_RESET << s << std::endl
#  define ERROR(s)   std::cerr << CLR_RED     "[ERROR] "   CLR_RESET << s << std::endl; kthxbye(EXIT_FAILURE)
#  define WARNING(s) std::cerr << CLR_YELLOW  "[WARNING] " CLR_RESET << s << std::endl
#  define DEBUG(s)   std::cout << CLR_MAGENTA "[DEBUG] "   CLR_RESET << s << std::endl
# else
#  define MSG(s)     std::cout << s << std::endl
#  define ERROR(s)   std::cerr << s << std::endl; kthxbye(EXIT_FAILURE)
#  define WARNING(s) std::cerr << s << std::endl
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
void            kthxbye(int status);

#endif
