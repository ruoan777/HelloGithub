#include <iostream>
#include <string>
#include <math.h>
using namespace std;
#define MAXTABLESIZE 1000000
typedef string ElementType;
typedef int Index;

typedef struct ListNode *PtrtoListNode;
struct ListNode{
    ElementType Data;
    int Cout;
    PtrtoListNode next;
};
typedef PtrtoListNode List;
typedef PtrtoListNode Position;
typedef struct HashTbl *HashTable;
struct HashTbl{
    int TableSize;
    List Heads;
};
HashTable CreateTable(int N);
void ScanAndOutput(HashTable H);
void DestroyTable(HashTable H);
Position Find(HashTable H,ElementType key);
void Insert(HashTable H,ElementType key);
int NextPrime(int N);
Index Hash(int key,int P);

Index Hash(int key,int P){
    return key%P;
}
Position Find(HashTable H,ElementType key){
    Position P;
    Index Pos;
    ElementType tmp=key.substr(6,5);
    int KEY=stoi(tmp);
    Pos=Hash(KEY,H->TableSize);
    P=H->Heads[Pos].next;
    while(P && P->Data!=key)
        P=P->next;
    return P;
}
void Insert(HashTable H,ElementType key){
    Position P,NewCell;
    Index Pos;
    ElementType tmp;
    int KEY;
    P=Find(H,key);
    if(!P){
        NewCell=(Position)malloc(sizeof(ListNode));
        NewCell->Data=key;
        NewCell->Cout=1;
        tmp=key.substr(6,5);
        KEY=stoi(tmp);
        Pos=Hash(KEY,H->TableSize);
        NewCell->next=H->Heads[Pos].next;
        H->Heads[Pos].next=NewCell;
    }
    else{
        P->Cout++;
    }
}
int NextPrime(int N){
/* 返回大于N且不超过MAXTABLESIZE的最小素数 */
    int i,p=(N%2)? N+2 : N+1; /*从大于N的下一个奇数开始 */
    while(p<= MAXTABLESIZE ) {
        for(i=(int)sqrt(p);i>2;i--)
            if (!(p%i)) break; /* p不是素数 */
        if (i==2) break; /* for正常结束，说明p是素数 */
        else  p+=2; /* 否则试探下一个奇数 */
    }
    return p;
}
HashTable CreateTable(int N){
    HashTable H;
    int i;
    H=(HashTable)malloc(sizeof(HashTbl));
    H->TableSize=NextPrime(N);
    H->Heads=(List)malloc(sizeof(ListNode)*(H->TableSize));
    for(i=0;i<H->TableSize;i++){
        //H->Heads[i].Data=;
        H->Heads[i].next=nullptr;
        H->Heads[i].Cout=0;
    }
    return H;
}
void DestroyTable( HashTable H ){
    int i;
    Position P, tmp;
    /* 释放每个链表的结点 */
    for( i=0; i<H->TableSize; i++ ){
        P=H->Heads[i].next;
        while(P){
            tmp = P->next;
            delete P;
            P=tmp;
        }
    }
    delete H->Heads;/* 释放头结点数组 */
    delete H;/* 释放散列表结点 */
}
void ScanAndOutput(HashTable H){
    int i,MaxCnt=0;
    ElementType MinPhone;
    List Ptr;
    int SameCnt=0;
    for(i=0;i<H->TableSize;i++){
        Ptr=H->Heads[i].next;
        while(Ptr){
            if(Ptr->Cout>MaxCnt){
                MaxCnt=Ptr->Cout;
                MinPhone=Ptr->Data;
                SameCnt=1;
            }
            else if(Ptr->Cout==MaxCnt){
                SameCnt++;
                if(Ptr->Data<MinPhone)
                    MinPhone=Ptr->Data;
            }
            Ptr=Ptr->next;
        }
    }
    cout<<MinPhone<<" "<<MaxCnt<<endl;
    if(SameCnt>1)
        cout<<SameCnt<<endl;
}
int main(){
    HashTable H;
    int i,N;
    ElementType key;
    cin>>N;
    H=CreateTable(N*2);
    for(i=0;i<N;i++){
        cin>>key;Insert(H,key);
        cin>>key;Insert(H,key);
    }
    ScanAndOutput(H);
    DestroyTable(H);
    return 0;
}/*
6
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832
15005713862 15005713862
18087925832 18087925832*/
