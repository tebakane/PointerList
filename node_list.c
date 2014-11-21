#include "node_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

NList *InitNList(void *root_value){
	NList *list = (NList*)malloc(sizeof(NList));
	if(!list){ return NULL; }
	memset(list, 0x00, sizeof(NList));
	list->root = (NodeValue*)malloc(sizeof(NodeValue));
	if(!list->root){ FinalNList(list); return NULL; }
	memset(list->root, 0x00, sizeof(NodeValue));
	list->root->value = root_value;
	return list;
}

/* Nodeの中身を削除する */
void DeleteAllNode(NodeValue *node){
	NodeValue *child_node;
	if(!node){ return; }
	if(node->children){
		PListValue *child_value;
		forlistvalue(child_value, node->children){ 
			child_node = (NodeValue*)child_value->value;
			DeleteAllNode(child_node); 
		}
		FinalPList(node->children);
	}
	if(node->route){ FinalPList(node->route); }
	free(node);
}

void FinalNList(NList *list){
	if(!list){ return; }
	DeleteAllNode(list->root);
	free(list);
}

/* 第一引数の子ノードを追加する。戻り値は追加された子ノード */
NodeValue *CreateChildNodeValue(NodeValue *node, void *value){
	NodeValue *child;
	if(!node->children){ 
		node->children = InitPList(sizeof(NodeValue)); 
		if(!node->children){ return NULL; }
	}
	child = CreateNodeValue(value);
	if(!child){ return NULL; }
	child->parent = node;
	AddPList(node->children, child);
	return child;
}

/* ノードを作成する。 */
NodeValue *CreateNodeValue(void *value){
	NodeValue *node = (NodeValue*)malloc(sizeof(NodeValue));
	if(!node){ return NULL; }
	memset(node, 0x00, sizeof(NodeValue));
	node->value = value;
	return node;
}

void AddChildNodeValue(NodeValue *parent, NodeValue *child){
	child->parent = parent;
	AddPList(parent->children, child);
}

/* リストの中からノードを削除する。 */
void DeleteNodeFromNList(NList *list, NodeValue *node){
	NodeValue *parent = node->parent;
	/* rootノードの削除の場合はrootを作り直す。 */
	if(list->root = node){
		list->root = (NodeValue*)malloc(sizeof(NodeValue));
		memset(list->root, 0x00, sizeof(NodeValue));
	}
	DeleteAllNode(node);
	if(parent){ parent->children = NULL; }
}

NodeValue *GetNextChildNode(NList *list){
	NodeValue *parent;
	if(!list->now){ return NULL; }
	parent = list->now->parent;
	if(!parent){ return NULL; }
	parent->now_list_value = parent->now_list_value->next;
	if(!parent->now_list_value){ return NULL; }
	list->now = parent->now_list_value->value;
	return list->now;
}

void InitDepthSearchNList(NList *list){
	list->now = NULL;
}
/* 深さ優先探索 */
void *DepthFirstSearchNList(NList *list){
	PList *children;
	/* list->nowがNULLの場合、はじまり */
	if(!list->now){
		list->now = list->root;
		return list->now->value;
	}
	children = list->now->children;
	if(children){
		/* 子ノードの最初を返す。 */
		list->now->now_list_value = children->first;
		list->now = (NodeValue*)children->first->value;
		if(children->first){ return list->now->value; }
	}
	/* 自分の次のノードを返す。 自分の次のノードは親に戻ってから探索 */
	while(list->now){
		NodeValue *next = GetNextChildNode(list);
		if(next){ list->now = next; break; }
		list->now = list->now->parent;
	}
	if(!list->now){ return NULL; }
	return list->now->value;
}

void InitBreadthSearchNList(NList *list){
	list->now = NULL;

}
/* 幅優先探索(開発中) */
void *BreadthFirstSearchNList(NList *list){
	return NULL;	
}


void CreateRouteNodeValue(NodeValue *node, PList *route){
	if(node->parent){ CreateRouteNodeValue(node->parent, route); }
	AddPList(route, node->value);
}

/* ルートを深さ0として深さnodeの深さを求める */
int DepthForNodeValue(NodeValue *node){
	if(node->parent){ return DepthForNodeValue(node->parent) + 1; }
	return 0;
}

/* 上から順番のルートを返す。失敗するとNULLを返す */
PList *RouteForNodeValue(NodeValue *node){
	if(node->route){ FinalPList(node->route); }
	node->route = InitPList();
	if(!node->route){ return NULL; }
	CreateRouteNodeValue(node, node->route);
	return node->route;
}

/* 確認用関数 */
void PrintNListTree(NList *list){
	char *value;
	InitDepthSearchNList(list);
	while((value = DepthFirstSearchNList(list))){
		int i = 0;
		int depth = DepthForNodeValue(list->now);
		for(i = 0; i < depth; i++){
			printf("    ");
		}
		if(depth != 0){ printf("∟"); }
		printf(" %s", value);
		printf("\n");
	}
}

/* ancestorが祖先かどうかを検証する。祖先の場合はTRUE, 違う場合はFALSE
 * baseとancestorが同じ場合はFALSE
*/
BOOL IsAncestorNodeValue(NodeValue *ancestor, NodeValue *base){
	if(!base->parent){ return FALSE; }
	if(ancestor == base->parent){ return TRUE; }
	return IsAncestorNodeValue(ancestor, base->parent);
}

