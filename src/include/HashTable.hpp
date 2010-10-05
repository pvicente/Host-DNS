#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <stdint.h>
#include "NonCopyable.hpp"
#include "String.hpp"

namespace utils
{
	class HashTable;

/**
* @brief Implement HashNode with StringKey and double ptr to implement a double linked list for buckets in HashTable
*/
	class HashNode
	{
		private:
		String m_Key;
		HashNode *m_next;
		HashNode *m_back;

		friend class HashTable;

		public:
		explicit HashNode(const String &p_Key):m_Key(p_Key), m_next(NULL), m_back(NULL){}
		HashNode(const HashNode &c):m_Key(c.m_Key), m_next(NULL), m_back(NULL){}

		virtual ~HashNode(){}
		
		HashNode& operator=(const HashNode &c)
		{
			m_Key = c.m_Key;
			m_next = NULL;
			m_back = NULL;

			return *this;
		}

		const String& GetKey() const
		{
			return m_Key;
		}
	};

	class HashTable:public NonCopyable
	{
		private:
		HashNode** m_table;
		std::size_t m_actual_size;
		std::size_t m_allocated_size;
		std::size_t m_collisions;

/**
* @brief Find HashNode with p_Key in List of HashNodes
*
* @param p_Key String with the key
* @param p_List List
*
* @return HashNode if successful or NULL if not founded
*/
		HashNode* _find(const String &p_Key, HashNode *p_List);


/**
* @brief Insert p_Node in hash_table with size p_Size
*
* @param p_Node
* @param p_Table
* @param p_Size
*
* @return true if successful or false if already exists
*/
		bool _insert_node(HashNode *p_Node, HashNode **p_Table, std::size_t p_Size);

/**
* @brief Remove all elementes in p_List
*
* @param p_List
*/
		void _remove_list(HashNode *p_List);

/**
* @brief Rehashing table with new size
*
* @param p_size
*/
		void _realloc(std::size_t p_size) throw();

		public:
/**
* @brief Construct hash table with allocated p_size
*
* @param p_size
*/
		explicit HashTable(std::size_t p_size);

		~HashTable();

/**
* @brief Return elements in hash table
*
* @return
*/
		std::size_t length() const;

/**
* @brief To debug only return number of collisions
*
* @return
*/
		std::size_t collisions() const;

/**
* @brief Insert HashNode in table
*
* @param p_Node
*
* @return True if successful or False if already exists
*/
		bool insert(HashNode* p_Node);

/**
* @brief Find HashNode with key p_Key
*
* @param p_key
*
* @return HashNode if successful or NULL if not
*/
		HashNode* find(const String &p_key);

/**
* @brief Remove HashNode with p_Key in table and return it
*
* @param p_key
*
* @return return HashNode* if successful or NULL if don't exists
*/
		HashNode* erase(const String &p_key);
	};

}


#endif

