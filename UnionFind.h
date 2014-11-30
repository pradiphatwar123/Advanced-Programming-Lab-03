
#ifndef _UNIONFIND_H_
#define _UNIONFIND_H_


#define POSITIVE_SENTINEL ((pow(2,((sizeof(int)*8)-1))) - 1)

#define NEGATIVE_SENTINEL (-(pow(2,((sizeof(int)*8)-1)))) 

 
using namespace std;

//Binary Search Tree Node 
class UFNode
{
	public:
		string		name;
		int		rank;
		UFNode		*parent;

};

//UNIONFIND ADT class
class UNIONFIND
{

	public:
		UNIONFIND();
		UNIONFIND(int);
		~UNIONFIND();

		bool			success;
		UFNode			*UFSets;
		
		void 			MakeSet(char *);
		void 			Union(char *, char *);
		UFNode* 		FindSet(char *);
	private:
		void 			Link(UFNode *, UFNode *);
		
};

#endif 
