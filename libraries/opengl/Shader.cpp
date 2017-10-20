#include "Shader.h"
#include <iostream>
#include <fstream>
#include <cstdint>

namespace opengl
{
	bool Shader::Initialized ( ) const noexcept
	{
		return bool { handle_ };
	}

	void Shader::Use ( ) const noexcept
	{
		return glUseProgram ( handle_.get ( ) );
	}

	Shader::Shader ( const std::string& vertex_shader, const std::string& fragment_shader ) : handle_ ( LoadShaders ( vertex_shader, fragment_shader ) )
	{
	}

	/******************************************************************************/
	/*!
	\brief
	Return the id of the uniform in the shaders.

	\param uniformName
	The name of the uniform in the shaders.

	\return
	The id of the uniform.

	*/
	/******************************************************************************/
	Shader::UniformId Shader::GetUniformId ( const std::string& uniform_name ) const noexcept
	{
		return glGetUniformLocation ( handle_.get ( ), uniform_name.c_str ( ) );
	}

	//Updating Uniforms (Wow, this is gonna be long...)

	//Integers
	void Shader::Update ( const Uniform<GLint>& uniform ) noexcept
	{
		glUniform1i ( uniform.GetId ( ), *uniform );
	}

	void Shader::Update ( const Uniform<IntVec2>& uniform ) noexcept
	{
		glUniform2i ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data ( ) [ 1 ] );
	}

	void Shader::Update ( const Uniform<IntVec3>& uniform ) noexcept
	{
		glUniform3i ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data ( ) [ 1 ], uniform->data ( ) [ 2 ] );
	}

	void Shader::Update ( const Uniform<IntVec4>& uniform ) noexcept
	{
		glUniform4i ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ], uniform->data() [ 2 ], uniform->data() [ 3 ] );
	}

	void Shader::Update ( const UniformArray<GLint>& uniform_array ) noexcept
	{
		glUniform1iv ( uniform_array.GetId ( ), uniform_array.size ( ), &*uniform_array.begin ( ) );
	}

	void Shader::Update ( const UniformArray<IntVec2>& uniform_array ) noexcept
	{
		glUniform2iv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<IntVec3>& uniform_array ) noexcept
	{
		glUniform3iv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<IntVec4>& uniform_array ) noexcept
	{
		glUniform4iv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	//Unsigned Integers
	void Shader::Update ( const Uniform<GLuint>& uniform ) noexcept
	{
		glUniform1ui ( uniform.GetId ( ), *uniform );
	}

	void Shader::Update ( const Uniform<UIntVec2>& uniform ) noexcept
	{
		glUniform2ui ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ] );
	}

	void Shader::Update ( const Uniform<UIntVec3>& uniform ) noexcept
	{
		glUniform3ui ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ], uniform->data() [ 2 ] );
	}

	void Shader::Update ( const Uniform<UIntVec4>& uniform ) noexcept
	{
		glUniform4ui ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ], uniform->data() [ 2 ], uniform->data() [ 3 ] );
	}
	
	void Shader::Update ( const UniformArray<GLuint>& uniform_array ) noexcept
	{
		glUniform1uiv ( uniform_array.GetId ( ), uniform_array.size ( ), &*uniform_array.begin ( ) );
	}

	void Shader::Update ( const UniformArray<UIntVec2>& uniform_array ) noexcept
	{
		glUniform2uiv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<UIntVec3>& uniform_array ) noexcept
	{
		glUniform3uiv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<UIntVec4>& uniform_array ) noexcept
	{
		glUniform4uiv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	//Floats
	void Shader::Update ( const Uniform<GLfloat>& uniform ) noexcept
	{
		glUniform1f ( uniform.GetId ( ), *uniform );
	}

	void Shader::Update ( const Uniform<FloatVec2>& uniform ) noexcept
	{
		glUniform2f ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ] );
	}

	void Shader::Update ( const Uniform<FloatVec3>& uniform ) noexcept
	{
		glUniform3f ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ], uniform->data() [ 2 ] );
	}

	void Shader::Update ( const Uniform<FloatVec4>& uniform ) noexcept
	{
		glUniform4f ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ], uniform->data() [ 2 ], uniform->data() [ 3 ] );
	}

	void Shader::Update ( const Uniform<FloatMat2x2>& uniform ) noexcept
	{
		glUniformMatrix2fv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<FloatMat2x3>& uniform ) noexcept
	{
		glUniformMatrix2x3fv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<FloatMat2x4>& uniform ) noexcept
	{
		glUniformMatrix2x4fv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<FloatMat3x2>& uniform ) noexcept
	{
		glUniformMatrix3x2fv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<FloatMat3x3>& uniform ) noexcept
	{
		glUniformMatrix3fv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<FloatMat3x4>& uniform ) noexcept
	{
		glUniformMatrix3x4fv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<FloatMat4x2>& uniform ) noexcept
	{
		glUniformMatrix4x2fv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<FloatMat4x3>& uniform ) noexcept
	{
		glUniformMatrix4x3fv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<FloatMat4x4>& uniform ) noexcept
	{
		glUniformMatrix4fv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const UniformArray<GLfloat>& uniform_array ) noexcept
	{
		glUniform1fv ( uniform_array.GetId ( ), uniform_array.size ( ), &*uniform_array.begin ( ) );
	}

	void Shader::Update ( const UniformArray<FloatVec2>& uniform_array ) noexcept
	{
		glUniform2fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatVec3>& uniform_array ) noexcept
	{
		glUniform3fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatVec4>& uniform_array ) noexcept
	{
		glUniform4fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatMat2x2>& uniform_array ) noexcept
	{
		glUniformMatrix2fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatMat2x3>& uniform_array ) noexcept
	{
		glUniformMatrix2x3fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatMat2x4>& uniform_array ) noexcept
	{
		glUniformMatrix2x4fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatMat3x2>& uniform_array ) noexcept
	{
		glUniformMatrix3x2fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatMat3x3>& uniform_array ) noexcept
	{
		glUniformMatrix3fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatMat3x4>& uniform_array ) noexcept
	{
		glUniformMatrix3x4fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatMat4x2>& uniform_array ) noexcept
	{
		glUniformMatrix4x2fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatMat4x3>& uniform_array ) noexcept
	{
		glUniformMatrix4x3fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<FloatMat4x4>& uniform_array ) noexcept
	{
		glUniformMatrix4fv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	//Doubles
	void Shader::Update ( const Uniform<GLdouble>& uniform ) noexcept
	{
		glUniform1d ( uniform.GetId ( ), *uniform );
	}

	void Shader::Update ( const Uniform<DoubleVec2>& uniform ) noexcept
	{
		glUniform2d ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ] );
	}

	void Shader::Update ( const Uniform<DoubleVec3>& uniform ) noexcept
	{
		glUniform3d ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ], uniform->data() [ 2 ] );
	}

	void Shader::Update ( const Uniform<DoubleVec4>& uniform ) noexcept
	{
		glUniform4d ( uniform.GetId ( ), uniform->data() [ 0 ], uniform->data() [ 1 ], uniform->data() [ 2 ], uniform->data() [ 3 ] );
	}

	void Shader::Update ( const Uniform<DoubleMat2x2>& uniform ) noexcept
	{
		glUniformMatrix2dv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<DoubleMat2x3>& uniform ) noexcept
	{
		glUniformMatrix2x3dv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<DoubleMat2x4>& uniform ) noexcept
	{
		glUniformMatrix2x4dv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<DoubleMat3x2>& uniform ) noexcept
	{
		glUniformMatrix3x2dv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<DoubleMat3x3>& uniform ) noexcept
	{
		glUniformMatrix3dv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<DoubleMat3x4>& uniform ) noexcept
	{
		glUniformMatrix3x4dv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<DoubleMat4x2>& uniform ) noexcept
	{
		glUniformMatrix4x2dv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<DoubleMat4x3>& uniform ) noexcept
	{
		glUniformMatrix4x3dv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const Uniform<DoubleMat4x4>& uniform ) noexcept
	{
		glUniformMatrix4dv ( uniform.GetId ( ), 1, uniform.GetTranspose ( ), uniform->data() );
	}

	void Shader::Update ( const UniformArray<GLdouble>& uniform_array ) noexcept
	{
		glUniform1dv ( uniform_array.GetId ( ), uniform_array.size ( ), &*uniform_array.begin ( ) );
	}

	void Shader::Update ( const UniformArray<DoubleVec2>& uniform_array ) noexcept
	{
		glUniform2dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleVec3>& uniform_array ) noexcept
	{
		glUniform3dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleVec4>& uniform_array ) noexcept
	{
		glUniform4dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleMat2x2>& uniform_array ) noexcept
	{
		glUniformMatrix2dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleMat2x3>& uniform_array ) noexcept
	{
		glUniformMatrix2x3dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleMat2x4>& uniform_array ) noexcept
	{
		glUniformMatrix2x4dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleMat3x2>& uniform_array ) noexcept
	{
		glUniformMatrix3x2dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleMat3x3>& uniform_array ) noexcept
	{
		glUniformMatrix3dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleMat3x4>& uniform_array ) noexcept
	{
		glUniformMatrix3x4dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleMat4x2>& uniform_array ) noexcept
	{
		glUniformMatrix4x2dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleMat4x3>& uniform_array ) noexcept
	{
		glUniformMatrix4x3dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	void Shader::Update ( const UniformArray<DoubleMat4x4>& uniform_array ) noexcept
	{
		glUniformMatrix4dv ( uniform_array.GetId ( ), uniform_array.size ( ), uniform_array.GetTranspose ( ), uniform_array.begin ( )->data() );
	}

	Shader::ProgramId Shader::LoadShaders ( const std::string& vertex_file_path, const std::string& fragment_file_path )
	{
		// Create the shaders
		GLuint vertex_shader_id = glCreateShader ( GL_VERTEX_SHADER );
		GLuint fragment_shader_id = glCreateShader ( GL_FRAGMENT_SHADER );

		// Read the Vertex Shader code from the file
		std::string vertex_shader_code;
		std::ifstream vertex_shader_stream { vertex_file_path };

		if ( vertex_shader_stream.is_open ( ) )
		{
			std::string line;

			while ( getline ( vertex_shader_stream, line ) )
			{
				vertex_shader_code += "\n" + line;
			}

			vertex_shader_stream.close ( );
		}
		else
		{
			throw std::runtime_error { ( "Impossible to open " + vertex_file_path + ". Are you in the right directory? Don't forget to read the FAQ!" ).c_str ( ) };
		}

		// Read the Fragment Shader code from the file
		std::string fragment_shader_code;
		std::ifstream fragment_shader_stream { fragment_file_path };

		if ( fragment_shader_stream.is_open ( ) )
		{
			std::string line;

			while ( getline ( fragment_shader_stream, line ) )
			{
				fragment_shader_code += "\n" + line;
			}

			fragment_shader_stream.close ( );
		}
		else
		{
			throw std::runtime_error { ( "Impossible to open " + fragment_file_path + ". Are you in the right directory? Don't forget to read the FAQ!" ).c_str ( ) };
		}

		// Compile Vertex Shader
		std::cout << "Compiling shader: " << vertex_file_path.c_str ( ) << std::endl;

		const char*const vertex_source_pointer = vertex_shader_code.c_str ( );
		glShaderSource ( vertex_shader_id, 1, &vertex_source_pointer, nullptr );
		glCompileShader ( vertex_shader_id );

		// Check Vertex Shader
		{
			GLint success = GL_FALSE;
			glGetShaderiv ( vertex_shader_id, GL_COMPILE_STATUS, &success );
			if ( success == GL_FALSE )
			{
				int info_log_length;
				glGetShaderiv ( vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length );

				std::string vertex_shader_error_message;
				vertex_shader_error_message.resize ( info_log_length );
				glGetShaderInfoLog ( vertex_shader_id, info_log_length, &info_log_length, &vertex_shader_error_message [ 0 ] );
				vertex_shader_error_message.resize ( info_log_length );

				glDeleteShader ( vertex_shader_id );

				throw std::runtime_error { vertex_shader_error_message.c_str ( ) };
			}
		}

		// Compile Fragment Shader
		std::cout << "Compiling shader: " << fragment_file_path.c_str ( ) << std::endl;

		const char*const fragment_source_pointer = fragment_shader_code.c_str ( );
		glShaderSource ( fragment_shader_id, 1, &fragment_source_pointer, nullptr );
		glCompileShader ( fragment_shader_id );

		// Check Fragment Shader
		{
			GLint success = GL_FALSE;
			glGetShaderiv ( fragment_shader_id, GL_COMPILE_STATUS, &success );
			if ( success == GL_FALSE )
			{
				int info_log_length;
				glGetShaderiv ( fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length );

				std::string fragment_shader_error_message;
				fragment_shader_error_message.resize ( info_log_length );
				glGetShaderInfoLog ( fragment_shader_id, info_log_length, &info_log_length, &fragment_shader_error_message [ 0 ] );
				fragment_shader_error_message.resize ( info_log_length );

				glDeleteShader ( vertex_shader_id );
				glDeleteShader ( fragment_shader_id );

				throw std::runtime_error { fragment_shader_error_message.c_str ( ) };
			}
		}

		// Link the program
		std::cout << "Linking program" << std::endl;
		GLuint program_id = glCreateProgram ( );
		glAttachShader ( program_id, vertex_shader_id );
		glAttachShader ( program_id, fragment_shader_id );
		glLinkProgram ( program_id );

		// Check the program
		{
			GLint success = GL_FALSE;
			glGetProgramiv ( program_id, GL_LINK_STATUS, &success );
			if ( success == GL_FALSE )
			{
				int info_log_length;
				glGetProgramiv ( program_id, GL_INFO_LOG_LENGTH, &info_log_length );

				std::string program_error_message;
				program_error_message.resize ( info_log_length );
				glGetProgramInfoLog ( program_id, info_log_length, &info_log_length, &program_error_message [ 0 ] );
				program_error_message.resize ( info_log_length );

				glDeleteShader ( vertex_shader_id );
				glDeleteShader ( fragment_shader_id );
				glDeleteProgram ( program_id );

				throw std::runtime_error { program_error_message.c_str ( ) };
			}
		}

		glDeleteShader ( vertex_shader_id );
		glDeleteShader ( fragment_shader_id );

		std::cout << "Link successful!" << std::endl;

		glUseProgram ( program_id );

		return program_id;
	}

	void Shader::Deleter::operator ( )( const pointer& pointer ) const noexcept
	{
		glDeleteProgram ( pointer );
	}
}