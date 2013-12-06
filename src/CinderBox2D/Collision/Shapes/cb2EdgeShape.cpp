/*
* Copyright (c) 2006-2010 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include <CinderBox2D/Collision/Shapes/cb2EdgeShape.h>
#include <new>
using namespace std;

void b2EdgeShape::set(const ci::Vec2f& v1, const ci::Vec2f& v2)
{
	m_vertex1 = v1;
	m_vertex2 = v2;
	m_hasVertex0 = false;
	m_hasVertex3 = false;
}

b2Shape* b2EdgeShape::Clone(b2BlockAllocator* allocator) const
{
	void* mem = allocator->Allocate(sizeof(b2EdgeShape));
	b2EdgeShape* clone = new (mem) b2EdgeShape;
	*clone = *this;
	return clone;
}

int b2EdgeShape::GetChildCount() const
{
	return 1;
}

bool b2EdgeShape::TestPoint(const b2Transform& xf, const ci::Vec2f& p) const
{
	B2_NOT_USED(xf);
	B2_NOT_USED(p);
	return false;
}

// p = p1 + t * d
// v = v1 + s * e
// p1 + t * d = v1 + s * e
// s * e - t * d = p1 - v1
bool b2EdgeShape::RayCast(b2RayCastOutput* output, const b2RayCastInput& input,
							const b2Transform& xf, int childIndex) const
{
	B2_NOT_USED(childIndex);

	// Put the ray into the edge's frame of reference.
	ci::Vec2f p1 = b2MulT(xf.q, input.p1 - xf.p);
	ci::Vec2f p2 = b2MulT(xf.q, input.p2 - xf.p);
	ci::Vec2f d = p2 - p1;

	ci::Vec2f v1 = m_vertex1;
	ci::Vec2f v2 = m_vertex2;
	ci::Vec2f e = v2 - v1;
	ci::Vec2f normal(e.y, -e.x);
	normal.normalize();

	// q = p1 + t * d
	// dot(normal, q - v1) = 0
	// dot(normal, p1 - v1) + t * dot(normal, d) = 0
	float numerator = b2Dot(normal, v1 - p1);
	float denominator = b2Dot(normal, d);

	if (denominator == 0.0f)
	{
		return false;
	}

	float t = numerator / denominator;
	if (t < 0.0f || input.maxFraction < t)
	{
		return false;
	}

	ci::Vec2f q = p1 + t * d;

	// q = v1 + s * r
	// s = dot(q - v1, r) / dot(r, r)
	ci::Vec2f r = v2 - v1;
	float rr = b2Dot(r, r);
	if (rr == 0.0f)
	{
		return false;
	}

	float s = b2Dot(q - v1, r) / rr;
	if (s < 0.0f || 1.0f < s)
	{
		return false;
	}

	output->fraction = t;
	if (numerator > 0.0f)
	{
		output->normal = -normal;
	}
	else
	{
		output->normal = normal;
	}
	return true;
}

void b2EdgeShape::ComputeAABB(b2AABB* aabb, const b2Transform& xf, int childIndex) const
{
	B2_NOT_USED(childIndex);

	ci::Vec2f v1 = b2Mul(xf, m_vertex1);
	ci::Vec2f v2 = b2Mul(xf, m_vertex2);

	ci::Vec2f lower = b2Min(v1, v2);
	ci::Vec2f upper = b2Max(v1, v2);

	ci::Vec2f r(m_radius, m_radius);
	aabb->lowerBound = lower - r;
	aabb->upperBound = upper + r;
}

void b2EdgeShape::ComputeMass(b2MassData* massData, float density) const
{
	B2_NOT_USED(density);

	massData->mass = 0.0f;
	massData->center = 0.5f * (m_vertex1 + m_vertex2);
	massData->I = 0.0f;
}
