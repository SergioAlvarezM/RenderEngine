#ifndef RENDERENGINE_SHADER_H
#define RENDERENGINE_SHADER_H

#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <map>

/* Enum para identificar a que tipo de dato corresponden los uniforms del shader */
enum dataType
{
    U_BOOLEAN,
    U_INTEGER,
    U_FLOAT,
    U_VEC2,
    U_VEC3,
    U_VEC4,
    U_MAT2,
    U_MAT3,
    U_MAT4
};

/* Estructura que almacena toda la informacion de un uniform en el shader */
struct UniformData
{
    bool UD_boolean;
    int UD_integer;
    float UD_float;
    glm::vec2 UD_vec2;
    glm::vec3 UD_vec3;
    glm::vec4 UD_vec4;
    glm::mat2 UD_mat2;
    glm::mat3 UD_mat3;
    glm::mat4 UD_mat4;
    dataType myType;
};

class Shader
{
public:
    unsigned int ID;
    std::map<std::string, UniformData> myUniforms;

    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath = nullptr,
           const char *computePath = nullptr)
    {

        // 0. initialize variables
        myUniforms = std::map<std::string, UniformData>();

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;
        std::string computeCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;
        std::ifstream cShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // if vertex shader path is present, load a vertex shader
            if (vertexPath != nullptr)
            {
                vShaderFile.open(vertexPath);
                std::stringstream vShaderStream;
                vShaderStream << vShaderFile.rdbuf();
                vShaderFile.close();
                vertexCode = vShaderStream.str();
            }
            // if fragment shader path is present, also load a fragment shader
            if (fragmentPath != nullptr)
            {
                fShaderFile.open(fragmentPath);
                std::stringstream fShaderStream;
                fShaderStream << fShaderFile.rdbuf();
                fShaderFile.close();
                fragmentCode = fShaderStream.str();
            }
            // if geometry shader path is present, also load a geometry shader
            if (geometryPath != nullptr)
            {
                gShaderFile.open(geometryPath);
                std::stringstream gShaderStream;
                gShaderStream << gShaderFile.rdbuf();
                gShaderFile.close();
                geometryCode = gShaderStream.str();
            }
            // if compute shader path is present, also load a compute shader
            if (computePath != nullptr)
            {
                cShaderFile.open(computePath);
                std::stringstream cShaderStream;
                cShaderStream << cShaderFile.rdbuf();
                cShaderFile.close();
                computeCode = cShaderStream.str();
            }
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        // if vertex shader is given, compile vertex shader
        unsigned int vertex;
        if (vertexPath != nullptr)
        {
            const char *vShaderCode = vertexCode.c_str();
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            checkCompileErrors(vertex, "VERTEX");
        }
        // if fragment shader is given, compile fragment shader
        unsigned int fragment;
        if (fragmentPath != nullptr)
        {
            const char *fShaderCode = fragmentCode.c_str();
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            checkCompileErrors(fragment, "FRAGMENT");
        }
        // if geometry shader is given, compile geometry shader
        unsigned int geometry;
        if (geometryPath != nullptr)
        {
            const char *gShaderCode = geometryCode.c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &gShaderCode, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }
        // if compute shader is given, compile compute shader
        unsigned int compute;
        if (computePath != nullptr)
        {
            const char *cShaderCode = computeCode.c_str();
            compute = glCreateShader(GL_COMPUTE_SHADER);
            glShaderSource(compute, 1, &cShaderCode, NULL);
            glCompileShader(compute);
            checkCompileErrors(compute, "COMPUTE");
        }
        // shader Program
        ID = glCreateProgram();
        if (vertexPath != nullptr)
            glAttachShader(ID, vertex);
        if (fragmentPath != nullptr)
            glAttachShader(ID, fragment);
        if (geometryPath != nullptr)
            glAttachShader(ID, geometry);
        if (computePath != nullptr)
            glAttachShader(ID, compute);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessery
        if (vertexPath != nullptr)
            glDeleteShader(vertex);
        if (fragmentPath != nullptr)
            glDeleteShader(fragment);
        if (geometryPath != nullptr)
            glDeleteShader(geometry);
        if (computePath != nullptr)
            glDeleteShader(compute);
    }

    // activate the shader
    // ------------------------------------------------------------------------
    void use()
    {
        glUseProgram(ID);
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_BOOLEAN;
        uniform.UD_boolean = value;

        // overwrite information
        myUniforms[name] = uniform;
    }

    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_INTEGER;
        uniform.UD_integer = value;

        // overwrite information
        myUniforms[name] = uniform;
    }

    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_FLOAT;
        uniform.UD_float = value;

        // overwrite information
        myUniforms[name] = uniform;
    }

    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_VEC2;
        uniform.UD_vec2 = value;

        // overwrite information
        myUniforms[name] = uniform;
    }

    void setVec2(const std::string &name, float x, float y)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_VEC2;
        uniform.UD_vec2 = glm::vec2(x, y);

        // overwrite information
        myUniforms[name] = uniform;
    }

    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_VEC3;
        uniform.UD_vec3 = value;

        // overwrite information
        myUniforms[name] = uniform;
    }

    void setVec3(const std::string &name, float x, float y, float z)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_VEC3;
        uniform.UD_vec3 = glm::vec3(x, y, z);

        // overwrite information
        myUniforms[name] = uniform;
    }

    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_VEC4;
        uniform.UD_vec4 = value;

        // overwrite information
        myUniforms[name] = uniform;
    }

    void setVec4(const std::string &name, float x, float y, float z, float w)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_VEC4;
        uniform.UD_vec4 = glm::vec4(x, y, z, w);

        // overwrite information
        myUniforms[name] = uniform;
    }

    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_MAT2;
        uniform.UD_mat2 = mat;

        // overwrite information
        myUniforms[name] = uniform;
    }

    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_MAT3;
        uniform.UD_mat3 = mat;

        // overwrite information
        myUniforms[name] = uniform;
    }

    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat)
    {

        // create uniform storing the data
        UniformData uniform = UniformData();
        uniform.myType = U_MAT4;
        uniform.UD_mat4 = mat;

        // overwrite information
        myUniforms[name] = uniform;
    }

    // Set and Update the shaders uniform
    // ------------------------------------------------------------------------
    void updateUniform()
    {

        for (std::map<std::string, UniformData>::iterator it = myUniforms.begin(); it != myUniforms.end(); ++it)
        {

            // we obtain the uniform from the hash
            std::string name = it->first;
            UniformData uniform = it->second;

            // identify and define the uniform
            switch (uniform.myType)
            {

            case U_BOOLEAN:
                glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)uniform.UD_boolean);
                break;

            case U_INTEGER:
                glUniform1i(glGetUniformLocation(ID, name.c_str()), uniform.UD_integer);
                break;

            case U_FLOAT:
                glUniform1f(glGetUniformLocation(ID, name.c_str()), uniform.UD_float);
                break;

            case U_VEC2:
                glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &uniform.UD_vec2[0]);
                break;

            case U_VEC3:
                glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &uniform.UD_vec3[0]);
                break;

            case U_VEC4:
                glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &uniform.UD_vec4[0]);
                break;

            case U_MAT2:
                glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &uniform.UD_mat2[0][0]);
                break;

            case U_MAT3:
                glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &uniform.UD_mat3[0][0]);
                break;

            case U_MAT4:
                glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &uniform.UD_mat4[0][0]);
                break;
            }
        }
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif