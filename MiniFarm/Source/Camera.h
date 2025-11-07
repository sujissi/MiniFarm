#pragma once

class Camera {
public:
    Camera();

    void Init();
    void MoveForward(float amount);
    void MoveRight(float amount);
    void RotateYaw(float deg);

    glm::mat4 GetView() const;
    glm::mat4 GetProj(float aspect) const;

public:
    glm::vec3 eye;
    glm::vec3 at;
    glm::vec3 up;
};
