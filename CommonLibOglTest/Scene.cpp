#include "stdafx.h"
#include "Scene.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOglTestApp;

//////////////////////////////////////////////////////////////////////////


Scene::Scene()
{
}

Scene::~Scene()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    if (0 != m_index)
    {
        glDeleteBuffers(1, &m_index);
    }

    if (0 != m_vbo)
    {
        glDeleteBuffers(1, &m_vbo);
    }

    if (0 != m_vao)
    {
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &m_vao);
    }
}

bool Scene::initialize()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Set up the vertex buffer.

    std::vector<GLfloat> vertices = {
        -0.90f, -0.90f, 0.0f,
         0.85f, -0.90f, 0.0f,
        -0.90f,  0.85f, 0.0f
    };

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    // Fill in the vertex position attribute.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);

    // Set up the index buffer.

    std::vector<GLuint> indices = {0, 1, 2};

    m_indexCount = indices.size();

    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Our shaders don't use the function yet.
    // Eventually create something more complex and uncomment this function.
#if 0
    updateUniforms(spCamera);
#endif

    return true;
}

void Scene::updateUniforms(const std::unique_ptr<CommonLibOgl::Camera>& spCamera) const
{
    // Our shaders don't use the function yet.
    // Eventually create something more complex and uncomment this function.
#if 0
    ATLASSERT(m_programId);

    glUseProgram(m_programId);

    glm::mat4 proj  = spCamera->getProjectionMatrix();
    glm::mat4 view  = spCamera->getViewMatrix();
    glm::mat4 model = spCamera->getModelMatrix();

    // Apply translation.
    model *= glm::translate(glm::mat4(1.0f), m_translation);

    // Apply rotation.
    model *= glm::rotate(glm::mat4(1.0f), glm::radians(m_rotationDegrees.x), glm::vec3(1.0f, 0.0f, 0.0));    // X axis
    model *= glm::rotate(glm::mat4(1.0f), glm::radians(m_rotationDegrees.y), glm::vec3(0.0f, 1.0f, 0.0));    // Y axis
    model *= glm::rotate(glm::mat4(1.0f), glm::radians(m_rotationDegrees.z), glm::vec3(0.0f, 0.0f, 1.0));    // Z axis

    // Apply scaling.
    model *= glm::scale(glm::mat4(1.0f), glm::vec3(m_scaleFactor));

    glm::mat4 mv = view * model;

    glm::mat4 mvp = proj * view * model;

    glUseProgram(m_programId);

    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvp));

    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(mv));

    glm::mat3 normal = glm::mat3(glm::transpose(glm::inverse(mv)));
    //glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));

    glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(normal));

    glUseProgram(0);
#endif
}

void Scene::render() const
{
    ATLASSERT(m_programId);

    // Our shaders don't use the function yet.
    // Eventually create something more complex and uncomment this function.
#if 0
    updateUniforms(spCamera);
#endif

    glUseProgram(m_programId);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);

    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}
