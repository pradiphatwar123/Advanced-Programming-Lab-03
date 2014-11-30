/*********************************************************************************************************
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :  03 - KRUSKAL MST ALGORITHM Implementation using UNIONFIND ADT

File name         :  KRUSKAL.CPP

Description       :  Implements Interfaces for KRUSKAL ALGORITHM

Programmers       :  (1) Pradip Hatwar     (CS13M022)
                     (2) Hem Kapil         (CS13M023)
                     (3) Pradeep Vankadaru (CS13M037)

Compiler name     :  g++-4.6

Date created      :  26/09/2013

List of functions : (1)  		KRUSKAL(void)
                    (2)  		~KRUSKAL(void)
                    (3)  		kruskal(void)	
History           :  

*********************************************************************************************************/

#include<iostream>

#include "globals.h"
#include "kruskal.h"
#include "UnionFind.h"
#include "sort.h"

using namespace std;


int mst_edges_count=0;

/*********************************************************************************************************
Function Name            : KRUSKAL
Inputs                   : void                       
Returns                  : void
Description              : Constructor
*********************************************************************************************************/
KRUSKAL::KRUSKAL( )
{
	try{
		Graph_Nodes_List = new Node[INITIAL_NODES_COUNT]; // Graph_Nodes_List to hold list of nodes in a graph
	}catch(bad_alloc xa){
		success = false;
		cout << "Failed to intialize memory for Graph Nodes List" << endl; 
	}			
	try{
		Graph_Edges_List = new Edge[INITIAL_EDGES_COUNT]; // Graph_Edges_List to hold list of edges in a graph
	}catch(bad_alloc xa){
		success = false;
		cout << "Failed to intialize memory for Graph Edges List" << endl; 
	}
	try{
		Graph_Sorted_Edges_List = new Edge[INITIAL_EDGES_COUNT]; // Graph_Sorted_Edges_List to hold list of sorted edges in a graph
	}catch(bad_alloc xa){
		success = false;
		cout << "Failed to intialize memory for Graph Sorted Edges List" << endl; 
	}
	try{
		MST_Edges_List = new Edge[MST_EDGES_COUNT];// MST_Edges_List to hold list of edges of Minimum Spanning Tree of a graph
	}catch(bad_alloc xa){
		success = false;
		cout << "Failed to intialize memory for MST Edges List" << endl; 
	}

	NODES_COUNT = INITIAL_NODES_COUNT;
	EDGES_COUNT = INITIAL_EDGES_COUNT;	
	NUM_NODES   = 0;
	NUM_EDGES   = 0;		
	NUM_MST_EDGES   = 0;


	if(success != false)
		success = true;
}

/*********************************************************************************************************
Function Name            : ~KRUSKAL
Inputs                   : void                       
Returns                  : void
Description              : Destructor
*********************************************************************************************************/

KRUSKAL::~KRUSKAL()
{
	delete [] Graph_Nodes_List; 
	delete [] Graph_Edges_List; 
	delete [] Graph_Sorted_Edges_List; 
	delete [] MST_Edges_List; 
}
/*********************************************************************************************************
Function Name            : kruskal
Inputs                   : void                      
Returns                  : void
Description              : This function implements kruskal algorithm
*********************************************************************************************************/
bool KRUSKAL::Kruskal()
{
	bool 		error = false; 
	int 		i=0, j=0;
	string		str_u, str_v;
	SORT		SortObj;

	UNIONFIND	UFObj(NUM_NODES);
	UFNode 		*uNode, *vNode;
	
	if(UFObj.success == false)
	{
		cout<< "Failed to initialize UnionFind Sets " << endl;
		error = true;	
	}
	else
	{		
		for(i=0; i< NUM_NODES; i++)  // For each vertex in Graph Make-set			
		{
			UFObj.MakeSet(const_cast<char*>(Graph_Nodes_List[i].name.c_str()));
		}
		// Sort the edges into non-decreasing order by weight
		SortObj.MergeSort(Graph_Sorted_Edges_List, 0, NUM_EDGES - 1);		
		cout << endl <<  "Sorted Edges " << endl << endl;
		for(j = 0; j < NUM_EDGES; j++)
		{
			cout << "Edge::" << Graph_Sorted_Edges_List[j].u.name.c_str();
			cout << "::" << Graph_Sorted_Edges_List[j].v.name.c_str();
			cout << "::" << Graph_Sorted_Edges_List[j].weight << endl;

		}
		// For each edge taken in nondecreasing order by weight
		for(j=0; j<NUM_EDGES ; j++)
		{
					
			// Findset operation returns uNode which is the representative element from the set that contains 'u'
			uNode = UFObj.FindSet(const_cast<char*>(Graph_Sorted_Edges_List[j].u.name.c_str()));

			// Findset operation returns vNode which is the representative element from the set that contains 'v'
			vNode = UFObj.FindSet(const_cast<char*>(Graph_Sorted_Edges_List[j].v.name.c_str()));
					
			str_u.assign(uNode->name.c_str());
			str_v.assign(vNode->name.c_str());

			if(str_u.compare(str_v) != 0 )	// Check if two elements 'u' and 'v' belongs to the same tree
			{
				
				// If not this means two vertices belong to different trees
				// MST_Edges_List is updated to include the edge
				MST_Edges_List[mst_edges_count].u.name.assign(Graph_Sorted_Edges_List[j].u.name.c_str());
				MST_Edges_List[mst_edges_count].v.name.assign(Graph_Sorted_Edges_List[j].v.name.c_str());
				MST_Edges_List[mst_edges_count].weight = Graph_Sorted_Edges_List[j].weight;

				mst_edges_count++; //Counter for MST edges
				NUM_MST_EDGES++; //Counter for MST edges

				//Merge the vertices the two tress
				UFObj.Union(const_cast<char*>(str_u.c_str()), const_cast<char*>(str_v.c_str()));
			} //end if

		} // end for
		
		cout << endl  << "  MST edges are " << NUM_MST_EDGES << endl << endl;

		for(j = 0; j < NUM_MST_EDGES; j++)
		{			
			cout << "MST Edge " << j <<  ":: " << MST_Edges_List[j].u.name.c_str() ;
			cout << "::" << MST_Edges_List[j].v.name.c_str();
			cout << "::" << MST_Edges_List[j].weight << endl;
		}


	} // end if-else
	return error;	
}

