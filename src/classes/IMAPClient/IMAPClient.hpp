/**
 *	@file	Classes/IMAPClient/IMAPClient.hpp
 *	@brief	IMAPClient header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef IMAPCLIENT_HPP
#define IMAPCLIENT_HPP


/**
 * @class IMAPClient
 * @brief The IMAPClient class manages the overall functionality of the IMAP client.
 * 
 * This class is responsible for:
 * - Parsing command-line arguments using the ArgsParser class.
 * - Managing authorization through the AuthManager class.
 * - Establishing an IMAP connection with the specified server and port via the IMAPConnection class.
 * 
 * It acts as the main controller that ties together the different components required
 * to interact with an IMAP server.
 */
class IMAPClient {
public:

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
    IMAPClient(int argc, char* argv[]);

private:

    /**
     * @brief Counter for the command send.
     */
    int cntCommand = 0;

    /**
     * @brief Counter of emails.
     */
    int cntEmails = 0;

    /**
     * @brief Generates a sequential command string in the format "A###".
     * @return The next command string.
     */
    std::string getNextCommand();

    /**
     * @brief Returns command string in the format "A###".
     * @return The current command string.
     */
    std::string getCurrentCommand();

    /**
     * @brief The ArgsParser object used to parse command-line arguments.
     * 
     * The ArgsParser is responsible for handling and validating command-line arguments,
     * including the server address, port, and other optional arguments.
     */
    ArgsParser argsParser;

    /**
     * @brief The AuthManager object used for managing the authentication process.
     * 
     * The AuthManager handles the parsing of the authentication file and storing
     * the credentials needed for logging into the IMAP server.
     */
    AuthManager authManager;

    /**
     * @brief The IMAPConnection object that establishes a connection to the IMAP server.
     * 
     * The IMAPConnection object is responsible for establishing a connection to
     * the specified server and port and ensuring that the connection is secure (if necessary).
     */
    IMAPConnection connection;   


    /**
     * @brief The MessageFactory object that manages email messages.
     * 
     * The MessageFactory object is responsible for storing, parsing, and managing
     * email messages received from the IMAP server. It provides functionality to 
     * add, retrieve, and process email messages, including handling their headers and bodies.
     */
    MessageFactory emails;  

    /**
     * @brief The FiniteStateMachine (FSM) object that controls the state transitions.
     * 
     * The FiniteStateMachine object is responsible for managing the states and transitions
     * within the application.
     */
    FiniteStateMachine FSM;

};

#endif // IMAPCLIENT_HPP