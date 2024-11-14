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


        IMAPClient imapClient(argc, argv);
    

    } catch (const ArgumentsException& e) {
        std::cerr << ANSI_COLOR_RED << "Arguments error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const AuthenticateException& e) {
        std::cerr << ANSI_COLOR_RED << "Authenticate error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const BIOException& e) {
        std::cerr << ANSI_COLOR_RED << "Bio error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const CommandException& e) {
        std::cerr << ANSI_COLOR_RED << "Command error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const ConnectionException& e) {
        std::cerr << ANSI_COLOR_RED << "Connection error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const FileException& e) {
        std::cerr << ANSI_COLOR_RED << "File error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
        return e.code();
    } catch (const MailboxException& e) {
        std::cerr << ANSI_COLOR_RED << "Mail error (" << e.code() << ")" << ANSI_COLOR_RESET << ": " << e.what() << std::endl;
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
