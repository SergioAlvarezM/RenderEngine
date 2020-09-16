//
// Created by sergi on 02/11/2019.
//

#ifndef RENDERENGINE_MODEL_H
#define RENDERENGINE_MODEL_H

#include <vector>
#include <glm/glm.hpp>
#include <Shader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <Model.h>
#include <Utils.h>

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
    void load_obj(std::string filename)
    {
        std::ifstream infile(filename);
        std::string line = "";
        std::vector<std::string> parsed_line;

        std::vector<std::vector<float>> vertices;
        std::vector<std::vector<int>> faces;

        while (std::getline(infile, line))
        {

            parsed_line = split(line, ' ');
            if (parsed_line.size() == 0)
            {
                continue;
            }

            if (parsed_line[0].compare("v") == 0)
            {
                std::vector<float> new_vertex;
                new_vertex.push_back(std::stof(parsed_line[1]));
                new_vertex.push_back(std::stof(parsed_line[2]));
                new_vertex.push_back(std::stof(parsed_line[3]));

                vertices.push_back(new_vertex);
            }

            if (parsed_line[0].compare("f") == 0)
            {
                std::vector<int> face;

                for (int i = 1; i < parsed_line.size(); i++)
                {
                    // faces can also have this format: f 6/4/1 3/5/3 7/6/5
                    std::string pos_vertex = split(parsed_line[i], '/')[0];

                    face.push_back(std::stoi(pos_vertex));
                }

                faces.push_back(face);
            }
        }

        std::vector<float> vertices_triangles;
        for (std::vector<int> face : faces)
        {
            for (int i = 1; i + 1 < face.size(); i++)
            {
                // indexes in the faces start from 1 and not from 0
                vertices_triangles.push_back(vertices[face[0] - 1][0]);
                vertices_triangles.push_back(vertices[face[0] - 1][1]);
                vertices_triangles.push_back(vertices[face[0] - 1][2]);

                vertices_triangles.push_back(vertices[face[i] - 1][0]);
                vertices_triangles.push_back(vertices[face[i] - 1][1]);
                vertices_triangles.push_back(vertices[face[i] - 1][2]);

                vertices_triangles.push_back(vertices[face[i + 1] - 1][0]);
                vertices_triangles.push_back(vertices[face[i + 1] - 1][1]);
                vertices_triangles.push_back(vertices[face[i + 1] - 1][2]);
            }
        }

        this->vertex = vertices_triangles;
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
     * @brief Set the Vertex object
     * 
     * @param vector Vector of vertex to be used in the model.
     */
    void setVertex(const std::vector<float> &vector)
    {
        this->vertex = vector;
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
        Model::colors = colors;
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
