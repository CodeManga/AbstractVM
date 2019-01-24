/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 05:03:37 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/19 13:11:17 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_HPP
# define FACTORY_HPP

# include <iostream>
# include <string>
# include <list>
# include <vector>

# include "IOperand.hpp"
# include "Operand.hpp"
# include "Exceptions.hpp"

typedef std::list<IOperand *> opStack;

class Factory{
private:
    typedef IOperand            *(Factory::*f)(const std::string &);

    IOperand		            *createInt8(const std::string &value);
    IOperand	            	*createInt16(const std::string &value);
    IOperand		            *createInt32(const std::string &value);
    IOperand		            *createFloat(const std::string &value);
    IOperand		            *createDouble(const std::string &value);

    f                           _funcList[5];
    opStack                     _stack;
    eOperandType                _type;
    int                         _typeNo;
    std::string                 _tab[5];
    std::vector<std::string>    _dumpTab;    

public:
    Factory();
    Factory(Factory const &ref);
    ~Factory();

    Factory             &operator=(Factory const &ref);

    void                        exec(int instructNo, std::string value);
    IOperand                    *createOperand(eOperandType type, const std::string &value);
    
    void                        push(IOperand *ref);
    void                        assert(IOperand *ref);
    void                        pop();
    void                        dump();
    void                        exit();
    void                        print();

    IOperand                    *get();
    IOperand                    *add();
    IOperand                    *sub();
    IOperand                    *mul();
    IOperand                    *div();
    IOperand                    *mod();

    void                        execFunction(int instructNo, IOperand *op);
    bool                        getIntType(const std::string &value);
    bool                        findTypeNo(const std::string &tmp);
    void                        setTypeNo(int i);
    void                        setVector(std::string);
    std::string                 getTab(int i);
    std::vector<std::string>    getDump() const;

};

#endif