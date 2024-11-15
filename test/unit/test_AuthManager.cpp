TEST(AuthManagerTest, ValidFile) {
    const std::string filepath = "valid_auth.txt";
    std::ofstream file(filepath);
    file << "username=test_user\npassword=test_pass\n";
    file.close();

    EXPECT_NO_THROW({
        AuthManager authManager(filepath);
        EXPECT_EQ(authManager.getUsername(), "test_user");
        EXPECT_EQ(authManager.getPassword(), "test_pass");
    });

    std::remove(filepath.c_str());
}

TEST(AuthManagerTest, MissingFile) {
    const std::string filepath = "missing_auth.txt";
    EXPECT_THROW(AuthManager authManager(filepath), FileException);
}

TEST(AuthManagerTest, InvalidFormat) {
    const std::string filepath = "invalid_auth.txt";
    std::ofstream file(filepath);
    file << "username=test_user\ninvalid_line\npassword=test_pass\n";
    file.close();

    EXPECT_THROW(AuthManager authManager(filepath), AuthenticateException);

    std::remove(filepath.c_str());
}

TEST(AuthManagerTest, MissingFields) {
    const std::string filepath = "missing_fields_auth.txt";
    std::ofstream file(filepath);
    file << "username=test_user\n";
    file.close();

    EXPECT_THROW(AuthManager authManager(filepath), AuthenticateException);

    std::remove(filepath.c_str());
}

TEST(AuthManagerTest, ExtraWhitespace) {
    const std::string filepath = "whitespace_auth.txt";
    std::ofstream file(filepath);
    file << "  username  =   test_user   \n  password   =   test_pass   \n";
    file.close();

    EXPECT_NO_THROW({
        AuthManager authManager(filepath);
        EXPECT_EQ(authManager.getUsername(), "test_user");
        EXPECT_EQ(authManager.getPassword(), "test_pass");
    });

    std::remove(filepath.c_str());
}