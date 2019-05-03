#include <iostream>
#include <fstream>
#include <istream>
#include <iomanip>
#include "BinaryTree.h"
#include "BinaryHeap.h"	

using namespace std;

int main(int argc, char** argv){
	// Declaring variables, classes, and arrays
	string input;
	int totalnumber = 0;
	int indices_index = 0;
	int indices[100];
	BinaryTree TreeArr[128];
	
	int totalcount = 0;
	
	// Initializing ASCII class array
	for(int I=0; I<128; I++){
		TreeArr[I].count = 0;
		TreeArr[I].tree = false;
		if(I==1)
			TreeArr[I].Letter = '\n';
		if(I>=32)
			TreeArr[I].Letter = char(I);
	}
	
	// Inserting characters from file into class array
	ifstream file(argv[1]);
	while(getline(file,input)){
		for(int i=0; i<input.length(); i++){
			if(input[i]==' '){
				TreeArr[32].count++;
				totalcount++;
				if(TreeArr[32].count==1){
					totalnumber++; 
					indices[indices_index++] = 32;
				}
			}
			else{
				TreeArr[input[i]].count++;
				totalcount++;
				if(TreeArr[input[i]].count==1){
					totalnumber++;
					indices[indices_index++] = input[i];
				}
			}
		}
		TreeArr[1].count++;
		totalcount++;
		if(TreeArr[1].count==1){
			totalnumber++; 
			indices[indices_index++] = 1;
		}
	}
	
	// Creating sorted and shorter list
	BinaryTree final_list[totalnumber];
	for(int J=0; J<totalnumber ; J++){
		final_list[J] = TreeArr[indices[J]];
		if(J>0){
			for(int K=J; K>0; K--){
				if(final_list[K].count<final_list[K-1].count){
					BinaryTree temp = final_list[K-1];
					final_list[K-1] = final_list[K];
					final_list[K] = temp;
				}
				else
					break;
			}
		}
	}
	// Declaring more variables
	BinaryTree treestack[100];
	int tree_storing_index = 0;		// variable for treestack for storing subtrees into treestack
	int tree_searchmin_index = 0;	// variable for treestack to search for the smallest subtree in treestack
	int list_searchmin_index = 0;	// variable for final_list to search for the smallest element in final_list
	
	while(true){
		if(tree_storing_index==0){
			BinaryTree newtree;
			newtree.count = final_list[0].count + final_list[1].count;
			newtree.Letter = 'T';
			newtree.tree = true;
			newtree.leftchild = &final_list[0];
			newtree.rightchild = &final_list[1];
			treestack[tree_storing_index] = newtree;
			tree_storing_index++;
			list_searchmin_index = 2;
		}
		else{
			BinaryTree newtree;
			int count = 0;
			// setting left subtree
			if(list_searchmin_index<totalnumber){
				if(final_list[list_searchmin_index].count<=treestack[tree_searchmin_index].count){
					count = count + final_list[list_searchmin_index].count;
					newtree.leftchild = &final_list[list_searchmin_index];
					list_searchmin_index++;
				}
				else{
					count = count + treestack[tree_searchmin_index].count;
					newtree.leftchild = &treestack[tree_searchmin_index];
					tree_searchmin_index++;
				}
			}
			else{
				count = count + treestack[tree_searchmin_index].count;
				newtree.leftchild = &treestack[tree_searchmin_index];
				tree_searchmin_index++;
			}
			
			// setting right subtree
			if(list_searchmin_index<totalnumber){
				if(tree_searchmin_index<tree_storing_index){
					if(final_list[list_searchmin_index].count<=treestack[tree_searchmin_index].count){
						count = count + final_list[list_searchmin_index].count;
						newtree.rightchild = &final_list[list_searchmin_index];
						list_searchmin_index++;
					}
					else{
						count = count + treestack[tree_searchmin_index].count;
						newtree.rightchild = &treestack[tree_searchmin_index];
						tree_searchmin_index++;
					}
				}
				else{
					count = count + final_list[list_searchmin_index].count;
					newtree.rightchild = &final_list[list_searchmin_index];
					list_searchmin_index++;
				}
			}
			else{
				count = count + treestack[tree_searchmin_index].count;
				newtree.rightchild = &treestack[tree_searchmin_index];
				tree_searchmin_index++;
			}
			newtree.tree = true;
			newtree.Letter = 'T';
			newtree.count = count;
			treestack[tree_storing_index] = newtree;
			tree_storing_index++;
		}
		if(treestack[tree_searchmin_index].count == totalcount)
			break;
	}
	
	// printing the tree
	treestack[tree_storing_index-1].printinorder();
	return 0; 
}
