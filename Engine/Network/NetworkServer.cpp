#include "NetworkServer.h"

NetworkServer::NetworkServer() : _nextId{0} {
    enet_initialize();
}
NetworkServer::~NetworkServer() {
    if (_host) enet_host_destroy(_host);
    
    enet_deinitialize();
}

void NetworkServer::start(uint16_t port, size_t maxPeers) {
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;

    _host = enet_host_create(&address, maxPeers, 2, 0, 0);
    if (!_host) return;
}
void NetworkServer::update() {
    if (!_host) return;
    
    ENetEvent event;
    while (enet_host_service(_host, &event, 0) > 0)
    {
        if (event.type == ENET_EVENT_TYPE_CONNECT) {
            ConnectionId currentId = _nextId++;
            
            event.peer->data = new ConnectionId(currentId);
            _peers[currentId] = event.peer;
            
            BufferWritter writter;
            writter.write(currentId);
            send(currentId, UINT32_MAX, writter, 0, true);
            
            if (_onConnectCallback) _onConnectCallback(currentId);
        } else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
            ConnectionId currentId = *static_cast<ConnectionId*>(event.peer->data);
            delete static_cast<ConnectionId*>(event.peer->data);
            
            if (_onDisconnectCallback) _onDisconnectCallback(currentId);
            _peers.erase(currentId);
        } else if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            ConnectionId currentId = *static_cast<ConnectionId*>(event.peer->data);

            BufferReader reader(event.packet->data, event.packet->dataLength);

            MessageType type = reader.read<MessageType>();

            auto it = _onReceivePackets.find(type);
            if (it != _onReceivePackets.end()) {
                it->second(currentId, reader);
            }

            enet_packet_destroy(event.packet);
        }
    }
}

void NetworkServer::kick(ConnectionId id) noexcept {
    auto it = _peers.find(id);
    if (it != _peers.end()) {
        enet_peer_disconnect(it->second, 0);
    }
}
std::string NetworkServer::getIp(ConnectionId id) noexcept {
    std::string address;
    
    auto it = _peers.find(id);
    if (it != _peers.end()) {
        char ip[64];
        enet_address_get_host_ip(&it->second->address, ip, sizeof(ip));

        address = ip;
    }
    return address;
}

void NetworkServer::forEachPeer(const std::function<void(ConnectionId)>& func) const noexcept {
    for (const auto& [id, peer] : _peers) {
        func(id);
    }
}
