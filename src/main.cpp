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
 */
int main (int argc, char* argv[])
{

    try {

        ArgsParser argsParser(argc, argv);  // Parse arguments.    
        AuthManager authManager(argsParser.getAuthFile());  // Parse authorization file.
        IMAPConnection connection(true, argsParser.getServer(), argsParser.getPort());  // Create connection.

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


    } catch (const ArgumentsException& e) {
        std::cerr << ANSI_COLOR_RED << "Arguments error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const AuthenticateException& e) {
        std::cerr << ANSI_COLOR_RED << "Authenticate error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const ConnectionException& e) {
        std::cerr << ANSI_COLOR_RED << "Connection error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const FileException& e) {
        std::cerr << ANSI_COLOR_RED << "File error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const SSLException& e) {
        std::cerr << ANSI_COLOR_RED << "SSL error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
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
