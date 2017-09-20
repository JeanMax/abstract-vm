// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   lexer.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 03:02:05 by mc                #+#    #+#             //
//   Updated: 2017/09/21 00:32:18 by mc               ###   ########.fr       //
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

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    if (filename) {
        try {
            file.open(filename);
        } catch (const std::ifstream::failure &e) {
            ERROR("Could not open '" << filename << "'.");
        }
    }

    while (filename ? !file.eof() : !!std::cin) {
        try {
            getline(filename ? file : std::cin, input, SEP_CHAR);
        } catch (const std::ifstream::failure &e) {
            ERROR("Could not read '" << (filename ? filename : "stdin") << "'.");
        }

        if (!filename && input == STDIN_END) {
            break;
        }

        if (regex_match(input, match, instr_reg)) {
            parse_operator(match[1], NULL);
        } else if (regex_match(input, match, instr_with_value_reg)) {
            if (match[3].matched) {
                parse_operator(match[1], parse_operand(match[3], match[5]));
            } else {
                parse_operator(match[1], parse_operand(match[6], match[7]));
            }
        } else if (!regex_match(input, empty_reg)) {
            WARNING("Syntax error: '" << input << "'.");
        }
    }


    if (filename) {
        try {
            file.close();
        } catch (const std::ifstream::failure &e) {
            ERROR("Could not close '" << filename << "'.");
        }
    }
}
