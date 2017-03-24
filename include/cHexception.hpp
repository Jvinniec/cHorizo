//
//  cHexception.hpp
//  cHorizo
//
//  Created by Josh Cardenzana on 3/23/17.
//  Copyright © 2017 Josh Cardenzana. All rights reserved.
//

#ifndef CHEXCEPTION_HPP
#define CHEXCEPTION_HPP

#include <iostream>
#include <exception>
#include <errno.h>
#include <string.h>
#include <string>

class cHexception : public std::exception {
public:
    // Create the error from the 'errno' error code
    cHexception()
    {
        error_msg = strerror(errno);
    }
    
    // create the error message from a supplied message
    cHexception(const std::string& msg)
    {
        error_msg = msg;
    }
    
    // Prints out the exception
    virtual const char* what() const throw()
    {
        return error_msg.c_str();
    }
    
protected:
    
    std::string error_msg;
};

#endif /* CHEXCEPTION_HPP */
