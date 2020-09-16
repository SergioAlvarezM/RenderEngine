//
// Created by sergi on 28/10/2019.
//

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
    Scene()
    {

        this->Models = std::vector<Model *>();
        this->vectorVAO = std::vector<GLuint>();
        this->vectorVBO = std::vector<GLuint>();
        this->vectorVBOC = std::vector<GLuint>();
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

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)WIDTH / (float)HEIGHT,
                                                0.1f, 100.0f);

        // se dibuja cada moedelo por separado
        for (size_t i = 0; i < this->Models.size(); i++)
        {

            Model *m = this->Models.at(i);

            if (m->getVertex().size() == 0)
                error("Modelo de nombre " + m->getName() + " no tiene vertices");

            // use the correct VAO
            glBindVertexArray(this->vectorVAO.at(i));

            // we use the shader
            m->getShader()->use();
            m->getShader()->setMat4("projection", projection);

            // the uniforms are only available to the shader that is in use
            // so we must update them in every change.
            m->getShader()->updateUniform();

            // camera/view transformation
            glm::mat4 view = camera->GetViewMatrix();
            m->getShader()->setMat4("view", view);

            // render boxes
            m->getShader()->setMat4("model", m->getModelMatrix());
            glDrawArrays(m->getDrawType(), 0, m->getVertex().size());
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

        /////////////////////////
        // GENERATE VAO AND VBO//
        /////////////////////////

        /* WARNING */
        /* Esta parte se debe modificar si el tipo de los objetos cambia, se deben generar VAOs con la estructura
     * de los objetos.*/

        GLuint VBOC, VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &VBOC);

        // add vao and vbo to the vectors
        // the vector stores copies, but the VAO and VBO variables are pointers, there isnt a problem
        // but probably that could generate bugs
        this->vectorVAO.push_back(VAO);
        this->vectorVBO.push_back(VBO);
        this->vectorVBOC.push_back(VBOC);

        glBindVertexArray(VAO);

        // only enable position if the model have positions
        if (!m->getVertex().empty())
        {

            //  &m->getVertex()[0] entega un puntero al inicio de los elementos
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, m->getVertex().size() * sizeof(float), &m->getVertex()[0], GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
            glEnableVertexAttribArray(0);
        }

        // only enable color atribute if the model has the array
        if (!m->getColors().empty())
        {

            // color attribute
            glBindBuffer(GL_ARRAY_BUFFER, VBOC);
            glBufferData(GL_ARRAY_BUFFER, m->getColors().size() * sizeof(float), &m->getColors()[0], GL_STATIC_DRAW);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
            glEnableVertexAttribArray(1);
        }
    }

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
            error("Se intento borrar un modelo que no se encuentra en el arreglo");
        }

        // delete the elements in the array
        this->Models.erase(this->Models.begin() + index);
        this->vectorVBOC.erase(this->vectorVBOC.begin() + index);
        this->vectorVBO.erase(this->vectorVBO.begin() + index);
        this->vectorVAO.erase(this->vectorVAO.begin() + index);
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

        xAxis->setPos(glm::vec3(0, 0, 0));
        yAxis->setPos(glm::vec3(0, 0, 0));
        zAxis->setPos(glm::vec3(0, 0, 0));

        // add models to the scene
        this->addModel(xAxis);
        this->addModel(yAxis);
        this->addModel(zAxis);
    }

    /**
     * @brief Print a personalized error message.
     * 
     * @param msg Print a personalized error message in the standart output.
     */
    void error(std::string msg)
    {

        std::cout << "Error: "
                  << "SCENE: " << msg << std::endl;
    }
};

#endif //RENDERENGINE_SCENE_H
