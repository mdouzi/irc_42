#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "server.hpp"
#include "client.hpp"


class client;
class my_server;

class Channel {
  private:
        std::string name;
        std::string topic;
        std::vector<client> users;
        std::vector<client> operators;
        std::string password;
        std::vector<client> invited;
        std::string mode;
  public:
        Channel();
        Channel(std::string name, std::string topic, client op, std::string password);
        Channel(std::string name, std::string topic);
        ~Channel();
        std::string const & getName() const;
        std::string const & getTopic() const;
        std::string const & getPassword() const;
       std::string const & getMode() const;
        
        std::vector<client> const &getUsers() const;
        std::vector<client> const &getoperators() const;
        std::vector<client> const &getInvitedClients() const;


        void setName(std::string const & str);
        void setTopic(std::string const & str);
        void setPassword(std::string const & str);
      //   void setMode(std::string const & str);

        void sendMessageToChannel(my_server server, std::string message);
        void receiveMessage(std::string const & message);


        void addClientToChannel(const client newClient);
        bool isOperator(client newClient);
        void deleteClientFromChannel(client newClient);
        bool isClientcInChannel(std::string name);
        void broadcast(std::string message);
};


#endif
