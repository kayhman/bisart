#pragma once
#include <string>
#include <vector>

class ObjParser
{
    public:
        static void load(const std::string& file, std::vector<float>& vertex, std::vector<int>& triangles);

    private:
        static void vertex(std::istream& stream, std::vector<float>& vertex);
        static void triangle(std::istream& stream, std::vector<int>& triangles);
        static void comment(std::istream& stream);
        static void parse(std::istream& stream,std::vector<float>& vertex, std::vector<int>& triangles);

};
