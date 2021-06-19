#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 1000
#define MAX 20

typedef struct {
    int data[MAX];
    int count, front, rear;
}Queue;

typedef struct{
    int data[MAX];
    int count;
}stack;


//fungsi inisialisasi
void inisialisasiMatriks();
void inisialisasi(Queue *q);
void cetakArray(int arr[N]);

//fungsi queue
int penuh (Queue *q);
int kosong (Queue *q);
void enqueue(Queue *q, int x);
int dequeue(Queue *q);

//fungsi djikstra
int cari(Queue *q, int cari);
void djikstra(Queue *q);

//fungsi stack
void inisialStack(stack *s);
int kosongStack(stack *s);
void push(stack *s, int x);
int pop(stack *s);

//fungsi cetak
void cetakRute();
void lagi(Queue *antrian);

//int global
int beban[N][N] = {{M, 1, 3, M, M}, {M, M, 1, M, 5}, {3, M, M, 2, M}, {M, M, M, M, 1}, {M, M, M, M, M}};
int TQ[N], R[N], asal, tujuan;

int main()
{
    Queue antrian;
    eksekusi(&antrian);
}

void eksekusi(Queue *antrian)
{
    char jwb;
    do{
        printf("Algoritma Graph Berbasis Djikstra\n\n");

        printf("Node asal : ");
        scanf("%d", &asal);
        printf("Node tujuan : ");
        scanf("%d", &tujuan);

        asal = asal - 1;
        tujuan = tujuan - 1;

        inisialisasiMatriks();
        inisialisasi(antrian);

        djikstra(antrian);
        cetakRute();

        printf("Total beban : %d", TQ[tujuan]);
        printf("\nMatriks TQ : ");
        cetakMatriks(TQ);

        printf("Matriks R : ");
        cetakMatriks(R);
        fflush(stdin);

        printf("\nLagi ? (Y/T) ");
        scanf(" %c", &jwb);
        fflush(stdin);

    } while(jwb == 'y' || jwb == 'Y');
}

void cetakMatriks(int arr[N])
{
    int i;
    for(i=0; i<N; i++){
        printf("%d ", arr[i]);
    }
    puts("");
}

void inisialisasiMatriks()
{
    int i;
    for(i=0; i<N; i++){
        TQ[i] = M;
        R[i] = -1;
    }
    TQ[asal] = 0;
}

void inisialisasi(Queue *q)
{
    q->count = 0;
    q->front = 0;
    q->rear = 0;
}

int penuh (Queue *q)
{
    return(q->count == MAX);
}

int kosong (Queue *q)
{
    return(q->count == 0);
}

void enqueue(Queue *q, int x)
{
    if(penuh(q))
        puts("Queueu penuh, tidak bisa masukkan data");
    else{
        q->data[q->rear] = x;
        q->rear = (q->rear + 1) % MAX;
        q->count++;
    }
}

int dequeue(Queue *q)
{
    int temp;
    temp = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return temp;
}

int cari(Queue *q, int cari)
{
    int i = 0;
    int depan = q->front;
    while(i < q->count){
        if(q->data[depan] == cari)
            return 1;
        depan = (depan + 1)%MAX;
        i++;
    }
    if(q->data[depan] != cari)
        return 0;
}

void djikstra(Queue *q)
{
    int currentNode, i;
    enqueue(q, asal);
    while(!kosong(q)){
        currentNode = dequeue(q);
        i = 0;
        while(i<5){
            if(beban[currentNode][i] != M){
                if(beban[currentNode][i] + TQ[currentNode] < TQ[i]){
                    TQ[i] = beban[currentNode][i] + TQ[currentNode];
                    R[i] = currentNode;
                    if(i != asal && i != tujuan && !cari(q, i))
                        enqueue(q, i);
                }
            }
            i++;
        }
    }
}

void inisialStack(stack *s)
{
    s->count = 0;
}

int kosongStack(stack *s)
{
    if(s->count==0)
        return (1);
    else
        return (0);
}

void push(stack *s, int x)
{
    s->data[s->count] = x;
    s->count++;
}

int pop(stack *s)
{
    int temp;
    if(kosong(s)){
        printf("Stack kosong, tidak dapat Pop data\n");
        return ' ';
    }
    else{
        --s->count;
        temp = s->data[s->count];
        return temp;
    }
}

void cetakRute()
{
    int i, jauh;
    stack rute;

    inisialisasi(&rute);

    jauh = tujuan - asal;

    printf("\nRute tercepat : %d-", asal+1);

    for(i=jauh+asal; i>asal+1; i--)
        push(&rute, R[i]);

    while(!kosongStack(&rute))
        printf("%d-", pop(&rute)+1);

    printf("%d\n", tujuan+1);
}
