#pragma once
#include <memory>
#include <mutex>

namespace data_structure
{
	template<class SingleType>
	class Singleton
	{
	public:
		static std::shared_ptr<SingleType> GetInstance ( )
		{
			static std::mutex mutex_;
			static std::weak_ptr<SingleType> single_object_;

			std::lock_guard<std::mutex> guard { mutex_ };
			auto shared_object = single_object_.lock ( );
			if ( !shared_object )
			{
				shared_object = std::make_shared<SingleType> ( );
				single_object_ = shared_object;
			}

			return shared_object;
		}
	};

	class Winsock : public Singleton<Winsock>
	{
	public:
		//API bullshit

	private:
		friend class Singleton<Winsock>;

		Winsock ( ) = default;

		//More API bullshit
	};
	std::mutex Singleton<Winsock>::mutex_ { };
	std::weak_ptr<Winsock> Singleton<Winsock>::single_object_ { };
}