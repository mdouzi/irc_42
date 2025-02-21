# IRC_42

IRC_42 is a custom IRC (Internet Relay Chat) server implemented as part of the 42 school curriculum. It is built to follow the RFC 1459 standard, allowing multiple users to communicate in real-time through channels.

## Features
- Handles multiple clients with socket programming
- Supports basic IRC commands (`JOIN`, `PART`, `KICK`, `PRIVMSG`, `NOTICE`, etc.)
- Channel management with operators and user privileges
- Private messaging between users
- Nickname registration and authentication
- Graceful handling of client connections and disconnections

## Requirements
- Linux/macOS
- C++ Compiler (g++)
- Make

## Installation
Clone the repository and compile the project:
```sh
git clone https://github.com/yourusername/irc_42.git
cd irc_42
make
```

## Usage
Run the server with:
```sh
./ircserv <port> <password>
```
Example:
```sh
./ircserv 6667 mypassword
```
Then, connect using any IRC client:
```sh
/connect 127.0.0.1 6667 mypassword
```

## Authors
- Mohamed Douzi

## License
This project is part of the 42 curriculum and follows its academic integrity rules.

