// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 18:50:52 by mc                #+#    #+#             //
//   Updated: 2017/09/20 22:41:26 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include "IOperand.hpp"

class OperandFactory {
	public:
		OperandFactory(void);
		OperandFactory(OperandFactory const &copy);
		~OperandFactory(void);
		OperandFactory const &operator=(OperandFactory const &copy);

		IOperand const * createOperand(eOperandType type, std::string const &value) const;

	private:
		IOperand const * createInt8(std::string const &value) const;
		IOperand const * createInt16(std::string const &value) const;
		IOperand const * createInt32(std::string const &value) const;
		IOperand const * createFloat(std::string const &value) const;
		IOperand const * createDouble(std::string const &value) const;
};

#endif
