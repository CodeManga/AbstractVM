/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 01:03:42 by hmthimun          #+#    #+#             */
/*   Updated: 2018/08/19 13:11:17 by hmthimun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArgReader.hpp"
#include "Factory.hpp"
#include "Split.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void checkEndOfFile(Split& words, Factory& stack)
{
    if (words.getInstructNo() != 8)
        std::cout << "The last instruction must be \"exit\"" << std::endl;
    if (!stack.getDump().empty()) {
        for (std::vector<std::string>::iterator itr = stack.getDump().begin(); itr != stack.getDump().end(); ++itr) {
            std::cout << *itr << std::endl;
        }
    }
}

void parseArgFromStdin(ArgReader arg, Split words, Factory stack)
{
    std::string end(";;");
    int i = 0;
    int status = 0;
    bool done = false;
    char buffer[4096];
    while (1) {
        std::cin.getline(buffer, 4096);
        if (!end.compare(buffer))
        {
            done = true;
            break;
        }
            std::cout << "bufer " << buffer << std::endl;
        i++;
        if (status == 0) {
            arg.argReader(buffer);
            words.execute(arg.getVector(), arg.getNoOfWords());
            if (words.getInstructNo() == 8)
                break;
            if (words.getValue() != "Jump")
                stack.exec(words.getInstructNo(), words.getValue());
            words.setValue("");
        }
    }
    if (!done)
        checkEndOfFile(words, stack);

}

void parseArgFromFile(ArgReader& arg, Split& words, Factory& stack, std::string file)
{
    std::string line = "";
    std::ifstream in(file.data());
    if (in.is_open()) {
        while (getline(in, line)) {
            arg.argReader(line);
            words.execute(arg.getVector(), arg.getNoOfWords());
            if (words.getInstructNo() == 8)
                break;
            if (words.getValue() != "Jump")
                stack.exec(words.getInstructNo(), words.getValue());
            words.setValue("");
        }
        checkEndOfFile(words, stack);
    }
}

int main(int argc, char** argv)
{
    ArgReader arg;
    Split words;
    Factory stack;
    try {
        if (argc == 2)
            parseArgFromFile(arg, words, stack, argv[1]);
        else
            parseArgFromStdin(arg, words, stack);
    } catch (Exceptions& e) {
        std::cout << "\033[31m"
                  << "Exception occured"
                  << ": "
                  << "\033[34m";
        std::cout << e.what() << std::endl;
    }
    return (0);
}