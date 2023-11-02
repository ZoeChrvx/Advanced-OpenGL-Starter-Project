#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 1f, 0.8f, 1.0f);
}

/*
float timeValue = (float)SDL_GetTicks() / 1000;
		float redColor = (sin(timeValue) / 2.0f) + 0.5f;
		float greenColor = (sin(timeValue) + 2.0f) + 0.5f;
		float blueColor = (sin(timeValue) + 4.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

*/

