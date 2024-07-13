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

        size_t getLimit() const;
        
        std::vector<client> &getUsers() ;
        std::vector<client> &getOperators() ;
        // std::vector<client> const &getInvitedClients() const;
        bool getTopicRestricted();


        void setMode(std::string const & str);
        void setName(std::string const & str);
        void setTopic(std::string const & str);
        void setPassword(std::string const & str);
        void setInviteOnly(bool isInviteOnly);
        void setTopicRestricted(bool isTopicRestricted);
        void setLimited(bool isLimited, int limit);
        void setInvitedClients(client newClient);

        void sendMessageToChannel(my_server& server, std::string message , int index);
        // void receiveMessage(std::string const & message);

        // check if the client if invited to the channel
        bool isInvited(client newClient);
        void addClientToChannel(const client newClient);
      //   void deleteClientFromChannel(client newClient);
        bool isClientInChannel(Channel channel);
        void broadcast(std::string message);
        bool isOperator(client newClient);
        bool isInviteOn();

        bool isMember(std::string const & ClientName);
        void addOperator(std::string newClient);
        void removeOperator(std::string newClient);
};


#endif
