#ifndef list_hpp
#define list_hpp

#include <iterator>
#include <initializer_list>

namespace adt
{
    // * LINK LIST
    // * doubled ended linked list implimentation
    // * keep track of the front and back of the list
    template<typename _node_type>
    class list
    {
    public:

        // * list node structure to store node data
        struct list_node
        {
            _node_type m_data;
            list_node* m_parent = nullptr;
            list_node* m_child = nullptr;

            ~list_node()
            {
                if (m_child != nullptr)
                {
                    delete m_child;
                }
            }
        };

    public:

        // * list constructor and destructor
        list() 
        {
            // * create dummy head node
            m_head = new list_node;
            // * create dummy tail node
            m_tail = new list_node;

            // * set heads child to tail
            m_head->m_child = m_tail;
            // * set tails parent to head
            m_tail->m_parent = m_head;
        }

        list(std::initializer_list<_node_type> t_initalizer_list) : list()
        {
            for (auto item : t_initalizer_list)
            {
                push_back(item);
            }
        }

        list<_node_type>& operator=(const std::initializer_list<_node_type>& t_init_list)
        {
            clear();

            for (auto item : t_init_list)
            {
                push_back(item);
            }

            return *this;
        }

        list<_node_type>& operator=(const list<_node_type>& t_other)
        {
            clear();

            for (auto item : t_other)
            {
                push_back(item);
            }

            return *this;
        }

        ~list()
        {
            // * this will recersivley delete all of the heads children
            delete m_head;
        }

        _node_type &at(int t_pos) const
        {
            if (m_size <= t_pos)
            {
                throw std::runtime_error("SIZE ERROR: cannot read at this position");
            }

            list_node* n = m_head->m_child;
            for (int i = 0; i < t_pos; i++)
            {
                n = n->m_child;
            }

            return n->m_data;
        }

        _node_type& operator[](int t_pos) const
        {
            return at(t_pos);
        }

        void insert(int t_pos, _node_type t_val)
        {
            if (m_size < t_pos)
            {
                throw std::runtime_error("SIZE ERROR: cannot read at this position");
            }

            // * find the target node
            list_node* target_node = m_head->m_child;
            for (int i = 0; i < t_pos; i++)
            {
                target_node = target_node->m_child;
            }

            // * create a new node
            list_node* new_node = new list_node();
            // * set new node data
            new_node->m_data = t_val;
            // * set new node parent to target nodes parent
            new_node->m_parent = target_node->m_parent;
            // * set new nodes child to target node
            new_node->m_child = target_node;

            // * new node parent
            new_node->m_parent->m_child = new_node;
            // * new node child
            new_node->m_child->m_parent = new_node;

            // * increase the size
            m_size++;
        }

        void push_back(_node_type t_val)
        {
            insert(m_size,t_val);
        }

        void push_front(_node_type t_val)
        {
            insert(0,t_val);
        }

        _node_type pop(int t_pos)
        {
            if (m_size < t_pos)
            {
                throw std::runtime_error("SIZE ERROR: cannot read at this position");
            }

            // * find the target node
            list_node* target_node = m_head->m_child;
            for (int i = 0; i < t_pos; i++)
            {
                target_node = target_node->m_child;
            }

            // * set the targets nodes parents child to the targets node child
            target_node->m_parent->m_child = target_node->m_child;
            // * set the target nodes child parent to the target nodes parent
            target_node->m_child->m_parent = target_node->m_parent;
            // * all references to target node have been removed from the linked list
            // * store the value to retern
            _node_type data = target_node->m_data;

            // * clear pointers to children before delleting
            // * this stops the target nodes children from being reversivly deleted
            target_node->m_child = nullptr;
            target_node->m_parent = nullptr;

            // * delete 
            delete target_node;


            // decremnt the size
            m_size--;

            // return the data
            return data;
        }

        _node_type pop_front()
        {
            return pop(0);
        }

        _node_type pop_back()
        {
            return pop(m_size - 1);
        }

        bool empty() const
        {
            // check the size is zero
            return m_size == 0;
        }

        void clear()
        {
            // * this will delete the whole list
            delete m_head;

            // * create dummy head node
            m_head = new list_node;
            // * create dummy tail node
            m_tail = new list_node;

            // * set heads child to tail
            m_head->m_child = m_tail;
            // * set tails parent to head
            m_tail->m_parent = m_head;

            // * set size to zero
            m_size = 0;
        }

        _node_type front() const
        {
            // * read the data fater the dummy heads childs data
            return m_head->m_child->m_data;
        }

        _node_type back() const
        {
            // * read the data before the tails dummy
            return m_tail->m_parent->m_data;
        }

        int size() const
        {
            return m_size;
        }

    public:

        // * std functions

        // * iterator class
        class iterator : public std::iterator<std::bidirectional_iterator_tag, _node_type>
        {
        public:
            explicit iterator(list<_node_type>::list_node *t_start) { m_node = t_start; }
            iterator& operator++() { m_node = m_node->m_child; return *this; }
            iterator operator++(int) { iterator retval = (*this); ++(*this); return retval; }
            iterator& operator--() { m_node = m_node->m_parent; return *this; }
            iterator operator--(int) { iterator retval = (*this); --(*this); return retval; }
            bool operator==(const iterator& t_other) const { return (t_other.m_node == m_node); }
            bool operator!=(const iterator& t_other) const { return !(*this == t_other); }
            _node_type& operator*() const { return m_node->m_data; }

        private:

            list<_node_type>::list_node *m_node;
        };

        // * begin and end
        iterator begin() const { return iterator(m_head->m_child); }
        iterator end() const { return iterator(m_tail); }

        // * std cout
        friend std::ostream& operator<<(std::ostream& t_out, const list<_node_type>& l)
        {
            t_out << "{";
            for (int i = 0; i < l.m_size - 1; i++)
            {
                t_out << l[i] << ", ";
            }

            if (!l.empty())
            {
                t_out << l.back() << "}";
            }

            return t_out;
        }

    private:

        // * store the head of the list
        list_node* m_head = nullptr;
        // * store the tail of the list
        list_node* m_tail = nullptr;

        // * store the size
        int m_size = 0;
    };
}

#endif