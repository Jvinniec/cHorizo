//
//  ch001_TestConnection.cpp
//  cHorizo
//
//  Created by Josh Cardenzana on 3/24/17.
//  Copyright © 2017 Josh Cardenzana. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "cHorizo.hpp"

bool quit(cHconnect& horizons);

int main(int argc, char** argv)
{
    // Make a connection to the telnet
    try {
        std::cout << "Connecting to server ...";
        std::cout.flush();
        cHconnect horizons(false) ;
        
        horizons.Connect(true);
        
        // Print out success or failure
        if (horizons.TestConnection()) {
            std::cout << " SUCCESS!" << std::endl;
        } else {
            std::cout << " FAILURE!" << std::endl;
        }
        
        // Create a server request
        
        
        // Send the server request
        // Attempt to quit the server
        quit(horizons);
        
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
        return 1;
    }
    
    return 0;
}


bool quit(cHconnect& horizons)
{
    // Send 'quit' to the server
    std::cout << "Sending 'quit' to server ... ";
    std::cout.flush();
    if (!horizons.Send("?\n")) {
        std::cout << "FAILURE!" << std::endl;
        return false;
    } else {
        std::cout << "SUCCESS!" << std::endl;
        std::cout << "Server reply:\n" << std::endl;
        // Try to catch the reply
        std::string reply = horizons.Recv();
        std::cout << reply << std::endl;
    }
    return true;
}
