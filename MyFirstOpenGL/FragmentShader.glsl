#version 440 core

uniform vec2 windowSize;
uniform float time;
out vec4 fragColor;

void main() 
{
	float MitadAltura = windowSize.y / 2.0;
    float TercioAnchura = windowSize.x * 0.66;

	if(gl_FragCoord.y > MitadAltura && gl_FragCoord.x < TercioAnchura)
		fragColor = vec4(1.0, 1.0, 0.0, 1.0);
	else if(gl_FragCoord.y < MitadAltura && gl_FragCoord.x < TercioAnchura)
		fragColor = vec4(1.0, 0.5, 0.0, 1.0);

	int iColorIndex = int(time / 2.0) % 3;

	if(iColorIndex == 0 && gl_FragCoord.x > TercioAnchura)
		fragColor = vec4(1.0, 0.0, 0.0, 1.0);
	else if(iColorIndex == 1 && gl_FragCoord.x > TercioAnchura)
		fragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else if (iColorIndex == 2 && gl_FragCoord.x > TercioAnchura)
		fragColor = vec4(0.0, 0.0, 1.0, 1.0);
}
