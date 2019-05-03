#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()

int ceiling(int a){
	if (a%2==0){
		return a/2;
	}
	else{
		return (a/2)+1;
	}
}

InternalNode* InternalNode::Sort(){
	for(int k = count-1; k>=1; k--){
		if(InternalNode::keys[k]<InternalNode::keys[k-1]){
			BTreeNode* tempnode = InternalNode::children[k-1];
			InternalNode::children[k-1] = InternalNode::children[k];
			InternalNode::children[k] = tempnode;
			InternalNode::keys[k] = (InternalNode::children[k])->getMinimum();
			InternalNode::keys[k-1] = (InternalNode::children[k-1])->getMinimum();
		}
	}
}

InternalNode* InternalNode::updatekeys(){
	for(int k = count-1; k>=0; k--){
		InternalNode::keys[k] = (InternalNode::children[k])->getMinimum();
	}
}

int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()

InternalNode* InternalNode::insert(int value)	// when inserting value
{	
	BTreeNode* newvar;
	for(int i=count-1; i>=0; i--){
		if(value>InternalNode::keys[i]){
			newvar = (InternalNode::children[i])->insert(value);	// increased count by 1
			if(newvar!=NULL){
			  if(count<internalSize){
				  // leaf split
				  if(count-1!=i){
					  //right middle split
					  for(int j = count-1; j>=i ; j--){
						  InternalNode::children[j+1] = InternalNode::children[j];
						  InternalNode::keys[j+1] = (InternalNode::children[j+1])->getMinimum();
					  }
					  InternalNode::children[i] = newvar;
					  InternalNode::keys[i] = newvar->getMinimum();
					  (InternalNode::children[i])->setParent(this);
					  if(i>0)
						(InternalNode::children[i])->setLeftSibling(InternalNode::children[i-1]);
					  (InternalNode::children[i])->setRightSibling(InternalNode::children[i+1]);
					  (InternalNode::children[i+1])->setLeftSibling(InternalNode::children[i]);
					  if(i>0)
						(InternalNode::children[i-1])->setRightSibling(InternalNode::children[i]);
					  InternalNode::Sort();
				  }
				  else{
					  //right edge split
					  InternalNode::children[i+1] = newvar;
					  InternalNode::keys[i+1] = newvar->getMinimum();
					  
					  (InternalNode::children[i+1])->setLeftSibling(InternalNode::children[i]);
					  (InternalNode::children[i])->setRightSibling(InternalNode::children[i+1]);
					  (InternalNode::children[i+1])->setParent(this);
					  InternalNode::Sort();
				  }
				  InternalNode::count++;
			  }
			  else{
				  
				  // internal node passing
				  if(InternalNode::getLeftSibling()!=NULL){
					  /*
					  if(InternalNode::getLeftSibling()->getCount()<internalSize){
						  //InternalNode::getLeftSibling()->insert(InternalNode::children[0]);
						  for(int B = count-1; B>0; B--){
							  InternalNode::children[B-1] = InternalNode::children[B];
						  }
						  InternalNode::Sort();
						  InternalNode::children[count-1] = newvar;
						  InternalNode::updatekeys();
						  (InternalNode::children[count-1])->setParent(this);
						  return NULL;
					  }*/
					  return NULL;
				  }
				  if(InternalNode::getRightSibling()!=NULL){
					  /*
					  if(InternalNode::getRightSibling()->getCount()<internalSize){
						  //(InternalNode::getRightSibling())->insert(newvar);
						  return NULL;
					  }*/
					  return NULL;
					  
				  }
				  InternalNode* newnode = new InternalNode(internalSize,leafSize,parent,this,rightSibling);
				  newnode->count = 1;
				  newnode->children[0] = newvar;
				  newnode->leafSize = leafSize;
				  newnode->keys[0] = newvar->getMinimum();
				  if(InternalNode::getRightSibling()!=NULL){
					  InternalNode::getRightSibling()->setLeftSibling(newnode);
				  }
				  
				  for(int H=0; H<ceiling(internalSize); H++){
					  newnode->children[newnode->count] = InternalNode::children[count-1];
					  newnode->keys[newnode->count] = InternalNode::keys[count-1];
					  newnode->count++;
					  InternalNode::count--;
				  }
				  newnode->Sort();
				  newnode->updatekeys();
				  
				  return newnode;
				  
			  }
			}
			InternalNode::Sort();
			InternalNode::updatekeys();
			return NULL;
		}
	}
	newvar = (InternalNode::children[0])->insert(value);
	if(newvar!=NULL){
		if(count<internalSize){
			for(int index=count-1; index>=1; index--){
				InternalNode::children[index+1] = InternalNode::children[index];
				InternalNode::keys[index+1] = (InternalNode::children[index+1])->getMinimum();
			}
			InternalNode::children[1] = newvar;
			InternalNode::keys[1] = newvar->getMinimum();
			(InternalNode::children[0])->setRightSibling(InternalNode::children[1]);
			(InternalNode::children[1])->setLeftSibling(InternalNode::children[0]);
			(InternalNode::children[1])->setRightSibling(InternalNode::children[2]);
			(InternalNode::children[2])->setLeftSibling(InternalNode::children[1]);
			(InternalNode::children[1])->setParent(this);
			InternalNode::count++;
			InternalNode::Sort();
			InternalNode::updatekeys();
			return NULL;
		}
		else{
			return NULL;
		}
	}
	else{
		InternalNode::keys[0] = (InternalNode::children[0])->getMinimum();
		InternalNode::keys[1] = (InternalNode::children[1])->getMinimum();
		return NULL;
	}
	InternalNode::updatekeys();
	return NULL;
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)	// called frm BTree.cpp; called only once after first split
{ // Node must be the root, and node1
  InternalNode::keys[0] = oldRoot->getMinimum();
  InternalNode::keys[1] = node2->getMinimum();
  InternalNode::children[0] = oldRoot;
  InternalNode::children[1] = node2;
  oldRoot->setParent(this);
  node2->setParent(this);
  (InternalNode::children[0])->setLeftSibling(NULL);
  (InternalNode::children[1])->setLeftSibling(InternalNode::children[0]);
  (InternalNode::children[0])->setRightSibling(InternalNode::children[1]);
  (InternalNode::children[1])->setRightSibling(NULL);
  
  InternalNode::count = 2;
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling; for splitting between internal nodes
{
	
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


