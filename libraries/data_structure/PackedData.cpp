#include "PackedData.h"

namespace data_structure
{
	PackedData<float>::Readable::Readable ( const PackedData& packed_values )
	{
		_mm_store_ps ( contents_, packed_values.sse_register_ );
	}

	float PackedData<float>::Readable::operator[]( const std::size_t index ) const
	{
		return contents_ [ index ];
	}

	const float* PackedData<float>::Readable::begin ( ) const
	{
		return contents_;
	}

	const float* PackedData<float>::Readable::end ( ) const
	{
		return contents_ + size;
	}

	PackedData<float> PackedData<float>::Min ( const PackedData& packed_values1, const PackedData& packed_values2 )
	{
		return _mm_min_ps ( packed_values1.sse_register_, packed_values2.sse_register_ );
	}

	PackedData<float> PackedData<float>::Max ( const PackedData& packed_values1, const PackedData& packed_values2 )
	{
		return _mm_max_ps ( packed_values1.sse_register_, packed_values2.sse_register_ );
	}

	PackedData<float>::PackedData ( const float value )
	{
		sse_register_ = _mm_set_ps1 ( value );
	}

	PackedData<float>::PackedData ( const float value1, const float value2, const float value3, const float value4 )
	{
		sse_register_ = _mm_set_ps ( value4, value3, value2, value1 );
	}

	PackedData<float>::PackedData ( const float* values )
	{
		sse_register_ = _mm_load_ps ( values );
	}

	PackedData<float>::PackedData ( const __m128 sse_register ) : sse_register_ ( sse_register )
	{
	}

	PackedData<float> PackedData<float>::operator+( const PackedData& packed_values ) const
	{
		return _mm_add_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<float> PackedData<float>::operator-( const PackedData& packed_values ) const
	{
		return _mm_sub_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<float> PackedData<float>::operator*( const PackedData& packed_values ) const
	{
		return _mm_mul_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<float> PackedData<float>::operator/( const PackedData& packed_values ) const
	{
		return _mm_div_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<float>& PackedData<float>::operator+=( const PackedData& packed_values )
	{
		*this = *this + packed_values;
		return *this;
	}

	PackedData<float>& PackedData<float>::operator-=( const PackedData& packed_values )
	{
		*this = *this - packed_values;
		return *this;
	}

	PackedData<float>& PackedData<float>::operator*=( const PackedData& packed_values )
	{
		*this = *this * packed_values;
		return *this;
	}

	PackedData<float>& PackedData<float>::operator/=( const PackedData& packed_values )
	{
		*this = *this / packed_values;
		return *this;
	}

	PackedData<bool, float> PackedData<float>::operator>( const PackedData& packed_values ) const
	{
		return _mm_cmpgt_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, float> PackedData<float>::operator<( const PackedData& packed_values ) const
	{
		return _mm_cmplt_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, float> PackedData<float>::operator>=( const PackedData& packed_values ) const
	{
		return _mm_cmpge_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, float> PackedData<float>::operator<=( const PackedData& packed_values ) const
	{
		return _mm_cmple_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, float> PackedData<float>::operator==( const PackedData& packed_values ) const
	{
		return _mm_cmpeq_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, float> PackedData<float>::operator!=( const PackedData& packed_values ) const
	{
		return _mm_cmpneq_ps ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<float> PackedData<float>::Sqrt ( ) const
	{
		return _mm_sqrt_ps ( sse_register_ );
	}

	PackedData<float> PackedData<float>::Reciprocal ( ) const
	{
		return _mm_rcp_ps ( sse_register_ );
	}

	PackedData<float> PackedData<float>::ReciprocalOfSqrt ( ) const
	{
		return _mm_rsqrt_ps ( sse_register_ );
	}

	PackedData<bool, float>::Readable::Iterator::Iterator ( const std::bitset<size> flags, const std::size_t index ) : flags_ ( flags ), index_ ( index )
	{
	}

	bool PackedData<bool, float>::Readable::Iterator::operator!=( const Iterator iterator ) const
	{
		return index_ != iterator.index_;
	}

	PackedData<bool, float>::Readable::Iterator& PackedData<bool, float>::Readable::Iterator::operator++( )
	{
		++index_;
		return *this;
	}

	bool PackedData<bool, float>::Readable::Iterator::operator*( ) const
	{
		return flags_ [ index_ ];
	}

	PackedData<bool, float>::Readable::Readable ( const PackedData& packed_booleans )
	{
		const int extracted_flags = _mm_movemask_ps ( packed_booleans.sse_register_ );
		flags_ = extracted_flags;
	}

	bool PackedData<bool, float>::Readable::operator[]( const std::size_t index ) const
	{
		return flags_ [ index ];
	}

	const PackedData<bool, float>::Readable::Iterator PackedData<bool, float>::Readable::begin ( ) const
	{
		return Iterator ( flags_, 0 );
	}

	const PackedData<bool, float>::Readable::Iterator PackedData<bool, float>::Readable::end ( ) const
	{
		return Iterator ( flags_, size );
	}

	PackedData<bool, float>::PackedData ( const __m128 sse_register ) : sse_register_ ( sse_register )
	{
	}

	PackedData<bool, float> PackedData<bool, float>::operator&&( const PackedData& packed_booleans ) const
	{
		return _mm_and_ps ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, float> PackedData<bool, float>::operator||( const PackedData& packed_booleans ) const
	{
		return _mm_or_ps ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, float> PackedData<bool, float>::operator^( const PackedData& packed_booleans ) const
	{
		return _mm_xor_ps ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, float> PackedData<bool, float>::operator==( const PackedData& packed_booleans ) const
	{
		return _mm_cmpeq_ps ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, float> PackedData<bool, float>::operator!=( const PackedData& packed_booleans ) const
	{
		return _mm_cmpneq_ps ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, float> PackedData<bool, float>::AndNot ( const PackedData& packed_booleans ) const
	{
		return _mm_andnot_ps ( packed_booleans.sse_register_, sse_register_ );
	}

	PackedData<double>::Readable::Readable ( const PackedData& packed_values )
	{
		_mm_store_pd ( contents_, packed_values.sse_register_ );
	}

	double PackedData<double>::Readable::operator[]( const std::size_t index ) const
	{
		return contents_ [ index ];
	}

	const double* PackedData<double>::Readable::begin ( ) const
	{
		return contents_;
	}

	const double* PackedData<double>::Readable::end ( ) const
	{
		return contents_ + size;
	}

	PackedData<double> PackedData<double>::Min ( const PackedData& packed_values1, const PackedData& packed_values2 )
	{
		return _mm_min_pd ( packed_values1.sse_register_, packed_values2.sse_register_ );
	}

	PackedData<double> PackedData<double>::Max ( const PackedData& packed_values1, const PackedData& packed_values2 )
	{
		return _mm_max_pd ( packed_values1.sse_register_, packed_values2.sse_register_ );
	}

	PackedData<double>::PackedData ( const double value )
	{
		sse_register_ = _mm_set1_pd ( value );
	}

	PackedData<double>::PackedData ( const double value1, const double value2 )
	{
		sse_register_ = _mm_set_pd ( value2, value1 );
	}

	PackedData<double>::PackedData ( const double* values )
	{
		sse_register_ = _mm_load_pd ( values );
	}

	PackedData<double>::PackedData ( const __m128d sse_register ) : sse_register_ ( sse_register )
	{
	}

	PackedData<double> PackedData<double>::operator+( const PackedData& packed_values ) const
	{
		return _mm_add_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<double> PackedData<double>::operator-( const PackedData& packed_values ) const
	{
		return _mm_sub_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<double> PackedData<double>::operator*( const PackedData& packed_values ) const
	{
		return _mm_mul_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<double> PackedData<double>::operator/( const PackedData& packed_values ) const
	{
		return _mm_div_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<double>& PackedData<double>::operator+=( const PackedData& packed_values )
	{
		*this = *this + packed_values;
		return *this;
	}

	PackedData<double>& PackedData<double>::operator-=( const PackedData& packed_values )
	{
		*this = *this - packed_values;
		return *this;
	}

	PackedData<double>& PackedData<double>::operator*=( const PackedData& packed_values )
	{
		*this = *this * packed_values;
		return *this;
	}

	PackedData<double>& PackedData<double>::operator/=( const PackedData& packed_values )
	{
		*this = *this / packed_values;
		return *this;
	}

	PackedData<bool, double> PackedData<double>::operator>( const PackedData& packed_values ) const
	{
		return _mm_cmpgt_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, double> PackedData<double>::operator<( const PackedData& packed_values ) const
	{
		return _mm_cmplt_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, double> PackedData<double>::operator>=( const PackedData& packed_values ) const
	{
		return _mm_cmpge_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, double> PackedData<double>::operator<=( const PackedData& packed_values ) const
	{
		return _mm_cmple_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, double> PackedData<double>::operator==( const PackedData& packed_values ) const
	{
		return _mm_cmpeq_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<bool, double> PackedData<double>::operator!=( const PackedData& packed_values ) const
	{
		return _mm_cmpneq_pd ( sse_register_, packed_values.sse_register_ );
	}

	PackedData<double> PackedData<double>::Sqrt ( ) const
	{
		return _mm_sqrt_pd ( sse_register_ );
	}

	PackedData<bool, double>::Readable::Iterator::Iterator ( const std::bitset<size> flags, const std::size_t index ) : flags_ ( flags ), index_ ( index )
	{
	}

	bool PackedData<bool, double>::Readable::Iterator::operator!=( const Iterator iterator ) const
	{
		return index_ != iterator.index_;
	}

	PackedData<bool, double>::Readable::Iterator& PackedData<bool, double>::Readable::Iterator::operator++( )
	{
		++index_;
		return *this;
	}

	bool PackedData<bool, double>::Readable::Iterator::operator*( ) const
	{
		return flags_ [ index_ ];
	}

	PackedData<bool, double>::Readable::Readable ( const PackedData& packed_booleans )
	{
		const int extracted_flags = _mm_movemask_pd ( packed_booleans.sse_register_ );
		flags_ = extracted_flags;
	}

	bool PackedData<bool, double>::Readable::operator[]( const std::size_t index ) const
	{
		return flags_ [ index ];
	}

	const PackedData<bool, double>::Readable::Iterator PackedData<bool, double>::Readable::begin ( ) const
	{
		return Iterator ( flags_, 0 );
	}

	const PackedData<bool, double>::Readable::Iterator PackedData<bool, double>::Readable::end ( ) const
	{
		return Iterator ( flags_, size );
	}

	PackedData<bool, double>::PackedData ( const __m128d sse_register ) : sse_register_ ( sse_register )
	{
	}

	PackedData<bool, double> PackedData<bool, double>::operator&&( const PackedData& packed_booleans ) const
	{
		return _mm_and_pd ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, double> PackedData<bool, double>::operator||( const PackedData& packed_booleans ) const
	{
		return _mm_or_pd ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, double> PackedData<bool, double>::operator^( const PackedData& packed_booleans ) const
	{
		return _mm_xor_pd ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, double> PackedData<bool, double>::operator==( const PackedData& packed_booleans ) const
	{
		return _mm_cmpeq_pd ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, double> PackedData<bool, double>::operator!=( const PackedData& packed_booleans ) const
	{
		return _mm_cmpneq_pd ( sse_register_, packed_booleans.sse_register_ );
	}

	PackedData<bool, double> PackedData<bool, double>::AndNot ( const PackedData& packed_booleans ) const
	{
		return _mm_andnot_pd ( sse_register_, packed_booleans.sse_register_ );
	}
}