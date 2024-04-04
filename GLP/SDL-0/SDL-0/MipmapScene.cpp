#include "MipmapScene.h"

#include "Shapes2D.h"

MipmapScene::MipmapScene(std::string nameP):Scene(nameP)
{
    m_name = nameP;
    glGenBuffers(1, &m_vbo);
}

MipmapScene::~MipmapScene()
{
    glDeleteVertexArrays(1, &m_vao);
}

void MipmapScene::LoadShaders()
{
    m_vertexShader.LoadFrom("vertexMove.shader", VERTEX);
    m_fragmentShader.LoadFrom("simpleFragment.shader", FRAGMENT);
}

void MipmapScene::CreateShaderPrograms()
{
    m_shaderProgram.Compose(vector<Shader*>{&m_vertexShader,&m_fragmentShader});
}

void MipmapScene::VerticeInformationSlicer()
{
}


void MipmapScene::SetupScene()
{
    Shape2D::CreateRectangle(m_vertices,Vector2(-0.5f,-0.75f), Vector2(0.5f,0.25f));
    Shape2D::CreateRectangle(m_vertices,Vector2(-0.5f,-0.75f), Vector2(0.5f,0.25f));
    Shape2D::CreateRectangle(m_vertices,Vector2(-0.5f,-0.75f), Vector2(0.5f,0.25f));
    Shape2D::CreateRectangle(m_vertices,Vector2(-0.5f,-0.75f), Vector2(0.5f,0.25f));

    LoadShaders();
    CreateShaderPrograms();
    VerticeInformationSlicer();
    
}

void MipmapScene::UpdateScene()
{
    
}
