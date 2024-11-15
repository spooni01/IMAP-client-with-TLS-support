class MessageTest : public ::testing::Test {
protected:
    const std::string rawMessage = "* 2 FETCH (UID 2032 BODY[] {882}\n"
                                   "Return-Path: <xlizic00@stud.fit.vutbr.cz>\n"
                                   "Received: from roundcube.fit.vut.cz\n"
                                   "MIME-Version: 1.0\n"
                                   "Date: Fri, 15 Nov 2024 10:07:02 +0100\n"
                                   "From: =?UTF-8?Q?Li=C5=BEi=C4=8Diar_Adam?= <xlizic00@stud.fit.vutbr.cz>\n"
                                   "To: =?UTF-8?Q?Li=C5=BEi=C4=8Diar_Adam?= <xlizic00@stud.fit.vut.br>\n"
                                   "Subject: Predmet\n"
                                   "User-Agent: Roundcube Webmail\n"
                                   "Message-ID: <452e6ebc8446c0eb59446aae5ca70615@stud.fit.vut.cz>\n"
                                   "Content-Type: text/plain; charset=UTF-8;\n"
                                   "Content-Transfer-Encoding: 8bit\n"
                                   "\nTest message body.\n)A004 OK Fetch completed (0.001 + 0.000 secs).\n";

    Message msg;

    void SetUp() override {
        msg = Message(rawMessage);
    }
};

TEST_F(MessageTest, ExtractUID) {
    std::string expectedUID = "2032";  
    EXPECT_EQ(msg.extractUID(rawMessage), expectedUID);
}

TEST_F(MessageTest, GetFormattedOutput) {
    std::string formattedOutput = msg.getFormattedOutput();
    
    EXPECT_TRUE(formattedOutput.find("Date: Fri, 15 Nov 2024 10:07:02 +0100") != std::string::npos);
    EXPECT_TRUE(formattedOutput.find("From: Ližičiar Adam <xlizic00@stud.fit.vut.br>") != std::string::npos);
    EXPECT_TRUE(formattedOutput.find("Subject: Predmet") != std::string::npos);
}

TEST_F(MessageTest, GetFileName) {
    std::string expectedFileName = "452e6ebc8446c0eb59446aae5ca70615@stud.fit.vut.cz"; 
    EXPECT_EQ(msg.getFileName(), expectedFileName);
}

TEST_F(MessageTest, DecodeMime) {
    std::string encodedText = "=?UTF-8?Q?Li=C5=BEi=C4=8Diar_Adam?=";
    std::string decodedText = msg.decodeMime(encodedText);
    EXPECT_EQ(decodedText, "Ližičiar Adam");
}

TEST_F(MessageTest, RemoveLastLine) {
    std::string body = "This is the body.\nThis is the second line.\n";
    std::string result = msg.removeLastLine(body);
    EXPECT_EQ(result, "This is the body.\nThis is the second line.");
    
    std::string singleLine = "Only one line.";
    std::string resultSingleLine = msg.removeLastLine(singleLine);
    EXPECT_EQ(resultSingleLine, "Only one line.");
}

TEST_F(MessageTest, ParseMessage) {
    std::string body = msg.getFormattedOutput(); 
    EXPECT_TRUE(body.find("Test message body.") != std::string::npos);

    std::map<std::string, std::string> headers = msg.headers;
    EXPECT_EQ(headers.at("From"), "Ližičiar Adam <xlizic00@stud.fit.vut.br>");
    EXPECT_EQ(headers.at("Subject"), "Predmet");
    EXPECT_EQ(headers.at("Date"), "Fri, 15 Nov 2024 10:07:02 +0100");
}
