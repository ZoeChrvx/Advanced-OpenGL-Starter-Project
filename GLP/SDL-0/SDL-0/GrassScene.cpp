#include "GrassScene.h"
#include <iostream>
#include "Shapes2D.h"

void GrassScene::LoadShaders()
{
	m_vertexShader.LoadFrom("Blades.shader", VERTEX);
	m_fragmentShader.LoadFrom("textureFragment.shader", FRAGMENT);
}

void GrassScene::CreateShaderPrograms()
{
	m_shaderProgram.Compose(std::vector<Shader*>{&m_vertexShader, &m_fragmentShader});
	m_shaderProgram.Use();
}

void GrassScene::VerticeInformationSlicer()
{
	float* verticeArray = new float [m_vertices.size()]();
	std::copy(m_vertices.begin(), m_vertices.end(), verticeArray);

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), verticeArray, GL_STATIC_DRAW);

	glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

	delete [] verticeArray;
}

void GrassScene::SetupScene()
{
	Vector2 tiling = Vector2(1.0,1.0);

	m_vertices = {
		//Position		    Texture Coordinates
		0.5, -0.5,           tiling.x, tiling.y,       //A
		0.5, 0.5,           tiling.x, 0.0,           //B
		-0.5, -0.5,          0.0, tiling.y,           //C
		-0.5, 0.5,          0.0, 0.0,               //D
	};

	LoadShaders();
	CreateShaderPrograms();

	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glDepthFunc(GL_LESS);

	VerticeInformationSlicer();

	m_GrassTexture = Texture2D();
	m_GrassTexture.load("Textures/grass.png");
	m_GrassTexture.generate();
	m_GrassTexture.use();
	glGenerateTextureMipmap(m_GrassTexture.id);
}

/*void ActivateMipMap(bool mipmap = true)
{
	if(mipmap)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}*/

void GrassScene::UpdateScene()
{
	m_shaderProgram.Use();
	m_GrassTexture.use();

	glBindVertexArray(m_vao);
	//ActivateMipMap(mipmap);
	glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
	glDrawArrays(GL_TRIANGLE_STRIP, 4,4);
	glDrawArrays(GL_TRIANGLE_STRIP, 8,4);
	glDrawArrays(GL_TRIANGLE_STRIP, 12,4);
	glDrawArrays(GL_TRIANGLE_STRIP, 16,4);

	m_shaderProgram.Use();
	float timeValue = (float)SDL_GetTicks() / 1000;
	float sinusoidValue = (sin(timeValue)/2.0 ) + 0.5f;
	//ActivateMipMap(mipmap);

	glDrawArrays(GL_TRIANGLE_STRIP, 20,4);
}




