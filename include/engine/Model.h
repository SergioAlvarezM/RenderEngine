/**
 * @file Model.h
 * @author Sergio Alvarez Medina (ser.alvarez1998@gmail.com)
 * @brief File with the defiunition of the Rotation struct and the Model class.
 * @version 0.1
 * @date 2020-09-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef RENDERENGINE_MODEL_H
#define RENDERENGINE_MODEL_H

#include <vector>
#include <glm/glm.hpp>
#include <Shader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <Model.h>
#include <Utils.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

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

    //! VAO of the model
    GLuint VAO;

    //! VBO of the model
    GLuint VBO;

    //! VBOC of the model (for colors)
    GLuint VBOC;

    //! EBO of the model (For index of vertexs)
    GLuint EBO;

    //! vector of vertex to be draw
    std::vector<float> vertex;

    //! vector of the colors of each vertex
    std::vector<float> colors;

    //! indices of the vertex to be draw (to use in OpenGL)
    std::vector<unsigned int> indexes;

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
    void load_obj(std::string filename)
    {
        std::ifstream infile(filename);
        std::string line = "";
        std::vector<std::string> parsed_line;

        std::vector<float> vertices;
        std::vector<unsigned int> indexes;

        while (std::getline(infile, line))
        {

            parsed_line = split(line, ' ');
            if (parsed_line.size() == 0)
            {
                continue;
            }

            if (parsed_line[0].compare("v") == 0)
            {
                vertices.push_back(std::stof(parsed_line[1]));
                vertices.push_back(std::stof(parsed_line[2]));
                vertices.push_back(std::stof(parsed_line[3]));
            }

            if (parsed_line[0].compare("f") == 0)
            {
                indexes.push_back(std::stof(parsed_line[1]) - 1);
                indexes.push_back(std::stof(parsed_line[2]) - 1);
                indexes.push_back(std::stof(parsed_line[3]) - 1);
            }
        }

        this->setVertexIndex(indexes);
        this->setVertex(vertices);
    }

public:
    /**
     * @brief Construct a new Model object
     * 
     */
    Model() noexcept
    {

        /* move to the center */
        pos = glm::vec3(0, 0, 0);

        /* dont rotate */
        rot.x = 0;
        rot.y = 0;
        rot.x = 0;

        /* No shader */
        shader = nullptr;

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->VBOC);
        glGenBuffers(1, &this->EBO);

        /* Draw triangles by default */
        drawType = GL_TRIANGLES;
    }

    /**
     * @brief Destroy the Model object
     * 
     */
    virtual ~Model()
    {

        // must delete the shader
        delete this->shader;
    }

    /**
     * @brief Get the Model Matrix object in world cooordinates
     * 
     * Get the Model matrix for the model (world coordinates). The rotations are applied in 
     * the following order: X->Y->Z
     * 
     * @return glm::mat4 Model matrix to use to render the object.
     */
    glm::mat4 getModelMatrix()
    {

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

        model = glm::translate(model, pos);
        model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

        return model;
    }

    /**
     * @brief Get the Vertex object
     * 
     * @return const std::vector<float>& Vertex vector of the model.
     */
    [[nodiscard]] const std::vector<float> &getVertex() const
    {
        return vertex;
    }

    /**
     * @brief Set the Vertex object of the model
     * 
     * @param vector Vector of vertex to be used in the model.
     */
    void setVertex(const std::vector<float> &vector)
    {
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, vector.size() * sizeof(float), &vector[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(0);

        this->vertex = vector;
    }

    /**
     * @brief Set the Vertex Index object.
     * 
     * Set the indexes of the vertex to be draw by OpenGL. (for example by GL_TRIANGLES)
     * 
     * @param vector Vector with the indexes of the vertices.
     */
    void setVertexIndex(const std::vector<unsigned int> &vector)
    {
        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vector.size() * sizeof(unsigned int), &vector[0], GL_STATIC_DRAW);

        this->indexes = vector;
    }

    /**
     * @brief Get the Indexes object of the model.
     * 
     * @return const std::vector<float>& Indexes to be used in the model for render.
     */
    const std::vector<unsigned int> &getIndexes()
    {
        return this->indexes;
    }

    /**
     * @brief Get the VAO of the model.
     * 
     * @return GLuint Vertex Atribute Object id.
     */
    GLuint getVAO()
    {
        return this->VAO;
    }

    /**
     * @brief Get the VBO of the model.
     * 
     * @return GLuint Vertex Buffer Object id.
     */
    GLuint getVBO()
    {
        return this->VBO;
    }

    /**
     * @brief Get the EBO of the model.
     * 
     * @return GLuint Element Buffer Object id.
     */
    GLuint getEBO()
    {
        return this->EBO;
    }

    /**
     * @brief Get the VBOC of the model.
     * 
     * @return GLuint Vertex Buffer Object id.
     */
    GLuint getVBOC()
    {
        return this->VBOC;
    }

    /**
     * @brief Get the Shader object
     * 
     * @return Shader* Shader used in the model for rendering.
     */
    [[nodiscard]] Shader *getShader() const
    {
        return shader;
    }

    /**
     * @brief Load the information from a file.
     * 
     * Currently only accepts .obj files.
     * 
     * @param filename Name of the file.
     */
    void loadFile(std::string filename)
    {

        if (filename.substr(filename.find_last_of(".") + 1) == "obj")
        {
            this->load_obj(filename);
        }
        else
        {
            this->error("Model could not be loaded. Incorrect format...");
        }
    }

    /**
     * @brief Set the Shader object
     * 
     * @param pShader Shader to be used in the model.
     */
    void setShader(Shader *pShader)
    {
        this->shader = pShader;
    }

    /**
     * @brief Get the Pos object
     * 
     * @return const glm::vec3& Position of the model.
     */
    [[nodiscard]] const glm::vec3 &getPos() const
    {
        return pos;
    }

    /**
     * @brief Set the Pos object
     * 
     * @param position New position of the model.
     */
    void setPos(const glm::vec3 &position)
    {
        this->pos = position;
    }

    /**
     * @brief Get the Rot object
     * 
     * @return const Rotation& Rotation of the model.
     */
    [[nodiscard]] const Rotation &getRot() const
    {
        return rot;
    }

    /**
     * @brief Set the Rot object
     * 
     * @param rotation New rotation of the model.
     */
    void setRot(const Rotation &rotation)
    {
        Model::rot = rotation;
    }

    /**
     * @brief Get the Colors object
     * 
     * @return const std::vector<float>& Vector with the color of the vertex of the model.
     */
    const std::vector<float> &getColors() const
    {
        return colors;
    }

    /**
     * @brief Set the Colors object
     * 
     * @param colors Vector with the colors of the vertex of the model.
     */
    void setColors(const std::vector<float> &colors)
    {
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBOC);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(1);

        this->colors = colors;
    }

    /**
     * @brief Get the Draw Type object
     * 
     * @return GLint Type of drawing of the model. (See OpenGL options)
     */
    GLint getDrawType() const
    {
        return drawType;
    }

    /**
     * @brief Set the Draw Type object
     * 
     * @param drawType Type of drawing of the model. (See OpenGL options)
     */
    void setDrawType(GLint drawType)
    {
        Model::drawType = drawType;
    }

    /**
     * @brief Get the Name object
     * 
     * @return const std::string& Name of the model.
     */
    const std::string &getName()
    {
        return name;
    }

    /**
     * @brief Set the Name object
     * 
     * @param name Name of the model.
     */
    void setName(std::string &name)
    {
        Model::name = name;
    }

    /**
     * @brief Method to give an error message
     * 
     * @param msg Message to show as an Error.
     */
    void error(std::string msg)
    {
        std::cout << "Error: "
                  << "SCENE: " << msg << std::endl;
    }
};

#endif //RENDERENGINE_MODEL_H
