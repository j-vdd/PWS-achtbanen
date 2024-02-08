#include "graphics/Mesh.h"

class Sphere
{
public:
    float RADIUS = 5.0f;
    unsigned int RESOLUTION = 10;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    std::vector<float> line_indices;
    std::vector<float> normals;
    std::vector<float> tex_coords;

public:
    Ref<Mesh> genMesh()
    {
        auto x = Mesh::create(vertices, indices);
        return x;
    }

    Sphere(const int radius, const int resolution);
};