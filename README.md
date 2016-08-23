# Chain

A chain data structure is similar to a vector but allows fast insertion, 
deletion, catenation and slicing.

It's inspired in part by [Rope](https://en.wikipedia.org/wiki/Rope_(data_structure)),
the [Model T Enfilade](https://en.wikipedia.org/wiki/Enfilade_(Xanadu)) 
and the [Judy Array](https://en.wikipedia.org/wiki/Judy_array).

## Attributes

Chains are an adaptive data structure which has the benefits of a vector 
when used like a vector, and those of a balanced binary tree when used 
like a tree. It's designed for fast indexed access like a
vector but also provides efficient insertion, deletion, catenation and
slicing operations.

When used as a vector chains are approximately as fast as vectors, having O(1) 
indexed access characteristics. Insertion, deletion, catenation and slicing
take worst case O(log n) time with subsequent indexed accesses taking 
amortised O(1) and worst case O(log n). 

## Description

Chain treat a vector as a series of values plus a series of "edits" such
as insertions, deletions and catenations. Conceptually the vector is 
treated as a chain of values where it's possible to unlink the chain
at any point and add or remove another chain.

Chains are an adaptive data structure. When used mostly for indexed access 
they transform into a vector and when used for insertion, deletion and 
catenation they become a tree. They adapt progressively between the two 
types of representation, keeping usage statistics to drive the
transformations and keep access as efficient as possible.

The chain data structure is fundamentally a tree of vectors. Initially 
the tree has only a single node which represents the entire chain as a 
single vector. This vector is accessed with O(1) speed. 

When insertion, deletion or catenation operations occur the new data is
added to a new nodes in the tree. The tree is a balanced binary tree, with
the balancing based on the "weight" of each branch of the tree. The 
weight is defined as the number of items in the subtree. In this way the
larger, more frequently accessed vectors remain near the top of the tree
for faster access and the smaller, less popular vectors tend to gravitate
towards the bottom of the tree.

Chains can share sub-slices with other chains. For instance slices are 
chains with a set of nodes which refer to the exact same underlying 
storage as the original chain. This leads to a fast and memory 
efficient implementation of slicing. If it's preferred not to share 
data then the slice can be copied and flattened but this will have O(n) 
cost.

Sharing of sliced data between chains may share some tree nodes with the 
original chain. Because of this the tree nodes don't store the absolute
indices of their data members. Instead nodes store the sum of the number 
of items in their two subtrees. This allows nodes to be used in multiple
chains at the same time.   

## Adaptation

When accesses are made to the chain checks are done to see if data which
is found lower in the tree can be moved up the tree for quicker access.
For instance if a chain with a small number of end-edits is accessed 
sequentially and if sufficient space is found in the top node then it's 
possible that the chain may be flattened by a single sequential access. 

Statistics are kept in each tree node indicating how many 
times it has been accessed. If the number of accesses to a node exceeds 
the cost of coalescing it with its parent node then a resize and
coalesce to the parent node is performed. The count of the number of
accesses is reset after any coalesce, insertion or deletion. In this way
parts of the tree with frequent edits will tend to be kept in tree form
while parts of the tree which are accessed by index will be gradually
flattened for faster access. If the pattern of access moves from editing
to reading then the chain will eventually be entirely flattened.

## Memory management

The data in chains are fundamentally stored in vectors which are associated
with tree nodes. This one to one association may break down however when
edits are made to the chain. Deleting a section from the middle of a chain
will leave a gap, however it's not possible to separate the two used 
sections of data at the ends from the unused section in the middle without
incurring an O(n) cost. For this reason the tree nodes are stored separately
from the underlying vector data and reference counting is used to track 
when a vector becomes completely unused and may be freed.

Nodes can also be shared between trees after slice operations. Reference 
counts are also used in the nodes to determine when they can be freed.  

## Operations

### Index

Last node is cached for quicker access.

### Insert

### Delete

### Catenation

### Slicing

### Flattening
