//
// Created by sergi on 28/10/2019.
//

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include <algorithm>

Scene::Scene() {
    this->Models = std::vector<Model *>();
    this->vectorVAO = std::vector<int>();
    this->vectorVBO = std::vector<int>();
    this->vectorVBOC = std::vector<int>();
}

Scene::~Scene() {

    // delete all the models
    for (Model *m : this->Models) {
        delete m;
    }

}

void Scene::drawModels(int WIDTH, int HEIGHT, Camera *camera) {

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float) WIDTH / (float) HEIGHT,
                                            0.1f, 100.0f);

    // se dibuja cada moedelo por separado
    for (int i = 0; i < this->Models.size(); i++) {

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

void Scene::addModel(Model *m) {

    // add model at the end of the vector
    this->Models.push_back(m);

    /////////////////////////
    // GENERATE VAO AND VBO//
    /////////////////////////

    /* WARNING */
    /* Esta parte se debe modificar si el tipo de los objetos cambia, se deben generar VAOs con la estructura
     * de los objetos.*/

    unsigned int VBOC, VBO, VAO;
    glGenVertexArrays(this->Models.size(), &VAO); // the id of the VAO and VBO is the length of the Model Buffer
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
    if (!m->getVertex().empty()) {

        //  &m->getVertex()[0] entega un puntero al inicio de los elementos
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, m->getVertex().size() * sizeof(float), &m->getVertex()[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
        glEnableVertexAttribArray(0);

    }

    // only enable color atribute if the model has the array
    if (!m->getColors().empty()) {

        // color attribute
        glBindBuffer(GL_ARRAY_BUFFER, VBOC);
        glBufferData(GL_ARRAY_BUFFER, m->getColors().size() * sizeof(float), &m->getColors()[0], GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
        glEnableVertexAttribArray(1);

    }

}

void Scene::error(std::string msg) {

    std::cout << "Error: " << "SCENE: " << msg << std::endl;

}

void Scene::addAxis() {

    // create 3 models
    Model *xAxis = new Model();
    Model *yAxis = new Model();
    Model *zAxis = new Model();

    // create and set shader
    Shader *shader = new Shader("./Shaders/Vertex_SimplePosAndColor.glsl", "./Shaders/Pixel_SimplePosAndColor.glsl");
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

void Scene::deleteModel(Model *model) {

    int index = -1;

    // get the index
    std::vector<Model *>::iterator itr = std::find(this->Models.begin(), this->Models.end(), model);
    if (itr != this->Models.cend()) {
        index = std::distance(this->Models.begin(), itr);
    }

    // in case that the model doesnt exist
    if (index == -1) {
        error("Se intento borrar un modelo que no se encuentra en el arreglo");
    }

    // delete the elements in the array
    this->Models.erase(this->Models.begin() + index);
    this->vectorVBOC.erase(this->vectorVBOC.begin() + index);
    this->vectorVBO.erase(this->vectorVBO.begin() + index);
    this->vectorVAO.erase(this->vectorVAO.begin() + index);

}

