//
//  cHquery.hpp
//  cHorizo
//
//  Created by Josh Cardenzana on 3/27/17.
//  Copyright © 2017 Josh Cardenzana. All rights reserved.
//

#ifndef cHquery_h
#define cHquery_h

#include <string>

#include "cHconnect.hpp"

class cHquery {
public:
    
    /* Constructors/Destructors */
    
    cHquery();
    virtual ~cHquery();
    
    /******  METHODS  ******/
    
    void SetQuery(const std::string& query);
    std::string SubmitQuery();
    
    /****** VARIABLES ******/
    
protected:
    
    /******  METHODS  ******/
    
    
    
    /****** VARIABLES ******/
    
    std::string h_query_msg;
    
private:
};

#endif /* cHquery_h */
