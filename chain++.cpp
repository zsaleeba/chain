/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                     "chain" data structure.                     ////
////                                                                 ////
////                           - by Zik Saleeba zik@zikzak.net       ////
////                                       2016-08-23                ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////

//
// Licensed under the "New BSD License".
// See LICENSE file.
//

#include "chain++.h"


ChainNode::addRef()
{
    refCount_++;
}


ChainNode::unRef(ChainNode<T> *node)
{
    node->refCount--;
    if (node->refCount_ == 0)
        delete node;
}


ChainNodeTree::~ChainNodeTree()
{
    if (left_ != nullptr)
    {
        unRef(left_);
    }

    if (right_ != nullptr)
    {
        unRef(right_);
    }
}
