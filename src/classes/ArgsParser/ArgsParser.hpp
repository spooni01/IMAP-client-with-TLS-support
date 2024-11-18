/**
 *	@file	Classes/ArgsParser/ArgsParser.hpp
 *	@brief	ArgsParser header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef ARGSPARSER_HPP
#define ARGSPARSER_HPP


/**
 * @brief The ArgsParser class handles parsing and validating command-line arguments for the IMAP client.
 *
 * This class allows users to parse various parameters necessary for configuring the IMAP client,
 * including server information, encryption settings, mailbox specification, and output directory.
 * Required and optional arguments are validated to ensure proper configuration of the application.
 */
class ArgsParser {
public:
    
    /**
     * @brief Constructs an ArgsParser and initializes with command-line arguments.
     *
     * @param argc The number of command-line arguments.
     * @param argv The array of argument strings.
     */
    ArgsParser(int argc, char* argv[]);    

    // Getters for parsed values with const char* return type
    const char* getServer() const { return server.c_str(); }
    int getPort() const { return port; }
    bool isTLS() const { return useTLS; }
    const char* getCertFile() const { return certFile.c_str(); }
    const char* getCertDir() const { return certDir.c_str(); }
    bool isReadOnlyNew() const { return readOnlyNew; }
    bool isHeadersOnly() const { return headersOnly; }
    const char* getAuthFile() const { return authFile.c_str(); }
    const std::string& getMailbox() const { return mailbox; }
    const char* getOutDir() const { return outDir.c_str(); }
    bool interactive = false;
    bool readOnlyNew = false;
    std::string mailbox = "INBOX"; 

private:

    std::string server;
    int port;
    bool useTLS;
    std::string certFile;
    std::string certDir = "/etc/ssl/certs";  
    bool headersOnly;
    std::string authFile;    
    std::string outDir;

    /**
     * @brief Parses command-line arguments and stores values in the corresponding member variables.
     *
     * @param argc The argument count.
     * @param argv The argument values.
     */
    void parseArguments(int argc, char* argv[]);

    /**
     * @brief Validates parsed arguments to ensure that all required parameters are specified and valid.
     */
    void validateArguments();

};


#endif // ARGSPARSER_HPP