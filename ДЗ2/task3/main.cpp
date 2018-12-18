#include <iostream>
#include <vector>
#include <queue>

template <class T>
class BinaryTree {
public:
    BinaryTree() = default;
    ~BinaryTree() {
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

    void add(const T& data) {
        auto* curr_node = &root;

        while (*curr_node != nullptr) {
            curr_node = data < (*curr_node)->data ? &((*curr_node)->left) : &((*curr_node)->right);
        }

        *curr_node = new Node(data);
    }
    bool remove(const T& data) {
        auto* curr_node = &root;

        while (*curr_node != nullptr) {
            curr_node = data < (*curr_node)->data ? &((*curr_node)->left) : &((*curr_node)->right);
        }

        if (*curr_node) {
            if ((*curr_node)->right && (*curr_node)->left) {
                Node** min = &(*curr_node)->right;
                while ((*min)->left) {
                    min = &(*min)->left;
                }

                Node* new_node = *min;
                *min = (*min)->right;
                new_node->right = (*curr_node)->right;
                new_node->left = (*curr_node)->left;
                delete *curr_node;
                *curr_node = new_node;
            } else {
                auto new_node = (*curr_node)->left ? (*curr_node)->left : (*curr_node)->right;
                delete *curr_node;
                *curr_node = new_node;
            }

            return true;
        } else {
            return false;
        }
    }
    bool has(const T& data) {
        auto curr_node = root;
        while (curr_node != nullptr && curr_node->data != data) {
            curr_node = data < curr_node->data ? curr_node->left : curr_node->right;
        }

        return curr_node;
    }

    size_t get_widest_layer_count() {
        using Layer_pair = std::pair<Node*, size_t>;

        size_t max_layer_num = 0;
        size_t max_layer_count = 1;

        size_t not_max_layer_num = 0;
        size_t not_max_layer_count = 0;

        std::queue<Layer_pair> node_queue;

        if (root != nullptr) {
            node_queue.push(std::make_pair(root, 0));
        } else {
            return 0;
        }

        while (!node_queue.empty()) {
            const auto temp_pair = node_queue.front();
            node_queue.pop();

            if (temp_pair.second != not_max_layer_num) {
                if (not_max_layer_count > max_layer_count) {
                    max_layer_num = not_max_layer_num;
                    max_layer_count = not_max_layer_count;
                }

                not_max_layer_num = temp_pair.second;
                not_max_layer_count = 1;
            } else {
                not_max_layer_count++;
            }

            if (temp_pair.first->left != nullptr) {
                node_queue.push(std::make_pair(temp_pair.first->left, temp_pair.second + 1));
            }
            if (temp_pair.first->right != nullptr) {
                node_queue.push(std::make_pair(temp_pair.first->right, temp_pair.second + 1));
            }
        }

        return max_layer_count > not_max_layer_count ? max_layer_count : not_max_layer_count;
    }

private:
    struct Node {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;

        explicit Node(const T& _data) :
            data(_data) {
        }
    };

    Node* root = nullptr;
};

template <class T>
class DecartTree {
  public:
    DecartTree() = default;
    ~DecartTree() {
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

    void add(const T& data, size_t priority) {
        auto* curr_node = &root;

        while (*curr_node != nullptr && (*curr_node)->priority >= priority) {
            curr_node = data < (*curr_node)->data ? &((*curr_node)->left) : &((*curr_node)->right);
        }

        if (*curr_node == nullptr) {
            *curr_node = new Node(data, priority);
            return;
        } else {
            Node* left_subtree = nullptr;
            Node* right_subtree = nullptr;
            auto* new_node = new Node(data, priority);

            split(*curr_node, data, left_subtree, right_subtree);
            new_node->left = left_subtree;
            new_node->right = right_subtree;

            *curr_node = new_node;
        }
    }

    bool remove(const T& data) {
        auto curr_node = &root;
        while (*curr_node != nullptr && (*curr_node)->data != data) {
            curr_node = data < (*curr_node)->data ? &(*curr_node)->left : &(*curr_node)->right;
        }

        if (!*curr_node) {
            return false;
        }

        auto new_node = merge((*curr_node)->left, (*curr_node)->right);
        delete *curr_node;
        *curr_node = new_node;
    }
    bool has(const T& data) {
        auto curr_node = root;
        while (curr_node != nullptr && curr_node->data != data) {
            curr_node = data < curr_node->data ? curr_node->left : curr_node->right;
        }

        return curr_node;
    }

    size_t get_widest_layer_count() {
        using Layer_pair = std::pair<Node*, size_t>;

        size_t max_layer_num = 0;
        size_t max_layer_count = 1;

        size_t not_max_layer_num = 0;
        size_t not_max_layer_count = 0;

        std::queue<Layer_pair> node_queue;

        if (root != nullptr) {
            node_queue.push(std::make_pair(root, 0));
        } else {
            return 0;
        }

        while (!node_queue.empty()) {
            const auto temp_pair = node_queue.front();
            node_queue.pop();

            if (temp_pair.second != not_max_layer_num) {
                if (not_max_layer_count > max_layer_count) {
                    max_layer_num = not_max_layer_num;
                    max_layer_count = not_max_layer_count;
                }

                not_max_layer_num = temp_pair.second;
                not_max_layer_count = 1;
            } else {
                not_max_layer_count++;
            }

            if (temp_pair.first->left != nullptr) {
                node_queue.push(std::make_pair(temp_pair.first->left, temp_pair.second + 1));
            }
            if (temp_pair.first->right != nullptr) {
                node_queue.push(std::make_pair(temp_pair.first->right, temp_pair.second + 1));
            }
        }

        return max_layer_count > not_max_layer_count ? max_layer_count : not_max_layer_count;
    }

  private:
    struct Node {
        T data;
        size_t priority;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(const T& _data, size_t _priority) :
            data(_data), priority(_priority) {
        }
    };

    Node* root = nullptr;

    void split(Node* current, size_t key, Node*& left_subtree, Node*& right_subtree) {
        if (current == nullptr) {
            left_subtree = nullptr;
            right_subtree = nullptr;
        } else if (current->data <= key) {
            split(current->right, key, current->right, right_subtree);
            left_subtree = current;
        } else {
            split(current->left, key, left_subtree, current->left);
            right_subtree = current;
        }
    }
    Node* merge(Node* left_subtree, Node* right_subtree) {
        if (left_subtree == nullptr || right_subtree == nullptr) {
            return left_subtree == nullptr ? right_subtree : left_subtree;
        }
        if(left_subtree->priority > right_subtree->priority) {
            left_subtree->right = merge(left_subtree->right, right_subtree);
            return left_subtree;
        } else {
            right_subtree->left = merge(left_subtree, right_subtree->left);
            return right_subtree;
        }
    }
};

int main() {
    BinaryTree<int> tree;
    DecartTree<int> d_tree;
    int data;
    size_t priority;
    size_t size;

    std::cin >> size;

    for (size_t i = 0; i < size; i++) {
        std::cin >> data >> priority;
        tree.add(data);
        d_tree.add(data, priority);
    }

    std::cout << int(d_tree.get_widest_layer_count()) - int(tree.get_widest_layer_count()) << std::endl;

    return 0;
}