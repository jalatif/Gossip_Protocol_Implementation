/**********************
*
* Progam Name: MP1. Membership Protocol
* 
* Code authors: <your name here>
*
* Current file: mp1_node.c
* About this file: Member Node Implementation
* 
***********************/

#include "mp1_node.h"
#include "emulnet.h"
#include "MPtemplate.h"
#include "log.h"


/*
 *
 * Routines for introducer and current time.
 *
 */

char NULLADDR[] = {0,0,0,0,0,0};

int isnulladdr( address *addr){
    return (memcmp(addr, NULLADDR, 6)==0?1:0);
}

/* Print the address in pretty format whose pointer is passed */
void printAddr(address *addr){
    if (addr == NULL) return;
    printf("Member's Address is %d.%d.%d.%d", addr->addr[0], addr->addr[1], addr->addr[2], addr->addr[3]);//, *(short *)&addr->addr[4]);
}

/* create an empty member list for a given member in form of hash table*/
void createMemberList(member *node, int size){

    if (size <= 0) return;

    node->memlist = (memberList *) malloc(sizeof(memberList));
    node->memlist->size = size;

    node->memlist->list = (linkedlist **) malloc(size * sizeof(linkedlist *));

    int i;
    for (i= 0; i < size; i++)
        node->memlist->list[i] = NULL;

}

/* Put member data into the member list (hash table) */
void putMemberData(member *node, address *addr, int heartbeat_counter, int local_time){
    memberdata *md = (memberdata *) malloc(sizeof(memberdata));
    memcpy(&md->addr, addr, sizeof(address));
    md->heartbeat_counter = heartbeat_counter;
    md->local_time = local_time;
    md->suspected = 0;

    int hash = hashCode(&md->addr.addr, node->memlist->size); // find hashcode of address string

    // if no linked list at desired position make one
    if (node->memlist->list[hash] == NULL){
        node->memlist->list[hash] = (linkedlist *) malloc(sizeof(linkedlist));
        node->memlist->list[hash]->data = *md;
        node->memlist->list[hash]->next = NULL;
        node->memlist->actual_member_data += 1;
        free(md);
        return;
    }
    // try to look if the entry with same address is already present, if yes then update it
    linkedlist *temp = node->memlist->list[hash];
    while (temp != NULL){
        //if (strcmp(temp->data->addr->addr, adrs) == 0){
        if (memcmp(addr, &temp->data.addr, 4 * sizeof(char)) == 0){
            temp->data.heartbeat_counter = heartbeat_counter;
            temp->data.local_time = local_time;
            free(temp);
            free(md);
            return;
        }
        temp = temp->next;
    }
    // if same entry not found previously, will put new entry
    linkedlist *list = (linkedlist *) malloc(sizeof(linkedlist));
    list->data = *md;
    list->next = node->memlist->list[hash];
    node->memlist->list[hash] = list->next;
    node->memlist->actual_member_data += 1;
    free(md);
    return;
}

/* Update Membership List for each entry. Takes the node whose membership list to be updated and the member Data Set which contains members info in array form */
void updateMemberData(member *node, memDataSet *mds, int curr_time){
    int i = 0;
    memberdata *old_md;
    for (i = 0; i < mds->collection_size ; i++) {
        memberdata *md = *(mds->mD + i);
        if (md == NULL)
            continue;
        old_md = getMemberData(node, &md->addr);
        if (old_md == NULL && md->suspected == 0) { // if this member was not present earlier then put new one and log it
            putMemberData(node, &md->addr, md->heartbeat_counter, curr_time);
#ifdef DEBUGLOG
            logNodeAdd(&node->addr, &md->addr);
#endif

        } else if (old_md != NULL) { // otherwise check for greater heartbeat and then update the entries. Update only when entry is non-suspected and has greater heartbeat
            if (md->heartbeat_counter > old_md->heartbeat_counter  && md->suspected == 0) {
                old_md->heartbeat_counter = md->heartbeat_counter;
                old_md->local_time = curr_time;
                if (old_md->suspected == 1 && md->suspected == 0)
                    old_md->suspected = 0;
            }
        }
    }
    return;
}

/* Get Member Data according to address from a member list */
memberdata* getMemberData(member *node, address *adrs){
    int hash = hashCode(adrs->addr, node->memlist->size);
    if (node->memlist->list[hash] == NULL) return NULL;
    linkedlist *temp = node->memlist->list[hash];
    while (temp != NULL){
        if (memcmp(adrs, &temp->data.addr, 4 * sizeof(char)) == 0)
            return &temp->data;
        temp = temp->next;
    }
    return NULL;
}

/* Copy membership list so that it can be send to other members. Don't send suspected members */
memDataSet* copyMemberData(member *node){
    int i = 0;
    memDataSet *cmds = (memDataSet *) malloc(sizeof(memDataSet));
    memDataSet *mds = enumerateData(node->memlist);
    cmds->collection_size = 0;
    cmds->mD = (memberdata **) malloc(mds->collection_size * sizeof(memberdata *));
    for (i = 0; i < mds->collection_size; i++){
        memberdata *md = *(mds->mD + i);
        if (md->suspected == 1 || md->suspected == 2)
            continue;
        memberdata *nmd = (memberdata *) malloc(sizeof(memberdata));
        nmd->heartbeat_counter = md->heartbeat_counter;
        nmd->local_time = md->local_time;
        nmd->suspected = md->suspected;
        memcpy(&nmd->addr, &md->addr, sizeof(address));

        *(cmds->mD + cmds->collection_size++) = nmd;
    }
    free(mds);
    return cmds;
}

/* delete a member from the memberlist */
void deleteMember(member *node, address *adrs){
    int hash = hashCode(adrs->addr, node->memlist->size);
    if (node->memlist->list[hash] == NULL) return;
    linkedlist *temp = node->memlist->list[hash];
    linkedlist *prev = NULL;
    while (temp != NULL){
        if (memcmp(adrs, &temp->data.addr, 4 * sizeof(char)) == 0){
            if (prev == NULL)
                node->memlist->list[hash] = temp->next;
            else
                prev->next = temp->next;
            temp->next = NULL;
            //temp->data = NULL;

            node->memlist->actual_member_data -= 1;
            break ;
        }
        prev = temp;
        temp = temp->next;
    }
    free(temp);
    free(prev);
    return;
}

/* make an enumeration of every data member and return array of member info as memDataSet* */
memDataSet* enumerateData(memberList *memlist){
    address joinaddr;
    memDataSet *mds = (memDataSet *) malloc(sizeof(memDataSet));
    mds->mD = (memberdata **) malloc(memlist->actual_member_data * sizeof(memberdata *));
    int i = 0, j = 0;
    for (i = 0; i < memlist->size; i++){
        linkedlist *temp = memlist->list[i];
        while (temp != NULL){
            *(mds->mD + j++) = &temp->data;
            temp = temp->next;
        }
    }
    mds->collection_size = j;
    return mds;
}

/* Print each Member Data in pretty format */
void printMemberData(member *node){
    //printf("\n Size of members now is %d\n", actual_size);
    memDataSet *mds = enumerateData(node->memlist);

    int i = 0;
    for (i = 0; i < mds->collection_size; i++){
        memberdata *md = *(mds->mD + i);
        if (md == NULL)
            continue;
        printAddr(&md->addr);
        printf(", Heartbeat = %d, Local Time = %d, Suspected = %d\n", md->heartbeat_counter, md->local_time, md->suspected);
    }
    free(mds);
    return;
}

/* Compute the hashcode of a string according to given size*/
int hashCode(char *str, int size){
    int i;
    int hash = 0;
    for (i = 0; i < strlen(str); i++){
        hash = (31 * hash) + *(str + i);
        hash = hash % size;
    }
    return hash;
}

/* Remove the member from the membership list of node */
void removeMemberData(member *node, address *addr){
    memberdata *md = getMemberData(node, addr);
    if (md == NULL)
        return;
    if (md->suspected == 2)
        return;
    md->suspected = 2;
#ifdef DEBUGLOG
    logNodeRemove(&node->addr, &md->addr);
#endif

    deleteMember(node, addr);

}

/* Check for failed members for each node in a member list by checking their local time and comparing it with time passed from then to Tfail and Tfail + Tclean time  */
void checkFailedMembers(member *node, int current_time){
    int i = 0;
    memDataSet *mds = enumerateData(node->memlist);
    for (i = 0; i < mds->collection_size; i++){
        memberdata *md = *(mds->mD + i);
        if (current_time - Tfail - Tclean > md->local_time){ // if local time outdated after Tfail + Tclean then delete it
            printf("\nNode Removed from ");
            printAddr(&node->addr);
            removeMemberData(node, &md->addr);
        } else // if local time outdated after Tfail then mark it as suspected
        if (current_time - Tfail > md->local_time){
            md->suspected = 1;
            printf("\nNode Suspected = ");
            printAddr(&md->addr);
        }
    }
    return;
}

/* 
Return the address of the introducer member. 
*/
address getjoinaddr(void){

    address joinaddr;

    memset(&joinaddr, 0, sizeof(address));
    *(int *)(&joinaddr.addr)=1;
    *(short *)(&joinaddr.addr[4])=0;

    return joinaddr;
}

/*
 *
 * Message Processing routines.
 *
 */

/* 
Received a JOINREQ (joinrequest) message.
*/
void Process_joinreq(void *env, char *data, int size)
{
	/* Introducer adds the entry of node to the list and sends JOIN REPLY to that node along with a copy of membership list */
    printf("\nIn process joinreq\n");
    messagehdr *msg;
    member *node = (member *) env;

    address joinaddr = getjoinaddr();

    address *destination_node;
    destination_node = (address *) malloc(sizeof(address));
    memset(destination_node, 0, sizeof(address));

    strcpy(destination_node->addr, data);

    if(memcmp(&node->addr, &joinaddr, 4 * sizeof(char)) != 0) return;

    // if membership was not present create one and put entry of itself
    if (node->memlist == NULL){
        createMemberList(node, MAX_NNB);
        putMemberData(node, &joinaddr, 0, globaltime);
#ifdef DEBUGLOG
        logNodeAdd(&node->addr, &node->addr);
#endif
    }
    // if member not present already then add the member from where join request came
    if (getMemberData(node, destination_node) == NULL){
        putMemberData(node, destination_node, 0, globaltime);
#ifdef DEBUGLOG
        logNodeAdd(&node->addr, destination_node);
#endif
    }

    printMemberData(node);
    memDataSet *cmds = copyMemberData(node);
    size_t msgsize = sizeof(messagehdr) + sizeof(memDataSet **);
    msg=malloc(msgsize);

    /* create JOINREQ message: format of data is {struct memDataSet } **/
    msg->msgtype=JOINREP;
    memcpy((char *)(msg + 1), &cmds, sizeof(memDataSet **));

    printf("\nTrying to send joinrep message from introducer to ");
    printAddr(destination_node);
    printf("\n");

    /* send JOINREP message to the member from where join request came. */
    MPp2psend(&joinaddr, destination_node, (char *)msg, msgsize);

    free(msg);

    free(destination_node);
    return;
}

/* 
Received a JOINREP (joinreply) message. 
*/
void Process_joinrep(void *env, char *data, int size)
{
	/* Recieves join reply from introducer along with membership list. Add itself to the group and update its membership list */
    printf("\nIn process_join Reply of");
    member *node = (member *) env;
    printAddr(&node->addr);
    printf("\n");

    memDataSet **cmds = (memDataSet **) data;
    memberList *mds = *cmds;
    if (node->memlist == NULL){
        createMemberList(node, MAX_NNB);
    }

    updateMemberData(node, mds, globaltime);

    printMemberData(node);

    printf("\nI am adding myself to the group\n");
    printAddr(&node->addr);
    printf("\n");
    node->ingroup = 1;

    free(mds);
    return;
}
/*
Received a Gossip_Hearbeat message.
*/
void Process_gossiping(void *env, char *data, int size){

    /* If gossip message recieved from someone in the group along with membership list and updates it membership list according to gossiping rules */
    member *node = (member *) env;
    printf("\nIn Gossip_Processing of");
    printAddr(&node->addr);
    if (node->ingroup == 0){
        printf("Can't accept gossip\n");
        return;
    }
    printf("\n");

    memDataSet **cmds = (memDataSet **) data;
    memberList *mds = *cmds;
    if (node->memlist == NULL){
        createMemberList(node, MAX_NNB);
    }

    updateMemberData(node, mds, globaltime);

    printMemberData(node);

    free(mds);
    return;
}

/* 
Array of Message handlers. 
*/
void ( ( * MsgHandler [20] ) STDCLLBKARGS )={
/* Message processing operations at the P2P layer. */
    Process_joinreq, 
    Process_joinrep,
    Process_gossiping
};

/* 
Called from nodeloop() on each received packet dequeue()-ed from node->inmsgq. 
Parse the packet, extract information and process. 
env is member *node, data is 'messagehdr'. 
*/

int recv_callback(void *env, char *data, int size){

    member *node = (member *) env;
    messagehdr *msghdr = (messagehdr *)data;
    char *pktdata = (char *)(msghdr+1);

    if(size < sizeof(messagehdr)){
#ifdef DEBUGLOG
        LOG(&((member *)env)->addr, "Faulty packet received - ignoring");
#endif
        return -1;
    }

#ifdef DEBUGLOG
    LOG(&((member *)env)->addr, "Received msg type %d with %d B payload", msghdr->msgtype, size - sizeof(messagehdr));
#endif

    if((node->ingroup && msghdr->msgtype >= 0 && msghdr->msgtype <= DUMMYLASTMSGTYPE)
        || (!node->ingroup && msghdr->msgtype==JOINREP))            
            /* if not yet in group, accept only JOINREPs */
        MsgHandler[msghdr->msgtype](env, pktdata, size-sizeof(messagehdr));
    /* else ignore (garbled message) */
    free(data);

    return 0;

}

/*
 *
 * Initialization and cleanup routines.
 *
 */

/* 
Find out who I am, and start up. 
*/
int init_thisnode(member *thisnode, address *joinaddr){
    
    if(MPinit(&thisnode->addr, PORTNUM, (char *)joinaddr)== NULL){ /* Calls ENInit */
#ifdef DEBUGLOG
        LOG(&thisnode->addr, "MPInit failed");
#endif
        exit(1);
    }
#ifdef DEBUGLOG
    else LOG(&thisnode->addr, "MPInit succeeded. Hello.");
#endif

    thisnode->bfailed=0;
    thisnode->inited=1;
    thisnode->ingroup=0;
    /* node is up! */

    return 0;
}


/* 
Clean up this node. 
*/
int finishup_thisnode(member *node){

	/* Clean the hashtable memberlist structure for the node by calling free on every pointer */

    int i = 0;
    for (i = 0; i < node->memlist->size; i++){
        free(node->memlist->list[i]);
    }
    free(node->memlist->list);
    free(node->memlist);

    return 0;
}


/* 
 *
 * Main code for a node 
 *
 */

/* 
Introduce self to group. 
*/
int introduceselftogroup(member *node, address *joinaddr){
    
    messagehdr *msg;
#ifdef DEBUGLOG
    static char s[1024];
#endif

    if(memcmp(&node->addr, joinaddr, 4*sizeof(char)) == 0){
        /* I am the group booter (first process to join the group). Boot up the group. */
#ifdef DEBUGLOG
        LOG(&node->addr, "Starting up group...");
#endif

        node->ingroup = 1;
    }
    else{
        size_t msgsize = sizeof(messagehdr) + sizeof(address);
        msg=malloc(msgsize);

    /* create JOINREQ message: format of data is {struct address myaddr} */
        msg->msgtype=JOINREQ;
        memcpy((char *)(msg+1), &node->addr, sizeof(address));

#ifdef DEBUGLOG
        sprintf(s, "Trying to join...");
        LOG(&node->addr, s);
#endif

    /* send JOINREQ message to introducer member. */
        address *address2;
        address2 = (address*) malloc(sizeof(address));
        memcpy(&address2, &node->addr, sizeof(address));
        MPp2psend(&node->addr, joinaddr, (char *)msg, msgsize);
        
        free(msg);
    }

    return 1;

}

/* 
Called from nodeloop(). 
*/
void checkmsgs(member *node){
    void *data;
    int size;

    /* Dequeue waiting messages from node->inmsgq and process them. */
	
    while((data = dequeue(&node->inmsgq, &size)) != NULL) {
        recv_callback((void *)node, data, size); 
    }
    return;
}


/* 
Executed periodically for each member. 
Performs necessary periodic operations. 
Called by nodeloop().
*/
void nodeloopops(member *node){

	/* If a node is in the group and its membership table has been initialized then update heartbeat of itself in its membership list
	and then
	pick a random node which is not itself and a suspected node and send its membership table to them by making a copy of it. */

    if (node->memlist == NULL || node->ingroup == 0)
        return;
    printf("\n In Node Loop Operations of ");
    printAddr(&node->addr);
    printf("\n");
    //==========================Gossip to random node =================================================================

    messagehdr *msg;

    /* Heartbeats and updates the membership list */
    memberdata *gmd = getMemberData(node, &node->addr);
    gmd->heartbeat_counter++;
    gmd->local_time = globaltime;

    printMemberData(node);

    memDataSet *mds = enumerateData(node->memlist);
    int random_id, i = 0;
    address random_address = getjoinaddr();
    while (1){
        if ( i >= node->memlist->actual_member_data){
            printf("No gossip for this one right now");
            return;
        }
        random_id = rand() % mds->collection_size;
        random_address = mds->mD[random_id]->addr;

        if (memcmp(&random_address, &node->addr, sizeof(address)) != 0 && mds->mD[random_id]->suspected == 0)
            break;
        i++;
        printf("Chose Myself for Gossip but will correct this.\n");
    }
    printf("\nSending to a random node = ");
    printAddr(&random_address);
    printf("\n");

    memDataSet *cmds = copyMemberData(node);

    size_t msgsize = sizeof(messagehdr) + sizeof(memDataSet **);
    msg=malloc(msgsize);

    /* create GOSSIP_HEARBEAT message: format of data is {struct memDataSet } **/
    msg->msgtype=GOSSIP_HEARTBEAT;
    memcpy((char *)(msg + 1), &cmds, sizeof(memDataSet **));

    /* Sending Membership List to a random member in the group */

    MPp2psend(&node->addr, &random_address, (char *)msg, msgsize);

    free(msg);
    free(mds);
    //===========================================================================================

    //=============================Check for failures in nodes ==============================================================

    checkFailedMembers(node, globaltime);
    //===========================================================================================
    return;
}

/* 
Executed periodically at each member. Called from app.c.
*/
void nodeloop(member *node){
    if (node->bfailed) return;

    checkmsgs(node);

    /* Wait until you're in the group... */
    if(!node->ingroup) return ;

    /* ...then jump in and share your responsibilites! */
    nodeloopops(node);

    return;
}

/* 
All initialization routines for a member. Called by app.c. 
*/
void nodestart(member *node, char *servaddrstr, short servport){

    address joinaddr=getjoinaddr();

    /* Self booting routines */
    if(init_thisnode(node, &joinaddr) == -1){

#ifdef DEBUGLOG
        LOG(&node->addr, "init_thisnode failed. Exit.");
#endif
        exit(1);
    }

    if(!introduceselftogroup(node, &joinaddr)){
        finishup_thisnode(node);
#ifdef DEBUGLOG
        LOG(&node->addr, "Unable to join self to group. Exiting.");
#endif
        exit(1);
    }

    return;
}

/* 
Enqueue a message (buff) onto the queue env. 
*/
int enqueue_wrppr(void *env, char *buff, int size){    return enqueue((queue *)env, buff, size);}

/* 
Called by a member to receive messages currently waiting for it. 
*/
int recvloop(member *node){
    if (node->bfailed) return -1;
    else return MPrecv(&(node->addr), enqueue_wrppr, NULL, 1, &node->inmsgq); 
    /* Fourth parameter specifies number of times to 'loop'. */
}

