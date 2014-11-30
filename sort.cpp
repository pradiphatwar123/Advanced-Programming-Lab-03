/*********************************************************************************************************
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :   03 - KRUSKAL MST ALGORITHM Implementation using UNIONFIND ADT

File name         :  SORT.CPP

Description       :  Implements Interfaces for Sorting Edges of Graph

Programmers       :  (1) Pradip Hatwar     (CS13M022)
                     (2) Hem Kapil         (CS13M023)
                     (3) Pradeep Vankadaru (CS13M037)

Compiler name     :  g++-4.6

Date created      :  21/09/2013

List of functions : (1)  		SORT(void)
                    (2)  		~SORT(void)
                    (3)  void  		MERGESORT()
					(4)  void 		MERGE();	
                    
History           :  

*********************************************************************************************************/

#include<iostream>
#include <math.h>
#include "globals.h"
#include "sort.h"


SORT::SORT()
{
	
}
SORT::~SORT()
{
	
}
/*********************************************************************************************************
Function Name            : MERGESORT 
Inputs                   : (1) int itemToInsert                          
Returns                  : void
Description              : This function implements MergeSort Algorithm
*********************************************************************************************************/
void SORT::MergeSort(Edge *Graph_Edges_List1, int p, int r)
{
	int 	q;
     
	if(p<r)
	{
           q=(p+r)/2;
	
           MergeSort(Graph_Edges_List1,p,q);
           MergeSort(Graph_Edges_List1,q+1,r);
           Merge(Graph_Edges_List1,p,q,r);

		 
          }
	
}
/*********************************************************************************************************
Function Name            : MERGE
Inputs                   : (1) int position                          
Returns                  : void
Description              : This function implements Merge procedure to merge 2 sorted sublists
*********************************************************************************************************/
void SORT::Merge(Edge *sorted_Edges_List, int p, int q, int r)
{	
	int i,j,k;
    	int n1,n2;


    	n1=q-p+1;
    	n2=r-q;

	Edge *L=new Edge[n1+1],*R=new Edge[n2+1];

	for(i=0;i<n1;i++)
	{				
		L[i]=sorted_Edges_List[p+i];	
	}
	for(j=0;j<n2;j++)
	{
            	R[j]=sorted_Edges_List[q+j+1];

	}

    	L[n1].weight = POSITIVE_SENTINEL;
    	R[n2].weight = POSITIVE_SENTINEL;


    	i=0;
    	j=0;

    	for(k=p;k<=r;k++)
    	{
              if(L[i].weight <= R[j].weight)
              {          
                         sorted_Edges_List[k]=L[i];
                         i++;
              }
              else
              {
                         sorted_Edges_List[k]=R[j]; 
                         j++;         
              }                           
    	}
}
