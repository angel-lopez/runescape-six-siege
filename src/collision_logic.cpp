#include <stdio.h>
#include "rectangle.cpp"


#if !defined(COLLISION_LOGIC)
#define COLLISION_LOGIC

bool pointLiesWithinLineSegment(double point, LineSegment* segment)
{
  return point >= segment->start && point <= segment->end;
}

bool lineSegmentsOverlap(LineSegment* segmentA, LineSegment* segmentB)
{
    LineSegment* longLine;
    LineSegment* shortLine;

    // if lengths are equal, either line can be "shortLine", logic still works
    if (segmentA->length > segmentB->length)
    {
        longLine = segmentA;
        shortLine = segmentB;
    }
    else
    {
        longLine = segmentB;
        shortLine = segmentA;
    }

    return (
        pointLiesWithinLineSegment(shortLine->start, longLine) ||
        pointLiesWithinLineSegment(shortLine->end, longLine)
    );
}

bool rectanglesAreColliding(Rectangle* rectangleA, Rectangle* rectangleB)
{
    bool topLinesOverlap = lineSegmentsOverlap(&rectangleA->topLine, &rectangleB->topLine);
    bool leftLinesOverlap = lineSegmentsOverlap(&rectangleA->leftLine, &rectangleB->leftLine);
    return topLinesOverlap && leftLinesOverlap;
}

#endif // COLLISION_LOGIC
