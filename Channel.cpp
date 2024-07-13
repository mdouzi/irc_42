#include "Channel.hpp"

// Default constructor
Channel::Channel() {
    // Initialize members if needed
}

// Constructor with specified parameters
Channel::Channel(std::string name, std::string topic, client op, std::string password)
    : name(name), topic(topic), password(password) {
    operators.push_back(op); // Add operator to operators vector
}

// Constructor without password and operator
Channel::Channel(std::string name, std::string topic)
    : name(name), topic(topic) {
        _isInviteOnly = false;
        _isLimited = false;
        _isTopicRestricted = false;
        _limit = 0;
        std::cout << " >>>>>>>   Channel created <<<<<<<<  " << std::endl;
    // Initialize members
}

// Destructor
Channel::~Channel() {
    // Clean up if needed
}

// Getter for topic
bool Channel::getTopicRestricted() {
    return _isTopicRestricted;
}

// Getter for mode
std::string const & Channel::getMode() const {
    return mode;
}

// Getter for name
std::string const & Channel::getName() const {
    return name;
}

// Getter for topic
std::string const & Channel::getTopic() const {
    return topic;
}

// Getter for password
std::string const & Channel::getPassword() const {
    return password;
}

// Getter for users vector
std::vector<client> & Channel::getUsers() {
    return users;
}

// check if the client is invited to the channel
bool Channel::isInvited(client newClient) {
    for (size_t i = 0; i < invited.size(); ++i) {
        if (invited[i].getNickName() == newClient.getNickName()) {
            return true;
        }
    }
    return false;
}

// isInviteOnly
bool Channel::isInviteOn() {
    return _isInviteOnly;
}

// setter for invited clients
void Channel::setInvitedClients(client newClient) {
    invited.push_back(newClient);
}

// setter for Limited
void Channel::setLimited(bool isLimited, int limit) {
    std::cout << isLimited << " Limited" << limit << std::endl;
    std::cout << limit << "   limit" << std::endl;
    _isLimited = isLimited;
    _limit = limit;
}

// setter for TopicRestricted
void Channel::setTopicRestricted(bool isTopicRestricted) {
    _isTopicRestricted = isTopicRestricted;
}

// getter for Limited
size_t Channel::getLimit() const {
    return _limit;
}

// setter for Mode
void Channel::setMode(std::string const & str) {
    mode = str;
}

// setter for InviteOnly
void Channel::setInviteOnly(bool isInviteOnly) {
    std::cout << "hahwa HSAAAAAAAAALLLLLLLL " << std::endl;
    _isInviteOnly = isInviteOnly;
}

// Setter for name
void Channel::setName(std::string const & str) {
    name = str;
}

// Setter for topic
void Channel::setTopic(std::string const & str) {
    topic = str;
}

// Setter for password
void Channel::setPassword(std::string const & str) {
    password = str;
}

// Add client to users vector
void Channel::addClientToChannel(const client newClient) {
    this->users.push_back(newClient);
}

// Send message to all clients in the channel
void Channel::sendMessageToChannel(my_server& server, std::string message, int index) {
    std::string messageToSend = ":" + server.clients[index].getNickName() + "!" + server.clients[index].getUserName() + " PRIVMSG " + this->name + " :" + message;

    for (size_t i = 0; i < this->users.size(); ++i) {
        if (this->users[i].getNickName() != server.clients[index].getNickName()) {
            server.send_reply(this->users[i].getClientFd(), messageToSend);
        }
        // server.send_reply(this->users[i].getClientFd(), message);
    }
}

// :dan!~h@localhost PRIVMSG #coolpeople :Hi everyone!

// remove operator
void Channel::removeOperator(std::string newClient) {
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i].getNickName() == newClient) {
            operators.erase(operators.begin() + i);
            break;
        }
    }
}

// Set operator
void Channel::addOperator(std::string newClient) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].getNickName() == newClient) {
            operators.push_back(users[i]);
            break;
        }
    }
    // operators.push_back(newClient);
}

// Check if a client is an operator
bool Channel::isOperator(client newClient) {
     for (size_t i = 0; i < operators.size(); ++i) {
         if (operators[i].getNickName() == newClient.getNickName()) {
           return true;
        }
     }
     return false;
}

// getter fors
std::vector<client> & Channel::getOperators() {
    return operators;
}

// Check if a client is a member of the channel
bool Channel::isMember(std::string const & ClientName) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].getNickName() == ClientName) {
            return true;
        }
    }
    return false;
}

// // Remove client from users vector
//  void Channel::deleteClientFromChannel(client newClient) {
//      for (size_t i = 0; i < users.size(); ++i) {
//          if (users[i].getNickName() == newClient.getNickName()) {
//              users.erase(users.begin() + i);
//              break;
//          }
//      }
//  }

// // Check if a client (by name) is in the channel
//  bool Channel::isClientInChannel(my_server server, std::string name) {
//      for (size_t i = 0; i < users.size(); ++i) {
//          if ( == name) {
//              return true;
//          }
//      }
//      return false;
//  }

// // Broadcast a message to all clients in the channel (not used)
//  void Channel::broadcast(std::string message) {
//      for (size_t i = 0; i < users.size(); ++i) {
//          users[i].receiveMessage(message);
//      }
// }


