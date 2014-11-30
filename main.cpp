/*********************************************************************************************************
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :  03 - KRUSKAL MST ALGORITHM Implementation using UNIONFIND ADT

File name         :  MAIN.CPP

Description       :  Implements main functions required to implement Kruskal MST Algorithm

Programmers       :  (1) Pradip Hatwar     (CS13M022)
                     (2) Hem Kapil         (CS13M023)
                     (3) Pradeep Vankadaru (CS13M037)

Compiler name     :  g++-4.6

Date created      :  21/09/2013

List of functions : (1)  int 	main(int argc, char *argv[])
		    (2)  int	ValidateCmdline(int, char *[], char **, char **, char **);
		    (3)  int 	CheckFiles(char *, char *);
		    (4)	 int	ValidateFile(char *);	
		    (5)  int 	ValidateInput(char *);
		    (6)  void	PopulateGraph(char *);	
		    (7)  int	VerifyEdges(void *, string ,string , int );					    
		    (8)  bool	Kruskal();	
		    (9)  int	WriteOutput(char *);		     
		    (10) int 	LookMst(void *, string , string );	
                    
History           :  

*********************************************************************************************************/
#include<iostream>
#include<cstdlib>
#include<ctype.h>
#include<fstream>
#include<cstring>
#include<sstream>

#include "globals.h"
#include "kruskal.h"


int	nodes_count = 0, edges_count = 0;

/*********************************************************************************************************
Function Name            : main 
Inputs                   : (1) Number of command line arguements passed
			   (2) List of Command line arguements
Outputs                  : int
Description              : This is a 'main'function which implements UnionFind ADT Operations.
*********************************************************************************************************/

int main(int argc, char *argv[])
{		
	char		*inputfile, *outputfile;
	bool		retval;
	KRUSKAL		KObj;

	inputfile = (char *)" " ;	
	outputfile = (char *)" ";
			
	// Check if proper command line arguements are given 
	if(ValidateCmdline(argc,argv,&inputfile,&outputfile) == -1)  
	{   		
		cout << "Exiting ....." <<endl;
		exit(-1);		
	}					
	// Check for successful files existence operation on all files
	// successful create operation on outfile file given
	else if(CheckFiles(inputfile,outputfile) == -1) 
	{					    
		cout << "Exiting......" << endl;
		exit(-1);	
	}	
//	else if(ValidateFile(inputfile) == -1) // Validating Input File 
//	{
//		cout << "Failed to validate file  " << inputfile  << ", Exiting....." << endl;
//		exit(-1);
//	}
	else if(KObj.success == false)	// Check if unable to create object of KRUSKAL Class Object
	{				
		cout << "Failed to create Kruskal object, Exiting......." << endl;
        	exit(-1);         
	}										
	else
	{	
		//It reads graph nodes, edges information from input file and populates in arrays
		PopulateGraph(inputfile,&KObj);
		if((KObj.NUM_NODES == -1) && (KObj.NUM_EDGES == -1)) //Invalid Entries in the Input Graph
		{
			cout << "Exiting....." << endl;
			exit(-1);
		}
		else
		{							
			if(!((KObj.NUM_NODES == 0) && (KObj.NUM_EDGES == 0)))
			{	
				//It Implements Kruskal's MST Algorithm for the given input graph using UnionFind ADT
				retval = KObj.Kruskal();	
			}
			else
				retval = false;
			if(!retval)
			{
				WriteOutput(outputfile,&KObj);//Write to Output File
				cout << endl << "Output File produced, Program completed " << endl;
			}
		}
	} // End 
	getchar();
	return 0;
}
/*********************************************************************************************************
Function Name            : ValidateCmdline
Inputs                   : (1) Number of Command line arguements passed
			   (2) List of Command line arguements
			   (3) Reference to input file
			   (4) Reference to output file			   
Outputs                  : int 
			   0 If no error
			  -1 If Error
Description              : This function Validates Command line arguements
*********************************************************************************************************/
int	ValidateCmdline(int argc, char *argv[], char **inputfile, char **outputfile)
{
	
	int 	error = 0, iter;
	string	tempstr, tempstr1;
	
	if(argc < 3)	
	{	
		cout << "Error: valid command for execution is " << endl;
		cout << "<exename> <inputfilename>.gv <outputfilename>.gv"<< endl;		
		error = -1;
	}
	else
	{
		tempstr1 = argv[1];
		tempstr = tempstr1.substr(strlen(argv[1]) - 3, 3);		
		if(tempstr.compare(".gv") != 0)//Verifying whether input file extension is .gv
		{
			cout << "Error: valid command for execution is " << endl;
			cout << "<exename> <inputfilename>.gv <outputfilename>.gv"<< endl;		
			error = -1;
		}
		else
		{
			tempstr1 = argv[2];
			tempstr = tempstr1.substr(strlen(argv[2]) - 3, 3);			
			if(tempstr.compare(".gv") != 0)//Verifying whether output file extension is .gv
			{
				cout << "Error: valid command for execution is " << endl;
				cout << "<exename> <inputfilename>.gv <outputfilename>.gv"<< endl;			
				error = -1;
			}
			else			//Filling inputfile, outputfile entries
			{						
				*inputfile = argv[1];
				*outputfile = argv[2];		
			}	
		}
	}	

	return error;
}
/*********************************************************************************************************
Function Name            : check_files 
Inputs                   : (1) Reference to input file
			   (2) Reference to output file			   
Outputs                  : -1 In case of error 
                            0 In case of sucess
Description              : This function verifies the existence of input file, and creates output file if it does not exist
*********************************************************************************************************/
int CheckFiles(char *inputfile, char *outputfile)
{

	int		retval = 0;
	ifstream	inpstrm ; // Input file reference
	ofstream	optstrm ; // Output file reference
	

	inpstrm.open(inputfile, ios::in); /* Opening inputfile */

	if(!inpstrm)
	{
		cout << "File "  << inputfile << " does not exist" << endl;		
		retval = -1;
	}
	else
	{	
		inpstrm.close();
		inpstrm.open(outputfile, ios::out | ios::trunc); /* Creating outputfile if it does not exist*/
		if(!inpstrm)
		{
			cout << "File " << outputfile << " does not exist" << endl;			
			retval = -1;
		}
		else
		{
			inpstrm.close();			
		}			
	} 
	
		
	return retval;
}
/*********************************************************************************************************
Function Name            : PopulateGraph
Inputs                   : (1) Reference to input file	
			   (2) Reference to KRUSKAL Object			  
Outputs                  :   
Description              : This function reads data from input file and Populates into Graph Arrays
*********************************************************************************************************/
void PopulateGraph(char *inpfile, void *KObj1)
{	
	int			count = 0, retval = 0, nodes_start = 0, edges_start = 0,temp = 0;
	int			nodes_count = 0, edges_count = 0, line_num = 1;
	ifstream		inpstrm ;	
	char			buff1[10241],buff[100],ch;
	stringstream 		sis, sis1, sis2;	
	string			str, prevstr = " ";
	bool			value_exists = false ;
	string			node1, node2, edge_del, weigthlabel;
	string			tempstr[3];
	KRUSKAL			*KObj;

	KObj = (KRUSKAL *)KObj1;
	
	inpstrm.open(inpfile, ios::in);	/* Opening Input file */
	if(!inpstrm){
		cout << "Input File does not exist" << endl;				
	}
	else
	{			
		while(inpstrm)
		{			
			inpstrm.getline(buff1,10240,'\n');	// Reading Input file line wise 
			
			if(inpstrm)
			{				
				if(inpstrm.eof()) 
				{
					buff1[strlen(buff1)-1] = '\0';					
				}
				sis << buff1;					
				while(getline(sis,str,'\n'))
				{					
					//npos is very large value, if substring is not found it returns this value
					if(prevstr.find("nodes", 0) != std::string::npos) //Nodes start 
					{
						nodes_start = 1;
						cout << endl << "Graph Vertices " << endl << endl;	
					}
					if(str.find("edges",0) != std::string::npos) //Nodes End
					{
						cout << endl << "Graph Edges " << endl << endl;
						nodes_start = 0;
					}				
					if(prevstr.find("edges", 0 ) != std::string::npos) //Edges Start
					{
						edges_start = 1;
					}
					if(str.find("}",0) != std::string::npos) //Edges End
					{
						nodes_start = 0;	
						edges_start = 0;
						cout << endl;
					}
					if(nodes_start == 1) 	//Nodes
					{					
						KObj->Graph_Nodes_List[nodes_count++].name.assign(str, 0, str.length() - 1);						
						cout << "Vertex :: " << KObj->Graph_Nodes_List[nodes_count - 1].name << endl;  						
					}
					if(edges_start == 1)	//Edges
					{
						sis1 << str;
						
						sis1 >> node1 >> edge_del >> node2 >> weigthlabel;
						retval = VerifyEdges(KObj,node1,node2,nodes_count);
						if(retval == -1)	//Invalid Edge Endpoints
						{
							cout << "Edge Vertices are not present in Vertices list, Error at ine_num " << line_num << endl;
							break;
						}
						KObj->Graph_Edges_List[edges_count].u.name.assign(node1);
						KObj->Graph_Edges_List[edges_count].v.name.assign(node2);
						KObj->Graph_Sorted_Edges_List[edges_count].u.name.assign(node1);
						KObj->Graph_Sorted_Edges_List[edges_count].v.name.assign(node2);
																								
						sis2 << weigthlabel;
						temp =0;

						while(getline(sis2,tempstr[temp++],'"'))
						{
							//Breaking Edge Attribute into 3 parts keeping " as delimiter 	
						}
						KObj->Graph_Edges_List[edges_count].weight = atoi(tempstr[1].c_str());						
						KObj->Graph_Sorted_Edges_List[edges_count].weight = atoi(tempstr[1].c_str());					
						sis2.clear();	
						cout << "Edge :: " << KObj->Graph_Edges_List[edges_count].u.name << " :: " << KObj->Graph_Edges_List[edges_count].v.name << ":: " << KObj->Graph_Edges_List[edges_count].weight << endl;
							
						edges_count++;
						sis1.clear();	
					}
					line_num++;										
				}
				prevstr = str;
				sis.clear();
			}
			else
			{				
				if(inpstrm.eof())
				{
					//Reached end of the file 
				}
				else
				{
					cout << "Failed to read data from file " << inpfile << "inside PopulateGraph  " << endl; 
					retval = -1;				
				}			
			}
			if(retval == -1)
				break;	
		}
		inpstrm.close(); /* Closing the input file */		
	}
	if(retval == -1)
	{
		KObj->NUM_NODES = -1;
		KObj->NUM_EDGES = -1;
	}
	else		
	{
		KObj->NUM_NODES = nodes_count;
		KObj->NUM_EDGES = edges_count;
		
		cout << endl;
		cout << "Total Number of Vertices " << KObj->NUM_NODES << endl;
		cout << "Total Number of Edges " << KObj->NUM_EDGES << endl;			 	
	}
}
/*********************************************************************************************************
Function Name            : VerifyEdges
Inputs                   : (1) Reference to KRUSKAL Object					
			   (2) Edge Vertex1 name					
			   (3) Edge Vertex2 name					
		
Outputs                  : -1 In case of any error occurrs
                            0 In case edge vertices are proper
Description              :  This function validates the graph edges endpoints names
*********************************************************************************************************/
int VerifyEdges(void *KObj1, string node1,string node2, int nodes_count)
{
	KRUSKAL		*KObj;
	int		retval = 0, iter = 0, found = 0;
		
	KObj = (KRUSKAL *)KObj1;
		
	for( iter = 0; iter < nodes_count; iter++)
	{
	
		//Comparing Edge Endpoint with Nodes 
		if(KObj->Graph_Nodes_List[iter].name.compare(node1) == 0)
		{			
			found++;
		}	
		if(KObj->Graph_Nodes_List[iter].name.compare(node2) == 0)
		{			
			found++;
		}			
			
	} 	 
	if(found != 2)
		retval = -1;
	return retval;	
}


/*********************************************************************************************************
Function Name            : ValidateFile
Inputs                   : (1) Reference to file to be validated					

Outputs                  : -1 In case of any error occurrs
                            0 In case of all items in the file are proper
Description              :  This function validates the file consisting of a graph nodes, edges information
*********************************************************************************************************/

int ValidateFile(char *inpfile)
{

	int		retval = 0, count = 0, line_num = 1, temp;
	ifstream	inpstrm ;	
	char		buff1[1025],buff[100],ch;
	stringstream 	sis;	
	string		str;


	inpstrm.open(inpfile, ios::in);	// Opening Input file 

	if(!inpstrm){		
		cout << "Exiting...." << endl;
		retval = -1;
	}
	else
	{			
		while(inpstrm)		
		{		
			std::fill(buff1, buff1 + 1024, ' ');	//Filling entire buffer with blank space
			inpstrm.getline(buff1,1024, '\n');	// Reading Input file line wise			
			if(inpstrm)
			{	
												
				if((int)buff1[0] == 0) //For handling blank lines
				{					
					retval = ValidateInput(buff1, line_num);
					if(retval == -1)
					{		
						cout << "Invalid Entry in the input.gv at line num " << line_num << endl;					
						break;
					}
				}	 				
				sis << buff1;					
				while(getline(sis,str,'\n'))
				{					
					strncpy(buff, str.c_str(), sizeof(buff));
					retval = ValidateInput(buff, line_num); // Validating items read from Input file 					
					if(retval == -1)
					{ 	
						cout << "Invalid Entry in the input.gv at line num " << line_num << endl;					
						break;	
					}
				}
				sis.clear();
			}
			else
			{
				if(inpstrm.eof())
				{
					//Reached end of the file
				}
				else
				{
					cout << "Failed to read data from file " << inpfile << "inside validate_file " << endl; 
					retval = -1;				
				}
			}	
			if(retval == -1)
				break;
			line_num++;
		}
		inpstrm.close(); // Closing the input file 
	}	
	return retval;
}

/*********************************************************************************************************
Function Name            : ValidateInput 
Inputs                   : (1) Reference to input item	
			   (2) Line NUmber
							
Outputs                  : -1 In case of any error occurrs
                            0 In case of valid item
Description              :  This function validates the token read by ValidateFile to be a valid Graph information
*********************************************************************************************************/
int ValidateInput(char *input, int line_num)
{

		int		retval =0, iter =0, iter1 = 0, iter3 =0;
	static 	int		nodes_start = 0, edges_start = 0, last_line = 0;
		int		nodes_line_num = 0, edges_line_num = 0;
		stringstream	sis,sis1;
		string		str,str1;	
		char		buff[50],buff1[50];
		
	//Verifying if blank space is received
	if(strlen(input) == 0)			//No line of Input File must be blank
	{
		retval = -1;
	} 	
	else
	{
		if(line_num == 1) 		//Line 1 must be "graph G {"
		{		
			if(strcmp(input, "graph G {") != 0 )
			{
				retval = -1;		
			}			
		}	
		else if(line_num == 2) 		//Line 2 must be "// nodes"
		{		
			if(strcmp(input, "// nodes") != 0 )
			{
				retval = -1;		
			}
			else			//Nodes information starts from next line
			{				
				nodes_start = 1;
				nodes_line_num = line_num;			
 			}	
		}	
		else if(strstr(input,"edges"))	//Edges information starts from next line
		{					
			edges_line_num = line_num;		
			nodes_start = 0;
			edges_start = 1;			
		}	
		else if(strstr(input,"}"))	//Last Line
		{
			if(last_line == 0)
			{	
				nodes_start = 0;
				edges_start = 0;	
				last_line = 1;	
			}
			else			//Invalid End of the file
			{
				cout << "Invalid End of the file " << endl;
				retval = -1;
			}
		}
		else if(nodes_start == 1)	//Verifiying Node Line Structure
		{			
			for(iter = 0; iter < strlen(input) - 1 ; iter++)
			{
				if(isalnum(input[iter]) == 0)	//Only Alphanumeric characters
				{
					cout << "Not a valid node name "<< endl;
					retval = -1;
					break;
				} 
			}
			if(input[strlen(input) - 1] != ';') 	//Must End with semicolon
			{
				cout << "Not a valid node line " << endl;
				retval = -1;			
			}			
		}
		else if(edges_start == 1)	//Verifiying Edge Line Structure
		{		
			sis << input;	
			iter = 0;						
			while(getline(sis,str,' '))
			{	
				strncpy(buff, str.c_str(), sizeof(buff));			
				if(iter == 0)	//Edge 1st Vertex
				{	
					//Edge Endpoint1 extracted endl;											
					for(iter1 = 0; iter1 < strlen(buff) ; iter1++)
					{
						if(isalnum(buff[iter1]) == 0) //Only Alphanumeric characters
						{
							cout << "Not a valid edge endpoint "<< endl;							
							retval = -1;
							break;
						} 
					}
					if(retval == -1)
					break;	
				}			
				else if(iter == 1)	//Edge divider	
				{
					// Edge Divider extracted 
	
					if(strlen(buff) != 2)
					{
						cout << "Not a valid edge divider"<< endl;
						retval = -1;
						break;
					}
					else
					{						
						for(iter1 = 0; iter1 < strlen(buff) ; iter1++)
						{
							if(buff[iter1] != '-') //Only -- is allowed
							{
								cout << "Not a valid edge divider"<< endl;								
								retval = -1;
								break;
							} 
						}
					}
					if(retval == -1)
					break;
				}
				else if(iter == 2)	//Edge 2nd Vertex
				{
					//Edge Endpoint2 extracted

					for(iter1 = 0; iter1 < strlen(buff) ; iter1++)
					{
						if(isalnum(buff[iter1]) == 0) //Only Alphanuemeric
						{
							cout << "Not a valid edge endpoint"<< endl;
							retval = -1;
							break;
						} 
					}	
					if(retval == -1)
					break;
				}
				else if(iter == 3)	//Edge Attributes Structure	
				{
					sis1 << buff;	
					iter3 = 0;						
					while(getline(sis1,str1,'"')) //  " delimiter 
					{		
						strncpy(buff1, str1.c_str(), sizeof(buff1));
						if(iter3 == 0)	//Edge Attribute part1
						{
							if(strcmp(buff1,"[label=") != 0)
							{
								cout << "Not a valid edge label attribute"<< endl;
								retval = -1;
								break;

							}	
						}
						else if(iter3 == 1) 	//Edge Attribute part2 - weight
						{
							for(iter1 = 0; iter1 < strlen(buff1) ; iter1++)
							{
								if(isdigit(buff1[iter1]) == 0) //Only Digit
								{
									cout << "Not a valid edge weight"<< endl;
									retval = -1;
									break;
								}	 
							}
						}
						else if(iter3 == 2)	//Edge Attribute part3
						{
							if(strcmp(buff1,"];") != 0)
							{
								cout << "Not a valid edge label attribute"<< endl;	
								retval = -1;
								break;

							}
						}
						else			//Invalid Edge Attribute
						{
							cout << "Invalid Edge Label Attribute " << endl;
							retval  = -1;
							break;
						}
						iter3++;
						if(retval == -1)
						{	 	
							break;	
						}
					}
					sis1.clear();
				}
				else 				//Invalid Entry in input file
				{
					cout << "Inavlid Edge Line " << endl;
					retval = -1;
					break;
				}
				iter++;						
				if(retval == -1)
				{ 	
					break;	
				}
			}
			sis.clear();						
		}
		else						//Invalid End of the file
		{
			if(last_line == 1)
			{
				cout << "Invalid end of the file " << endl;
				retval = -1;
			}
		}	
	}	
				
	return retval;

}
/*********************************************************************************************************
Function Name            : WriteOutput
Inputs                   : (1) Reference to output file			   
			   (2) Reference to KRUSKAL class Object		 
Outputs                  : -1 In case of any error occurrs
                            0 In case of sucessful write
Description              :  This function writes Graph along with MST information to the output file
*********************************************************************************************************/
int WriteOutput(char *outputfile, void *KObj1)
{

	int 		retval = 0,mst_edge = 0, no_chars = 0, iter = 0;
	KRUSKAL		*KObj;
	ofstream 	optstrm;
	char		buff[100];
	size_t 		pos=-1;
	string		tempstr;		
	stringstream	ss;

	KObj = (KRUSKAL *)KObj1;	
	optstrm.open(outputfile, ios::out | ios::trunc); // Opening outputfile in write Mode//

	if(!optstrm)
	{
		cout << "Failed to open File " << outputfile << endl;		
		retval = -1;
	}
	else
	{			
		//writing Graph Elements to the output file		
		strcpy(buff,"graph G {\n");
		no_chars = strlen(buff);	
		buff[no_chars] = '\0';
		if(optstrm.write(buff,no_chars))
		{
			strcpy(buff,"// nodes\n");
			no_chars = strlen(buff);	
			buff[no_chars] = '\0';
			if(optstrm.write(buff,no_chars))
			{				
				for(iter = 0; iter < KObj->NUM_NODES; iter++)//Writing Nodes
				{
					tempstr = KObj->Graph_Nodes_List[iter].name;
					strcpy(buff,tempstr.c_str());
					strcat(buff,";\n");	
					no_chars = strlen(buff);
					buff[no_chars] = '\0';
					if(!optstrm.write(buff,no_chars))
					{
						retval = -1;
						break;
					}					
				}
				if(retval != -1)
				{	
					strcpy(buff,"// edges\n");
					no_chars = strlen(buff);	
					buff[no_chars] = '\0';
					if(optstrm.write(buff,no_chars))
					{					
						for(iter = 0; iter < KObj->NUM_EDGES; iter++)//Writing Edges
						{
							mst_edge = LookMst(KObj, KObj->Graph_Edges_List[iter].u.name,KObj->Graph_Edges_List[iter].v.name);	//Looking in MST Edges List
							tempstr = KObj->Graph_Edges_List[iter].u.name;
							strcpy(buff,tempstr.c_str());
							strcat(buff," ");					
							strcat(buff,"--");
							strcat(buff," ");
							tempstr = KObj->Graph_Edges_List[iter].v.name;
							strcat(buff,tempstr.c_str());				
							strcat(buff," ");
							strcat(buff,"[label=\"");	
							ss << KObj->Graph_Edges_List[iter].weight;
							tempstr = ss.str();
							ss.clear();
							ss.str("");
							strcat(buff,tempstr.c_str());
							if(mst_edge == 1)//For MST Edge
							{
								strcat(buff,"\",color=blue]");
							
							}
							else		//For NON MST Edge
							{
								strcat(buff,"\",style=dotted]");
							}
							strcat(buff,";\n");	
							no_chars = strlen(buff);
							buff[no_chars] = '\0';
							if(!optstrm.write(buff,no_chars))
							{
								retval = -1;
								break;
							}
						}
					}
					else
					{
						retval = -1;
					}
				}
				if(retval != -1)
				{
					strcpy(buff,"}\n");
					no_chars = strlen(buff);	
					buff[no_chars] = '\0';
					if(!optstrm.write(buff,no_chars))
					{
						retval  = -1;
					}			
				}					
			}
			else
			{
				retval = -1;
			}	
		}
		else
		{
			retval = -1;
		}
		optstrm.close();	// Closing output file 							
	}	
	return retval;	
}
/*********************************************************************************************************
Function Name            : LookMst
Inputs                   : (1) Reference to KRUSKAL Class Object
			   (2) Edge Endpoint 1
			   (3) Edge Endpoint 2
	   
Outputs                  :  1 If the edge is MST Edge
                            0 otherwise
Description              :  This function Verifies wether a given Edge is MST Edge or not
*********************************************************************************************************/
int LookMst(void *KObj1 , string node1, string node2)
{
	int 		retval, iter = 0, found = 0;	
	KRUSKAL 	*KObj;


	KObj = (KRUSKAL *)KObj1;
	for(iter = 0; iter < KObj->NUM_MST_EDGES; iter++)//Look in MST Edges List
	{
		if((KObj->MST_Edges_List[iter].u.name.compare(node1) == 0) &&  (KObj->MST_Edges_List[iter].v.name.compare(node2) == 0))
		{
			found = 1;
			break;
		}	
	}	 		
	return found;
}
	

