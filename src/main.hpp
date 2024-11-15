/**
 *	@file   main.hpp
 *	@brief  Main header file
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef MAIN_HPP
#define MAIN_HPP


// Include libraries
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <stdexcept>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <filesystem>
#include <regex>
#include <bitset>
#include <sstream>
#include <cctype>
#include <map>
#include <iomanip>
#include <iterator>
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// success
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_GRAY   "\033[1;30m"   // info
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset

// Macros
#ifdef DEBUG
    #define DEBUG_PRINT(color, x) std::cout << "[" << color << "DEBUG" << ANSI_COLOR_RESET << "] " << x << std::endl
#else
    #define DEBUG_PRINT(color, x) // žádná akce
#endif

// Exceptions
#include "exceptions/IMAPException.cpp"
#include "exceptions/ArgumentsException.cpp"
#include "exceptions/AuthenticateException.cpp"
#include "exceptions/BIOException.cpp"
#include "exceptions/CommandException.cpp"
#include "exceptions/ConnectionException.cpp"
#include "exceptions/FileException.cpp"
#include "exceptions/MailboxException.cpp"
#include "exceptions/SSLException.cpp"

// Include classes
#include "classes/FiniteStateMachine/FiniteStateMachine.cpp"
#include "classes/AuthManager/AuthManager.cpp"
#include "classes/ArgsParser/ArgsParser.cpp"
#include "classes/Message/Message.cpp"
#include "classes/MessageFactory/MessageFactory.cpp"
#include "classes/IMAPConnection/IMAPConnection.cpp"
#include "classes/IMAPClient/IMAPClient.cpp"


#endif // MAIN_HPP