/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
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

#ifndef CB2_SETTINGS_H
#define CB2_SETTINGS_H

#include <cinder/Cinder.h>
#include <stddef.h>
#include <assert.h>
#include <float.h>

#define CB2_NOT_USED(x) ((void)(x))
#define cb2Assert(A) assert(A)

#define	cb2_maxFloat		FLT_MAX
#define	cb2_epsilon		FLT_EPSILON
#define cb2_pi			3.14159265359f

/// @file
/// Global tuning constants based on meters-kilograms-seconds (MKS) units.
///

// Collision

/// The maximum number of contact points between two convex shapes. Do
/// not change this value.
#define cb2_maxManifoldPoints	2

/// The maximum number of vertices on a convex polygon. You cannot increase
/// this too much because cb2BlockAllocator has a maximum object size.
#define cb2_maxPolygonVertices	8

/// This is used to fatten AABBs in the dynamic tree. This allows proxies
/// to move by a small amount without triggering a tree adjustment.
/// This is in meters.
#define cb2_aabbExtension		0.1f

/// This is used to fatten AABBs in the dynamic tree. This is used to predict
/// the future position based on the current displacement.
/// This is a dimensionless multiplier.
#define cb2_aabbMultiplier		2.0f

/// A small length used as a collision and constraint tolerance. Usually it is
/// chosen to be numerically significant, but visually insignificant.
#define cb2_linearSlop			0.005f

/// A small angle used as a collision and constraint tolerance. Usually it is
/// chosen to be numerically significant, but visually insignificant.
#define cb2_angularSlop			(2.0f / 180.0f * cb2_pi)

/// The radius of the polygon/edge shape skin. This should not be modified. Making
/// this smaller means polygons will have an insufficient buffer for continuous collision.
/// Making it larger may create artifacts for vertex collision.
#define cb2_polygonRadius		(2.0f * cb2_linearSlop)

/// Maximum number of sub-steps per contact in continuous physics simulation.
#define cb2_maxSubSteps			8


// Dynamics

/// Maximum number of contacts to be handled to solve a TOI impact.
#define cb2_maxTOIContacts			32

/// A velocity threshold for elastic collisions. Any collision with a relative linear
/// velocity below this threshold will be treated as inelastic.
#define cb2_velocityThreshold		1.0f

/// The maximum linear position correction used when solving constraints. This helps to
/// prevent overshoot.
#define cb2_maxLinearCorrection		0.2f

/// The maximum angular position correction used when solving constraints. This helps to
/// prevent overshoot.
#define cb2_maxAngularCorrection		(8.0f / 180.0f * cb2_pi)

/// The maximum linear velocity of a body. This limit is very large and is used
/// to prevent numerical problems. You shouldn't need to adjust this.
#define cb2_maxTranslation			2.0f
#define cb2_maxTranslationSquared	(cb2_maxTranslation * cb2_maxTranslation)

/// The maximum angular velocity of a body. This limit is very large and is used
/// to prevent numerical problems. You shouldn't need to adjust this.
#define cb2_maxRotation				(0.5f * cb2_pi)
#define cb2_maxRotationSquared		(cb2_maxRotation * cb2_maxRotation)

/// This scale factor controls how fast overlap is resolved. Ideally this would be 1 so
/// that overlap is removed in one time step. However using values close to 1 often lead
/// to overshoot.
#define cb2_baumgarte				0.2f
#define cb2_toiBaugarte				0.75f


// Sleep

/// The time that a body must be still before it will go to sleep.
#define cb2_timeToSleep				0.5f

/// A body cannot sleep if its linear velocity is above this tolerance.
#define cb2_linearSleepTolerance		0.01f

/// A body cannot sleep if its angular velocity is above this tolerance.
#define cb2_angularSleepTolerance	(2.0f / 180.0f * cb2_pi)

// Memory Allocation

/// Implement this function to use your own memory allocator.
void* cb2Alloc(int size);

/// If you implement cb2Alloc, you should also implement this function.
void cb2Free(void* mem);

/// Logging function.
void cb2Log(const char* string, ...);

/// Version numbering scheme.
/// See http://en.wikipedia.org/wiki/Software_versioning
struct cb2Version
{
	int major;		///< significant changes
	int minor;		///< incremental changes
	int revision;		///< bug fixes
};

/// Current version.
extern cb2Version cb2_version;

#endif
