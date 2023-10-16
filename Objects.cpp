
/****************************************************************************************

    CarGL (Objects.cpp)

    Grado en Ingeniería Multimedia.
    Práctica de Gráficos por Computador.
    OpenGL con Shaders.
  ---------------------------------------------------------------------------------------

    2012 - 2020 (C) Juan Antonio Puchol García (puchol@dccia.ua.es)


*****************************************************************************************/

#include "Objects.h"
#include <GL/glui.h>
#include <string>

#include "load3ds.c"
#include "loadjpeg.c"

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light0_position_c[4] = {-100.0f, 100.0f, 50.0f, 1.0f };

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat light2_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light2_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light2_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light2_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -9.0 };

float coloresc_c[3][4] = { {0.5, 0.5, 0.5, 1.0}, {0.5, 0.5, 0.5, 1.0}, {0.2, 0.2, 0.2, 1.0}}; // Color del coche
//float coloresc_c[2][4] = { {1.0, 0.878, 0.141, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Color del coche
float coloresr_c[2][4] = { {0.3, 0.3, 0.3, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de la carretera
float coloresCalzada_c[1][4] = { {0.549, 0.533, 0.388, 1.0} };
float coloresFarolas_c[1][4] = { {0.7, 0.7, 0.7, 1.0} };
float coloresEdifiocioM_c[1][4] = { {0.352, 0.427, 0.486, 0.7} };
float coloresEdifiocioG_c[2][4] = { {0.7, 0.7, 0.7, 1.0}, {0.5, 0.5, 0.5, 1.0} };
float coloresEstacionTren_c[1][4] = { {0.015, 0.466, 0.823, 1.0} };
float coloresViaTren_c[2][4] = { {0.172, 0.149, 0.129, 1.0}, {0.2, 0.2, 0.2, 1.0} };
float coloresTren_c[2][4] = {{0.941, 0.980, 0.939, 1.0}};
float coloresMaquinasExp[2][4] = {{0.1, 0.1, 0.1, 1.0}};
float coloresTaburetes_c[1][4] = {{0.9, 0.1, 0.1, 1.0}};
float coloresRestaurante_c[3][4] = {{0.4, 0.4, 0.46, 1.0}, {0.6, 0.4, 0.0, 1.0}, {0.85, 0.85, 0.85, 1.0}};
float coloresEdifioViejo[2][4] = {{0.713, 0.747, 0.747, 1.0}, {0.7, 0.7, 0.7, 1.0}};
float coloresTienda[5][4] = {{0.55, 0.55, 0.55, 1.0}, {0.639, 0.368, 0.0, 1.0}, {0.660, 0.694, 0.6, 1.0}, {0.0, 0.823, 0.960, 1.0}, {0.494, 0.235, 0.086, 1.0}};
float coloresCuerdas[1][4] = { { 0.682, 0.611, 0.560, 1.0} };
float coloresPapeleras[1][4] = { { 0.482, 0.541, 0.415, 1.0} };
float coloresMarcador[1][4] = { { 0.411, 0.007, 0.086, 0.7} };
//************************************************************** Variables de clase

TEscena escena;
TGui    gui;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int t)
{

    ID   = DL;
    tipo = t;
    sx = sy = sz = 1;
    rx = ry = rz = 0;
    tx =  0.0;
    ty =  0.0;
    tz =  0.0;
	switch (tipo) {
		case CARRETERA_ID: {  // Creación de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/carretera.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/carreteraLineas.3ds", &num_vertices1);
            break;
		}
		case CALZADA_ID: {  // Creación de las calzadas

            memcpy(colores, coloresCalzada_c, 4*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/calzada.3ds", &num_vertices0);

            break;
		}
		case FAROLAS_ID: {  // Creación de las farolas

            memcpy(colores, coloresFarolas_c, 4*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/farolas.3ds", &num_vertices0);

            break;
		}
		case EDIFICIOM_ID: {  // Creación de las farolas

            memcpy(colores, coloresEdifiocioM_c, 4*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/edificios2.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/edificios21.3ds", &num_vertices1);
            modelo2 = Load3DS("../../Modelos/ventanas2.3ds", &num_vertices2);
            modelo3 = Load3DS("../../Modelos/ventanas21.3ds", &num_vertices3);
            break;
		}
		case EDIFICIOG_ID: {  // Creación de las farolas

            memcpy(colores, coloresEdifiocioG_c, 8*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/edificiosG.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/edificiosGTuberias.3ds", &num_vertices1);
            break;
		}
		case ESTACION_ID: {  // Creación de las farolas

            memcpy(colores, coloresEstacionTren_c, 4*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/estacionTren.3ds", &num_vertices0);

            break;
		}
		case VIA_ID: {  // Creación de la via y los soportes

            memcpy(colores, coloresViaTren_c, 8*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/ViaTren.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/ViaTrenSoporte.3ds", &num_vertices1);
            break;
		}
		case TREN_ID: {  // Creación de las farolas

            memcpy(colores, coloresTren_c, 4*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Tren.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/TrenRuedas.3ds", &num_vertices1);

            break;
		}
		case MAQUINAEXP_ID: {  // Creación de las farolas

            memcpy(colores, coloresMaquinasExp, 4*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/maquinasExp.3ds", &num_vertices0);

            break;
		}
		case TABURETES_ID: {  // Creación de las farolas

            memcpy(colores, coloresTaburetes_c, 4*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/taburetes.3ds", &num_vertices0);

            break;
		}
		case PUESTOCOMIDA_ID: {  // Creación de las farolas
            tx =  0.0;
		    ty =  0.0;
		    tz =  0.0;
		    rr =  0.0;

            memcpy(colores, coloresRestaurante_c, 12*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/puestoComida.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/puestoComidaEncimera.3ds", &num_vertices1);
            modelo2 = Load3DS("../../Modelos/puestoComidaArmario.3ds", &num_vertices2);
            break;
		}
		case EDIFICIOVIEJO_ID: {  // Creación de las farolas
            tx =  0.0;
		    ty =  0.0;
		    tz =  0.0;
		    rr =  0.0;

            memcpy(colores, coloresEdifioViejo, 12*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/edificioViejo.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/edificioViejoTejado.3ds", &num_vertices1);
            break;
		}
		case TIENDA_ID: {  // Creación de las farolas
            tx =  0.0;
		    ty =  0.0;
		    tz =  0.0;
		    rr =  0.0;

            memcpy(colores, coloresTienda, 20*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/tienda.3ds", &num_vertices0);
            modelo5 = Load3DS("../../Modelos/tiendaPuerta.3ds", &num_vertices5);
            modelo1 = Load3DS("../../Modelos/tiendaMostrador.3ds", &num_vertices1);
            modelo2 = Load3DS("../../Modelos/tiendaSoportes.3ds", &num_vertices2);
            modelo3 = Load3DS("../../Modelos/tiendaToldo.3ds", &num_vertices3);
            modelo4 = Load3DS("../../Modelos/mostradorFruta.3ds", &num_vertices4);
            break;
		}
		case CUERDAS_ID: {  // Creación de las farolas
            tx =  0.0;
		    ty =  0.0;
		    tz =  0.0;
		    rr =  0.0;

            memcpy(colores, coloresCuerdas, 4*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/cuerdas.3ds", &num_vertices0);

            break;
		}
		case PAPELERAS_ID: {  // Creación de las farolas
            tx =  0.0;
		    ty =  0.0;
		    tz =  0.0;
		    rr =  0.0;

            memcpy(colores, coloresPapeleras, 4*sizeof(float));
            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/papeleras.3ds", &num_vertices0);

            break;
		}
        case MARCADOR_ID:{
            tx =  0.0;
		    ty =  0.0;
		    tz =  0.0;
		    rr =  0.0;
            rm =  0.0;
		    memcpy(colores, coloresMarcador, 4*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/Marcador.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/MarcadorSup.3ds", &num_vertices1);
            break;
        }
		case COCHE_ID: { // Creación del coche

		    tx = -2.0;
		    ty =  0.0;
		    tz =  0.0;
		    rr =  0.0;

		    memcpy(colores, coloresc_c, 12*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por vértice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/cocheMotorT.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/rueda.3ds", &num_vertices1);
            modelo2 = Load3DS("../../Modelos/motorCoche.3ds", &num_vertices2);
            break;
		}
	} // switch
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;
    switch (tipo) {

        case CARRETERA_ID: {
            if (escena.show_road) {
                /**Para activar el modo alambrico y el modo puntos se añade lo siguiente**/
                if(escena.wireframe == 1){
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }else if(escena.wireframe == 0){
                    glPolygonMode(GL_FRONT, GL_FILL);
                    glPolygonMode(GL_BACK, GL_FILL);
                }else if(escena.wireframe == 2){
                    glPolygonMode(GL_FRONT, GL_POINT);
                    glPolygonMode(GL_BACK, GL_POINT);
                }
                /**
                    Para activar las caras ocultas(culling)
                **/
                if(escena.culling== 0){
                    glDisable(GL_CULL_FACE);
                }else{
                    glEnable(GL_CULL_FACE);
                }
                // Cálculo de la ModelView
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                // Pintar la carretera
                glUniform4fv(escena.uColorLocation, 1, colores[0]);
                //                   Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[3]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);

                // Pintar las líneas
                glUniform4fv(escena.uColorLocation, 1, colores[1]);
                //                   Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);

            }
            break;
        }
        case CALZADA_ID: {
            // Pintar las calzadas
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[5]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
            break;
        }
        case FAROLAS_ID: {
            // Pintar las farolas
            tx=0;
            ty=0;
            tz=0;
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);

            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            break;
        }
        case EDIFICIOM_ID: {
            // Pintar los edificios medianos
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[7]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            // Pintar los edificios medianos
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[7]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);


            // Pintar las ventanas edificios medianos
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+6);
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices2);
            glDisable(GL_BLEND);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            // Pintar las ventanas edificios medianos
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo3);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo3+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo3+6);
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices3);
            glDisable(GL_BLEND);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            break;
        }
        case EDIFICIOG_ID: {
            // Pintar los edificios medianos
            glUniform4fv(escena.uColorLocation, 1, colores[0]);

            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[7]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            glUniform4fv(escena.uColorLocation, 1, colores[1]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[8]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            break;
        }
        case ESTACION_ID: {
            // Pintar las calzadas
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[15]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
            break;
        }
        case VIA_ID: {
            // Pintar la via del tren
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            glUniform4fv(escena.uColorLocation, 1, colores[1]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
            break;
        }
        case TREN_ID: {
            // Pintar las calzadas
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[9]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);



            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            break;
        }
        case MAQUINAEXP_ID: {
            // Pintar las calzadas
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            break;
        }
        case TABURETES_ID: {
            // Pintar las calzadas
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //                   Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[14]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
            break;
        }

        case PUESTOCOMIDA_ID: {
            // Pintar el edificio del puesto de comida
            glUniform4fv(escena.uColorLocation, 1, colores[0]);
            //Asociamos los vértices y sus normales
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[13]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            /*
                Pintar los armarios del puesto de comida
            */
            glUniform4fv(escena.uColorLocation, 1, colores[1]);

            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+6);
            // Cálculo de la matriz modelo
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-45.992, ty+1.8039, tz-19.476));
            modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,1,0));      // en radianes
            modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(270.0), glm::vec3(0,1,0));   // en radianes

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[12]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices2);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            //El otro armario
            glUniform4fv(escena.uColorLocation, 1, colores[1]);

            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+6);
            // Cálculo de la matriz modelo
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-17.825, ty+1.8039, tz+57.272));

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[12]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices2);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);



            /*
                Pintar las encimeras del puesto de comida
            */
            glUniform4fv(escena.uColorLocation, 1, colores[2]);

            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);
            // Cálculo de la matriz modelo
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-54.2, ty, tz-17.0));
            modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,1,0));      // en radianes
            modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(0.0), glm::vec3(0,1,0));   // en radianes

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[10]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);

            //La otra encimera
            glUniform4fv(escena.uColorLocation, 1, colores[2]);

            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);
            // Cálculo de la matriz modelo
            modelMatrix     = glm::mat4(1.0f); // matriz identidad
            modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-15.199, ty, tz+65.476));
            modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,1,0));      // en radianes
            modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(90.0), glm::vec3(0,1,0));   // en radianes

            modelViewMatrix = escena.viewMatrix * modelMatrix;

            // Envía nuestra ModelView al Vertex Shader
            glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

            /**Codigo para mostrar la textura**/
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, escena.texturas[10]);
            glEnable(GL_TEXTURE_2D);
            glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
            break;
        }
        case EDIFICIOVIEJO_ID: {

            /*
                Pintar el edificio viejo
            */
            float posiciones[3]={44.302, 32.914, 16.478};
            glUniform4fv(escena.uColorLocation, 1, colores[0]);

            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
            // Cálculo de la matriz modelo


            int tam = sizeof(posiciones)/sizeof(posiciones[0]);

            for(int i = 0; i < tam; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-11.035, ty+8.34, tz+posiciones[i]));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[15]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
            }

            //Pintar el techo de los edificios
            glUniform4fv(escena.uColorLocation, 1, colores[1]);

            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);
            // Cálculo de la matriz modelo


            for(int i = 0; i < tam; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-10.231, ty+14.832, tz+posiciones[i]));


                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[11]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
            }


            break;
        }
        case TIENDA_ID: {
            // Pinta la tienda
            float posicionesTiendas[2][4]={{25.61, 3.1472,-18.23, 0.0}, {-18.239, 3.1458, 50.786, -90.0}};
            float posicionesTiendasSoportes[9][4]={{34.894, 2.4504, -5.9448, 0.0}, {28.852, 2.4504, -5.9448, 0.0}, {16.826, 2.4504, -5.9448, 0.0},
                                                    {-7.5969, 2.8424, -46.432, 90.0}, {-7.5969, 2.8424, -32.628, 90.0}, {-7.5969, 2.8424, -20.273, 90.0},
                                                    {-5.9549, 2.8424, 41.503, -90.0}, {-5.9549, 2.8424, 47.546, -90.0}, {-5.9549, 2.8424, 59.571, -90.0} };
            float posicionesTiendasMostradores[6][4]={{37.47, 0.96044,-10.819, 0.0}, {31.427, 0.96044,-10.819, 0.0}, {19.402, 0.96044,-10.819, 0.0},
                                                        {-10.829, 0.96044, 38.927, 90.0}, {-10.829, 0.96044, 44.97, 90.0}, {-10.829, 0.96044, 56.996, 90.0} };
            float posicionesTiendasToldos[9][4]={{37.363, 4.9552,-7.9209, 0.0}, {31.321, 4.9552,-7.9209, 0.0}, {19.295, 4.9552,-7.9209, 0.0},
                                                    {-6.8781, 4.9552,-43.9, -90.0}, {-6.8481, 4.9552,-30.3, -90.0}, {-6.8481, 4.9552,-17.706, -90.0},
                                                    {-7.931, 4.9552, 39.034, -90.0}, {-7.931, 4.9552, 45.077, -90.0}, {-7.931, 4.9552, 57.102, -90.0}};
            float posicionesMostradores[3][4]={{-7.3667, 1.35, -44.227, 0.0}, {-7.3667, 1.35, -30.522, 0.0}, {-7.3667, 1.35, -18.068, 0.0}};

            glUniform4fv(escena.uColorLocation, 1, colores[0]);

            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
            // Cálculo de la matriz modelo
            int tamTiendas = sizeof(posicionesTiendas)/sizeof(posicionesTiendas[0]);

            for(int i = 0; i < tamTiendas; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-posicionesTiendas[i][0], ty+posicionesTiendas[i][1], tz+posicionesTiendas[i][2]));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(posicionesTiendas[i][3]), glm::vec3(0,1,0));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[10]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
            }

            /*
                Puertas metalicas tiendas
            */
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo5);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo5+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo5+6);
            for(int i = 0; i < tamTiendas; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-posicionesTiendas[i][0], ty+posicionesTiendas[i][1], tz+posicionesTiendas[i][2]));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(posicionesTiendas[i][3]), glm::vec3(0,1,0));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[11]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices5);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
            }
            /*
                Soportes de los toldos para las tiendas
            */
            glUniform4fv(escena.uColorLocation, 1, colores[1]);
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+6);
            // Cálculo de la matriz modelo
            int tamTiendasSoportes = sizeof(posicionesTiendasSoportes)/sizeof(posicionesTiendasSoportes[0]);

            for(int i = 0; i < tamTiendasSoportes; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-posicionesTiendasSoportes[i][0], ty, tz+posicionesTiendasSoportes[i][2]));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(posicionesTiendasSoportes[i][3]), glm::vec3(0,1,0));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[12]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices2);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
            }

            /*
                Mostradores de las tiendas
            */
            glUniform4fv(escena.uColorLocation, 1, colores[2]);
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);
            // Cálculo de la matriz modelo
            int tamTiendasMostradores = sizeof(posicionesTiendasMostradores)/sizeof(posicionesTiendasMostradores[0]);

            for(int i = 0; i < tamTiendasMostradores; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-posicionesTiendasMostradores[i][0], ty+posicionesTiendasMostradores[i][1], tz+posicionesTiendasMostradores[i][2]));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(posicionesTiendasMostradores[i][3]), glm::vec3(0,1,0));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[12]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);

            }


            /*
                Toldos de la tienda
            */
            glUniform4fv(escena.uColorLocation, 1, colores[3]);
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo3);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo3+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo3+6);
            // Cálculo de la matriz modelo
            int tamTiendasToldos = sizeof(posicionesTiendasToldos)/sizeof(posicionesTiendasToldos[0]);

            for(int i = 0; i < tamTiendasToldos; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-posicionesTiendasToldos[i][0], ty+posicionesTiendasToldos[i][1], tz+posicionesTiendasToldos[i][2]));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(posicionesTiendasToldos[i][3]), glm::vec3(0,1,0));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[6]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices3);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
            }

            /*
                Puestos de fruta
            */
            glUniform4fv(escena.uColorLocation, 1, colores[4]);
            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo4);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo4+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo4+6);
            // Cálculo de la matriz modelo
            int tamMostradores = sizeof(posicionesMostradores)/sizeof(posicionesMostradores[0]);

            for(int i = 0; i < tamMostradores; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-posicionesMostradores[i][0], ty+posicionesMostradores[i][1], tz+posicionesMostradores[i][2]));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(0,1,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(posicionesMostradores[i][3]), glm::vec3(0,1,0));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[12]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices4);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);

            }


            break;
        }
        case CUERDAS_ID: {
            // Pinta  las cuerdas del edificio grande
            float posicionesCuerdas[2][3]={ {-30.91, 48.138, -32.65}, {42.472, 48.138, 32.631} };

            glUniform4fv(escena.uColorLocation, 1, colores[0]);

            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
            // Cálculo de la matriz modelo
            int tamCuerdas = sizeof(posicionesCuerdas)/sizeof(posicionesCuerdas[0]);

            for(int i = 0; i < tamCuerdas; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-posicionesCuerdas[i][0], ty+posicionesCuerdas[i][1], tz+posicionesCuerdas[i][2]));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
            }
            break;
        }
        case PAPELERAS_ID: {
            // Pinta  las cuerdas del edificio grande
            float posicionesPapepleras[6][4]={ {28.044, 0.92, -10.132}, {10.619, 0.92, -10.132}, {-16.432, 0.92, -14.663}, {15.578, 0.92, 9.82}, {-7.426, 0.92, 5.7596}, {-10.198, 0.92, 66.698} };

            glUniform4fv(escena.uColorLocation, 1, colores[0]);

            glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
            glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
            glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);
            // Cálculo de la matriz modelo
            int tamPapepeleras = sizeof(posicionesPapepleras)/sizeof(posicionesPapepleras[0]);

            for(int i = 0; i < tamPapepeleras; i++){
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx-posicionesPapepleras[i][0], ty+posicionesPapepleras[i][1], tz+posicionesPapepleras[i][2]));

                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
            }
            break;
        }
        case MARCADOR_ID: {
            ty = 0.1;
            rm += 0.3;
            if(subir == true){
                alt += 0.01;
                if(alt >= 0.5){
                    subir = false;
                }
            }else{
                alt -= 0.01;
                if(alt <= 0){
                    subir = true;
                }
            }
            if(escena.seleccion > 0){
                TPrimitiva *car = escena.GetCar(escena.seleccion);
                tx = car->tx + 1.7*sin(glm::radians(-car->ry));
                tz = car->tz - 1.7*cos(glm::radians(car->ry));
                if(escena.show_marca != 0){
                // Pintar el marcador
                    glUniform4fv(escena.uColorLocation, 1, colores[0]);
                    //                   Asociamos los vértices y sus normales
                    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                    glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                    modelMatrix     = glm::mat4(1.0f); // matriz identidad
                    modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));
                    modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rm), glm::vec3(0,1,0));      // en radianes

                    modelViewMatrix = escena.viewMatrix * modelMatrix;

                    // Envía nuestra ModelView al Vertex Shader
                    glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                    /**Codigo para mostrar la textura**/
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, escena.texturas[2]);
                    glEnable(GL_TEXTURE_2D);
                    glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    glDisable(GL_TEXTURE_2D);

                    /**Marcador superior**/

                    glUniform4fv(escena.uColorLocation, 1, colores[0]);
                    //                   Asociamos los vértices y sus normales
                    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
                    glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);

                    modelMatrix     = glm::mat4(1.0f); // matriz identidad
                    modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty+2.0+alt, tz));
                    modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rm*2), glm::vec3(0,1,0));      // en radianes
                    modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rm*2), glm::vec3(1,0,0));      // en radianes
                    modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rm*2), glm::vec3(0,0,1));      // en radianes

                    modelViewMatrix = escena.viewMatrix * modelMatrix;

                    // Envía nuestra ModelView al Vertex Shader
                    glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                    /**Codigo para mostrar la textura**/
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, escena.texturas[2]);
                    glEnable(GL_TEXTURE_2D);
                    glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    glDisable(GL_TEXTURE_2D);
                }
            }

            break;
        }
        case COCHE_ID: {
            float de = 0.65;
            float detx = 0.85;
            float det = 2.75;
            gc = 8;
            /*float dix = car->tx + de*cos(glm::radians(car->gc));
            float diz = car->tz - de*sin(glm::radians(car->gc));*/
            float dix = de * cos(glm::radians(ry));
            float diz = -de * sin(glm::radians(ry));

            float ddx = de * cos(glm::radians(ry));
            float ddz = -de * sin(glm::radians(-ry));

            float cex = tx + det*sin(glm::radians(-ry));
            float cez = tz - det*cos(glm::radians(ry));

            float tix = detx * cos(glm::radians(ry));
            float tiz = -detx * sin(glm::radians(-ry));

            float tdx = detx * cos(glm::radians(ry));
            float tdz = -detx * sin(glm::radians(-ry));
            float desp = tz;

            if (escena.show_car) {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                // Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+6);

                // Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty+0.2, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));      // en radianes
                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[0]);
                glEnable(GL_TEXTURE_2D);

                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);

                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[2]);
                // Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo2+6);

                // Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty+0.2, tz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));      // en radianes
                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envía nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[4]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices2);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
            }


            if (escena.show_wheels)
            {
                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[1]);
                // Asociamos los vértices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);
                glVertexAttribPointer(escena.aUVLocation, UV_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+6);

                // RUEDA Delantera Izquierda : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx + dix, ty+0.35, tz + diz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gr), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));  // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[1]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);

                // RUEDA Delantera Derecha : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-ddx, ty+0.35, tz + ddz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));

                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(gr), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[1]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);

                // RUEDA Trasera Izquierda : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad

                modelMatrix     = glm::translate(modelMatrix, glm::vec3(cex + tix, ty+0.35, cez - tiz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));      // en radianes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));   // en radianes

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[1]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);

                // RUEDA Trasera Derecha : Cálculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(cex - tdx, ty+0.35, cez + tdz));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(0.0), glm::vec3(0,1,0));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

                /**Codigo para mostrar la textura**/
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, escena.texturas[1]);
                glEnable(GL_TEXTURE_2D);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
                break;
            }
        }
    } // switch

}

//************************************************************** Clase TEscena

TEscena::TEscena() {

    seleccion = 1;
    num_objects = 0;
    num_cars = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;
    show_marca = 1;
    alturaCamara = 10.0;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;
    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(light2_ambient, light2_ambient_c, 4*sizeof(float));
    memcpy(light2_diffuse, light2_diffuse_c, 4*sizeof(float));
    memcpy(light2_specular, light2_specular_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glDepthFunc(GL_LESS);
    /**Para activar la transparencia o blending**/
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	//glFrontFace(GL_CCW); //sentido contrario a las agujas del reloj(lo normal)
	glFrontFace(GL_CW); //sentido horario

    // Inicialización de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    //std::cout << "Vertex Shader: " << shader.ReturnShaderID() << std::endl;
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));
    //std::cout << "Fragment Shader: " << shader.ReturnShaderID() << std::endl;
    shaderProgram = new Program(shaders);

    //std::cout << "Shader Program: " << shaderProgram->ReturnProgramID() << std::endl;

    glUseProgram(shaderProgram->ReturnProgramID());
    //glValidateProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);
    aUVLocation=shaderProgram->attrib(A_UV);
    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);
    uLuz0Location=shaderProgram->uniform(U_LUZ0);
    uLuz1Location=shaderProgram->uniform(U_LUZ1);
    uLuz2Location=shaderProgram->uniform(U_LUZ2);

    uLuz0Intensity=shaderProgram->uniform(U_LUZ0INTENSITY);
    uLuz1Intensity=shaderProgram->uniform(U_LUZ1INTENSITY);
    uLuz2Intensity=shaderProgram->uniform(U_LUZ2INTENSITY);

    uLuz0Pos=shaderProgram->uniform(U_LUZ0POS);
    uLuz1Pos=shaderProgram->uniform(U_LUZ1POS);
    uLuz2Pos=shaderProgram->uniform(U_LUZ2POS);


    /*
    std::cout << "a_Position Location: " << aPositionLocation << std::endl;
    std::cout << "a_Normal Location: " << aNormalLocation << std::endl;

    std::cout << "u_ProjectionMatrix Location: " << uProjectionMatrixLocation << std::endl;
    std::cout << "u_MVMatrix Location: " << uMVMatrixLocation << std::endl;
    std::cout << "u_VMatrix Location: " << uVMatrixLocation << std::endl;
    std::cout << "u_Color Location: " << uColorLocation << std::endl;
    std::cout << "u_Luz0 Location: " << uLuz0Location << std::endl;
    */

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);
    glEnableVertexAttribArray(aUVLocation);

    // Estableciendo la matriz de proyección perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);

    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    AddTextures();
    /**Para las sombras**/

}
void __fastcall TEscena::AddTextures()
{
    std::string nombreTexturas[17] = { "cocheTextura", "ruedaTextura", "marcador1", "asfalto", "sinTextB", "calzada", "toldo", "pared", "tuberias", "tren",
                                    "cemento", "puertaMetalica", "madera", "paredRestaurante", "sillas", "ladrillos", "paredCemento"};
    int tamNombres = sizeof(nombreTexturas)/sizeof(nombreTexturas[0]);

    glGenTextures(17, texturas);

    for(int i = 0; i < tamNombres; i++){
        std::string ruta = "../../Texturas/" + nombreTexturas[i] +".jpg";
        int t = ruta.length();
        char rutaChar[t+1];
        strcpy(rutaChar, ruta.c_str());
        pixeles = LoadJPEG (rutaChar, &ancho, &alto);
        glBindTexture(GL_TEXTURE_2D, texturas[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixeles);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        free(pixeles);
    }
}

/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

/******************** TPrimitiva *TEscena::GetCar(int id) ********************/

TPrimitiva __fastcall *TEscena::GetCar(int id)
{
    TPrimitiva *p=NULL;

    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];
        }

    }
    return(p);
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo) {

    for (int i=0; i<num_cars; i++)
    {
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, i+1, 0xFF);
        cars[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i=0; i<num_objects; i++)
    {
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        objects[i]->Render(seleccion, reflejo);
    }
}
void computePos(float deltaMovex, float deltaMovey) {

	escena.x += escena.deltaMovex * escena.lx * 0.5f;
	escena.z += escena.deltaMovex * escena.lz * 0.5f;
	escena.y += escena.deltaMovey * escena.ly * 0.5f;
}
/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{
    glm::mat4 rotateMatrix;

    glClearColor(0.0, 0.7, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    if(camara == 0){
        // Cálculo de la vista (cámara)
        //Movimiento normal de la camara por defecto
        /*
        viewMatrix      = glm::mat4(1.0f);
        rotateMatrix    = glm::make_mat4(view_rotate);
        viewMatrix      = glm::translate(viewMatrix,glm::vec3(view_position[0], view_position[1], view_position[2]));
        viewMatrix      = viewMatrix*rotateMatrix;
        viewMatrix      = glm::scale(viewMatrix,glm::vec3(scale, scale, scale));*/
        /**Movimiento de la camara normal con el raton**/

        computePos(deltaMovex, deltaMovey);
        viewMatrix      = glm::mat4(1.0f);
        glm::vec3 cameraEye     = glm::vec3(escena.x, escena.y, escena.z);
        glm::vec3 cameraCenter  = glm::vec3(escena.x+escena.lx, escena.y+escena.ly,  escena.z+escena.lz);
        glm::vec3 up            = glm::vec3(0,1,0);
        viewMatrix = glm::lookAt(cameraEye, cameraCenter, up);


    }else if(camara == 2){
        if(seleccion != 0){
            TPrimitiva *car = GetCar(seleccion);
            glm::vec3 cameraEye     = glm::vec3(car->tx-6*sin(glm::radians(car->ry)), car->ty+3, car->tz-6*cos(glm::radians(car->ry)));
            glm::vec3 cameraCenter  = glm::vec3(car->tx, car->ty, car->tz);
            glm::vec3 up            = glm::vec3(0,1,0);
            viewMatrix = glm::lookAt(cameraEye, cameraCenter, up);
        }


    }else{
        if(seleccion != 0){
            TPrimitiva *car = GetCar(seleccion);
            glm::vec3 cameraEye     = glm::vec3(car->tx, car->ty+alturaCamara, car->tz);
            glm::vec3 cameraCenter  = glm::vec3(car->tx, car->ty, car->tz);
            glm::vec3 up            = glm::vec3(0,0,1);
            viewMatrix = glm::lookAt(cameraEye, cameraCenter, up);
        }
    }
    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniform1i(uLuz1Location, gui.light1_enabled);
    glUniform1i(uLuz2Location, gui.light2_enabled);

    glUniform1f(uLuz0Intensity, gui.light0_intensity);
    glUniform1f(uLuz1Intensity, gui.light1_intensity);
    glUniform1f(uLuz2Intensity, gui.light2_intensity);

    glUniform4fv(uLuz0Pos, 1, light0_position);
    glUniform4fv(uLuz1Pos, 1, light1_position);
    glUniform4fv(uLuz2Pos, 1, light2_position);

    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!
    if(escena.perspectiva == 0){
        projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    }else{

        projectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.01f, 1000.0f);
    }
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

    glutSwapBuffers();
}

// Selecciona un objeto a través del ratón
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y)
{
    int tx, ty, tw, th;
    int index;
    int x, y, ancho, alto;
    GLUI_Master.get_viewport_area( &x, &y, &ancho, &alto );
    glReadPixels(mouse_x, alto-mouse_y+81, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
    seleccion = index;
    gui.sel = seleccion;
    show_marca = seleccion;
    GLUI_Master.sync_live_all();
}

//************************************************************** Clase TGui

TGui::TGui()
{
    sel = 1;
    selCamara = 0;
    enable_panel2 = 1;
    light0_enabled = 1;
    light1_enabled = 1;
    light2_enabled = 1;
    light0_intensity = 0.8;
    light1_intensity = 0.2;
    light2_intensity = 0.2;
    memcpy(light0_position, light0_position_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        Código con el interfaz Gráfico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );


    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    // Añade un panel con texto con el valor de la selección
    GLUI_Panel *panel0 = new GLUI_Panel(glui, "Seleccion");
    GLUI_RadioGroup *radioGroup = new GLUI_RadioGroup(panel0, &sel, SEL_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroup, "NINGUNO");


    glui->add_radiobutton_to_group(radioGroup, "COCHE 1");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 2");
    // Añade una separación
    new GLUI_Separator( glui );

    GLUI_Panel *panelCamara = new GLUI_Panel(glui, "Seleccion camara");
    GLUI_RadioGroup *radioGroupCamara = new GLUI_RadioGroup(panelCamara, &selCamara, CAMARA_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroupCamara, "Normal");


    glui->add_radiobutton_to_group(radioGroupCamara, "Aerea");
    glui->add_radiobutton_to_group(radioGroupCamara, "Seguimiento");

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    GLUI_Spinner *alturaCam = new GLUI_Spinner(glui, "Altura",&altu, ALTURA_ID, controlCallback);
    alturaCam ->set_float_limits(10.0, 100.0);
    // Añade una separación
    new GLUI_StaticText( glui, "" );

    obj_panel = new GLUI_Rollout(glui, "Propiedades", true );

    /***** Control para las propiedades de escena *****/

    //new GLUI_Checkbox( obj_panel, "Modo Alambrico", &escena.wireframe, 1, controlCallback );
    GLUI_RadioGroup *radioGroupMode = new GLUI_RadioGroup(obj_panel, &modeRender, MODERENDER_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroupMode, "Solido");
    glui->add_radiobutton_to_group(radioGroupMode, "Alambrico");
    glui->add_radiobutton_to_group(radioGroupMode, "Puntos");

    glui->add_column_to_panel(obj_panel, true);
    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, 1, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, ZBUFFER_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Ortografica", &pers, PERSPECTIVA_ID, controlCallback );

    /******** Añade controles para las luces ********/

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", false );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Luz 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Luz 2" );
    GLUI_Panel *light2 = new GLUI_Panel( roll_lights, "Luz 3" );

    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity,
                            LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;
    sb = new GLUI_Scrollbar( light0, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[0],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[1],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light0_position[2],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox( light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback );
    light1_spinner = new GLUI_Spinner( light1, "Intensidad:", &light1_intensity,
                            LIGHT1_INTENSITY_ID, controlCallback );
    light1_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light1, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[0],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[1],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light1_position[2],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);

    new GLUI_Checkbox( light2, "Encendida", &light2_enabled, LIGHT2_ENABLED_ID, controlCallback );
    light2_spinner = new GLUI_Spinner( light2, "Intensidad:", &light2_intensity,
                            LIGHT2_INTENSITY_ID, controlCallback );
    light2_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light2, "X",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[0],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light2, "Y",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[1],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light2, "Z",GLUI_SCROLL_HORIZONTAL,
                            &escena.light2_position[2],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);


    // Añade una separación
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", true );
    new GLUI_Checkbox( options, "Dibujar Coche", &escena.show_car );
    new GLUI_Checkbox( options, "Dibujar Ruedas", &escena.show_wheels );
    new GLUI_Checkbox( options, "Dibujar Carretera", &escena.show_road );


    /*** Disable/Enable botones ***/
    // Añade una separación
    new GLUI_StaticText( glui, "" );
    new GLUI_Checkbox( glui, "Bloquear Movimiento", &enable_panel2 );
    // Añade una separación
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Resetear Posicion", RESET_ID, controlCallback );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

     // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "  Autor:" );
    new GLUI_StaticText( glui, "  2021-2022 (C) Angel Robles Gonzalez  " );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

    // Añade una separación
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "Salir", 0,(GLUI_Update_CB)exit );

    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );
    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate );
    view_rot->set_spin( 0.05 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position );
    trans_xy->set_speed( .000025 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x =  new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position );
    trans_x->set_speed( .000025 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1] );
    trans_y->set_speed( .000025 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.scale );
    trans_z->set_speed( .00000005 );
}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    switch (control) {
        case LIGHT0_ENABLED_ID: {
            if ( light0_enabled )
                light0_spinner->enable();
            else
                light0_spinner->disable();
            break;
        }
        case LIGHT1_ENABLED_ID: {
            if ( light1_enabled )
                light1_spinner->enable();
            else
                light1_spinner->disable();
            break;
        }
        case LIGHT2_ENABLED_ID: {
            if ( light2_enabled )
                light2_spinner->enable();
            else
                light2_spinner->disable();
            break;
        }
        case LIGHT0_INTENSITY_ID: {

            float v[] = {
                escena.light0_diffuse[0],  escena.light0_diffuse[1],
                escena.light0_diffuse[2],  escena.light0_diffuse[3] };

            v[0] *= light0_intensity;
            v[1] *= light0_intensity;
            v[2] *= light0_intensity;
            break;
        }
        case LIGHT1_INTENSITY_ID: {

            float v[] = {
                escena.light1_diffuse[0],  escena.light1_diffuse[1],
                escena.light1_diffuse[2],  escena.light1_diffuse[3] };

            v[0] *= light1_intensity;
            v[1] *= light1_intensity;
            v[2] *= light1_intensity;
            break;
        }
        case LIGHT2_INTENSITY_ID: {

            float v[] = {
                escena.light2_diffuse[0],  escena.light2_diffuse[1],
                escena.light2_diffuse[2],  escena.light2_diffuse[3] };

            v[0] *= light2_intensity;
            v[1] *= light2_intensity;
            v[2] *= light2_intensity;
            break;
        }
        case ENABLE_ID: {
            glui2->enable();
            break;
        }
        case DISABLE_ID: {
            glui2->disable();
            break;
        }
        case RESET_ID: {
            memcpy(escena.view_position,view_position_c,3*sizeof(float));
            view_rot->reset();
            escena.scale = 1.0;
            break;
        }
        case SEL_ID: {
            escena.seleccion = sel;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case CAMARA_ID: {
            escena.camara = selCamara;
            if(selCamara != 0){
                enable_panel2 = 0;
            }else{
                enable_panel2 = 1;
            }
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case ALTURA_ID: {
            escena.alturaCamara = altu;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case MODERENDER_ID: {
            escena.wireframe = modeRender;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case PERSPECTIVA_ID: {
            escena.perspectiva = pers;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case ZBUFFER_ID:{
            if(escena.z_buffer == 1){
                glEnable(GL_DEPTH_TEST);
            }else{
                glDisable(GL_DEPTH_TEST);
            }
            glutSetWindow( glui->get_glut_window_id() );
        }
  } // switch
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != window_id )
    glutSetWindow(window_id);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */
    if (enable_panel2)

        glui2->enable();
    else
        glui2->disable();

  glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int xx, int yy )
{
    int x, y, ancho, alto;
    GLUI_Master.get_viewport_area( &x, &y, &ancho, &alto );
    glViewport( x, y, ancho, alto );

    // ATENCIÓN: comprobar que alto no sea 0
    if(alto != 0){
        escena.xy_aspect = (float)ancho / (float)alto;
        if(escena.perspectiva == 0){
            escena.projectionMatrix = glm::perspective(45.0f, escena.xy_aspect, 0.1f, 1000.0f);
        }else{
            escena.projectionMatrix = glm::ortho(200.0f, 200.0f, 500.0f, 500.0f, 0.1f, 1000.0f);
        }
    }

    glUniformMatrix4fv(escena.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(escena.projectionMatrix));

    //std::cout << "xy aspect: " << escena.xy_aspect << std::endl;

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y )
{
    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{
    escena.Pick3D(x, y);
}

