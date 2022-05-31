#ifndef queue_hpp
#define queue_hpp

#include "list.hpp"

namespace adt
{
    // * QUEUE IMPLIMENTATION
    // * if the size is not -1, the queue is fixed size
    // * used size -1 (or no size) for dynamic queue
    template<typename _node_type, int _size = -1>
    class queue
    {
    public:

        queue() {}
        queue(std::initializer_list<_node_type> t_initalizer_list)
        {
            // * loop through each item in initalizer list
            for (auto item : t_initalizer_list)
            {
                // * add each item to the stack
                enqueue(item);
            }
        }

        void enqueue(_node_type t_val)
        {
            if (size() >= _size)
            {
                throw std::runtime_error("QUEUE ERROR: NOT ENOUGH ROOM IN QUEUE");
            }
            // * set the new value and rest the rear pointer
            m_data[m_rear] = t_val;
            m_rear = (m_rear + 1) % _size;
            m_size++;
        }

        _node_type dequeue()
        {
            if (empty())
            {
                throw std::runtime_error("QUEUE ERROR: CANNOT DEQUEUE EMPTY QUEUE");
            }
            // * set the new value and reset the front pointer
            _node_type retval = m_data[m_front];
            m_front = (m_front + 1) % _size;
            m_size--;

            return retval;
        }

        _node_type peek() const
        {
            // * return top of queue
            return m_data[m_front];
        }

        bool full() const
        {
            // * compare the position iterator to the size 
            return (m_front >= m_rear) && !empty();
        }

        bool empty() const
        {
            // * compare the size of the queue to zero
            return m_size == 0;
        }

        int size() const
        {
            // * return the size
            return m_size;
        }

        int max_size() const
        {
            // * return the maximum stack size
            return _size;
        }

        void clear()
        {
            // * set the size to zero
            m_size = 0;
            // * set the front of the queue to zero
            m_front = 0;
            // * set the rear of the queue to zero
            m_rear = 0;
        }

    private:

        // * store the posoitions
        int m_front = 0;
        int m_rear = 0;
        int m_size = 0;
        // * store the queue data
        _node_type m_data[_size];
    };

    // * dynamic queue implimentation
    template<typename _node_type>
    class queue<_node_type, -1>
    {
    public:

        queue() {}
        queue(std::initializer_list<_node_type> t_initalizer_list)
        {
            // * loop through each item in initalizer list
            for (auto item : t_initalizer_list)
            {
                // * add each item to the stack
                enqueue(item);
            }
        }

        void enqueue(_node_type t_val)
        {
            // * increment the position iterator and set stack new value
            m_data.push_back(t_val);
        }

        _node_type dequeue()
        {
            // * decrement the position iterator and return value
            return m_data.pop_front();
        }

        _node_type peek() const
        {
            // * return fromt of quque
            return m_data.front();
        }

        int size()
        {
            // * return the size of the queue list
            return m_data.size();
        }

        bool empty()
        {
            // * return if the data list is empty
            return m_data.empty();
        }

        void clear()
        {
            // * clear the underlying queue data
            m_data.clear();
        }

    private:
        
        // * store the queue data
        list<_node_type> m_data;
    };
}

#endif