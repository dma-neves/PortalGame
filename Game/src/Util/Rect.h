#ifndef RECT_H
#define RECT_H

#include "LineSegment.h"

class Rect
{
public:
    Rect(Vector2D pos = Vector2D(), Vector2D size = Vector2D());

    Vector2D getOrigin() { return (pos - (size/2.f)); }

    bool pointOnRect(Vector2D point);
    bool intersects(Rect rect);

    Vector2D pos;
    Vector2D size;
};

#endif // RECT_H
