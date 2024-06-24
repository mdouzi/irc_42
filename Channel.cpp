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

// Getter for name
std::string const & Channel::getName() const {
    return name;
}

// Getter for mode
std::string const & Channel::getMode() const {
    return mode;
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

// Getter for operators vector
std::vector<client> const & Channel::getoperators() const {
    return operators;
}

// Getter for invited clients vector
std::vector<client> const & Channel::getInvitedClients() const {
    return invited;
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

// Setter for mode
// void Channel::setMode(std::string const & str) {
//     mode = str;
//     ChannelsMode(server, index);
// }

// Add client to users vector
void Channel::addClientToChannel(client newClient) {
    users.push_back(newClient);
}

void Channel::sendMessageToChannel(my_server server, std::string message) {
    for (size_t i = 0; i < users.size(); ++i) {
        server.send_reply(users[i].getClientFd(), message);
    }
}


// Check if a client is an operator
// bool Channel::isOperator(client newClient) {
//     for (size_t i = 0; i < operators.size(); ++i) {
//         if (operators[i] == newClient) {
//             return true;
//         }
//     }
//     return false;
// }

// Remove client from users vector
// void Channel::deleteClientFromChannel(client newClient) {
//     for (size_t i = 0; i < users.size(); ++i) {
//         if (users[i] == newClient.getUserName()) {
//             users.erase(users.begin() + i);
//             break;
//         }
//     }
// }

// Check if a client (by name) is in the channel
// bool Channel::isClientcInChannel(std::string name) {
//     for (size_t i = 0; i < users.size(); ++i) {
//         if (users[i].getName() == name) {
//             return true;
//         }
//     }
//     return false;
// }

// // Broadcast a message to all clients in the channel
// void Channel::broadcast(std::string message) {
//     for (size_t i = 0; i < users.size(); ++i) {
//         users[i].receiveMessage(message);
//     }
// }
