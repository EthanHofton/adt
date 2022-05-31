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
    
    // * heap implimentation
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

            // * create the heap
            createHeap();
        }

        void peek() const
        {
            // * return the front of the heap (first element)
            return m_data.front();
        }

        void pop()
        {
            // * alogorihm for popping from heap:
            // *    (-) swap the first and the last
            // *    (-) remove the last element from the heap
            // *    (-) reconstruct heap
            // * first check if the size of the heap is 1
            if (m_data.size() == 1)
            {
                // * delete the last element of the heap
                m_data.pop_back();
                // * nothing left in the heap, so just return
                return;
            }
            // * swap the first and the last element
            // * get an iterator to the end of the list
            auto end = m_data.end();
            // * decrement the end
            end--;
            // * stop the beggining and the end
            std::swap(*m_data.begin(), *(end));
            // * remove the last element
            m_data.pop_back();
            // * reconstuct the heap
            createHeap();
        }

        void push(_node_type t_data)
        {
            // * push algortihm:
            // *    (-) add the new item to the end of the list
            // *    (-) reconstruct the heap
            // * add new item to list
            m_data.push_back(t_data);
            // * reconstuct heap
            createHeap();
        }

        int size() const
        {
            // * return the size of the data
            return m_data.size();
        }

    public:

        // * std functions

        // * std cout
        friend std::ostream& operator<<(std::ostream& t_out, const heap<_node_type, _heap_type>& l)
        {
            l.printPretty(t_out, 0, "", true);
            return t_out;
        }

    private:

        // * private helper functions

        void printPretty(std::ostream& out, const int& node, std::string indent, const bool& last) const
        {
            // * indent out
            out << indent;
            // * check if the node is the last child
            if (last)
            {
                // * print list child marker
                out << "\\-";
                // * add space to indent
                indent += "  ";
            } else {
                // * print child maker
                out << "|-";
                // * add tree root to indent
                indent += "| ";
            }

            // * print the node name
            out << m_data[node] << std::endl;


            // * loop through each child of the node        
            for (int i = 1; i <= 2 && (node*2)+i < m_data.size(); i++)
            {
                // recerivly call pretty print again for each child
                printPretty(out, (node*2)+i, indent, i == 2);
            }
        }

        void createHeap()
        {
            // * call heapify to convert compleate binary tree to heap
            // * maintain heap invarient
            // * start from first no-leaf node and iter to zero
            // *    (-): (n / 2) - 1 is first leaf node
            for (int i = int(m_data.size() / 2) - 1; i >= 0; i--)
            {
                heapify(i);
            }
        }

        void heapify(int t_i)
        {
            // * get the beginning of the data
            typename adt::list<_node_type>::iterator pos = m_data.begin();
            // * advance the interator to position i
            std::advance(pos, t_i);
            // * get a pointer to the largest data value
            _node_type *largest = &(*pos);
            // * get a refernce to the left child, if has no child, it is equal to largest
            _node_type &left_child = (2*t_i + 1 < m_data.size()) ? m_data[2*t_i + 1] : *largest;
            // * get a refernce to the right child, if has no child, it is equal to largest
            _node_type &right_child = (2*t_i + 2 < m_data.size()) ? m_data[2*t_i + 2] : *largest;

            // * compare largest against left child, check weather min or max heap to take either gratest value or smallest
            if ((_heap_type == heap_types::max_heap) ? left_child > *largest : left_child < *largest)
            {
                // * set largest to left value
                largest = &left_child;
            }

            // * compare largest against right child, check weather min or max heap to take either gratest value or smallest
            if ((_heap_type == heap_types::max_heap) ? right_child > *largest : right_child < *largest)
            {
                // * set largest to right value
                largest = &right_child;
            }

            // * swap the values of pos and largest
            std::swap(*pos, *largest);
        }

    private:

        // * store heap data
        list<_node_type> m_data;
    };
}

#endif