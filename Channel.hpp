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
  public:
      Channel();
      Channel(std::string name, std::string topic, client op, std::string password);
      Channel(std::string name, std::string topic);
      ~Channel();
      std::string const & getName() const;
      std::string const & getTopic() const;
      std::string const & getPassword() const;
      
      std::vector<client> const &getUsers() const;
      std::vector<client> const &getoperators() const;
      std::vector<client> const &getInvitedClients() const;


      void setName(std::string const & str);
      void setTopic(std::string const & str);
      void setPassword(std::string const & str);
      

      void addClientToChannel(client newClient);
      bool isOperator(client newClient);
      void deleteClientFromChannel(client newClient);
      bool isClientcInChannel(std::stering name);
      void broadcast(std::string message);
};


#endif
