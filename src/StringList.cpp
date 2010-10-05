#include "StringList.hpp"

namespace utils
{
	struct StringNode: public String
	{
		StringNode *next;
		StringNode *back;

		explicit StringNode(const String &c):String(c), next(NULL), back(NULL)
		{

		}
	};


typedef StringList::iterator Titerator;


	Titerator::iterator(const StringNode *c):m_node(const_cast<StringNode*>(c))
	{
	}

	Titerator::iterator(const Titerator &c):m_node(c.m_node)
	{
	}

	Titerator& Titerator::operator=(const Titerator &c)
	{
		m_node = c.m_node;
		return *this;
	}

	Titerator Titerator::operator++(int)
	{
		Titerator res(*this);
		
		if (m_node)
		{
			m_node = m_node->next;
		}

		return res;
	}

	String& Titerator::operator*() const
	{
		return *m_node;
	}	

	bool Titerator::operator==(const Titerator &c) const
	{
		return m_node == c.m_node;
	}

	bool Titerator::operator!=(const Titerator &c) const
	{
		return !(*this == c);
	}

/***************************************************************/
	
	StringList::StringList():m_head(NULL), m_end(NULL), m_size(0)
	{

	}

	StringList::~StringList()
	{
		clear();
	}

	void StringList::clear()
	{
		for (const StringNode *temp = m_head; temp != NULL; temp = m_head)
		{
			m_head = temp->next;
			delete temp;
		}

		m_end = NULL;
	}

	Titerator StringList::begin() const
	{
		return Titerator(m_head);
	}

	Titerator StringList::end() const
	{
		return Titerator(NULL);
	}

	std::size_t StringList::size() const
	{
		return m_size;
	}

	bool StringList::empty() const
	{
		return m_head == NULL && m_end == NULL;
	}

	String& StringList::back()
	{
		return *m_end;
	}

	String& StringList::top()
	{
		return *m_head;
	}

	void StringList::push_back(const String &c)
	{
		StringNode *temp(new StringNode(c));
		if (m_head == NULL)
		{
			m_head = m_end = temp;
		}
		else
		{
			m_end->next = temp;
			temp->back = m_end;
			m_end = temp;
		}

		m_size++;	
	}
	
	void StringList::push_front(const String &c)
	{
		StringNode *temp = new StringNode(c);
		if (m_head == NULL)
		{
			m_head = m_end = temp;
		}
		else
		{
			temp->next = m_head;
			m_head->back = temp;
			m_head = temp;
		}

		m_size++;
	}

	void StringList::pop_back()
	{
		if (m_head == NULL)
			return;

		StringNode * new_end = m_end->back;
		delete m_end;

		if (new_end == NULL)
		{
			m_head = m_end = NULL;
		}
		else
		{
			new_end->next = NULL;
			m_end = new_end;
		}

		m_size--;
	}

	void StringList::pop_front()
	{
		if (m_head == NULL)
			return;

		StringNode *new_head = m_head->next;
		delete m_head;

		if (new_head == NULL)
		{
			m_head = m_end = NULL;
		}
		else
		{
			new_head->back = NULL;
			m_head = new_head;
		}
	}

	Titerator StringList::insert(Titerator i, const String& c)
	{
		if (end() == i)
		{
			push_back(c);
			return Titerator(m_end);
		}

		if (begin() == i)
		{
			push_front(c);
			return Titerator(m_head);
		}

		StringNode *new_ele = new StringNode(c);

		new_ele->back = i.m_node->back;
		new_ele->next = i.m_node;

		i.m_node->back = new_ele;
		new_ele->back->next = new_ele;

		m_size--;

		return Titerator(new_ele);
	}

	Titerator StringList::erase(StringList::iterator i)
	{
		if (end() == i)
			return end();

		if (begin() == i)
		{
			pop_front();
			return begin();
		}

		if (Titerator(m_end) == i)
		{
			pop_back();
			return Titerator(m_end);
		}

		StringNode *temp = i.m_node;
		temp->back->next = temp->next;
		temp->next->back = temp->back;

		Titerator res(temp->next);
		delete temp;

		m_size--;

		return res;
	}

	Titerator StringList::find(const String &c) const
	{
		Titerator i = begin();
		for ( ; i != end() && *i != c; i++);

		return i;
	}
}




