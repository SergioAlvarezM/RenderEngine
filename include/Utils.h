/**
 * @file Utils.h
 * @author Sergio Alvarez Medina (ser.alvarez1998@gmail.com)
 * @brief File with the utility functions that the engine uses.
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef RENDERENGINE_UTILS_H
#define RENDERENGINE_UTILS_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

/**
 * @brief Split a string.
 * 
 * @param line String to be splitted.
 * @param character Character to search for the split.
 * @return std::vector<std::string> vector with the elements of the string.
 */
std::vector<std::string> split(std::string line, char character)
{
    std::vector<std::string> parsed_line;
    std::string word_analized = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == character)
        {
            parsed_line.push_back(word_analized);
            word_analized = "";
        }
        else if (i == line.length() - 1)
        {
            word_analized += line[i];
            parsed_line.push_back(word_analized);
        }
        else
        {
            word_analized += line[i];
        }
    }

    return parsed_line;
}

#endif