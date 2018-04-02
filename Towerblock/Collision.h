#ifndef COLLISION_H
#define COLLISION_H

#include "Framework\Data\Pair.h"
#include "Framework\Data\AABB.h"
#include "Circle.h"
#include "Line.h"

#include "Rotation.h"

bool PointWithinAABB(PairFloat point, AABB box);
bool PointWithinCircle(PairFloat point, Circle circ);
bool PointWithinLine(PairFloat point, Line line);
bool CollideAABBtoAABB(AABB box1, AABB box2);
bool CollideAABBtoCircle(AABB box, Circle circ);
bool CollideAABBtoLine(AABB box, Line line);
bool CollideCircletoAABB(Circle circ, AABB box);
bool CollideCircletoCircle(Circle circ1, Circle circ2);
bool CollideCircletoLine(Circle circ, Line line);
bool CollideLinetoAABB(Line line, AABB box);
bool CollideLinetoCircle(Line line, Circle circ);
bool CollideLinetoLine(Line line1, Line line2);

#endif
