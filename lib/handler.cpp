#include "handler.h"

Handler::Handler() {

}

Handler& Handler::getInstance() {
    static Handler instance;
    return instance;
}

void Handler::registerTriangle(Triangle* triangle){
    triangle->id = triangles.size();
    std::cout << "[";
    for(int i=0; i < 18; i++) {
        std::cout << triangle->getVertices()[i] << ", ";
    }
    std::cout << "]" << std::endl;
    std::cout<<std::endl;
    triangles.push_back(triangle);
    std::cout << "triangle" << std::endl;
}

void Handler::unregisterTriangle(Triangle triangle) {
    for(int i = 0; i < Handler::getInstance().triangles.size(); i++) {
        if(Handler::getInstance().triangles[i]->id == triangle.id) {
            triangles.erase(Handler::getInstance().triangles.begin() + i);
            break;
        }
    }
}

void Handler::getVertices() {
    std::vector<float> vertices1;
    std::vector<int> indices1;

    for(int i = 0; i < Handler::getInstance().triangles.size(); i++) {
        float* v = Handler::getInstance().triangles.at(i)->getVertices();
        for(int j = 0; j < 18; j++) {
            vertices1.push_back(v[j]);
            if(j == 0) {
                indices1.push_back(i*3);
            } else if(j == 6) {
                indices1.push_back(i*3+1);
            } else if(j == 12) {
                indices1.push_back(i*3+2);
            }
        }
    }
    if(vertices1.size() != Handler::getInstance().vertices.size()) {
        Handler::getInstance().FLAG |= 1UL << 0;
    } else {
        bool same = true;
        for(int i = 0; i < vertices1.size(); i++) {
            if(vertices1[i] != Handler::getInstance().vertices[i]) {
                same = false;
            }
        }
        if(same == false) {
            Handler::getInstance().FLAG |= 1UL << 0;
        }
    }

    /*int deletedVertices = 0;
    for(int i = 0; i < indices.size(); i++) {
        // j is the index getting operated on
        for(int j = 0; j < indices.size(); j++) {
            Triangle t = triangles.at(floor(i/3.0));
            Triangle t1 = triangles.at(floor(j/3.0));
            glm::vec3 origVert1 = glm::vec3(vertices[i*6] * t.scale + t.center.x,
                    vertices[i*6+1] * t.scale + t.center.y,vertices[i*6+2] * t.scale + t.center.z);
            glm::vec3 origVert2 = glm::vec3(vertices[j*6] * t1.scale + t1.center.x,
                    vertices[j*6+1] * t1.scale + t1.center.y,vertices[j*6+2] * t1.scale + t1.center.z);
            if(origVert1 == origVert2 && i != j) {
                vertices.erase(vertices.begin()+j*6);
                vertices.erase(vertices.begin()+j*6+1);
                vertices.erase(vertices.begin()+j*6+2);
                vertices.erase(vertices.begin()+j*6+3);
                vertices.erase(vertices.begin()+j*6+4);
                vertices.erase(vertices.begin()+j*6+5);
                int erasedValue = indices.at(j);
                deletedVertices += 1;
                for(int k = 0; k < indices.size(); k++) {
                    if(indices.at(k) > erasedValue) {
                        indices[k] -= 1;
                    }
                    if(k == j) {
                        indices[k] = i;
                    }
                }
            }
        }
    }*/
    Handler::getInstance().vertices = vertices1;
    Handler::getInstance().indices = indices1;
}
