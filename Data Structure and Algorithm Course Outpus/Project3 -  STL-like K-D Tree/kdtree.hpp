#include <tuple>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdexcept>

/**
 * An abstract template base of the KDTree class
 */
template<typename...>
class KDTree;

/**
 * A partial template specialization of the KDTree class
 * The time complexity of functions are based on n and k
 * n is the size of the KDTree
 * k is the number of dimensions
 * @typedef Key         key type
 * @typedef Value       value type
 * @typedef Data        key-value pair
 * @static  KeySize     k (number of dimensions)
 */
template<typename ValueType, typename... KeyTypes>
class KDTree<std::tuple<KeyTypes...>, ValueType> {
public:
    typedef std::tuple<KeyTypes...> Key;
    typedef ValueType Value;
    typedef std::pair<const Key, Value> Data;
    static inline constexpr size_t KeySize = std::tuple_size<Key>::value;
    static_assert(KeySize > 0, "Can not construct KDTree with zero dimension");
protected:
    struct Node {
        Data data;
        Node *parent;
        Node *left = nullptr;
        Node *right = nullptr;

        Node(const Key &key, const Value &value, Node *parent) : data(key, value), parent(parent) {}

        const Key &key() { return data.first; }

        Value &value() { return data.second; }
    };

    template<size_t DIM>
    static bool Compare(const std::pair<Key,Value> &a, const std::pair<Key,Value> &b) {
        return compareKey<DIM,std::less<>>(a.first,b.first);
    }

    Node*  copy_helper(Node * node, Node * that){
        if (that== nullptr) {
            return nullptr;
        }
        Node* current_root = new Node(that->key(), that->value(), node);
        current_root->left = copy_helper(current_root,that->left);
        current_root->right = copy_helper(current_root,that->right);
        return current_root;
    }

    void delete_helper(Node * node){
        if (node==nullptr) {
            return;
        }
        if (node->left) {
            delete_helper(node->left);
        }
        if (node->right) {
            delete_helper(node->right);
        }
        delete node;
    }

    template<size_t DIM>
    Node * copy_from_vector_helper(std::vector<std::pair<Key, Value>> & data, Node * par){
        constexpr size_t DIM_NEXT = (DIM+1)%KeySize;
        if (data.empty()) {
            return nullptr;
        }
        typename std::vector<std::pair<Key, Value>>::iterator middle_iterator = data.begin() + (data.size() - 1) /2;
        typename std::vector<std::pair<Key, Value>>::iterator begin = data.begin();
        typename std::vector<std::pair<Key, Value>>::iterator end = data.end();
        std::nth_element(begin,middle_iterator,end,Compare<DIM>);
        std::vector<std::pair<Key, Value>> left;
        std::vector<std::pair<Key, Value>> right;
        left.assign(begin,middle_iterator);
        right.assign(middle_iterator+1,end);
        Node* current_node = new Node(middle_iterator->first,middle_iterator->second,par);
        current_node->left = copy_from_vector_helper<DIM_NEXT>(left,current_node);
        current_node->right = copy_from_vector_helper<DIM_NEXT>(right,current_node);
        return current_node;
    }

    template<size_t DIM_CMP>
    Node* smaller_node(Node * node1, Node * node2){
        return compareNode<DIM_CMP,std::less<>>(node1, node2);
    }

    template<size_t DIM_CMP>
    Node* bigger_node(Node * node1, Node * node2){
        return compareNode<DIM_CMP,std::greater<>>(node1, node2);
    }

    static bool key_equal(const Key & a, const Key & b){
        bool less=compareKey<(size_t)0,std::less<>>(a,b);
        bool greater=compareKey<(size_t)0,std::greater<>>(a,b);
        return (!less && !greater);
    }

    template <size_t DIM>
    static bool key_less(const Key & a, const Key & b){
        return (std::get<DIM>(a) < std::get<DIM>(b));
    }

    static bool pair_key_equal(const std::pair<Key, Value> & a, const std::pair<Key, Value> & b){
        return key_equal(a.first,b.first);
    }

public:
    /**
     * A bi-directional iterator for the KDTree
     * ! ONLY NEED TO MODIFY increment and decrement !
     */
    class Iterator {
    private:
        KDTree *tree;
        Node *node;

        Iterator(KDTree *tree, Node *node) : tree(tree), node(node) {}
        void goto_rightest() {
            while (node->right){
                node=node->right;
            }
        }
        void goto_leftest() {
            while (node->left) {
                node=node->left;
            }
        }
        /**
         * Increment the iterator
         * Time complexity: O(log n)
         */
        void increment() {
            // TODO: implement this function
            if (node->right == nullptr) { // if the current node has a right subtree
                Node* previous_node;
                previous_node = node;
                node = node->parent;
                while (node!=nullptr && node->left!=previous_node){ // the parent of the root node is nullptr
                    previous_node = node;
                    node = node->parent;
                }
            }
            else {
                node = node->right;
                goto_leftest();
            }
        }

        /**
         * Decrement the iterator
         * Time complexity: O(log n)
         */
        void decrement() {
            // TODO: implement this function
            if (node != nullptr){
                if (node->left!= nullptr){
                    goto_rightest();
                }
                else {
                    Node * previous_node;
                    previous_node = node;
                    node = node->parent;
                    while (node!= nullptr && node->right!=previous_node){
                        previous_node = node;
                        node = node->parent;
                    }
                }
            }
            else {
                node = tree->root;
                goto_rightest();
            }
        }

            public:
            friend class KDTree;

            Iterator() = delete;

            Iterator(const Iterator &) = default;

            Iterator &operator=(const Iterator &) = default;

            Iterator &operator++() {
                increment();
                return *this;
            }

            Iterator operator++(int) {
                Iterator temp = *this;
                increment();
                return temp;
            }

            Iterator &operator--() {
                decrement();
                return *this;
            }

            Iterator operator--(int) {
                Iterator temp = *this;
                decrement();
                return temp;
            }

            bool operator==(const Iterator &that) const {
                return node == that.node;
            }

            bool operator!=(const Iterator &that) const {
                return node != that.node;
            }

            Data *operator->() {
                return &(node->data);
            }

            Data &operator*() {
                return node->data;
            }
        };

    protected:                      // DO NOT USE private HERE!
        Node *root = nullptr;       // root of the tree
        size_t treeSize = 0;        // size of the tree

        /**
         * Find the node with key
         * Time Complexity: O(k log n)
         * @tparam DIM current dimension of node
         * @param key
         * @param node
         * @return the node with key, or nullptr if not found
         */
        template<size_t DIM>
        Node *find(const Key &key, Node *node) {
            constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
            // TODO: implement this function
            if (key_equal(key,node->key())) {
                return node;
            }
            else if (key_less<DIM>(key,node->key())) {
                if(node->left!= nullptr){
                    return find<DIM_NEXT>(key,node->left);
                }
                else{
                    return nullptr;
                }
            }
            else  {
                if(node->right!= nullptr){
                    return find<DIM_NEXT>(key,node->right);
                }
                else{
                    return nullptr;
                }
            }
            return node;
        }

        /**
         * Insert the key-value pair, if the key already exists, replace the value only
         * Time Complexity: O(k log n)
         * @tparam DIM current dimension of node
         * @param key
         * @param value
         * @param node
         * @param parent
         * @return whether insertion took place (return false if the key already exists)
         */
        template<size_t DIM>
        bool insert(const Key &key, const Value &value, Node *&node, Node *parent) {
            constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
            // TODO: implement this function
            if (node!= nullptr){
                if (key_equal(key,node->key())){   //if the key already exists, replace the value only
                    node->data.second = value;
                    return false;
                }
                else if (key_less<DIM>(key,node->key())){
                    return insert<DIM_NEXT>(key,value,node->left,node);
                }
                else {
                    return insert<DIM_NEXT>(key,value,node->right,node);
                }
            }
            else{
                this->treeSize = this->treeSize + 1;
                node = new Node(key,value,parent);
                return true;
            }
            return false;
        }

        /**
         * Compare two keys on a dimension
         * Time Complexity: O(1)
         * @tparam DIM comparison dimension
         * @tparam Compare
         * @param a
         * @param b
         * @param compare
         * @return relationship of two keys on a dimension with the compare function
         */
        template<size_t DIM, typename Compare>
        static bool compareKey(const Key &a, const Key &b, Compare compare = Compare()) {
            if (std::get<DIM>(a) != std::get<DIM>(b)){
                return compare(std::get<DIM>(a), std::get<DIM>(b));
            }
            return compare(a, b);
        }

        /**
         * Compare two nodes on a dimension
         * Time Complexity: O(1)
         * @tparam DIM comparison dimension
         * @tparam Compare
         * @param a
         * @param b
         * @param compare
         * @return the minimum / maximum of two nodes
         */
        template<size_t DIM, typename Compare>
        static Node *compareNode(Node *a, Node *b, Compare compare = Compare()) {
            if (!a) return b;
            if (!b) return a;
            return compareKey<DIM, Compare>(a->key(), b->key(), compare) ? a : b;
        }

        /**
         * Find the minimum node on a dimension
         * Time Complexity: ?
         * @tparam DIM_CMP comparison dimension
         * @tparam DIM current dimension of node
         * @param node
         * @return the minimum node on a dimension
         */
        template<size_t DIM_CMP, size_t DIM>
        Node *findMin(Node *node) {
            constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
            // TODO: implement this function
            if (node== nullptr) {
                return nullptr;
            }
            Node * min = findMin<DIM_CMP,DIM_NEXT>(node->left);
            if (DIM_CMP != DIM) {
                Node * rightMin = findMin<DIM_CMP,DIM_NEXT>(node->right);
                min = smaller_node<DIM_CMP>(min, rightMin);
            }
            return smaller_node<DIM_CMP>(min,node);
        }


        /**
         * Find the maximum node on a dimension
         * Time Complexity: ?
         * @tparam DIM_CMP comparison dimension
         * @tparam DIM current dimension of node
         * @param node
         * @return the maximum node on a dimension
         */
        template<size_t DIM_CMP, size_t DIM>
        Node *findMax(Node *node) {
            constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
            // TODO: implement this function
            if (node== nullptr) {
                return nullptr;
            }
            Node * max = findMax<DIM_CMP,DIM_NEXT>(node->right);
            if (DIM_CMP != DIM) {
                Node * leftMax = findMax<DIM_CMP,DIM_NEXT>(node->left);
                max = bigger_node<DIM_CMP>(max, leftMax);
            }
            return bigger_node<DIM_CMP>(max,node);
        }

        template<size_t DIM>
        Node *findMinDynamic(size_t dim) {
            constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
            if (dim >= KeySize) {
                dim %= KeySize;
            }
            if (dim == DIM) return findMin<DIM, 0>(root);
            return findMinDynamic<DIM_NEXT>(dim);
        }

        template<size_t DIM>
        Node *findMaxDynamic(size_t dim) {
            constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
            if (dim >= KeySize) {
                dim %= KeySize;
            }
            if (dim == DIM) return findMax<DIM, 0>(root);
            return findMaxDynamic<DIM_NEXT>(dim);
        }

        /**
         * Erase a node with key (check the pseudocode in project description)
         * Time Complexity: max{O(k log n), O(findMin)}
         * @tparam DIM current dimension of node
         * @param node
         * @param key
         * @return nullptr if node is erased, else the (probably) replaced node
         */
        template<size_t DIM>
        Node *erase(Node *node, const Key &key) {
            constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
            // TODO: implement this function
            if (node== nullptr) {
                return nullptr;
            }
            if (key_equal(key,node->key())) { // equal
                if (node->right == nullptr && node->left == nullptr){ // node is a leaf
                    delete node;
                    this->treeSize = this->treeSize -1;
                    if (this->treeSize == 0) this->root = nullptr;
                    return nullptr;
                }
                else if (node->right){ // node has right subtree
                    Node * min = findMin<DIM,DIM_NEXT>(node->right);
                    Key & node_key = const_cast<Key&>(node->data.first);
                    node_key = min->key();
                    node->data.second = min->value();
                    node->right = erase<DIM_NEXT>(node->right,min->key());
                }
                else { // node has left subtree
                    Node * max = findMax<DIM,DIM_NEXT>(node->left);
                    Key & node_key = const_cast<Key&>(node->data.first);
                    node_key = max->key();
                    node->data.second = max->value();
                    node->left = erase<DIM_NEXT>(node->left,max->key());
                }
            }
            else if (key_less<DIM>(key,node->key())){
                node->left = erase<DIM_NEXT>(node->left,key);
            }
            else {
                node->right = erase<DIM_NEXT>(node->right,key);
            }
            return node;
        }

        template<size_t DIM>
        Node *eraseDynamic(Node *node, size_t dim) {
            constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
            if (dim >= KeySize) {
                dim %= KeySize;
            }
            if (dim == DIM) return erase<DIM>(node, node->key());
            return eraseDynamic<DIM_NEXT>(node, dim);
        }

        // TODO: define your helper functions here if necessary

    public:
        KDTree() = default;

        /**
         * Time complexity: O(kn log n)
         * @param v we pass by value here because v need to be modified
         */
        explicit KDTree(std::vector<std::pair<Key, Value>> v) {
            // TODO: implement this function
            delete_helper(this->root);
            std::stable_sort(v.begin(), v.end(),Compare<(size_t)0>);
            auto last = std::unique(v.rbegin(), v.rend(), pair_key_equal);
            v.assign(last.base(),v.end());
            this->treeSize = v.size();
            this->root = copy_from_vector_helper<0>(v, nullptr);
        }

        /**
         * Time complexity: O(n)
         */
        KDTree(const KDTree &that) {
            *this = that;
        }

        /**
         * Time complexity: O(n)
         */
        KDTree &operator=(const KDTree &that) {
            // TODO: implement this function
            if (this==&that){
                return *this;
            }
            else{
                delete_helper(this->root);
                this->root = copy_helper(nullptr, that.root);
                this->treeSize = that.treeSize;
                return *this;
            }
        }

        /**
         * Time complexity: O(n)
         */
        ~KDTree() {
            // TODO: implement this function
            delete_helper(this->root);
        }

        Iterator begin() {
            if (!root) return end();
            auto node = root;
            while (node->left) node = node->left;
            return Iterator(this, node);
        }

        Iterator end() {
            return Iterator(this, nullptr);
        }

        Iterator find(const Key &key) {
            return Iterator(this, find<0>(key, root));
        }

        void insert(const Key &key, const Value &value) {
            insert<0>(key, value, root, nullptr);
        }

        template<size_t DIM>
        Iterator findMin() {
            return Iterator(this, findMin<DIM, 0>(root));
        }

        Iterator findMin(size_t dim) {
            return Iterator(this, findMinDynamic<0>(dim));
        }

        template<size_t DIM>
        Iterator findMax() {
            return Iterator(this, findMax<DIM, 0>(root));
        }

        Iterator findMax(size_t dim) {
            return Iterator(this, findMaxDynamic<0>(dim));
        }

        bool erase(const Key &key) {
            auto prevSize = treeSize;
            erase<0>(root, key);
            return prevSize > treeSize;
        }

        Iterator erase(Iterator it) {
            if (it == end()) return it;
            auto node = it.node;
            if (!it.node->left && !it.node->right) {
                it.node = it.node->parent;
            }
            size_t depth = 0;
            auto temp = node->parent;
            while (temp) {
                temp = temp->parent;
                ++depth;
            }
            eraseDynamic<0>(node, depth % KeySize);
            return it;
        }

        size_t size() const { return treeSize; }
    };