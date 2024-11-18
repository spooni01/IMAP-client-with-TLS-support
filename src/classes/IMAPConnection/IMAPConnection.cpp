/**
 *	@file	Classes/IMAPConnection/IMAPConnection.cpp
 *	@brief	IMAPConnection file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "IMAPConnection.hpp"


/**
 *  @brief Constructor for the IMAPConnection class.
 *  
 *  Initializes the connection by creating an SSL context, establishing a BIO
 *  connection to the IMAP server, and setting up the SSL connection.
 * 
 *  @param  secure Indicate if the connection is secured or not.
 *  @param	server Name of server (can be IP address or domain name)
 *	@param	port Number of port on the server.
 */
IMAPConnection::IMAPConnection(bool secure, const char *server, int port) : secure(secure)
{
    
    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPConnection::IMAPConnection() -> Starting IMAP connection...");
    
    if(this->secure) {
        this->initOpenSSL();
        this->ctx = this->createSSLContext();
    }

    this->bio = this->createBioConnection(server, port);

    if(this->secure)
        this->ssl = this->createSSLConnection(this->ctx, this->bio);
    
}


/**
 *  @brief Destructor for the IMAPConnection class.
 *  
 *  Cleans up and releases all resources used by the IMAPConnection object, including
 *  the SSL context, SSL object, and BIO connection. This ensures proper cleanup
 *  of resources when the object is destroyed.
 */
IMAPConnection::~IMAPConnection()
{

    // Free resources
    if (this->bio) {
        DEBUG_PRINT(ANSI_COLOR_GRAY, "Freeing BIO object...");
        BIO_free_all(this->bio);
    }

    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAP connection closed and resources freed.");

}


/**
 *  @brief Initializes OpenSSL libraries.
 *  
 *  This function loads OpenSSL error strings and algorithms required for SSL communication.
 */
void IMAPConnection::initOpenSSL()
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPConnection::initOpenSSL() -> Initializing OpenSSL...");
    
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    
    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPConnection::initOpenSSL() -> OpenSSL initialized successfully.");

}


/**
 *  @brief Creates an SSL context.
 *  
 *  Creates and returns an SSL context object that will be used for SSL connections.
 *  
 *  @return A pointer to the created SSL context.
 */
SSL_CTX *IMAPConnection::createSSLContext()
{
    
    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPConnection::createSSLContext() -> Creating SSL context...");
    
    const SSL_METHOD *method;
    SSL_CTX *ctx;
    method = SSLv23_client_method(); 
    ctx = SSL_CTX_new(method);

    // Try to create context.
    if (!ctx) {
        DEBUG_PRINT(ANSI_COLOR_RED, "IMAPConnection::createSSLContext() -> Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        throw SSLException("IMAPConnection::createSSLContext() -> Unable to create BIO connection.");
    }

    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPConnection::createSSLContext() -> SSL context created successfully.");
    return ctx;

}


/**
 *  @brief Creates a BIO connection.
 *  
 *  Establishes a low-level network connection (BIO) to the given server and port.
 *  
 *  @param host The server's hostname or IP address.
 *  @param port The port number on the server to connect to.
 *  @return A pointer to the created BIO object for the connection.
 */
BIO *IMAPConnection::createBioConnection(const char *host, int port)
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPConnection::createBioConnection() -> Creating BIO connection...");
    
    char host_with_port[256];
    BIO *bio;

    // Try to create BIO connection.
    snprintf(host_with_port, sizeof(host_with_port), "%s:%d", host, port);   
    bio = BIO_new_connect(host_with_port);
    if (!bio) {
        DEBUG_PRINT(ANSI_COLOR_RED, "IMAPConnection::createBioConnection() -> Unable to create BIO connection");
        throw BIOException("Unable to create BIO connection.");
    }

    // Try connect to server.
    if (BIO_do_connect(bio) <= 0) {
        DEBUG_PRINT(ANSI_COLOR_RED, "IMAPConnection::createBioConnection() -> Unable to connect to server");
        throw BIOException("Unable to connect to server.");
    }

    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPConnection::createBioConnection() -> BIO connection established.");
    return bio;

}


/**
 *  @brief Creates an SSL connection.
 *  
 *  Establishes an SSL/TLS connection using the provided SSL context and BIO connection.
 *  
 *  @param ctx The SSL context to use for the connection.
 *  @param bio The BIO connection to use for the underlying network communication.
 *  @return A pointer to the created SSL object for the secured connection.
 */
SSL *IMAPConnection::createSSLConnection(SSL_CTX *ctx, BIO *bio)
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPConnection::createSSLConnection() -> Creating SSL connection...");

    // Create SSL object.
    SSL *ssl = SSL_new(ctx);
    if (!ssl) {
        DEBUG_PRINT(ANSI_COLOR_RED, "IMAPConnection::createSSLConnection() -> Unable to create SSL object");
        ERR_print_errors_fp(stderr);
        throw SSLException("Unable to create SSL object.");
    }

    SSL_set_bio(ssl, bio, bio);

    // Try connect.
    if (SSL_connect(ssl) <= 0) {
        DEBUG_PRINT(ANSI_COLOR_RED, "IMAPConnection::createSSLConnection() -> SSL connection failed");
        ERR_print_errors_fp(stderr);
        throw SSLException("SSL connection failed.");
    }

    DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPConnection::createSSLConnection() -> SSL connection established.");
    return ssl;

}


/**
 *  @brief Sends an IMAP command to the server.
 *  
 *  This function sends an IMAP command to the server over the established SSL connection.
 *  
 *  @param command The IMAP command string to send.
 */
void IMAPConnection::sendCommand(const char *command)
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPConnection::sendCommand() -> Sending IMAP command...");

    // Secure connection (SSL) or non-secure (BIO).
    if (this->secure) {
        
        if (SSL_write(this->ssl, command, strlen(command)) <= 0) {
            DEBUG_PRINT(ANSI_COLOR_RED, "IMAPConnection::sendCommand() -> Unable to send command via SSL");
            ERR_print_errors_fp(stderr);
            throw SSLException("Unable to send command via SSL.");
        }
        DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPConnection::sendCommand() -> IMAP command sent via SSL.");
   
    } else {

        int len = strlen(command);
        if (BIO_write(bio, command, len) <= 0) {
            DEBUG_PRINT(ANSI_COLOR_RED, "IMAPConnection::sendCommand() -> Unable to send command via BIO");
            ERR_print_errors_fp(stderr);
            throw BIOException("Unable to send command via BIO.");
        }

        DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPConnection::sendCommand() -> IMAP command sent via BIO.");
    
    }

}


/**
 *  @brief Reads the IMAP server's response.
 *  
 *  Reads and prints the server's response after sending an IMAP command.
 *
 *  @param endCondition The specific condition, that must be in the packet to end packets reading.
 * 
 *  @return The server's response as a std::string.
 */
std::string IMAPConnection::readResponse(const std::string& endCondition)
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "IMAPConnection::readResponse() -> Reading IMAP response...");
    char buffer[4096];
    int bytes;
    std::string response; 

    // Secure connection (SSL) or non-secure (BIO).
    if (this->secure) {

        while ((bytes = SSL_read(this->ssl, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes] = '\0';  
            response += buffer;

            // Check for the specified end condition.
            if (response.find(endCondition) != std::string::npos) {
                DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPConnection::readResponse() -> End of response received with specified condition.");
                break;
            }
        }

        // If there is an error while reading message with SSL.
        if (bytes < 0) {
            DEBUG_PRINT(ANSI_COLOR_RED, "IMAPConnection::readResponse() -> Unable to read response via SSL.");
            ERR_print_errors_fp(stderr);
            throw SSLException("Unable to read response via SSL.");
        }

        // Recursive call to continue reading if full response not yet received.
        if (bytes > 0 && response.find(endCondition) == std::string::npos) {
            response += this->readResponse(endCondition);
        }

    } else {

        while ((bytes = BIO_read(this->bio, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes] = '\0';  
            response += buffer;    

            // Check for the specified end condition.
            if (response.find(endCondition) != std::string::npos) {
                DEBUG_PRINT(ANSI_COLOR_GREEN, "IMAPConnection::readResponse() -> End of response received with specified condition.");
                break;
            }
        }

        // If there is an error while reading message with BIO.
        if (bytes < 0) {
            DEBUG_PRINT(ANSI_COLOR_RED, "IMAPConnection::readResponse() -> Unable to read response via BIO.");
            ERR_print_errors_fp(stderr);
            throw BIOException("Unable to read response via BIO.");
        }

        // Recursive call to continue reading if full response not yet received.
        if (bytes > 0 && response.find(endCondition) == std::string::npos) {
            response += this->readResponse(endCondition);
        }
    }

    return response;

}