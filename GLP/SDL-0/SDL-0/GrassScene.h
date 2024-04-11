#pragma once
#include "Scene.h"
#include "Texture.h"

class GrassScene: public Scene
{
private:
    Shader m_vertexShader, m_fragmentShader;
    ShaderProgram m_shaderProgram;
    Texture2D m_GrassTexture;

    
    void LoadShaders() override;
    void CreateShaderPrograms() override;
    void VerticeInformationSlicer() override;

public:
    GrassScene() : Scene("Texture Scene") {}
    ~GrassScene(){}
    void SetupScene() override;
    void UpdateScene() override;
};