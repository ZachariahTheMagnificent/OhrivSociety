#pragma once
#include <math\Vector3.h>
#include <math\Matrix4x4.h>
#include <math\Rotation.h>
#include "FirstPersonCamera.h"
#include <random>

class Body
{
public:
	using Float = float;
	using Vector3 = math::Vector3<Float>;

	class Force
	{
	protected:
		static void ApplyForce ( Body& body, const Vector3 force ) noexcept
		{
			body.accumulated_force_ += force;
		}
	};

	Body ( ) = default;
	Body ( const Vector3 position, const Vector3 velocity, const Float inverse_mass ) noexcept : position_ { position }, velocity_ { velocity }, inverse_mass_ { inverse_mass }, accumulated_force_ { }
	{

	}

	Vector3 Update ( const float delta_time ) noexcept
	{
		const Vector3 acceleration = accumulated_force_ * inverse_mass_;

		velocity_ += acceleration * delta_time;
		position_ += velocity_ * delta_time;

		accumulated_force_ = Vector3 { };

		return position_;
	}

	Vector3 GetPosition ( ) const noexcept
	{
		return position_;
	}
	Vector3 GetVelocity ( ) const noexcept
	{
		return velocity_;
	}
	bool HasInfiniteMass ( ) const noexcept
	{
		return inverse_mass_ == 0;
	}
	float GetMass ( ) const noexcept
	{
		return 1 / inverse_mass_;
	}

private:
	Vector3 position_ { };
	Vector3 velocity_ { };
	Float inverse_mass_ { };
	Vector3 accumulated_force_ { };
};

class Gravity : private Body::Force
{
public:
	using Float = Body::Float;
	using Vector3 = Body::Vector3;

	Gravity ( ) = default;
	Gravity ( const Vector3 acceleration_due_to_gravity ) noexcept : acceleration_due_to_gravity_ { acceleration_due_to_gravity }
	{

	}

	void ApplyTo ( Body& body ) const noexcept
	{
		if ( !body.HasInfiniteMass ( ) )
		{
			const Float mass = body.GetMass ( );
			ApplyForce ( body, acceleration_due_to_gravity_ * mass );
		}
	}

private:
	Vector3 acceleration_due_to_gravity_;
};

class Spring : private Body::Force
{
public:
	using Float = Body::Float;
	using Vector3 = Body::Vector3;

	Spring ( ) = default;
	Spring ( Body*const body1, Body*const body2, const Float rest_length, const Float constant ) noexcept : body1_ { body1 }, body2_ { body2 }, rest_length_ { rest_length }, constant_ { constant }
	{

	}

	void Update ( ) const noexcept
	{
		const Vector3 body1_to_body2 = body2_->GetPosition ( ) - body1_->GetPosition ( );
		const Float distance = body1_to_body2.Length ( );
		const Vector3 body1_to_body2_direction = body1_to_body2 / distance;
		const Float stretch = distance - rest_length_;

		ApplyForce ( *body1_, body1_to_body2_direction * stretch * constant_ );
		ApplyForce ( *body2_, -body1_to_body2_direction * stretch * constant_ );
	}

private:
	Body* body1_ { };
	Body* body2_ { };
	Float rest_length_ { };
	Float constant_ { };
};

class Game
{
public:
	using Vector3 = Body::Vector3;
	using Normal = Vector3::Normal;
	using Rotation = math::Rotation<float>;
	using Matrix = math::Matrix<float>;
	using FirstPersonCamera = FirstPersonCamera<float>;

	template<class Derived>
	class Renderer
	{
	public:
		void Render ( const Game& game )
		{
			Derived& derived = *static_cast< Derived* >( this );

			derived.SetCamera ( game.camera_ );
			derived.UpdateSprite ( game.delta_time_ );
		}
	};

	//template<class Derived>
	class InputManager
	{
	public:
		template<bool SET_VALUE>
		static void OnMoveUp ( Game& game )
		{
			game.move_up_ = SET_VALUE;
		}
		template<bool SET_VALUE>
		static void OnMoveDown ( Game& game )
		{
			game.move_down_ = SET_VALUE;
		}
		template<bool SET_VALUE>
		static void OnMoveLeft ( Game& game )
		{
			game.move_left_ = SET_VALUE;
		}
		template<bool SET_VALUE>
		static void OnMoveRight ( Game& game )
		{
			game.move_right_ = SET_VALUE;
		}
		static void OnRotateCamera ( Game& game, const float yaw, const float pitch )
		{
			game.camera_.Rotate ( yaw, pitch );
		}
	};

	void Update ( const float delta_time )
	{
		delta_time_ = delta_time;

		Vector3 velocity { };
		static constexpr float speed = 5.f;

		if ( move_up_ )
		{
			velocity += static_cast< Vector3 >( camera_.GetView ( ) );
		}
		if ( move_down_ )
		{
			velocity += static_cast< Vector3 >( -camera_.GetView ( ) );
		}
		if ( move_left_ )
		{
			velocity += static_cast< Vector3 >( camera_.GetLeft ( ) );
		}
		if ( move_right_ )
		{
			velocity += static_cast< Vector3 >( camera_.GetRight ( ) );
		}

		if ( !velocity.IsZero ( ) )
		{
			const Vector3 delta_position = velocity.Normalized ( ) * speed * delta_time;

			camera_.Move ( delta_position );
		}

		std::random_device r;
		std::mt19937 f ( r ( ) );
		std::uniform_real_distribution<float> d ( -1000, 1000 );
		std::uniform_real_distribution<float> d2 ( 1000, 2000 );

		for ( auto& particle : particles_ )
		{
			particle += Vector3 { 0, -100, 0 } *delta_time;
			if ( particle.Y() <= 0 )
			{

				particle = Vector3 { d ( f ), d2 ( f ), d ( f ) };
			}
		}
	}

	std::vector<Vector3> particles_ { 10000 };

private:
	float delta_time_;
	FirstPersonCamera camera_;
	bool move_up_;
	bool move_down_;
	bool move_left_;
	bool move_right_;
};