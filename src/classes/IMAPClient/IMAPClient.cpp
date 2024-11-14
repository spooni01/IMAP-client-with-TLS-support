/**
 *	@file	Classes/IMAPClient/IMAPClient.cpp
 *	@brief	IMAPClient file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "IMAPClient.hpp"


/**
 * @brief Constructor for the IMAPClient class.
 * 
 * This constructor is responsible for initializing the core components required
 * for the IMAP client, including parsing command-line arguments, initializing
 * the authentication manager, and establishing the IMAP connection.
 * 
 * @param argc The number of command-line arguments passed to the program.
 * @param argv The array of command-line argument strings.
 */
IMAPClient::IMAPClient(int argc, char* argv[]) 
        : argsParser(argc, argv), 
          authManager(argsParser.getAuthFile()),
          connection(true, argsParser.getServer(), argsParser.getPort()) 
{

    // IMAP login
    std::string tmpLoginCommand = "001 LOGIN " + authManager.getUsername() + " " + authManager.getPassword() + "\r\n";
    connection.sendCommand(tmpLoginCommand.c_str());
    std::cout << connection.readResponse() << std::endl;

    // Select the mailbox
    connection.sendCommand("002 SELECT INBOX\r\n");
    std::cout << connection.readResponse() << std::endl;

    // Fetch the first message
    connection.sendCommand("003 FETCH 1 (BODY[HEADER.FIELDS (FROM SUBJECT DATE)])\r\n");
    std::cout << connection.readResponse() << std::endl;

    // Logout and close the connection
    connection.sendCommand("004 LOGOUT\r\n");
    std::cout << connection.readResponse() << std::endl;

}