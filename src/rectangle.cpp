#include "entity.cpp"

#if !defined(RECTANGLE)
#define RECTANGLE

struct LineSegment
{
  double start;
  double end;
  double length;
  LineSegment(double _start, double _length)
  {
    start = _start;
    end = _start + _length;
    length = _length;
  }
  LineSegment() {};
};

struct Rectangle
{
  LineSegment topLine;
  LineSegment leftLine;
  Rectangle(Entity* entity)
  {
    LineSegment _topLine(entity->coordinates.x, entity->dimensions.width);
    LineSegment _leftLine(entity->coordinates.y, entity->dimensions.height);
    topLine = _topLine;
    leftLine = _leftLine;
  }
};

#endif // RECTANGLE
