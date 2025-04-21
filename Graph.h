#ifndef GraphTemplateLibrary
#define GraphTemplateLibrary

#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>
#include <cassert>
#include <cstdlib>
#include "PriorityQueue.h"

#ifndef ToInt
#define  ToInt( strToCast ) atoi( strToCast.c_str() )
#endif

using namespace std;

template <typename T>
class Arc;

template <typename T>
class Node;

template <typename T>
class Graph;

template <typename NodeType>
std::ostream& operator<<(std::ostream &s, const Node<NodeType>& node);

template <typename NodeType>
std::ostream& operator<<(std::ostream &s, const Node<NodeType>* node);

template <typename NodeType>
std::ostream& operator<<(std::ostream &s, const std::vector<Node<NodeType>*> &vecNodes);

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const Graph<NodeType>& graph);

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const Arc<NodeType>& arc);

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const std::pair<Node<NodeType>*, Node<NodeType>*>& arc);

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> >& vecPairNodes);

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const std::list<std::pair<Node<NodeType>*, Node<NodeType>* > >& listEdges);

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, std::vector<std::list<std::pair<Node<NodeType>*, Node<NodeType>* > > >& vecListEdges);

template <typename T>
class Node
{
	friend class Graph<T>;
	friend class Arc<T>;
	friend std::ostream& operator<< <>(std::ostream &s, const Node<T>& node);
	friend std::ostream& operator<< <>(std::ostream &s, const Node<T>* node);
	friend std::ostream& operator<< <>(std::ostream &s, const Graph<T>& graph);

	T name;
	std::list<Arc<T> > neighbors;
	bool visited;
	Node* previous;
	bool dfsFinished;
	int dfsNumber;
	int numChildren;
public:
	Node() : name(T()), visited(false), previous(NULL), dfsFinished(false), dfsNumber(0), numChildren(0) {}
	Node(T _name) : name(_name), visited(false), previous(NULL), dfsFinished(false), dfsNumber(0), numChildren(0) {}
	T& GetName()
	{
		return name;
		visited = false;
	}

	void AddArc(Node &dstNode, int weight = 1);
};

template<typename T>
void Node<T>::AddArc(Node &dstNode, int weight)
{
	neighbors.push_back(Arc<T>(dstNode, weight));
}

template <typename T>
class Arc
{
	friend class Graph<T>;
	friend class Node<T>;
	friend std::ostream& operator<< <>(std::ostream& s, const Arc<T>& arc);

	Node<T> &destNode;
	int weight;
public:
	Arc(Node<T> &_destNode, int _weight) : destNode(_destNode)
	{
		weight = _weight;
		assert(weight > 0);
	}
};

template <typename NodeType>
class Graph
{
public:
	typedef std::pair<Node<NodeType>*, Node<NodeType>* > Edge;
	typedef std::vector<std::list<Edge> > VecListEdges;
	typedef std::stack<Edge> BiconnectedComponentsStack;

private:
	friend class Arc<NodeType>;
	friend class Node<NodeType>;
	friend std::ostream& operator<< <>(std::ostream& s, const Graph<NodeType>& graph);

	std::vector<Node<NodeType>* > nodes;
	std::map<NodeType, Node<NodeType> *> nodeNamesToNodesMap;

	int globalNum;

	int visit(Node<NodeType> &node1, Node<NodeType> &node2, int currentLength = 0);
	void visit(Node<NodeType> &node1, int currentLength = 0);
	void visitRoot(Node<NodeType> &node, std::set<Node<NodeType>*> &articulationPointsSet);
	int visitNonRoot(Node<NodeType> &node, Node<NodeType> &father, std::set<Node<NodeType>*> &articulationPointsSet);
	void checkCycle(Node<NodeType> &node, std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> > &cycleNodes);
	void visitTopological(Node<NodeType> &node, std::vector<Node<NodeType>*> &topologicalNodes);
	void biconVisitRoot(Node<NodeType> &node, VecListEdges &biconComponents);
	int biconVisitNonRoot(Node<NodeType> &node, Node<NodeType> &father, VecListEdges &biconComponents, 
		BiconnectedComponentsStack &biconStack);
	void biconPopFromStack(const Edge &edge, VecListEdges &biconComponents, 
		BiconnectedComponentsStack &biconStack);
	void visitStronglyConnectedComponents(Node<NodeType> &node, std::stack<Node<NodeType> *> &nodesStack);
	void visitTransposedStronglyConnectedComponents(Node<NodeType> &node, std::stack<Node<NodeType> *> &nodesStack);
public:
	Graph() : globalNum(0) { }
	~Graph() { Clear(); }
	Graph(const Graph &g);

	Node<NodeType>& AddNode(NodeType nodeName);
	Node<NodeType>& AddNode(const Node<NodeType> &node);
	Node<NodeType>& AddNode(Node<NodeType> *node);

	Node<NodeType>& GetNodeByName(NodeType name) const;

	void Clear();
	void ResetResults();

	int BFS(Node<NodeType> &node1, Node<NodeType> &node2);
	void DFS(Node<NodeType> &node1);
	int DFS(Node<NodeType> &node1, Node<NodeType> &node2);
	int ShortestPath(Node<NodeType> &node1, Node<NodeType> &node2);
	std::vector<Node<NodeType>*> FindArticulationPoints();
	VecListEdges GetBiconnectedComponents();
	std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> > FindMinimumSpanningTree(Node<NodeType> &startingNode);
	std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> > FindCycles(Node<NodeType> &startingNode);
	std::vector<Node<NodeType>*> TopologicalSort(Node<NodeType> &node);
	std::vector<Node<NodeType>*> GetPath(Node<NodeType> &node1, Node<NodeType> &node2);
	Graph<NodeType> Transpose();
	void GetStronglyConnectedComponents();

	void ReadGraphFromFile(std::string fileName);
};

template <typename NodeType>
Graph<NodeType>::Graph(const Graph<NodeType> &g)
{
	// first copy all the nodes
	for (typename std::vector<Node<NodeType>* >::const_iterator iter = g.nodes.begin(); iter != g.nodes.end(); iter++)
	{
		this->AddNode(**iter);
	}
	// then copy all nodes' neighbors
	for (typename std::vector<Node<NodeType>* >::const_iterator iter = g.nodes.begin(); iter != g.nodes.end(); iter++)
	{
		Node<NodeType> &copiedNode = GetNodeByName((*iter)->name);
		for (typename std::list<Arc<NodeType> >::const_iterator arcsIter = (*iter)->neighbors.begin();
			arcsIter != (*iter)->neighbors.end(); arcsIter++)
		{
			Node<NodeType> &origNode = g.GetNodeByName(arcsIter->destNode.name);
			copiedNode.AddArc(GetNodeByName(origNode.name), arcsIter->weight);
		}
	}
}

template <typename NodeType>
void Graph<NodeType>::ResetResults()
{
	globalNum = 0;
	for (typename std::vector<Node<NodeType>* >::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		(*iter)->previous = NULL;
		(*iter)->visited = false;
		(*iter)->dfsFinished = false;
		(*iter)->dfsNumber = 0;
		(*iter)->numChildren = 0;
	}
}

template <typename NodeType>
void Graph<NodeType>::Clear()
{
	for (typename std::vector<Node<NodeType>* >::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
		delete *iter;
}

template <typename NodeType>
int Graph<NodeType>::visit(Node<NodeType> &node1, Node<NodeType> &node2, int currentLength)
{
	if (node2.dfsFinished)
		return currentLength;
	node1.visited = true;
#ifndef NDEBUG
	std::cout << node1 << std::endl;
#endif
	if (&node1 == &node2)
	{
		node2.dfsFinished = true;
		return currentLength;
	}

	for (typename std::list<Arc<NodeType> >::const_iterator iter = node1.neighbors.begin();
		iter != node1.neighbors.end(); iter++)
	{
		if (!iter->destNode.visited)
		{
			iter->destNode.previous = &node1;
			return visit(iter->destNode, node2, currentLength + 1);
		}
#ifndef NDEBUG
		else
		{
			std::cout << "Back edge: " << std::endl;
		}
#endif
	}

	return -1;
}

template <typename NodeType>
void Graph<NodeType>::visit(Node<NodeType> &node1, int currentLength)
{
	node1.visited = true;
#ifndef NDEBUG
	std::cout << node1 << std::endl;
#endif
	for (typename std::list<Arc<NodeType> >::const_iterator iter = node1.neighbors.begin();
		iter != node1.neighbors.end(); iter++)
	{
		if (!iter->destNode.visited)
		{
			iter->destNode.previous = &node1;
			return visit(iter->destNode, currentLength + 1);
		}
#ifndef NDEBUG
		else
		{
			std::cout << "Back edge: " << node1 << "-" << iter->destNode << std::endl;
		}
#endif
	}
}

template <typename NodeType>
int Graph<NodeType>::DFS(Node<NodeType> &node1, Node<NodeType> &node2)
{
	return visit(node1, node2);
}

template <typename NodeType>
void Graph<NodeType>::DFS(Node<NodeType> &node1)
{
	return visit(node1);
}

template <typename NodeType>
int Graph<NodeType>::BFS(Node<NodeType> &node1, Node<NodeType> &node2)
{
	std::queue<std::pair<Node<NodeType>*, int> > q;
	Node<NodeType> *node = &node1;

	q.push(std::make_pair(node, 0));
	while (!q.empty())
	{
		std::pair<Node<NodeType>*, int> p = q.front();
		q.pop();
		if (!p.first->visited)
		{
			p.first->visited = true;
#ifndef NDEBUG
			std::cout << "(" << p.first << ", " << p.second << ") " << std::endl;
#endif
			if (p.first == &node2)
				return p.second;
			for (typename std::list<Arc<NodeType> >::const_iterator iter = p.first->neighbors.begin();
				iter != p.first->neighbors.end(); iter++)
			{
				if (!iter->destNode.visited)
				{
					iter->destNode.previous = p.first;
					q.push(make_pair(&iter->destNode, p.second+1));
				}
			}
		}
	}

	return -1;
}

template <typename NodeType>
int Graph<NodeType>::ShortestPath(Node<NodeType> &node1, Node<NodeType> &node2)
{
	PriorityQueue<Node<NodeType>*, string> pq(100);
	pq.enqueue(&node1, 0, node1.GetName());
	int length = -1;

	while (!pq.IsEmpty())
	{
		int priority;
		string data;
		Node<NodeType> *node = pq.dequeue(priority, data);
		node->visited = true;
#ifndef NDEBUG
		std::cout << "(" << node << ", " << priority << ")" << std::endl;
#endif
		if (node == &node2)
		{
			length = priority;
			break;
		}
		for (typename std::list<Arc<NodeType> >::const_iterator iter = node->neighbors.begin();
			iter != node->neighbors.end(); iter++)
		{
			if (!iter->destNode.visited)
			{
				if (pq.change(&iter->destNode, iter->weight + priority, iter->destNode.GetName()))
					iter->destNode.previous = node;
			}
		}
	}

	return length;
}

template <typename NodeType>
std::vector<Node<NodeType>*> Graph<NodeType>::GetPath(Node<NodeType> &node1, Node<NodeType> &node2)
{
	std::vector<Node<NodeType>*> path;

	Node<NodeType> *p = &node2;
	do
	{
		path.push_back(p);
		p = p->previous;
		if (!p)
			break;
	} while (p != &node1);
	if (p && &node1 != &node2)
		path.push_back(&node1);

	std::vector<Node<NodeType>*> reversed(path.rbegin(), path.rend());
	return reversed;
}

template <typename NodeType>
int Graph<NodeType>::visitNonRoot(Node<NodeType> &node, Node<NodeType> &father, std::set<Node<NodeType>*> &articulationPointsSet)
{
	node.dfsNumber = ++globalNum;
	father.numChildren++;
	int lowest = globalNum;
	for (typename std::list<Arc<NodeType> >::const_iterator iter = node.neighbors.begin();
		iter != node.neighbors.end(); iter++)
	{
		if (iter->destNode.dfsNumber == 0)
		{
			int childlowest = visitNonRoot(iter->destNode, node, articulationPointsSet);
			lowest = min(lowest, childlowest);
			if (childlowest >= node.dfsNumber)
				articulationPointsSet.insert(&node);
		}
		else
			lowest = min(lowest, iter->destNode.dfsNumber);
	}
	return lowest;
}

template <typename NodeType>
void Graph<NodeType>::visitRoot(Node<NodeType> &node, std::set<Node<NodeType>*> &articulationPointsSet)
{
	node.dfsNumber = ++globalNum;
	for (typename std::list<Arc<NodeType> >::const_iterator iter = node.neighbors.begin();
		iter != node.neighbors.end(); iter++)
	{
		if (iter->destNode.dfsNumber == 0)
			visitNonRoot(iter->destNode, node, articulationPointsSet);
	}
	// check if root is an articulation point
	if (node.numChildren >= 2)
		articulationPointsSet.insert(&node);
}

template <typename NodeType>
std::vector<Node<NodeType>*> Graph<NodeType>::FindArticulationPoints()
{
	std::set<Node<NodeType>*> articulationPointsSet;

	ResetResults();

	for (typename std::vector<Node<NodeType>* >::iterator iter = nodes.begin();
		iter != nodes.end();
		iter++)
	{
		if ((*iter)->dfsNumber == 0)
			visitRoot(**iter, articulationPointsSet);
	}

	return std::vector<Node<NodeType>*> (articulationPointsSet.begin(), articulationPointsSet.end());
}

template <typename NodeType>
void Graph<NodeType>::biconPopFromStack(const Edge &edge, typename Graph<NodeType>::VecListEdges &biconComponents,
										typename Graph<NodeType>::BiconnectedComponentsStack &biconStack)
{
	Edge poppedEdge;
	std::list<Edge> edgesList;
	do
	{
		poppedEdge = biconStack.top();
		biconStack.pop();
		edgesList.push_back(poppedEdge);
	} while (poppedEdge != edge);
	biconComponents.push_back(edgesList);
}

template <typename NodeType>
int Graph<NodeType>::biconVisitNonRoot(Node<NodeType> &node, Node<NodeType> &father, 
										typename Graph<NodeType>::VecListEdges &biconComponents,
										typename Graph<NodeType>::BiconnectedComponentsStack &biconStack)
{
	node.dfsNumber = ++globalNum;
	int lowest = globalNum;
	for (typename std::list<Arc<NodeType> >::const_iterator iter = node.neighbors.begin();
		iter != node.neighbors.end(); iter++)
	{
		if (iter->destNode.dfsNumber == 0)
		{
			biconStack.push(make_pair(&node, &iter->destNode));
			int childlowest = biconVisitNonRoot(iter->destNode, node, biconComponents, biconStack);
			lowest = min(lowest, childlowest);
			if (childlowest >= node.dfsNumber)
				biconPopFromStack(make_pair(&node, &iter->destNode), biconComponents, biconStack); 
		}
		else
		{
			lowest = min(lowest, iter->destNode.dfsNumber);
			// TODO: add != and == operator from Node<T>
			if ((node.dfsNumber > iter->destNode.dfsNumber) && (iter->destNode.name != father.name))
				biconStack.push(make_pair(&node, &iter->destNode));
		}
	}

	return lowest;
}

template <typename NodeType>
void Graph<NodeType>::biconVisitRoot(Node<NodeType> &node, typename Graph<NodeType>::VecListEdges &biconComponents)
{
	std::stack<Edge> edgeStack;
	node.dfsNumber = ++globalNum;

	for (typename std::list<Arc<NodeType> >::const_iterator iter = node.neighbors.begin();
			iter != node.neighbors.end(); iter++)
	{
		if (iter->destNode.dfsNumber == 0)
		{
			edgeStack.push(make_pair(&node, &iter->destNode));
			biconVisitNonRoot(iter->destNode, node, biconComponents, edgeStack);
			biconPopFromStack(make_pair(&node, &iter->destNode), biconComponents, edgeStack);
		}
	}
}

template <typename NodeType>
typename Graph<NodeType>::VecListEdges Graph<NodeType>::GetBiconnectedComponents()
{
	std::vector<std::list<Edge>> biconComponents;

	ResetResults();

	for (typename std::vector<Node<NodeType>* >::const_iterator nodesIter = nodes.begin();
		nodesIter != nodes.end();
		nodesIter++)
	{
		if ((*nodesIter)->dfsNumber == 0)
			biconVisitRoot(**nodesIter, biconComponents);
	}

	return biconComponents;
}

template <typename NodeType>
std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> > Graph<NodeType>::FindMinimumSpanningTree(Node<NodeType> &startingNode)
{
	std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> > mstArcs;	

	PriorityQueue<Node<NodeType>*, Node<NodeType>*> pq(100);
	pq.enqueue(&startingNode, 0, &startingNode);

	while (!pq.IsEmpty())
	{
		int priority;
		Node<NodeType> *parent;
		Node<NodeType> *node = pq.dequeue(priority, parent);
		node->visited = true;
		if (priority != 0)
			mstArcs.push_back(make_pair(parent, node));
		for (typename std::list<Arc<NodeType> >::const_iterator iter = node->neighbors.begin();
			iter != node->neighbors.end(); iter++)
		{
			if (!iter->destNode.visited)
				pq.change(&(iter->destNode), iter->weight, node);
		}
	}

	return mstArcs;
}

template <typename NodeType>
void Graph<NodeType>::checkCycle(Node<NodeType> &node, std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> > &cycleNodes)
{
	node.dfsNumber = ++globalNum;
	for (typename std::list<Arc<NodeType> >::const_iterator iter = node.neighbors.begin();
		iter != node.neighbors.end(); iter++)
	{
		if (iter->destNode.dfsNumber == 0)
			checkCycle(iter->destNode, cycleNodes);
		else if (iter->destNode.dfsNumber < node.dfsNumber)
			cycleNodes.push_back(make_pair(&node, &iter->destNode));
	}
	node.dfsNumber = std::numeric_limits<int>::max();
}

template <typename NodeType>
std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> > Graph<NodeType>::FindCycles(Node<NodeType> &startingNode)
{
	std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> > cycleNodes;	
	checkCycle(startingNode, cycleNodes);
	return cycleNodes;
}

template <typename NodeType>
void Graph<NodeType>::visitTopological(Node<NodeType> &node, std::vector<Node<NodeType>*> &topologicalNodes)
{
	node.visited = true;
	for (typename std::list<Arc<NodeType> >::const_iterator iter = node.neighbors.begin();
		iter != node.neighbors.end(); iter++)
	{
		if (!iter->destNode.visited)
			visitTopological(iter->destNode, topologicalNodes);
	}
	topologicalNodes.push_back(&node);
}

template <typename NodeType>
std::vector<Node<NodeType>*> Graph<NodeType>::TopologicalSort(Node<NodeType> &node)
{
	std::vector<Node<NodeType>*> topologicalNodes;
	visitTopological(node, topologicalNodes);
	std::vector<Node<NodeType>*> reversedTopological(topologicalNodes.rbegin(), topologicalNodes.rend());
	return reversedTopological;
}

template <typename NodeType>
Graph<NodeType> Graph<NodeType>::Transpose()
{
	Graph<NodeType> gT;

	// add nodes
	for (typename std::vector<Node<NodeType>* >::const_iterator nodesIter = nodes.begin();
		nodesIter != nodes.end();
		nodesIter++)
	{
		gT.AddNode(**nodesIter);
	}
	// add arcs
	for (typename std::vector<Node<NodeType>* >::const_iterator nodesIter = nodes.begin();
		nodesIter != nodes.end();
		nodesIter++)
	{
		for (typename std::list<Arc<NodeType> >::const_iterator iter = (*nodesIter)->neighbors.begin();
			iter != (*nodesIter)->neighbors.end(); iter++)
		{
			Node<NodeType> &transposedNode = gT.GetNodeByName(iter->destNode.name);
			transposedNode.AddArc(gT.GetNodeByName((*nodesIter)->name));
		}
	}

	return gT;
}

template <typename NodeType>
void Graph<NodeType>::visitStronglyConnectedComponents(Node<NodeType> &node, std::stack<Node<NodeType> *> &nodesStack)
{
	node.visited = true;
	for (typename std::list<Arc<NodeType> >::const_iterator iter = node.neighbors.begin();
			iter != node.neighbors.end(); iter++)
	{
		if (!iter->destNode.visited)
			visitStronglyConnectedComponents(iter->destNode, nodesStack);
	}
	nodesStack.push(&node);
}

template <typename NodeType>
void Graph<NodeType>::visitTransposedStronglyConnectedComponents(Node<NodeType> &node, std::stack<Node<NodeType> *> &nodesStack)
{
	std::cout << node << " ";
	node.visited = true;
	for (typename std::list<Arc<NodeType> >::const_iterator iter = node.neighbors.begin();
		iter != node.neighbors.end(); iter++)
	{
		if (!iter->destNode.visited)
		{
			nodesStack.pop();
			visitTransposedStronglyConnectedComponents(iter->destNode, nodesStack);
		}
	}
}

template <typename NodeType>
void Graph<NodeType>::GetStronglyConnectedComponents()
{
	std::stack<Node<NodeType>*> nodesStack;
	for (typename std::vector<Node<NodeType>* >::const_iterator nodesIter = nodes.begin();
		nodesIter != nodes.end();
		nodesIter++)
	{
		if (!(*nodesIter)->visited)
			visitStronglyConnectedComponents(**nodesIter, nodesStack);
	}

	Graph<NodeType> gT = Transpose();

	while (!nodesStack.empty())
	{
		Node<NodeType> *node = nodesStack.top();
		nodesStack.pop();
		visitTransposedStronglyConnectedComponents(gT.GetNodeByName(node->name), nodesStack);
		std::cout << endl;
	}
}

template <typename NodeType>
Node<NodeType>& Graph<NodeType>::GetNodeByName(NodeType name) const
{
	typename std::map<NodeType, Node<NodeType> *>::const_iterator iter = nodeNamesToNodesMap.find(name);
	if (iter != nodeNamesToNodesMap.end())
		return *(iter->second);

	throw out_of_range("Graph::GetNodeByName(): no node named \"" + name + "\"");
}

template <typename NodeType>
Node<NodeType>& Graph<NodeType>::AddNode(Node<NodeType> *node)
{
	nodes.push_back(node);
	nodeNamesToNodesMap[node->name] = node;
	return *node;
}

template <typename NodeType>
Node<NodeType>& Graph<NodeType>::AddNode(NodeType nodeName)
{
	return AddNode(new Node<NodeType>(nodeName));
}

template <typename NodeType>
Node<NodeType>& Graph<NodeType>::AddNode(const Node<NodeType> &node)
{
	return AddNode(new Node<NodeType>(node.name));
}

void Graph<std::string>::ReadGraphFromFile(std::string fileName)
{
	ResetResults();
	std::vector<Node<std::string>* >().swap(nodes);

	std::ifstream inputFile(fileName.c_str());
	if (inputFile)
	{
		std::string line;
		std::getline(inputFile, line);
		int nodesCount = ToInt(line);
		for (int i=1; i<=nodesCount; i++)
		{
			if (!std::getline(inputFile, line).eof())
				AddNode(line);
			else
			{
				// TODO: throw an appropriate exception
				return;
			}
		}
		while (!std::getline(inputFile, line).eof())
		{
			if (line == "")
				continue;
			size_t pos = line.find(":");
			if (pos == std::string::npos)
			{
				// TODO: throw an appropriate exception
				return;
			}
			std::string nodeName = line.substr(0, pos);
			std::string arcNames = line.substr(pos+1);
			Node<std::string> &node = GetNodeByName(nodeName);
			while (arcNames != "")
			{
				size_t pos = arcNames.find(",");
				std::string destNodeName = ((pos != std::string::npos) ? arcNames.substr(0, pos) : arcNames);
				Node<std::string> &destNode = GetNodeByName(destNodeName);	// TODO: this can throw an exception which should be handled here
				node.AddArc(destNode);
				arcNames = ((pos != std::string::npos) ? arcNames.substr(pos+1) : "");
			}
		}
	}
}

template <typename NodeType>
std::ostream& operator<<(std::ostream &s, const Node<NodeType>& node)
{
	s << node.name;
	return s;
}

template <typename NodeType>
std::ostream& operator<<(std::ostream &s, const Node<NodeType>* node)
{
	s << node->name;
	return s;
}

template <typename NodeType>
std::ostream& operator<<(std::ostream &s, const std::vector<Node<NodeType>*> &vecNodes)
{
	std::copy(vecNodes.begin(), vecNodes.end(), ostream_iterator<Node<NodeType>*>(s, " "));
	return s;
}

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const Arc<NodeType>& arc)
{
	s << arc.destNode << "(" << arc.weight << ")";
	return s;
}

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const Graph<NodeType>& graph)
{
	for (typename std::vector<Node<NodeType>* >::const_iterator iter = graph.nodes.begin();
		iter != graph.nodes.end();
		iter++)
	{
		s << *iter << ": ";
		std::copy((*iter)->neighbors.begin(), (*iter)->neighbors.end(), ostream_iterator<Arc<NodeType>>(s, " "));
		s << endl;
	}
	return s;
}

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const std::pair<Node<NodeType>*, Node<NodeType>*>& arc)
{
	s << "(" << arc.first << ", " << arc.second << ")";
	return s;
}

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const std::vector<std::pair<Node<NodeType>*, Node<NodeType>*> >& vecPairNodes)
{
	std::copy(vecPairNodes.begin(), vecPairNodes.end(), 
		ostream_iterator<pair<Node<NodeType>*, Node<NodeType>*> >(cout, " "));
	return s;
}

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, const std::list<std::pair<Node<NodeType>*, Node<NodeType>* > >& listEdges)
{
	std::copy(listEdges.begin(), listEdges.end(),
		ostream_iterator<std::pair<Node<NodeType>*, Node<NodeType>* > >(cout, " "));
	return s;
}

template <typename NodeType>
std::ostream& operator<<(std::ostream& s, std::vector<std::list<std::pair<Node<NodeType>*, Node<NodeType>* > > >& vecListEdges)
{
	std::copy(vecListEdges.begin(), vecListEdges.end(),
		ostream_iterator<std::list<std::pair<Node<NodeType>*, Node<NodeType>* > > >(cout, "\n"));
	return s;
}

#endif
