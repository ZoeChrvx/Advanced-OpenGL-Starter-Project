#pragma once
#include "Scene.h"

class MipmapScene : public Scene
{
protected:
    Shader m_vertexShader, m_fragmentShader;
    ShaderProgram m_shaderProgram;
    virtual void LoadShaders();
    virtual void CreateShaderPrograms();
    virtual void VerticeInformationSlicer();
    
public:
    MipmapScene(std::string nameP = "Demo");

    ~MipmapScene();

    virtual void SetupScene();
    virtual void UpdateScene();
    
};
