#include "pointer_list.h"
#include "key_value.h"
#include "node_list.h"
#include <stdio.h>
#include <stdlib.h>
void PListTest();
void KeyValueTest();
void NodeListTest();

int main(){
	PListTest();
	KeyValueTest();
	NodeListTest();
	return 0;
}

void PListTest(){
	char *val;
	PList *list = InitPList();
	AddPList(list, "HELLO");
	AddPList(list, "WORLD");
	AddPList(list, "WORLD2");
	forlist(val, list){
		printf("%s\n", val);
	}
	val = GetValueIndexPList(list, 1);
	printf("%s\n", val);
	DeletePList(list, 1);
	val = GetValueIndexPList(list, 1);
	printf("%s\n", val);
	FinalPList(list);
	
}

void KeyValueTest(){
	void *val;
	KVList *list = InitKVList();
	SetKVList(list, "KEY1", "VALUE1");
	SetKVList(list, "KEY2", "VALUE2");
	val = GetKVList(list, "KEY1");
	printf("[%s]\n", val);
	val = GetKVList(list, "KEY2");
	printf("[%s]\n", val);
	SetKVList(list, "KEY1", "VALUE1_1");
	val = GetKVList(list, "KEY1");
	printf("[%s]\n", val);
	FinalKVList(list);
}

void NodeListTest(){
	int i = 0;
	char *name = NULL;
	char *value = NULL;
	NList *list = InitNList("TEST_ROOT");
	for(i = 0; i < 5; i++){
		int j = 0;
		NodeValue *parent = NULL;
		name = (char*)malloc(2);
		sprintf(name, "%d", i);
		parent = CreateChildNodeValue(list->root, name);
		for(j = 0; j < 5; j++){
			int k = 0;
			NodeValue *child = NULL;
			name = (char*)malloc(4);
			sprintf(name, "%d-%d", i, j);
			child = CreateChildNodeValue(parent, name);
			for(k = 0; k < 5; k++){
				name = (char*)malloc(6);
				sprintf(name, "%d-%d-%d", i, j, k);
				CreateChildNodeValue(child, name);
			}
		}
	}		
	while(value = (char*)DepthFirstSearchNList(list)){
		printf("%s\n", value);
		if(strcmp(value, "TEST_ROOT") == 0){ continue; }
		free(value);
	}
	FinalNList(list);
}

