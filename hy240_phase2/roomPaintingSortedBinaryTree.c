


#include "roomPaintingSortedBinaryTree.h"
#include <stdlib.h>
#include <stdio.h>


void roomPaintingTreeInsert (int roomPaintingId, WORK** roomPaintingList){
	WORK * tmp = *roomPaintingList;
	WORK * newRoomPainting = NULL;
	WORK * parent = NULL;

	/*ama to dentro einai keno*/
	if(tmp == NULL){
		newRoomPainting = malloc (sizeof(WORK));
		newRoomPainting->paintingId = roomPaintingId;
		newRoomPainting->lc = NULL;
		newRoomPainting->rc = NULL;
		newRoomPainting->numOfChNodes = 0;
		*roomPaintingList = newRoomPainting;
		return;
	}

	/*uparxei hdh*/
	if (roomPaintingTreeLookUp(roomPaintingId,*roomPaintingList) != NULL) return;


	/*bres tin katallhlh thesh gia na mpei o kainoutgios kombos */
	while (tmp != NULL ){
		
		//if (tmp->paintingId == roomPaintingId) return;

		parent = tmp;
		
		if (tmp->paintingId > roomPaintingId) {
			(tmp->numOfChNodes)++;
			tmp = tmp->lc;
		}
		else 
			tmp = tmp->rc;
	
	}

	/*desmeush xwrou gia ton kainourgio kombo */

		newRoomPainting = malloc (sizeof(WORK));
		newRoomPainting->paintingId = roomPaintingId;
		newRoomPainting->lc = NULL;
		newRoomPainting->rc = NULL;
		newRoomPainting->numOfChNodes = 0;

	/* ftiaxe tis sundeseis tou kainourgiou komvou */
		if (parent != NULL && tmp == NULL){
			if (roomPaintingId <parent->paintingId){
				parent->lc = newRoomPainting;
				newRoomPainting->lc = NULL;
				newRoomPainting->rc = NULL;
			}
			else{
				parent->rc = newRoomPainting;
				newRoomPainting->lc = NULL;
				newRoomPainting->rc = NULL;
		}
	}
}


WORK * roomPaintingTreeLookUp(int roomPaintingId, WORK * roomPaintingList){
	WORK * tmp = roomPaintingList;
	while (tmp != NULL){
		/* ama breis to stoixeio epestrepse to */
		if (roomPaintingId == tmp->paintingId){
			return tmp;
		}	
		
		/*ama einai megalutero apo to roomId tou tmp, pigaine sto de3i paidi tou tmp diaforetika sto aristero */
		if (roomPaintingId > tmp->paintingId)
			tmp = tmp->rc;
		else
			tmp = tmp->lc;
	}

	/* ama de to breis epestrepse Null */
	return NULL;

}

static void visit_print(WORK * roomPaintingList){
	WORK * tmp = roomPaintingList;
	printf("%d %d %p %p\n", tmp->paintingId, tmp->numOfChNodes, tmp->lc,tmp->rc);
}

void roomPaintingTreePrint(WORK * roomPaintingList){
	if (roomPaintingList == NULL) return;
	roomPaintingTreePrint(roomPaintingList->lc);
	visit_print(roomPaintingList);
	roomPaintingTreePrint(roomPaintingList->rc);
}

static WORK * minValue(WORK* node, WORK ** father) {
  WORK * current = node;

  /* loop down to find the leftmost leaf */
  while (current->lc != NULL) {
		*father = current;
		current = current->lc;
  }
  return current;
}

static WORK * inOrderFindNext(WORK * node, WORK * root, WORK ** father){
	WORK * succ = NULL;
	*father = node;
	if( node->rc != NULL )
        return minValue(node->rc, father);
 
 
    while (root != NULL){
		
		if (node->paintingId < root->paintingId){
            succ = root;
            root = root->lc;
        }
		else if (node->paintingId > root->paintingId)
            root = root->rc;
        else
           break;
    }
 
    return succ;
	
}

void roomPaintingTreeDelete (int roomPaintingId, WORK ** roomPaintingList){

	WORK * current = NULL, *parent = NULL, *del_node = NULL, *child = NULL;
	WORK * root = *roomPaintingList;
	current = * roomPaintingList;

	if (roomPaintingTreeLookUp(roomPaintingId,*roomPaintingList) == NULL) return;


	while (current != NULL){

		if (current->paintingId == roomPaintingId){
			del_node = current;

			if (del_node->lc == NULL && del_node->rc == NULL){
				/* o kombos den exei paidia */

				if (parent == NULL){
					*roomPaintingList = NULL;
					del_node = NULL;
					return;
				}
				if (parent->lc == del_node)
					/*an o kombos einai aristero paidi tou patera tou kane to NULL */
					parent->lc = NULL;
				else
					parent->rc = NULL;
				
				/* diegrapse ton */
				free (del_node);
				return;
			}
			else if ((del_node->lc == NULL) || (del_node->rc == NULL)){
				/* o kombos exei ena paidi*/
				

				/*apothikeuoume se mia metablhth to paidi tou kombou*/
				if (del_node->lc != NULL)
					child = del_node->lc;
				else
					child = del_node->rc;

				/*ama o kombos pou theloume na diagrapsoume einai aristero paidi tou patera tou tote bale sth thesh tou to paidi tou*/
				if (parent == NULL){
					//free(del_node); /*apodesmeuse th mnhmh tou kombou */
					del_node = child;
					*roomPaintingList = child;
					
					return;
				}
						
				else if (parent->lc == del_node)
					parent->lc = child;
				else 
					parent->rc = child;

				
				free(del_node); /*apodesmeuse th mnhmh tou kombou */
				return;

			}
			else{
				/*o kombos exei 2 paidia*/
				
				/*bres ton epomeno kombo sthn endodiatetagmenh*/
				WORK * temp_father = NULL; /* o pateras tou epomenou sthn endodiatetagmenh*/
				WORK * next = inOrderFindNext(del_node,root, &temp_father);

				WORK * child = NULL;
			
					/*tha exei mono ena paidi to else, diaforetika epomenos ths endodiatetagmenhs tha htan to most lc */
					if(next->lc != NULL)
						child = next->lc;
					else
						child = next->rc;

				
				

				/*antegrapse ta stoixeia tou next sto kombo pou theloume na svhsoume */
				del_node->paintingId =  next->paintingId;

				/*ftiaxe ton deikth tou patera tou epomenou sthn endodiatetagmenh */
				if (temp_father->lc == next)
					temp_father->lc = child;
				else
					temp_father->rc = child;

				if (temp_father->numOfChNodes !=0 && temp_father->paintingId!= next->paintingId)
					(temp_father->numOfChNodes)--;

				free(next);
				
				return;
			
	
			}

		}

		parent = current;
		if ( roomPaintingId < current->paintingId){
			if(current->numOfChNodes!=0) 
				(current->numOfChNodes)--;
			current = current->lc;
		}
		else
			current = current->rc;

	}
}

void TreePrint(WORK *roomPaintingList, void (*visit)(WORK *, void *, int), void *ptr, int m) { 
	if(roomPaintingList == NULL) 
		return; 
	TreePrint(roomPaintingList->lc, visit, ptr,m);
	visit(roomPaintingList, ptr, m);
	TreePrint(roomPaintingList->rc, visit, ptr,m);
}


int getLength(WORK * tree){
	int count = 0;

	if(tree != NULL) { 
		count = 1 + getLength(tree->lc) + getLength(tree->rc);
	}
	return count;
}

