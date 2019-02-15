#include "stdafx.h"
#include "Scene.h"

//////////////////////////////////////////////////////////////////////////

using namespace CommonLibOgl;
using namespace CommonLibOglTestApp;

//////////////////////////////////////////////////////////////////////////


Scene::Scene(const glm::vec3& backgroundColor, CameraPtr& spCamera, GLuint programId)
    : m_backgroundColor(backgroundColor), m_spCamera(spCamera), m_programId(programId)
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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_MULTISAMPLE);

    glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, 1.0f);

    if (!initializeContents())
    {
        std::wcerr << L"Failed to initialize scene contents\n";
        return 1;
    }

    updateUniforms();

    return true;
}

bool Scene::initializeContents()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Set up the vertex buffer.

    std::vector<GLfloat> vertices = {
        -0.90f, -0.90f, 0.0f,
         0.85f, -0.90f, 0.0f,
        -0.90f,  0.85f, 0.0f };

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

    updateUniforms();

    return true;
}

void Scene::updateUniforms() const
{
    // Our shaders don't use the uniforms.
    // The code is left as a reference for more complex projects.
#if 0
    ATLASSERT(m_programId);

    glUseProgram(m_programId);

    // TODO:
    //     1) comment out the uniforms you don't need.
    //     2) correct the uniform locations if required.
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(m_spCamera->getModelViewProjectionMatrix()));
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(m_spCamera->getProjectionMatrix()));

    glm::mat4 modelView = m_spCamera->getModelViewMatrix();

    // WARNING: we are using the fact that there are no non-uniform scaling. If this will change, use the entire 4x4 matrix.
    glm::mat3 normal = glm::mat3(glm::transpose(glm::inverse(modelView)));
    //glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));

    glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(normal));

    glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(modelView));

    glUseProgram(0);
#endif
}

void Scene::resize(GLfloat aspectRatio)
{
    m_spCamera->resize(aspectRatio);

    updateUniforms();
}

void Scene::render() const
{
    ATLASSERT(m_programId);

    updateUniforms();

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
