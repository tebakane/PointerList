#ifndef _NODE_LIST_H_
#define _NODE_LIST_H_
#include "pointer_list.h"
#include "boolean.h"
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct _NList NList;
	typedef struct _NodeValue NodeValue;
	struct _NList{
		NodeValue *root; /* NodeValueのルートノード */
		NodeValue *now;
	};

	struct _NodeValue{
		NodeValue *parent;
		NodeValue *now;
		PListValue *now_list_value;
		PList *children;
		void *value;
		PList *route; /* RouteForNodeValueで */
	};

	NList *InitNList(void *root_value);
	void FinalNList(NList *list);
	NodeValue *CreateNodeValue(void *value);
	NodeValue *CreateChildNodeValue(NodeValue *node, void *value);
	void *DepthFirstSearchNList(NList *list);
	PList *RouteForNodeValue(NodeValue *node);
	void PrintNListTree(NList *list);
	void AddChildNodeValue(NodeValue *parent, NodeValue *child);
	int DepthForNodeValue(NodeValue *node);
	BOOL IsAncestorNodeValue(NodeValue *ancestor, NodeValue *base);
#ifdef __cplusplus
}
#endif
#endif /* _NODE_LIST_H_ */
