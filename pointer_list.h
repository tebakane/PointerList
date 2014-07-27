#ifndef _POINTER_LIST_H_
#define _POINTER_LIST_H_
/*
 * リスト用の関数
 */

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct _PListValue PListValue;
	typedef struct _PList{
		PListValue *first;
		PListValue *last;
		PListValue *now;
	}PList;
	struct _PListValue{
		void *value;
		PListValue *next;
		PListValue *prev;
	};

	PList *InitPList();
	void FinalPList(PList *list);
	void ClearPList(PList *list);
	void AddPList(PList *list, void *value);
	PList *CopyPList(PList *list);
	void PlusPList(PList *to, PList *from);
	void InsertPList(PList *list, void *value, const unsigned int index);
	void DeletePList(PList *list, const unsigned int index);
	void *FirstValuePList(PList *list);
	void *NextValuePList(PList *list);
	void UnshiftPList(PList *list, void *value);
	void *GetValueIndexPList(PList *list, const unsigned int index);
	int SizePList(PList *list);
#define LengthPList(list) SizePList(list) 
/* forlist内で同じPListに対してforlistを使用するとnowが変わって意味不明な動きをするので
 * そういった場合はforlistvalueを使用して value->valueでアクセスすること */
#define forlist(value, list) for(value = FirstValuePList(list); list->now != NULL; value = NextValuePList(list))
#define forlistvalue(value, list) for(value = list->first; value != NULL; value = value->next)
#ifdef __cplusplus
}
#endif
#endif /* _POINTER_LIST_H_ */

