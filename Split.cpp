/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 23:43:38 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/19 13:11:17 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Split.hpp"

Split::Split()
{
    initInstrTable();
    _instructions = "";
    _value = "";
    return ;
}

Split::Split(Split const &ref)
{
    *this = ref;
    return ;
}

Split::~Split()
{
    return ;
}


Split   & Split::operator=(Split const &ref)
{
    this->_instructions = ref._instructions;
    for (int i = 0; i < 11; i++){
        this->_instructTable[i] = ref._instructTable[i];    
    }
    this->_InstructNo = ref._InstructNo;
    this->_type = ref._type;
    this->_value = ref._value;
    return (*this);
}

void        Split::initInstrTable(void)
{
    _instructTable[0] = "print";
    _instructTable[1] = "pop";
    _instructTable[2] = "dump";
    _instructTable[3] = "add";
    _instructTable[4] = "sub";
    _instructTable[5] = "mul";
    _instructTable[6] = "div";
    _instructTable[7] = "mod";
    _instructTable[8] = "exit";
    _instructTable[9] = "push";
    _instructTable[10] = "assert";
    return ;
}

void        Split::execute(std::vector<std::string> words, int NoOfWords)
{
    std::vector<std::string>::iterator itr = words.begin();
    std::string instructoion = *itr;
    std::string tmp;

    if (instructoion[0] == ';' || instructoion[0] == '\0'){
        setValue("Jump");
        return ;
    }
    for (int i = 0; i <= 10; i++){
        if (instructoion.compare(_instructTable[i]) == 0){
            if (NoOfWords > 2 && i <= 8){
                tmp = words.at(1);
                if (tmp.find(";") != 0)
                    throw Exceptions("[ SyntaxException ] : Invalid Syntax");
            } else if (NoOfWords > 3 && i >= 9){
                tmp = words.at(2);
                if (tmp.find(";") != 0)
                    throw Exceptions("[ SyntaxException ] : Invalid Syntax");
            }
            if (i >= 9){
                std::string value = words.at(1);
                setValue(value);
            }
            setInstrut(instructoion);
            setNoOfInstruct(i);
            return ;
        }
    }
    throw Exceptions("[ InstrctionException ] : Invalid instruction")
    ;
    return ;
}

void        Split::setInstrut(std::string instructions)
{
    _instructions = instructions;
    return ;
}

void        Split::setNoOfInstruct(int num)
{
    _InstructNo = num;
    return ;
}

void        Split::setValue(std::string value)
{
    _value = value;
    return ;
}

std::string Split::getInstruct(void) const
{
    return (_instructions);
}

std::string Split::getValue(void) const
{
    return (_value);
}

int         Split::getInstructNo(void) const
{
    return (_InstructNo);
}
