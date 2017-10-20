#pragma once
#include "math\Spline.h"
#include <vector>
#include <string>
#include <fstream>
#include <opengl\VertexArray.h>
#include <opengl\VertexBuffer.h>
#include <opengl\IndexBuffer.h>
#include <opengl\Texture.h>
#include <array>
#include <data_structure\OffsetOf.h>
#include <math\Vector3.h>

class Terrain
{
public:
	using Vector3 = math::Vector3<float>;

	class HeightMap
	{
	public:
		HeightMap ( ) = default;
		HeightMap ( const std::string& file_path );

		float Read ( const float x, const float z ) const;
		std::vector<float> Read ( const std::size_t size_x, const std::size_t size_z ) const;

		std::size_t Length ( ) const noexcept;

	private:
		std::vector<tk::spline> splines_;
		std::size_t size_ { };
	};

	explicit Terrain ( const std::string& file_path, const unsigned resolution, const float height_multiplier );

	Terrain ( const Terrain& ) = delete;
	Terrain& operator=( const Terrain& ) = delete;

	Terrain ( Terrain&& ) = default;
	Terrain& operator=( Terrain&& ) = default;

	HeightMap& GetHeightMap ( ) noexcept;
	const HeightMap& GetHeightMap ( ) const noexcept;

	void BindVertex ( ) noexcept;
	void BindIndex ( ) noexcept;

	static void SetPosition ( const GLuint position_id ) noexcept;
	static void SetNormal ( const GLuint normal_id ) noexcept;
	static void SetUv ( const GLuint uv_id ) noexcept;

	void Render ( );

private:
	struct Vertex
	{
		std::array<GLfloat, 3> position;
		std::array<GLfloat, 3> normal;
		std::array<GLfloat, 2> uv;
	};

	opengl::VertexBuffer vertex_buffer_;
	opengl::IndexBuffer index_buffer_;

	HeightMap height_map_;
	GLuint num_indices_;
};