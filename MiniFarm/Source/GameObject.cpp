#include "PCH.H"
#include "GameObject.h"
#include "Shader.h"

void GameObject::Draw()
{
    if (!m_model) return;
    glm::mat4 modelMat =
        Translate(m_pos)
        * Rotate(m_rot.y, { 0,1,0 })
        * Rotate(m_rot.x, { 1,0,0 })
        * Rotate(m_rot.z, { 0,0,1 })
        * Scale(m_scale);

    Shader::SetModel(modelMat);
    m_model->Draw();
}
