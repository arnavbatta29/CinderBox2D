/*
* Copyright (c) 2006-2012 Erin Catto http://www.box2d.org
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

#ifndef CB2_MOTOR_JOINT_H
#define CB2_MOTOR_JOINT_H

#include <CinderBox2D/Dynamics/Joints/cb2Joint.h>

/// Motor joint definition.
struct cb2MotorJointDef : public cb2JointDef
{
	cb2MotorJointDef()
	{
		type = e_motorJoint;
		angularOffset = 0.0f;
		maxForce = 1.0f;
		maxTorque = 1.0f;
		correctionFactor = 0.3f;
	}

	/// Initialize the bodies and offsets using the current transforms.
	void Initialize(cb2Body* bodyA, cb2Body* bodyB);

	/// Position of bodyB minus the position of bodyA, in bodyA's frame, in meters.
	ci::Vec2f linearOffset;

	/// The bodyB angle minus bodyA angle in radians.
	float angularOffset;
	
	/// The maximum motor force in N.
	float maxForce;

	/// The maximum motor torque in N-m.
	float maxTorque;

	/// Position correction factor in the range [0,1].
	float correctionFactor;
};

/// A motor joint is used to control the relative motion
/// between two bodies. A typical usage is to control the movement
/// of a dynamic body with respect to the ground.
class cb2MotorJoint : public cb2Joint
{
public:
	ci::Vec2f GetAnchorA() const;
	ci::Vec2f GetAnchorB() const;

	ci::Vec2f GetReactionForce(float inv_dt) const;
	float GetReactionTorque(float inv_dt) const;

	/// Set/get the target linear offset, in frame A, in meters.
	void SetLinearOffset(const ci::Vec2f& linearOffset);
	const ci::Vec2f& GetLinearOffset() const;

	/// Set/get the target angular offset, in radians.
	void SetAngularOffset(float angularOffset);
	float GetAngularOffset() const;

	/// Set the maximum friction force in N.
	void SetMaxForce(float force);

	/// Get the maximum friction force in N.
	float GetMaxForce() const;

	/// Set the maximum friction torque in N*m.
	void SetMaxTorque(float torque);

	/// Get the maximum friction torque in N*m.
	float GetMaxTorque() const;

	/// Set the position correction factor in the range [0,1].
	void SetCorrectionFactor(float factor);

	/// Get the position correction factor in the range [0,1].
	float GetCorrectionFactor() const;

	/// Dump to cb2Log
	void Dump();

protected:

	friend class cb2Joint;

	cb2MotorJoint(const cb2MotorJointDef* def);

	void InitVelocityConstraints(const cb2SolverData& data);
	void SolveVelocityConstraints(const cb2SolverData& data);
	bool SolvePositionConstraints(const cb2SolverData& data);

	// Solver shared
	ci::Vec2f m_linearOffset;
	float m_angularOffset;
	ci::Vec2f m_linearImpulse;
	float m_angularImpulse;
	float m_maxForce;
	float m_maxTorque;
	float m_correctionFactor;

	// Solver temp
	int m_indexA;
	int m_indexB;
	ci::Vec2f m_rA;
	ci::Vec2f m_rB;
	ci::Vec2f m_localCenterA;
	ci::Vec2f m_localCenterB;
	ci::Vec2f m_linearError;
	float m_angularError;
	float m_invMassA;
	float m_invMassB;
	float m_invIA;
	float m_invIB;
  ci::Matrix22f m_linearMass;
	float m_angularMass;
};

#endif
