//-----------------------------------------------------------------------------
// Dictionary.cpp
// Implementation file for the Dictionary ADT
// Bradley Haire
// bhaire
// pa8
//-----------------------------------------------------------------------------
#include "Dictionary.h"
using std::endl;

#define RED -10
#define BLACK -100

Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}

Dictionary::Dictionary() {
    nil = new Node("", -1);
    root = this->nil;
    current = this->nil;
    num_pairs = 0;
    nil->color = BLACK;
}

Dictionary::Dictionary(const Dictionary& D) {
    this->nil = new Node("", -1);
    this->num_pairs = 0;
    this->root = this->nil;
    this->nil->color = BLACK;
    this->preOrderCopy(D.root, D.nil);
    this->current = this->nil;
    this->nil->color = BLACK;
}

Dictionary::~Dictionary() {
    this->clear();
    delete this->nil;
}

int Dictionary::size() const {
    return this->num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return (this->search(this->root, k) != this->nil);
}

valType& Dictionary::getValue(keyType k) const {
    return (this->search(this->root, k))->val;
}

bool Dictionary::hasCurrent() const {
    return (this->current != this->nil);
}

keyType Dictionary::currentKey() const {
    if (this->current == this->nil) {
        throw std::logic_error("Dictionary: currentKey(): current value undefined");
    }
    return this->current->key;
}

valType& Dictionary::currentVal() const {
    if (this->current == this->nil) {
        throw std::logic_error("Dictionary: currentVal(): current value undefined");
    }
    return this->current->val;
}

void Dictionary::clear() {
    this->postOrderDelete(this->root);
    this->root = this->nil;
    this->current = this->nil;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* x = this->root;
    Node* y = this->nil;
    while (x != this->nil) {
        y = x;
        if (k == x->key) {
            x->val = v;
            return;
        } else if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    Node* node = new Node(k, v);
    node->left = this->nil;
    node->right = this->nil;
    node->color = RED;
    node->parent = y;
    this->num_pairs += 1;
    if (y == this->nil) {
        this->root = node;
    } else if (node->key < y->key) {
        y->left = node;
    } else {
        y->right = node;
    }
    this->RB_InsertFixUp(node);
}

void Dictionary::LeftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == this->nil) {
        this->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Dictionary::RightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == this->nil) {
        this->root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* z) {
    Node* y;
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    this->LeftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                this->RightRotate(z->parent->parent);
            }
        }
        else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    this->RightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                this->LeftRotate(z->parent->parent);
            }
        }
    }
    this->root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* one, Node* two) {
    if (one->parent == this->nil) {
        this->root = two;
    }
    else if (one == one->parent->left) {
        one->parent->left = two;
    }
    else {
        one->parent->right = two;
    }
    two->parent = one->parent;
}

void Dictionary::RB_DeleteFixUp(Node* x) {
    while (x != this->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                this->LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    this->RightRotate(x->parent);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                this->LeftRotate(x->parent);
                x = this->root;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                this->RightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    this->LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                this->RightRotate(x->parent);
                x = this->root;
            }
        }
    }
    x->color = BLACK;
}

void Dictionary::RB_Delete(Node* z) {
    Node* x;
    Node* y = z;
    int y_color = y->color;
    if (z->left == this->nil) {
        x = z->right;
        this->RB_Transplant(z, z->right);
    }
    else if (z->right == this->nil) {
        x = z->left;
        this->RB_Transplant(z, z->left);
    }
    else {
        y = this->findMin(z->right);
        y_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            this->RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        this->RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_color == BLACK) {
        this->RB_DeleteFixUp(x);
    }
}

void Dictionary::remove(keyType k) {
    Node* node = this->search(this->root, k);
    if (node == this->nil) {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    if (node == this->current) {
        this->current = this->nil;
    }
    this->RB_Delete(node);
    this->num_pairs -= 1;
    delete node;
}

void Dictionary::begin() {
    if (this->num_pairs) {
        this->current = this->findMin(this->root);
    }
}

void Dictionary::end() {
    if (this->num_pairs) {
        this->current = this->findMax(this->root);
    }
}

void Dictionary::next() {
    if (this->current == this->nil) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    if (this->current->right != this->nil) {
        this->current = this->findMin(this->current->right);
    }
    else {
        Node * y = this->current->parent;
        while (y != this->nil && this->current == y->right) {
            this->current = y;
            y = y->parent;
        }
        this->current = y;
    }
}

void Dictionary::prev() {
    if (this->current == this->nil) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    if (this->current->left != this->nil) {
        this->current = this->findMax(this->current->left);
        return;
    }
    else {
        Node * y = this->current->parent;
        while (y != this->nil && this->current == y->left) {
            this->current = y;
            y = y->parent;
        }
        this->current = y;
    }
}

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if (R != this->nil) {
        if (R->left == nullptr || R->right == nullptr) {
            return;
        }
        this->inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += '\n';
        this->inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if (R != this->nil) {
        s += R->key;
        s += '\n';
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != this->nil && R != N) {
        this->setValue(R->key, R->val);
        this->preOrderCopy(R->left, N);
        this->preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != this->nil) {
        this->postOrderDelete(R->left);
        this->postOrderDelete(R->right);
        delete R;
        this->num_pairs -= 1;
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == this->nil){
        return this->nil;
    }
    if (R->key == k) {
        return R;
    }
    else {
        if (R->key < k) {
            return this->search(R->right, k);
        }
        else {
            return this->search(R->left, k);
        }
    }
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == this->nil) {
        return this->nil;
    }
    else {
        Node * cur = R;
        while(cur->left != this->nil) {
            cur = cur->left;
        }
        return cur;
    }
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R == this->nil) {
        return this->nil;
    }
    else {
        Node * cur = R;
        while(cur->right != this->nil) {
            cur = cur->right;
        }
        return cur;
    }
    
}

std::string Dictionary::to_string() const { // in order notation
    std::string s = "";
    this->inOrderString(s, this->root);
    return s;
}

std::string Dictionary::pre_string() const { // pre order
    std::string s = "";
    this->preOrderString(s, this->root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    return (this->to_string() == D.to_string());
}

std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    stream << D.to_string();
    return stream;
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if (this != &D) {
        Dictionary tmp = D;
        std::swap(this->num_pairs, tmp.num_pairs);
        std::swap(this->current, tmp.current);
        std::swap(this->root, tmp.root);
        std::swap(this->nil, tmp.nil);
        this->current = this->nil;
    }
    return *this;
}
