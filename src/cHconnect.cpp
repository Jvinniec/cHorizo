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
bool cHconnect::Connect()
{
    // Run the connection
    h_isConnected = connect(h_socket_ref,&h_sockaddr, sizeof(h_serv_addr));
    if (int(errno) != 0) throw cHexception();
    
    return h_isConnected;
}


/**************************************************************
 * Establishes the connection to the HORIZONS telnet service
 *  @returns Whether or not the connection was successful.
 **************************************************************/
bool cHconnect::Disconnect()
{
    // Shutdown the connection
    int shutdown_status(-1);
    if (h_isConnected) {
        shutdown_status = shutdown(h_socket_ref, 2);
    }
    
    // Check the status
    if (shutdown_status >= 0) {
        h_isConnected = false;
        return true;
    } else {
        std::cout << strerror(errno) << std::endl;
        return false;
    }
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
