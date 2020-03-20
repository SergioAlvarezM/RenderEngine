//
// Created by sergi on 02/11/2019.
//

#include <glm/gtc/matrix_transform.hpp>
#include <Model.h>
#include <Utils.h>

const std::vector<float> &Model::getVertex() const
{
    return vertex;
}

void Model::setVertex(const std::vector<float> &vector)
{
    this->vertex = vector;
}

Shader *Model::getShader() const
{
    return shader;
}

void Model::setShader(Shader *pShader)
{
    this->shader = pShader;
}

const glm::vec3 &Model::getPos() const
{
    return pos;
}

void Model::setPos(const glm::vec3 &position)
{
    this->pos = position;
}

Model::Model() noexcept
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

glm::mat4 Model::getModelMatrix()
{

    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0.0f, 0.0f, 1.0f));

    return model;
}

void Model::load_obj(std::string filename)
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

void Model::loadFile(std::string filename)
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

const Rotation &Model::getRot() const
{
    return rot;
}

void Model::setRot(const Rotation &rotation)
{
    Model::rot = rotation;
}

GLint Model::getDrawType() const
{
    return drawType;
}

void Model::setDrawType(GLint drawType)
{
    Model::drawType = drawType;
}

const std::string &Model::getName()
{
    return name;
}

void Model::setName(std::string &name)
{
    Model::name = name;
}

const std::vector<float> &Model::getColors() const
{
    return colors;
}

void Model::setColors(const std::vector<float> &colors)
{
    Model::colors = colors;
}

Model::~Model()
{

    // must delete the shader
    delete this->shader;
}

void Model::error(std::string msg)
{
    std::cout << "Error: "
              << "SCENE: " << msg << std::endl;
}