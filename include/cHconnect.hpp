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
    bool Connect(bool printwelcome=false);
    
    // Close the connection
    bool Disconnect();
    
    // Send/receive data to/from the server
    bool        Send(const std::string& msg);
    std::string Recv(int msg_size=-1);
    
    // Get/Set information regarding the connection
    bool        TestConnection();
    std::string GetURL() {return h_url;}
    int         GetPort() {return h_portnum;}
    void        SetURL(const std::string& url);
    void        SetPort(const int& port);
    
    /****** VARIABLES ******/
    
    
protected:
    
    /******  METHODS  ******/
    void Init();
    
    /****** VARIABLES ******/
    struct sockaddr h_sockaddr;
    struct hostent *h_server;
    struct sockaddr_in h_serv_addr;
    bool h_isConnected = false;         ///< True when connected to the service
    int h_socket_ref = -1;              ///< Reference returned by call to 'socket()'
    
    // Connection details
    
    int h_portnum = 6775;                           ///< Port to connect to
    std::string h_url = "horizons.jpl.nasa.gov";    ///< URL to connect to
    //std::string h_url = "128.149.23.134";         ///< Alternative URL

private:
    
};

#endif /* CHCONNECT_HPP */
