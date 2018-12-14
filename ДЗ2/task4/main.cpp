#include <iostream>
#include <queue>

template <class T>
class AVLTree {
  public:
    AVLTree() = default;
    ~AVLTree() {
        std::queue<Node*> node_queue;

        if (root != nullptr) {
            node_queue.push(root);
        }

        while (!node_queue.empty()) {
            Node* temp_node = node_queue.front();
            node_queue.pop();

            if (temp_node->left != nullptr) {
                node_queue.push(temp_node->left);
            }
            if (temp_node->right != nullptr) {
                node_queue.push(temp_node->right);
            }

            delete temp_node;
        }
    }

    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree& operator=(AVLTree&&) = delete;

    void add(const T& data) {
       root = inner_add(data, root);

    }
    void remove(const T& data) {
        root = inner_remove(data, root);
    }
    bool has(const T& data) = delete;

    T get_ord_statistic(size_t num) const {
        const auto* node = root;
        while (get_node_count(node->left) != num) {
            if (get_node_count(node->left) > num) {
                node = node->left;
            } else {
                num -= get_node_count(node->left) + 1;
                node = node->right;
            }
        }

        return node->data;
    }

  private:
    struct Node{
        T data;
        Node* left = nullptr;
        Node* right = nullptr;
        size_t height = 0;
        size_t node_count = 1;

        explicit Node(const T& _data, size_t _height = 1) :
            data(_data), height(_height) {
        }
    };

    Node* root = nullptr;

    Node* inner_add(const T& data, Node* node) {
        if (!node) {
            return new Node(data);
        }

        node->node_count++;

        if(data < node->data)
            node->left = inner_add(data, node->left);
        else
            node->right = inner_add(data, node->right);

        return balance(node);
    }
    Node* inner_remove(const T& data, Node* node) {
        if (!node) {
            return nullptr;
        }
        if (data < node->data) {
            node->left = inner_remove(data, node->left);
        } else if (data > node->data) {
            node->right = inner_remove(data, node->right);
        } else {
            auto *temp = node->left;
            auto *right = node->right;
            delete node;
            if (!right) {
                return temp;
            }
            auto *min = find_min(right);
            min->right = remove_min(right);
            min->left = temp;
            return balance(min);
        }
        return balance(node);
    }

    Node* balance(Node* node) {
        if (!node) {
            return nullptr;
        }

        fix_height(node);
        fix_node_count(node);  // TODO

        if (balance_factor(node) == 2) {
            if (balance_factor(node->right) < 0) {
                node->right = small_right_rotation(node->right);
            }
            return small_left_rotation(node);
        }
        if (balance_factor(node) == -2) {
            if (balance_factor(node->left) > 0) {
                node->left = small_left_rotation(node->left);
            }
            return small_right_rotation(node);
        }
        return node;
    }

    Node* small_left_rotation(Node*& node) {
        auto* temp = node->right;
        node->right = temp->left;
        temp->left = node;

        fix_node_count(node);
        fix_node_count(temp);

        fix_height(node);
        fix_height(temp);

        return temp;
    }
    Node* small_right_rotation(Node* node) {
        auto* temp = node->left;
        node->left = temp->right;
        temp->right = node;

        fix_node_count(node);
        fix_node_count(temp);

        fix_height(node);
        fix_height(temp);

        return temp;
    }
    Node* grand_left_rotation(Node*& node) {
        auto* temp_l = node->left->right->left;
        auto* temp_r = node->left->right->right;
        node->left->right->left = node->left;
        node->left->right->right = node;
        node = node->right->left;
        node->left->right = temp_l;
        node->right->left = temp_r;

        node->parent = node->left->parent;
        node->left->parent = node;
        node->right->parent = node;
        if (node->left->right) {
            node->left->right->parent = node->left;
        }
        if (node->right->left) {
            node->right->left->parent = node->right;
        }

        node->left->height = get_height(node->left);
        node->right->height = get_height(node->right);
        node->height = std::max(node->left->height, node->right->height);
    }
    Node* grand_right_rotation(Node*& node) {
        auto* temp_l = node->right->left->left;
        auto* temp_r = node->right->left->right;
        node->right->left->left = node;
        node->right->left->right = node->right;
        node = node->left->right;
        node->left->right = temp_l;
        node->right->left = temp_r;

        node->parent = node->right->parent;
        node->left->parent = node;
        node->right->parent = node;
        if (node->left->right) {
            node->left->right->parent = node->left;
        }
        if (node->right->left) {
            node->right->left->parent = node->right;
        }

        node->left->height = get_height(node->left);
        node->right->height = get_height(node->right);
        node->height = std::max(node->left->height, node->right->height);
    }

    Node* find_min(Node* node) {
        return node->left ? find_min(node->left) : node;
    }
    Node* remove_min(Node* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = remove_min(node->left);
        node->node_count--;
        return balance(node);
    }


    size_t get_height(const Node* node) const {
        return node ? node->height : 0;
    }
    size_t get_node_count(const Node* node) const {
        return node ? node->node_count : 0;
    }
    void fix_height(Node* node) {
        size_t l_h = get_height(node->left);
        size_t r_h = get_height(node->right);
        node->height = (l_h > r_h ? l_h : r_h) + 1;
    }
    void fix_node_count(Node* node) {
        if (!node) {
            return;
        }

        node->node_count = get_node_count(node->left) + get_node_count(node->right) + 1;
    }
    long balance_factor(Node* node) {
        return get_height(node->right) - get_height(node->left);
    }
};

int main() {
    AVLTree<int> tree;
    int data;
    size_t num;
    size_t size;

    std::cin >> size;

    for (size_t i = 0; i < size; i++) {
        std::cin >> data >> num;
        if (data > 0) {
            tree.add(data);
        } else {
            tree.remove(-data);
        }
        std::cout << tree.get_ord_statistic(num) << std::endl;
    }

    return 0;
}