/*********************************************************************************************************
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :   03 - KRUSKAL MST ALGORITHM Implementation using UNIONFIND ADT

File name         :  UNIONFIND.CPP

Description       :  Implements Interfaces for UNIONFIND Abstract Data Type (ADT) Operations

Programmers       :  (1) Pradip Hatwar     (CS13M022)
                     (2) Hem Kapil         (CS13M023)
                     (3) Pradeep Vankadaru (CS13M037)

Compiler name     :  g++-4.6

Date created      :  26/09/2013

List of functions : (1)  		UNIONFIND(void)
					(2)  		UNIONFIND(int)
                    (3)  		~UNIONFIND(void)
                    (4)  void  		MakeSet(char *)
                    (5)  void 		Union(char *, char *)
                    (6)  void 		FindSet(char *);
		    (7)	 void 		Link(char *, char *);
History           :  

*********************************************************************************************************/

#include<iostream>

#include "globals.h"
#include "UnionFind.h"

int makeCnt=0; // Counter for number of sets initialised using MakeSet
int	Num_Nodes =0; // Num_Nodes to hold global count of number of nodes craeted in graph


/*********************************************************************************************************
Function Name            : UNIONFIND 
Inputs                   : void                          
Returns                  : void
Description              : Empty Constructor
*********************************************************************************************************/
UNIONFIND::UNIONFIND()
{


}

/*********************************************************************************************************
Function Name            : UNIONFIND 
Inputs                   : void                          
Returns                  : void
Description              : Constructor to initialise list of nodes for Uninon-Find data structure
*********************************************************************************************************/

UNIONFIND::UNIONFIND(int num_nodes)
{

	Num_Nodes = num_nodes;	// Num_Nodes to hold global count of number of nodes craeted in graph
	try{
		UFSets = new UFNode[INITIAL_NODES_COUNT];
	}catch(bad_alloc xa){
		success = false;
		cout << "Failed to intialize memory for UnionFind Nodes List" << endl; 
	}		
	success = true;
}

/*********************************************************************************************************
Function Name            : ~UNIONFIND 
Inputs                   : void                          
Returns                  : void
Description              : Destructor 
*********************************************************************************************************/

UNIONFIND::~UNIONFIND()
{

}

/*********************************************************************************************************
Function Name            : MakeSet 
Inputs                   : (1) char x                          
Returns                  : void
Description              : This function creates a singleton set, a single node in the corresponding tree
						   has initial rank 0. Each node points to itself as parent
*********************************************************************************************************/
void UNIONFIND::MakeSet(char *x)
{
	UFSets[makeCnt].name.assign(x);  // Assign name to the node
	UFSets[makeCnt].rank = 0;		 // Assign initial rank 0 to the node
	UFSets[makeCnt].parent = &UFSets[makeCnt]; //Each node points to itself as parent initially

	makeCnt++;
}
/*********************************************************************************************************
Function Name            : Union 
Inputs                   : (1) char - Node name 1  
						   (1) char - Node name 2                        
Returns                  : void
Description              : This function performs union operation on the two sets namely x and y
*********************************************************************************************************/
void UNIONFIND::Union(char *x, char *y)
{

	UFNode *x_node, *y_node;

	int i=0;
	
	x_node = FindSet(x); // Find the representative node of set where x is the part of set
	y_node = FindSet(y); // Find the representative node of set where y is the part of set

	Link(x_node, y_node); // Link the two node representatives x_node and y_node
	
}
/*********************************************************************************************************

Function Name            : FindSet 
Inputs                   : (1) char x                          
Returns                  : (1) UFNode of x
Description              : This function is a two pass method: as it recurses, it makes one pass up the 
						   find path to find the root, and as the recursion unwinds, it makes a second pass
						   back to update each node point directly to the root
*********************************************************************************************************/
UFNode* UNIONFIND::FindSet(char *x)
{	
	UFNode *y;
	int i=0;
	
	string temp(x);

	// Find the location of 'x'in the list of nodes
	for(i=0; i<Num_Nodes; i++) 
	{
	
		if (UFSets[i].name.compare(temp) == 0) // x found at location i
			break;
	}
	if(UFSets[i].name.compare(UFSets[i].parent->name) != 0) // x is not its own parent that is x is not a singleton set
	{
	
		UFSets[i].parent = FindSet(const_cast<char*>(UFSets[i].parent->name.c_str())); // Find root of x and in the process
																					   // of recursion do Path-compression


	}

	return UFSets[i].parent; // Return representative node of as set [Or Root ]

}


/*********************************************************************************************************
Function Name            : Link 
Inputs                   : (1) UFNode type - Node 1    
						   (2) UFNode type - Node 2                     
Returns                  : void
Description              : This function does union of two sets depending upon the ranks of roots. If roots 
						   have unequal rank, root with the higher rank is made parent of the root with lower
						   rank but the rank themselves remain unchanged.
						   In case roots have equal ranks, y_node is chosen as parent of x_node.
*********************************************************************************************************/
void UNIONFIND::Link(UFNode *x_node1, UFNode *y_node1)
{
	int i=0, j=0;
	
	if ( x_node1->rank > y_node1->rank  ) // Compare ranks
	{
		y_node1->parent = x_node1; // If x_node has higher rank make it parent of y_node
		
	}
	else
	{
		x_node1->parent = y_node1;	// Else make y_node parent of x_node
		
		if(x_node1->rank == y_node1->rank) // If ranks of both nodes are equal
			y_node1->rank = y_node1->rank +1; // Assign y_node a higher rank
	}

}

