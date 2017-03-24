//
//  cHconnect.hpp
//  cHorizo
//
//  Created by Josh Cardenzana on 3/23/17.
//  Copyright © 2017 Josh Cardenzana. All rights reserved.
//

#ifndef CHCONNECT_HPP
#define CHCONNECT_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>

class cHconnect {
public:
    // Default constructor
    cHconnect(bool connect=true) ;
    
    // Deconstructor
    virtual ~cHconnect();
    
    /******  METHODS  ******/
    
    // Establish the connection
    bool Connect();
    
    // Close the connection
    bool Disconnect();
    
    // Send/receive data to/from the server
    void Send();
    void Recv();
    
    // Get information regarding the connection
    bool TestConnection();
    
    
    /****** VARIABLES ******/
    
    int h_portnum = 6775;                  ///< Port to connect to
    std::string h_url = "horizons.jpl.nasa.gov";
    //std::string h_url = "128.149.23.134";
    
    
protected:
    
    /******  METHODS  ******/
    void Init();
    
    /****** VARIABLES ******/
    struct sockaddr h_sockaddr;
    struct hostent *h_server;
    struct sockaddr_in h_serv_addr;
    bool h_isConnected = false;         ///< True when connected to the service
    int h_socket_ref = -1;              ///< Reference returned by call to 'socket()'
    
private:
    
};

#endif /* CHCONNECT_HPP */
