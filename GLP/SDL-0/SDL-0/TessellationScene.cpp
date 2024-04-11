#include "TessellationScene.h"

using namespace std;

const bool ENABLE_GEOMETRY_SHADER = false;

TessellationScene::TessellationScene() {

}

//Load the correct shaders from your files
void TessellationScene::LoadShaders() {
	m_vertexShader.LoadFrom("TessellationVertexRect.vert", VERTEX);
	m_fragmentShader.LoadFrom("tessellationFragment.shader", FRAGMENT);
	m_tessControlShader.LoadFrom("TessellationControlRect.tesc", TESSELLATION_CONTROL);
	m_tessEvalShader.LoadFrom("TessellationEvalRect.tese", TESSELLATION_EVALUATION);
	if(ENABLE_GEOMETRY_SHADER)m_geometryShader.LoadFrom("tessellationGeometry.shader", GEOMETRY);

	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TessellationScene::CreateShaderPrograms() {
	m_shaderProgram.Compose(
		vector<Shader*>{
		& m_vertexShader, 
		& m_fragmentShader,
		& m_tessControlShader,
		& m_tessEvalShader,
		& m_geometryShader
	});
}

void TessellationScene::VerticeInformationSlicer() {
	//No slicing necessary, everything is handled in shaders
}

void TessellationScene::SetupScene()
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

void TessellationScene::UpdateScene()
{
	float timeValue = (float)SDL_GetTicks() / 1000;
	float sinusoidValue = (sin(timeValue));
	m_shaderProgram.Use();
	m_shaderProgram.setFloat("ratio02", 5*(sinusoidValue + 2));
	m_shaderProgram.setFloat("ratio01", 2*(sinusoidValue + 1));
	glPointSize(5.0f);
	glDrawArrays(GL_PATCHES, 0, 4);
	

}
