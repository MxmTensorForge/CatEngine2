#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <enet/enet.h>
#include <functional>
#include <unordered_map>
#include <cstdint>
#include <string>

#include "BufferReader.h"
#include "BufferWritter.h"

using ConnectionId = uint32_t;
using MessageType = uint32_t;

using OnConnectCallback = std::function<void()>;
using OnDisconnectCallback = std::function<void()>;
using OnReceiveCallback = std::function<void(BufferReader&)>;

class NetworkClient final
{
private:
    ENetHost* _host = nullptr;
    ENetPeer* _peer = nullptr;

    ConnectionId _id;
    bool _isConnected;

    OnConnectCallback _onConnectCallback;
    OnDisconnectCallback _onDisconnectCallback;
    
    std::unordered_map<MessageType, OnReceiveCallback> _onReceivePackets;
public:
    NetworkClient();
    ~NetworkClient();

    NetworkClient(const NetworkClient&) = delete;
    NetworkClient& operator=(const NetworkClient&) = delete;

    void connect(const std::string& ip, uint16_t port);
    void disconnect();
    void update();

    void onConnect(const OnConnectCallback& callback) noexcept { _onConnectCallback = callback; }
    void onDisconnect(const OnDisconnectCallback& callback) noexcept { _onDisconnectCallback = callback; }

    void onReceive(MessageType type, const OnReceiveCallback& callback) noexcept {
        _onReceivePackets[type] = callback;
    }

    void send(MessageType type, const BufferWritter& data, uint8_t channel, bool isReliable) const {
        BufferWritter result;

        result.write(type);
        result.writeBytes(data.data(), data.size());
        
        ENetPacket* packet = enet_packet_create(result.data(), result.size(), isReliable ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
        enet_peer_send(_peer, channel, packet);
    }

    bool isConnected() const noexcept { return _isConnected; }
    ConnectionId getId() const noexcept { return _id; }
};

#endif
