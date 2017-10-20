#pragma once
#include <opengl\VertexArray.h>
#include <opengl\VertexBuffer.h>
#include <opengl\IndexBuffer.h>
#include <array>

class Sprite
{
public:
	class Instance
	{
	public:
		Instance ( const std::size_t total_frames, const std::size_t frame_per_second ) noexcept;
		
		void Update ( const float delta_time ) noexcept;
		void Reset ( ) noexcept;

		std::size_t GetCurrentFrame ( ) const noexcept;

	private:
		GLuint total_frames_ { };
		GLfloat total_time_before_next_frame_ { };
		GLuint current_frame_ { };
		GLfloat time_until_next_frame_ { };
	};

	explicit Sprite ( const std::size_t rows, const std::size_t columns, const std::size_t frame_per_second );

	Sprite ( const Sprite& ) = delete;
	Sprite& operator=( const Sprite& ) = delete;

	Sprite ( Sprite&& ) = default;
	Sprite& operator=( Sprite&& ) = default;

	Instance GetInstance ( ) const noexcept;

	void BindVertex ( ) noexcept;
	void BindIndex ( ) noexcept;

	static void SetPosition ( const GLuint position_id ) noexcept;
	static void SetUv ( const GLuint uv_id ) noexcept;

	void Render ( const Instance& instance ) noexcept;

private:
	struct Vertex
	{
		std::array<GLfloat, 3> position;
		std::array<GLfloat, 2> uv;
	};
	
	opengl::VertexBuffer vertex_buffer_;
	opengl::IndexBuffer index_buffer_;

	GLuint total_frames_;
	GLuint frame_per_second_;
};