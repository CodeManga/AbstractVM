/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 06:34:28 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/19 13:11:17 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include <iomanip>
#include <algorithm>
#include "Exceptions.hpp"

Factory::Factory()
{
    _funcList[0] = &Factory::createInt8;
    _funcList[1] = &Factory::createInt16;
    _funcList[2] = &Factory::createInt32;
    _funcList[3] = &Factory::createFloat;
    _funcList[4] = &Factory::createDouble;

    _tab[0] = "INT8";
    _tab[1] = "INT16";
    _tab[2] = "INT32";
    _tab[3] = "FLOAT";
    _tab[4] = "DOUBLE";

    return ;
}

Factory::Factory(Factory const &ref)
{
    return ;
}

Factory::~Factory()
{
    return ;
}

void                        Factory::execFunction(int instructNo, IOperand *op)
{
    if (instructNo == 0)
        print();
    else if (instructNo == 1)
        pop();
    else if (instructNo == 2)
        dump();
    else if (instructNo == 3)
        add();
    else if (instructNo == 4)
        sub();
    else if (instructNo == 5)
        mul();
    else if (instructNo == 6)
        div();
    else if (instructNo == 7)
        mod();
    else if (instructNo == 8)
        exit();
    else if (instructNo == 9)
        push(op);
    else if (instructNo == 10)
        assert(op);
    return ;
}

bool                        Factory::findTypeNo(const std::string &tmp)
{
    for (int i = 0; i < 5; i++){
        if (tmp.compare(Factory::getTab(i)) == 0){
            setTypeNo(i);
            return (true);
        }
    }
    throw Exceptions("[SyntaxException] : type not found");
}
std::string                 Factory::getTab(int i)
{
    return (_tab[i]);
}

bool                        Factory::getIntType(const std::string &value)
{
    std::string     tmp;
    int             end = value.find('(');
    tmp.append(value, 0, end);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), toupper);

    if (findTypeNo(tmp) == false)
        return (false);

    if (this->_typeNo == 0)
        _type = INT8;
    else if(this->_typeNo == 1)
        _type = INT16;
    else if(this->_typeNo == 2)
        _type = INT32;
    else if(this->_typeNo == 3)
        _type = FLOAT;
    else if(this->_typeNo == 4)
        _type = DOUBLE;

    return (true);
}

void                        Factory::exec(int instructNo, std::string value)
{
    if (value == "" && instructNo >= 9)
        throw Exceptions("[SyntaxException] : Invalid Syntax");
    
    std::string tmp;
    IOperand    *op = NULL;

    if (value != ""){
        if (getIntType(value) == false)
            return ;
        
        int end = value.find(')');
        int start = value.find('(');
        int len = value.length();

        if (end != (len - 1))
            throw Exceptions("[SyntaxException] : Missing end of parenthesis");
        
        tmp.append(value, (start + 1), (end - start - 1));

        if (tmp == "")
            throw Exceptions("[SyntaxException] : Invalid value");
        
        int i = 0;
        while (tmp[i]){
            if (isdigit(tmp[i]) || tmp[i] == '.')
                i++;
            else
                throw Exceptions("[SyntaxException] : Invalid value");
            
        }

        op = createOperand(_type, tmp);
    }
    execFunction(instructNo, op);
    return ;
}

IOperand		            *Factory::createInt8(const std::string &value)
{
    IOperand            *op;
    std::stringstream   ss;
    double              num;

    ss << value;
    ss >> num;

    op = new Operand<char>(INT8, num);
    return (op);
}

IOperand	            	*Factory::createInt16(const std::string &value)
{
    IOperand            *op;
    std::stringstream   ss;
    double              num;

    ss << value;
    ss >> num;

    op = new Operand<short>(INT16, num);
    return (op);
}

IOperand		            *Factory::createInt32(const std::string &value)
{
    IOperand            *op;
    std::stringstream   ss;
    double              num;

    ss << value;
    ss >> num;

    op = new Operand<int>(INT32, num);
    return (op);
}

IOperand		            *Factory::createFloat(const std::string &value)
{
    IOperand            *op;
    std::stringstream   ss;
    double              num;

    ss << value;
    ss >> num;

    op = new Operand<float>(FLOAT, num);
    return (op);
}

IOperand		            *Factory::createDouble(const std::string &value)
{
    IOperand            *op;
    std::stringstream   ss;
    double              num;

    ss << value;
    ss >> num;

    op = new Operand<double>(DOUBLE, num);
    return (op);
}


IOperand                    *Factory::createOperand(eOperandType type, const std::string &value)
{
    IOperand *op = (this->*_funcList[type])(value);
    return (op);
}


void                        Factory::push(IOperand *ref)
{
    _stack.push_front(ref);
    // print();
    return ;
}

void                        Factory::assert(IOperand *ref)
{
    if (_stack.size() < 1)
        throw Exceptions("[AssertException] : Stack needs to have atleat one element");
    if (ref->toString().compare(_stack.front()->toString()))
        throw Exceptions("[AssertException] : Asset failed, value on top of stack does not match");
    std::cout << "Asset passed, value on top of the stack matches" << std::endl;
    return ;
}

void                        Factory::pop()
{
    if (_stack.size() == 0)
        throw Exceptions("[StackException] : Invalid operation: stack is empty");
    _stack.pop_front();
    return ;
}

void                        Factory::dump()
{
    if (_stack.size() == 0)
        throw Exceptions("[StackException] : Invalid operation: stack is empty");

    for (std::list<IOperand *>::iterator itr = _stack.begin(); itr != _stack.end(); ++itr){
        std::cout << (*itr)->toString() << std::endl;
    }
    return ;
}

void                        Factory::exit()
{
    return ;
}

void                        Factory::print()
{
    std::stringstream   ss;
    int                 tmp;
    char                c;

    if (_stack.size() < 1)
        throw Exceptions("[PrintException] : 1 the stack must have atleast one element to print");
    
    if (_type == INT8){
        ss << _stack.front()->toString();
        std::cout << "Print: Value = " << ss.str() << std::flush;
        ss >> tmp;
        c = tmp;
        std::cout << " - Ascci value = " << c << std::endl;
    }
    else
        throw Exceptions("[PrintException] : 2 the stack must have atleast one element to print");
        
    return ;
}


IOperand                    *Factory::get()
{
    if (_stack.size() == 0)
        throw Exceptions("[ArithmeticException] : Invalid operation: stack is empty");
    return (_stack.front());
}

IOperand                    *Factory::add()
{
    if (_stack.size() < 2)
        throw Exceptions("[ArithmeticException] : Invalid operation: You need a minimum of two elements to add");

    IOperand *x = get();
    pop();

    IOperand *y = get();
    pop();

    push(*x + *y);

    IOperand *ans = get();
    return (ans);
}

IOperand                    *Factory::sub()
{
    if (_stack.size() < 2)
        throw Exceptions("[ArithmeticException] : Invalid operation: You need a minimum of two elements to sub");

    IOperand *x = get();
    pop();

    IOperand *y = get();
    pop();

    push(*x - *y);

    IOperand *ans = get();
    return (ans);
}

IOperand                    *Factory::mul()
{
    if (_stack.size() < 2)
        throw Exceptions("[ArithmeticException] : Invalid operation: You need a minimum of two elements to mul");

    IOperand *x = get();
    pop();

    IOperand *y = get();
    pop();

    push(*x * *y);

    IOperand *ans = get();
    return (ans);
}

IOperand                    *Factory::div()
{
   if (_stack.size() < 2)
        throw Exceptions("[ArithmeticException] : Invalid operation: You need a minimum of two elements to div");

    IOperand *x = get();
    pop();

    IOperand *y = get();
    pop();

    push(*x / *y);

    IOperand *ans = get();
    return (ans);
}

IOperand                    *Factory::mod()
{
    if (_stack.size() < 2)
        throw Exceptions("[ArithmeticException] : Invalid operation: You need a minimum of two elements to mod");

    IOperand *x = get();
    pop();

    IOperand *y = get();
    pop();

    push(*x % *y);

    IOperand *ans = get();
    return (ans);
}

void                        Factory::setTypeNo(int i)
{
    this->_typeNo = i;
    return ;
}

void                        Factory::setVector(std::string data)
{
    _dumpTab.push_back(data);
    return ;
}

std::vector<std::string>    Factory::getDump() const
{
    return (_dumpTab);
}
