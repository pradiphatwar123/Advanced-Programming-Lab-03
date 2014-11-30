#ifndef _GLOBALS_H_
#define _GLOBALS_H_


#define 	POSITIVE_SENTINEL 	((pow(2,((sizeof(int)*8)-1))) - 1)

#define 	NEGATIVE_SENTINEL 	(-(pow(2,((sizeof(int)*8)-1)))) 

#define		INITIAL_NODES_COUNT	256

#define 	INITIAL_EDGES_COUNT	((INITIAL_NODES_COUNT *(INITIAL_NODES_COUNT -1))/2)

#define 	MST_EDGES_COUNT		(INITIAL_NODES_COUNT - 1) 

#define 	SIZE_INCREMENT 		50

using namespace std;



//Graph Node 
class Node
{
	public:
		string		name; //Node Name
};
//Graph Edge
class Edge
{
	
	public: 
		Node		u;		//Start Vertex of Edge
		Node		v;		//End Vertex of Edge
		int		weight;		//Weight of Edge
	Edge()
	{		
		weight = 0;
	} 

};

int	ValidateCmdline(int, char *[], char **, char **);
int 	CheckFiles(char *, char *);
int	ValidateFile(char *);	
int 	ValidateInput(char *, int );
void	PopulateGraph(char *, void *);
int	VerifyEdges(void *, string ,string , int );
bool	Kruskal();
int	WriteOutput(char *, void *);	
int 	LookMst(void *, string , string );

#endif 
