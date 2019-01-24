/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgReader.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 09:09:16 by hmthimun          #+#    #+#             */
/*   Updated: 2018/07/25 04:42:17 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArgReader.hpp"

ArgReader::ArgReader()
{
    _NoOfWords = 0;
    return ;
}

ArgReader::ArgReader(ArgReader const &ref)
{
    *this = ref;
    return ;
}

ArgReader::~ArgReader()
{
    return ;
}

ArgReader   & ArgReader::operator= (ArgReader const &ref)
{
    this->_NoOfWords = ref._NoOfWords;
    this->_line = ref._line;
    this->_words = ref._words;
    return (*this);
}

void                        ArgReader::argReader(std::string line)
{
    std::vector<std::string>    words;
    std::stringstream           ss;
    int                         num = 0;

    ss << line;
    while (ss)
    {
        std::string tmp;
        ss >> tmp;
        words.push_back(tmp);
        num++;
    }
    setVector(words);
    setNoOfWords(num);
    return ;
}


std::vector<std::string>    ArgReader::getVector(void) const
{
    return (_words);
}

int  ArgReader::getNoOfWords(void) const
{
    return (_NoOfWords);
}

void ArgReader::setVector(std::vector<std::string> v)
{
    _words = v;
    return ;
}

void ArgReader::setNoOfWords(int num)
{
    _NoOfWords = num;
    return ;
}