#include<iostream>
#include<climits>
using namespace std;
class MinHeap
{
	int *harr; 
	int capacity; 
	int heap_size; 
public:
	MinHeap(int capacity);
	void MinHeapify(int );
	int parent(int i) { return (i-1)/2; }
	int left(int i) { return (2*i + 1); }
	int right(int i) { return (2*i + 2); }
	int extractMin();
	void decreaseKey(int i, int new_val);
	int getMin() { return harr[0]; }
	void deleteKey(int i);
	void insertKey(int k);
    void show();
};


MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}


void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swap(harr[i], harr[parent(i)]);
	i = parent(i);
	}
}



void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swap(harr[i], harr[parent(i)]);
	i = parent(i);
	}
}


int MinHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	
	int root = harr[0];
	harr[0] = harr[heap_size-1];
	heap_size--;
	MinHeapify(0);

	return root;
}




void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}



void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(harr[i], harr[smallest]);
		MinHeapify(smallest);
	}
}

void MinHeap::show(){
    for(int i=0;i<heap_size;i++)
        cout<<harr[i]<<" ";
    cout<<endl;
}


int main()
{
	MinHeap h(50);
	h.insertKey(5);
	h.insertKey(20);
	h.insertKey(3);
	h.insertKey(25);
	h.insertKey(40);
	h.insertKey(45);
	h.insertKey(65);
    cout<<"Heap:"<<endl;
    h.show();
	cout <<"Extract Min:"<<h.extractMin() <<endl;
	cout <<"Get Min:"<< h.getMin() << "\n";
    h.show();
    cout<<"Decrease key 2 to 1"<<endl;
	h.decreaseKey(2, 1);
    h.show();
	cout <<"Get Min:" << h.getMin()<<endl;
    h.deleteKey(1);
    cout<<"After deleting key 1"<<endl;
    h.show();

	return 0;
}
