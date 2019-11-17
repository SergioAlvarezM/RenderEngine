//
// Created by sergi on 02/11/2019.
//

#ifndef RENDERENGINE_MODEL_H
#define RENDERENGINE_MODEL_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"

/*
 * Clase modelo
 *
 * Clase general de la cual deben heredar todos los elementos que deban ser dibujados en la escena.
 *
 * Para que un modelo sea dibujado necesita como minimo 3 elementos:
 *      - Vector con los vertices que deben ser dibujados
 *      - Puntero al shader que se usara en el modelo
 *      - Posicion del modelo en la escena
 *
 * Con lo anterior la clase Scene deberia ser capaz de dibujar como minimo el modelo en pantalla.
 * Modelos mas complejos u otros
 * */

struct Rotation{
    float x;
    float y;
    float z;
};

class Model {

private:
    /* Parametros que deben ser modificados para poder usarlos */
    Shader* shader;
    glm::vec3 pos;
    Rotation rot{};
    std::vector<float> vertex;
    std::vector<float> colors;

    /* parametros usados por el render para dibujar */
    GLint drawType;

    /* parametros utiles */
    std::string name;

public:


    /***************
     * CONSTRUCTOR *
     ***************/
    Model() noexcept;

    virtual ~Model();

    /**************************************/
    /* Metodos compartidos de cada modelo */
    /**************************************/

    /* Metodo para obtener la matriz de modelo, el cual la enterga en coordenadas de mundo.
     * Se calcula la matriz en cada llamado.
     * Las rotaciones se aplican en el siguiente orden x->y->z*/
    glm::mat4 getModelMatrix();

    /***********************/
    /* SETTERS AND GETTERS */
    /***********************/
    [[nodiscard]] const std::vector<float> &getVertex() const;

    void setVertex(const std::vector<float> &vector);

    [[nodiscard]] Shader *getShader() const;

    void setShader(Shader *pShader);

    [[nodiscard]] const glm::vec3 &getPos() const;

    void setPos(const glm::vec3 &position);

    [[nodiscard]] const Rotation &getRot() const;

    void setRot(const Rotation &rotation);

    const std::vector<float> &getColors() const;

    void setColors(const std::vector<float> &colors);

    GLint getDrawType() const;

    void setDrawType(GLint drawType);

    const std::string &getName();

    void setName(std::string &name);

};


#endif //RENDERENGINE_MODEL_H
