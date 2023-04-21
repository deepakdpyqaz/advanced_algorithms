#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data, degree;
    Node *child, *sibling, *parent;
};

Node *newNode(int key)
{
    Node *temp = new Node;
    temp->data = key;
    temp->degree = 0;
    temp->child = temp->parent = temp->sibling = NULL;
    return temp;
}

Node *mergeBinomialTrees(Node *b1, Node *b2)
{

    if (b1->data > b2->data)
        swap(b1, b2);

    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;

    return b1;
}

list<Node *> unionBionomialHeap(list<Node *> l1,
                                list<Node *> l2)
{
    list<Node *> _new;
    list<Node *>::iterator it = l1.begin();
    list<Node *>::iterator ot = l2.begin();
    while (it != l1.end() && ot != l2.end())
    {

        if ((*it)->degree <= (*ot)->degree)
        {
            _new.push_back(*it);
            it++;
        }

        else
        {
            _new.push_back(*ot);
            ot++;
        }
    }

    while (it != l1.end())
    {
        _new.push_back(*it);
        it++;
    }

    while (ot != l2.end())
    {
        _new.push_back(*ot);
        ot++;
    }
    return _new;
}

list<Node *> adjust(list<Node *> bin_heap)
{
    if (bin_heap.size() <= 1)
        return bin_heap;
    list<Node *> newbin_heap;
    list<Node *>::iterator it1, it2, it3;
    it1 = it2 = it3 = bin_heap.begin();

    if (bin_heap.size() == 2)
    {
        it2 = it1;
        it2++;
        it3 = bin_heap.end();
    }
    else
    {
        it2++;
        it3 = it2;
        it3++;
    }
    while (it1 != bin_heap.end())
    {

        if (it2 == bin_heap.end())
            it1++;

        else if ((*it1)->degree < (*it2)->degree)
        {
            it1++;
            it2++;
            if (it3 != bin_heap.end())
                it3++;
        }

        else if (it3 != bin_heap.end() &&
                (*it1)->degree == (*it2)->degree &&
                (*it1)->degree == (*it3)->degree)
        {
            it1++;
            it2++;
            it3++;
        }

        else if ((*it1)->degree == (*it2)->degree)
        {
            Node *temp;
            *it1 = mergeBinomialTrees(*it1, *it2);
            it2 = bin_heap.erase(it2);
            if (it3 != bin_heap.end())
                it3++;
        }
    }
    return bin_heap;
}

list<Node *> insertATreeInHeap(list<Node *> bin_heap,
                               Node *tree)
{

    list<Node *> temp;

    temp.push_back(tree);

    temp = unionBionomialHeap(bin_heap, temp);

    return adjust(temp);
}

list<Node *> removeMinFromTreeReturnBHeap(Node *tree)
{
    list<Node *> heap;
    Node *temp = tree->child;
    Node *lo;

    while (temp)
    {
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        heap.push_front(lo);
    }
    return heap;
}

list<Node *> insert(list<Node *> _head, int key)
{
    Node *temp = newNode(key);
    return insertATreeInHeap(_head, temp);
}

Node *getMin(list<Node *> bin_heap)
{
    list<Node *>::iterator it = bin_heap.begin();
    Node *temp = *it;
    while (it != bin_heap.end())
    {
        if ((*it)->data < temp->data)
            temp = *it;
        it++;
    }
    return temp;
}

list<Node *> extractMin(list<Node *> bin_heap)
{
    list<Node *> newbin_heap, lo;
    Node *temp;

    temp = getMin(bin_heap);
    list<Node *>::iterator it;
    it = bin_heap.begin();
    while (it != bin_heap.end())
    {
        if (*it != temp)
        {

            newbin_heap.push_back(*it);
        }
        it++;
    }
    lo = removeMinFromTreeReturnBHeap(temp);
    newbin_heap = unionBionomialHeap(newbin_heap, lo);
    newbin_heap = adjust(newbin_heap);
    return newbin_heap;
}

void printTree(Node *h)
{
    while (h)
    {
        cout << h->data << " ";
        printTree(h->child);
        h = h->sibling;
    }
}

void printHeap(list<Node *> bin_heap)
{
    list<Node *>::iterator it;
    it = bin_heap.begin();
    while (it != bin_heap.end())
    {
        printTree(*it);
        it++;
    }
}

int main()
{
    int ch, key;
    list<Node *> bin_heap;

    bin_heap = insert(bin_heap, 5);
    bin_heap = insert(bin_heap, 20);
    bin_heap = insert(bin_heap, 8);
    bin_heap = insert(bin_heap, 13);
    bin_heap = insert(bin_heap, 28);

    cout << "Heap elements after insertion:\n";
    printHeap(bin_heap);

    Node *temp = getMin(bin_heap);
    cout << "\nMinimum element of heap "
        << temp->data << "\n";

    bin_heap = extractMin(bin_heap);
    cout << "Heap after deletion of minimum element\n";
    printHeap(bin_heap);

    return 0;
}
