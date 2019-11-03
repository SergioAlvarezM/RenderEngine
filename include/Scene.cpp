//
// Created by sergi on 28/10/2019.
//

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"

Scene::Scene() {
    this->Models = std::vector<Model*>();
    this->vectorVAO = std::vector<int>();
    this->vectorVBO =  std::vector<int>();
}

Scene::~Scene() {

}

void Scene::drawModels(int WIDTH, int HEIGHT, Camera* camera) {

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float) WIDTH / (float) HEIGHT,
                                            0.1f, 100.0f);

    // se dibuja cada moedelo por separado
    for(int i = 0; i < this->Models.size(); i++){

        Model* m = this->Models.at(i);

        if(m->getVertex().size() == 0)
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

void Scene::addModel(Model* m) {

    // add model at the end of the vector
    this->Models.push_back(m);

    /////////////////////////
    // GENERATE VAO AND VBO//
    /////////////////////////

    /* WARNING */
    /* Esta parte se debe modificar si el tipo de los objetos cambia, se deben generar VAOs con la estructura
     * de los objetos.*/

    unsigned int VBO, VAO;
    glGenVertexArrays(this->Models.size(), &VAO); // the id of the VAO and VBO is the length of the Model Buffer
    glGenBuffers(this->Models.size(), &VBO);

    // add vao and vbo to the vectors
    // the vector stores copies, but the VAO and VBO variables are pointers, there isnt a problem
    // but probably that could generate bugs
    this->vectorVAO.push_back(VAO);
    this->vectorVBO.push_back(VBO);

    glBindVertexArray(VAO);

    //  &m->getVertex()[0] entega un puntero al inicio de los elementos
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m->getVertex().size() * sizeof(float), &m->getVertex()[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(0);

}

void Scene::error(std::string msg) {

    std::cout << "Error: " << "SCENE: " << msg << std::endl;

}
