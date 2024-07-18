#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "server.hpp"


class client {

    private:
        int client_fd;
        bool hexChat;
        std::string realname;
        std::string username;
        std::string hostname;
        std::string servername;
        std::string nickname;
        bool Alreadyregistred;
        bool Alreadyregistred2;
        bool isAuthenticated;
    public:
        client();
        ~client();
       void sethexChat(bool of);
       void setNickName(std::string const & str);
       void setRealName(std::string const & str);
       void setHostName(std::string const & str);
       void setServerName(std::string const & str);
       void setUserName(std::string const & str);
        void setAuth(bool of);
        void setReg(bool of);
        void setReg2(bool of);
        void setClientFd(int fd);

        std::string const &getNickName();
        std::string const &getRealName();
        std::string const &getHostName();
        std::string const &getServerName();
        std::string const &getUserName();

        bool getHexChat();
        bool getAuth();
        bool getReg();
        bool getReg2();
        int getClientFd();

};

#endif

