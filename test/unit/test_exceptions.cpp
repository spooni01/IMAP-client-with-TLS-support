TEST(ExceptionTest, ArgumentsExceptionTest) {
    try {
        throw ArgumentsException("Invalid arguments provided");
    } catch (const ArgumentsException& e) {
        EXPECT_STREQ(e.what(), "Invalid arguments provided");
        EXPECT_EQ(e.code(), 10);
    }
}

TEST(ExceptionTest, AuthenticateExceptionTest) {
    try {
        throw AuthenticateException("Authentication failed");
    } catch (const AuthenticateException& e) {
        EXPECT_STREQ(e.what(), "Authentication failed");
        EXPECT_EQ(e.code(), 11);
    }
}

TEST(ExceptionTest, BIOExceptionTest) {
    try {
        throw BIOException("BIO error occurred");
    } catch (const BIOException& e) {
        EXPECT_STREQ(e.what(), "BIO error occurred");
        EXPECT_EQ(e.code(), 22);
    }
}

TEST(ExceptionTest, CommandExceptionTest) {
    try {
        throw CommandException("Invalid command");
    } catch (const CommandException& e) {
        EXPECT_STREQ(e.what(), "Invalid command");
        EXPECT_EQ(e.code(), 23);
    }
}

TEST(ExceptionTest, ConnectionExceptionTest) {
    try {
        throw ConnectionException("Connection error occurred");
    } catch (const ConnectionException& e) {
        EXPECT_STREQ(e.what(), "Connection error occurred");
        EXPECT_EQ(e.code(), 20);
    }
}

TEST(ExceptionTest, FileExceptionTest) {
    try {
        throw FileException("File not found");
    } catch (const FileException& e) {
        EXPECT_STREQ(e.what(), "File not found");
        EXPECT_EQ(e.code(), 12);
    }
}

TEST(ExceptionTest, MailboxExceptionTest) {
    try {
        throw MailboxException("Mailbox operation failed");
    } catch (const MailboxException& e) {
        EXPECT_STREQ(e.what(), "Mailbox operation failed");
        EXPECT_EQ(e.code(), 30);
    }
}

TEST(ExceptionTest, SSLExceptionTest) {
    try {
        throw SSLException("SSL handshake failed");
    } catch (const SSLException& e) {
        EXPECT_STREQ(e.what(), "SSL handshake failed");
        EXPECT_EQ(e.code(), 30);
    }
}

TEST(ExceptionTest, IMAPExceptionTest) {
    try {
        throw IMAPException("IMAP error occurred");
    } catch (const IMAPException& e) {
        EXPECT_STREQ(e.what(), "IMAP error occurred");
        EXPECT_EQ(e.code(), 2);
    }
}

TEST(ExceptionTest, IMAPExceptionTestOwnReturnCode) {
    try {
        throw IMAPException("IMAP error occurred", 999);
    } catch (const IMAPException& e) {
        EXPECT_STREQ(e.what(), "IMAP error occurred");
        EXPECT_EQ(e.code(), 999);
    }
}