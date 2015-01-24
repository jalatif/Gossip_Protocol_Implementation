/**********************
*
* Progam Name: MP1. Membership Protocol.
* 
* Code authors: <your name here>
*
* Current file: mp2_node.h
* About this file: Header file.
* 
***********************/

#ifndef _NODE_H_
#define _NODE_H_

#include "stdincludes.h"
#include "params.h"
#include "queue.h"
#include "requests.h"
#include "emulnet.h"

// Tfail and Tclean time for more accuracy
#define Tfail  15
#define Tclean 30

/* Configuration Parameters */
char JOINADDR[30];                    /* address for introduction into the group. */
extern char *DEF_SERVADDR;            /* server address. */
extern short PORTNUM;                /* standard portnum of server to contact. */

/* Miscellaneous Parameters */
extern char *STDSTRING;

/* Data template for each member in the list*/
typedef struct MemberData {
    struct address addr;
    int heartbeat_counter;
    int local_time;
    int suspected;
} memberdata;

// Array of memberData
typedef struct memDataSet{
    memberdata **mD;
    int collection_size;
} memDataSet;

/* Address element Linked List template */
typedef struct LinkedList {
    memberdata data;
    struct LinkedList *next;

} linkedlist;

/* String Key Hashtable where each key has a list of values for case of collision */
typedef struct MemberList {
    int size;
    int actual_member_data;
    struct LinkedList **list;
} memberList;


typedef struct member{            
        struct address addr;                   // my address
        int inited;                     // boolean indicating if this member is up
        int ingroup;                    // boolean indiciating if this member is in the group

        queue inmsgq;                   // queue for incoming messages

        int bfailed;                    // boolean indicating if this member has failed

        struct MemberList *memlist;          // Memberlist that is maintained at a particular node member

} member;

/* Message types */
/* Meaning of different message types
  JOINREQ - request to join the group
  JOINREP - replyto JOINREQ
  GOSSIP_HEARBEAT - process gossip message which was recieved
*/
enum Msgtypes{
		JOINREQ,			
		JOINREP,
        GOSSIP_HEARTBEAT,
		DUMMYLASTMSGTYPE
};

/* Generic message template. */
typedef struct messagehdr{ 	
	enum Msgtypes msgtype;
} messagehdr;


/* Functions in mp2_node.c */

/* Message processing routines. */
STDCLLBKRET Process_joinreq STDCLLBKARGS;
STDCLLBKRET Process_joinrep STDCLLBKARGS;
STDCLLBKRET Process_gossiping STDCLLBKARGS;
/*
int recv_callback(void *env, char *data, int size);
int init_thisnode(member *thisnode, address *joinaddr);
*/

/*
Other routines.
*/

void nodestart(member *node, char *servaddrstr, short servport);
void nodeloop(member *node);
int recvloop(member *node);
int finishup_thisnode(member *node);

/*  These are the routines for adding, getting, deleting, collecting, printing, failing and removing members of the member list data structure*/
int hashCode(char *str, int size);
void createMemberList(member *node, int size);
void putMemberData(member *node, address *addr, int heartbeat_counter, int local_time);
memberdata* getMemberData(member *node, address *adrs);
void deleteMember(member *node, address *adrs);
memDataSet* enumerateData(memberList *memlist);
void printMemberData(member *node);
void updateMemberData(member *node, memDataSet *mds, int curr_time);
void checkFailedMembers(member *node, int current_time);
void removeMemberData(member *node, address *addr);

#endif /* _NODE_H_ */

