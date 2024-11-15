# IMAP klient s TLS podporou
Program umožnuje čítať e-maily pomocou IMAP4rev1 (RFC 3501) protokolu. <br>

### Možné chyby
* Zo zatiaľ nezistených príčin nastáva niekedy problém pri overovaní certifikátov

### Rozšírenia 
* TODO

### Použitie programu
```
imapcl server [-p port] [-T [-c certfile] [-C certaddr]] [-n] [-h] -a auth_file [-b MAILBOX] -o out_dir
```

### Odovzdané súbory
```
.
├── doc
│   ├── res
│   │   ├── logo_FIT.pdf
│   ├── manual.tex
├── src
│   ├── classes
│   │   ├── ArgsParser
│   │   │   ├── ArgsParser.cpp
│   │   │   ├── ArgsParser.hpp
│   │   ├── AuthManager
│   │   │   ├── AuthManager.cpp
│   │   │   ├── AuthManager.hpp
│   │   ├── FiniteStateMachine
│   │   │   ├── FiniteStateMachine.cpp
│   │   │   ├── FiniteStateMachine.hpp
│   │   ├── IMAPClient
│   │   │   ├── IMAPClient.cpp
│   │   │   ├── IMAPClient.hpp
│   │   ├── IMAPConnection
│   │   │   ├── IMAPConnection.cpp
│   │   │   ├── IMAPConnection.hpp
│   │   ├── Message
│   │   │   ├── Message.cpp
│   │   │   ├── Message.hpp
│   │   ├── MessageFactory
│   │   │   ├── MessageFactory.cpp
│   │   │   ├── MessageFactory.hpp
│   ├── exceptions
│   │   ├── ArgumentsException.cpp
│   │   ├── AuthenticateException.cpp
│   │   ├── BIOException.cpp
│   │   ├── CommandException.cpp
│   │   ├── ConnectionException.cpp
│   │   ├── FileException.cpp
│   │   ├── IMAPException.cpp
│   │   ├── MailboxException.cpp
│   │   ├── SSLException.cpp
│   ├── main.cpp
│   ├── main.hpp
├── tests
│   ├── unit
│   │   ├── __init__.py
│   │   ├── test_ArgsParser.py
│   │   ├── test_AuthManager.py
│   │   ├── test_exceptions.py
│   │   ├── test_FiniteStateMachine.py
│   │   ├── test_Message.py
│   ├── valgrind
│   │   ├── suppressions.valgrind
├── .gitattributes
├── .gitignore
├── LICENSE
├── Makefile
├── manual.pdf
└── README.md
```

### Author
Adam Ližičiar (xlizic00@vutbr.cz)<br>
Vytvorené dňa 16.11.2024
