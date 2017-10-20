#pragma once
#include "opengl\Window.h"
#include "Shader2D.h"
#include "Game.h"
#include "Obj.h"
#include "opengl\Texture.h"

using Vector3 = Mesh::Vector3;

struct Ray
{
	Vector3 o, d;
	Ray ( const Vector3& o, const Vector3& d ) : o ( o ), d ( d )
	{
	}
};

struct Sphere
{
	Vector3 c;
	float r;
	Sphere ( const Vector3& c, float r ) : c ( c ), r ( r )
	{
	}
	Vector3 getNormal ( const Vector3& pi ) const
	{
		return ( pi - c ) / r;
	}
	bool intersect ( const Ray& ray, float &t ) const
	{
		const Vector3 o = ray.o;
		const Vector3 d = ray.d;
		const Vector3 oc = o - c;
		const float b = 2 * oc.Dot ( d );
		const float c = oc.Dot ( oc ) - r*r;
		float disc = b*b - 4 * c;
		if ( disc < 1e-4 ) return false;
		disc = sqrt ( disc );
		const float t0 = -b - disc;
		const float t1 = -b + disc;
		t = ( t0 < t1 ) ? t0 : t1;
		return true;
	}
};

Vector3 clamp255 ( const Vector3 col )
{
	return Vector3 {
		( col.X ( ) > 255 ) ? 255 : ( col.X ( ) < 0 ) ? 0 : col.X ( ),
		( col.Y ( ) > 255 ) ? 255 : ( col.Y ( ) < 0 ) ? 0 : col.Y ( ),
		( col.Z ( ) > 255 ) ? 255 : ( col.Z ( ) < 0 ) ? 0 : col.Z ( ) };
}

class RayTracingWindow : public opengl::Window
{
public:
	RayTracingWindow ( ) : opengl::Window { "Graphics", 800, 600, false }, screen_pixels_ ( W * H )
	{
		renderer_.SetClearColor ( 0.f, 0.f, 1.f, 0.25f );
		screen_mesh_.Bind ( );
		opengl::Texture::SetActiveSlot ( 0 );
		screen_texture_.Bind ( );
	}
	~RayTracingWindow ( )
	{
		Window::MakeContextCurrent ( );
	}

	RayTracingWindow ( const RayTracingWindow& ) = delete;
	RayTracingWindow& operator=( const RayTracingWindow& ) = delete;

	void Update ( )
	{
		MakeContextCurrent ( );
		renderer_.Clear ( );

		const Vector3 white ( 255, 255, 255 );
		const Vector3 black ( 0, 0, 0 );
		const Vector3 red ( 255, 0, 0 );

		const Sphere sphere ( Vector3 ( W*0.5, H*0.5, 50 ), 50 * M );
		const Sphere light ( Vector3 ( 0, 0, 50 ), 1 );

		float t;
		Vector3 pix_col ( black );

		for ( int y = 0; y < H; ++y )
		{
			for ( int x = 0; x < W; ++x )
			{
				pix_col = black;

				const Ray ray ( Vector3 ( static_cast< float >( x ), static_cast< float >( y ), 0.f ), Vector3 ( 0.f, 0.f, 1.f ) );
				if ( sphere.intersect ( ray, t ) )
				{
					const Vector3 pi = ray.o + ray.d*t;
					const Vector3 L = light.c - pi;
					const Vector3 N = sphere.getNormal ( pi );
					const float dt = L.Normalized ( ).Dot ( N.Normalized ( ) );

					pix_col = ( red + white*dt ) * 0.5;
					pix_col = clamp255 ( pix_col );
				}
				screen_pixels_ [ x + y * W ] = opengl::Pixel { static_cast< GLubyte >( pix_col.X ( ) ), static_cast< GLubyte >( pix_col.Y ( ) ), static_cast< GLubyte >( pix_col.Z ( ) ) };
			}
		}

		opengl::Texture::Fill ( W, H, screen_pixels_ );
		screen_mesh_.Render ( );
		SwapBuffers ( );
	}

private:
	static constexpr std::size_t M = 4;
	static constexpr std::size_t W = 800 * M;
	static constexpr std::size_t H = 600 * M;

	Obj screen_mesh_ { "objs\\quad.obj" };
	std::vector<opengl::Pixel> screen_pixels_;
	opengl::Texture screen_texture_;
	Shader2D shader_;
};