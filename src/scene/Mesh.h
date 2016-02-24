#ifndef MESH_H
#define MESH_H

#include "general.h"
#include "SceneObject.h"


/**
    Custom 3D mesh class. Capable of loading basic models from .obj files

    @author     Tom Skowron
    @version    1.0 30/05/2015
*/
class Mesh : public SceneObject
{
    public:
        Mesh();
        virtual ~Mesh(){}

    public:
        bool loadModel(std::string filename);
        virtual void drawModel();

        int numVertices();
        int numFaces();

    protected:
        vector<Vector3> v;
        vector<Vector3> n;
        vector<Vector2> t;
        vector<Face>    f;


};

#endif // MESH_H
