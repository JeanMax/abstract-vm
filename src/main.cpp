// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:27:03 by mc                #+#    #+#             //
//   Updated: 2017/10/05 17:36:32 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "abstract-vm.hpp"

OperandFactory const *g_factory = new OperandFactory;
std::stack<IOperand const *> g_stack = {};
extern std::stringstream g_syntax_errors;

void   kthxbye(int status)
{
    delete g_factory;
    while (!g_stack.empty()) {
        delete g_stack.top();
        g_stack.pop();
    }

    std::cerr << g_syntax_errors.str();

    exit(status);
}

int     main(int ac, char **av)
{
    if (ac > 3 || (ac == 3 && strcmp(*(av + 1), "-i"))) {
        ERROR("Usage: " << *av << " [-i] [FILE]");
        kthxbye(EXIT_FAILURE);
    }

    try {
        ++av;
        if (*av && !strcmp(*av, "-i")) {
            lexer(*++av, true);
        } else {
            lexer(*av, false);
        }
    } catch (std::exception const &e) {
        ERROR(e.what());
    }

    kthxbye(EXIT_SUCCESS);
    return EXIT_FAILURE;
}
