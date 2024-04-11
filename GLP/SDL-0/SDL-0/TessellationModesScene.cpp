#include "TessellationModesScene.h"

using namespace std;

TessellationModesScene::TessellationModesScene()
{
}

//Load the correct shaders from your files
void TessellationModesScene::LoadShaders() {
	m_vertexShader.LoadFrom("TessellationVertexRect.vert", VERTEX);
	m_fragmentShader.LoadFrom("tessellationFragment.shader", FRAGMENT);
	m_tessControlShader.LoadFrom("TessellationControlRect.tesc", TESSELLATION_CONTROL);
	m_tessEvalShader.LoadFrom("TessellationEvalRect.tese", TESSELLATION_EVALUATION);

	glPatchParameteri(GL_PATCH_VERTICES, 4);
}

void TessellationModesScene::CreateShaderPrograms() {
	m_shaderProgram.Compose(
		vector<Shader*>{
		&m_vertexShader,
			& m_fragmentShader,
			& m_tessControlShader,
			& m_tessEvalShader,
			& m_geometryShader
	});
}

void TessellationModesScene::SetupScene()
{
	LoadShaders();
	CreateShaderPrograms();

	//Create one ID to be given at object generation and store it in m_vao via reference
	glGenVertexArrays(1, &m_vao);
	//Binding the VAO 
	//   /!\ If you have multiple VAOs, you should bind the correct VAO after each change
	glBindVertexArray(m_vao);

	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	//VerticeInformationSlicer();
}

void TessellationModesScene::UpdateScene()
{
	m_shaderProgram.Use();

	glPointSize(5.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPatchParameteri(GL_PATCHES, 4);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
