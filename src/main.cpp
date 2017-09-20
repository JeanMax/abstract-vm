// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:27:03 by mc                #+#    #+#             //
//   Updated: 2017/09/20 19:22:19 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

/*
** todo
*/

#include "abstract-vm.hpp"

OperandFactory const *g_factory = new OperandFactory;
std::stack<IOperand const *> g_stack = {};

int kthxbye(int status)
{
	delete g_factory;
	while (!g_stack.empty()) {
		delete g_stack.top();
		g_stack.pop();
	}

	exit(status);
	return status;
}

int		main(int ac, char **av)
{
	if (ac > 2) {
		ERROR("Usage: " << *av << " [FILE]");
		return kthxbye(EXIT_FAILURE);
	}

	lexer(*(av + 1));

	return kthxbye(EXIT_SUCCESS);
}
