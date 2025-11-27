#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Player.h"

class SceneManager
{
public:
    static void Init();
    static void AddObject(std::shared_ptr<GameObject> obj);
	static void LoadStaticObjects(const std::string& path);
	static void LoadInteractableObjects(const std::string& path);

    static void Update(int time);
    static void Draw();
    static void Reshape(int w, int h);
    
    static Camera& GetCamera() { return s_camera; }
    static std::vector<std::shared_ptr<GameObject>>& GetObjects() { return s_objects; }
    static Shader& GetMainShader() { return s_mainShader; }
private:
    static std::vector<std::shared_ptr<GameObject>> s_objects;
    static Camera s_camera;

    static GameObject* s_selected;
    static Shader s_mainShader;
    static Player* s_player;
};
