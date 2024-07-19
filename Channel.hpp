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
        bool getTopicRestricted();


        void setMode(std::string const & str);
        void setName(std::string const & str);
        void setTopic(std::string const & str);
        void setPassword(std::string const & str);
        void setInviteOnly(bool isInviteOnly);
        void setTopicRestricted(bool isTopicRestricted);
        void setLimited(bool isLimited, int limit);
        void setInvitedClients(client newClient);
        void setHavePassword(bool havePassword);

        void sendMessageToChannel(my_server& server, std::string message , int index);
        void deleteUser(std::string const & userName);
        void send_reply(int cfd, std::string const & message);
        void broadcast(std::string message);

        bool isInvited(client newClient);
        void addClientToChannel(const client newClient);
        bool isClientInChannel(Channel channel);
        bool isOperator(client newClient);
        bool isInviteOn();
        bool isHavePassword();

        bool isMember(std::string const & ClientName);
        void addOperator(std::string newClient);
        void removeOperator(std::string newClient);
};


#endif
