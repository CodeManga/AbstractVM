/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 09:09:16 by hmthimun          #+#    #+#             */
/*   Updated: 2018/07/25 02:03:36 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <string>
# include <exception>

/*
 * Class: Exceptions
 * -------------------------------
 * This class contains a top-level exception handler to print exceptions thrown   
 */
class Exceptions : public std::exception{
    private:
        std::string _msg;

    public:
        /*
         * Constructor: Exceptions
         * ----------------------
         * Initializes an empty .
         */
        Exceptions(void);

        /*
         * Constructor: Exceptions
         * ----------------------
         * Initializes an exception with a massage from a throw.
         */
        Exceptions(std::string const &msg) throw();

        /*
         * Copy Constructor: Exceptions
         * Usage: Exceptions set1, Exceptions set2(set1);
         * --------------------------------------------
         * Copies an exception.
         */
        Exceptions(Exceptions const &ref);

        /*
         * Destructor: ~Exceptions()
         * --------------------------
         * Frees any heap storage.
         */
        virtual ~Exceptions() throw();


        /*
         * Operator: =
         * Usage: set1 = set2
         * -------------------
         * Returns this object which contains the same data from the ref object.
         */
        Exceptions  & operator=(Exceptions const &ref);

        /*
         * Method: what
         * -------------------
         * Returns the exception massage from a throw
         */
        virtual const char  *what(void) const throw();
};

#endif