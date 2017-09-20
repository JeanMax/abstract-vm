// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   DivideZeroError.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/20 17:22:41 by mc                #+#    #+#             //
//   Updated: 2017/09/20 18:35:45 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DIVIDEZEROERROR_HPP
# define DIVIDEZEROERROR_HPP

# include "../abstract-vm.hpp"

# include <stdexcept>

class DivideZeroError: public std::domain_error {
    public:
        DivideZeroError(void) throw();
		DivideZeroError(DivideZeroError const &copy) throw();
		~DivideZeroError(void) throw();
		DivideZeroError const &operator=(DivideZeroError const &copy) throw();
        const char* what() const throw();

    private:
        std::string _what;
};

#endif
