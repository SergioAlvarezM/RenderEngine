//
// Created by sergi on 28/10/2019.
//

#ifndef RENDERENGINE_SCENE_H
#define RENDERENGINE_SCENE_H

#include <vector>
#include <GLFW/glfw3.h>
#include "Model.h"
#include "Camera.h"

class Scene
{

private:
    std::vector<Model *> Models;
    std::vector<GLuint> vectorVAO;
    std::vector<GLuint> vectorVBO;
    std::vector<GLuint> vectorVBOC;

    // path to the shaders used by the class
    const char *AXIS_VERTEX_SHADER = "./Shaders/Vertex_SimplePosAndColor.glsl";
    const char *AXIS_FRAGMENT_SHADER = "./Shaders/Pixel_SimplePosAndColor.glsl";

public:
    Scene();
    virtual ~Scene();

    /***************************************/
    /* FUNCIONES PARA DIBUJAR EN LA ESCENA */
    /***************************************/
    void drawModels(int WIDTH, int HEIGHT, Camera *camera);

    /* Funcion que se encarga de annadir un modelo a la escena. Funcion tambien genera los VAO y VBO necesarios
     * para dibujarlos.
     *
     * EN CASO DE QUE SE MODIFIQUEN LOS OBJETOS TAMBIEN SE DEBE MODIFICAR ESTE METODO PARA DIBUJARLOS
     * YA QUE SE DEBEN MODIFICAR LOS VAO Y BVO.
     * */
    void addModel(Model *m);

    /***********************/
    /* GETTERS AND SETTERS */
    /***********************/

    /*********
     * UTILS *
     *********/

    /* delete the model from the arrays. (delete data in all arrays) */
    void deleteModel(Model *model);

    /* Method to add a model that draws the axis on the screen */
    void addAxis();

    /* Metodo que sirve para entregar un mensaje de error */
    void error(std::string msg);
};

#endif //RENDERENGINE_SCENE_H
