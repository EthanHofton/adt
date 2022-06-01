#ifndef binary_tree_hpp
#define binary_tree_hpp

#include "list.hpp"

namespace adt
{
    // * bianry tree
    // * tree starts from the root node
    // * each node can have 2 children
    template<typename _node_type>
    class binary_tree
    {
    friend class binary_tree_node;
    public:

        // * binary tree root constructor
        binary_tree(const _node_type& t_root)
        {
            // * create a new root node
            m_root = new binary_tree_node(t_root);
        }

        // * binary tree initalizer list constructor
        // * takes std::initalizer_list as argument
        // * this reprents a complete tree level order array
        binary_tree(const std::initializer_list<_node_type>& t_init_list)
        {
            // * create the initalizer list as an adt::list
            adt::list<_node_type> init_list = t_init_list;
            // * set root
            m_root = insert_level_order(init_list, 0);
        }

        // * binary tree initalizer list constructor
        // * takes adt::list as argument
        // * this reprents a complete tree level order array
        binary_tree(const adt::list<_node_type>& t_input_list)
        {
            // * set root
            m_root = insert_level_order(t_input_list, 0);
        }

        // * binary tree initalizer list equals overload
        binary_tree& operator=(const std::initializer_list<_node_type>& t_init_list)
        {
            // * clear the tree
            clear();

            // * create an adt::list from the initalizer list
            adt::list<_node_type> init_list = t_init_list;

            // * set the root
            m_root = insert_level_order(init_list, 0);

            return *this;
        }

        // * binary tree initalizer list equals overload
        binary_tree& operator=(const adt::list<_node_type>& t_input_list)
        {
            // * clear the tree
            clear();

            // * set the root
            m_root = insert_level_order(t_input_list, 0);

            return *this;
        }

        // * binary tree binary tree equals overload
        binary_tree& operator=(const binary_tree<_node_type>&t_other)
        {
            // * algorithm to create a new tree:
            // *    (-) delete the root
            // *    (-) create a new node for each node in the other tree
            // * clear the tree
            clear();


            return (*this);
        }

        ~binary_tree() 
        {
            // * clear the tree from the root
            clear();
        }

        // * clear tree from root
        void clear()
        {
            // * clear from root node
            clear_from(m_root);
        }

        binary_tree<int>::binary_tree_node& reset(_node_type t_root)
        {
            // * clear the tree
            clear();

            // * reset the root to the selected value
            m_root = new binary_tree_node(t_root);

            // * return deref root
            return *m_root;
        }

    public:

        // * std functions

        friend std::ostream& operator<<(std::ostream &t_out, const binary_tree<_node_type> &t_tree)
        {
            t_tree.pretty_print(t_out, t_tree.m_root, "", true);

            return t_out;
        }

    public:

        // * binary tree node
        // * stores data and node flags such as:
        // *    (-) visited flag
        // *    (-) node data
        // *    (-) node parent
        // *    (-) node left and right child
        class binary_tree_node
        {
        friend class binary_tree<_node_type>;

        private:
            // * node data
            _node_type m_data;

            // * node parent pointer
            binary_tree_node* m_parent = nullptr;
            // * node children pointer
            binary_tree_node* m_lchild = nullptr;
            binary_tree_node* m_rchild = nullptr;

            // * node flags
            bool m_visied = false;

        private:

            binary_tree_node(const _node_type& t_data)
            {
                m_data = t_data;
            }

        public:

            _node_type get_data() const
            {
                return m_data;
            }

            binary_tree_node& get_parent() const
            {
                return *m_parent;
            }

            binary_tree_node& get_left_child() const
            {
                return *m_lchild;
            }

            binary_tree_node& get_right_child() const
            {
                return *m_rchild;
            }

            bool was_visited() const
            {
                return m_visied;
            }

            void set_data(_node_type t_data)
            {
                m_data = t_data;
            }

            void set_left_child(const _node_type& t_data)
            {
                if (m_lchild != nullptr)
                {
                    clear_from(m_lchild);
                }

                m_lchild = new binary_tree_node(t_data);
            }

            void set_right_child(const _node_type& t_data)
            {
                if (m_rchild != nullptr)
                {
                    clear_from(m_rchild);
                }

                m_rchild = new binary_tree_node(t_data);
            }

            void set_visited(bool t_visited)
            {
                m_visied = t_visited;
            }
        };

    private:

        // * private helper functions

        // * clear tree from a node
        static void clear_from(binary_tree_node *t_start)
        {
            // * do not do anything if null
            if (t_start == nullptr)
            {
                return;
            }

            // * clear the the left sub tree
            if (t_start->m_lchild != nullptr)
            {
                clear_from(t_start->m_lchild);
            }

            // * clear the the right sub tree
            if (t_start->m_rchild != nullptr)
            {
                clear_from(t_start->m_rchild);
            }

            // * delete the starting node
            delete t_start;
        }

        binary_tree_node* insert_level_order(const adt::list<_node_type>& t_arr, int t_i)
        {
            // * initalize a root as nullptr
            binary_tree_node* root = nullptr;

            // * if i is in range
            if (t_i < t_arr.size())
            {
                // * create a new root node
                root = new binary_tree_node(t_arr[t_i]);
                // * recerivly set right child
                root->m_lchild = insert_level_order(t_arr, 2*t_i + 1);
                // * set childs parent to root if not null
                if (root->m_lchild != nullptr)
                {
                    root->m_lchild->m_parent = root;
                }
                // * recerivly set left child
                root->m_rchild = insert_level_order(t_arr, 2*t_i + 2);
                // * set childs parent to root if not null
                if (root->m_rchild != nullptr)
                {
                    root->m_rchild->m_parent = root;
                }
            }

            return root;
        }

        // * pretty print
        void pretty_print(std::ostream &t_out, binary_tree_node* t_n, std::string t_indent, bool t_last) const
        {
            // * indent out
            t_out << t_indent;
            // * check if the node is the last child
            if (t_last)
            {
                // * print list child marker
                t_out << "\\-";
                // * add space to indent
                t_indent += "  ";
            } else {
                // * print child maker
                t_out << "|-";
                // * add tree root to indent
                t_indent += "| ";
            }

            // * print the node name
            t_out << t_n->m_data << std::endl;

            if (t_n->m_lchild != nullptr)
            {
                pretty_print(t_out, t_n->m_lchild, t_indent, t_n->m_rchild == nullptr);
            }

            if (t_n->m_rchild != nullptr)
            {
                pretty_print(t_out, t_n->m_rchild, t_indent, true);
            }
        }

    private:

        // * store the root of the tree
        binary_tree_node* m_root = nullptr;

    };
}

#endif