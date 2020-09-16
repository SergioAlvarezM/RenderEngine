//
// Created by sergi on 28/10/2019.
//

#ifndef RENDERENGINE_SCENE_H
#define RENDERENGINE_SCENE_H

#include <vector>
#include <GLFW/glfw3.h>
#include <Model.h>
#include <Camera.h>

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

    //! Vector with the VAO objects for the render and the shaders.
    std::vector<GLuint> vectorVAO;

    //! Vector with the VBO object of the models.
    std::vector<GLuint> vectorVBO;

    //! Vector with the VBO object storing the colors of the models.
    std::vector<GLuint> vectorVBOC;

    //! Path to the pixel shader used to draw the axis
    const char *AXIS_VERTEX_SHADER = "./Shaders/Vertex_SimplePosAndColor.glsl";

    //! Path to the fragment shader used to draw the axis
    const char *AXIS_FRAGMENT_SHADER = "./Shaders/Pixel_SimplePosAndColor.glsl";

public:
    /**
     * @brief Construct a new Scene object.
     *
     */
    Scene();

    /**
     * @brief Destroy the Scene object
     * 
     */
    virtual ~Scene();

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
    void drawModels(int WIDTH, int HEIGHT, Camera *camera);

    /**
     * @brief Add a model to the scene. Creating the respective VAO and VBO buffers to the object.
     * 
     * In case of modifying the objects (number of buffers to store data) this method should be changed
     * due that this is the method that draw them.
     * 
     * @param m Model to add to the scene.
     */
    void addModel(Model *m);

    /***********************/
    /* GETTERS AND SETTERS */
    /***********************/

    /*********
     * UTILS *
     *********/

    /**
     * @brief Delete the model from the scene.
     * 
     * Delete the model from the scene array and also all the buffers asociated to
     * the model from the others arrays.
     * 
     * @param model Model to delete from the arrays of the scene.
     */
    void deleteModel(Model *model);

    /**
     * @brief Add the coordinate axis to the scene.
     * 
     * Add a model with the cordinate axis in different colors to be drawn in the scene.
     */
    void addAxis();

    /**
     * @brief Print a personalized error message.
     * 
     * @param msg Print a personalized error message in the standart output.
     */
    void error(std::string msg);
};

#endif //RENDERENGINE_SCENE_H
