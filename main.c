typedef struct Processo{
    int id;
    int burst;
    int cpu;
    int io;
    int temp;
} processo;

typedef struct Execucao{
    int id;
    int burst;
    int cpu;
    int io;
    int temp;
}execucao;

typedef struct Espera{
        int n;
        processo *ptr;
}espera;

typedef struct RR{
    int n;
    processo *ptr;
}RR;

typedef struct FCFS{
    int n;
    processo *ptr;
}FCFS;

typedef struct TERM{
    int n;
    processo *ptr;
}TERM;

void cabecalho(int n, int x){
    int i;
    printf("\n FILA\t");
    for(i=n-1; i>=0; i--)
        printf(" %3d\t", i+1);
    if(x==1){
    printf("-->  EXECUCAO   ");
    printf("-->  ESPERA\t");
    for(i=n-1; i>=0; i--)
        printf("%3d    ", i+1);
    printf("   -->    TEMPO");
    }
}

void imprimeRR(RR *ptrx, int n,execucao *exec, espera *esp,int contA, int cont){
    int i;

    /// linha Q0
    printf("\n   Q0\t");
    for(i=n; i>0; i--){
        if((*ptrx).ptr[i-1].id!=0)
            printf("  P%d\t", (*ptrx).ptr[i-1].id);
        if((*ptrx).ptr[i-1].id==0)
            printf("    \t");
    }
    if((*exec).id!=0)
        printf("-->\tP%d\t", (*exec).id);
    if((*exec).id==0)
        printf("-->\t  \t");


    /// esp linha Q0
    printf("-->\t        ");
    for(i=n; i>0; i--){
        if((*esp).ptr[i-1].id!=0)
            printf(" P%d    ", (*esp).ptr[i-1].id);
        if((*esp).ptr[i-1].id==0)
            printf("       ");
    }

    if(cont>=10)
        printf("   -->   %3d-%d", contA,cont);
    else
        printf("   -->      %d", cont);


    /// linha Burst
    printf("\nBurst\t");
    for(i=n; i>0; i--){
        if((*ptrx).ptr[i-1].id!=0)
            printf(" %3d\t", (*ptrx).ptr[i-1].burst);
        if((*ptrx).ptr[i-1].id==0)
            printf("    \t");
    }
    if((*exec).id!=0)
        printf("-->    %3d\t", (*exec).burst);
    if((*exec).id==0)
         printf("-->       \t");

    printf("-->\t        ");
    for(i=n; i>0; i--){
        if((*esp).ptr[i-1].id!=0)
            printf("%3d    "  ,  (*esp).ptr[i-1].burst);
        if((*esp).ptr[i-1].id==0)
            printf("       ");
    }
    printf("   -->");

    ///linha I/O
    printf("\n  I/O\t");
    for(i=n; i>0; i--){
        if((*ptrx).ptr[i-1].id!=0)
            printf(" %3d\t", (*ptrx).ptr[i-1].io);
        if((*ptrx).ptr[i-1].id==0)
            printf("    \t");
    }

    if((*exec).id!=0)
        printf("-->    %3d\t", (*exec).io);
    if((*exec).id==0)
        printf("-->       \t");



    printf("-->\t        ");
    for(i=n; i>0; i--){
        if((*esp).ptr[i-1].id!=0)
            printf("%3d    ", (*esp).ptr[i-1].io);
        if((*esp).ptr[i-1].id==0)
            printf("       ");
    }
    printf("   -->");
    printf("\n");
}

void imprimeFCFS(FCFS *ptrx, int n){
    int i;
    printf("\n   Q1\t");
    for(i=n; i>0; i--){
        if((*ptrx).ptr[i-1].id!=0)
            printf("  P%d\t", (*ptrx).ptr[i-1].id);
        if((*ptrx).ptr[i-1].id==0)
            printf("    \t");
    }
    printf("\nBurst\t");

    for(i=n; i>0; i--){
        if((*ptrx).ptr[i-1].id!=0)
            printf(" %3d\t", (*ptrx).ptr[i-1].burst);
        if((*ptrx).ptr[i-1].id==0)
            printf("    \t");
    }
    printf("\n  I/O\t");

    for(i=n; i>0; i--){
        if((*ptrx).ptr[i-1].id!=0)
            printf(" %3d\t", (*ptrx).ptr[i-1].io);
        if((*ptrx).ptr[i-1].id==0)
            printf("    \t");
    }
    printf("\n");

}

void imprimeTerm(TERM *ptrx,int n){
    int i;
    printf("\n TERM\t");

    for(i=n; i>0; i--){
        if((*ptrx).ptr[i-1].id!=0&&i>0)
            printf("  P%d\t", (*ptrx).ptr[i-1].id);
        if((*ptrx).ptr[i-1].id==0&&i>0)
            printf("    \t");
    }
    printf("\nBurst\t");

    for(i=n; i>0; i--){
        if((*ptrx).ptr[i-1].id!=0&&i>0)
            printf(" %3d\t", (*ptrx).ptr[i-1].burst);
        if((*ptrx).ptr[i-1].id==0&&i>0)
            printf("    \t");
    }
    printf("\n  I/O\t");

    for(i=n; i>0; i--){
        if((*ptrx).ptr[i-1].id!=0&&i>0)
            printf(" %3d\t", (*ptrx).ptr[i-1].io);
        if((*ptrx).ptr[i-1].id==0&&i>0)
            printf("    \t");
    }
    printf("\n");
}

void imprimeTudo(RR *Q0, FCFS *Q1, TERM *T, execucao *exec, espera *esp, int n,int contA, int cont){
        int i;
        cabecalho(n,1);
        imprimeRR(Q0,n,exec,esp,contA, cont);
        cabecalho(n,2);
        imprimeFCFS(Q1,n);
        cabecalho(n,2);
        imprimeTerm(T,n);
        for(i=0;i<131;i++) printf("*");
}

void RR_exec(RR *Q0, execucao *exec){
    int i;
    (*exec).id    = (*Q0).ptr[0].id;
    (*exec).burst = (*Q0).ptr[0].burst;
    (*exec).io    = (*Q0).ptr[0].io;
    (*exec).cpu   = (*Q0).ptr[0].cpu;
    (*exec).temp  = 10;
    for(i=0;i<(*Q0).n-1;i++)
        (*Q0).ptr[i]= (*Q0).ptr[i+1];
    if((*Q0).n>0){
        (*Q0).ptr[(*Q0).n-1].id    = 0;
        (*Q0).ptr[(*Q0).n-1].burst = 0;
        (*Q0).ptr[(*Q0).n-1].io    = 0;
        (*Q0).ptr[(*Q0).n-1].cpu   = 0;
        (*Q0).n--;
    }
}

void exec_esp(RR *Q0, execucao *exec, espera *esp){
        (*esp).ptr[(*esp).n].id    = (*exec).id;
        (*esp).ptr[(*esp).n].burst = (*exec).burst;
        (*esp).ptr[(*esp).n].io    = (*exec).io;
        (*esp).ptr[(*esp).n].cpu   = (*exec).cpu;
        (*esp).ptr[(*esp).n].temp  = 20;
        (*esp).n++;
        (*exec).id    =0;
        (*exec).burst =0;
        (*exec).io    =0;
        (*exec).cpu   =0;
}

void esp_RR(RR *Q0, FCFS *Q1, execucao *exec, espera *esp){
        int i;
        (*Q0).ptr[(*Q0).n].id    = (*esp).ptr[0].id;
        (*Q0).ptr[(*Q0).n].burst = (*esp).ptr[0].burst;
        (*Q0).ptr[(*Q0).n].io    = (*esp).ptr[0].io;
        (*Q0).ptr[(*Q0).n].cpu   = (*esp).ptr[0].cpu;
        (*Q0).ptr[(*Q0).n].burst = (*esp).ptr[0].cpu;
        (*Q0).ptr[(*Q0).n].io--;
        (*Q0).n++;
        for(i=0;i<(*esp).n-1;i++)
            (*esp).ptr[i]= (*esp).ptr[i+1];
        (*esp).ptr[(*esp).n-1].id    = 0;
        (*esp).ptr[(*esp).n-1].burst = 0;
        (*esp).ptr[(*esp).n-1].io    = 0;
        (*esp).ptr[(*esp).n-1].cpu   = 0;
        (*esp).n--;
}

void exec_FCFS(RR *Q0, FCFS *Q1, execucao *exec){
        (*Q1).ptr[(*Q1).n].id    = (*exec).id;
        (*Q1).ptr[(*Q1).n].burst = (*exec).burst;
        (*Q1).ptr[(*Q1).n].io    = (*exec).io;
        (*Q1).ptr[(*Q1).n].cpu   = (*exec).cpu;
        (*Q1).ptr[(*Q1).n].temp  = 25;
        (*Q1).n++;
        (*exec).id    =0;
        (*exec).burst =0;
        (*exec).io    =0;
        (*exec).cpu   =0;
}

void FCFS_RR(RR *Q0, FCFS *Q1){
        int i;
        (*Q0).ptr[(*Q0).n].id    = (*Q1).ptr[0].id;
        (*Q0).ptr[(*Q0).n].burst = (*Q1).ptr[0].burst;
        (*Q0).ptr[(*Q0).n].io    = (*Q1).ptr[0].io;
        (*Q0).ptr[(*Q0).n].cpu   = (*Q1).ptr[0].cpu;
        (*Q0).n++;
        for(i=0;i<(*Q1).n-1;i++)
            (*Q1).ptr[i]= (*Q1).ptr[i+1];
        (*Q1).ptr[(*Q1).n-1].id    = 0;
        (*Q1).ptr[(*Q1).n-1].burst = 0;
        (*Q1).ptr[(*Q1).n-1].io    = 0;
        (*Q1).ptr[(*Q1).n-1].cpu   = 0;
        (*Q1).n--;
}

void exec_term(RR *Q0, TERM *T, execucao *exec){
        (*T).ptr[(*T).n].id    = (*exec).id;
        (*T).ptr[(*T).n].burst = (*exec).burst;
        (*T).ptr[(*T).n].io    = (*exec).io;
        (*T).ptr[(*T).n].cpu   = (*exec).cpu;
        (*T).n++;
        (*exec).id    =0;
        (*exec).burst =0;
        (*exec).io    =0;
        (*exec).cpu   =0;
}

int main(){

    int   n, i,x, aux1, aux2, cont=0,contA=0; 
    RR   Q0;
    FCFS Q1;
    TERM  T;
    execucao exec;
    espera   esp;

    printf("Digite o numero de processos de Q0: ");
    scanf("%d", &n);
    printf("\n");

    Q0.ptr=(processo*)malloc(n*sizeof(processo));
    Q1.ptr=(processo*)malloc(n*sizeof(processo));
    T.ptr =(processo*)malloc(n*sizeof(processo));
    esp.ptr=(processo*)malloc(n*sizeof(processo));

    for(i=0; i<n; i++){
        Q0.ptr[i].id    = 0;
        Q0.ptr[i].burst = 0;
        Q0.ptr[i].io    = 0;
    }
    Q0.n=0;
    for(i=0; i<n; i++){
        Q1.ptr[i].id    = 0;
        Q1.ptr[i].burst = 0;
        Q1.ptr[i].io    = 0;
    }
    Q1.n=0;
    for(i=0; i<n; i++){
        T.ptr[i].id    = 0;
        T.ptr[i].burst = 0;
        T.ptr[i].io    = 0;
    }
    T.n =0;
    for(i=0; i<n; i++){
        esp.ptr[i].id    = 0;
        esp.ptr[i].burst = 0;
        esp.ptr[i].io    = 0;
        esp.ptr[i].cpu   = 0;
    }
    esp.n =0;
    exec.id    = 0;
    exec.burst = 0;
    exec.io    = 0;

    printf("Digite a duracao do surto de CPU(ms) e o numero de operacoes de E/S de cada processo: \n");
    for(i=0; i<n; i++){
        printf("P%d -->", i+1);
        printf("Burst: ");
        scanf("%d", &aux1);
        do{
        printf("\tI/O: ");
        scanf("%d", &aux2);
        if(aux2>=aux1)
            printf("\nInvalido! I/O maior ou igual a Burst\n");
        }while(aux2>=aux1);
        Q0.ptr[i].id    = i+1;
        Q0.ptr[i].burst = aux1;
        Q0.ptr[i].cpu   = aux1;
        Q0.ptr[i].io    = aux2;
        Q0.n            = i+1;
        printf("\n");
    }
    for(i=0;i<131;i++) printf("*");

     do{
            if(Q0.n>0&&exec.id==0){
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
                contA=cont;
                RR_exec(&Q0,&exec);
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
            }
            if(exec.io>0&&exec.burst==0){
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
                contA=cont;
                exec_esp(&Q0,&exec,&esp);
                if(Q0.n>0&&exec.id==0)
                    RR_exec(&Q0,&exec);
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
            }
            if(esp.ptr[0].id!=0&&esp.ptr[0].temp==0){
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
                contA=cont;
                esp_RR(&Q0,&Q1,&exec,&esp);
                if(Q0.n>0&&exec.id==0)
                    RR_exec(&Q0,&exec);
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
            }
            if(exec.id!=0&&exec.temp==0&&exec.burst!=0){
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
                contA=cont;
                if(Q0.n==0&&Q1.n==0)
                    exec.temp=10;
                else{
                    exec_FCFS(&Q0,&Q1,&exec);
                }
                if(Q0.n>0&&exec.id==0)
                    RR_exec(&Q0,&exec);
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
            }
            if((Q1.ptr[0].temp==0&&Q1.ptr[0].id!=0)||(Q0.n==0&&exec.id==0&&Q1.ptr[0].temp>=0&&Q1.ptr[0].id!=0)){
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
                contA=cont;
                FCFS_RR(&Q0,&Q1);

                if(Q0.n>0&&exec.id==0)
                    RR_exec(&Q0,&exec);
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
            }
            if(exec.io==0&&exec.id!=0&&exec.burst==0){
                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
                contA=cont;
                exec_term(&Q0,&T, &exec);
                if(Q0.n>0&&exec.id==0)
                    RR_exec(&Q0,&exec);
                if(Q0.n==0&&exec.id==0&&Q1.n>0){
                    FCFS_RR(&Q0,&Q1);
                    RR_exec(&Q0,&exec);
                }

                imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
            }
            if(T.n==n){
               imprimeTudo(&Q0,&Q1,&T,&exec,&esp,n,contA, cont);
               goto fim;
            }
            if(exec.burst>0)
                exec.burst--;
            if(exec.temp>0)
                exec.temp--;
            for(i=0;i<esp.n;i++)
                if(esp.ptr[i].temp>0)
                    esp.ptr[i].temp--;
            for(i=0;i<Q1.n;i++)
                if(Q1.ptr[i].temp>0)
                    Q1.ptr[i].temp--;
            cont++;
     }while(cont<500);

    fim :
    free(Q0.ptr);
    free(Q1.ptr);
    free(T.ptr);
    free(esp.ptr);

    printf("\n");
    system("pause");

    return 0;
}
