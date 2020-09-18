/**
 * @file Scene.h
 * @author your name (you@domain.com)
 * @brief File with the Scene class definition.
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef RENDERENGINE_SCENE_H
#define RENDERENGINE_SCENE_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Model.h>
#include <Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Scene.h>
#include <algorithm>
#include <spdlog/spdlog.h>

/**
 * @brief Class in charge of the scene of the render engine.
 * 
 * Connects the Render class with the Models and the logic of the program.
 * Have a strict connection with the models that will be drawn in the scene.
 * 
 * Use addModels to add models to the scene and drawModels to render them in
 * the screen (the render is the only one who should be doing this).
 */
class Scene
{

private:
    //! Vector with model in the scene.
    std::vector<Model *> Models;

    //! Path to the pixel shader used to draw the axis
    const char *AXIS_VERTEX_SHADER = "./Shaders/Vertex_SimplePosAndColor.glsl";

    //! Path to the fragment shader used to draw the axis
    const char *AXIS_FRAGMENT_SHADER = "./Shaders/Pixel_SimplePosAndColor.glsl";

public:
    /**
     * @brief Construct a new Scene object.
     *
     */
    Scene()
    {

        this->Models = std::vector<Model *>();
    }

    /**
     * @brief Destroy the Scene object
     * 
     */
    virtual ~Scene()
    {

        // delete all the models
        for (Model *m : this->Models)
        {
            delete m;
        }
    }

    /***************************************/
    /* FUNCIONES PARA DIBUJAR EN LA ESCENA */
    /***************************************/

    /**
     * @brief Draw the models that are in the scene in the screen.
     * 
     * Draw the models that are stored in the different buffers in the scene.
     * This method should be only used by the render of the engine.
     * 
     * @param WIDTH width of the screen to calculate the aspect for the camera.
     * @param HEIGHT height of the screen to calculate the aspect of the camera.
     * @param camera Camera object to draw the elements in the scene.
     */
    void drawModels(int WIDTH, int HEIGHT, Camera *camera)
    {
        // se dibuja cada moedelo por separado
        for (size_t i = 0; i < this->Models.size(); i++)
        {
            Model *m = this->Models.at(i);
            m->draw(WIDTH, HEIGHT, camera);
        }
    }

    /**
     * @brief Add a model to the scene. Creating the respective VAO and VBO buffers to the object.
     * 
     * In case of modifying the objects (number of buffers to store data) this method should be changed
     * due that this is the method that draw them.
     * 
     * @param m Model to add to the scene.
     */
    void addModel(Model *m)
    {
        // add model at the end of the vector
        this->Models.push_back(m);
    }

    /**
     * @brief Delete the model from the scene.
     * 
     * Delete the model from the scene array and also all the buffers asociated to
     * the model from the others arrays.
     * 
     * @param model Model to delete from the arrays of the scene.
     */
    void deleteModel(Model *model)
    {

        int index = -1;

        // get the index
        std::vector<Model *>::iterator itr = std::find(this->Models.begin(), this->Models.end(), model);
        if (itr != this->Models.cend())
        {
            index = std::distance(this->Models.begin(), itr);
        }

        // in case that the model doesnt exist
        if (index == -1)
        {
            spdlog::error("Se intento borrar un modelo que no se encuentra en el arreglo");
        }

        // delete the elements in the array
        this->Models.erase(this->Models.begin() + index);
    }

    /**
     * @brief Add the coordinate axis to the scene.
     * 
     * Add a model with the cordinate axis in different colors to be drawn in the scene.
     */
    void addAxis()
    {

        // create 3 models
        Model *xAxis = new Model();
        Model *yAxis = new Model();
        Model *zAxis = new Model();

        // create and set shader
        Shader *shader = new Shader(this->AXIS_VERTEX_SHADER, this->AXIS_FRAGMENT_SHADER);
        xAxis->setShader(shader);
        yAxis->setShader(shader);
        zAxis->setShader(shader);

        // create the positions
        std::vector<float> xVector = {0, 0, 0, 10000, 0, 0};
        std::vector<float> yVector = {0, 0, 0, 0, 10000, 0};
        std::vector<float> zVector = {0, 0, 0, 0, 0, 10000};

        // set the positions
        xAxis->setVertex(xVector);
        yAxis->setVertex(yVector);
        zAxis->setVertex(zVector);

        // set colors
        std::vector<float> xColor = {1, 0, 0, 1, 0, 0};
        std::vector<float> yColor = {0, 1, 0, 0, 1, 0};
        std::vector<float> zColor = {0, 0, 1, 0, 0, 1};

        // set colors
        xAxis->setColors(xColor);
        yAxis->setColors(yColor);
        zAxis->setColors(zColor);

        // set type of draw
        xAxis->setDrawType(GL_LINES);
        yAxis->setDrawType(GL_LINES);
        zAxis->setDrawType(GL_LINES);

        // set indexes
        std::vector<unsigned int> index = {0, 1};
        xAxis->setVertexIndex(index);
        yAxis->setVertexIndex(index);
        zAxis->setVertexIndex(index);

        xAxis->setPos(glm::vec3(0, 0, 0));
        yAxis->setPos(glm::vec3(0, 0, 0));
        zAxis->setPos(glm::vec3(0, 0, 0));

        // add models to the scene
        this->addModel(xAxis);
        this->addModel(yAxis);
        this->addModel(zAxis);
    }
};

#endif //RENDERENGINE_SCENE_H
