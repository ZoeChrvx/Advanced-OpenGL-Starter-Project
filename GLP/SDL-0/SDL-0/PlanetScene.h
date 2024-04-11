#pragma once
#include "BaseScene.h"

class PlanetScene : public Scene
{
private:
    Shader m_vertexShader, m_fragmentShader, m_tessControlShader, m_tessEvalShader, m_geometryShader;
    ShaderProgram m_Program;
    Matrix4  mv, rotation, projection;

protected:
    void LoadShaders() override;
    void CreateShaderPrograms() override;
    void VerticeInformationSlicer() override;

public:
    PlanetScene();
    ~PlanetScene();
    void SetupScene() override;
    void UpdateScene() override;
};
