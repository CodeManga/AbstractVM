/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgReader.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 09:09:45 by hmthimun          #+#    #+#             */
/*   Updated: 2018/07/30 16:38:00 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGREADER_HPP
# define ARGREADER_HPP

# include <iostream>
# include <string.h>
# include <vector>
# include <sstream>

# include "Exceptions.hpp"

/*
 * Class: ArgReader
 * -------------------------------
 * Class to parse all instructions from a file or std input using arguments.
 * Has its own excpetions for handling files and Syntax when parsing instructions.
 */

class ArgReader{
protected:

    /**********************************************************************/
    /*                           Properties                               */
    /**********************************************************************/

    std::string                 _line;          // get line content from a file/stdin
    std::vector<std::string>    _words;         // broken down line into words
    int                         _NoOfWords;     // number of words in a line


    /**********************************************************************/
    /*                           Exceptions                               */
    /*          This part contains a top-level exception handler          */
    /*                    to print exceptions thrown                      */
    /**********************************************************************/

    /*
     * Class: BadFileException
     * -------------------------------
     * Class used to throw an exception when parsing instructions from a file.
     * The class will throw an exception if the file is invalid
     */
    class InvalidFileException : public Exceptions {
        virtual const char  *what(void) const throw(){
            return ("[ FileException ] : Invalid file");
        }
    };

    /*
     * Class: UnknownInstructionException
     * -------------------------------
     * Class used to throw an exception if instructions parsed from a file do not
     * match instructions in the VM
     */
    class UnknownInstructionException : public Exceptions {
        virtual const char  *what(void) const throw(){
            return ("[ InstrctionException ] : Instruction is unknown");
        }
    };
    
    /*
     * Class: BadInstructionException
     * -------------------------------
     * Class used to throw an exception if instruction(s) parsed from a file or stdin
     * are/is invalid
     */
    class BadInstructionException : public Exceptions {
        virtual const char  *what(void) const throw(){
            return ("[ InstrctionException ] : Instruction is of a bad format");
        }
    };

    /*
     * Class: UnknownTypeException
     * -------------------------------
     * Class used to throw an exception if type parsed from a file do not
     * match type in the VM
     */
    class UnknownTypeException : public Exceptions {
        virtual const char  *what(void) const throw(){
            return ("[ TypeException ] : Type unknown");
        }
    };


public:

    /*
     * Constructor: ArgReader
     * Usage: ArgReader set;
     * ----------------------
     * Initializes an empty .
     */
    ArgReader();

    /*
     * Copy Constructor: ArgReader
     * Usage: ArgReader set1, ArgReader set2(set1);
     * --------------------------------------------
     * Initializes an empty .
     */
    ArgReader(ArgReader const &ref);

    /*
     * Destructor: ~ArgReader()
     * ------------------------
     * Frees any heap storage.
     */
    virtual ~ArgReader();

    /*
     * Operator: =
     * Usage: set1 = set2
     * -------------------
     * Returns this object which contains the same data from the ref object.
     */
    ArgReader   & operator= (ArgReader const &ref);

    /*
     * Method: argReader
     * Usage: arg.argReader();
     * -----------------------
     * This method takes a line of data(string without a new line charector)
     * And breaks it down to individual words. Multiple whitespaces are converted
     * to a single white space. The method will save all the words inside a vector
     * and keep count of the number of words stored. This method will trim whitespaces
     * int the begining of a line and tryling whitespaces. This is due to stringstream
     */
    void                        argReader(std::string);

    /*
     * Method: getVector
     * Usage: v.getVector();
     * ---------------------
     * Returns a vector of words broken down from a line parsed from a file
     * or stdin
     */
    std::vector<std::string>    getVector(void) const;

    /*
     * Method: getNoOfWords
     * Usage: arg.getNoOfWords();
     * --------------------------
     * Returns the total number of words from a line parsed from a file or stdin.
     * White spaces are treated as one word
     */
    int                         getNoOfWords(void) const;

    /*
     * Method: setVector
     * Usage: v.setVector(words);
     * --------------------------
     * Sets a vector of broken down words from a line or stdin 
     */
    void                        setVector(std::vector<std::string> v);

    /*
     * Method: setNoOfWords
     * Usage: arg.setNoOfWords(counter);
     * ---------------------------------
     * Sets the number of words that are broken down from a line or stdin
     */
    void                        setNoOfWords(int num);
};

#endif