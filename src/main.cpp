// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:27:03 by mc                #+#    #+#             //
//   Updated: 2017/09/27 14:06:47 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "abstract-vm.hpp"

OperandFactory const *g_factory = new OperandFactory;
std::stack<IOperand const *> g_stack = {};

void   kthxbye(int status)
{
    delete g_factory;
    while (!g_stack.empty()) {
        delete g_stack.top();
        g_stack.pop();
    }

    exit(status);
}

int     main(int ac, char **av)
{
    if (ac > 2) {
        ERROR("Usage: " << *av << " [FILE]");
        kthxbye(EXIT_FAILURE);
    }

    try {
        lexer(*(av + 1));
    } catch (std::exception const &e) {
        ERROR(e.what());
        kthxbye(EXIT_FAILURE);
    }

    return EXIT_FAILURE;
}
