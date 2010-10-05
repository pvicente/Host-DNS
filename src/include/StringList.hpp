#ifndef STRING_LIST_HPP
#define STRING_LIST_HPP

#include "String.hpp"
#include "NonCopyable.hpp"

namespace utils
{
	class StringNode;

/**
* @brief Implements a particular StringList with similar std interface
*/
	class StringList: public NonCopyable
	{
		public:
/**
* @brief implements interator over StringList similar to std
*/
		class iterator
		{
			private:
			iterator();

			private:
			StringNode *m_node;
			friend class StringList;

			public:
			explicit iterator(const StringNode *c);
			iterator(const iterator &c);
		
			iterator& operator=(const iterator &c);

			iterator operator++(int);
			String& operator*() const;

			bool operator==(const iterator &c) const;
			bool operator!=(const iterator &c) const;
		};

		private:
		StringNode *m_head;
		StringNode *m_end;
		std::size_t m_size;

		public:
		StringList();

		~StringList();

		void clear();

		StringList::iterator begin() const;
		StringList::iterator end() const;

		std::size_t size() const;
		bool empty() const;

		String& back();
		String& top();

		void push_back(const String &c);
		void push_front(const String &c);

		void pop_back();
		void pop_front();

		StringList::iterator insert(StringList::iterator i, const String &c);

		StringList::iterator erase(StringList::iterator i);

		StringList::iterator find(const String &c) const;
	};
}

#endif

