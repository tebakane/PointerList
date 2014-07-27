#include "pointer_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

PList *InitPList(){
	PList *list = NULL;
	list = (PList*)malloc(sizeof(PList));
	if(!list){ return NULL; }
	memset(list, 0x00, sizeof(PList));
	return list;
}

void FinalPList(PList *list){
	if(!list){ return; }
	ClearPList(list);
	free(list);
}


/* ���g���܂�����ɂ��� */
void ClearPList(PList *list){
	PListValue *lvalue, *next_value;
	for(lvalue = list->first; lvalue != NULL; lvalue = next_value){ 
		next_value = lvalue->next;
		free(lvalue);
	}
	list->now = list->last = list->first = NULL;
}

/* index��0����X�^�[�g */
/* index�ɒl�����݂��Ȃ��ꍇ��NULL��Ԃ� */
PListValue *GetPListValueIndex(PListValue *lvalue, const unsigned int index){
	if(index == 0){ return lvalue; }
	if(lvalue == NULL){ return NULL; }
	return GetPListValueIndex(lvalue->next, index - 1);
}

void *GetValueIndexPListValue(PListValue *lvalue, const unsigned int index){
	if(lvalue == NULL){ return NULL; }
	if(index == 0){ return lvalue->value; }
	return GetValueIndexPListValue(lvalue->next, index - 1);
}
void *GetValueIndexPList(PList *list, const unsigned int index){
	return GetValueIndexPListValue(list->first,index);
}

/* �Ō�ɒǉ����� */
void AddPList(PList *list, void *value){
	PListValue *lvalue = (PListValue*)malloc(sizeof(PListValue));
	if(!lvalue){ return; }
	memset(lvalue, 0x00, sizeof(PListValue));
	lvalue->value = value;
	if(!list->first){ list->first = lvalue; }
	else{
		lvalue->prev = list->last;
		list->last->next = lvalue; 
	}
	list->last = lvalue;
}

/* �ŏ��ɒǉ����� */
void UnshiftPList(PList *list, void *value){
	PListValue *lvalue = (PListValue*)malloc(sizeof(PListValue));
	if(!lvalue){ return; }
	memset(lvalue, 0x00, sizeof(PListValue));
	lvalue->value = value;
	/* list->first��NULL�łȂ��ꍇ�A����̑O�ɒǉ����� */
	if(list->first){
		list->first->prev = lvalue;
	}
	lvalue->next = list->first;
	list->first = lvalue;
}

PList *CopyPList(PList *list){
	PList *copy;
	void *value;
	if(!list){ return NULL; }
	copy = InitPList();
	forlist(value, list){
		AddPList(copy, value);
	}
	return copy;
}

/* to�̍Ō��from��ǉ�����B */
void PlusPList(PList *to, PList *from){
	void *value;
	if(!to){ return; }
	if(!from || !from->first){ return; }
	forlist(value, from){ AddPList(to, value); }
}

/* index�̉ӏ��ɒǉ�����
 * index�������Ă���ꍇ�͍Ō�ɒǉ� */
void InsertPList(PList *list, void *value, const unsigned int index){
	PListValue *lvalue, *new_lvalue;
	if(index == 0){ UnshiftPList(list, value); return; } 
	lvalue = GetPListValueIndex(list->first, index);
	/* index���Ōォ�����Ă���̂ōŌ�ɒǉ� */
	if(!lvalue){ AddPList(list, value); return; }
	new_lvalue = (PListValue*)malloc(sizeof(PListValue));
	if(!new_lvalue){ return; }
	new_lvalue->value = value;
	new_lvalue->prev = lvalue->prev;
	new_lvalue->next = lvalue;
	lvalue->prev->next = new_lvalue;
	lvalue->prev = new_lvalue;
}

/* index�̉ӏ��̃f�[�^���폜���� */
void DeletePList(PList *list, const unsigned int index){
	PListValue *lvalue = GetPListValueIndex(list->first, index);
	if(lvalue == NULL){ return; }
	
	if(lvalue == list->last && lvalue == list->first){
		/* 1�����������Ă��Ȃ� */
		list->last = list->first = NULL;
	} else if(lvalue == list->last){
		/* lvalue���Ō� */
		list->last = lvalue->prev;
		lvalue->prev->next = NULL;
	} else if(lvalue == list->first){
		/* lvalue���ŏ� */
		list->first = lvalue->next;
		lvalue->next->prev = NULL;
	} else {
		/* lvalue���r�� */
		lvalue->prev->next = lvalue->next;
		lvalue->next->prev = lvalue->prev;
	}
	free(lvalue);
}


void *FirstValuePList(PList *list){
	list->now = list->first;
	if(!list->now){ return NULL; }
	return list->now->value;
}

void *NextValuePList(PList *list){
	list->now = list->now->next;
	if(!list->now){ return NULL; }
	return list->now->value;
}

int SizePListValue(PListValue *value){
	if(!value){ return 0; }
	return SizePListValue(value->next);
}

int SizePList(PList *list){
	return SizePListValue(list->first);
}
