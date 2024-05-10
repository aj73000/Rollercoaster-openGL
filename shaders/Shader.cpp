#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath,
               const char* tessellationControlPath,
               const char* tessellationEvaluationPath,
               const char* geometryPath)
{
    unsigned int vertex, fragment,tessellationControl,tessellationEvaluation,geometry;
    // shader Program
    ID = glCreateProgram();
    // vertex shader
    if(vertexPath != nullptr){
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::ifstream vShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open file
            vShaderFile.open(vertexPath);
            std::stringstream vShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        glAttachShader(ID, vertex);
    }
    if(tessellationControlPath != nullptr){
        std::string tessellationControlCode;
        std::ifstream tcShaderFile;
        tcShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            tcShaderFile.open(tessellationControlPath);
            std::stringstream tcShaderStream;
            tcShaderStream << tcShaderFile.rdbuf();
            tcShaderFile.close();
            tessellationControlCode = tcShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char * tcShaderCode = tessellationControlCode.c_str();
        tessellationControl = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tessellationControl, 1, &tcShaderCode, nullptr);
        glCompileShader(tessellationControl);
        checkCompileErrors(tessellationControl, "Tessellation Control");
        glAttachShader(ID, tessellationControl);
    }
    if(tessellationEvaluationPath != nullptr){
        std::string tessellationEvaluationCode;
        std::ifstream teShaderFile;
        teShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            teShaderFile.open(tessellationEvaluationPath);
            std::stringstream teShaderStream;
            teShaderStream << teShaderFile.rdbuf();
            teShaderFile.close();
            tessellationEvaluationCode = teShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char * teShaderCode = tessellationEvaluationCode.c_str();
        tessellationEvaluation = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tessellationEvaluation, 1, &teShaderCode, nullptr);
        glCompileShader(tessellationEvaluation);
        checkCompileErrors(tessellationEvaluation, "Tessellation Evaluation");
        glAttachShader(ID, tessellationEvaluation);
    }
    if(fragmentPath != nullptr){
        // fragment Shader
        std::string fragmentCode;
        std::ifstream fShaderFile;
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            fShaderFile.open(fragmentPath);
            std::stringstream fShaderStream;
            fShaderStream << fShaderFile.rdbuf();
            fShaderFile.close();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char * fShaderCode = fragmentCode.c_str();
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        glAttachShader(ID, fragment);
    }
    if(geometryPath != nullptr){
        std::string geometryCode;
        std::ifstream geometryShaderFile;
        geometryShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            geometryShaderFile.open(geometryPath);
            std::stringstream geometryShaderStream;
            geometryShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = geometryShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* geometryShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &geometryShaderCode, nullptr);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "Geometry");
        glAttachShader(ID, geometry);
    }
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(tessellationControl);
    glDeleteShader(tessellationEvaluation);
    glDeleteShader(geometry);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}