#pragma once

namespace Toy2D {
    class Camera {
    public:
        Camera(const Matrix& projection = Matrix::Identity) :
            m_projection(projection) {}

        virtual ~Camera() = default;

        const Matrix& getProjection() const { return m_projection; }

    protected:
        Matrix m_projection;
    };
} // namespace Toy2D