#include "HashTable.hpp"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <new>

namespace utils
{
	static const float realloc_factor = 0.8;

	static int is_prime(std::size_t num)
	{
		register unsigned int i ;

		for (i = 2; i<num && (num % i) != 0; i++);
		return (i == num);
	}

	static std::size_t get_next_prime(std::size_t i)
	{
		for(;!is_prime(i);i++);
		return i;
	}	

	static std::size_t MyHash(const String& str)
	{
		std::size_t seed = 0;

		for(std::size_t i = 0; i < str.length(); i++)
		{
			seed ^= tolower(str[i]) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		}
		return seed;
	}

	HashNode* HashTable::_find(const String &p_Key, HashNode *p_List)
	{	
		HashNode *i = p_List;
		for (;i != NULL && strcasecmp(i->GetKey().c_str(), p_Key.c_str()) != 0; i = i->m_next);
		
		return i; 
	}

	bool HashTable::_insert_node(HashNode *p_Node, HashNode **p_Table, std::size_t p_size)
	{
		if (!p_Node || !p_Table)
			return false;

		const String &key = p_Node->GetKey();

		std::size_t hash_value = MyHash(key) % p_size;
		HashNode* actual_list = p_Table[hash_value];

		if (_find(key, actual_list) != NULL)
			return false;

		if (actual_list != NULL)
		{
			m_collisions++;
			actual_list->m_back = p_Node;
		}

		p_Table[hash_value] = p_Node;
		p_Node->m_next = actual_list;

		return true;
	}

	void HashTable::_remove_list(HashNode *p_List)
	{
		HashNode *temp = NULL;

		while (p_List != NULL)
		{
			temp = p_List;
			p_List = p_List->m_next;
			delete temp;
		}
	}

	void HashTable::_realloc(std::size_t p_size) throw()
	{
		uint32_t new_size = get_next_prime(p_size);
		if (new_size == m_allocated_size)
			return;

		HashNode **new_table = reinterpret_cast<HashNode**>(calloc(new_size, sizeof(HashNode*)));
		if (!new_table)
		{
			throw std::bad_alloc();
		}

		m_collisions = 0; //Reset collisions

		for (uint32_t i = 0; i < m_allocated_size; i++)
		{
			HashNode *actual = m_table[i];
			HashNode *temp = NULL;

			while (actual != NULL)
			{
				temp = actual->m_next;
				if (_insert_node(actual, new_table, new_size))
				{
					m_table[i] = temp;
					actual = temp;
				}
				else
				{
					abort(); //must not happen
				}
			}
		}

		free(m_table);

		m_table = new_table;
		m_allocated_size = new_size;
	}

	HashTable::HashTable(std::size_t p_size):m_table(NULL), m_actual_size(0), m_allocated_size(0), m_collisions(0)
	{
		_realloc(p_size);
	}

	HashTable::~HashTable()
	{
		for (uint32_t i = 0; i < m_allocated_size; i++)
		{
			if (m_table[i] != NULL)
			{
				_remove_list(m_table[i]);
				m_table[i] = NULL;
			}
		}
		free(m_table);
	}


	std::size_t HashTable::length() const
	{
		return m_actual_size;
	}

	std::size_t HashTable::collisions() const
	{
		return m_collisions;
	}

	bool HashTable::insert(HashNode *p_Node)
	{
		float factor = ((float) m_actual_size) / m_allocated_size;

		if (factor > realloc_factor)
		{
			_realloc(m_allocated_size * 2);
		}
		
		if (_insert_node(p_Node, m_table, m_allocated_size))
		{
			m_actual_size++;
			return true;
		}

		return false;
	}

	HashNode* HashTable::find(const String &p_Key)
	{
		std::size_t hash = MyHash(p_Key) % m_allocated_size;
		
		return _find(p_Key, m_table[hash]);
	}

	HashNode* HashTable::erase(const String &p_Key)
	{
		std::size_t hash = MyHash(p_Key) % m_allocated_size;

		HashNode *res = NULL;
		res = _find(p_Key, m_table[hash]);

		if (res)
		{
			if (res->m_back == NULL) //First element
			{
				m_table[hash] = res->m_next;
				if (m_table[hash])
					m_table[hash]->m_back = NULL;
			}
			else
			{
				res->m_back->m_next = res->m_next;
				if (res->m_next)
					res->m_next->m_back = res->m_back;
			}

			m_actual_size--;
		}

		return res;	
	}
}

