#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <enet/enet.h>
#include <functional>
#include <unordered_map>
#include <cstdint>
#include <string>

#include "BufferReader.h"
#include "BufferWritter.h"

using ConnectionId = uint32_t;
using MessageType = uint32_t;

using OnConnectCallback = std::function<void(ConnectionId)>;
using OnDisconnectCallback = std::function<void(ConnectionId)>;
using OnReceiveCallback = std::function<void(ConnectionId, BufferReader&)>;

class NetworkServer final
{
private:
    ENetHost* _host = nullptr;

    std::unordered_map<ConnectionId, ENetPeer*> _peers;

    OnConnectCallback _onConnectCallback;
    OnDisconnectCallback _onDisconnectCallback;
    
    std::unordered_map<MessageType, OnReceiveCallback> _onReceivePackets;

    ConnectionId _nextId;
public:
    NetworkServer();
    ~NetworkServer();

    NetworkServer(const NetworkServer&) = delete;
    NetworkServer& operator=(const NetworkServer&) = delete;

    void start(uint16_t port, size_t maxPeers);
    void update();

    void kick(ConnectionId id) noexcept;
    std::string getIp(ConnectionId id) noexcept;

    void forEachPeer(const std::function<void(ConnectionId)>& func) const noexcept;
    size_t peersCount() const noexcept { return _peers.size(); }

    void onConnect(const OnConnectCallback& callback) noexcept { _onConnectCallback = callback; }
    void onDisconnect(const OnDisconnectCallback& callback) noexcept { _onDisconnectCallback = callback; }

    void onReceive(MessageType type, const OnReceiveCallback& callback) noexcept {
        _onReceivePackets[type] = callback;
    }

    void broadcast(MessageType type, const BufferWritter& data, uint8_t channel, bool isReliable) const {
        BufferWritter result;

        result.write(type);
        result.writeBytes(data.data(), data.size());
        
        ENetPacket* packet = enet_packet_create(result.data(), result.size(), isReliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
        enet_host_broadcast(_host, channel, packet);
    }
    void send(ConnectionId id, MessageType type, const BufferWritter& data, uint8_t channel, bool isReliable) const {
        BufferWritter result;

        result.write(type);
        result.writeBytes(data.data(), data.size());
        
        ENetPacket* packet = enet_packet_create(result.data(), result.size(), isReliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
        enet_peer_send(_peers.at(id), channel, packet);
    }
};

#endif
