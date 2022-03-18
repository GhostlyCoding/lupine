#include "handler.h"

Handler::Handler() {
    //
}

Triangle Handler::registerTriangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3,
        glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) {
    Triangle triangle(p1, p2, p3, c1, c2, c3);

    triangle.id = triangles.size();
    triangles.push_back(triangle);
    return triangle;
}

void Handler::unregisterTriangle(Triangle triangle) {
    for(int i = 0; i < triangles.size(); i++) {
        if(triangles[i].id == triangle.id) {
            triangles.erase(triangles.begin() + i);
            break;
        }
    }
}

void Handler::getVertices() {
    std::vector<float> vertices;
    std::vector<int> indices;

    for(int i = 0; i < triangles.size(); i++) {
        float* v = triangles.at(i).getVertices();
        for(int j = 0; j < 18; j++) {
            vertices.push_back(v[j]);
            if(j == 0) {
                indices.push_back(i*3);
            } else if(j == 6) {
                indices.push_back(i*3+1);
            } else if(j == 12) {
                indices.push_back(i*3+2);
            }
        }
    }

    int deletedVertices = 0;
    for(int i = 0; i < indices.size(); i+=6) {
        // j is the index getting operated on
        for(int j = 0; j < indices.size(); j+=6) {
            if(vertices[i] == vertices[j] && i != j) {
                if(vertices[i+1] == vertices[j+1]) {
                    if(vertices[i+2] == vertices[j+2]) {
                        int erasedValue = indices.at(j/6);
                        indices.erase(indices.begin()+j/6);
                        deletedVertices += 1;
                        for(int k = 0; k < indices.size(); k++) {
                            if(indices.at(k) > erasedValue) {
                                indices[k] -= 1;
                            }
                        }
                        if(j > indices.size()){
                            break;
                        }
                    }
                }
            }
        }
        if(i > indices.size()) {
            break;
        }
    }
    this->vertices = vertices;
    this->indices = indices;
}
