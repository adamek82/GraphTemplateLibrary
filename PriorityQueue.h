#ifndef PQ_container
#define PQ_container

#include <vector>
#include <map>
#include <cassert>

using namespace std;

template <typename KeyType, typename DataType>
class PriorityQueue
{
protected:
	int pqmax;
	struct HeapItem
	{
		int priority;
		KeyType key;
		DataType data;
	};
	std::vector<HeapItem> contents;
	std::map<KeyType, int> position;
	int num;

	void upheap(int pos, KeyType key, int priority, DataType data);
	void downheap(int pos, KeyType key, int priority, DataType data);
public:
	PriorityQueue(int initialMaxSize) : pqmax(initialMaxSize) 
	{
		contents.resize(pqmax);
		num = 0;
	}
	bool IsEmpty()
	{
		return num == 0;
	}
	~PriorityQueue() {}

	void enqueue(KeyType key, int priority, DataType data);
	KeyType dequeue(int &priority, DataType &data);
	bool change(KeyType key, int priority, DataType data);
	bool update(KeyType key, int priority);
};

template <typename KeyType, typename DataType>
void PriorityQueue<KeyType, DataType>::upheap(int pos, KeyType key, int priority, DataType data)
{
	int parent;

	while (pos>0 && contents[parent=(pos-1)/2].priority > priority) 
	{
		contents[pos] = contents[parent];
		position[contents[pos].key] = pos;
		pos = parent;
	}
	contents[pos].key = key;
	contents[pos].priority = priority;
	contents[pos].data = data;
	position[key] = pos;
}

// inserts element into position pos of priority queue pq, and restores
// the heap property moving downward. 
template <typename KeyType, typename DataType>
void PriorityQueue<KeyType, DataType>::downheap(int pos, KeyType key, int priority, DataType data)
{
	int lc,rc,child;

	while ((lc=2*pos+1) < num)
	{
		child = ((rc = lc + 1) < num && contents[rc].priority < contents[lc].priority) ? rc : lc;
		if (contents[child].priority >= priority)
			break;

		contents[pos] = contents[child];
		position[contents[pos].key] = pos;
		pos = child;
	}

	contents[pos].key = key;
	contents[pos].priority = priority;
	contents[pos].data = data;
	position[key] = pos;
}

template <typename KeyType, typename DataType>
void PriorityQueue<KeyType, DataType>::enqueue(KeyType key, int priority, DataType data)
{
	if (num == pqmax)
	{
		pqmax += pqmax;
		contents.resize(pqmax);
	}
	upheap(num++, key, priority, data);
}

template <typename KeyType, typename DataType>
KeyType PriorityQueue<KeyType, DataType>::dequeue(int &priority, DataType &data)
{
	KeyType key = contents[0].key;
	priority = contents[0].priority;
	data = contents[0].data;

	position[key] = -1;

	--num;
	downheap(0, contents[num].key, contents[num].priority, contents[num].data);
	return key;
}

// updates priority of a node. updated priority must be less or equal than current one.
// if a node could not be found, a new node is inserted.
template <typename KeyType, typename DataType>
bool PriorityQueue<KeyType, DataType>::change(KeyType key, int priority, DataType data)
{
	typename std::map<KeyType, int>::const_iterator iter = position.find(key);
	
	if (iter == position.end())
	{
		upheap(num++, key, priority, data);
		return true;
	}
	else if (contents[iter->second].priority > priority)
	{
		upheap(iter->second, key, priority, data);
		return true;
	}
	return false;
}

// updates priority of a node. updated priority may be less, equal, or grater than current one.
// does not insert a new node, when it cannot be found.
template <typename KeyType, typename DataType>
bool PriorityQueue<KeyType, DataType>::update(KeyType key, int priority)
{
	typename std::map<KeyType, int>::const_iterator iter = position.find(key);

	if (iter == position.end())
		return false;
	
	int pos = position[key];

	if (pos < num) 
	{
		if (contents[pos].priority > priority) 
			upheap(pos, key, priority, contents[pos].data);
		else if (contents[pos].priority < priority) 
			downheap(pos, key, priority, contents[pos].data);
	}

	return true;
}

#endif
