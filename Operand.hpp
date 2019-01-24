/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 02:53:52 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/19 13:04:15 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEREAND_HPP
# define OPEREAND_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <limits>

# include "IOperand.hpp"
# include "Exceptions.hpp"

template <typename T>
class Operand : public IOperand {
private:
    eOperandType    _type;
    std::string      _valueToString;
    int             _precision;
    T               _value;

public:
    explicit    Operand(eOperandType type, const double &value){
        std::stringstream   ss;

        _type = type;
        _precision = type;
        if (value < std::numeric_limits<T>::min())
            throw Exceptions("[LimitExcepption] : Underflow");
        else if (value > std::numeric_limits<T>::max())
            throw Exceptions("[LimitExcepption] : Overflow");
        _value = value;
        if (type == INT8)
            ss << value;
        else
            ss << _value;
        ss >> _valueToString;
    }

    virtual std::string const   &toString() const{
        return (_valueToString);
    }

    virtual int                 getPrecision() const{
        return (_precision);
    }

    virtual eOperandType        getType() const{
        return (_type);
    }

    virtual T                   getValue() const{
        return (_value);
    }

    virtual IOperand            *operator+(const IOperand &ref) const{
        IOperand            *op = NULL;
        std::stringstream   ss;
        eOperandType        type;
        double              num;

        ss << ref.toString();
        ss >> num;
        
        if (_precision >= ref.getPrecision())
            type = _type;
        else
            type = ref.getType();

        if (type == INT8)
            op = new Operand<char>(type, _value + num);
        else if (type == INT16)
            op = new Operand<short>(type, _value + num);
        else if (type == INT32)
            op = new Operand<int>(type, _value + num);
        else if (type == FLOAT)
            op = new Operand<float>(type, _value + num);
        else if (type == DOUBLE)
            op = new Operand<double>(type, _value + num);
        return (op);
    }

    virtual IOperand            *operator-(const IOperand &ref) const{
        IOperand            *op = NULL;
        std::stringstream   ss;
        eOperandType        type;
        double              num;

        ss << ref.toString();
        ss >> num;
        
        if (_precision >= ref.getPrecision())
            type = _type;
        else
            type = ref.getType();

        if (type == INT8)
            op = new Operand<char>(type, _value - num);
        else if (type == INT16)
            op = new Operand<short>(type, _value - num);
        else if (type == INT32)
            op = new Operand<int>(type, _value - num);
        else if (type == FLOAT)
            op = new Operand<float>(type, _value - num);
        else if (type == DOUBLE)
            op = new Operand<double>(type, _value - num);
        return (op);
    }

    virtual IOperand            *operator*(const IOperand &ref) const{
        IOperand            *op = NULL;
        std::stringstream   ss;
        eOperandType        type;
        double              num;

        ss << ref.toString();
        ss >> num;
        
        if (_precision >= ref.getPrecision())
            type = _type;
        else
            type = ref.getType();

        if (type == INT8)
            op = new Operand<char>(type, _value * num);
        else if (type == INT16)
            op = new Operand<short>(type, _value * num);
        else if (type == INT32)
            op = new Operand<int>(type, _value * num);
        else if (type == FLOAT)
            op = new Operand<float>(type, _value * num);
        else if (type == DOUBLE)
            op = new Operand<double>(type, _value * num);
        return (op);
    }

    virtual IOperand            *operator/(const IOperand &ref) const{
        IOperand            *op = NULL;
        std::stringstream   ss;
        eOperandType        type;
        double              num;

        ss << ref.toString();
        ss >> num;
        
        if (num == 0)
            throw Exceptions("[DivisionException] : Dividing by zero is an invalid calculation");
        
        if (_precision >= ref.getPrecision())
            type = _type;
        else
            type = ref.getType();

        if (type == INT8)
            op = new Operand<char>(type, _value / num);
        else if (type == INT16)
            op = new Operand<short>(type, _value / num);
        else if (type == INT32)
            op = new Operand<int>(type, _value / num);
        else if (type == FLOAT)
            op = new Operand<float>(type, _value / num);
        else if (type == DOUBLE)
            op = new Operand<double>(type, _value / num);
        return (op);
    }

    virtual IOperand            *operator%(const IOperand &ref) const{
        IOperand            *op = NULL;
        std::stringstream   ss;
        eOperandType        type;
        int                 num;

        ss << ref.toString();
        ss >> num;
        
        if (_precision >= ref.getPrecision())
            type = _type;
        else
            type = ref.getType();

        if (type == FLOAT)
            throw Exceptions("[ModulusException] : Cannot use modulo with a float");
        else if (type == DOUBLE)
            throw Exceptions("[ModulusException] : Cannot use modulo with a double");

        op = new Operand(type, (int)_value % num);
        return (op);
    }

    std::ostream                &operator<<(std::ostream &o){
        o << this->getValue();
        return (o);
    }
};

std::ostream                    &operator<<(std::ostream &o, IOperand const &rhs);

#endif