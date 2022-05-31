#ifndef stack_hpp
#define stack_hpp

#include "list.hpp"

namespace adt
{
    // * stack definition
    // * if size is not -1, fixed size stack is used
    // * stack is implimented with fixed size arrays
    template<typename _node_type, int _size = -1>
    class stack 
    {
    public:

        stack() {}
        stack(std::initializer_list<_node_type> t_initalizer_list)
        {
            // * loop through each item in initalizer list
            for (auto item : t_initalizer_list)
            {
                // * add each item to the stack
                push_back(item);
            }
        }

        void push_back(_node_type t_val)
        {
            // * increment the position iterator and set stack new value
            m_data[*(m_pos++)] = t_val;
        }

        _node_type pop_back()
        {
            // * decrement the position iterator and return value
            return m_data[*(m_pos--)];
        }

        _node_type peek() const
        {
            // * return top of stack
            return m_data[(*m_pos) - 1];
        }

        bool full() const
        {
            // * compare the position iterator to the size 
            return (*m_pos == _size);
        }

         bool empty() const
        {
            return size() == 0;
        }

        int size() const
        {
            // * return the size
            return *m_pos;
        }

        int max_size() const
        {
            // * return the maximum stack size
            return _size;
        }

        void clear()
        {
            // * reset the start point
            m_pos = 0;
        }

    private:

        // * iterator class
        class iterator : public std::iterator<std::bidirectional_iterator_tag, int>
        {
        public:
            explicit iterator(int t_pos = 0) { m_pos = t_pos; }
            iterator& operator=(const int &t_val) { m_pos = t_val; return (*this); }
            iterator& operator++() { m_pos++; return *this; }
            iterator operator++(int) { iterator retval = (*this); ++(*this); return retval; }
            iterator& operator--() { m_pos--; return *this; }
            iterator operator--(int) { iterator retval = (*this); --(*this); return retval; }
            bool operator==(const iterator& t_other) const { return (t_other.m_pos == m_pos); }
            bool operator!=(const iterator& t_other) const { return !(*this == t_other); }
            const int& operator*() const { return m_pos; }

        private:

            int m_pos;
        };

        iterator m_pos;
        _node_type m_data[_size];
    };

    // * variable size stack implimentation
    // * stack implimented using linked lists
    template<typename _node_type>
    class stack<_node_type, -1>
    {
    public:

        stack() {}
        stack(std::initializer_list<_node_type> t_initalizer_list)
        {
            // * loop through each item in initalizer list
            for (auto item : t_initalizer_list)
            {
                // * add each item to the stack
                push_back(item);
            }
        }

        void push_back(_node_type t_val)
        {
            // * increment the position iterator and set stack new value
            m_data.push_back(t_val);
        }

        _node_type pop_back()
        {
            // * decrement the position iterator and return value
            return m_data.pop_back();
        }

        _node_type peek() const
        {
            // * return top of stack
            return m_data.back();
        }

        int size() const
        {
            // * return the size of the stack list
            return m_data.size();
        }

        bool empty() const
        {
            // * return if the data list is empty
            return m_data.empty();
        }

        void clear()
        {
            // clear the underlying data
            m_data.clear();
        }

    private:
        
        // * store the stack data
        list<_node_type> m_data;
    };
}

#endif