# IMAP klient s podporou TLS
Hlavným zmyslom tohto programu je umožniť používateľovi čítanie emailov zo svojej emailovej schránky pomocou IMAP(S) protokolu s možnou podporou šifrovacieho protokolu TLS.<br>
IMAP je sieťový protokol, ktorý umožnuje klientovi pristupovať k e-mailom, ktoré sú umiestnené na vzdialenom serveri. Tento protokol umožnuje synchronizáciu medzi klientom a serverom, a teda je možný prístup k svojím e-mailom z rôznych zariadení.<br>
TLS je šifrovací protokol, ktorý robí komunikáciu medzi dvoma zariadeniami bezpečnejšou, teda v prípade tohto programu ochraňuje prenos údajov medzi klientom a serverom. V prípade, keď sa pripája klient pomocou IMAPS, automaticky sa vytvorí TLS spojenie, ktoré túto komunikáciu zabezpečuje.<br>
IMAPS je teda komunikácia protokolom IMAP s podporou šifrovacieho protokolu TLS.<br>

### Možné chyby
* Zo zatiaľ nezistených príčin nastáva niekedy problém pri overovaní certifikátov a pripájaní sa na takéto serveri

### Použitie programu
```
imapcl server [-p port] [-T [-c certfile] [-C certaddr]] [-n] [-h] -a auth_file [-b MAILBOX] -o out_dir
```

### Odovzdané súbory
```
.
├── doc
│   ├── bib
│   │   ├── czechiso.bst
│   │   ├── manual.bib
│   ├── res
│   │   ├── logo_FIT.pdf
│   │   ├── diagram_class.png
│   │   ├── diagram_usecase.png
│   │   ├── diagram_sequence.pdf
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
Vytvorené dňa 17.11.2024