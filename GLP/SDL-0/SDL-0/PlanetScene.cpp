#include "PlanetScene.h"


PlanetScene::PlanetScene()
{
}

PlanetScene::~PlanetScene()
{
}

void PlanetScene::LoadShaders()
{
    m_vertexShader.LoadFrom("planet.vert", VERTEX);
    m_geometryShader.LoadFrom("planet.geom", GEOMETRY);
    m_tessControlShader.LoadFrom("planet.tesc", TESSELLATION_CONTROL);
    m_tessEvalShader.LoadFrom("planet.tese", TESSELLATION_EVALUATION);
    m_fragmentShader.LoadFrom("planet.frag", FRAGMENT);

    glPatchParameteri(GL_PATCH_VERTICES,3);
}

void PlanetScene::CreateShaderPrograms()
{
}

void PlanetScene::VerticeInformationSlicer()
{
}


void PlanetScene::SetupScene()
{
}

void PlanetScene::UpdateScene()
{
}
