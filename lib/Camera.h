#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "CameraOptions.h"


class TCamera {
public:
    TCamera(size_t resX, size_t resY);

public:
    // Modifications.
    void MoveTo(const glm::vec3& position);

public:
    // Getters.
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    glm::mat4 GetViewProjectionMatrix() const;

protected:
    void UpdateProjectionMatrix();
    void UpdateViewMatrix();

    void SetupQuaternion();

private:
    const size_t ResolutionX;
    const size_t ResolutionY;
    const float Aspect;

    float ZNearPlane;
    float ZFarPlane;

    float FOV;

    glm::vec3 Position;

    glm::vec3 FwDirection;
    glm::vec3 UpDirection;
    glm::vec3 WorldUp;

    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    glm::quat CameraQuat;
};