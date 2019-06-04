#ifndef LINE_SEGMENT
#define LINE_SEGMENT

#include <cmath>

#include "Vector2D.h"

class LineSegment
{
public:
    Vector2D point[2];

    bool isHorizontal() { return (point[0].y == point[1].y); }
    bool isVertical()   { return (point[0].x == point[1].x); }

    LineSegment(Vector2D point_0 = Vector2D(), Vector2D point_1 = Vector2D())
    {
        point[0] = point_0;
        point[1] = point_1;
    }


    bool onLine(Vector2D p)
    {
       if(p.x <= std::max(point[0].x, point[1].x) && p.x <= std::min(point[0].x, point[1].x) &&
         (p.y <= std::max(point[0].y, point[1].y) && p.y <= std::min(point[0].y, point[1].y)))
         return true;

       return false;
    }

    int direction(Vector2D a, Vector2D b, Vector2D c)
    {
        int val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);

        if (val == 0)    return 0;    //colinear
        else if(val < 0) return 2;    //anti-clockwise direction
        else             return 1;    //clockwise direction
    }

    bool intersects(LineSegment ls)
    {
        int dir0 = direction(point[0], point[1], ls.point[0]);
        int dir1 = direction(point[0], point[1], ls.point[1]);
        int dir2 = direction(ls.point[0], ls.point[1], point[0]);
        int dir3 = direction(ls.point[0], ls.point[1], point[1]);

        if(dir0 != dir1 && dir2 != dir3) return true;

        if(dir0 == 0 && onLine(ls.point[0])) return true;
        if(dir1 == 0 && onLine(ls.point[1])) return true;
        if(dir2 == 0 && ls.onLine(point[0])) return true;
        if(dir3 == 0 && ls.onLine(point[1])) return true;

        return false;
    }
};

#endif
