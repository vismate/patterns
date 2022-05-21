#include <iostream>
#include <vector>

struct Circle;
struct Square;

// Note to self: Double dispatch
struct Visitor
{
    virtual auto visit(Circle &circle) -> void = 0;
    virtual auto visit(Square &square) -> void = 0;
    // ...
};

struct Shape
{
    float x, y;
    Shape(float x, float y) : x(x), y(y){};
    virtual auto draw() -> void = 0;
    virtual auto accept_visitor(Visitor &visitor) -> void = 0;
};

struct Circle : Shape
{
    float radius;
    Circle(float x, float y, float radius) : Shape(x, y), radius(radius){};
    virtual auto draw() -> void override
    {
        // Draw shape...
    }

    virtual auto accept_visitor(Visitor &visitor) -> void override
    {
        visitor.visit(*this);
    }
};

struct Square : Shape
{
    float width, height;
    Square(float x, float y, float width, float height) : Shape(x, y), width(width), height(height){};
    virtual auto draw() -> void override
    {
        // Draw shape
    }

    virtual auto accept_visitor(Visitor &visitor) -> void override
    {
        visitor.visit(*this);
    }
};

struct SerializeToJson : Visitor
{
    std::ostream &stream;

    SerializeToJson(std::ostream &stream) : stream(stream){};
    virtual auto visit(Circle &circle) -> void override
    {
        stream << "\"Circle\" : {\n"
               << "  \"x\" : " << circle.x << ",\n  \"y\" : " << circle.y << ",\n  \"r\" : " << circle.radius << "\n}";
    }
    virtual auto visit(Square &square) -> void override
    {
        stream << "\"Square\" : {\n"
               << "  \"x\" : " << square.x << ",\n  \"y\" : " << square.y << ",\n  \"width\" : " << square.width << ",\n  \"height\" : " << square.height << "\n}";
    }
};

inline auto serialize_shapes(std::vector<Shape *> &shapes, std::ostream &stream) -> std::ostream &
{
    SerializeToJson visitor{stream};

    if (shapes.empty())
        return stream;

    stream << '{';

    shapes[0]->accept_visitor(visitor);

    for (auto it = shapes.begin() + 1; it != shapes.end(); it++)
    {
        stream << ",\n";
        (*it)->accept_visitor(visitor);
    }

    stream << "\n}" << std::endl;

    return stream;
}

int main()
{
    std::vector<Shape *> shapes;
    Square square{12, 32, 123, 654};
    Circle circle{43, 67, 12};

    shapes.push_back(&square);
    shapes.push_back(&circle);

    serialize_shapes(shapes, std::cout);
}