//
// Created by sergi on 02/11/2019.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"

const std::vector<float> &Model::getVertex() const {
    return vertex;
}

void Model::setVertex(const std::vector<float> &vector) {
    this->vertex = vector;
}

Shader *Model::getShader() const {
    return shader;
}

void Model::setShader(Shader *pShader) {
    this->shader = pShader;
}

const glm::vec3 &Model::getPos() const {
    return pos;
}

void Model::setPos(const glm::vec3 &position) {
    this->pos = position;
}

Model::Model() noexcept {

    /* move to the center */
    pos = glm::vec3(0,0,0);

    /* dont rotate */
    rot.x = 0;
    rot.y = 0;
    rot.x = 0;

    /* No shader */
    shader = nullptr;

    /* Draw triangles by default */
    drawType = GL_TRIANGLES;
}

glm::mat4 Model::getModelMatrix() {

    glm::mat4 model = glm::mat4(1.0f);  // make sure to initialize matrix to identity matrix first

    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

    return model;
}

const Rotation &Model::getRot() const {
    return rot;
}

void Model::setRot(const Rotation &rotation) {
    Model::rot = rotation;
}

GLint Model::getDrawType() const {
    return drawType;
}

void Model::setDrawType(GLint drawType) {
    Model::drawType = drawType;
}

const std::string &Model::getName()  {
    return name;
}

void Model::setName( std::string &name) {
    Model::name = name;
}

const std::vector<float> &Model::getColors() const {
    return colors;
}

void Model::setColors(const std::vector<float> &colors) {
    Model::colors = colors;
}

Model::~Model() {

    // must delete the shader
    delete this->shader;
}
