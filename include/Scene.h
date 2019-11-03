//
// Created by sergi on 28/10/2019.
//

#ifndef RENDERENGINE_SCENE_H
#define RENDERENGINE_SCENE_H

#include<vector>
#include <GLFW/glfw3.h>
#include "Model.h"
#include "Camera.h"


class Scene {

private:
    std::vector<Model*> Models;
    std::vector<int> vectorVAO;
    std::vector<int> vectorVBO;

public:

    Scene();
    virtual ~Scene();


    /***************************************/
    /* FUNCIONES PARA DIBUJAR EN LA ESCENA */
    /***************************************/
    void drawModels(int WIDTH, int HEIGHT, Camera* camera);

    /* Funcion que se encarga de annadir un modelo a la escena. Funcion tambien genera los VAO y VBO necesarios
     * para dibujarlos.
     *
     * EN CASO DE QUE SE MODIFIQUEN LOS OBJETOS TAMBIEN SE DEBE MODIFICAR ESTE METODO PARA DIBUJARLOS
     * YA QUE SE DEBEN MODIFICAR LOS VAO Y BVO.
     * */
    void addModel(Model* m);

    /***********************/
    /* GETTERS AND SETTERS */
    /***********************/

    /*********
     * UTILS *
     *********/

    /* Metodo que sirve para entregar un mensaje de error */
    void error(std::string msg);

};


#endif //RENDERENGINE_SCENE_H
