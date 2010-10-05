#ifndef NON_COPIABLE_HPP
#define NON_COPIABLE_HPP

namespace utils
{
/**
* @brief Template class with no implementation to protect by inheritance copy constructor and assigment operator
*/
	class NonCopyable
	{
		protected:
		NonCopyable() {}
		~NonCopyable() {}

		private:  // emphasize the following members are private
		NonCopyable( const NonCopyable& );
		const NonCopyable& operator=( const NonCopyable& );
	};

}

typedef utils::NonCopyable NonCopyable;

#endif

