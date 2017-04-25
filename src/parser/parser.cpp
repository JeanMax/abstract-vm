// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   parser.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 03:13:02 by mc                #+#    #+#             //
//   Updated: 2017/04/25 13:33:13 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "parser.hpp"

static eOperandType get_type(std::string type)
{
	switch (type[3]) {
	case '8':
		return Int8;
		break;
	case '1':
		return Int16;
		break;
	case '3':
		return Int32;
		break;
	case 'a':
		return Float;
		break;
	case 'b':
		return Double;
		break;
	}

	return Unknown;		;//TODO: error

}

void parse_operand(std::string s_type, std::string s_value)
{
	std::cout << "type: " << s_type << std::endl;
	std::cout << "value: " << s_value << std::endl;

	// eOperandType type = get_type(s_type);
	// double d; //std:stod
	// float f;//std:stof
	// int i;//std:stoi


	std::cout << "TYPE: " << get_type(s_type) << std::endl;
}
