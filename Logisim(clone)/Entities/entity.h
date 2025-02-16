#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "../Shaders/shader.h"
#include "../Textures/texture.h"
#include "../Logger/logger.h"

#include <iostream>

class Entity {
public:
    
    virtual ~Entity() { }
    virtual Entity* GetInstance() const = 0;
    
    virtual void Draw(const glm::mat4& view, const glm::mat4& projection) const = 0;
    
    glm::vec3 GetPosition() const {
        return m_position;
    }
    
    GLuint GetTexID() const {
        return m_texture.ID;
    }
    
protected:
    Shader m_shader;
    Texture m_texture;
    glm::vec3 m_position;
    
    // Protected constructor for the abstract class
    // --------------------------------------------
    Entity(Shader& shader, Texture& texture, glm::vec3 position) : m_shader{shader}, m_texture{texture}, m_position{position} {}
};

#endif
