#include <iostream>
#include "websocketserver.h"

WebSocketServer::WebSocketServer(unsigned short int port)
{
    _server.clear_access_channels(websocketpp::log::alevel::frame_header | websocketpp::log::alevel::frame_payload);

    _server.init_asio();

    _server.set_open_handler(bind(&WebSocketServer::onOpen, this,
                                     websocketpp::lib::placeholders::_1));
    _server.set_close_handler(bind(&WebSocketServer::onClose, this,
                                      websocketpp::lib::placeholders::_1));

    _port = port;
}

void WebSocketServer::run()
{
    _server.listen(_port);
    _server.start_accept();
    _server.run();
}

void WebSocketServer::onOpen(websocketpp::connection_hdl connection)
{
    _connections.insert(connection);
}

void WebSocketServer::onClose(websocketpp::connection_hdl connection)
{
    _connections.erase(connection);
}

void WebSocketServer::sendData(std::string message)
{
    for (auto connection : _connections)
    {
        if(_server.get_con_from_hdl(connection)->get_state() ==
                websocketpp::session::state::open)
        {
            _server.send(connection, message, websocketpp::frame::opcode::text);
        }
    }
}
