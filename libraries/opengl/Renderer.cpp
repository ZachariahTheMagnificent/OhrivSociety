#include "Renderer.h"
#include <stdexcept>

namespace opengl
{
	Renderer::Renderer ( )
	{
		// Needed for core profile
		glewExperimental = true;

		// Initialize GLEW
		const GLenum err = glewInit ( );

		// If GLEW hasn't initialized
		if ( err != GLEW_OK )
		{
			throw std::runtime_error { reinterpret_cast< const char* >( glewGetErrorString ( err ) ) };
		}
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}

	void Renderer::GetViewPort ( GLint ( &view_port ) [ 4 ] )
	{
		glGetIntegerv ( GL_VIEWPORT, view_port );
	}

	void Renderer::SetViewPort ( const GLint bottom_left_x, const GLint bottom_left_y, const GLsizei width, const GLsizei height ) noexcept
	{
		glViewport ( bottom_left_x, bottom_left_y, width, height );
	}

	void Renderer::SetClearColour ( const float r, const float g, const float b, const float a ) noexcept
	{
		glClearColor ( r, g, b, a );
	}

	template<>
	void Renderer::Clear<true> ( ) noexcept
	{
		// Clear colour buffer
		glClear ( GL_COLOR_BUFFER_BIT );
	}

	template<>
	void Renderer::Clear<false, true> ( ) noexcept
	{
		// Clear depth buffer
		glClear ( GL_DEPTH_BUFFER_BIT );
	}

	template<>
	void Renderer::Clear<false, false, true> ( ) noexcept
	{
		// Clear stencil buffer
		glClear ( GL_STENCIL_BUFFER_BIT );
	}

	template<>
	void Renderer::Clear<true, true> ( ) noexcept
	{
		// Clear colour & depth buffer
		glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	template<>
	void Renderer::Clear<true, false, true> ( ) noexcept
	{
		// Clear colour & stencil buffer
		glClear ( GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}

	template<>
	void Renderer::Clear<false, true, true> ( ) noexcept
	{
		// Clear depth & stencil buffer
		glClear ( GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}

	template<>
	void Renderer::Clear<true, true, true> ( ) noexcept
	{
		// Clear color, depth & stencil buffer
		glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	}

	template<>
	void Renderer::Clear<false, false, false> ( ) noexcept
	{
		//Clear nothing. Completely redundant command for completely redundant people
		glClear ( 0x00 );
	}

	template<>
	void Renderer::Enable<Renderer::FEATURE::CULL> ( ) noexcept
	{
		glEnable ( GL_CULL_FACE );
	}

	template<>
	void Renderer::Enable<Renderer::FEATURE::BLENDING> ( ) noexcept
	{
		glEnable ( GL_BLEND );
	}

	template<>
	void Renderer::Enable<Renderer::FEATURE::DEPTH> ( ) noexcept
	{
		glEnable ( GL_DEPTH_TEST );
	}

	template<>
	void Renderer::Enable<Renderer::FEATURE::STENCIL> ( ) noexcept
	{
		glEnable ( GL_STENCIL_TEST );
	}

	template<>
	void Renderer::Disable<Renderer::FEATURE::CULL> ( ) noexcept
	{
		glDisable ( GL_CULL_FACE );
	}

	template<>
	void Renderer::Disable<Renderer::FEATURE::BLENDING> ( ) noexcept
	{
		glDisable ( GL_BLEND );
	}

	template<>
	void Renderer::Disable<Renderer::FEATURE::DEPTH> ( ) noexcept
	{
		glDisable ( GL_DEPTH_TEST );
	}

	template<>
	void Renderer::Disable<Renderer::FEATURE::STENCIL> ( ) noexcept
	{
		glDisable ( GL_STENCIL_TEST );
	}

	void Renderer::SetPolygonMode ( const FACE_SIDE side, const POLYGON_MODE mode ) noexcept
	{
		glPolygonMode ( static_cast< GLenum >( side ), static_cast< GLenum >( mode ) );
	}

	void Renderer::WriteToColour ( const bool r, const bool g, const bool b, const bool a ) noexcept
	{
		glColorMask ( r, g, b, a );
	}

	void Renderer::WriteToDepth ( const bool depth ) noexcept
	{
		glDepthMask ( depth );
	}

	void Renderer::WriteToStencil ( const GLuint mask ) noexcept
	{
		glStencilMask ( mask );
	}

	template<>
	void Renderer::SetWriteToStencilOutcome<Renderer::FACE_SIDE::FRONT> ( const STENCIL_OUTCOME fail_stencil, const STENCIL_OUTCOME pass_stencil_fail_depth, const STENCIL_OUTCOME pass_stencil_depth ) noexcept
	{
		glStencilOpSeparate ( GL_FRONT, static_cast< GLenum >( fail_stencil ), static_cast< GLenum >( pass_stencil_fail_depth ), static_cast< GLenum >( pass_stencil_depth ) );
	}

	template<>
	void Renderer::SetWriteToStencilOutcome<Renderer::FACE_SIDE::BACK> ( const STENCIL_OUTCOME fail_stencil, const STENCIL_OUTCOME pass_stencil_fail_depth, const STENCIL_OUTCOME pass_stencil_depth ) noexcept
	{
		glStencilOpSeparate ( GL_BACK, static_cast< GLenum >( fail_stencil ), static_cast< GLenum >( pass_stencil_fail_depth ), static_cast< GLenum >( pass_stencil_depth ) );
	}

	template<>
	void Renderer::SetWriteToStencilOutcome<Renderer::FACE_SIDE::FRONT_AND_BACK> ( const STENCIL_OUTCOME fail_stencil, const STENCIL_OUTCOME pass_stencil_fail_depth, const STENCIL_OUTCOME pass_stencil_depth ) noexcept
	{
		glStencilOp ( static_cast< GLenum >( fail_stencil ), static_cast< GLenum >( pass_stencil_fail_depth ), static_cast< GLenum >( pass_stencil_depth ) );
	}

	void Renderer::SetDepthComparison ( const COMPARISON comparison ) noexcept
	{
		glDepthFunc ( static_cast< GLenum >( comparison ) );
	}

	void Renderer::SetStencilComparison ( const COMPARISON comparison, const GLint value, const GLuint mask ) noexcept
	{
		glStencilFunc ( static_cast< GLenum >( comparison ), value, mask );
	}
}