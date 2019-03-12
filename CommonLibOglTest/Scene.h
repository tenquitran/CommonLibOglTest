#pragma once


namespace CommonLibOglTestApp
{
    class Scene
        : public CommonLibOgl::IScene
    {
    public:
        Scene(const glm::vec3& backgroundColor,
            CommonLibOgl::CameraPtr& spCamera,
            GLuint programId);

        virtual ~Scene();

        virtual bool initialize() override;

        virtual void resize(GLfloat aspectRatio) override;

        // Render the derived scene.
        virtual void render() const override;

        //////////////////////////////////////////////////////////////////////////
        // Camera control.
        //////////////////////////////////////////////////////////////////////////

        virtual void translateCamera(const glm::vec3& diff) override;

        virtual void rotateCamera(const glm::vec3& degrees) override;

        virtual void scaleCamera(GLfloat amount) override;

        GLfloat getCameraScale() const;

    private:
        // Initialize scene contents (usually something that will be rendered - e.g. a cube).
        bool initializeContents();

        // Update OpenGL uniforms such as ModelView matrix.
        void updateUniforms() const;

    private:
        glm::vec3 m_backgroundColor;

        CommonLibOgl::CameraPtr m_spCamera;

        // GLSL program ID.
        const GLuint m_programId = {};

        //////////////////////////////////////////////////////////////////////////

        // Scene contents.

        GLuint m_vao = {};
        GLuint m_vbo = {};

        GLuint m_index = {};          // index buffer
        GLsizei m_indexCount = {};    // number of indices
    };
}
