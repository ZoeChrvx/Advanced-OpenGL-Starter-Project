#include "TextureScene.h"
#include <iostream>
#include "Shapes2D.h"

void TextureScene::LoadShaders()
{
	m_vertexShader.LoadFrom("textureVertex.shader", VERTEX);
	m_animVertexShader.LoadFrom("textureAnimVertex.shader", VERTEX);
	m_fragmentShader.LoadFrom("textureFragment.shader", FRAGMENT);
}

void TextureScene::CreateShaderPrograms()
{
	m_animShaderProgram.Compose(std::vector<Shader*>{&m_animVertexShader, &m_fragmentShader});
	m_shaderProgram.Compose(std::vector<Shader*>{&m_vertexShader, &m_fragmentShader});
	m_shaderProgram.Use();
}

void TextureScene::VerticeInformationSlicer()
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

void TextureScene::SetupScene()
{
	Vector2 tiling = Vector2(1.0,1.0);
	std::cout<<"Mip Map : "<<(mipmap?"Active":"Inactive")<<std::endl;
	std::cout<<"Press M to active or deactivate mip maps"<<endl;

	m_vertices = {
		//Position		    Texture Coordinates
		0.0, 1.0,           tiling.x, tiling.y,       //A
		0.0, 0.0,           tiling.x, 0.0,           //B
		-1.0, 1.0,          0.0, tiling.y,           //C
		-1.0, 0.0,          0.0, 0.0,               //D

		0.5, 1.0,           tiling.x, tiling.y,       //A
	    0.5, 0.5,           tiling.x, 0.0,           //B
	    0.0, 1.0,           0.0, tiling.y,           //C
	    0.0, 0.5,           0.0, 0.0,               //D

	    0.25, 0.5,          tiling.x, tiling.y,       //A
	    0.25, 0.25,         tiling.x, 0.0,           //B
	    0.0, 0.5,           0.0, tiling.y,           //C
	    0.0, 0.25,          0.0, 0.0,               //D

	    0.125, 0.25,        tiling.x, tiling.y,       //A
	    0.125, 0.125,       tiling.x, 0.0,           //B
	    0.0, 0.25,          0.0, tiling.y,           //C
	    0.0, 0.125,         0.0, 0.0,               //D

	    0.06, 0.125,        tiling.x, tiling.y,       //A
	    0.06, 0.06,         tiling.x, 0.0,           //B
	    0.0, 0.125,         0.0, tiling.y,           //C
	    0.0, 0.06,          0.0, 0.0,               //D

	    0.5, 0.0,           tiling.x, tiling.y,       //A
	    0.5, -1.0,          tiling.x, 0.0,           //B
	    -0.5, 0.0,          0.0, tiling.y,           //C
	    -0.5, -1.0,         0.0, 0.0,               //D
	};

	LoadShaders();
	CreateShaderPrograms();

	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glDepthFunc(GL_LESS);

	VerticeInformationSlicer();

	m_WallTexture = Texture2D();
	m_WallTexture.load("Textures/wall.png");
	m_WallTexture.generate();
	m_WallTexture.use();
	glGenerateTextureMipmap(m_WallTexture.id);

	m_GrassTexture = Texture2D();
	m_GrassTexture.load("Textures/grass.png");
	m_GrassTexture.generate();
	m_GrassTexture.use();
	glGenerateTextureMipmap(m_GrassTexture.id);

	m_GroundTexture = Texture2D();
	m_GroundTexture.load("Textures/ground_01.png");
	m_GroundTexture.generate();
	m_GroundTexture.use();
	glGenerateTextureMipmap(m_GroundTexture.id);
}

void ActivateMipMap(bool mipmap = true)
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
}

void TextureScene::UpdateScene()
{
	 m_shaderProgram.Use();
	 m_WallTexture.use();

	 glBindVertexArray(m_vao);
	 ActivateMipMap(mipmap);
	 glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
	 glDrawArrays(GL_TRIANGLE_STRIP, 4,4);
	 glDrawArrays(GL_TRIANGLE_STRIP, 8,4);
	 glDrawArrays(GL_TRIANGLE_STRIP, 12,4);
	 glDrawArrays(GL_TRIANGLE_STRIP, 16,4);

	m_animShaderProgram.Use();
	m_GrassTexture.use();
	glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
	glDrawArrays(GL_TRIANGLE_STRIP, 4,4);
	float timeValue = (float)SDL_GetTicks() / 1000;
	float sinusoidValue = (sin(timeValue)/2.0 ) +0.5f;

	m_animShaderProgram.setFloat("scale", sinusoidValue);
	ActivateMipMap(mipmap);

	glDrawArrays(GL_TRIANGLE_STRIP, 120,4);
}

void TextureScene::HandleInputs(SDL_Event& e)
{
	switch(e.type)
	{
	case SDL_KEYDOWN:
		if(e.key.keysym.sym == SDLK_m)
		{
		mipmap = !mipmap;
		std::cout<<"Mip Map : "<<(mipmap?"Active":"Inactive")<< '\n';
		}
	}
}




