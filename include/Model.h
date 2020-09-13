//
// Created by sergi on 02/11/2019.
//

#ifndef RENDERENGINE_MODEL_H
#define RENDERENGINE_MODEL_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Shader.h>

/**
 * @brief Struct to manage the rotation of the models.
 * 
 * Structure used in the Model Class to manage the rotation of the models in the scene.
 * 
 */
struct Rotation
{
    //! Rotation in the x axis
    float x;

    //! Rotation in the y axis
    float y;

    //! Rotation in the z axis
    float z;
};

/**
 * @brief General class that has all the elements that must be draw in the scene.
 * 
 * For an element to be draw it must have 3 attributes:
 *      - Vector with the vertices.
 *      - A pointer to the shaders to be used.
 *      - Position of the model in the scene.
 * 
 * If the element have those attributes the Scene must be able to draw the element. All the 
 * elements that should be drawed by the scene should inherit from this class.
 * 
 */
class Model
{

private:
    /* Parametros que deben ser modificados para poder usarlos */

    //! Pointer to the shader to use
    Shader *shader;

    //! Position of the model
    glm::vec3 pos;

    //! Rotation of the model
    Rotation rot{};

    //! vector of vertex to be draw
    std::vector<float> vertex;

    //! vector of the colors of each vertex
    std::vector<float> colors;

    //! type of drawing to be used by openGL (usually GL_TRIANGLES)
    GLint drawType;

    //! Name of the model
    std::string name;

    /**
     * @brief Load a file of type .obj
     * 
     * Method to load a .obj file.
     * 
     * Load all the characteristic of the .obj into the parameters of the model.
     * TODO: load ALL the characteristic into the model. (currently only load the vertex and
     * the first parameter of the face), to do this its necessary to add material to the engine.
     * 
     * @param filename Name of the file.
     */
    void load_obj(std::string filename);

public:
    /**
     * @brief Construct a new Model object
     * 
     */
    Model() noexcept;

    /**
     * @brief Destroy the Model object
     * 
     */
    virtual ~Model();

    /**
     * @brief Get the Model Matrix object in world cooordinates
     * 
     * Get the Model matrix for the model (world coordinates). The rotations are applied in 
     * the following order: X->Y->Z
     * 
     * @return glm::mat4 
     */
    glm::mat4 getModelMatrix();

    /**
     * @brief Get the Vertex object
     * 
     * @return const std::vector<float>& 
     */
    [[nodiscard]] const std::vector<float> &getVertex() const;

    /**
     * @brief Set the Vertex object
     * 
     * @param vector 
     */
    void setVertex(const std::vector<float> &vector);

    /**
     * @brief Get the Shader object
     * 
     * @return Shader* 
     */
    [[nodiscard]] Shader *getShader() const;

    /**
     * @brief Load the information from a file.
     * 
     * Currently only accepts .obj files.
     * 
     * @param filename Name of the file.
     */
    void loadFile(std::string filename);

    /**
     * @brief Set the Shader object
     * 
     * @param pShader 
     */
    void setShader(Shader *pShader);

    /**
     * @brief Get the Pos object
     * 
     * @return const glm::vec3& 
     */
    [[nodiscard]] const glm::vec3 &getPos() const;

    /**
     * @brief Set the Pos object
     * 
     * @param position 
     */
    void setPos(const glm::vec3 &position);

    /**
     * @brief Get the Rot object
     * 
     * @return const Rotation& 
     */
    [[nodiscard]] const Rotation &getRot() const;

    /**
     * @brief Set the Rot object
     * 
     * @param rotation 
     */
    void setRot(const Rotation &rotation);

    /**
     * @brief Get the Colors object
     * 
     * @return const std::vector<float>& 
     */
    const std::vector<float> &getColors() const;

    /**
     * @brief Set the Colors object
     * 
     * @param colors 
     */
    void setColors(const std::vector<float> &colors);

    /**
     * @brief Get the Draw Type object
     * 
     * @return GLint 
     */
    GLint getDrawType() const;

    /**
     * @brief Set the Draw Type object
     * 
     * @param drawType 
     */
    void setDrawType(GLint drawType);

    /**
     * @brief Get the Name object
     * 
     * @return const std::string& 
     */
    const std::string &getName();

    /**
     * @brief Set the Name object
     * 
     * @param name Name of the model.
     */
    void setName(std::string &name);

    /**
     * @brief Method to give an error message
     * 
     * @param msg Message to show as an Error.
     */
    void error(std::string msg);
};

#endif //RENDERENGINE_MODEL_H
