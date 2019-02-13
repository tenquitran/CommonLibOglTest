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
        virtual bool initializeDerived() override;

        // Update OpenGL uniforms such as ModelView matrix (can be empty).
        virtual void updateUniformsDerived(const std::unique_ptr<CommonLibOgl::Camera>& spCamera) const override;

        // Render the derived scene.
        virtual void renderDerived() const override;
    };
}
