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
        auto curr_node = &root;

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

    std::vector<T> level_order() const{
        std::vector<T> data_vec;
        std::queue<Node*> node_queue;

        if (root != nullptr) {
            node_queue.push(root);
        }

        while (!node_queue.empty()) {
            const Node* temp_node = node_queue.front();
            node_queue.pop();
            data_vec.push_back(temp_node->data);

            if (temp_node->left != nullptr) {
                node_queue.push(temp_node->left);
            }
            if (temp_node->right != nullptr) {
                node_queue.push(temp_node->right);
            }
        }

        return data_vec;
    }

  private:
    struct Node {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;

        explicit Node(const T& _data) : data(_data) {
        }
    };

    Node* root = nullptr;
};

int main() {
    BinaryTree<int> tree;
    int temp;
    size_t size;

    std::cin >> size;

    for (size_t i = 0; i < size; i++) {
        std::cin >> temp;
        tree.add(temp);
    }

    auto vec = tree.level_order();

    for (const auto &item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}