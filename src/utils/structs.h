#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <general.h>
#include <string>
#include <vector>

class glCamera;

struct Vector2 {
    float x;
    float y;

    Vector2(float nx = 0.f, float ny = 0.f)
    {
        x = nx;
        y = ny;
    }

    void set(float nx, float ny)
    {
        x = nx;
        y = ny;
    }

    void operator=(const Vector2 &other)
    {
        x = other.x;
        y = other.y;
    }

    Vector2 operator+(const Vector2 &other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2 &other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    void rotate(float angle)
    {
        float ox = x;
        float oy = y;
        float theta = angle * TO_RAD;

        x = ox * cos(theta) + oy * -sin(theta);
        y = ox * sin(theta) + oy * cos(theta);
    }

    void operator+=(const Vector2 &other)
    {
        x += other.x;
        y += other.y;
    }

    void operator-=(const Vector2 &other)
    {
        x -= other.x;
        y -= other.y;
    }

    void operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
    }
};

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3(float nx = 0.f, float ny = 0.f, float nz = 0.f)
    {
        x = nx;
        y = ny;
        z = nz;
    }

    void rotateX(float angle){
        float oy = y;
        float oz = z;
        float theta = angle * TO_RAD;

        x = oy * cos(theta) + oz * -sin(theta);
        z = oy * sin(theta) + oz * cos(theta);
    }

    void rotateY(float angle){
        float ox = x;
        float oz = z;
        float theta = angle * TO_RAD;

        x = ox * cos(theta) + oz * sin(theta);
        z = ox * -sin(theta) + oz * cos(theta);
    }

    void rotateZ(float angle){
        float ox = x;
        float oy = y;
        float theta = angle * TO_RAD;

        x = ox * cos(theta) + oy * -sin(theta);
        z = ox * sin(theta) + oy * cos(theta);
    }

    void normalise() {
        float length = sqrt(x*x + y*y + z*z);
        x /= length;
        y /= length;
        z /= length;
    }

    float getMagnitude() {
        return sqrt(x*x + y*y + z*z);
    }

    void operator=(const Vector3 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    void operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    void operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    void operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }

    Vector3 operator*(float scalar)
    {
        return Vector3(x*scalar,y*scalar,z*scalar);
    }

    Vector3 operator/(float scalar)
    {
        return Vector3(x/scalar,y/scalar,z/scalar);
    }

};

struct Colour4 {
    float r;
    float g;
    float b;
    float a;

    Colour4(float nr = 0.f, float ng = 0.f, float nb = 0.f, float na =0.f) {
        r = nr;
        g = ng;
        b = nb;
        a = na;
    }

    void operator=(const Colour4 &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.r;
    }
};

struct Rec {
    float x;
    float y;
    float w;
    float h;

    Rec(float nx = 0, float ny = 0, float nw = 0, float nh = 0) {
        x = nx;
        y = ny;
        w = nw;
        h = nh;
    }

    Rec(Vector2 nPos, Vector2 nSize) {
        Rec(nPos.x,nPos.y,nPos.x,nPos.y);
    }

    void operator=(const Rec &other)
    {
        x = other.x;
        y = other.y;
        w = other.w;
        h = other.h;
    }

    void setPosition(float nx, float ny) {
        x = nx;
        y = ny;
    }

    void setPosition(Vector2 nPos) {
        setPosition(nPos.x, nPos.y);
    }

    void setSize(float nw, float nh) {
        w = nw;
        h = nh;
    }

    void setSize(Vector2 nSize) {
        setSize(nSize.x, nSize.y);
    }

    bool isInside(float px, float py) {

        if (px < x)             return false;
        else if (px > x + w)    return false;
        if (py < y)             return false;
        else if (py > y + h)    return false;

        return true;
    }

    bool isInside(Vector2 point) {
        return isInside(point.x, point.y);
    }
};

struct Viewport {
    Rec         r;
    glCamera*   c;

    Viewport(Rec rec = Rec(), glCamera* cam = NULL) {
        r = rec;
        c = cam;
    }
};

struct Face {
    std::vector<Vector3> vd; // vertex data

    void push_back(Vector3 vec) {
        vd.push_back(vec);
    }

    Vector3 at(int index) {
        return vd.at(index);
    }
};

struct RawSceneData
{
    std::string type;
    std::string colour;
    float initRotation;
    std::vector<Vector2> pointList;
};

#endif // STRUCTS_H_INCLUDED
