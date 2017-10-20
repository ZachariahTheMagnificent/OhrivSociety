#pragma once
#include <emmintrin.h>
#include <cstdlib>
#include <bitset>

namespace data_structure
{
	template<class UnsupportedType, class...Modifiers>
	class PackedData
	{
		PackedData ( )
		{
			static_assert( false, "The current implementation of PackedData does not support this type!" );
		}
	};

	template<>
	class PackedData<float>
	{
	public:
		enum
		{
			size = 4
		};

		class Readable
		{
		public:
			Readable ( const PackedData& packed_values );

			float operator[]( const std::size_t index ) const;
			const float* begin ( ) const;
			const float* end ( ) const;

		private:
			float contents_ [ size ];
		};

		static PackedData Min ( const PackedData& packed_values1, const PackedData& packed_values2 );
		static PackedData Max ( const PackedData& packed_values1, const PackedData& packed_values2 );

		PackedData ( const float value );
		PackedData ( const float value1, const float value2, const float value3, const float value4 );
		PackedData ( const float* values );
		PackedData ( const __m128 sse_register );

		PackedData operator+( const PackedData& packed_values ) const;
		PackedData operator-( const PackedData& packed_values ) const;
		PackedData operator*( const PackedData& packed_values ) const;
		PackedData operator/( const PackedData& packed_values ) const;

		PackedData& operator+=( const PackedData& packed_values );
		PackedData& operator-=( const PackedData& packed_values );
		PackedData& operator*=( const PackedData& packed_values );
		PackedData& operator/=( const PackedData& packed_values );

		PackedData<bool, float> operator>( const PackedData& packed_values ) const;
		PackedData<bool, float> operator<( const PackedData& packed_values ) const;
		PackedData<bool, float> operator>=( const PackedData& packed_values ) const;
		PackedData<bool, float> operator<=( const PackedData& packed_values ) const;
		PackedData<bool, float> operator==( const PackedData& packed_values ) const;
		PackedData<bool, float> operator!=( const PackedData& packed_values ) const;

		PackedData Sqrt ( ) const;
		PackedData Reciprocal ( ) const;
		PackedData ReciprocalOfSqrt ( ) const;

	private:
		__m128 sse_register_;
	};

	template<>
	class PackedData<bool, float>
	{
	public:
		enum
		{
			size = PackedData<float>::size
		};

		class Readable
		{
		public:
			class Iterator
			{
			public:
				Iterator ( const std::bitset<size> flags, const std::size_t index );

				bool operator!=( const Iterator iterator ) const;

				Iterator& operator++( );

				bool operator*( ) const;

			private:
				std::bitset<size> flags_;
				std::size_t index_;
			};

			Readable ( const PackedData& packed_booleans );

			bool operator[]( const std::size_t index ) const;
			const Iterator begin ( ) const;
			const Iterator end ( ) const;

		private:
			std::bitset<size> flags_;
		};

		PackedData ( const __m128 sse_register );

		PackedData operator&&( const PackedData& packed_booleans ) const;
		PackedData operator||( const PackedData& packed_booleans ) const;
		PackedData operator^( const PackedData& packed_booleans ) const;
		PackedData operator==( const PackedData& packed_booleans ) const;
		PackedData operator!=( const PackedData& packed_booleans ) const;

		PackedData AndNot ( const PackedData& packed_booleans ) const;

	private:
		__m128 sse_register_;
	};

	template<>
	class PackedData<double>
	{
	public:
		enum
		{
			size = 2
		};

		class Readable
		{
		public:
			Readable ( const PackedData& packed_values );

			double operator[]( const std::size_t index ) const;
			const double* begin ( ) const;
			const double* end ( ) const;

		private:
			double contents_ [ size ];
		};

		static PackedData Min ( const PackedData& packed_values1, const PackedData& packed_values2 );
		static PackedData Max ( const PackedData& packed_values1, const PackedData& packed_values2 );

		PackedData ( const double value );
		PackedData ( const double value1, const double value2 );
		PackedData ( const double* values );
		PackedData ( const __m128d sse_register );

		PackedData operator+( const PackedData& packed_values ) const;
		PackedData operator-( const PackedData& packed_values ) const;
		PackedData operator*( const PackedData& packed_values ) const;
		PackedData operator/( const PackedData& packed_values ) const;

		PackedData& operator+=( const PackedData& packed_values );
		PackedData& operator-=( const PackedData& packed_values );
		PackedData& operator*=( const PackedData& packed_values );
		PackedData& operator/=( const PackedData& packed_values );

		PackedData<bool, double> operator>( const PackedData& packed_values ) const;
		PackedData<bool, double> operator<( const PackedData& packed_values ) const;
		PackedData<bool, double> operator>=( const PackedData& packed_values ) const;
		PackedData<bool, double> operator<=( const PackedData& packed_values ) const;
		PackedData<bool, double> operator==( const PackedData& packed_values ) const;
		PackedData<bool, double> operator!=( const PackedData& packed_values ) const;

		PackedData Sqrt ( ) const;

	private:
		__m128d sse_register_;
	};

	template<>
	class PackedData<bool, double>
	{
	public:
		enum
		{
			size = PackedData<double>::size
		};

		class Readable
		{
		public:
			class Iterator
			{
			public:
				Iterator ( const std::bitset<size> flags, const std::size_t index );

				bool operator!=( const Iterator iterator ) const;

				Iterator& operator++( );

				bool operator*( ) const;

			private:
				std::bitset<size> flags_;
				std::size_t index_;
			};

			Readable ( const PackedData& packed_booleans );

			bool operator[]( const std::size_t index ) const;
			const Iterator begin ( ) const;
			const Iterator end ( ) const;

		private:
			std::bitset<size> flags_;
		};

		PackedData ( const __m128d sse_register );

		PackedData operator&&( const PackedData& packed_booleans ) const;
		PackedData operator||( const PackedData& packed_booleans ) const;
		PackedData operator^( const PackedData& packed_booleans ) const;
		PackedData operator==( const PackedData& packed_booleans ) const;
		PackedData operator!=( const PackedData& packed_booleans ) const;

		PackedData AndNot ( const PackedData& packed_booleans ) const;

	private:
		__m128d sse_register_;
	};
}