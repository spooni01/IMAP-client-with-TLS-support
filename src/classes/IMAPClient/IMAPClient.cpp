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
          connection(false, argsParser.getServer(), argsParser.getPort()) 
{

    // IMAP login
    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to login...");
    std::string tmpLoginCommand = "A001 LOGIN " + authManager.getUsername() + " " + authManager.getPassword() + "\r\n";
    connection.sendCommand(tmpLoginCommand.c_str());
    std::cout << connection.readResponse("A001 OK") << std::endl;
    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Login successful.");

    // Select the mailbox
    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to select mailbox...");
    std::string tmpMailboxCommand = "A002 SELECT " + argsParser.getMailbox() + "\r\n";
    connection.sendCommand(tmpMailboxCommand.c_str());
    std::cout << connection.readResponse("A002 OK") << std::endl;
    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Mailbox selected sucessful.");

    // Fetch messages
    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to fetching messages ID...");
    if(argsParser.isReadOnlyNew())
      connection.sendCommand("A003 UID SEARCH UNSEEN\r\n");
    else
      connection.sendCommand("A003 UID SEARCH ALL\r\n");
    std::cout << connection.readResponse("A003 OK") << std::endl;
    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Messages ID`s fetched sucessful.");

    // Get emails TODO
    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to downloading emails...");
    if(argsParser.isHeadersOnly())
      connection.sendCommand("A004 UID FETCH 2032 BODY[]\r\n");
    else
      connection.sendCommand("A004 UID FETCH 2032 BODY.PEEK[HEADER]\r\n");
    emails.addNewMessage(connection.readResponse("A004 OK"));

    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Messages downloaded sucessful.");

    // Logout and close the connection
    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to logout...");
    connection.sendCommand("A010 LOGOUT\r\n");
    std::cout << connection.readResponse("A010 OK") << std::endl;
    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Logout succesfull.");

}