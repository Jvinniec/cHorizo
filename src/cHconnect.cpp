//
//  cHconnect.cpp
//  cHorizo
//
//  Created by Josh Cardenzana on 3/23/17.
//  Copyright © 2017 Josh Cardenzana. All rights reserved.

/**************************************************************
 * Copyright (C) 2017 - Josh V. Cardenzana
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see http://www.gnu.org/licenses/.
 **************************************************************/

#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include<arpa/inet.h>

#include "cHconnect.hpp"
#include "cHexception.hpp"

/**********************************************************//**
 * Default constructor
 *  @param[in] connect          Specifies whether to immediately connect
 **************************************************************/
cHconnect::cHconnect(bool connect)
{
    Init();
}


/**********************************************************//**
 * Deconstructor
 **************************************************************/
cHconnect::~cHconnect()
{
    if (h_isConnected) Disconnect();
}


/**********************************************************//**
 * Tests whether the connection is live or not
 *  @returns Whether or not the connection was successfully made.
 **************************************************************/
bool cHconnect::TestConnection()
{
    return h_isConnected;
}

# pragma mark - Public Methods

/**************************************************************
 * Establishes the connection to the HORIZONS telnet service
 *  @returns Whether or not the connection was successful.
 **************************************************************/
bool cHconnect::Connect(bool printwelcome)
{
    // Run the connection
    if(connect(h_socket_ref, (struct sockaddr *)&h_serv_addr, sizeof(h_serv_addr)) < 0) {
        h_isConnected = false;
        throw cHexception();
    } else {
        h_isConnected = true;
        if (printwelcome) {
            std::cout << Recv() << std::endl;
        }
    }
    
    return h_isConnected;
}


/**************************************************************
 * Disconnects the connection to the HORIZONS telnet service
 *
 *  @returns Whether or not the disconnection was successful.
 *
 * Method returns 'true' if the disconnection was successful or
 * if the socket wasnt connected in the first place. If method
 * fails to disconnect, then method returns 'false' and throws an
 * exception. This method is called by default in the deconstructor.
 **************************************************************/
bool cHconnect::Disconnect()
{
    // Shutdown the connection
    int shutdown_status(-1);
    if (h_isConnected) {
        // Close the connection
        shutdown_status = close(h_socket_ref);
    } else {
        return true;
    }
    
    // Check the status
    if (shutdown_status == 0) {
        h_isConnected = false;
        return true;
    } else {
        throw cHexception();
        return false;
    }
}


/**************************************************************
 * Send a message to the server.
 *
 *  @param[in] msg          Message to send to the server
 *  @return True of send was successfull
 *
 * This methods sends a message to the server in 'h_url'. If a
 * reply is expected from the server, you should call 'Recv()'.
 **************************************************************/
bool cHconnect::Send(const std::string& msg)
{
    // Go ahead and connect
    return (send(h_socket_ref, msg.c_str(), msg.size(), 0) >= 0);
    
}


/**************************************************************
 * Receives a message fom the server.
 *
 *  @return Message from the server.
 *
 * This methods receives replys from the server.
 **************************************************************/
std::string cHconnect::Recv(int msg_size)
{
    std::string msgStr;
    char msg[1];
    while (recv(h_socket_ref, msg, 1, MSG_WAITALL) > 0) {
        std::cout << msg;
        msgStr.push_back(msg[0]);
    }
    std::cout << std::endl;
    return msgStr;
}

/**************************************************************
 * Set the url for the server to be connected to
 *
 *  @param[in] url      URL to connect to
 **************************************************************/
void cHconnect::SetURL(const std::string& url)
{
    h_url = url;
}


/**************************************************************
 * Set the port number to connect through
 *
 *  @param[in] portnum      Port number to connect through
 **************************************************************/
void cHconnect::SetPort(const int& portnum)
{
    h_portnum = portnum;
}

# pragma mark - Protected Methods

/**************************************************************
 * Initialize the parameters relevant to connecting to the HORIZONS
 * service.
 **************************************************************/
void cHconnect::Init()
{
    h_socket_ref = socket(AF_INET, SOCK_STREAM, 0);
    h_server = gethostbyname(h_url.c_str());
    
    // if server is null, throw an error
    if (h_server == NULL) {
        throw cHexception("SERVER IS NULL!");
    }
    /*
    h_serv_addr.sin_addr.s_addr = inet_addr(h_url.c_str());
    h_serv_addr.sin_family = AF_INET;
    h_serv_addr.sin_port = htons(h_portnum);
    bcopy((char *)h_server->h_addr, (char *)&h_serv_addr.sin_addr.s_addr, h_server->h_length);
     */
    
    bzero((char *) &h_serv_addr, sizeof(h_serv_addr));
    h_serv_addr.sin_family = AF_INET;
    bcopy((char *)h_server->h_addr, (char *)&h_serv_addr.sin_addr.s_addr, h_server->h_length);
    h_serv_addr.sin_port = htons(h_portnum);
}
