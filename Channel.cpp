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
    // Initialize members
}

// Destructor
Channel::~Channel() {
    // Clean up if needed
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
std::vector<client> const & Channel::getUsers() const {
    return users;
}

// Getter for invited clients vector
std::vector<client> const & Channel::getInvitedClients() const {
    return invited;
}

// setter for Limited
void Channel::setLimited(bool isLimited, int limit) {
    _isLimited = isLimited;
    _limit = limit;
}

// setter for TopicRestricted
void Channel::setTopicRestricted(bool isTopicRestricted) {
    _isTopicRestricted = isTopicRestricted;
}

// setter for InviteOnly
void Channel::setInviteOnly(bool isInviteOnly) {
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
void Channel::addClientToChannel(my_server server, const client newClient, int index) {
    server.channels[index].users.push_back(newClient);
    std::cout << "size of users: " << server.channels[index].users.size() << std::endl;
}

void Channel::sendMessageToChannel(my_server server, std::string message, int index) {
    std::cout << "size of users: " << server.channels[index].users.size() << std::endl;
    for (size_t i = 0; i < server.channels[index].users.size(); ++i) {
        std::cout << "the users are: " << server.channels[index].users[i].getNickName() << std::endl;
        server.send_reply(server.channels[index].users[i].getClientFd(), message);
    }
}

// remove operator
void Channel::removeOperator(client newClient) {
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i].getNickName() == newClient.getNickName()) {
            operators.erase(operators.begin() + i);
            break;
        }
    }
}

// Set operator
void Channel::addOperator(client newClient) {
    operators.push_back(newClient);
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

// Check if a client is a member of the channel
bool Channel::isMember(std::string const & ClientName) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].getNickName() == ClientName) {
            return true;
        }
    }
    return false;
}

// Remove client from users vector
//  void Channel::deleteClientFromChannel(client newClient) {
//      for (size_t i = 0; i < users.size(); ++i) {
//          if (users[i].getNickName() == newClient.getNickName()) {
//              users.erase(users.begin() + i);
//              break;
//          }
//      }
//  }

// Check if a client (by name) is in the channel
//  bool Channel::isClientInChannel(my_server server, std::string name) {
//      for (size_t i = 0; i < users.size(); ++i) {
//          if ( == name) {
//              return true;
//          }
//      }
//      return false;
//  }

// // Broadcast a message to all clients in the channel
//  void Channel::broadcast(std::string message) {
//      for (size_t i = 0; i < users.size(); ++i) {
//          users[i].receiveMessage(message);
//      }
// }

// isInviteOnly
bool Channel::isInviteOn() {
    return _isInviteOnly;
}
