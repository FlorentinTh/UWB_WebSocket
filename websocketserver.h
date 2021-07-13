#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <set>
#include <QThread>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> Server;
typedef std::set<websocketpp::connection_hdl,std::owner_less<websocketpp::connection_hdl>> Connections;

class WebSocketServer : public QThread
{
public:
    WebSocketServer(unsigned short int port);
    void onOpen(websocketpp::connection_hdl connection);
    void onClose(websocketpp::connection_hdl connection);
    void sendData(std::string message);

protected:
    virtual void run() override;

private:
    unsigned short int _port;
    Server _server;
    Connections _connections;
};

#endif // WEBSOCKETSERVER_H
