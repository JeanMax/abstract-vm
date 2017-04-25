// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   lexer.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 03:02:05 by mc                #+#    #+#             //
//   Updated: 2017/04/25 12:45:36 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "lexer.hpp"

void lexer(char *filename)
{
	std::regex  empty_reg(
		START_REGEX
		END_REGEX
		);

	std::regex  instr_reg(
		START_REGEX
		"(pop|dump|add|sub|mul|div|mod|print|exit)"
		END_REGEX
		);

	std::regex  instr_with_value_reg(
		START_REGEX
		"(push|assert)"
		"[[:space:]]+"
		"("
		    "(int(8|16|32))"
		    "\\((" N_REGEX ")\\)"
		"|"
		    "(float|double)"
		    "\\((" Z_REGEX ")\\)"
		")"
		END_REGEX
		);

	std::ifstream file;
	std::string   input;
	std::smatch   match;

	if (filename) {
		file.open(filename); //TODO: catch error
	}

	while (filename ? !file.eof() : !!std::cin) {
		getline(filename ? file : std::cin, input, SEP_CHAR); //TODO: catch error

		if (regex_match(input, match, instr_reg)) {
			std::cout << "op: " << match[1] << std::endl;
		} else if (regex_match(input, match, instr_with_value_reg)) {
			std::cout << "op: " << match[1] << std::endl;
			if (match[3].matched) {
				parse_operand(match[3], match[4]);
			} else {
				parse_operand(match[6], match[7]);
			}
		} else if (!regex_match(input, empty_reg)) {
			std::cout << "'" << input << "'" << ": nop." << std::endl; //TODO
		}
	}


	if (filename) {
		file.close(); //TODO: catch error
	}
}
