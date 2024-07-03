#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "server.hpp"
#include "client.hpp"


class client;
class my_server;

class Channel {
  private:
        std::string name;
        std::string mode;
        std::string topic;
        std::vector<client> users;
        std::vector<client> operators;
        std::string password;
        std::vector<client> invited;
        int  _limit;
        bool _havePassword;
        bool _isInviteOnly;
        bool _isLimited;
        bool _topicRestricted;
        bool _isTopicRestricted;
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
        // std::vector<client> const &getOperators() const;
        std::vector<client> const &getInvitedClients() const;


        void setName(std::string const & str);
        void setTopic(std::string const & str);
        void setPassword(std::string const & str);
        void setInviteOnly(bool isInviteOnly);
        void setTopicRestricted(bool isTopicRestricted);
        void setLimited(bool isLimited, int limit);

        void sendMessageToChannel(my_server server, std::string message, int index);
        // void receiveMessage(std::string const & message);


        void addClientToChannel(my_server server, const client newClient, int index);
      //   void deleteClientFromChannel(client newClient);
        bool isClientInChannel(Channel channel);
        void broadcast(std::string message);
        bool isOperator(client newClient);
        bool isInviteOn();

        bool isMember(std::string const & ClientName);
        void addOperator(client newClient);
        void removeOperator(client newClient);
};


#endif
