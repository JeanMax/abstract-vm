// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/20 22:27:03 by mc                #+#    #+#             //
//   Updated: 2017/03/21 03:09:59 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

/*
** todo
*/

#include "abstract-vm.hpp"

int		main(int ac, char **av)
{
	if (ac > 2) {
		std::cerr << "Usage blabla" << std::endl; //TODO
		return 42;
	}

	lexer(*(av + 1));

	return 0;
}
