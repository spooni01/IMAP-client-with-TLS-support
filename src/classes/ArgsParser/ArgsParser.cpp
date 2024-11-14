/**
 *	@file	Classes/IMAPConnection/IMAPConnection.cpp
 *	@brief	IMAPConnection header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "ArgsParser.hpp"


/**
 * @brief Constructs an ArgsParser and initializes with command-line arguments.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of argument strings.
 */
ArgsParser::ArgsParser(int argc, char* argv[]) : port(0), useTLS(false), readOnlyNew(false), headersOnly(false)
{
    
    parseArguments(argc, argv);
    validateArguments();

}

    
/**
 * @brief Parses command-line arguments and stores values in the corresponding member variables.
 *
 * @param argc The argument count.
 * @param argv The argument values.
 */
void ArgsParser::parseArguments(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-p" && i + 1 < argc) {
            port = std::stoi(argv[++i]);
        } else if (arg == "-T") {
            useTLS = true;
            if (port == 0) port = 993;  
        } else if (arg == "-c" && i + 1 < argc) {
            certFile = argv[++i];
        } else if (arg == "-C" && i + 1 < argc) {
            certDir = argv[++i];
        } else if (arg == "-n") {
            readOnlyNew = true;
        } else if (arg == "-h") {
            headersOnly = true;
        } else if (arg == "-a" && i + 1 < argc) {
            authFile = argv[++i];
        } else if (arg == "-b" && i + 1 < argc) {
            mailbox = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outDir = argv[++i];
        } else if (server.empty()) {
            server = arg;  // First non-flag argument is treated as the server address.
        } else {
            throw ArgumentsException("Unknown or improperly formatted argument: " + arg);
        }
    }
        
    // If TLS is disabled and no port was specified, default to the standard IMAP port (143).
    if (!useTLS && port == 0)
        port = 143;

}

/**
 * @brief Validates parsed arguments to ensure that all required parameters are specified and valid.
 */
void ArgsParser::validateArguments()
{

    if (server.empty()) {
        throw ArgumentsException("Server address is required.");
    }
    if (authFile.empty()) {
        throw ArgumentsException("Authentication file (-a) is required.");
    }
    if (outDir.empty()) {
        throw ArgumentsException("Output directory (-o) is required.");
    }
    if (port <= 0 || port > 65535) {
        throw ArgumentsException("Port must be a valid number between 1 and 65535.");
    }

}
