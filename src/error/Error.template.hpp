// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Error.template.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mc </var/spool/mail/mc>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/20 21:48:43 by mc                #+#    #+#             //
//   Updated: 2017/09/20 22:27:48 by mc               ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ERROR_TEMPLATE_HPP
# define ERROR_TEMPLATE_HPP

# include "../abstract-vm.hpp"

# include <stdexcept>

template <typename MOTHER_EXCEPTION>
class Error: public MOTHER_EXCEPTION {
    private:
        std::string _what;

    public:
        /*
        ** constructor
        */
        Error(std::string what = "Error") throw() :
            MOTHER_EXCEPTION(what.c_str()),
            _what(what)
        {
            DEBUG(this->what() << " constructor");
        }

        Error(Error const &copy) throw() : std::domain_error(copy.what())
        {
            *this = copy;
            DEBUG(copy.what() << " copy");
        }


        /*
        ** destructor
        */
        ~Error(void) throw()
        {
            DEBUG(this->what() << " destructor");
        }


        /*
        ** operator overload
        */
        Error const &operator=(Error const &copy) throw()
        {
            (void)copy; //TODO
            return *this;
        }


        /*
        ** public
        */
        const char* what() const throw()
        {
            return this->_what.c_str();
        }
};

#endif
