#include <stdio.h>
#include "mp1_node.h"

memberList* createMemberList(int size){
    memberList* ml;

    if (size <= 0) return NULL;

    ml = (memberList *) malloc(sizeof(memberList));
    ml->size = size;

    ml->list = (linkedlist **) malloc(size * sizeof(linkedlist *));

    int i;
    for (i= 0; i < size; i++)
        ml->list[i] = NULL;

    return ml;

}

int putMemberData(memberList *ml, address *adrs, int heartbeat_counter, int local_time){
    int hash = hashCode(adrs, ml->size);
    if (ml->list[hash] == NULL){
        ml->list[hash] = (linkedlist *) malloc(sizeof(linkedlist));
        ml->list[hash]->data = (memberdata *) malloc(sizeof(memberdata));
        ml->list[hash]->data->addr = adrs;
        ml->list[hash]->data->heartbeat_counter = heartbeat_counter;
        ml->list[hash]->data->local_time = local_time;
        ml->list[hash]->next = NULL;
        ml->actual_member_data += 1;
        return 0;
    }
    linkedlist *temp = ml->list[hash];
    while (temp != NULL){
        //if (strcmp(temp->data->addr->addr, adrs) == 0){
        if (memcmp(adrs, temp->data->addr, 4 * sizeof(char)) == 0){
            temp->data->heartbeat_counter = heartbeat_counter;
            temp->data->local_time = local_time;
            return 0;
        }
        temp = temp->next;
    }
    linkedlist *list = (linkedlist *) malloc(sizeof(linkedlist));
    list->data = (memberdata *) malloc(sizeof(memberdata));
    list->data->addr = adrs;
    list->data->heartbeat_counter = heartbeat_counter;
    list->data->local_time = local_time;
    list->next = ml->list[hash];
    ml->list[hash] = list->next;
    ml->actual_member_data += 1;
    return 0;
}

memberdata* getMemberData(memberList *ml, address *adrs){
    int hash = hashCode(adrs, ml->size);
    if (ml->list[hash] == NULL) return NULL;
    linkedlist *temp = ml->list[hash];
    while (temp != NULL){
        if (memcmp(adrs, temp->data->addr, 4 * sizeof(char)) == 0)
            return temp->data;
        temp = temp->next;
    }
    return NULL;
}

int deleteMember(memberList *ml, address *adrs){
    int hash = hashCode(adrs, ml->size);
    if (ml->list[hash] == NULL) return -1;
    linkedlist *temp = ml->list[hash];
    linkedlist *prev = NULL;
    while (temp != NULL){
        if (memcmp(adrs, temp->data->addr, 4 * sizeof(char)) == 0){
            if (prev == NULL)
                ml->list[hash] = temp->next;
            else
                prev->next = temp->next;
            temp->next = NULL;
            temp->data = NULL;
            free(temp);
            ml->actual_member_data -= 1;
            return 0;
        }
        prev = temp;
        temp = temp->next;
    }
    return -1;
}

memberdata** enumerateData(memberList *ml){
    memberdata **mds = (memberdata *) malloc(ml->actual_member_data * sizeof(memberdata *));
    int i = 0, j = 0;
    for (i = 0; i < ml->size; i++){
        linkedlist *temp = ml->list[i];
        while (temp != NULL){
            *(mds + j++) = temp->data;
            temp = temp->next;
        }
    }
    return mds;
}

void printAddr(address *addr){
    printf("--->%d.%d.%d.%d:%d\n", addr->addr[0], addr->addr[1], addr->addr[2], addr->addr[3], *(short *)&addr->addr[4]);
}

void printMemberData(memberdata **mds, int actual_size){
    printf("\n Size of members now is %d\n", actual_size);
    int i = 0;
    for (i = 0; i < actual_size; i++){
        memberdata *md = *(mds + i);
        if (md == NULL)
            break;
        printf("Member Data is HeartBeatCounter = %d, LocalTime = %d and Address = ", md->heartbeat_counter, md->local_time);
        printAddr(md->addr);
    }
    printf("\n Size of members now is %d\n", i);
}

int hashCode(char* str, int size){
    int i;
    int hash = 0;
    for (i = 0; i < strlen(str); i++){
        hash = (31 * hash) + *(str + i);
        hash = hash % size;
    }
    return hash;
}

int main(){
    printf("%d\n", hashCode("abcd", 100));
    memberList *ml = createMemberList(10);
    address j1;
    memset(&j1, 0, sizeof(address));
    j1.addr[0] = 1; j1.addr[1] = 2; j1.addr[2] = 3; j1.addr[3] = 4; j1.addr[4] = 1;


    putMemberData(ml, &j1, 1, 1);

    address j2;
    memset(&j2, 0, sizeof(address));
    j2.addr[0] = 2; j2.addr[1] = 2; j2.addr[2] = 3; j2.addr[3] = 4; j2.addr[4] = 1;

    putMemberData(ml, &j2, 2, 1);

    memberdata *val = getMemberData(ml, j1.addr);
    printf("Member Data Values = %d %d\n", val->heartbeat_counter, val->local_time);
    //deleteMember(ml, j1.addr);
    val = getMemberData(ml, &j1);
    if (val != -1)
        printf("Member Data Values = %d %d\n", val->heartbeat_counter, val->local_time);
    else
        printf("NULL Member Data value for this address\n");
    val = getMemberData(ml, &j2);
    printf("Member Data Values = %d %d\n", val->heartbeat_counter, val->local_time);

    memberdata **mds = enumerateData(ml);
    printMemberData(mds, ml->actual_member_data);
}