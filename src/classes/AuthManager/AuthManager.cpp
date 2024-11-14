/**
 *	@file	Classes/AuthManager/AuthManager.cpp
 *	@brief	AuthManager file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "AuthManager.hpp"


/**
 * @brief Constructs the AuthManager with the specified file path and parses credentials.
 *
 * @param filepath The path to the file containing authentication credentials.
 */
AuthManager::AuthManager(const std::string& filepath)
{

    parseFile(filepath);

}


/**
 * @brief Parses the file to extract the username and password.
 * 
 * @param filepath The path to the file containing authentication credentials.
 */
void AuthManager::parseFile(const std::string& filepath)
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "AuthManager::parseFile() -> Parsing of authentication file...");

    // Find file.
    std::ifstream file(filepath);
    if (!file.is_open()) {
        DEBUG_PRINT(ANSI_COLOR_RED, "AuthManager::parseFile() -> Unable to open authentication file.");
        throw FileException("Unable to open authentication file: " + filepath);
    }

    std::string line;
    bool usernameSet = false;
    bool passwordSet = false;

    // Loop through file.
    while (std::getline(file, line)) {

        std::string::size_type pos = line.find('=');
        if (pos == std::string::npos) {
            DEBUG_PRINT(ANSI_COLOR_RED, "AuthManager::parseFile() -> Invalid format in authentication file.");
            throw AuthenticateException("Invalid format in authentication file: " + filepath);
        }

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
            
        // Trim whitespace.
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        if (key == "username") {
            username = value;
            usernameSet = true;
        } else if (key == "password") {
            password = value;
            passwordSet = true;
        }
    }

    if (!usernameSet || !passwordSet) {
        DEBUG_PRINT(ANSI_COLOR_RED, "AuthManager::parseFile() -> Authentication file missing required fields.");
        throw AuthenticateException("Authentication file missing required fields: " + filepath);
    }

    DEBUG_PRINT(ANSI_COLOR_GREEN, "AuthManager::parseFile() -> Authentication file parsed.");
    
}
