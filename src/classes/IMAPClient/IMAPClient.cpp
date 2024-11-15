/**
 *	@file	Classes/IMAPClient/IMAPClient.cpp
 *	@brief	IMAPClient file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "IMAPClient.hpp"


/**
 * @brief Constructor for the IMAPClient class, this function is main controller of entire program.
 * 
 * 
 * @param argc The number of command-line arguments passed to the program.
 * @param argv The array of command-line argument strings.
 */
IMAPClient::IMAPClient(int argc, char* argv[]) 
        : argsParser(argc, argv), 
          authManager(argsParser.getAuthFile()),
          connection(true, argsParser.getServer(), argsParser.getPort()) 
{


    // Loop until it is not end of program (FSM state = QUIT).
    while(FSM.getState() != FiniteStateMachine::State::QUIT) {

        // INIT: When FSM state is INIT, switch to AUTH.
        if(FSM.getState() == FiniteStateMachine::State::INIT)
        {
            FSM.transitionToAuth();
        }

        // AUTH: Try to authorize user.
        // TODO handle wrong answer, make internal counter for A001 etc.
        else if(FSM.getState() == FiniteStateMachine::State::AUTH)
        {
            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to login...");
            std::string tmpLoginCommand = "A001 LOGIN " + authManager.getUsername() + " " + authManager.getPassword() + "\r\n";
            connection.sendCommand(tmpLoginCommand.c_str());
            DEBUG_PRINT(ANSI_COLOR_ORANGE, "IMAPClient::IMAPClient() -> "+connection.readResponse("A001 OK"));
            DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Login successful.");
        
            // TODO if login success
            FSM.transitionToSelect();
            // else FSM.transitionToQuit();
        }

        // SELECT: Select mailbox.
        // TODO handle wrong answer, make internal counter for A001 etc.
        else if(FSM.getState() == FiniteStateMachine::State::SELECT)
        {
            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to select mailbox...");
            std::string tmpMailboxCommand = "A002 SELECT " + argsParser.getMailbox() + "\r\n";
            connection.sendCommand(tmpMailboxCommand.c_str());
            DEBUG_PRINT(ANSI_COLOR_ORANGE, "IMAPClient::IMAPClient() -> "+connection.readResponse("A002 OK"));
            DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Mailbox selected sucessful.");
            
            // TODO if mailbox success
            FSM.transitionToDownload();
            // else FSM.transitionToQuit();
        }
        
        // DOWNLOAD: Download emails.
        // TODO handle wrong answer, make internal counter for A001 etc.
        else if(FSM.getState() == FiniteStateMachine::State::DOWNLOAD)
        {
            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to fetching messages ID...");
            if(argsParser.isReadOnlyNew())
            connection.sendCommand("A003 UID SEARCH UNSEEN\r\n");
            else
            connection.sendCommand("A003 UID SEARCH ALL\r\n");
            DEBUG_PRINT(ANSI_COLOR_ORANGE, "IMAPClient::IMAPClient() -> "+connection.readResponse("A003 OK"));
            DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Messages ID`s fetched sucessful.");

            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to downloading emails...");
            if(argsParser.isHeadersOnly())
            connection.sendCommand("A004 UID FETCH 2032 BODY.PEEK[HEADER]\r\n");
            else
            connection.sendCommand("A004 UID FETCH 2032 BODY[]\r\n");
            emails.addNewMessage(connection.readResponse("A004 OK"), argsParser.getOutDir());

            DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Messages downloaded sucessful.");
       
            FSM.transitionToQuit();
        }

        // QUIT: Quit application, logout and close the connection.
        else if(FSM.getState() == FiniteStateMachine::State::QUIT)
        {
            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to logout...");
            connection.sendCommand("A010 LOGOUT\r\n");
            DEBUG_PRINT(ANSI_COLOR_ORANGE, "IMAPClient::IMAPClient() -> "+connection.readResponse("A010 OK"));
            DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Logout succesfull.");
        }

        // Error.
        else
        {
            throw IMAPException("An out-of-FSM condition has occurred");
        }


    }


}