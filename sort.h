
#ifndef _SORT_H_
#define _SORT_H_


#define POSITIVE_SENTINEL ((pow(2,((sizeof(int)*8)-1))) - 1)

#define NEGATIVE_SENTINEL (-(pow(2,((sizeof(int)*8)-1)))) 

 
using namespace std;


//SORT Class 
class SORT{
	public:
		SORT();
		~SORT();
	
		void 		MergeSort(Edge *, int, int);
		void 		Merge(Edge *, int, int, int);			
};

#endif 
