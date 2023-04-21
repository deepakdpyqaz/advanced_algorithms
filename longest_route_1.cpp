#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Tree
{
public:
    int data;
    Tree *left;
    Tree *right;
    Tree(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }

    void insert(int data)
    {
        if (data == this->data)
        {
            return;
        }
        if (data < this->data)
        {
            if (left == NULL)
            {
                left = new Tree(data);
            }
            else
            {
                left->insert(data);
            }
        }
        else
        {
            if (right == NULL)
            {
                right = new Tree(data);
            }
            else
            {
                right->insert(data);
            }
        }
    }
    void display()
    {
        if (left != NULL)
        {
            left->display();
        }
        cout << data << " ";
        if (right != NULL)
        {
            right->display();
        }
    }

    int getDepth(Tree *root)
    {
        if (root == NULL)
            return 0;
        else
        {
            int lDepth = getDepth(root->left);
            int rDepth = getDepth(root->right);

            if (lDepth > rDepth)
                return (lDepth + 1);
            else
                return (rDepth + 1);
        }
    }
    int maxpathlength()
    {
        int lh=0,rh=0;
        int ld=0,rd=0;
        if (this == NULL)
            return 0;

        int ldiameter = this->left->maxpathlength();
        int rdiameter = this->right->maxpathlength();

        int diameter = getDepth(this->left) + getDepth(this->right) + 1;
        return max(diameter,
            max(ldiameter, rdiameter));
    }
};

int main()
{
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    Tree *root = nullptr;
    srand(time(0));
    cout<<"Data entered:  ";
    for (int i = 0; i < n; i++)
    {
        int data = rand() % 10000;
        cout<<data<<" ";
        if (root == nullptr)
        {
            root = new Tree(data);
        }
        else
        {
            root->insert(data);
        }
    }
    cout << "\nTree: ";
    root->display();

    cout<<endl<<"Max path length: "<<root->maxpathlength();
    return 0;
}