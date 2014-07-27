#include "pointer_list.h"
#include "key_value.h"
#include <stdio.h>

void KeyValueTest();
int main(){
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
	KeyValueTest();
	return 0;
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

