#include "key_value.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _KeyValue{
	char *key;
	void *value;
};

struct _KVList{
	PList *list; /* KeyValue */
	PList *keys;
	PList *values;
	int center;
};

KeyValue *GetKeyValueWithKeyKVList(KVList *list, char *key);

KVList *InitKVList(){
	KVList *key_values = (KVList*)malloc(sizeof(KVList));
	if(!key_values){ return NULL; }
	memset(key_values, 0x00, sizeof(KVList));
	key_values->list = InitPList();
	key_values->keys = InitPList();
	key_values->values = InitPList();
	if(!key_values->list){ free(key_values); return NULL; }
	return key_values;
}

/* If key has already existed, value will be replaced */
void AddKVList(KVList *list, char *key, void *value){
	KeyValue *kv = NULL;
	size_t len = strlen(key);
	if(!key || len == 0){ return; }
	kv = GetKeyValueWithKeyKVList(list, key);
	if(kv == NULL){
		kv = (KeyValue*)malloc(sizeof(KeyValue));
		if(!kv){ return; }
		memset(kv, 0x00, sizeof(KeyValue));
		kv->key = (char*)malloc(len + 1);
		strcpy(kv->key, key);
		AddPList(list->list, kv);
	}
	kv->value = value;
}

/* key‚ª‘¶Ý‚µ‚È‚¢ê‡‚Í‚È‚É‚à‚µ‚È‚¢ */
void DeleteKVKist(KVList *list, char *key){
	KeyValue *kv;
	int index = 0;
	if(!key || strlen(key) == 0){ return; }
	forlist(kv, list->list){
		if(strcmp(kv->key, key) == 0){ 
			break; 
		}
		index++;
	}
	if(list->list->now == NULL){ return; }
	DeletePList(list->list, index);
	free(kv->key);
	free(kv);
}
void *GetValueKVList(KVList *list, char *key){
	KeyValue *kv = GetKeyValueWithKeyKVList(list, key);
	if(kv == NULL){ return NULL; }
	return kv->value;
}

PList *GetKeysKVList(KVList *list){
	KeyValue *kv;
	ClearPList(list->keys);
	forlist(kv, list->list){
		AddPList(list->keys, kv->key);
	}
	return list->keys;
}

PList *GetValuesKVList(KVList *list){
	KeyValue *kv;
	ClearPList(list->values);
	forlist(kv, list->list){
		AddPList(list->values, kv->value);
	}
	return list->values;
}

KeyValue *GetKeyValueWithKeyKVList(KVList *list, char *key){
	KeyValue *kv;
	if(!list || !key){ return NULL; }
	forlist(kv, list->list){
		if(strcmp(kv->key, key) != 0){ continue; }
		return kv;
	}
	return NULL;	
}

BOOL IsKeyExistsKVList(KVList *list, const char *key){
	KeyValue *kv;
	forlist(kv, list->list){
		if(strcmp(kv->key, key) == 0){ return TRUE; }
	}
	return FALSE;
}

void FinalKVList(KVList *key_values){
	KeyValue *kv;
	if(!key_values){ return; }
	forlist(kv, key_values->list){ 
		free(kv->key);
		free(kv);
	}
	FinalPList(key_values->list);
	FinalPList(key_values->keys);
	FinalPList(key_values->values);
	free(key_values);
}

