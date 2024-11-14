/**
 *	@file	main.cpp
 *	@brief	Main file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "main.hpp"

/**
 *	@brief	Main function.
 *	@param	argc Number of parameters.
 *	@param	argv Parameters.
 *	@return	`0` on success, error code (1 to infinity) on a error.
 *	@throws	todo
 */
int main (int argc, char* argv[])
{

    try {

        (void)argc;
        (void)argv;
        IMAPConnection connection(true, "imap.stud.fit.vutbr.cz", 993);
        
        // IMAP login
        connection.sendCommand("a001 LOGIN xlizic00 x\r\n");
        std::cout << connection.readResponse() << std::endl;

        // Select the mailbox
        connection.sendCommand("a002 SELECT INBOX\r\n");
        std::cout << connection.readResponse() << std::endl;

        // Fetch the first message
        connection.sendCommand("a003 FETCH 1 (BODY[HEADER.FIELDS (FROM SUBJECT DATE)])\r\n");
        std::cout << connection.readResponse() << std::endl;

        // Logout and close the connection
        connection.sendCommand("a004 LOGOUT\r\n");
        std::cout << connection.readResponse() << std::endl;


    } catch (const ConnectionException& e) {
        std::cerr << ANSI_COLOR_RED << "Connection error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const IMAPException& e) {
        std::cerr << ANSI_COLOR_RED << "IMAP error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const std::exception& e) {
        std::cerr << ANSI_COLOR_RED << "General error" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return 1;
    }

    return 0;

}
