#pragma once


namespace CommonLibOglTestApp
{
    class Scene
        : public CommonLibOgl::OglScene
    {
    public:
        Scene();

        virtual ~Scene();

        // Initialize the derived scene.
        virtual bool initialize() override;

        // Update OpenGL uniforms such as ModelView matrix (can be empty).
        virtual void updateUniforms(const std::unique_ptr<CommonLibOgl::Camera>& spCamera) const override;

        // Render the derived scene.
        virtual void render() const override;

    private:
        // Data for a triangle.

        GLuint m_vao = {};
        GLuint m_vbo = {};

        GLuint m_index = {};          // index buffer
        GLsizei m_indexCount = {};    // number of indices
    };
}
