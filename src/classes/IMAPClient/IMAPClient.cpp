/**
 *	@file	Classes/IMAPClient/IMAPClient.cpp
 *	@brief	IMAPClient file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "IMAPClient.hpp"


/**
 * @brief Constructor for the IMAPClient class, this function is main controller of entire program.
 * 
 * Representation of use case diagram.
 * 
 * @param argc The number of command-line arguments passed to the program.
 * @param argv The array of command-line argument strings.
 */
IMAPClient::IMAPClient(int argc, char* argv[]) 
        : argsParser(argc, argv), 
          authManager(argsParser.getAuthFile()),
          connection(argsParser.isTLS(), argsParser.getServer(), argsParser.getPort()),
          emails(argsParser.getOutDir())
{


    // Loop until it is not end of program (FSM state = END).
    // This loop represents use case diagram.
    while(FSM.getState() != FiniteStateMachine::State::END) {

        // INIT: When FSM state is INIT, switch to AUTH.
        if(FSM.getState() == FiniteStateMachine::State::INIT)
        {            
            FSM.transitionToAuth();
        }

        // AUTH: Try to authorize user.
        else if(FSM.getState() == FiniteStateMachine::State::AUTH)
        {
            // Send login data.
            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to login...");
            std::string tmpLoginCommand = this->getNextCommand() + " LOGIN " + authManager.getUsername() + " " + authManager.getPassword() + "\r\n";
            connection.sendCommand(tmpLoginCommand.c_str());
            
            // Check if authorization was successfull.
            std::string tmpServerResponse = connection.readResponse((this->getCurrentCommand() + " ").c_str());
            if (tmpServerResponse.find((this->getCurrentCommand() + " OK").c_str()) != std::string::npos) {
                DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Login successful.");
                FSM.transitionToSelect();
            }
            else {
                DEBUG_PRINT(ANSI_COLOR_RED, "IMAPClient::IMAPClient() -> Login failed.");
                std::cout << "Není možné ověřit identitu serveru " << argsParser.getServer() << "." << std::endl;
                FSM.transitionToEnd();
            }
        }

        // SELECT: Select mailbox.
        else if(FSM.getState() == FiniteStateMachine::State::SELECT)
        {
            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to select mailbox...");
            std::string tmpMailboxCommand = this->getNextCommand() + " SELECT " + argsParser.getMailbox() + "\r\n";
            connection.sendCommand(tmpMailboxCommand.c_str());

            // Receive answer.
            std::string tmpServerResponse = connection.readResponse((this->getCurrentCommand() + " ").c_str());
            if (tmpServerResponse.find((this->getCurrentCommand() + " OK").c_str()) != std::string::npos) {
                DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Mailbox selected sucessful.");
                FSM.transitionToDownload();
            }
            else {
                DEBUG_PRINT(ANSI_COLOR_RED, "IMAPClient::IMAPClient() -> Mailbox do not exists.");
                std::cout << "Mailbox " << argsParser.getMailbox() << " neexistuje." << std::endl;
                FSM.transitionToQuit();
            }
        }
        
        // DOWNLOAD: Download emails.
        else if(FSM.getState() == FiniteStateMachine::State::DOWNLOAD)
        {
            
            // Search messages.
            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to fetching messages ID...");
            if(argsParser.isReadOnlyNew())
                connection.sendCommand((this->getNextCommand() + " UID SEARCH UNSEEN\r\n").c_str());
            else
                connection.sendCommand((this->getNextCommand() + " UID SEARCH ALL\r\n").c_str());
            std::string tmpServerResponse = connection.readResponse((this->getCurrentCommand() + " OK").c_str());
            
            // Fetch ID`s.
            std::vector<std::string> numbers;
            std::regex numberRegex(R"(\d+)");
            std::smatch match;

            // Find the SEARCH line.
            std::size_t searchPos = tmpServerResponse.find("* SEARCH");
            if (searchPos != std::string::npos) {
                std::string searchLine = tmpServerResponse.substr(searchPos, tmpServerResponse.find('\n', searchPos) - searchPos);
                auto begin = std::sregex_iterator(searchLine.begin(), searchLine.end(), numberRegex);
                auto end = std::sregex_iterator();

                for (std::sregex_iterator i = begin; i != end; ++i) 
                    numbers.push_back((*i).str());  
            }
            DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Messages ID`s fetched sucessful.");

            // Download emails.
            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to downloading emails...");
            for (std::string number : numbers) {
                if(!emails.existsInDataStorage(argsParser.getServer(), std::stoi(number))) {
                    if(argsParser.isHeadersOnly())
                        connection.sendCommand((this->getNextCommand() + " UID FETCH " + number + " BODY.PEEK[HEADER]\r\n").c_str());
                    else
                        connection.sendCommand((this->getNextCommand() + " UID FETCH " + number + " BODY[]\r\n").c_str());
                    
                    // Internal synchronization procedures.
                    emails.addNewMessage(connection.readResponse((this->getCurrentCommand() + " OK").c_str()), argsParser.getOutDir());
                    emails.addToDataStorage(argsParser.getServer(), std::stoi(number));
                    cntEmails++;
                }
            }
            DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Messages downloaded sucessful.");
       
            // Write output into STDOUT.
            if(this->cntEmails == 1)
                std::cout << "Stažena " << this->cntEmails << " zpráva ze schránky " << argsParser.getMailbox() << "." << std::endl;
            else if(this->cntEmails < 5)
                std::cout << "Staženy " << this->cntEmails << " zprávy ze schránky " << argsParser.getMailbox() << "." << std::endl;
            else
                std::cout << "Staženo " << this->cntEmails << " zpráv ze schránky " << argsParser.getMailbox() << "." << std::endl;

            FSM.transitionToQuit();
        }

        // QUIT: Quit application, logout and close the connection.
        else if(FSM.getState() == FiniteStateMachine::State::QUIT)
        {
            DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPClient::IMAPClient() -> Trying to logout...");
            connection.sendCommand((this->getNextCommand() + " LOGOUT\r\n").c_str());
            DEBUG_PRINT(ANSI_COLOR_ORANGE, "IMAPClient::IMAPClient() -> "+connection.readResponse((this->getCurrentCommand() + " OK").c_str()));
            DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPClient::IMAPClient() -> Logout succesfull.");

            FSM.transitionToEnd();
        }

        // Error.
        else
        {
            throw IMAPException("An out-of-FSM condition has occurred");
        }


    }


}


/**
 * @brief Generates a sequential command string in the format "A###".
 * @return The next command string.
 */
std::string IMAPClient::getNextCommand()
{

    std::ostringstream command;
    command << "A" << std::setw(3) << std::setfill('0') << ++cntCommand;
    return command.str();

}

/**
 * @brief Returns command string in the format "A###".
 * @return The current command string.
 */
std::string IMAPClient::getCurrentCommand()
{

    std::ostringstream command;
    command << "A" << std::setw(3) << std::setfill('0') << cntCommand;
    return command.str();

}