/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                     "chain" data structure.                     ////
////                                                                 ////
////                           - by Zik Saleeba zik@zikzak.net       ////
////                                       2016-08-23                ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////

//
// Licensed under the "unlicense".
// See LICENSE file.
//

#include <memory>
#include <vector>


//
// A generic node with reference counting and sub-item counting.
//

template <class T>
class ChainNode
{
protected:
    unsigned refCount_;
    size_t   itemCount_;

public:
    ChainNode() : refCount_(0), itemCount_(0) {}

    void addRef();
    static void unRef(ChainNode<T> *node);
};


//
// A payload node that contains a vector of items.
//

template <class T>
class ChainNodeVector : public ChainNode<T>
{
    std::vector<T> vec_;

public:
    ChainNodeVector() {}
};


//
// An intermediate node which says to use a sub-segment of the
// items beneath it. This is used when we want to use only part
// of a vector via a slice() operation for instance.
//

template <class T>
class ChainNodeSubset : public ChainNode<T>
{
    off_t  start_;
    size_t len_;

public:
    ChainNodeSubset() {}
};


//
// A tree node. This is used when inserting or deleting to
// make a self-balacing tree of edits attached to a part of the
// chain.
//

template <class T>
class ChainNodeTree : public ChainNode<T>
{
    ChainNode<T> *left_;
    ChainNode<T> *right_;

public:
    ChainNodeTree() : left_(nullptr), right_(nullptr) {}
    ~ChainNodeTree();
};


//
// The user-accessible top level part of a chain.
//

template <class T>
class Chain
{
    ChainNode<T> *root;

public:
    Chain();
    Chain(const T *data, size_t len);
    ~Chain();
};
