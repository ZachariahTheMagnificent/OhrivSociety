/******************************************************************************/
/*!
\file	Matrix.h
\author	Muhammad Shafik Bin Mazlinan
\par	email: cyboryxmen\@yahoo.com
\brief
Contains the Matrix class from the namespace math.

*/
/******************************************************************************/
#pragma once
#include "Basic.h"
#include "Vector3.h"
#include "Rotation.h"
#include <array>

namespace math
{
	template<class Float>
	/******************************************************************************/
	/*!
	Class Matrix:
	\brief

	*/
	/******************************************************************************/
	class Matrix : public std::array<Float, 16>
	{
	public:
		static constexpr std::size_t TOTAL_COLUMNS = 4;
		static constexpr std::size_t TOTAL_ROWS = 4;
		static constexpr std::size_t TOTAL_MEMBERS = TOTAL_COLUMNS * TOTAL_ROWS;

		using Container = std::array<Float, TOTAL_MEMBERS>;
		using Vector3 = Vector3<Float>;
		using Normal = typename Vector3::Normal;
		using Rotation = Rotation<Float>;

		/******************************************************************************/
		/*!
		\brief
		Set this matrix to frustum matrix

		\param left
		Frustum - left
		\param right
		Frustum - right
		\param bottom
		Frustum - bottom
		\param top
		Frustum - top
		\param nearVal
		Frustum - front
		\param farVal
		Frustum - back
		*/
		/******************************************************************************/
		static Matrix GetFrustum ( const Float left, const Float right, const Float bottom, const Float top, const Float near_plane, const Float far_plane )
		{
			return Matrix {
				static_cast< Float > ( 2 ) * near_plane / ( right - left ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 2 ) * near_plane / ( top - bottom ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				( right + left ) / ( right - left ),
				( top + bottom ) / ( top - bottom ),
				-( far_plane + near_plane ) / ( far_plane - near_plane ),
				static_cast< Float > ( -1 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( -2 ) * far_plane * near_plane / ( far_plane - near_plane ),
				static_cast< Float > ( 0 )
			};
		}
		/******************************************************************************/
		/*!
		\brief Set matrix to be a perspective matrix

		\param fovy
		Field of view
		\param aspect
		Aspect ratio = width : height
		\param zNear
		Near plane
		\param zFar
		Far plane
		*/
		/******************************************************************************/
		static Matrix GetPerspective ( const Float fov_y, const Float aspect, const Float near_plane, const Float far_plane )
		{
			const Float f = math::Reciprocal ( std::tan ( math::Pi<Float> ( ) / ( static_cast< Float > ( 180 ) ) * fov_y * static_cast< Float > ( 0.5 ) ) );

			return Matrix {
				f / aspect,
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				f,
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				( far_plane + near_plane ) / ( near_plane - far_plane ),
				static_cast< Float > ( -1 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 2 ) * far_plane * near_plane / ( near_plane - far_plane ),
				static_cast< Float > ( 0 )
			};
		}
		/******************************************************************************/
		/*!
		\brief Setup orthogonal matrix

		\param left
		View box - left
		\param right
		View box - right
		\param bottom
		View box - bottom
		\param top
		View box - top
		\param nearVal
		View box - front
		\param farVal
		View box - back
		*/
		/******************************************************************************/
		static Matrix GetOrtho ( const Float left, const Float right, const Float bottom, const Float top, const Float near_plane, const Float far_plane )
		{
			return Matrix {
				static_cast< Float > ( 2 ) / ( right - left ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 2 ) / ( top - bottom ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( -2 ) / ( far_plane - near_plane ),
				static_cast< Float > ( 0 ),

				-( right + left ) / ( right - left ),
				-( top + bottom ) / ( top - bottom ),
				-( far_plane + near_plane ) / ( far_plane - near_plane ),
				static_cast< Float > ( 1 )
			};
		}

		static Matrix GetViewTransform ( const Vector3& position, const Normal& direction, const Normal& up )
		{
			const Normal right = direction.Cross ( up ).Normalized ( );

			return Matrix {
				right.X ( ),
				up.X ( ),
				-direction.X ( ),
				Float ( 0 ),

				right.Y ( ),
				up.Y ( ),
				-direction.Y ( ),
				Float ( 0 ),

				right.Z ( ),
				up.Z ( ),
				-direction.Z ( ),
				Float ( 0 ),

				Float ( 0 ),
				Float ( 0 ),
				Float ( 0 ),
				Float ( 1 )
			} * GetTranslation ( -position );
		}

		template<bool CheckForUnitVector = true>
		static Matrix GetViewTransform ( const Vector3& position, const Rotation& rotation, const Vector3& default_look_direction, const Vector3& default_up )
		{
			if ( CheckForUnitVector )
			{
				if ( !default_look_direction.IsUnit ( ) || !default_up.IsUnit ( ) )
				{
					throw Math::MustBeUnit ( );
				}
			}

			return GetViewTransform ( position, rotation_matrix * default_look_direction, rotation_matrix * default_up );
		}

		/******************************************************************************/
		/*!
		\brief
		Create an identity matrix (1's along the diagonal)

		*/
		/******************************************************************************/
		static Matrix GetIdentity ( )
		{
			return Matrix {
				static_cast< Float > ( 1 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 1 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 1 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 1 )
			};
		}
		/******************************************************************************/
		/*!
		\brief
		Set Matrix to a rotation matrix about arbitrary axis

		\param	degrees
		Angle of rotation, in degrees, clockwise
		\param	axisX
		X-component of the rotation axis
		\param	axisY
		Y-component of the rotation axis
		\param	axisZ
		Z-component of the rotation axis
		\exception	DivideByZero
		Thrown if rotation axis is a zero vector
		*/
		/******************************************************************************/
		static Matrix GetRotation ( const Float radians, const Vector3& rotation_vector )
		{
			const Float c = std::cos ( radians ), s = std::sin ( radians );
			const Float x = rotation_vector.X ( );
			const Float y = rotation_vector.Y ( );
			const Float z = rotation_vector.Z ( );

			return Matrix {
				x * x * ( static_cast< Float > ( 1 ) - c ) + c,
				y * x * ( static_cast< Float > ( 1 ) - c ) + z * s,
				x * z * ( static_cast< Float > ( 1 ) - c ) - y * s,
				static_cast< Float > ( 0 ),

				x * y * ( static_cast< Float > ( 1 ) - c ) - z * s,
				y * y * ( static_cast< Float > ( 1 ) - c ) + c,
				y * z * ( static_cast< Float > ( 1 ) - c ) + x * s,
				static_cast< Float > ( 0 ),

				x * z * ( static_cast< Float > ( 1 ) - c ) + y * s,
				y * z * ( static_cast< Float > ( 1 ) - c ) - x * s,
				z * z * ( static_cast< Float > ( 1 ) - c ) + c,
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 1 )
			};
		}

		static Matrix GetRotation ( const Rotation& rotation )
		{
			const Float x = rotation.X ( );
			const Float y = rotation.Y ( );
			const Float z = rotation.Z ( );
			const Float w = rotation.W ( );

			return Matrix {
				static_cast< Float > ( 1 ) - static_cast< Float > ( 2 ) * y * y - static_cast< Float > ( 2 ) * z * z,
				static_cast< Float > ( 2 ) * x * y - static_cast< Float > ( 2 ) * w * z,
				static_cast< Float > ( 2 ) * x * z + static_cast< Float > ( 2 ) * w * y,
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 2 ) * x * y + static_cast< Float > ( 2 ) * w * z,
				static_cast< Float > ( 1 ) - static_cast< Float > ( 2 ) * x * x - static_cast< Float > ( 2 ) * z * z,
				static_cast< Float > ( 2 ) * y * z + static_cast< Float > ( 2 ) * w * x,
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 2 ) * x * z - static_cast< Float > ( 2 ) * w * y,
				static_cast< Float > ( 2 ) * y * z - static_cast< Float > ( 2 ) * w * x,
				static_cast< Float > ( 1 ) - static_cast< Float > ( 2 ) * x * x - static_cast< Float > ( 2 ) * y * y,
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 1 )
			};
		}
		/******************************************************************************/
		/*!
		\brief
		Set this matrix to a scaling matrix with scale factors sx, sy and sz

		\param sx
		scale at x-axis
		\param sy
		scale at y-axis
		\param sz
		scale at z-axis
		*/
		/******************************************************************************/
		static Matrix GetScale ( const Vector3& scale )
		{
			const Float x = scale.X ( );
			const Float y = scale.Y ( );
			const Float z = scale.Z ( );

			return Matrix {
				x,
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				y,
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				z,
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 1 )
			};
		}
		/******************************************************************************/
		/*!
		\brief
		Set this matrix to a translation matrix with translation of (x, y, z)

		\param x
		translate at x-axis
		\param y
		translate at y-axis
		\param z
		translate at y-axis
		*/
		/******************************************************************************/
		static Matrix GetTranslation ( const Vector3& translation )
		{
			const Float x = translation.X ( );
			const Float y = translation.Y ( );
			const Float z = translation.Z ( );

			return Matrix {
				static_cast< Float > ( 1 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 1 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),

				static_cast< Float > ( 0 ),
				static_cast< Float > ( 0 ),
				static_cast< Float > ( 1 ),
				static_cast< Float > ( 0 ),

				x,
				y,
				z,
				static_cast< Float > ( 1 )
			};
		}

		constexpr Matrix ( ) : Matrix ( Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ), Float ( ) )
		{
		}
		/******************************************************************************/
		/*!
		\brief
		Default Constructor. Default values are zero

		\param a00 to a33 - Initial values for the matrix in (row, column) format

		\exception None
		\return None
		*/
		/******************************************************************************/
		constexpr Matrix ( const Float column0row0, const Float column1row0, const Float column2row0, const Float column3row0, const Float column0row1, const Float column1row1, const Float column2row1, const Float column3row1, const Float column0row2, const Float column1row2, const Float column2row2, const Float column3row2, const Float column0row3, const Float column1row3, const Float column2row3, const Float column3row3 ) : Container { column0row0,column1row0,column2row0,column3row0,column0row1,column1row1,column2row1,column3row1,column0row2,column1row2,column2row2,column3row2,column0row3,column1row3,column2row3,column3row3 }
		{
		}
		/******************************************************************************/
		/*!
		\brief
		Set this matrix to its Transpose
		*/
		/******************************************************************************/
		Matrix& Transpose ( )
		{
			for ( std::size_t column = 0; column < TOTAL_COLUMNS; ++column )
			{
				for ( std::size_t row = column + 1; row < TOTAL_ROWS; ++row )
				{
					const std::size_t first_position = MemberIndex ( column, row );
					const std::size_t inverse_position = MemberIndex ( row, column );

					std::swap ( data ( ) [ first_position ], data ( ) [ inverse_position ] );
				}
			}

			return *this;
		}

		template<bool CheckForZeroError = true>
		/******************************************************************************/
		/*!
		\brief
		Return a new matrix that is an inverse

		\exception DivideByZero
		thrown if the determinant of the matrix is zero
		\return A new matrix
		*/
		/******************************************************************************/
		Matrix GetInverse ( ) const
		{
			const Float a0 = data ( ) [ 0 ] * data ( ) [ 5 ] - data ( ) [ 1 ] * data ( ) [ 4 ];
			const Float a1 = data ( ) [ 0 ] * data ( ) [ 6 ] - data ( ) [ 2 ] * data ( ) [ 4 ];
			const Float a2 = data ( ) [ 0 ] * data ( ) [ 7 ] - data ( ) [ 3 ] * data ( ) [ 4 ];
			const Float a3 = data ( ) [ 1 ] * data ( ) [ 6 ] - data ( ) [ 2 ] * data ( ) [ 5 ];
			const Float a4 = data ( ) [ 1 ] * data ( ) [ 7 ] - data ( ) [ 3 ] * data ( ) [ 5 ];
			const Float a5 = data ( ) [ 2 ] * data ( ) [ 7 ] - data ( ) [ 3 ] * data ( ) [ 6 ];
			const Float b0 = data ( ) [ 8 ] * data ( ) [ 13 ] - data ( ) [ 9 ] * data ( ) [ 12 ];
			const Float b1 = data ( ) [ 8 ] * data ( ) [ 14 ] - data ( ) [ 10 ] * data ( ) [ 12 ];
			const Float b2 = data ( ) [ 8 ] * data ( ) [ 15 ] - data ( ) [ 11 ] * data ( ) [ 12 ];
			const Float b3 = data ( ) [ 9 ] * data ( ) [ 14 ] - data ( ) [ 10 ] * data ( ) [ 13 ];
			const Float b4 = data ( ) [ 9 ] * data ( ) [ 15 ] - data ( ) [ 11 ] * data ( ) [ 13 ];
			const Float b5 = data ( ) [ 10 ] * data ( ) [ 15 ] - data ( ) [ 11 ] * data ( ) [ 14 ];

			const float determinant = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;

			if ( CheckForZeroError )
			{
				if ( math::AlmostEquals ( std::abs ( determinant ), Float ( ) ) )
				{
					throw DivideByZero ( );
				}
			}

			Float RowAColumn1, RowAColumn2, RowAColumn3, RowAColumn4, RowBColumn1, RowBColumn2, RowBColumn3, RowBColumn4, RowCColumn1, RowCColumn2, RowCColumn3, RowCColumn4, RowDColumn1, RowDColumn2, RowDColumn3, RowDColumn4;

			RowAColumn1 = +data ( ) [ 5 ] * b5 - data ( ) [ 6 ] * b4 + data ( ) [ 7 ] * b3;
			RowBColumn1 = -data ( ) [ 4 ] * b5 + data ( ) [ 6 ] * b2 - data ( ) [ 7 ] * b1;
			RowCColumn1 = +data ( ) [ 4 ] * b4 - data ( ) [ 5 ] * b2 + data ( ) [ 7 ] * b0;
			RowDColumn1 = -data ( ) [ 4 ] * b3 + data ( ) [ 5 ] * b1 - data ( ) [ 6 ] * b0;
			RowAColumn2 = -data ( ) [ 1 ] * b5 + data ( ) [ 2 ] * b4 - data ( ) [ 3 ] * b3;
			RowBColumn2 = +data ( ) [ 0 ] * b5 - data ( ) [ 2 ] * b2 + data ( ) [ 3 ] * b1;
			RowCColumn2 = -data ( ) [ 0 ] * b4 + data ( ) [ 1 ] * b2 - data ( ) [ 3 ] * b0;
			RowDColumn2 = +data ( ) [ 0 ] * b3 - data ( ) [ 1 ] * b1 + data ( ) [ 2 ] * b0;
			RowAColumn3 = +data ( ) [ 13 ] * a5 - data ( ) [ 14 ] * a4 + data ( ) [ 15 ] * a3;
			RowBColumn3 = -data ( ) [ 12 ] * a5 + data ( ) [ 14 ] * a2 - data ( ) [ 15 ] * a1;
			RowCColumn3 = +data ( ) [ 12 ] * a4 - data ( ) [ 13 ] * a2 + data ( ) [ 15 ] * a0;
			RowDColumn3 = -data ( ) [ 12 ] * a3 + data ( ) [ 13 ] * a1 - data ( ) [ 14 ] * a0;
			RowAColumn4 = -data ( ) [ 9 ] * a5 + data ( ) [ 10 ] * a4 - data ( ) [ 11 ] * a3;
			RowBColumn4 = +data ( ) [ 8 ] * a5 - data ( ) [ 10 ] * a2 + data ( ) [ 11 ] * a1;
			RowCColumn4 = -data ( ) [ 8 ] * a4 + data ( ) [ 9 ] * a2 - data ( ) [ 11 ] * a0;
			RowDColumn4 = +data ( ) [ 8 ] * a3 - data ( ) [ 9 ] * a1 + data ( ) [ 10 ] * a0;

			const Float inv_determinant = Float ( 1 ) / determinant;

			return Matrix (
				RowAColumn1 * inv_determinant,
				RowBColumn1 * inv_determinant,
				RowCColumn1 * inv_determinant,
				RowDColumn1 * inv_determinant,
				RowAColumn2 * inv_determinant,
				RowBColumn2 * inv_determinant,
				RowCColumn2 * inv_determinant,
				RowDColumn2 * inv_determinant,
				RowAColumn3 * inv_determinant,
				RowBColumn3 * inv_determinant,
				RowCColumn3 * inv_determinant,
				RowDColumn3 * inv_determinant,
				RowAColumn4 * inv_determinant,
				RowBColumn4 * inv_determinant,
				RowCColumn4 * inv_determinant,
				RowDColumn4 * inv_determinant
			);
		}
		/******************************************************************************/
		/*!
		\brief
		operator* overload for matrix-matrix multiplication

		\param rhs
		Matrix to multiply with
		\return
		Resulting matrix
		*/
		/******************************************************************************/
		Matrix operator*( const Matrix& rhs ) const
		{
			Matrix ret;
			for ( std::size_t row = 0; row < TOTAL_ROWS; ++row )
			{
				for ( std::size_t column = 0; column < TOTAL_COLUMNS; ++column )
				{
					ret.data( ) [ MemberIndex ( column, row ) ] =
						data( ) [ MemberIndex ( column, 0 ) ] * rhs.data( ) [ MemberIndex ( 0, row ) ] +
						data( ) [ MemberIndex ( column, 1 ) ] * rhs.data( ) [ MemberIndex ( 1, row ) ] +
						data( ) [ MemberIndex ( column, 2 ) ] * rhs.data( ) [ MemberIndex ( 2, row ) ] +
						data( ) [ MemberIndex ( column, 3 ) ] * rhs.data( ) [ MemberIndex ( 3, row ) ];
				}
			}
			return ret;
		}
		/******************************************************************************/
		/*!
		\brief
		operator+ overload for matrix-matrix addition

		\param rhs
		Matrix to add with
		\return
		Resulting matrix
		*/
		/******************************************************************************/
		Matrix operator+( const Matrix& rhs ) const
		{
			return Matrix ( *this ) += *this;
		}

		/******************************************************************************/
		/*!
		\brief
		operator* overload for scalar multiplication

		\param scalar
		Float to multiply with
		\return
		Resulting matrix
		*/
		/******************************************************************************/
		Matrix operator*( const Float scalar ) const
		{
			return Matrix ( *this ) *= scalar;
		}
		/******************************************************************************/
		/*!
		\brief
		operator* overload for matrix-vector3 multiplication

		\param rhs
		Vector3 to multiply with
		\return
		Resulting vector
		*/
		/******************************************************************************/
		Vector3 operator*( const Vector3& rhs ) const
		{
			//w is the forth dimension of a vector.
			const Float w = 1;
			//the vector is treated as if it is a matrix with it's x,y,z,w values placed in the last column top to bottom.

			//represents a four dimentional vector.
			Float b [ 4 ];

			for ( int i = 0; i < TOTAL_COLUMNS; ++i )
			{
				b [ i ] = data( ) [ MemberIndex ( i, 0 ) ] * rhs.X ( ) + data( ) [ MemberIndex ( i, 1 ) ] * rhs.Y ( ) + data( ) [ MemberIndex ( i, 2 ) ] * rhs.Z ( ) + data( ) [ MemberIndex ( i, 3 ) ] * w;
			}

			return Vector3 ( b [ 0 ], b [ 1 ], b [ 2 ] );
		}
		Vector3 operator*( const Normal& rhs ) const
		{
			//w is the forth dimension of a vector.
			const Float w = 0;
			//the vector is treated as if it is a matrix with it's x,y,z,w values placed in the last column top to bottom.

			//represents a four dimentional vector.
			Float b [ 4 ];

			for ( int i = 0; i < TOTAL_COLUMNS; ++i )
			{
				b [ i ] = data ( ) [ MemberIndex ( i, 0 ) ] * rhs.X ( ) + data ( ) [ MemberIndex ( i, 1 ) ] * rhs.Y ( ) + data ( ) [ MemberIndex ( i, 2 ) ] * rhs.Z ( ) + data ( ) [ MemberIndex ( i, 3 ) ] * w;
			}

			return Vector3 ( b [ 0 ], b [ 1 ], b [ 2 ] );
		}
		/******************************************************************************/
		/*!
		\brief
		operator* overload for matrix-matrix multiplication

		\param rhs
		Matrix to multiply with
		\return
		Resulting matrix
		*/
		/******************************************************************************/
		Matrix& operator*=( const Matrix& rhs )
		{
			return *this = *this * rhs;
		}
		/******************************************************************************/
		/*!
		\brief
		operator+ overload for matrix-matrix addition

		\param rhs
		Matrix to add with
		\return
		Resulting matrix
		*/
		/******************************************************************************/
		Matrix& operator+=( const Matrix& rhs )
		{
			data( ) [ 0 ] += rhs.data( ) [ 0 ];
			data( ) [ 1 ] += rhs.data( ) [ 1 ];
			data( ) [ 2 ] += rhs.data( ) [ 2 ];
			data( ) [ 3 ] += rhs.data( ) [ 3 ];
			data( ) [ 4 ] += rhs.data( ) [ 4 ];
			data( ) [ 5 ] += rhs.data( ) [ 5 ];
			data( ) [ 6 ] += rhs.data( ) [ 6 ];
			data( ) [ 7 ] += rhs.data( ) [ 7 ];
			data( ) [ 8 ] += rhs.data( ) [ 8 ];
			data( ) [ 9 ] += rhs.data( ) [ 9 ];
			data( ) [ 10 ] += rhs.data( ) [ 10 ];
			data( ) [ 11 ] += rhs.data( ) [ 11 ];
			data( ) [ 12 ] += rhs.data( ) [ 12 ];
			data( ) [ 13 ] += rhs.data( ) [ 13 ];
			data( ) [ 14 ] += rhs.data( ) [ 14 ];
			data( ) [ 15 ] += rhs.data( ) [ 15 ];

			return *this;
		}

		/******************************************************************************/
		/*!
		\brief
		operator* overload for scalar multiplication

		\param scalar
		Float to multiply with
		\return
		Resulting matrix
		*/
		/******************************************************************************/
		Matrix& operator*=( const Float scalar )
		{
			for ( float& member : *this )
			{
				
				member *= scalar;
			}

			return *this;
		}

		std::size_t MemberIndex ( const std::size_t column, const std::size_t row ) const
		{
			return row * TOTAL_COLUMNS + column;
		}
	};
}
