#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

int ceilres(int a){
	if (a%2==0){
		return a/2;
	}
	else{
		return (a/2)+1;
	}
}

LeafNode* LeafNode::Sort(){
	for(int j=count-1; j>=1; j--){
		if(values[j-1]>values[j]){
			int temp = values[j-1];
			values[j-1] = values[j];
			values[j] = temp;
		}
	}
}

int LeafNode::getMaximum()const
{
	if(count>0)
		return values[count-1];
	else
		return 0;
}

int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()

LeafNode* LeafNode::insert(int value)
{
	//cout << "LeafNode left sibling = " << LeafNode::getLeftSibling()->getCount() << endl;
	if(LeafNode::getCount() < leafSize){
		values[count] = value;												// does original values change?
		count++;																// does the original value of count inside the class change?
		LeafNode::Sort();
		return NULL;
	}
	else if(LeafNode::getCount() == leafSize){
		if(LeafNode::getLeftSibling()!=NULL){
		  //cout << "Current key/min = " << LeafNode::getMinimum() << endl;
		  //cout << "Left sibling count = "<< LeafNode::getLeftSibling()->getCount() << endl;
			if((LeafNode::getLeftSibling()->getCount())<leafSize){
				if(value>LeafNode::getMinimum()){
					int tempmin = LeafNode::getMinimum();
					for(int z = count-1; z>0; z--){
						values[z-1] = values[z];
					}
					values[count-1] = value;
					LeafNode::Sort();
					LeafNode::getLeftSibling()->insert(tempmin);
				}
				else
					LeafNode::getLeftSibling()->insert(value);
				return NULL;
			}
		}
		if(LeafNode::getRightSibling()!=NULL){
			if((LeafNode::getRightSibling()->getCount())<leafSize){
				if(value>LeafNode::getMaximum())
					LeafNode::getRightSibling()->insert(value);
				else{
					int tempmax = LeafNode::getMaximum();
					values[count-1] = value;
					LeafNode::Sort();
					LeafNode::getRightSibling()->insert(tempmax);
				}
				return NULL;
			}
		}
		
		LeafNode* newleaf = new LeafNode(leafSize,parent,this,rightSibling);
		if(LeafNode::getRightSibling()!=NULL){
			LeafNode::getRightSibling()->setLeftSibling(newleaf);
		}
		//LeafNode::setRightSibling(newleaf);	
		newleaf->count = 0;
		newleaf->leafSize = leafSize;
		//newleaf->setLeftSibling(this);
		for(int i=0; i<=ceilres(leafSize); i++){
			if(LeafNode::values[count-1]>value){
				newleaf->values[i] = LeafNode::getMaximum();
				count--;
				newleaf->count++;
			}
			else{
				newleaf->values[i] = value;
				newleaf->count++;
				value = 0;
			}
			newleaf->Sort();
			if((value!=0)&&(i==ceilres(leafSize))){
				values[count] = value;
				LeafNode::count++;
				LeafNode::Sort();
			}
		}	
		LeafNode::setRightSibling(newleaf);
		newleaf->setLeftSibling(this);
		return newleaf;
	}
	
	
  /*
	  if(LeafNode::getRightSibling()!=NULL){
		  if((LeafNode::getRightSibling()->getCount())<leafSize){
			  if(value>LeafNode::getMaximum())
				  LeafNode::getRightSibling()->insert(value);
			  else{
				  int tempmax = LeafNode::getMaximum();
				  values[count-1] = value;
				  LeafNode::Sort();
				  LeafNode::getRightSibling()->insert(tempmax);
			  }
			  return NULL;
		  }
	  }
	*/
	/*
	LeafNode* newleaf = new LeafNode(leafSize,parent,this,rightSibling);
	if(LeafNode::getRightSibling()!=NULL){
		LeafNode::getRightSibling()->setLeftSibling(newleaf);
	}
	//LeafNode::setRightSibling(newleaf);	
	newleaf->count = 0;
	newleaf->leafSize = leafSize;
	//newleaf->setLeftSibling(this);
	for(int i=0; i<=ceilres(leafSize); i++){
		if(LeafNode::values[count-1]>value){
			newleaf->values[i] = LeafNode::getMaximum();
			count--;
			newleaf->count++;
		}
		else{
			newleaf->values[i] = value;
			newleaf->count++;
			value = 0;
		}
		newleaf->Sort();
	}
	
	if(value!=0){
		values[count] = value;
		LeafNode::count++;
		LeafNode::Sort();
	}
	
	LeafNode::setRightSibling(newleaf);
	newleaf->setLeftSibling(this);
	return newleaf;
	*/
  
  //return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


