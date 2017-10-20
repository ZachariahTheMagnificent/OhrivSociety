#pragma once
#include <string>
#include <glew\glew.h>
#include <memory>
#include <vector>
#include <array>

namespace opengl
{
	class Shader
	{
	public:
		Shader ( ) = default;

		Shader ( const Shader& ) = delete;
		Shader& operator=( const Shader& ) = delete;

		Shader ( Shader&& shader ) = default;
		Shader& operator=( Shader&& shader ) = default;

		bool Initialized ( ) const noexcept;

		void Use ( ) const noexcept;

	protected:
		using ProgramId = GLuint;
		using UniformId = GLuint;

		template<class Type, std::size_t size>
		class Vector : public std::array<Type, size>
		{
		public:
			Vector ( ) = default;
			Vector ( const array& vector ) : array { vector }
			{
			}
			Vector ( array&& vector ) : array { std::move ( vector ) }
			{
			}

			Vector& operator=( const array& vector )
			{
				static_cast< array& >( *this ) = vector;
				return *this;
			}
			Vector& operator=( array&& vector )
			{
				static_cast< array& >( *this ) = std::move ( vector );
				return *this;
			}
		};

		template<class Type, std::size_t rows, std::size_t columns>
		class Matrix : public std::array<Type, rows * columns>
		{
		public:
			Matrix ( ) = default;
			Matrix ( const array& matrix ) : array { matrix }
			{
			}
			Matrix ( array&& matrix ) : array { std::move ( matrix ) }
			{
			}

			Matrix& operator=( const array& matrix )
			{
				static_cast< array& >( *this ) = matrix;
				return *this;
			}
			Matrix& operator=( array&& matrix )
			{
				static_cast< array& >( *this ) = std::move ( matrix );
				return *this;
			}
		};

		template<class Type>
		class Uniform
		{
		public:
			Uniform ( ) = default;
			Uniform ( const UniformId id ) noexcept : id_ { id }
			{
			}

			UniformId GetId ( ) const noexcept
			{
				return id_;
			}

			Type& operator* ( ) noexcept
			{
				return value_;
			}

			const Type& operator* ( ) const noexcept
			{
				return value_;
			}

			Type* operator-> ( ) noexcept
			{
				return &value_;
			}

			const Type* operator-> ( ) const noexcept
			{
				return &value_;
			}

		private:
			UniformId id_ { };
			Type value_ { };
		};

		template<class Type, std::size_t rows, std::size_t columns>
		class Uniform<Matrix<Type, rows, columns>>
		{
		public:
			using Matrix = Matrix<Type, rows, columns>;

			Uniform ( ) = default;
			Uniform ( const UniformId id ) noexcept : id_ { id }
			{
			}

			UniformId GetId ( ) const noexcept
			{
				return id_;
			}

			bool GetTranspose ( ) const noexcept
			{
				return transpose_;
			}

			void SetTranspose ( const bool flag ) noexcept
			{
				transpose_ = flag;
			}

			Matrix& operator* ( ) noexcept
			{
				return value_;
			}

			const Matrix& operator* ( ) const noexcept
			{
				return value_;
			}

			Matrix* operator-> ( ) noexcept
			{
				return &value_;
			}

			const Matrix* operator-> ( ) const noexcept
			{
				return &value_;
			}

		private:
			UniformId id_ { };
			Matrix value_ { };
			bool transpose_ { };
		};

		template<class Type>
		class UniformArray : public std::vector<Type>
		{
		public:
			UniformArray ( ) = default;
			UniformArray ( const UniformId id ) : id_ { id }
			{
			}

			UniformId GetId ( ) const noexcept
			{
				return id_;
			}

		private:
			UniformId id_ { };
		};

		template<class Type, std::size_t rows, std::size_t columns>
		class UniformArray<Matrix<Type, rows, columns>> : public std::vector<Matrix<Type, rows, columns>>
		{
		public:
			using Matrix = Matrix<Type, rows, columns>;

			UniformArray ( ) = default;
			UniformArray ( const UniformId id ) : id_ { id }
			{
			}

			UniformId GetId ( ) const noexcept
			{
				return id_;
			}

			bool GetTranspose ( ) const noexcept
			{
				return transpose_;
			}

			void SetTranspose ( const bool flag ) noexcept
			{
				return transpose_ = flag;
			}

		private:
			UniformId id_ { };
			bool transpose_ { };
		};

		using IntVec2 = Vector<GLint, 2>;
		using UIntVec2 = Vector<GLuint, 2>;
		using FloatVec2 = Vector<GLfloat, 2>;
		using DoubleVec2 = Vector<GLdouble, 2>;
		using IntVec3 = Vector<GLint, 3>;
		using UIntVec3 = Vector<GLuint, 3>;
		using FloatVec3 = Vector<GLfloat, 3>;
		using DoubleVec3 = Vector<GLdouble, 3>;
		using IntVec4 = Vector<GLint, 4>;
		using UIntVec4 = Vector<GLuint, 4>;
		using FloatVec4 = Vector<GLfloat, 4>;
		using DoubleVec4 = Vector<GLdouble, 4>;

		using FloatMat2x2 = Matrix<GLfloat, 2, 2>;
		using DoubleMat2x2 = Matrix<GLdouble, 2, 2>;
		using FloatMat2x3 = Matrix<GLfloat, 2, 3>;
		using DoubleMat2x3 = Matrix<GLdouble, 2, 3>;
		using FloatMat2x4 = Matrix<GLfloat, 2, 4>;
		using DoubleMat2x4 = Matrix<GLdouble, 2, 4>;
		using FloatMat3x2 = Matrix<GLfloat, 3, 2>;
		using DoubleMat3x2 = Matrix<GLdouble, 3, 2>;
		using FloatMat3x3 = Matrix<GLfloat, 3, 3>;
		using DoubleMat3x3 = Matrix<GLdouble, 3, 3>;
		using FloatMat3x4 = Matrix<GLfloat, 3, 4>;
		using DoubleMat3x4 = Matrix<GLdouble, 3, 4>;
		using FloatMat4x2 = Matrix<GLfloat, 4, 2>;
		using DoubleMat4x2 = Matrix<GLdouble, 4, 2>;
		using FloatMat4x3 = Matrix<GLfloat, 4, 3>;
		using DoubleMat4x3 = Matrix<GLdouble, 4, 3>;
		using FloatMat4x4 = Matrix<GLfloat, 4, 4>;
		using DoubleMat4x4 = Matrix<GLdouble, 4, 4>;

		explicit Shader ( const std::string& vertex_shader, const std::string& fragment_shader );

		UniformId GetUniformId ( const std::string& uniform_name ) const noexcept;

		//Integers
		static void Update ( const Uniform<GLint>& uniform ) noexcept;
		static void Update ( const Uniform<IntVec2>& uniform ) noexcept;
		static void Update ( const Uniform<IntVec3>& uniform ) noexcept;
		static void Update ( const Uniform<IntVec4>& uniform ) noexcept;

		static void Update ( const UniformArray<GLint>& uniform_array ) noexcept;
		static void Update ( const UniformArray<IntVec2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<IntVec3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<IntVec4>& uniform_array ) noexcept;

		//Unsigned Integers
		static void Update ( const Uniform<GLuint>& uniform ) noexcept;
		static void Update ( const Uniform<UIntVec2>& uniform ) noexcept;
		static void Update ( const Uniform<UIntVec3>& uniform ) noexcept;
		static void Update ( const Uniform<UIntVec4>& uniform ) noexcept;

		static void Update ( const UniformArray<GLuint>& uniform_array ) noexcept;
		static void Update ( const UniformArray<UIntVec2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<UIntVec3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<UIntVec4>& uniform_array ) noexcept;

		//Floats
		static void Update ( const Uniform<GLfloat>& uniform ) noexcept;
		static void Update ( const Uniform<FloatVec2>& uniform ) noexcept;
		static void Update ( const Uniform<FloatVec3>& uniform ) noexcept;
		static void Update ( const Uniform<FloatVec4>& uniform ) noexcept;
		static void Update ( const Uniform<FloatMat2x2>& uniform ) noexcept;
		static void Update ( const Uniform<FloatMat2x3>& uniform ) noexcept;
		static void Update ( const Uniform<FloatMat2x4>& uniform ) noexcept;
		static void Update ( const Uniform<FloatMat3x2>& uniform ) noexcept;
		static void Update ( const Uniform<FloatMat3x3>& uniform ) noexcept;
		static void Update ( const Uniform<FloatMat3x4>& uniform ) noexcept;
		static void Update ( const Uniform<FloatMat4x2>& uniform ) noexcept;
		static void Update ( const Uniform<FloatMat4x3>& uniform ) noexcept;
		static void Update ( const Uniform<FloatMat4x4>& uniform ) noexcept;

		static void Update ( const UniformArray<GLfloat>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatVec2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatVec3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatVec4>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatMat2x2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatMat2x3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatMat2x4>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatMat3x2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatMat3x3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatMat3x4>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatMat4x2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatMat4x3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<FloatMat4x4>& uniform_array ) noexcept;

		//Doubles
		static void Update ( const Uniform<GLdouble>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleVec2>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleVec3>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleVec4>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleMat2x2>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleMat2x3>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleMat2x4>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleMat3x2>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleMat3x3>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleMat3x4>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleMat4x2>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleMat4x3>& uniform ) noexcept;
		static void Update ( const Uniform<DoubleMat4x4>& uniform ) noexcept;

		static void Update ( const UniformArray<GLdouble>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleVec2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleVec3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleVec4>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleMat2x2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleMat2x3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleMat2x4>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleMat3x2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleMat3x3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleMat3x4>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleMat4x2>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleMat4x3>& uniform_array ) noexcept;
		static void Update ( const UniformArray<DoubleMat4x4>& uniform_array ) noexcept;

	private:
		class Deleter
		{
		public:
			using pointer = ProgramId;

			void operator()( const pointer& pointer ) const noexcept;
		};
		using Handle = std::unique_ptr<ProgramId, Deleter>;

		static ProgramId LoadShaders ( const std::string& vertex_file_path, const std::string& fragment_file_path );

		Handle handle_;
	};
}