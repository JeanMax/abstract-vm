// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:27:03 by mc                #+#    #+#             //
//   Updated: 2017/04/25 17:00:36 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

/*
** todo
*/

#include "abstract-vm.hpp"

OperandFactory const *g_factory = new OperandFactory;
std::forward_list<IOperand const *> g_stack = {};

int kthxbye(int status)
{
	delete g_factory;
	while (!g_stack.empty()) {
		delete g_stack.front();
		g_stack.pop_front();
	}

	exit(status);
	return status;
}

int		main(int ac, char **av)
{
	if (ac > 2) {
		std::cerr << "Usage: " << *av << "[FILE]" << std::endl;
		return kthxbye(EXIT_FAILURE);
	}

	lexer(*(av + 1));

	return kthxbye(EXIT_SUCCESS);
}
