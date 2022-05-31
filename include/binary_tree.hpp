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
    public:

        // * binary tree root constructor
        binary_tree(_node_type t_root)
        {

        }

        // * binary tree initalizer list constructor
        binary_tree(std::initializer_list<_node_type> t_init_list)
        {

        }

        // * binary tree initalizer list equals overload
        binary_tree& operator=(const std::initializer_list<_node_type> t_init_list)
        {
            
        }

        // * binary tree binary tree equals overload
        binary_tree& operator=(const binary_tree<_node_type>&t_other)
        {

        }

        ~binary_tree() 
        {
            // * delete the root node and let node destructor recevivley delete the rest
            
            // * check if the root node is not null
            if (m_root != nullptr)
            {
                // * delete the root node
                delete m_root;
            }
        }

    private:

        // * binary tree node
        // * stores data and node flags such as:
        // *    (-) visited flag
        // *    (-) node data
        // *    (-) node parent
        // *    (-) node left and right child
        struct binary_tree_node
        {
            // * node data
            _node_type m_data;

            // * node parent pointer
            binary_tree_node* m_parent = nullptr;
            // * node children pointer
            binary_tree_node* m_lchild = nullptr;
            binary_tree_node* m_rchild = nullptr;

            // * node flags
            bool m_visied = false;

            // * binary tree node destructor
            ~binary_tree_node()
            {
                // * recervily deelte all nodes in a tree by deleting the root node
                // * by deleting each nodes children in the destructor

                // * delete the left node if not null
                if (m_lchild != nullptr)
                {
                    delete m_lchild;
                }

                // * delete the right node if node null
                if (m_rchild != nullptr)
                {
                    delete m_rchild;
                }
            }
        };

    private:

        // * store the root of the tree
        binary_tree_node* m_root = nullptr;

    };
}

#endif