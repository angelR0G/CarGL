
/****************************************************************************************************

    CarGL (main.cpp)

    Grado en Ingeniería Multimedia.
    Práctica de Gráficos por Computador.
    OpenGL con Shaders.
  ------------------------------------------------------------------------------------------

    CarsGL, 2012 - 2020 (C) Juan Antonio Puchol García (puchol@dccia.ua.es)

    Changelog:

    Versión 1.0 (Noviembre 2012)
        - Versión inicial para Code::Blocks 10.05

    Versión 1.1 (Noviembre 2012)
        - Arreglado el bug de selección incorrecta debido al panel inferior de controles

    Versión 1.2 (Octubre 2013 )
        - Adaptación de la librería GLUI a Code::Blocks 12.11 y 13.12

    Versión 1.3 (Octubre 2014 )
        - Adaptación de la librería GLUI a Code::Blocks 13.12

    Versión 2.0 (Octubre 2015 )
        - Adaptación del código empleando Shaders (Modern OpenGL Graphics)

    Versión 2.1 (Septiembre 2016 )
        - Modificación de los scrollbars de las luces para manipular la posisión (compatible con Code::Blocks 16.01)

    ----------------------------------------------------------------------------------------------------------------

    NOTA:   Para que esta aplicación compile correctamente se necesita tener copiados los
            siguientes archivos desde la carpeta "Para Copiar":

            glut32.dll  -> C:\Windows\system

            Si es un Windows de 32 bits:
            glew32s.lib -> C:\Program Files\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files\CodeBlocks\MinGW\include

            Si es un Windows de 64 bits:
            glew32s.lib -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glew32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            libglui32.a -> C:\Program Files (x86)\CodeBlocks\MinGW\lib
            glut32.lib  -> C:\Program Files (x86)\CodeBlocks\MinGW\lib

            glui.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glut.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL
            glew.h      -> C:\Program Files (x86)\CodeBlocks\MinGW\include\GL

            y la carpeta completa
            glm         -> C:\Program Files (x86)\CodeBlocks\MinGW\include


            ACLARACIÓN:
                Hay varias librerías libglui32.a en la carpeta "otros"
                - Renombrar libglui32.10.05.a a libglui32.a para usar Code::Blocks 10.05
                - Renombrar libglui32.12.11.a a libglui32.a para usar Code::Blocks 12.11
                - Renombrar libglui32.13.12.a a libglui32.a para usar Code::Blocks 13.12 a 17.12
                - De momento no funciona con la versión Code::Blocks 20.03

****************************************************************************************************/

#include "Objects.h"
#include <GL\glui.h>

/**************************************** myGlutKeyboard() **********/

void Keyboard(unsigned char Key, int x, int y)
{
    TPrimitiva *car = escena.GetCar(escena.seleccion);
    float velocidad = 0.24;
    switch(Key)
    {
        case 27:
        case 'q':
        case 'Q':
            exit(0);
            break;

    }

    glutPostRedisplay();
}

/**************************************** mySpecialKey() *************/

static void movement()
{
    TPrimitiva *car = escena.GetCar(escena.seleccion);
    float velocidad = 0.24;
    std::cout<<"---------------------------------------------------------------------------------------"<<std::endl;
    for(int i = 0; i < 4; i++){
        std::cout<<"La tecla "<< i <<" esta "<< car ->keyStates[i]<<std::endl;
    }
    std::cout<<"---------------------------------------------------------------------------------------"<<std::endl;
    // Comprobar que el puntero car no sea NULL
    if(car ->keyStates[0]){
        car->rr-=16;
        car->tz += velocidad * cos(glm::radians(car -> ry));
        car->tx += velocidad * sin(glm::radians(car -> ry));
        car->ry += car->gr * 0.1;
    }
    if(car ->keyStates[1]){
        car->rr+=16;
        car->tz -= velocidad  * cos(glm::radians(car -> ry));
        car->tx -= velocidad  * sin(glm::radians(car -> ry));
        car->ry -= car->gr * 0.1;
    }
    if(car ->keyStates[2]){
        if(car -> gr > -45){
            car -> gr -= car -> gc *0.5;
        }
    }
    if(car ->keyStates[3]){
        if(car -> gr < 45){
            car -> gr += car -> gc *0.5;
        }
    }
    /*switch(key)
    {
       case GLUT_KEY_UP:   // El coche avanza
        car->rr+=16;
        car->tz += velocidad * cos(glm::radians(car -> ry));
        car->tx += velocidad * sin(glm::radians(car -> ry));
        car->ry += car->gr * 0.1;
        break;

        case GLUT_KEY_DOWN:   // El coche retrocede
        car->rr-=16;
        car->tz -= velocidad  * cos(glm::radians(car -> ry));
        car->tx -= velocidad  * sin(glm::radians(car -> ry));
        car->ry -= car->gr * 0.1;
        break;

        case GLUT_KEY_RIGHT:
        //car->ry -= car->gc;
        if(car -> gr > -45){
            car -> gr -= car -> gc;
        }
        break;

        case GLUT_KEY_LEFT:
        //car->ry +=car->gc;
        if(car -> gr < 45){
            car -> gr += car -> gc;
        }

        break;
    }*/


    glutPostRedisplay();
}
static void SpecialKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F1  : escena.deltaMovex = 0.5f; break;
        case GLUT_KEY_F3  : escena.deltaMovey = 0.5f; break;
        case GLUT_KEY_F2  : escena.deltaMovex = -0.5f; break;
    }
    if(escena.seleccion != 0){
        TPrimitiva *car = escena.GetCar(escena.seleccion);
        switch(key)
        {
            case GLUT_KEY_UP:
                car ->keyStates[0] = true;
                break;
            case GLUT_KEY_DOWN:
                car ->keyStates[1] = true;
                break;
            case GLUT_KEY_RIGHT:
                car ->keyStates[2] = true;
                break;
            case GLUT_KEY_LEFT:
                car ->keyStates[3] = true;
                break;

        }
        movement();
        /*TPrimitiva *car = escena.GetCar(escena.seleccion);
        float velocidad = 0.24;
        // Comprobar que el puntero car no sea NULL
        switch(key)
        {
           case GLUT_KEY_UP:   // El coche avanza
            car->rr-=16;
            car->tz += velocidad * cos(glm::radians(car -> ry));
            car->tx += velocidad * sin(glm::radians(car -> ry));
            car->ry += car->gr * 0.1;
            break;

            case GLUT_KEY_DOWN:   // El coche retrocede
            car->rr+=16;
            car->tz -= velocidad  * cos(glm::radians(car -> ry));
            car->tx -= velocidad  * sin(glm::radians(car -> ry));
            car->ry -= car->gr * 0.1;
            break;

            case GLUT_KEY_RIGHT:
            //car->ry -= car->gc;
            if(car -> gr > -45){
                car -> gr -= car -> gc;
            }
            break;

            case GLUT_KEY_LEFT:
            //car->ry +=car->gc;
            if(car -> gr < 45){
                car -> gr += car -> gc;
            }

            break;
        }
        glutPostRedisplay();*/

    }
    //car->keyStates[key] = true;
    /*switch(key)
    {
        case GLUT_KEY_UP:
            car ->keyStates[0] = true;
            break;
        case GLUT_KEY_DOWN:
            car ->keyStates[1] = true;
            break;
        case GLUT_KEY_RIGHT:
            car ->keyStates[2] = true;
            break;
        case GLUT_KEY_LEFT:
            car ->keyStates[3] = true;
            break;
    }*/
    //std::cout<<"La tecla "<< key << " es " << car ->keyStates[key]<<std::endl;

    //movement();
}
static void SpecialKeyUp(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F1  :
        case GLUT_KEY_F3  :
        case GLUT_KEY_F2  : escena.deltaMovex = 0;escena.deltaMovey = 0;break;
    }
    if(escena.seleccion != 0){
        TPrimitiva *car = escena.GetCar(escena.seleccion);
        switch(key)
        {
            case GLUT_KEY_UP:
                car ->keyStates[0] = false;
                break;
            case GLUT_KEY_DOWN:
                car ->keyStates[1] = false;
                break;
            case GLUT_KEY_RIGHT:
                car ->keyStates[2] = false;
                car -> gr = 0;
                break;
            case GLUT_KEY_LEFT:
                car ->keyStates[3] = false;
                car -> gr = 0;
                break;

        }

        movement();
    }
}



/***************************************** myGlutMenu() ***********/

void Menu( int value )
{
  Keyboard( value, 0, 0 );
}

void Mouse(int button, int button_state, int x, int y )
{
    gui.Mouse(button, button_state, x, y);

    if (button == GLUT_LEFT_BUTTON) {
        int action = glutGetModifiers();
        if( action == GLUT_ACTIVE_SHIFT){
            escena.shift= true;
        }else{
            escena.shift= false;
        }


        if (button_state == GLUT_UP) {
            escena.anglex += escena.deltaAnglex;
            escena.angley += escena.deltaAngley;
            escena.xOrigin = -1;
            escena.yOrigin = -1;
        }
        else  {
            escena.xOrigin = x;
            escena.yOrigin = y;
        }



	}


}

void Render()
{
    escena.Render();
}

void Idle()
{
    gui.Idle();
}

void Reshape(int x, int y){
    gui.Reshape(x, y);
}

void Motion(int x, int y){
    gui.Motion(x, y);
    /**Movimiento de la camara con el raton**/
    if(escena.shift == true){
        float auxdeltaAnglex = (x - escena.xOrigin) * 0.001f;
        float auxdeltaAngley = (y - escena.yOrigin) * 0.001f;
        if(auxdeltaAnglex>= 0){

            escena.deltaMovex = 0.5f;
        }else{

            escena.deltaMovex =-0.5f;
        }
        if(auxdeltaAngley>= 0){
            escena.deltaMovey = -1.0f;
        }else{
            escena.deltaMovey = 1.0f;
        }


	}else{
        escena.deltaMovex = 0.0f;
        escena.deltaMovey = 0.0f;
        /**Rotacion de la camara con el raton**/
        if (escena.xOrigin >= 0) {
            escena.deltaAnglex = (x - escena.xOrigin) * 0.001f;
            escena.deltaAngley = (y - escena.yOrigin) * 0.001f;

            escena.lx = cos(escena.anglex + escena.deltaAnglex);
            escena.lz = -sin(escena.anglex + escena.deltaAnglex);
            escena.ly = -cos(escena.angley + escena.deltaAngley);

        }
	}

}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
    // Inicializa GLUT and crea la ventana principal
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE );
    glutInitWindowPosition( 10, 10 );
    glutInitWindowSize( 1200, 800 );

    int main_window = glutCreateWindow( "CarGL V2.1 (2020) con Shaders" );

    // Inicializa los valores de OpenGL para esta Aplicación
    escena.InitGL();
    gui.Init(main_window);

    glutDisplayFunc( Render );
    GLUI_Master.set_glutReshapeFunc( Reshape );
    GLUI_Master.set_glutKeyboardFunc( Keyboard );




    /**** We register the idle callback with GLUI, *not* with GLUT ****/
    GLUI_Master.set_glutIdleFunc( Idle );


    // Crea los objetos


    TPrimitiva *car1 = new TPrimitiva(1, COCHE_ID);
    TPrimitiva *car2 = new TPrimitiva(2, COCHE_ID);

    car1 ->keyStates[0] = false;
    car1 ->keyStates[1] = false;
    car1 ->keyStates[2] = false;
    car1 ->keyStates[3] = false;
    car1 -> gr = 0;

    car2 ->keyStates[0] = false;
    car2 ->keyStates[1] = false;
    car2 ->keyStates[2] = false;
    car2 ->keyStates[3] = false;
    car2 -> gr = 0;

    GLUI_Master.set_glutSpecialFunc( SpecialKey );
    glutSpecialUpFunc(SpecialKeyUp);
    GLUI_Master.set_glutMouseFunc( Mouse );
    glutMotionFunc( Motion );
    TPrimitiva *road = new TPrimitiva(CARRETERA_ID, CARRETERA_ID);
    TPrimitiva *calzada = new TPrimitiva(CALZADA_ID, CALZADA_ID);
    TPrimitiva *farolas = new TPrimitiva(FAROLAS_ID, FAROLAS_ID);
    TPrimitiva *edificioM = new TPrimitiva(EDIFICIOM_ID, EDIFICIOM_ID);
    TPrimitiva *edificioM1 = new TPrimitiva(EDIFICIOM_ID, EDIFICIOM_ID);
    TPrimitiva *estacion = new TPrimitiva(ESTACION_ID, ESTACION_ID);
    TPrimitiva *via = new TPrimitiva(VIA_ID, VIA_ID);
    TPrimitiva *tren = new TPrimitiva(TREN_ID, TREN_ID);
    TPrimitiva *edificioG = new TPrimitiva(EDIFICIOG_ID, EDIFICIOG_ID);
    TPrimitiva *maquina = new TPrimitiva(MAQUINAEXP_ID, MAQUINAEXP_ID);

    TPrimitiva *taburetes = new TPrimitiva(TABURETES_ID, TABURETES_ID);
    TPrimitiva *puestocomida = new TPrimitiva(PUESTOCOMIDA_ID, PUESTOCOMIDA_ID);
    TPrimitiva *puestocomidaArmario = new TPrimitiva(PUESTOCOMIDA_ID, PUESTOCOMIDA_ID);
    TPrimitiva *puestocomidaArmario1 = new TPrimitiva(PUESTOCOMIDA_ID, PUESTOCOMIDA_ID);
    TPrimitiva *puestocomidaEncimera = new TPrimitiva(PUESTOCOMIDA_ID, PUESTOCOMIDA_ID);
    TPrimitiva *puestocomidaEncimera1 = new TPrimitiva(PUESTOCOMIDA_ID, PUESTOCOMIDA_ID);

    TPrimitiva *edificioViejo = new TPrimitiva(EDIFICIOVIEJO_ID, EDIFICIOVIEJO_ID);
    TPrimitiva *edificioViejo1 = new TPrimitiva(EDIFICIOVIEJO_ID, EDIFICIOVIEJO_ID);
    TPrimitiva *edificioViejo2 = new TPrimitiva(EDIFICIOVIEJO_ID, EDIFICIOVIEJO_ID);

    TPrimitiva *tienda = new TPrimitiva(TIENDA_ID, TIENDA_ID);
    TPrimitiva *tiendaSoportes = new TPrimitiva(TIENDA_ID, TIENDA_ID);
    TPrimitiva *tiendaMostrador = new TPrimitiva(TIENDA_ID, TIENDA_ID);
    TPrimitiva *tiendaToldos = new TPrimitiva(TIENDA_ID, TIENDA_ID);
    TPrimitiva *mostrador = new TPrimitiva(TIENDA_ID, TIENDA_ID);

    TPrimitiva *cuerdas = new TPrimitiva(CUERDAS_ID, CUERDAS_ID);

    TPrimitiva *papeleras = new TPrimitiva(PAPELERAS_ID, PAPELERAS_ID);

    TPrimitiva *marcador = new TPrimitiva(MARCADOR_ID, MARCADOR_ID);
    /*Colores coche azul*/
    car2->colores[0][0] = 0.4;
    car2->colores[0][1] = 0.2;
    car2->colores[0][2] = 0.2;
    car2->colores[0][3] = 1.0;
    car2->tx = 2;
    car2->tz = 3;

    escena.AddObject(road);

    escena.AddObject(calzada);
    escena.AddObject(farolas);
    escena.AddObject(edificioM);
    escena.AddObject(edificioM1);
    escena.AddObject(estacion);
    escena.AddObject(via);
    escena.AddObject(tren);
    escena.AddObject(edificioG);
    escena.AddObject(maquina);

    escena.AddObject(taburetes);
    escena.AddObject(puestocomida);
    escena.AddObject(puestocomidaArmario);
    escena.AddObject(puestocomidaArmario1);
    escena.AddObject(puestocomidaEncimera);
    escena.AddObject(puestocomidaEncimera1);

    escena.AddObject(edificioViejo);
    escena.AddObject(edificioViejo1);
    escena.AddObject(edificioViejo2);

    escena.AddObject(tienda);
    escena.AddObject(tiendaMostrador);
    escena.AddObject(tiendaSoportes);
    escena.AddObject(tiendaToldos);
    escena.AddObject(mostrador);
    escena.AddObject(cuerdas);

    escena.AddObject(papeleras);

    escena.AddObject(marcador);
    escena.AddCar(car1);
    escena.AddCar(car2);

    /**** Regular GLUT main loop ****/
    glutMainLoop();

    return EXIT_SUCCESS;
}

