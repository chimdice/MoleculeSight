#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <fstream>

void readFile(std::string file, std::string& outputFile)
{

    std::ifstream inputFile;
    inputFile.open(file);

    if (inputFile.is_open()) {
        std::string line {};
        while(std::getline(inputFile, line)) {
            outputFile.append(line);
            outputFile.append("\n");
        }

        inputFile.close();
    } else {
        std::cout << "file closed \n";
    }
}

unsigned int CompileShaders(const std::string& shaderSourceString, unsigned int shaderType)
{
    unsigned int shader;
    const char* shaderSource {shaderSourceString.c_str()};
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

unsigned int CreateShaders(const std::string& vertexShader, const std::string& fragmentShader)
{

    unsigned int vertex {CompileShaders(vertexShader, GL_VERTEX_SHADER)};
    unsigned int fragment {CompileShaders(fragmentShader, GL_FRAGMENT_SHADER)};
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);

    int  success3;
    char infoLog3[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success3);
    if(!success3) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog3);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED2\n" << infoLog3 << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shaderProgram;
}

float btyeSize2DVector (std::vector<std::vector<float>> vectors)
{
    float size {0};
    float floatSize {sizeof(float)};

    for (std::vector<float>& v: vectors) {
        size += (v.size()*floatSize);
    }

    return size;
}

float btyeSize2DVector (std::vector<std::vector<int>> vectors)
{
    float size {0};
    float intSize {sizeof(int)};

    for (std::vector<int>& v: vectors) {
        size += (v.size()*intSize);
    }

    return size;
}

std::vector<float> fillVector (std::vector<std::vector<float>> vectors)
{
    std::vector<float> vIn {};
    for (std::vector<float>& v: vectors) {
        for (float& value: v) {
            vIn.push_back(value);
        }
    }
    return vIn;
}

std::vector<int> fillVector (std::vector<std::vector<int>> vectors)
{
    std::vector<int> vIn {};
    for (std::vector<int>& v: vectors) {
        for (int& value: v) {
            vIn.push_back(value);
        }
    }
    return vIn;
}

#endif