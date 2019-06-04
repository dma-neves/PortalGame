#include "Rect.h"

Rect::Rect(Vector2D pos, Vector2D size) : pos(pos), size(size)
{
}

bool Rect::pointOnRect(Vector2D point)
{
    if(point.x < pos.x - size.x/2.f || point.x > pos.x + size.x/2.f) return false;
    if(point.y < pos.y - size.y/2.f || point.y > pos.y + size.y/2.f) return false;
    return true;
}

bool Rect::intersects(Rect rect)
{
	Vector2D l1 = getOrigin();
	Vector2D r1 = getOrigin() + size;
	Vector2D l2 = rect.getOrigin();
	Vector2D r2 = rect.getOrigin() + rect.size;

    if (l1.x > r2.x || l2.x > r1.x) return false;

    if(l1.y > r2.y || l2.y > r1.y) return false;

    return true;
}
