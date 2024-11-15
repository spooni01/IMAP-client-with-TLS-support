/**
 *	@file	Classes/IMAPConnection/IMAPConnection.hpp
 *	@brief	IMAPConnection header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef IMAPCONNECTION_HPP
#define IMAPCONNECTION_HPP


/**
 *  @class IMAPConnection
 *  @brief This class handles communication between the client and an IMAP server.
 *  
 *  This class manages the connection to the IMAP server using SSL/TLS. It is responsible
 *  for establishing the connection, sending commands, and reading responses over SSL-secured
 *  communication.
 */
class IMAPConnection {
private:
    
    /**
     * @brief Indicates whether the connection is secure.
     *
     * If `true`, the connection uses SSL/TLS for secure communication.
     * If `false`, the connection uses an unencrypted, plain BIO connection.
     */
    bool secure;
    /**
     *  @brief OpenSSL context pointer for managing SSL sessions.
     *  
     *  This context is used to set up SSL connections.
     */
    SSL_CTX *ctx;
    
    /**
     *  @brief BIO pointer for the network communication.
     *  
     *  BIO (Basic Input/Output) is used to establish the network connection to the server.
     */
    BIO *bio;
    
    /**
     *  @brief SSL pointer for managing the encrypted connection.
     *  
     *  This SSL object represents the secured connection using SSL/TLS protocols.
     */
    SSL *ssl;

public:
    
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
    IMAPConnection(bool secure, const char *server, int port);

    /**
     *  @brief Destructor for the IMAPConnection class.
     *  
     *  Cleans up and releases all resources used by the IMAPConnection object, including
     *  the SSL context, SSL object, and BIO connection. This ensures proper cleanup
     *  of resources when the object is destroyed.
     */
    ~IMAPConnection();
    
    /**
     *  @brief Initializes OpenSSL libraries.
     *  
     *  This function loads OpenSSL error strings and algorithms required for SSL communication.
     */
    void initOpenSSL();
    
    /**
     *  @brief Creates an SSL context.
     *  
     *  Creates and returns an SSL context object that will be used for SSL connections.
     *  
     *  @return A pointer to the created SSL context.
     */
    SSL_CTX *createSSLContext();
    
    /**
     *  @brief Creates a BIO connection.
     *  
     *  Establishes a low-level network connection (BIO) to the given server and port.
     *  
     *  @param host The server's hostname or IP address.
     *  @param port The port number on the server to connect to.
     *  @return A pointer to the created BIO object for the connection.
     */
    BIO *createBioConnection(const char *host, int port);
    
    /**
     *  @brief Creates an SSL connection.
     *  
     *  Establishes an SSL/TLS connection using the provided SSL context and BIO connection.
     *  
     *  @param ctx The SSL context to use for the connection.
     *  @param bio The BIO connection to use for the underlying network communication.
     *  @return A pointer to the created SSL object for the secured connection.
     */
    SSL *createSSLConnection(SSL_CTX *ctx, BIO *bio);
    
    /**
     *  @brief Sends an IMAP command to the server.
     *  
     *  This function sends an IMAP command to the server over the established SSL connection.
     *  
     *  @param command The IMAP command string to send.
     */
    void sendCommand(const char *command);
    
    /**
     *  @brief Reads the IMAP server's response.
     *  
     *  Reads and prints the server's response after sending an IMAP command.
     *
     *  @return The server's response as a std::string.
     */
    std::string readResponse(const std::string& endCondition);
    
};


#endif // IMAPCONNECTION_HPP