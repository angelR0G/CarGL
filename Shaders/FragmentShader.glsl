
precision mediump float;	// Precisi�n media, en algunas gr�ficas no se soporta (depende de la versi�n de GLSL)

varying vec4 v_Color;		// in: color del vertex shader
varying vec2 v_UV;
varying sampler2D v_TextureUnit;
void main()
{
            vec4 t_Color = texture2D(v_TextureUnit, v_UV);
    		gl_FragColor = v_Color * t_Color;
}
