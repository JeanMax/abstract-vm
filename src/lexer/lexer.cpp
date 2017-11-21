// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   lexer.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 03:02:05 by mc                #+#    #+#             //
//   Updated: 2017/11/21 12:41:12 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "lexer.hpp"

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

std::stringstream g_syntax_errors;


static bool read_loop(const char *filename, std::ifstream &file, bool interactive,
                      bool ret = true, unsigned int line_count = 1)
{
    std::string   input;
    std::smatch   match;

    if (line_count == LINES_LIMIT) {
        throw Error<std::runtime_error>("Input too long.");
    }

    if (filename ? file.eof() : !std::cin) {
        return ret;
    }

    try {
        getline(filename ? file : std::cin, input, SEP_CHAR);
    } catch (const std::ifstream::failure &e) {
        return ret;
    }

    if (!filename && input == STDIN_END) {
        return ret;
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
        if (interactive) {
            WARNING("Line " << line_count
                    << ": Syntax error: '" << input << "'.");
        } else {
            g_syntax_errors << "Line " << line_count
                          << ": Syntax error: '" << input << "'." << std::endl;
            ret = false;
        }
    }

    if (interactive) {
        exec_tokens();
    }

    return read_loop(filename, file, interactive, ret, line_count + 1);
}

void lexer(const char *filename, bool interactive)
{
    std::ifstream file;
    bool lexing_success;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    if (filename) {
        try {
            file.open(filename);
        } catch (const std::ifstream::failure &e) {
            throw Error<std::runtime_error>(
                "Could not open '"
                + std::string(filename ? filename : "stdin")
                + "'."
            );
        }
    }

    lexing_success = read_loop(filename, file, interactive);

    if (filename) {
        try {
            file.close();
        } catch (const std::ifstream::failure &e) {
            throw Error<std::runtime_error>(
                "Could not close '"
                + std::string(filename ? filename : "stdin")
                + "'."
            );
        }
    }

    if (lexing_success) {
        exec_tokens();
        throw Error<std::logic_error>("No exit instruction");
    }
}
