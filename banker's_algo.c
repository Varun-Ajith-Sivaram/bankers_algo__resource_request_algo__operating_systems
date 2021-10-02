#include<stdio.h>
#include<stdlib.h>

void get_details(int x,int y,int[x],int[x][y],int[x][y],int[y]);
void calc_need(int x,int y,int[x][y],int[x][y],int[x][y]);
int* calc_total_resources(int x,int y,int[x][y],int[y]);
void disp_total_resources(int x,int[x]);
void disp_available_resources(int y,int[y]);
void disp_alloc_details(int x,int y,int[x],int[x][y]);
void disp_max_details(int x,int y,int[x],int[x][y]);
void disp_need_details(int x,int y,int[x],int[x][y]);
int* bankers_algo(int x,int y,int[x],int[x][y],int[x][y],int[y]);
void disp_safe_sequence(int x,int[x]);

int i,j,k,l,m,total,res_total;

void main()
{
    printf("\tImplementation of Banker's Algorithm\n\n");
    
    printf("\n Enter the total number of processes: ");
    scanf("%d",&total);
    
    int Process[total];
    
    printf("\n Enter the total number of resource types: ");
    scanf("%d",&res_total);
    printf("\n");
    
    int Allocated[total][res_total];
    int Max_resources[total][res_total];
    int Need_resources[total][res_total];
    int Available[res_total];
    
    for(i =0 ; i < res_total; i++)
    {
        Available[i] = 0;
    }
    
    get_details(total,res_total,Process,Allocated,Max_resources,Available);
    
    int *sum;
    sum = calc_total_resources(total,res_total,Allocated,Available);
    
    disp_total_resources(res_total,sum);
    
    disp_available_resources(res_total,Available);
    
    disp_alloc_details(total,res_total,Process,Allocated);
    disp_max_details(total,res_total,Process,Max_resources);
    
    calc_need(total,res_total,Allocated,Max_resources,Need_resources);
    disp_need_details(total,res_total,Process,Need_resources);
    
    int *seq;
    seq = bankers_algo(total,res_total,Process,Allocated,Need_resources,Available);
    disp_safe_sequence(total,seq);
}

void get_details(int x,int y,int p[x],int alloc[x][y],int max[x][y],int avail[y])
{
    for(i = 0; i < x; i++)
    {
        if(i == 0)
        {
            printf("\n\tEnter the details of available resources: \n");
            
            for(j = 0; j < y; j++)
            {
                printf("\n\t   Available instances of Resource %d: ",j+1);
                scanf("%d",&avail[j]);
            }
            printf("\n\n");
        }
        
        printf("\n\tEnter the process id: ");
        scanf("%d",&p[i]);
        
        printf("\n\t   Enter details of allocated resources of Process %d:\n",p[i]);
        
        for(j = 0; j < y; j++)
        {
            printf("\n\t\tAllocated instances of Resource %d: ",j+1);
            scanf("%d",&alloc[i][j]);
        }
        printf("\n");
        
        printf("\n\t   Enter details of maximum resources required by Process %d:\n",p[i]);
        
        for(j = 0; j < y; j++)
        {
            printf("\n\t\tMaximum required instances of Resource %d: ",j+1);
            scanf("%d",&max[i][j]);
        }
        printf("\n");
    }
}

void calc_need(int x,int y,int alloc[x][y],int max[x][y],int need[x][y])
{
    for(i=0;i<x;i++)
    {
        for(j=0;j<y;j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

int* calc_total_resources(int x,int y,int alloc[x][y],int avail[y])
{
    int *s = malloc(sizeof(y));
    
    for(j = 0; j < y; j++)
    {
        s[j] = 0;
    }
    
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            if(i == 0)
            {
                s[j] = s[j] + alloc[i][j] + avail[j];  
            }
            
            else
                s[j] += alloc[i][j];
        }
    }
    
    return(s);
}

void disp_total_resources(int x,int s[x])
{
    printf("\n\n\tTotal Resources:\n");
    
    for(i = 0; i < x; i++)
    {
        printf("\n\t\t\tResource %d: %d",i+1,s[i]);    
    }
    
    printf("\n\n");
}

void disp_available_resources(int y,int avail[y])
{
    printf("\n\n\tAvailable resources:\n");
    
    for(i = 0; i < y; i++)
    {
        printf("\n\t\t\tResource %d: %d",i+1,avail[i]);    
    }
    
    printf("\n\n");
}

void disp_alloc_details(int x,int y,int p[x],int alloc[x][y])
{
    printf("\n");
    
    printf("\n   Process      Allocated\n");
    
    for(i = 0; i < 1; i++)
    {   
        printf("\t        ");
        
        for(j = 0; j < y; j++)
        {
            printf("%d  ",j+1);
        }
        
        printf("\n   ________     __________\n");
    }
    
    for(i = 0; i < x; i++)
    {
        printf("     %d\t\t",p[i]);
        
        for(j = 0; j < y; j++)
        {
            printf("%d  ",alloc[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    
}

void disp_max_details(int x,int y,int p[x],int max[x][y])
{
    printf("\n");
    
    printf("\n   Process      Maximum\n");
    
    for(i = 0; i < 1; i++)
    {   
        printf("\t        ");
        
        for(j = 0; j < y; j++)
        {
            printf("%d  ",j+1);
        }
        
        printf("\n   ________     __________\n");
    }
    
    for(i = 0; i < x; i++)
    {
        printf("     %d\t\t",p[i]);
        
        for(j = 0; j < y; j++)
        {
            printf("%d  ",max[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    
}

void disp_need_details(int x,int y,int p[x],int need[x][y])
{
    printf("\n");
    
    printf("\n   Process      Need\n");
    
    for(i = 0; i < 1; i++)
    {   
        printf("\t        ");
        
        for(j = 0; j < y; j++)
        {
            printf("%d  ",j+1);
        }
        
        printf("\n   ________     __________\n");
    }
    
    for(i = 0; i < x; i++)
    {
        printf("     %d\t\t",p[i]);
        
        for(j = 0; j < y; j++)
        {
            printf("%d  ",need[i][j]);
        }
        printf("\n");
    }
    
    printf("\n");
    
}

int* bankers_algo(int x,int y,int p[x],int alloc[x][y],int need[x][y],int avail[y])
{
    int *sequence = malloc(sizeof(x));
    
    for(i=0;i<x;i++)
    {
        sequence[i] = 0;
    }
    
    int executed[x];
    
    for(i = 0; i < x; i++)
    {
        executed[i] = 0;
    }
    
    
    int l = 0,exit_flag = 0,flag = 0,count = 0;
    int process_executed;

    while(1)
    {
        process_executed = 0;
        
        for(i = 0; i < x; i++)    
        {
            if(executed[i] == 0)
            {
                for(j = 0; j < y; j++)
                {
                    if(avail[j] >= need[i][j])
                    {
                        flag = 1;    
                    }
                
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                
                if(flag == 1)
                {
                    executed[i] = 1;
                    sequence[l] = p[i];
                    l++;
                    process_executed = 1;
                    ++count;
                    
                    for(k = 0; k < y; k++)
                    {
                        avail[k] = avail[k] + alloc[i][k];
                    }
                    
                    printf("\n\n\tAvailable resources after executing Process %d: \n",p[i]);
                    
                    for(m = 0; m < y; m++)
                    {
                        printf("\n\t\t\tResource %d: %d",m+1,avail[m]);
                    }
                    
                    printf("\n");
                }
            }
            
            if(count == x)
            {
                exit_flag = 1;
                break;
            }
        }
        
        if(exit_flag == 1)
            {
                printf("\n\n\t   --> System is in safe state!! Deadlock will never occur!!\n");
                break;
            }
        
        else if(process_executed == 0)
        {
            printf("\n\n\t   --> System is in unsafe state!! Deadlock will occur!!\n");
            exit(0);
        }
    }
    
    return(sequence);
}

void disp_safe_sequence(int x,int s[x])
{
    printf("\n\t   --> Safe Sequence: ");
    
    for(i = 0; i < x; i++)
    {
        if(i == 0)
        {
            printf("< %d,  ",s[i]);
        }
        
        else if(i == x-1)
        {
            printf("%d >",s[i]);
        }
        
        else
        {
            printf("%d,  ",s[i]);
        }
    }
}