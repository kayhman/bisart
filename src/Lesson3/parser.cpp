#include "parser.h"
#include <fstream>
#include <istream>
#include <iostream>


void ObjParser::load(const std::string& file, std::vector<float>& vertex, std::vector<int>& triangles)
{
    std::ifstream in(file.c_str());
    parse(in, vertex, triangles);
    std::cout << vertex.size() << " vertices" << std::endl;
    std::cout << triangles.size() << " triangles" << std::endl;
}

void ObjParser::vertex(std::istream& stream, std::vector<float>& vertices)
{
    float scale = 10.0;
    char c;
    float x, y, z;
    stream >> c;
    stream >> x;
    stream >> y;
    stream >> z;
    vertices.push_back(x*scale);
    vertices.push_back(y*scale);
    vertices.push_back(z*scale);
}

void ObjParser::triangle(std::istream& stream, std::vector<int>& triangles)
{
    char ch;
    int a, b, c;
    stream >> ch;
    stream >> a;
    stream >> b;
    stream >> c;
    triangles.push_back(a-1);
    triangles.push_back(b-1);
    triangles.push_back(c-1);
}

void ObjParser::comment(std::istream& stream)
{
    std::string line;
    std::getline(stream, line);
}

void ObjParser::parse(std::istream& stream, std::vector<float>& vertices, std::vector<int>& triangles)
{
    std::string line;
    while(stream.good())
    {
        char c = stream.get();
        stream.unget();
        switch(c) {
            case '#':
                comment(stream);
                break;
            case 'v':
                vertex(stream, vertices);
                break;
            case 'f':
                triangle(stream, triangles);
                break;
            default:
            std::getline(stream, line);
        }
    }
}
