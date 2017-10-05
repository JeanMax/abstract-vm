// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   lexer.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 03:02:52 by mc                #+#    #+#             //
//   Updated: 2017/10/05 17:26:47 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LEXER_HPP
# define LEXER_HPP

# include "../abstract-vm.hpp"

# include <fstream>
# include <regex>

# define COMMENT_REGEX "(;+.*$|$)"
# define START_REGEX   "^[[:space:]]*"
# define END_REGEX     "[[:space:]]*" COMMENT_REGEX
# define N_REGEX       "[-]?[0-9]+"
# define Z_REGEX       "[-]?[0-9]+\\.[0-9]+"
# define STDIN_END     ";;"
# define SEP_CHAR      '\n'

#endif
