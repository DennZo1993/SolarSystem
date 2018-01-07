#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


TCamera::TCamera(size_t resX, size_t resY)
    : ResolutionX(resX)
    , ResolutionY(resY)
    , Aspect(static_cast<float>(resX) / static_cast<float>(resY))
    , FwDirection(0.0f, 0.0f, -1.0f)
    , UpDirection(0.0f, 1.0f, 0.0f)
    , ZNearPlane(100.0f)
    , ZFarPlane(0.1f)
    , FOV(45.0f)
{
    UpdateProjectionMatrix();
    UpdateViewMatrix();
}


void TCamera::MoveTo(const glm::vec3& position)
{
    Position = position;
    UpdateViewMatrix();
}


void TCamera::SetupQuaternion()
{
    glm::quat qPitch = glm::angleAxis(0.0f, glm::vec3(1, 0, 0));
    glm::quat qYaw   = glm::angleAxis(0.0f, glm::vec3(0, 1, 0));
    glm::quat qRoll  = glm::angleAxis(0.0f, glm::vec3(0, 0, 1));

    CameraQuat = glm::normalize(qPitch * qYaw * qRoll);
}


void TCamera::UpdateProjectionMatrix()
{
    ProjectionMatrix = glm::perspective(FOV, Aspect, ZNearPlane, ZFarPlane);
}


void TCamera::UpdateViewMatrix()
{
    ViewMatrix = glm::lookAt(Position, Position + FwDirection, UpDirection);
}


glm::mat4 TCamera::GetViewMatrix() const
{
    // return glm::mat4(1.0f);
    return ViewMatrix;
}


glm::mat4 TCamera::GetProjectionMatrix() const
{
    return ProjectionMatrix;
}


glm::mat4 TCamera::GetViewProjectionMatrix() const
{
    return ProjectionMatrix * ViewMatrix;
}