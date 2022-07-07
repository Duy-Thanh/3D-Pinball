#include "pch.h"
#include "maths.h"

#include "TBall.h"
#include "TFlipperEdge.h"


// Performs AABB merge, creating rect that is just large enough to contain both source rects.
void maths::enclosing_box(const rectangle_type& rect1, const rectangle_type& rect2, rectangle_type& dstRect)
{
	auto xPos = rect1.XPosition, width = rect1.Width;
	if (rect2.XPosition < rect1.XPosition)
	{
		xPos = rect2.XPosition;
		width += rect1.XPosition - rect2.XPosition;
	}

	auto yPos = rect1.YPosition, height = rect1.Height;
	if (rect2.YPosition < rect1.YPosition)
	{
		yPos = rect2.YPosition;
		height += rect1.YPosition - rect2.YPosition;
	}

	auto xEnd2 = rect2.XPosition + rect2.Width;
	if (xEnd2 > xPos + width)
		width = xEnd2 - xPos;

	auto yEnd2 = rect2.YPosition + rect2.Height;
	if (yEnd2 > yPos + height)
		height = yEnd2 - yPos;

	dstRect.XPosition = xPos;
	dstRect.YPosition = yPos;
	dstRect.Width = width;
	dstRect.Height = height;
}

// Creates rect that represents an intersection of rect1 and rect2.
// Return true when intersection exists.
bool maths::rectangle_clip(const rectangle_type& rect1, const rectangle_type& rect2, rectangle_type* dstRect)
{
	auto xEnd2 = rect2.XPosition + rect2.Width;
	if (rect2.XPosition >= rect1.XPosition + rect1.Width || rect1.XPosition >= xEnd2)
		return 0;

	auto yEnd2 = rect2.YPosition + rect2.Height;
	if (rect2.YPosition >= rect1.YPosition + rect1.Height || rect1.YPosition >= yEnd2)
		return 0;

	auto xPos = rect1.XPosition, width = rect1.Width;
	if (rect1.XPosition < rect2.XPosition)
	{
		xPos = rect2.XPosition;
		width += rect1.XPosition - rect2.XPosition;
	}

	auto yPos = rect1.YPosition, height = rect1.Height;
	if (rect1.YPosition < rect2.YPosition)
	{
		yPos = rect2.YPosition;
		height += rect1.YPosition - rect2.YPosition;
	}

	if (xPos + width > xEnd2)
		width = xEnd2 - xPos;
	if (yPos + height > yEnd2)
		height = yEnd2 - yPos;

	if (width == 0 || height == 0)
		return false;

	if (dstRect)
	{
		dstRect->XPosition = xPos;
		dstRect->YPosition = yPos;
		dstRect->Width = width;
		dstRect->Height = height;
	}
	return true;
}

// Returns the distance from ray origin to the first ray-circle intersection point.
float maths::ray_intersect_circle(const ray_type& ray, const circle_type& circle)
{
	// O - ray origin
	// D - ray direction
	// C - circle center
	// R - circle radius
	// L, C - O, vector between O and C
	auto L = vector_sub(circle.Center, ray.Origin);

	// Tca, L dot D, projection of L on D
	float Tca = DotProduct(L, ray.Direction);
	if (Tca < 0.0f) // No intersection if Tca is negative
		return 1000000000.0f;

	// L dot L, distance from ray origin to circle center
	float LMagSq = DotProduct(L, L);

	// Thc^2 = rad^2 - d^2; d = sqrt(L dot L - Tca * Tca)
	float ThcSq = circle.RadiusSq - LMagSq + Tca * Tca;

	// T0 = Tca - Thc, distance from origin to first intersection
	// If ray origin is inside of the circle, then T0 is negative
	if (LMagSq < circle.RadiusSq)
		return Tca - sqrt(ThcSq);

	// No intersection if ThcSq is negative, that is if d > rad
	if (ThcSq < 0.0f)
		return 1000000000.0f;

	// T0 should be positive and less that max ray distance
	float T0 = Tca - sqrt(ThcSq);
	if (T0 < 0.0f || T0 > ray.MaxDistance)
		return 1000000000.0f;
	return T0;
}

float maths::normalize_2d(vector2& vec)
{
	float mag = sqrt(vec.X * vec.X + vec.Y * vec.Y);
	if (mag != 0.0f)
	{
		vec.X /= mag;
		vec.Y /= mag;
	}
	return mag;
}


void maths::line_init(line_type* line, float x0, float y0, float x1, float y1)
{
	line->Origin = { x0, y0 };
	line->Direction.X = x1 - x0;
	line->Direction.Y = y1 - y0;
	normalize_2d(line->Direction);

	// Clockwise perpendicular to the line direction vector
	line->PerpendicularC = { line->Direction.Y, -line->Direction.X };

	auto lineStart = x0, lineEnd = x1;
	if (std::abs(line->Direction.X) < 0.000000001f)
	{
		line->Direction.X = 0.0;
		lineStart = y0;
		lineEnd = y1;
	}

	line->MinCoord = std::min(lineStart, lineEnd);
	line->MaxCoord = std::max(lineStart, lineEnd);
}

// Returns the distance from ray origin to the ray-line segment intersection point.
float maths::ray_intersect_line(ray_type* ray, line_type* line)
{
	// V1 vector between ray origin and line origin
	// V2 ray direction
	// V3 line perpendicular clockwise
	auto v1 = vector_sub(ray->Origin, line->Origin);
	auto v2 = line->Direction;
	auto v3 = vector2{ -ray->Direction.Y, ray->Direction.X };

	// Project line on ray perpendicular, no intersection if ray is pointing away from the line
	auto v2DotV3 = DotProduct(v2, v3);
	if (v2DotV3 < 0.0f)
	{
		// Distance to the intersect point: (V2 X V1) / (V2 dot V3)
		auto distance = cross(v2, v1) / v2DotV3;
		if (distance >= -ray->MinDistance && distance <= ray->MaxDistance)
		{
			line->RayIntersect.X = distance * ray->Direction.X + ray->Origin.X;
			line->RayIntersect.Y = distance * ray->Direction.Y + ray->Origin.Y;

			// Check if intersection point is inside line segment
			auto testPoint = line->Direction.X != 0.0f ? line->RayIntersect.X : line->RayIntersect.Y;
			if (testPoint >= line->MinCoord && testPoint <= line->MaxCoord)
			{
				return distance;
			}
		}
	}

	return 1000000000.0;
}

void maths::cross(const vector3& vec1, const vector3& vec2, vector3& dstVec)
{
	dstVec.X = vec2.Z * vec1.Y - vec2.Y * vec1.Z;
	dstVec.Y = vec2.X * vec1.Z - vec1.X * vec2.Z;
	dstVec.Z = vec1.X * vec2.Y - vec2.X * vec1.Y;
}

float maths::cross(const vector2& vec1, const vector2& vec2)
{
	return vec1.X * vec2.Y - vec1.Y * vec2.X;
}

float maths::magnitude(const vector3& vec)
{
	float result;
	auto magSq = vec.X * vec.X + vec.Y * vec.Y + vec.Z * vec.Z;
	if (magSq == 0.0f)
		result = 0.0;
	else
		result = sqrt(magSq);
	return result;
}

void maths::vector_add(vector2& vec1Dst, const vector2& vec2)
{
	vec1Dst.X += vec2.X;
	vec1Dst.Y += vec2.Y;
}

vector2 maths::vector_sub(const vector2& vec1, const vector2& vec2)
{
	return { vec1.X - vec2.X, vec1.Y - vec2.Y };
}

float maths::basic_collision(TBall* ball, vector2* nextPosition, vector2* direction, float elasticity, float smoothness,
							 float threshold, float boost)
{
	ball->Position.X = nextPosition->X;
	ball->Position.Y = nextPosition->Y;
	float proj = -(direction->Y * ball->Acceleration.Y + direction->X * ball->Acceleration.X);
	if (proj < 0)
	{
		proj = -proj;
	}
	else
	{
		float dx1 = proj * direction->X;
		float dy1 = proj * direction->Y;
		ball->Acceleration.X = (dx1 + ball->Acceleration.X) * smoothness + dx1 * elasticity;
		ball->Acceleration.Y = (dy1 + ball->Acceleration.Y) * smoothness + dy1 * elasticity;
		normalize_2d(ball->Acceleration);
	}
	float projSpeed = proj * ball->Speed;
	float newSpeed = ball->Speed - (1.0f - elasticity) * projSpeed;
	ball->Speed = newSpeed;
	if (projSpeed >= threshold)
	{
		ball->Acceleration.X = newSpeed * ball->Acceleration.X + direction->X * boost;
		ball->Acceleration.Y = newSpeed * ball->Acceleration.Y + direction->Y * boost;
		ball->Speed = normalize_2d(ball->Acceleration);
	}
	return projSpeed;
}

float maths::Distance_Squared(const vector2& vec1, const vector2& vec2)
{
	auto dx = vec1.X - vec2.X;
	auto dy = vec1.Y - vec2.Y;
	return dy * dy + dx * dx;
}

float maths::DotProduct(const vector2& vec1, const vector2& vec2)
{
	return vec1.X * vec2.X + vec1.Y * vec2.Y;
}

float maths::Distance(const vector2& vec1, const vector2& vec2)
{
	return sqrt(Distance_Squared(vec1, vec2));
}

void maths::SinCos(float angle, float* sinOut, float* cosOut)
{
	*sinOut = sin(angle);
	*cosOut = cos(angle);
}

void maths::RotatePt(vector2& point, float sin, float cos, const vector2& origin)
{
	auto dirX = point.X - origin.X;
	auto dirY = point.Y - origin.Y;
	point.X = dirX * cos - dirY * sin + origin.X;
	point.Y = dirX * sin + dirY * cos + origin.Y;
}

float maths::distance_to_flipper(ray_type* ray1, ray_type* ray2)
{
	auto distance = 1000000000.0f;
	auto distanceType = -1;
	auto newDistance = ray_intersect_line(ray1, &TFlipperEdge::lineA);
	if (newDistance < 1000000000.0f)
	{
		distance = newDistance;
		distanceType = 0;
	}
	newDistance = ray_intersect_circle(*ray1, TFlipperEdge::circlebase);
	if (newDistance < distance)
	{
		distance = newDistance;
		distanceType = 2;
	}
	newDistance = ray_intersect_circle(*ray1, TFlipperEdge::circleT1);
	if (newDistance < distance)
	{
		distance = newDistance;
		distanceType = 3;
	}
	newDistance = ray_intersect_line(ray1, &TFlipperEdge::lineB);
	if (newDistance < distance)
	{
		distance = newDistance;
		distanceType = 1;
	}
	if (!ray2 || distance >= 1000000000.0f)
		return distance;

	if (distanceType != -1)
	{
		vector2* nextOrigin;
		if (distanceType)
		{
			if (distanceType != 1)
			{
				float dirY;
				ray2->Origin.X = distance * ray1->Direction.X + ray1->Origin.X;
				ray2->Origin.Y = distance * ray1->Direction.Y + ray1->Origin.Y;
				if (distanceType == 2)
				{
					ray2->Direction.X = ray2->Origin.X - TFlipperEdge::circlebase.Center.X;
					dirY = ray2->Origin.Y - TFlipperEdge::circlebase.Center.Y;
				}
				else
				{
					ray2->Direction.X = ray2->Origin.X - TFlipperEdge::circleT1.Center.X;
					dirY = ray2->Origin.Y - TFlipperEdge::circleT1.Center.Y;
				}
				ray2->Direction.Y = dirY;
				normalize_2d(ray2->Direction);
				return distance;
			}
			ray2->Direction = TFlipperEdge::lineB.PerpendicularC;
			nextOrigin = &TFlipperEdge::lineB.RayIntersect;
		}
		else
		{
			ray2->Direction = TFlipperEdge::lineA.PerpendicularC;
			nextOrigin = &TFlipperEdge::lineA.RayIntersect;
		}
		ray2->Origin = *nextOrigin;
		return distance;
	}
	return 1000000000.0;
}

void maths::RotateVector(vector2& vec, float angle)
{
	float s = sin(angle), c = cos(angle);
	vec.X = c * vec.X - s * vec.Y;
	vec.Y = s * vec.X + c * vec.Y;
	/* Error in the original, should be:
	 * auto newX = c * vec.X - s * vec.Y;
	 * vec.Y = s * vec.X + c * vec.Y;
	 * vec.X = newX;
	 */
	// Original code rotates the point on a figure eight curve.
	// Luckily, it is never used with angle always set to 0.
}

void maths::find_closest_edge(ramp_plane_type* planes, int planeCount, wall_point_type* wall, vector2& lineEnd,
							  vector2& lineStart)
{
	vector2 wallEnd{}, wallStart{};

	wallStart.X = wall->X0;
	wallStart.Y = wall->Y0;
	wallEnd.Y = wall->Y1;
	wallEnd.X = wall->X1;

	float maxDistance = 1000000000.0f;
	for (auto index = 0; index < planeCount; index++)
	{
		auto& plane = planes[index];
		vector2* pointOrder[4] = { &plane.V1, &plane.V2, &plane.V3, &plane.V1 };

		for (auto pt = 0; pt < 3; pt++)
		{
			auto& point1 = *pointOrder[pt], point2 = *pointOrder[pt + 1];

			auto distance = Distance(wallStart, point1) + Distance(wallEnd, point2);
			if (distance < maxDistance)
			{
				maxDistance = distance;
				lineEnd = point1;
				lineStart = point2;
			}
		}
	}
}