#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_


using namespace std;

//KRUSKAL Class
class KRUSKAL
{
	public:
		KRUSKAL();
		~KRUSKAL();

		bool 	success;	
		int	NODES_COUNT;		//Size of Graph Vertices Dynamic Array
		int	EDGES_COUNT;		//Size Of Graph Edges Dynamic Array
		int	NUM_NODES;		//Num Of Vertices in the given input Graph
		int	NUM_EDGES;		//Num Of Edges in the given input Graph
		int	NUM_MST_EDGES;  	//Num Of Edges in the MST of the given input Graph
	
		Node	*Graph_Nodes_List;		//Pointer to Graph Vertices dynamic Array
		Edge	*Graph_Edges_List;		//Pointer to Graph Edges dynamic Array
		Edge	*Graph_Sorted_Edges_List;	//Pointer to Graph Sorted Edges dynamic Array
		Edge	*MST_Edges_List;		//Pointer to Graph MST Edges dynamic Array

		bool 	Kruskal();		
};
#endif 
