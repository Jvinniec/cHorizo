//
//  MercuryQuery.cpp
//  cHorizo
//
//  Created by Josh Cardenzana on 3/23/17.
//  Copyright © 2017 Josh Cardenzana. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "cHorizo.hpp"

int main(int argc, char** argv)
{
    // Make a connection to the telnet
    try {
        std::cout << "Connecting to server ...";
        std::cout.flush();
        cHconnect horizons(false) ;
        
        horizons.Connect();
        
        // Print out success or failure
        if (horizons.TestConnection()) {
            std::cout << " SUCCESS!" << std::endl;
        } else {
            std::cout << " FAILURE!" << std::endl;
        }
        
        // Create a server request
        
        
        // Send the server request
        
        
        // Recieve the results of the request
        
        
        // Print the results of the request
        
        
        // Close the connection
        std::cout << "Closing connection ...";
        std::cout.flush();
        horizons.Disconnect();
        
        // Check whether the connection is still open or closed
        if (!horizons.TestConnection()) {
            std::cout << " SUCCESS!" << std::endl;
        } else {
            std::cout << " FAILURE!" << std::endl;
        }
        
    } catch (cHexception & e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}
