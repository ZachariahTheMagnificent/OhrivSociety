#pragma once
#include <cstdlib>
#include <cstdint>
#include <array>
#include <memory>
#include <type_traits>

namespace data_structure
{
	class BaseRoom
	{
	protected:
		using VirtualCopy = void ( *)( void*const lhs, const void*const rhs );

		template<class Type>
		static void Copy ( void*const lhs, const void*const rhs ) noexcept( noexcept( new ( lhs ) Type { *reinterpret_cast< const Type* >( rhs ) } ) )
		{
			new ( lhs ) Type { *reinterpret_cast< const Type* >( rhs ) };
		}

		using VirtualMove = void ( *)( void*const lhs, void*const rhs );

		template<class Type>
		static void Move ( void*const lhs, void*const rhs ) noexcept( noexcept( new ( lhs ) Type { std::move ( *reinterpret_cast< Type* >( rhs ) ) } ) )
		{
			new ( lhs ) Type { std::move ( *reinterpret_cast< Type* >( rhs ) ) };
		}

		using VirtualDestroy = void ( *)( void*const object );

		template<class Type, bool test = std::is_destructible<Type>::value>
		struct DestroyClass
		{
			static void Destroy ( void*const object )
			{
				reinterpret_cast< Type* >( object )->~Type ( );
			}
		};
		template<class Type>
		struct DestroyClass<Type, false>
		{
			static void Destroy ( void*const object )
			{
			}
		};
		template<class Type>
		static void Destroy ( void*const object )
		{
			DestroyClass<Type>::Destroy ( object );
		}

		template<class Visitor, class...OtherParameterTypes>
		using VirtualDispatch = typename std::remove_reference<Visitor>::type::ReturnType ( *)( void*const object, Visitor&& visitor, OtherParameterTypes&&...other_parameters );
		template<class Visitor, class...OtherParameterTypes>
		using VirtualDispatchConst = typename std::remove_reference<Visitor>::type::ReturnType ( *)( const void*const object, Visitor&& visitor, OtherParameterTypes&&...other_parameters );
		template<class Visitor, class...OtherParameterTypes>
		using VirtualDispatchTemp = typename std::remove_reference<Visitor>::type::ReturnType ( *)( void*const temp_object, Visitor&& visitor, OtherParameterTypes&&...other_parameters );
		template<class Visitor, class...OtherParameterTypes>
		using VirtualDispatchConstTemp = typename std::remove_reference<Visitor>::type::ReturnType ( *)( const void*const temp_object, Visitor&& visitor, OtherParameterTypes&&...other_parameters );

		template<class Type, class Visitor, class...OtherParameterTypes>
		static typename std::remove_reference<Visitor>::type::ReturnType Dispatch ( void*const object, Visitor&& visitor, OtherParameterTypes&&...other_parameters );
		template<class Type, class Visitor, class...OtherParameterTypes>
		static typename std::remove_reference<Visitor>::type::ReturnType DispatchConst ( const void*const object, Visitor&& visitor, OtherParameterTypes&&...other_parameters );
		template<class Type, class Visitor, class...OtherParameterTypes>
		static typename std::remove_reference<Visitor>::type::ReturnType DispatchTemp ( void*const temp_object, Visitor&& visitor, OtherParameterTypes&&...other_parameters );
		template<class Type, class Visitor, class...OtherParameterTypes>
		static typename std::remove_reference<Visitor>::type::ReturnType DispatchConstTemp ( const void*const temp_object, Visitor&& visitor, OtherParameterTypes&&...other_parameters );

		template<class CurrentType, class...OtherTypes>
		struct TypeEnum
		{
			static constexpr std::size_t Size ( )
			{
				return TypeEnum<OtherTypes...>::Size ( ) + 1;
			}
			template<class Type>
			static constexpr bool HasType ( )
			{
				return TypeEnum<OtherTypes...>::HasType<Type> ( );
			}
			template<>
			static constexpr bool HasType<CurrentType> ( )
			{
				return true;
			}
			template<class Type>
			static constexpr std::size_t GetEnum ( )
			{
				return TypeEnum<OtherTypes...>::GetEnum<Type> ( );
			}
			template<>
			static constexpr std::size_t GetEnum<CurrentType> ( )
			{
				return Size ( ) - 1;
			}
		};

		template<class LastType>
		struct TypeEnum<LastType>
		{
			static constexpr std::size_t Size ( )
			{
				return 1;
			}
			template<class Type>
			static constexpr bool HasType ( )
			{
				return false;
			}
			template<>
			static constexpr bool HasType<LastType> ( )
			{
				return true;
			}
			template<class Type>
			static constexpr std::size_t GetEnum ( )
			{
				return void;
			}
			template<>
			static constexpr std::size_t GetEnum<LastType> ( )
			{
				return Size ( ) - 1;
			}
		};

		template<class FirstType, class SecondType, bool test = ( sizeof ( FirstType ) > sizeof ( SecondType ) )>
		struct BiggestType
		{
			using Type = FirstType;
		};

		template<class FirstType, class SecondType>
		struct BiggestType<FirstType, SecondType, false>
		{
			using Type = SecondType;
		};

		template<class FirstType, class SecondType, class...OtherTypes>
		struct FindBiggestType
		{
			using Type = typename FindBiggestType<typename BiggestType<FirstType, SecondType>::Type, OtherTypes...>::Type;
		};

		template<class FirstType, class SecondType>
		struct FindBiggestType<FirstType, SecondType>
		{
			using Type = typename BiggestType<FirstType, SecondType>::Type;
		};
	};

	template<class BaseClass, class FirstType, class SecondType, class...OtherTypes>
	class Room final : public BaseRoom
	{
		std::size_t type_index_;
		std::uint8_t data_ [ sizeof ( typename FindBiggestType<FirstType, SecondType, OtherTypes...>::Type ) ];

		using Enum = TypeEnum<FirstType, SecondType, OtherTypes...>;

		template<class Type>
		static void SetVirtualCopy ( std::array<VirtualCopy, Enum::Size ( )>& arr )
		{
			arr [ Enum::GetEnum<Type> ( ) ] = &Copy<Type>;
		}
		template<class Type>
		static void SetVirtualMove ( std::array<VirtualMove, Enum::Size ( )>& arr )
		{
			arr [ Enum::GetEnum<Type> ( ) ] = &Move<Type>;
		}
		template<class Type>
		static void SetVirtualDestroy ( std::array<VirtualDestroy, Enum::Size ( )>& arr )
		{
			arr [ Enum::GetEnum<Type> ( ) ] = &Destroy<Type>;
		}
		template<class Visitor, class...OtherParameterTypes>
		struct SetVirtualDispatchClass
		{
			template<class Type>
			static void Set ( std::array<VirtualDispatch<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
			{
				arr [ Enum::GetEnum<Type> ( ) ] = &Dispatch<Type, Visitor, OtherParameterTypes...>;
			}
			template<class Type>
			static void SetConst ( std::array<VirtualDispatchConst<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
			{
				arr [ Enum::GetEnum<Type> ( ) ] = &DispatchConst<Type, Visitor, OtherParameterTypes...>;
			}
			template<class Type>
			static void SetTemp ( std::array<VirtualDispatchTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
			{
				arr [ Enum::GetEnum<Type> ( ) ] = &DispatchTemp<Type, Visitor, OtherParameterTypes...>;
			}
			template<class Type>
			static void SetConstTemp ( std::array<VirtualDispatchConstTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
			{
				arr [ Enum::GetEnum<Type> ( ) ] = &DispatchConstTemp<Type, Visitor, OtherParameterTypes...>;
			}
		};

		template<class CurrentType, class...OtherTableTypes>
		struct BuildVirtualTableCopyClass
		{
			static void Build ( std::array<VirtualCopy, Enum::Size ( )>& arr )
			{
				SetVirtualCopy<CurrentType> ( arr );
				BuildVirtualTableCopyClass<OtherTableTypes...>::Build ( arr );
			}
		};
		template<class LastType>
		struct BuildVirtualTableCopyClass<LastType>
		{
			static void Build ( std::array<VirtualCopy, Enum::Size ( )>& arr )
			{
				SetVirtualCopy<LastType> ( arr );
			}
		};
		template<class CurrentType, class...OtherTableTypes>
		struct BuildVirtualTableMoveClass
		{
			static void Build ( std::array<VirtualMove, Enum::Size ( )>& arr )
			{
				SetVirtualMove<CurrentType> ( arr );
				BuildVirtualTableMoveClass<OtherTableTypes...>::Build ( arr );
			}
		};
		template<class LastType>
		struct BuildVirtualTableMoveClass<LastType>
		{
			static void Build ( std::array<VirtualMove, Enum::Size ( )>& arr )
			{
				SetVirtualMove<LastType> ( arr );
			}
		};
		template<class CurrentType, class...OtherTableTypes>
		struct BuildVirtualTableDestroyClass
		{
			static void Build ( std::array<VirtualDestroy, Enum::Size ( )>& arr )
			{
				SetVirtualDestroy<CurrentType> ( arr );
				BuildVirtualTableDestroyClass<OtherTableTypes...>::Build ( arr );
			}
		};
		template<class LastType>
		struct BuildVirtualTableDestroyClass<LastType>
		{
			static void Build ( std::array<VirtualDestroy, Enum::Size ( )>& arr )
			{
				SetVirtualDestroy<LastType> ( arr );
			}
		};
		template<class Visitor, class...OtherParameterTypes>
		struct BuildVirtualTableDispatchClasses
		{
			template<class CurrentType, class...OtherTableTypes>
			struct BuildVirtualTableDispatchClass
			{
				static void Build ( std::array<VirtualDispatch<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
				{
					SetVirtualDispatchClass<Visitor, OtherParameterTypes...>::Set<CurrentType> ( arr );
					BuildVirtualTableDispatchClass<OtherTableTypes...>::Build ( arr );
				}
			};
			template<class LastType>
			struct BuildVirtualTableDispatchClass<LastType>
			{
				static void Build ( std::array<VirtualDispatch<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
				{
					SetVirtualDispatchClass<Visitor, OtherParameterTypes...>::Set<LastType> ( arr );
				}
			};
			template<class CurrentType, class...OtherTableTypes>
			struct BuildVirtualTableDispatchConstClass
			{
				static void Build ( std::array<VirtualDispatchConst<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
				{
					SetVirtualDispatchClass<Visitor, OtherParameterTypes...>::SetConst<CurrentType> ( arr );
					BuildVirtualTableDispatchConstClass<OtherTableTypes...>::Build ( arr );
				}
			};
			template<class LastType>
			struct BuildVirtualTableDispatchConstClass<LastType>
			{
				static void Build ( std::array<VirtualDispatchConst<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
				{
					SetVirtualDispatchClass<Visitor, OtherParameterTypes...>::SetConst<LastType> ( arr );
				}
			};
			template<class CurrentType, class...OtherTableTypes>
			struct BuildVirtualTableDispatchTempClass
			{
				static void Build ( std::array<VirtualDispatchTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
				{
					SetVirtualDispatchClass<Visitor, OtherParameterTypes...>::SetTemp<CurrentType> ( arr );
					BuildVirtualTableDispatchTempClass<OtherTableTypes...>::Build ( arr );
				}
			};
			template<class LastType>
			struct BuildVirtualTableDispatchTempClass<LastType>
			{
				static void Build ( std::array<VirtualDispatchTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
				{
					SetVirtualDispatchClass<Visitor, OtherParameterTypes...>::SetTemp<LastType> ( arr );
				}
			};
			template<class CurrentType, class...OtherTableTypes>
			struct BuildVirtualTableDispatchConstTempClass
			{
				static void Build ( std::array<VirtualDispatchConstTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
				{
					SetVirtualDispatchClass<Visitor, OtherParameterTypes...>::SetConstTemp<CurrentType> ( arr );
					BuildVirtualTableDispatchConstTempClass<OtherTableTypes...>::Build ( arr );
				}
			};
			template<class LastType>
			struct BuildVirtualTableDispatchConstTempClass<LastType>
			{
				static void Build ( std::array<VirtualDispatchConstTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )>& arr )
				{
					SetVirtualDispatchClass<Visitor, OtherParameterTypes...>::SetConstTemp<LastType> ( arr );
				}
			};
		};

		std::array<VirtualCopy, Enum::Size ( )> GetVirtualTableCopy ( )
		{
			std::array<VirtualCopy, Enum::Size ( )> arr;
			BuildVirtualTableCopyClass<FirstType, SecondType, OtherTypes...>::Build ( arr );
			return arr;
		}
		std::array<VirtualMove, Enum::Size ( )> GetVirtualTableMove ( )
		{
			std::array<VirtualMove, Enum::Size ( )> arr;
			BuildVirtualTableMoveClass<FirstType, SecondType, OtherTypes...>::Build ( arr );
			return arr;
		}
		std::array<VirtualDestroy, Enum::Size ( )> GetVirtualTableDestroy ( )
		{
			std::array<VirtualDestroy, Enum::Size ( )> arr;
			BuildVirtualTableDestroyClass<FirstType, SecondType, OtherTypes...>::Build ( arr );
			return arr;
		}
		template<class Visitor, class...OtherParameterTypes>
		struct GetVirtualTableDispatchClass
		{
			static std::array<VirtualDispatch<Visitor, OtherParameterTypes...>, Enum::Size ( )> Get ( )
			{
				std::array<VirtualDispatch<Visitor, OtherParameterTypes...>, Enum::Size ( )> arr;
				BuildVirtualTableDispatchClasses<Visitor, OtherParameterTypes...>::BuildVirtualTableDispatchClass<FirstType, SecondType, OtherTypes...>::Build ( arr );
				return arr;
			}
			static std::array<VirtualDispatchConst<Visitor, OtherParameterTypes...>, Enum::Size ( )> GetConst ( )
			{
				std::array<VirtualDispatchConst<Visitor, OtherParameterTypes...>, Enum::Size ( )> arr;
				BuildVirtualTableDispatchClasses<Visitor, OtherParameterTypes...>::BuildVirtualTableDispatchConstClass<FirstType, SecondType, OtherTypes...>::Build ( arr );
				return arr;
			}
			static std::array<VirtualDispatchTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )> GetTemp ( )
			{
				std::array<VirtualDispatchTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )> arr;
				BuildVirtualTableDispatchClasses<Visitor, OtherParameterTypes...>::BuildVirtualTableDispatchTempClass<FirstType, SecondType, OtherTypes...>::Build ( arr );
				return arr;
			}
			static std::array<VirtualDispatchConstTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )> GetConstTemp ( )
			{
				std::array<VirtualDispatchConstTemp<Visitor, OtherParameterTypes...>, Enum::Size ( )> arr;
				BuildVirtualTableDispatchClasses<Visitor, OtherParameterTypes...>::BuildVirtualTableDispatchConstTempClass<FirstType, SecondType, OtherTypes...>::Build ( arr );
				return arr;
			}
		};

		template<class Type>
		static constexpr bool IsValidType ( )
		{
			return Enum::HasType<Type> ( ) && ( std::is_base_of<BaseClass, Type>::value || std::is_same<BaseClass, void>::value );
		}

		template<class Type>
		void CreateFrom ( Type&& object )
		{
			new ( data_ ) Type { std::forward<Type> ( object ) };
			type_index_ = Enum::GetEnum<Type> ( );
		}
		void CreateFrom ( const Room& object )
		{
			static const auto table = GetVirtualTableCopy ( );

			table [ object.type_index_ ] ( data_, object.data_ );
			type_index_ = object.type_index_;
		}
		void CreateFrom ( Room&& object )
		{
			static const auto table = GetVirtualTableMove ( );

			table [ object.type_index_ ] ( data_, object.data_ );
			type_index_ = object.type_index_;
		}

	public:
		Room ( ) = default;
		explicit Room ( const Room& room )
		{
			CreateFrom ( room );
		}
		explicit Room ( Room&& room )
		{
			CreateFrom ( std::move ( room ) );
		}
		template<class Type/*, class Test = typename std::enable_if<IsValidType<Type> ( )>::type*/>
		explicit Room ( Type&& object )
		{
			CreateFrom ( std::forward<Type> ( object ) );
		}
		~Room ( )
		{
			static const auto table = GetVirtualTableDestroy ( );

			table [ type_index_ ] ( data_ );
		}

		Room& operator=( const Room& room )
		{
			~Room ( );

			CreateFrom ( room );

			return *this;
		}
		Room& operator=( Room&& room )
		{
			~Room ( );

			CreateFrom ( std::move ( room ) );

			return *this;
		}
		template<class Type/*, class Test = typename std::enable_if<IsValidType<Type> ( )>::type*/>
		Room& operator=( Type&& object )
		{
			~Room ( );

			CreateFrom ( std::forward<Type> ( object ) );

			return *this;
		}

		template<class Type, class...ParameterTypes>
		static void InitByEmplace ( Room& room, ParameterTypes&&...parameters )
		{
			new ( room.data_ ) Type { std::forward<ParameterTypes> ( parameters )... };
			room.type_index_ = Enum::GetEnum<Type> ( );
		}

		template<class Type, class...ParameterTypes>
		void Emplace ( ParameterTypes&&...parameters )
		{
			~Room ( );

			InitByEmplace ( *this, std::forward<ParameterTypes> ( parameters )... );
		}

		BaseClass* GetOccupant ( ) noexcept
		{
			return reinterpret_cast< BaseClass* >( data_ );
		}
		const BaseClass* GetOccupant ( ) const noexcept
		{
			return reinterpret_cast< const BaseClass* >( data_ );
		}

		BaseClass* operator->( ) noexcept
		{
			return GetOccupant ( );
		}
		const BaseClass* operator->( ) const noexcept
		{
			return GetOccupant ( );
		}

		//Disabled until I Visual Studio gets its shit together and implement SFINAE
		//template<class Test = typename std::enable_if<!std::is_same<BaseClass, void>::value>::type>
		//BaseClass& operator*( )
		//{
		//	return *GetOccupant ( );
		//}
		//template<class Test = typename std::enable_if<!std::is_same<BaseClass, void>::value>::type>
		//const BaseClass& operator*( ) const
		//{
		//	return *GetOccupant ( );
		//}

		template<class Visitor, class...OtherParameterTypes>
		auto Accept ( Visitor&& visitor, OtherParameterTypes&&...other_parameters )
		{
			static const auto table = GetVirtualTableDispatchClass<Visitor, OtherParameterTypes...>::Get ( );

			return table [ type_index_ ] ( data_, std::forward<Visitor> ( visitor ), std::forward<OtherParameterTypes> ( other_parameters )... );
		}
		template<class Visitor, class...OtherParameterTypes>
		auto Accept ( Visitor&& visitor, OtherParameterTypes&&...other_parameters ) const
		{
			static const auto table = GetVirtualTableDispatchClass<Visitor, OtherParameterTypes...>::GetConst ( );

			return table [ type_index_ ] ( data_, std::forward<Visitor> ( visitor ), std::forward<OtherParameterTypes> ( other_parameters )... );
		}
		template<class Visitor, class...OtherParameterTypes>
		auto AcceptAsTemp ( Visitor&& visitor, OtherParameterTypes&&...other_parameters )
		{
			static const auto table = GetVirtualTableDispatchClass<Visitor, OtherParameterTypes...>::GetTemp ( );

			return table [ type_index_ ] ( data_, std::forward<Visitor> ( visitor ), std::forward<OtherParameterTypes> ( other_parameters )... );
		}
		template<class Visitor, class...OtherParameterTypes>
		auto AcceptAsTemp ( Visitor&& visitor, OtherParameterTypes&&...other_parameters ) const
		{
			static const auto table = GetVirtualTableDispatchClass<Visitor, OtherParameterTypes...>::GetConstTemp ( );

			return table [ type_index_ ] ( data_, std::forward<Visitor> ( visitor ), std::forward<OtherParameterTypes> ( other_parameters )... );
		}
	};

	template<class Visitor, class...OtherTypes>
	static auto MakeVisit ( Visitor&& visitor, OtherTypes&&...other_parameters )
	{
		return visitor ( std::forward<OtherTypes> ( other_parameters )... );
	}
	template<class Visitor, class BaseClass, class FirstRoomType, class SecondRoomType, class...OtherRoomTypes, class...OtherTypes >
	static auto MakeVisit ( Visitor&& visitor, Room<BaseClass, FirstRoomType, SecondRoomType, OtherRoomTypes...>& room, OtherTypes&&...other_parameters )
	{
		return room.Accept ( std::forward<Visitor> ( visitor ), std::forward<OtherTypes> ( other_parameters )... );
	}
	template<class Visitor, class BaseClass, class FirstRoomType, class SecondRoomType, class...OtherRoomTypes, class...OtherTypes >
	static auto MakeVisit ( Visitor&& visitor, const Room<BaseClass, FirstRoomType, SecondRoomType, OtherRoomTypes...>& room, OtherTypes&&...other_parameters )
	{
		return room.Accept ( std::forward<Visitor> ( visitor ), std::forward<OtherTypes> ( other_parameters )... );
	}
	template<class Visitor, class BaseClass, class FirstRoomType, class SecondRoomType, class...OtherRoomTypes, class...OtherTypes >
	static auto MakeVisit ( Visitor&& visitor, Room<BaseClass, FirstRoomType, SecondRoomType, OtherRoomTypes...>&& room, OtherTypes&&...other_parameters )
	{
		return room.AcceptAsTemp ( std::forward<Visitor> ( visitor ), std::forward<OtherTypes> ( other_parameters )... );
	}
	template<class Visitor, class BaseClass, class FirstRoomType, class SecondRoomType, class...OtherRoomTypes, class...OtherTypes >
	static auto MakeVisit ( Visitor&& visitor, const Room<BaseClass, FirstRoomType, SecondRoomType, OtherRoomTypes...>&& room, OtherTypes&&...other_parameters )
	{
		return room.AcceptAsTemp ( std::forward<Visitor> ( visitor ), std::forward<OtherTypes> ( other_parameters )... );
	}

	template<class Type, class Visitor, class...OtherParameterTypes>
	typename std::remove_reference<Visitor>::type::ReturnType BaseRoom::Dispatch ( void*const object, Visitor&& visitor, OtherParameterTypes&&...other_parameters )
	{
		return MakeVisit ( std::forward<Visitor> ( visitor ), std::forward<OtherParameterTypes> ( other_parameters )..., *reinterpret_cast< Type* >( object ) );
	}

	template<class Type, class Visitor, class...OtherParameterTypes>
	typename std::remove_reference<Visitor>::type::ReturnType BaseRoom::DispatchConst ( const void*const object, Visitor&& visitor, OtherParameterTypes&&...other_parameters )
	{
		return MakeVisit ( std::forward<Visitor> ( visitor ), std::forward<OtherParameterTypes> ( other_parameters )..., *reinterpret_cast< const Type* >( object ) );
	}

	template<class Type, class Visitor, class...OtherParameterTypes>
	typename std::remove_reference<Visitor>::type::ReturnType BaseRoom::DispatchTemp ( void*const temp_object, Visitor&& visitor, OtherParameterTypes&&...other_parameters )
	{
		return MakeVisit ( std::forward<Visitor> ( visitor ), std::forward<OtherParameterTypes> ( other_parameters )..., std::move ( *reinterpret_cast< Type* >( temp_object ) ) );
	}

	template<class Type, class Visitor, class...OtherParameterTypes>
	typename std::remove_reference<Visitor>::type::ReturnType BaseRoom::DispatchConstTemp ( const void*const temp_object, Visitor&& visitor, OtherParameterTypes&&...other_parameters )
	{
		return MakeVisit ( std::forward<Visitor> ( visitor ), std::forward<OtherParameterTypes> ( other_parameters )..., std::move ( *reinterpret_cast< const Type* >( temp_object ) ) );
	}
}