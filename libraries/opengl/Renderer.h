#pragma once
#include <glew/glew.h>

namespace opengl
{
	class Renderer
	{
	public:
		enum class FEATURE
		{
			CULL,
			BLENDING,
			DEPTH,
			STENCIL
		};

		enum class POLYGON_MODE : GLenum
		{
			POINT = GL_POINT,
			LINE = GL_LINE,
			FILL = GL_FILL
		};

		enum class COMPARISON : GLenum
		{
			NEVER_TRUE = GL_NEVER,
			LESS = GL_LESS,
			LESS_OR_EQUAL = GL_LEQUAL,
			GREATER = GL_GREATER,
			GREATER_OR_EQUAL = GL_GEQUAL,
			EQUAL = GL_EQUAL,
			NOT_EQUAL = GL_NOTEQUAL,
			ALWAYS_PASS = GL_ALWAYS
		};

		enum class STENCIL_OUTCOME : GLenum
		{
			KEEP = GL_KEEP,
			SET_ZERO = GL_ZERO,
			REPLACE = GL_REPLACE,
			INCREMENT_CLAMP = GL_INCR,
			INCREMENT_WRAP = GL_INCR_WRAP,
			DECREMENT_CLAMP = GL_DECR,
			DECREMENT_WRAP = GL_DECR_WRAP,
			INVERT = GL_INVERT
		};

		enum class FACE_SIDE
		{
			FRONT,
			BACK,
			FRONT_AND_BACK
		};

		Renderer ( );

		Renderer ( const Renderer& ) = delete;
		Renderer& operator=( const Renderer& ) = delete;

		Renderer ( Renderer&& ) = default;
		Renderer& operator=( Renderer&& ) = default;

	protected:
		void GetViewPort ( GLint ( &view_port ) [ 4 ] );
		void SetViewPort ( const GLint bottom_left_x, const GLint bottom_left_y, const GLsizei width, const GLsizei height ) noexcept;

		void SetClearColour ( const float r, const float g, const float b, const float a ) noexcept;
		template<bool colour = false, bool depth = false, const bool stencil = false>
		void Clear ( ) noexcept;

		template<FEATURE feature>
		void Enable ( ) noexcept;
		template<FEATURE feature>
		void Disable ( ) noexcept;

		void SetPolygonMode ( const FACE_SIDE side, const POLYGON_MODE mode ) noexcept;

		void WriteToColour ( const bool r, const bool g, const bool b, const bool a ) noexcept;
		void WriteToDepth ( const bool depth ) noexcept;
		void WriteToStencil ( const GLuint mask ) noexcept;

		template<FACE_SIDE side>
		void SetWriteToStencilOutcome ( const STENCIL_OUTCOME fail_stencil, const STENCIL_OUTCOME pass_stencil_fail_depth, const STENCIL_OUTCOME pass_stencil_depth ) noexcept;

		void SetDepthComparison ( const COMPARISON comparison ) noexcept;
		void SetStencilComparison ( const COMPARISON comparison, const GLint value, const GLuint mask ) noexcept;
	};
}