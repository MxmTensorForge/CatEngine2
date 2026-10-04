#include "NetworkClient.h"

#include "../Core/Logger.h"

NetworkClient::NetworkClient() : _id{0}, _isConnected{false} {
    enet_initialize();
}
NetworkClient::~NetworkClient() {
    if (_peer) enet_peer_disconnect_now(_peer, 0);
    if (_host) enet_host_destroy(_host);
    
    enet_deinitialize();
}

void NetworkClient::connect(const std::string& ip, uint16_t port) {
    if (_host) {
        enet_host_destroy(_host);
        _host = nullptr;
    }

    _host = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!_host) return;

    ENetAddress address;
    enet_address_set_host(&address, ip.c_str());
    address.port = port;

    Logger::getInstance().log(LogType::Message, "Connecting to " + ip + ":" + std::to_string(port));
    _peer = enet_host_connect(_host, &address, 2, 0);
    if (!_peer) {
        Logger::getInstance().log(LogType::Warning, "Connecting failed");
    }
}
void NetworkClient::disconnect() {
    if (_peer) {
        enet_peer_disconnect(_peer, 0);
    }
}
void NetworkClient::update() {
    if (!_host) return;
    
    ENetEvent event;
    while (enet_host_service(_host, &event, 0) > 0)
    {
        if (event.type == ENET_EVENT_TYPE_CONNECT) {
            _isConnected = true;
            _peer = event.peer; 
            
            if (_onConnectCallback) _onConnectCallback();
        } else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
            _isConnected = false;
            _id = 0;
            _peer = nullptr;
            
            if (_onDisconnectCallback) _onDisconnectCallback();
        } else if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            BufferReader reader(event.packet->data, event.packet->dataLength);
            MessageType type = reader.read<MessageType>();
            
            if (type == UINT32_MAX) {
                _id = reader.read<ConnectionId>();
                enet_packet_destroy(event.packet);
                continue;
            }

            auto it = _onReceivePackets.find(type);
            if (it != _onReceivePackets.end()) {
                it->second(reader);
            }

            enet_packet_destroy(event.packet);
        }
    }
}
