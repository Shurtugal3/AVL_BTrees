#include "pch.h"
#include "AVL.h"


AVL::AVL()
{
}


//private methods  
void AVL::_updateBFs(AVL_Node* in_node)
{
	//update BFs using traverse idea 

	bool complete = false;
	AVL_Node* correctionCenter = nullptr;

	do
	{
		//start at inserted node and work up to root to calculate new BFs
		in_node->BF = _calculateBalanceFactor(in_node);
		//numOfBFChanges++;

		if ((in_node->BF == 2) || (in_node->BF == -2))
		{
			//this is node where rotation needs to occur
			if (!correctionCenter) correctionCenter = in_node;
		}

		if (in_node == rootNode) complete = true;
		else in_node = in_node->parent;

	} while (complete == false);

	if (correctionCenter)
	{
		_rotationHandler(correctionCenter);
	}
}

int AVL::_calculateBalanceFactor(AVL_Node* tippingNode)
{
	int rightHeight, leftHeight;
	if (tippingNode->rightChild != 0)
	{
		rightHeight = (_getNodeHeight(tippingNode->rightChild) + 1);
	}
	else rightHeight = 0;

	if (tippingNode->leftChild != 0)
	{
		leftHeight = (_getNodeHeight(tippingNode->leftChild) + 1);
	}
	else leftHeight = 0;

	_getNodeHeight(tippingNode);
	return (leftHeight - rightHeight);
}

int AVL::_getNodeHeight(AVL_Node* focusNode)
{
	int ret1, ret2;
	//calculate the height of the node 
	if ((focusNode->rightChild == 0) && (focusNode->leftChild == 0))
	{
		return 0;
	}
	else
	{
		if (focusNode->rightChild != 0)
		{
			ret1 = _getNodeHeight(focusNode->rightChild);
		}
		else ret1 = 0;

		if (focusNode->leftChild != 0)
		{
			ret2 = _getNodeHeight(focusNode->leftChild);
		}
		else ret2 = 0;

		if (ret1 > ret2)
		{
			return (ret1 + 1);
		}
		else
		{
			return (ret2 + 1);
		}
	}
}

void AVL::_rotationHandler(AVL_Node* correctionCenter)
{
	//correctionCenter will be the lowest node with a BF that is out of spec and requires rotation to correct 

	//insertionSide: 
	//1 - left 
	//2 - right

	int temp = nodeStorage_index - 1;
	AVL_Node *insertedNode = &nodeStorage[temp];
	AVL_Node *grandparentNode = nullptr;
	AVL_Node *loopNode = nullptr;

	char tempContainer[50];
	int direction1 = 0;
	int direction2 = 0;

	if (correctionCenter->BF >= 2)
	{
		//left subtree too big 
		if (correctionCenter->leftChild->BF > 0)
		{
			//inserted node was in the left subtree of the left node LL
			LL_rotate(correctionCenter);
		}
		else
		{
			//LR 
			LR_rotate(correctionCenter);
		}
	}
	else
	{
		if (correctionCenter->rightChild->BF > 0)
		{
			//left subtree of right node RL 
			RL_rotate(correctionCenter);
		}
		else
		{
			//RR rotate, should be 
			RR_rotate(correctionCenter);
		}
	}
}