// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OperandFactory.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc <mc.maxcanal@gmail.com>                 +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/03/21 18:50:52 by mc                #+#    #+#             //
//   Updated: 2017/09/21 21:38:39 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

# include "IOperand.hpp"
# include <stdint.h> //int{8,16,32}_t
# include <float.h> //{FLT,DBL}_{MIN,MAX}

class OperandFactory {
    public:
        OperandFactory(void);
        OperandFactory(OperandFactory const &copy);
        ~OperandFactory(void);
        OperandFactory const &operator=(OperandFactory const &copy);

        IOperand const * createOperand(eOperandType type, std::string const &value) const;
        double           getMin(eOperandType type) const;
        double           getMax(eOperandType type) const;

    private:
        IOperand const * createInt8(std::string const &value) const;
        IOperand const * createInt16(std::string const &value) const;
        IOperand const * createInt32(std::string const &value) const;
        IOperand const * createFloat(std::string const &value) const;
        IOperand const * createDouble(std::string const &value) const;

        const double _min[NUMBER_OF_TYPES] = {INT8_MIN, INT16_MIN, INT32_MIN, FLT_MIN, DBL_MIN};
        const double _max[NUMBER_OF_TYPES] = {INT8_MAX, INT16_MAX, INT32_MAX, FLT_MAX, DBL_MAX};
};

#endif
