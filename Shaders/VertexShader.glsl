
attribute vec4 a_Position;	        // in: Posición de cada vértice
attribute vec3 a_Normal;	        // in: Normal de cada vértice
attribute vec2 a_UV;

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat4 u_VMatrix;             // in: Matriz View (cámara)
uniform vec4 u_Color;		        // in: Color del objeto
uniform int  u_Luz0;                // in: Indica si la luz 0 está encedida
uniform int  u_Luz1;                // in: Indica si la luz 1 está encedida
uniform int  u_Luz2;                // in: Indica si la luz 2 está encedida

uniform float  u_Luz0Intensity;                // in: Indica si la luz 0 está encedida
uniform float  u_Luz1Intensity;                // in: Indica si la luz 1 está encedida
uniform float  u_Luz2Intensity;                // in: Indica si la luz 2 está encedida

uniform vec4 u_Luz0Pos;
uniform vec4 u_Luz1Pos;
uniform vec4 u_Luz2Pos;

uniform sampler2D u_TextureUnit;

varying vec2 v_UV;
varying sampler2D v_TextureUnit;
varying vec4 v_Color;		        // out: Color al fragment shader

void main()
{
    vec4 LightPos = u_VMatrix * u_Luz0Pos;		// Posición de la luz [fija]
    vec4 LightPos1 = u_VMatrix * u_Luz1Pos;		// Posición de la luz [fija]
    vec4 LightPos2 = u_VMatrix * u_Luz2Pos;		// Posición de la luz [fija]
    vec3 P = vec3(u_MVMatrix * a_Position);	            // Posición del vértice
	vec3 N = vec3(u_MVMatrix * vec4(a_Normal, 0.0));    // Normal del vértice

	float d = length(LightPos.xyz - P);			        // distancia de la luz
	vec3  L = normalize(LightPos.xyz - P);			    // Vector Luz

	float d1 = length(LightPos1.xyz - P);			        // distancia de la luz
	vec3  L1 = normalize(LightPos1.xyz - P);			    // Vector Luz

	float d2 = length(LightPos2.xyz - P);			        // distancia de la luz
	vec3  L2 = normalize(LightPos2.xyz - P);			    // Vector Luz

    vec3 V = normalize(-P.xyz);

    // Calculate R by reflecting -L around the plane defined by N
    vec3 R = reflect(-L, N);
    vec3 R1 = reflect(-L1, N);
    vec3 R2 = reflect(-L2, N);
    int n = 32;
	float ambient = 0.15;                               // (15% de int. ambiente)
	float diffuse = 0.0;
	float diffuseTotal = 0.0;
	float specular = 0.0;
	float specularTotal = 0.0;

	if (u_Luz0>0) {                                     // Si la luz 0 está encendida se calcula la intesidad difusa de L
        diffuse = max(dot(N, L), 0.0);		            // Cálculo de la int. difusa
        specularTotal +=pow(max(0.0, dot(R, V)), n);
        // Cálculo de la atenuación
        float attenuation = (u_Luz0Intensity * 100.0)/(0.25+(0.01*d)+(0.003*d*d));
        diffuseTotal = diffuse*attenuation;
	}
	if (u_Luz1>0) {                                     // Si la luz 0 está encendida se calcula la intesidad difusa de L
        diffuse = max(dot(N, L1), 0.0);		            // Cálculo de la int. difusa
        specularTotal +=pow(max(0.0, dot(R1, V)), n);
        // Cálculo de la atenuación
        float attenuation = (u_Luz1Intensity * 100.0)/(0.25+(0.01*d1)+(0.003*d1*d1));
        diffuseTotal += diffuse*attenuation;
	}
	if (u_Luz2>0) {                                     // Si la luz 0 está encendida se calcula la intesidad difusa de L
        diffuse = max(dot(N, L2), 0.0);		            // Cálculo de la int. difusa
        specularTotal +=pow(max(0.0, dot(R2, V)), n);
        // Cálculo de la atenuación
        float attenuation = (u_Luz2Intensity * 100.0)/(0.25+(0.01*d2)+(0.003*d2*d2));
        diffuseTotal += diffuse*attenuation;
	}

	//v_Color = u_Color * (ambient + diffuse + specular);
	v_UV = a_UV;
	v_TextureUnit = u_TextureUnit;
	v_Color =  u_Color * (ambient + diffuseTotal) + vec4(1.0, 1.0, 1.0, 1.0) * specularTotal;
	gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
}
