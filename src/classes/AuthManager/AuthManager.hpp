/**
 *	@file	Classes/AuthManager/AuthManager.hpp
 *	@brief	AuthManager header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef AUTHMANAGER_HPP
#define AUTHMANAGER_HPP


/**
 * @class AuthManager
 * @brief Manages authentication by reading and parsing credentials from a file.
 * 
 * This class reads a specified file to extract the username and password
 * for authentication. The file is expected to have the following format:
 * 
 * @code
 * username = jmeno
 * password = heslo
 * @endcode
 */
class AuthManager {
public:

    /**
     * @brief Constructs the AuthManager with the specified file path and parses credentials.
     *
     * @param filepath The path to the file containing authentication credentials.
     */
    AuthManager(const std::string& filepath);

    /**
     * @brief Gets the parsed username.
     * @return The username as a string.
     */
    const std::string& getUsername() const { return username; }

    /**
     * @brief Gets the parsed password.
     * @return The password as a string.
     */
    const std::string& getPassword() const { return password; }

private:

    std::string username;
    std::string password;

    /**
     * @brief Parses the file to extract the username and password.
     * 
     * @param filepath The path to the file containing authentication credentials.
     */
    void parseFile(const std::string& filepath);

};

#endif // AUTHMANAGER_HPP