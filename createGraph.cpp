#include<iostream>
#include<string>
#include<fstream>

// define constants
#define MaxSize 50
#define MaxVer 50
using namespace std;

// define data structures 
typedef struct GEdge {
	int child, weight;
	struct GEdge*nextEdge;
}*GEdgePtr;

typedef struct GVertex {
	char id[MaxSize + 1], color;
	int inDegree;
	GEdgePtr firstEdge;
};

// a basic function which create a vertex
GVertex newGVertex(char name[]) {
	GVertex temp;
	strcpy_s(temp.id, name);
	temp.firstEdge = NULL;
	return temp;
}

GEdgePtr newGEdge(int c, int w) {
	GEdgePtr p = new GEdge;
	p->child = c;
	p->weight = w;
	p->nextEdge = NULL;
	return p;
}

typedef struct Graph {
	int numV;
	GVertex vertex[MaxVer + 1];
}*GraphPtr;

GraphPtr newGraph(int n) {
	if (n>MaxVer) {
		printf("Error");
		exit(1);
	}
	GraphPtr p = new Graph;
	p->numV = n;
	return p;
}
int addEdge(char x[], char y[], int weight, GraphPtr G) {
	int j, k;
	// find x in the list of nodes, its location is j
	for (j = 1; j <= G->numV; j++) {
		//printf("%s->%s -  j %d",x,G->vertex[j].id, j);
		if (strcmp(x, G->vertex[j].id) == 0) break;
	}

	// find y in the list of nodes, its location is k
	for (k = 1; k <= G->numV; k++) {
		
		if (strcmp(y, G->vertex[k].id) == 0) break;
	}
	//printf(" before j %d k %d numv %d  \n", j, k, G->numV);

	if (j>G->numV || k > G->numV) {
		cout << "no such edge" << x << " --> " << y;
		exit(1);
	}
	// at this point we are sure that x and y are verticies of the grpah G
	GEdgePtr ep = newGEdge(k, weight);
	GEdgePtr prev, curr;
	prev = curr = G->vertex[j].firstEdge;
	while (curr != NULL && strcmp(y, G->vertex[curr->child].id)>0) {
		prev = curr;
		curr = curr->nextEdge;
	}
	if (prev == curr) {
		ep->nextEdge = G->vertex[j].firstEdge;
		G->vertex[j].firstEdge = ep;
	}
	else {
		ep->nextEdge = curr;
		prev->nextEdge = ep;
	}
}


void buildGraph(std::fstream *in, GraphPtr G) {
	int j, k, numEdges, weight;
	char nodeID[MaxSize + 1], adjID[MaxSize + 1];

	// read the labels of the vertices
	for (j = 1; j <= G->numV; j++) {
		G->vertex[j] = newGVertex("");
		*in>>G->vertex[j].id;
	}

	// read and create edges
	for (j = 1; j <= G->numV; j++) {
		*in >> nodeID; 
		*in>> numEdges;
		for (k = 1; k <= numEdges; k++) {
			*in >> adjID; 
			*in>> weight;
			addEdge(nodeID, adjID, weight, G);
		}
	}
}


void printGraph(GraphPtr G) {
	int j;
	for (j = 1; j <= G->numV; j++) {
		cout<< G->vertex[j].id<<":";
		GEdgePtr p = G->vertex[j].firstEdge;
		while (p != NULL) {
			cout << G->vertex[p->child].id<<" ";
			cout<<p->weight<<" ";
			p = p->nextEdge;
		}
		cout<<"\n";
	}
}
3

int main() {
	int numVertices;
	fstream in; 
	in.open("graph.txt");
	if (!in.is_open()) { cout<<"Can not open the file"; system("pause"); exit(1); }
	// reading the first line in the file
	in>>numVertices;
	GraphPtr G = newGraph(numVertices);
	// first its opening the file from the abov code 

	buildGraph(&in, G);
	cout<<"The graph Created based on graph.txt \n";
	printGraph(G);
	//fclose(in);

	fstream in1; 
	in1.open("graph1.txt");
	if (!in1.is_open()) { cout<<"Can not open the file"; system("pause"); exit(1); }
	in1>>numVertices;
	GraphPtr G1 = newGraph(numVertices);
	buildGraph(&in1, G1);
	cout<<"\n \n The graph Created based on graph1.txt \n";
	printGraph(G1);
	//fclose(in1);
	system("pause");
}


