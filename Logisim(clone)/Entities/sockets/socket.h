#ifndef SOCKET_H
#define SOCKET_H

#include <functional>

enum class SocketState {
    ERROR,
    UNINITIALIZED,
    LOW,
    HIGH
};

static const std::map<SocketState, glm::vec3> socketStateColorMap = {
    {SocketState::ERROR,         glm::vec3(188.0f / 255, 10.0f / 255, 0.0f / 255)},
    {SocketState::UNINITIALIZED, glm::vec3(37.0f / 255, 17.0f / 255, 255.0f / 255)},
    {SocketState::LOW,           glm::vec3(19.0f / 255, 100.0f / 255, 0.0f / 255)},
    {SocketState::HIGH,          glm::vec3(51.0f / 255, 211.0f / 255, 0.0f / 255)},
};

class Socket {
public:
    Socket(glm::ivec2 position, glm::vec2 absPosition, SocketState state) : m_position{position}, m_absPosition{absPosition}, m_state{state}, m_entityCallback{nullptr} {
        m_color = socketStateColorMap.at(m_state);
    }
    Socket(glm::ivec2 position, glm::vec2 absPosition) : m_position{position}, m_absPosition{absPosition},  m_state{SocketState::UNINITIALIZED}, m_entityCallback{nullptr} {
        m_color = socketStateColorMap.at(m_state);
    }
    Socket() : m_position{glm::ivec2(0, 0)}, m_state{SocketState::UNINITIALIZED}, m_entityCallback{nullptr} {
        m_color = socketStateColorMap.at(m_state);
    }
    ~Socket() {
        
    }
    
    glm::ivec2 GetPosition() const {
        return this->m_position;
    }
    
    glm::vec2 GetAbsPosition() const {
        return this->m_absPosition;
    }
    
    glm::vec3 GetColor() const {
        return this->m_color;
    }
    
    SocketState GetState() const {
        return this->m_state;
    }
    
    void ChangeState(SocketState newState, bool notifyCallback = true) {
        if(m_state != newState) {
            m_state = newState;
            m_color = socketStateColorMap.at(m_state);
            if(m_entityCallback && notifyCallback) (*m_entityCallback)(newState);
        }
    }
    
    void RegisterChangeCallback(std::function<void(SocketState)>* entityCallback) {
        m_entityCallback = entityCallback;
    }
    
private:
    glm::ivec2 m_position;
    glm::vec2 m_absPosition;
    SocketState m_state;
    glm::vec3 m_color;
    std::function<void(SocketState)>* m_entityCallback;
};

#endif
