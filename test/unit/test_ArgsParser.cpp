#include <gtest/gtest.h>

TEST(ArgsParserTest, ValidMinimalArguments) {
    const char* argv[] = { "program", "imap.example.com", "-a", "auth.txt", "-o", "output/" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_NO_THROW({
        ArgsParser parser(argc, const_cast<char**>(argv));
        EXPECT_EQ(parser.getServer(), std::string("imap.example.com"));
        EXPECT_EQ(parser.getAuthFile(), std::string("auth.txt"));
        EXPECT_EQ(parser.getOutDir(), std::string("output/"));
        EXPECT_EQ(parser.getPort(), 143);
        EXPECT_FALSE(parser.isTLS());
    });
}

TEST(ArgsParserTest, ValidTLSWithImplicitPort) {
    const char* argv[] = { "program", "imap.example.com", "-T", "-a", "auth.txt", "-o", "output/" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_NO_THROW({
        ArgsParser parser(argc, const_cast<char**>(argv));
        EXPECT_TRUE(parser.isTLS());
        EXPECT_EQ(parser.getPort(), 993);
    });
}

TEST(ArgsParserTest, MissingServer) {
    const char* argv[] = { "program", "-a", "auth.txt", "-o", "output/" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_THROW({
        ArgsParser parser(argc, const_cast<char**>(argv));
    }, ArgumentsException);
}

TEST(ArgsParserTest, MissingAuthFile) {
    const char* argv[] = { "program", "imap.example.com", "-o", "output/" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_THROW({
        ArgsParser parser(argc, const_cast<char**>(argv));
    }, ArgumentsException);
}

TEST(ArgsParserTest, InvalidPort) {
    const char* argv[] = { "program", "imap.example.com", "-p", "70000", "-a", "auth.txt", "-o", "output/" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_THROW({
        ArgsParser parser(argc, const_cast<char**>(argv));
    }, ArgumentsException);
}

TEST(ArgsParserTest, ValidCertificates) {
    const char* argv[] = { "program", "imap.example.com", "-T", "-c", "cert.pem", "-C", "/certs", "-a", "auth.txt", "-o", "output/" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_NO_THROW({
        ArgsParser parser(argc, const_cast<char**>(argv));
        EXPECT_EQ(parser.getCertFile(), std::string("cert.pem"));
        EXPECT_EQ(parser.getCertDir(), std::string("/certs"));
    });
}

TEST(ArgsParserTest, UnknownArgument) {
    const char* argv[] = { "program", "imap.example.com", "-x", "-a", "auth.txt", "-o", "output/" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_THROW({
        ArgsParser parser(argc, const_cast<char**>(argv));
    }, ArgumentsException);
}

TEST(ArgsParserTest, ValidMailboxArgument) {
    const char* argv[] = { "program", "imap.example.com", "-b", "Inbox", "-a", "auth.txt", "-o", "output/" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_NO_THROW({
        ArgsParser parser(argc, const_cast<char**>(argv));
        EXPECT_EQ(parser.getMailbox(), "Inbox");
    });
}

TEST(ArgsParserTest, HeadersOnlyAndReadOnlyNew) {
    const char* argv[] = { "program", "imap.example.com", "-n", "-h", "-a", "auth.txt", "-o", "output/" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    EXPECT_NO_THROW({
        ArgsParser parser(argc, const_cast<char**>(argv));
        EXPECT_TRUE(parser.isHeadersOnly());
        EXPECT_TRUE(parser.isReadOnlyNew());
    });
}
