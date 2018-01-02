#version 330 core

in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{


	// GLSL built in texture function

	//FragColor = texture(texture1, TexCoord);
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	FragColor = vec4(1.0);
}