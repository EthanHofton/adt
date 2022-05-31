#ifndef heap_hpp
#define heap_hpp

#include "list.hpp"

namespace adt
{
    // * heap types enum
    enum class heap_types
    {
        min_heap,      // * for max heap
        max_heap       // * for min heap
    };
    
    // * min heap implimentation
    // * compleate tree that follows
    // * the heap invariant:
    // *    - all children must be less then the parent (max heap)
    // *    - all children must be more then the parent (min heap)
    template<typename _node_type, heap_types _heap_type = heap_types::max_heap>
    class heap
    {
    public:

        heap() {}
        heap(std::initializer_list<_node_type> t_initalizer_list)
        {
            // * takes initalizer list as compleate binary tree
            // * eg. first element is top node, next 2 emelments are second layer, ect...
            m_data = t_initalizer_list;
            // * call heapify to convert compleate binary tree to heap
            // * maintain heap invarient
            // heapify();
        }

        void peek()
        {
            return m_data.front();
        }

        void print()
        {
            std::cout << m_data << std::endl;
        }

    public:

        void heapify()
        {
            auto pos = m_data.begin();
            std::advance(pos, int(m_data.size() / 2) + 1);
            for (int i = 0; pos != m_data.end(); pos++)
            {
                _node_type *largest = &(*pos);
                _node_type &left_child = m_data[2*i + 1];
                _node_type &right_child = m_data[2*i + 2];

                if (left_child > *largest)
                {
                    largest = &left_child;
                }

                if (right_child > *largest)
                {
                    largest = &right_child;
                }

                std::swap(*pos, *largest);
            }
        }

    private:

        list<_node_type> m_data;
    };

    // * min heap implimentation
    template<typename _node_type>
    class heap<_node_type, heap_types::min_heap>
    {
    };
}

#endif