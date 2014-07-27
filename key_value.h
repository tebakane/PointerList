/*
 * KEY VALUE型
 * KEYとVALUEをひも付けるために使用する。
 */

#ifndef _KEY_VALUE_H_
#define _KEY_VALUE_H_
#include "pointer_list.h"
#include "boolean.h"
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct _KeyValue KeyValue;
	typedef struct _KVList KVList;

	KVList *InitKVList();
	void FinalKVList(KVList *key_values);

	void AddKVList(KVList *list, char *key, void *value);
	void DeleteKVKist(KVList *list, char *key);
	void *GetValueKVList(KVList *list, char *key);
	PList *GetKeysKVList(KVList *list);
	PList *GetValuesKVList(KVList *list);
	BOOL IsKeyExistsKVList(KVList *list, const char *key);

#define SetKVList(list, key, value) AddKVList(list, key, value)
#define GetKVList(list, key) GetValueKVList(list, key)

#ifdef __cplusplus
}
#endif
#endif /* _HASH_KEY_H_ */
