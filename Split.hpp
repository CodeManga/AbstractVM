/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Split.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 23:43:38 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/19 13:11:15 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_HPP
# define SPLIT_HPP

# include <stdio.h>
# include <string>
# include <iostream>
# include <vector>

# include "Exceptions.hpp"

class Split {
    protected:
        std::string _instructTable[11];
        std::string _type;
        std::string _value;
        std::string _instructions;
        int         _InstructNo;

        
    public:
        Split();
        Split(Split const &ref);
        virtual~Split();

        Split   & operator=(Split const &ref);

        void        initInstrTable(void);
        void        execute(std::vector<std::string> words, int NoOfWords);
        void        setInstrut(std::string instructions);
        void        setNoOfInstruct(int num);
        void        setValue(std::string value);

        std::string getInstruct(void) const;
        std::string getValue(void) const;
        int         getInstructNo(void) const;

};

#endif