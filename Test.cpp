#include <iostream>
#include "PriorityQueue.h"
#include "Graph.h"

using namespace std;

int main()
{
/*	Graph<string> g;

	Node<string>& nodeA = g.AddNode("A");
	Node<string>& nodeB = g.AddNode("B");
	Node<string>& nodeC = g.AddNode("C");
	Node<string>& nodeD = g.AddNode("D");
	Node<string>& nodeE = g.AddNode("E");
	Node<string>& nodeF = g.AddNode("F");
	Node<string>& nodeG = g.AddNode("G");
	Node<string>& nodeH = g.AddNode("H");
	Node<string>& nodeI = g.AddNode("I");
	Node<string>& nodeJ = g.AddNode("J");
	Node<string>& nodeK = g.AddNode("K");
	Node<string>& nodeL = g.AddNode("L");
	Node<string>& nodeM = g.AddNode("M");
	Node<string>& nodeN = g.AddNode("N");
	Node<string>& nodeO = g.AddNode("O");
	Node<string>& nodeP = g.AddNode("P");

	nodeA.AddArc(nodeB, 1);		// AB = 1
	nodeB.AddArc(nodeA, 1);		// BA

	nodeB.AddArc(nodeC, 1);		// BC = 1
	nodeC.AddArc(nodeB, 1);		// CB

	nodeC.AddArc(nodeD, 1);		// CD = 1
	nodeD.AddArc(nodeC, 1);		// DC

	nodeA.AddArc(nodeE, 7);		// AE = 7
	nodeE.AddArc(nodeA, 7);		// EA

	nodeB.AddArc(nodeF, 9);		// BF = 9
	nodeF.AddArc(nodeB, 9);		// FB

	nodeC.AddArc(nodeG, 7);		// CG = 7
	nodeG.AddArc(nodeC, 7);		// GC

	nodeD.AddArc(nodeH, 1);		// DH = 1
	nodeH.AddArc(nodeD, 1);		// HD

	nodeE.AddArc(nodeF, 6);		// EF = 6
	nodeF.AddArc(nodeE, 6);		// FE

	nodeF.AddArc(nodeG, 4);		// FG = 4
	nodeG.AddArc(nodeF, 4);		// GF

	nodeG.AddArc(nodeH, 3);		// GH = 3
	nodeH.AddArc(nodeG, 3);		// HG

	nodeE.AddArc(nodeI, 2);		// EI = 2
	nodeI.AddArc(nodeE, 2);		// IE

	nodeF.AddArc(nodeJ, 8);		// FJ = 8
	nodeJ.AddArc(nodeF, 8);		// JF

	nodeG.AddArc(nodeK, 6);		// GK = 6
	nodeK.AddArc(nodeG, 6);		// KG

	nodeH.AddArc(nodeL, 1);		// HL = 1
	nodeL.AddArc(nodeH, 1);		// LH

	nodeI.AddArc(nodeJ, 1);		// IJ = 1
	nodeJ.AddArc(nodeI, 1);		// JI

	nodeJ.AddArc(nodeK, 1);		// JK = 1
	nodeK.AddArc(nodeJ, 1);		// KJ

	nodeK.AddArc(nodeL, 1);		// KL = 1
	nodeL.AddArc(nodeK, 1);		// LK

	nodeI.AddArc(nodeM, 1);		// IM = 1
	nodeM.AddArc(nodeI, 1);		// MI

	nodeJ.AddArc(nodeN, 7);		// JN = 7
	nodeN.AddArc(nodeJ, 7);		// NJ

	nodeK.AddArc(nodeO, 6);		// KO = 6
	nodeO.AddArc(nodeK, 6);		// OK

	nodeL.AddArc(nodeP, 8);		// LP = 8
	nodeP.AddArc(nodeL, 8);		// PL

	nodeM.AddArc(nodeN, 1);		// MN = 1
	nodeN.AddArc(nodeM, 1);		// NM

	nodeN.AddArc(nodeO, 1);		// NO = 1
	nodeO.AddArc(nodeN, 1);		// ON

	nodeO.AddArc(nodeP, 1);		// OP = 1
	nodeP.AddArc(nodeO, 1);		// PO
*/
/*
	Graph<string> g;

	Node<string>& nodeA = g.AddNode("A");
	Node<string>& nodeB = g.AddNode("B");
	Node<string>& nodeC = g.AddNode("C");
	Node<string>& nodeD = g.AddNode("D");
	Node<string>& nodeE = g.AddNode("E");
	Node<string>& nodeF = g.AddNode("F");
	Node<string>& nodeG = g.AddNode("G");
	Node<string>& nodeH = g.AddNode("H");
	Node<string>& nodeI = g.AddNode("I");
	Node<string>& nodeJ = g.AddNode("J");
	Node<string>& nodeK = g.AddNode("K");
	Node<string>& nodeL = g.AddNode("L");
	Node<string>& nodeM = g.AddNode("M");
	Node<string>& nodeN = g.AddNode("N");
	Node<string>& nodeO = g.AddNode("O");
	Node<string>& nodeP = g.AddNode("P");
	Node<string>& nodeQ = g.AddNode("Q");

	nodeA.AddArc(nodeB, 1);		// AB = 1
	nodeB.AddArc(nodeA, 1);
	nodeB.AddArc(nodeC, 9);		// BC = 9
	nodeC.AddArc(nodeB, 9);
	nodeA.AddArc(nodeE, 5);		// AE = 5
	nodeE.AddArc(nodeA, 5);
	nodeB.AddArc(nodeF, 3);		// BF = 3
	nodeF.AddArc(nodeB, 3);
	nodeE.AddArc(nodeF, 2);		// EF = 2
	nodeF.AddArc(nodeE, 2);
	nodeA.AddArc(nodeF, 7);		// AF = 7
	nodeF.AddArc(nodeA, 7);
	nodeB.AddArc(nodeE, 2);		// BE = 2
	nodeE.AddArc(nodeB, 2);
	nodeC.AddArc(nodeD, 4);		// CD = 4
	nodeD.AddArc(nodeC, 4);
	nodeD.AddArc(nodeG, 9);		// DG = 9
	nodeG.AddArc(nodeD, 9);
	nodeC.AddArc(nodeE, 4);		// CE = 4
	nodeE.AddArc(nodeC, 4);
	nodeH.AddArc(nodeI, 1);		// HI = 1
	nodeI.AddArc(nodeH, 1);
	nodeI.AddArc(nodeJ, 1);		// IJ = 1
	nodeJ.AddArc(nodeI, 1);
	nodeH.AddArc(nodeJ, 1);		// HJ = 1
	nodeJ.AddArc(nodeH, 1);
*/	

/* bicon-test
	Graph<string> g;
	Node<string>* nodeA = g.AddNode("A");
	Node<string>* nodeB = g.AddNode("B");
	Node<string>* nodeC = g.AddNode("C");
	Node<string>* nodeD = g.AddNode("D");
	Node<string>* nodeE = g.AddNode("E");
	Node<string>* nodeF = g.AddNode("F");
	Node<string>* nodeG = g.AddNode("G");
	Node<string>* nodeH = g.AddNode("H");
	Node<string>* nodeI = g.AddNode("I");
	Node<string>* nodeJ = g.AddNode("J");

	nodeA->AddArc(nodeB, 1);		// AB
	nodeB->AddArc(nodeA, 1);
	nodeA->AddArc(nodeE, 1);		// AE
	nodeE->AddArc(nodeA, 1);
	nodeA->AddArc(nodeF, 1);		// AF
	nodeF->AddArc(nodeA, 1);
	nodeB->AddArc(nodeC, 1);		// BC
	nodeC->AddArc(nodeB, 1);
	nodeB->AddArc(nodeE, 1);		// BE
	nodeE->AddArc(nodeB, 1);
	nodeB->AddArc(nodeF, 1);		// BF
	nodeF->AddArc(nodeB, 1);
	nodeC->AddArc(nodeE, 1);		// CE
	nodeE->AddArc(nodeC, 1);
	nodeC->AddArc(nodeD, 1);		// CD
	nodeD->AddArc(nodeC, 1);
	nodeD->AddArc(nodeG, 1);		// DG
	nodeG->AddArc(nodeD, 1);
	nodeH->AddArc(nodeI, 1);		// HI
	nodeI->AddArc(nodeH, 1);
	nodeI->AddArc(nodeJ, 1);		// IJ
	nodeJ->AddArc(nodeI, 1);
	nodeJ->AddArc(nodeH, 1);		// JH
	nodeH->AddArc(nodeJ, 1);
*/
/*
	Graph<string> g;
	Node<string>* nodeA = g.AddNode("A");
	Node<string>* nodeB = g.AddNode("B");
	Node<string>* nodeC = g.AddNode("C");
	nodeA->AddArc(nodeB, 1);		// AB
	nodeB->AddArc(nodeA, 1);
	nodeA->AddArc(nodeC, 1);		// AC
	nodeC->AddArc(nodeA, 1);
	nodeB->AddArc(nodeC, 1);		// BC
	nodeC->AddArc(nodeB, 1);
*/

/*
	Graph<string> g;
	Node<string>& nodeA = g.AddNode("A");
	Node<string>& nodeB = g.AddNode("B");
	Node<string>& nodeC = g.AddNode("C");
	Node<string>& nodeD = g.AddNode("D");
	Node<string>& nodeE = g.AddNode("E");
	Node<string>& nodeF = g.AddNode("F");
	Node<string>& nodeG = g.AddNode("G");
	Node<string>& nodeH = g.AddNode("H");
	Node<string>& nodeI = g.AddNode("I");
	Node<string>& nodeJ = g.AddNode("J");
	nodeA.AddArc(nodeB, 1);		// AB
	nodeA.AddArc(nodeE, 1);		// AE
	nodeB.AddArc(nodeE, 1);		// BE
	nodeC.AddArc(nodeB, 1);		// CB
	nodeC.AddArc(nodeE, 1);		// CE
	nodeD.AddArc(nodeC, 1);		// DC
	nodeD.AddArc(nodeG, 1);		// DG
	nodeF.AddArc(nodeA, 1);		// FA
	nodeF.AddArc(nodeB, 1);		// FB
	nodeF.AddArc(nodeE, 1);		// FE
	nodeH.AddArc(nodeI, 1);		// HI
	nodeI.AddArc(nodeJ, 1);		// IJ
	nodeJ.AddArc(nodeH, 1);		// JH

	vector<pair<Node<string>*, Node<string>*> > cycleNodes = g.FindCycles(nodeH);
	if (cycleNodes.size() > 0)
		cout << "Nodes containing cycle: " << cycleNodes << endl;
*/

/*
	//test topological sort
	Graph<string> g;
	Node<string>& nodeA = g.AddNode("A");
	Node<string>& nodeB = g.AddNode("B");
	Node<string>& nodeC = g.AddNode("C");
	nodeA.AddArc(nodeB);
	nodeA.AddArc(nodeC);
	nodeC.AddArc(nodeB);

	vector<Node<string>*> topologicalNodes = g.TopologicalSort(nodeA);
	cout << "Topological sort: " << topologicalNodes << endl;
*/

/*
	Graph<string> g;
	Node<string>& nodeA = g.AddNode("A");
	Node<string>& nodeB = g.AddNode("B");
	Node<string>& nodeC = g.AddNode("C");
	Node<string>& nodeD = g.AddNode("D");
	Node<string>& nodeE = g.AddNode("E");
	Node<string>& nodeF = g.AddNode("F");
	Node<string>& nodeG = g.AddNode("G");
	Node<string>& nodeH = g.AddNode("H");
	nodeA.AddArc(nodeB);
	nodeB.AddArc(nodeC);
	nodeB.AddArc(nodeF);
	nodeB.AddArc(nodeE);
	nodeC.AddArc(nodeD);
	nodeC.AddArc(nodeG);
	nodeD.AddArc(nodeC);
	nodeD.AddArc(nodeH);
	nodeE.AddArc(nodeA);
	nodeE.AddArc(nodeF);
	nodeF.AddArc(nodeG);
	nodeG.AddArc(nodeF);
	nodeG.AddArc(nodeH);
	nodeH.AddArc(nodeH);
*/	

/*
	Graph<string> g;
	Node<string>& nodeA = g.AddNode("A");
	Node<string>& nodeB = g.AddNode("B");
	Node<string>& nodeC = g.AddNode("C");
	Node<string>& nodeD = g.AddNode("D");
	Node<string>& nodeE = g.AddNode("E");
	Node<string>& nodeF = g.AddNode("F");
	Node<string>& nodeG = g.AddNode("G");
	Node<string>& nodeH = g.AddNode("H");
	Node<string>& nodeI = g.AddNode("I");
	Node<string>& nodeJ = g.AddNode("J");
	nodeA.AddArc(nodeB);	// A-B
	nodeB.AddArc(nodeA);
	nodeA.AddArc(nodeE);	// A-E
	nodeE.AddArc(nodeA);
	nodeA.AddArc(nodeF);	// A-F
	nodeF.AddArc(nodeA);
	nodeB.AddArc(nodeC);	// B-C
	nodeC.AddArc(nodeB);
	nodeB.AddArc(nodeE);	// B-E
	nodeE.AddArc(nodeB);
	nodeB.AddArc(nodeF);	// B-F
	nodeF.AddArc(nodeB);
	nodeC.AddArc(nodeE);	// C-E
	nodeE.AddArc(nodeC);
	nodeC.AddArc(nodeD);	// C-D
	nodeD.AddArc(nodeC);
	nodeE.AddArc(nodeF);	// E-F
	nodeF.AddArc(nodeE);
	nodeD.AddArc(nodeG);	// D-G
	nodeG.AddArc(nodeD);
	nodeH.AddArc(nodeI);	// H-I
	nodeI.AddArc(nodeH);
	nodeI.AddArc(nodeJ);	// I-J
	nodeJ.AddArc(nodeI);
	nodeH.AddArc(nodeJ);	// H-J
	nodeJ.AddArc(nodeH);

	vector<Node<string>*> articulationPoints = g.FindArticulationPoints();
	if (articulationPoints.size() > 0)
		cout << "Articulation points: " << articulationPoints << endl;
*/

/*
	Graph<string> g;
	Node<string>& nodeA = g.AddNode("A");
	Node<string>& nodeB = g.AddNode("B");
	Node<string>& nodeC = g.AddNode("C");
	Node<string>& nodeD = g.AddNode("D");
	Node<string>& nodeE = g.AddNode("E");
	Node<string>& nodeF = g.AddNode("F");
	Node<string>& nodeG = g.AddNode("G");
	nodeA.AddArc(nodeB);	// A-B
	nodeB.AddArc(nodeA);
	nodeA.AddArc(nodeC);	// A-C
	nodeC.AddArc(nodeA);
	nodeB.AddArc(nodeD);	// B-D
	nodeD.AddArc(nodeB);
	nodeC.AddArc(nodeD);	// C-D
	nodeD.AddArc(nodeC);
	nodeD.AddArc(nodeE);	// D-E
	nodeE.AddArc(nodeD);
	nodeD.AddArc(nodeF);	// D-F
	nodeF.AddArc(nodeD);
	nodeE.AddArc(nodeG);	// E-G
	nodeG.AddArc(nodeE);
	nodeF.AddArc(nodeG);	// F-G
	nodeG.AddArc(nodeF);

	vector<Node<string>*> articulationPoints = g.FindArticulationPoints();
	if (articulationPoints.size() > 0)
		cout << "Articulation points: " << articulationPoints << endl;
*/

/*
	Graph<string> g;
	Node<string>& nodeA = g.AddNode("A");
	Node<string>& nodeB = g.AddNode("B");
	Node<string>& nodeC = g.AddNode("C");
	Node<string>& nodeD = g.AddNode("D");
	Node<string>& nodeE = g.AddNode("E");
	Node<string>& nodeF = g.AddNode("F");
	Node<string>& nodeG = g.AddNode("G");
	Node<string>& nodeH = g.AddNode("H");
	Node<string>& nodeI = g.AddNode("I");
	Node<string>& nodeJ = g.AddNode("J");
	nodeA.AddArc(nodeB);	// A-B
	nodeB.AddArc(nodeA);
	nodeA.AddArc(nodeC);	// A-C
	nodeC.AddArc(nodeA);
	nodeB.AddArc(nodeE);	// B-E
	nodeE.AddArc(nodeB);
	nodeB.AddArc(nodeF);	// B-F
	nodeF.AddArc(nodeB);
	nodeE.AddArc(nodeG);	// E-G
	nodeG.AddArc(nodeE);
	nodeF.AddArc(nodeG);	// F-G
	nodeG.AddArc(nodeF);
	nodeC.AddArc(nodeH);	// C-H
	nodeH.AddArc(nodeC);
	nodeC.AddArc(nodeJ);	// C-J
	nodeJ.AddArc(nodeC);
	nodeH.AddArc(nodeI);	// H-I
	nodeI.AddArc(nodeH);
	nodeI.AddArc(nodeJ);	// I-J
	nodeJ.AddArc(nodeI);

	vector<Node<string>*> articulationPoints = g.FindArticulationPoints();
	if (articulationPoints.size() > 0)
		cout << "Articulation points: " << articulationPoints << endl;
*/
/*
	Graph<string> g;
	g.ReadGraphFromFile("graph.txt");
	cout << "Graph:" << endl;
	cout << g << endl;
	Graph<string> gT = g.Transpose();
	cout << "Transposed graph:" << endl;
	cout << gT << endl;
	g.GetStronglyConnectedComponents();
*/
	
	
/*	int length = g.ShortestPath(nodeA, nodeP);
	if (length != -1)
	{
		cout << "Length = " << length << endl;
		vector<Node<string>*> path = g.GetPath(nodeA, nodeP);
		cout << "Path: " << path << endl;
	}
	g.ResetResults();

	length = g.BFS(nodeA, nodeP);
	if (length != -1)
	{
		cout << "BFS from " << nodeA << " to " << nodeP << " takes " << length << " steps" << endl;
		vector<Node<string>*> path = g.GetPath(nodeA, nodeP);
		cout << "Path: " << path << endl;
	}
	g.ResetResults();

	length = g.DFS(nodeA, nodeP);
	if (length != -1)
	{
		cout << "DFS from " << nodeA << " to " << nodeP << " takes " << length << " steps" << endl;
		vector<Node<string>*> path = g.GetPath(nodeA, nodeP);
		cout << "Path: " << path << endl;
	}
	g.ResetResults();

	vector<pair<Node<string>*, Node<string>*> > minSpanningTreeArcs = g.FindMinimumSpanningTree(nodeA);
	if (minSpanningTreeArcs.size() > 0)
		cout << "Minimum spanning tree: " << minSpanningTreeArcs << endl;
*/	
	/*
	vector<Node<string>*> articulationPoints = g.FindArticulationPoints();
	if (articulationPoints.size() > 0)
		cout << "Articulation points: " << articulationPoints << endl;

	vector<list<pair<Node<string>*, Node<string>* > > > bicon = g.GetBiconnectedComponents();
	*/

/* Krótki test krawêdzi powrotnych */
/*
	Graph<string> g;
	Node<string>& nodeA = g.AddNode("A");
	Node<string>& nodeB = g.AddNode("B");
	Node<string>& nodeC = g.AddNode("C");
	nodeA.AddArc(nodeB);
	nodeB.AddArc(nodeA);
	nodeB.AddArc(nodeC);
	nodeC.AddArc(nodeB);

	g.DFS(nodeA);
*/

	Graph<string> g;
	g.ReadGraphFromFile("graph.txt");
	cout << "Graph:" << endl;
	cout << g << endl;

	vector<Node<string>*> articulationPoints = g.FindArticulationPoints();
	if (articulationPoints.size() > 0)
		cout << "Articulation points: " << articulationPoints << endl;

	Graph<string>::VecListEdges biConnComponents = g.GetBiconnectedComponents();
	cout << "Biconnected components: " << biConnComponents << endl;
}
