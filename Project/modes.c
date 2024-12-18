#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"functions.h"

void Modo_P(char *s, park_list* l)
{
    int capacity = 0;
    float x = 0, y = 0, z = 0;
    park* new_park = NULL;
    char ** ret = NULL;

    switch (Count_Args(s))
    {
    case 1:
        Print_park(l);
        break;
    case 6:
        ret = Get_Name(s+1);
        if(sscanf(ret[1], "%d %f %f %f", &capacity, &x, &y, &z) != 4)
        {
            printf(NUM_ARGUMENTS);
            break;
        }
        if(l->info != NULL && Find_park_in_lis(ret[0], l) != NULL)  
        {
            printf(PARK_EXISTS, ret[0]);
            break;
        }
        if(capacity <= 0)  
        {
            printf(CAP_INVALID, capacity);
            break;
        }
        if(x <= 0 || y <= 0 || z <= 0)  
        {
            printf(COST_INVALID);
            break;
        }
        if(!(z > y && y > x))
        {
            printf(COST_INVALID);
            break;
        }
        if(Get_park_number(l) >= NUM_MAX_PARK)  
        {
            printf(LIMIT_PARKS);
            break;
        }
        new_park = Create_Park(ret[0], capacity, x, y, z);
        Add_park_to_list(new_park, l);
        free(ret[0]);
        free(ret);
        break;
    default:
        printf(NUM_ARGUMENTS);
        break;
    }
}

void Modo_E(char* s, park_list* l)
{
    char** ret = NULL;
    char* mat = NULL;
    char* new_mat = NULL;
    char* date = NULL;
    char* time_in = NULL;
    entry* new_entry = NULL;
    park * p = NULL;

    if(Count_Args(s) != 5)
    {
        printf(NUM_ARGUMENTS);
        return;
    }
    ret = Get_Name(s+1);
    p = Find_park_in_lis(ret[0], l);
    if(l->info != NULL && p == NULL)  
    {
        printf(PARK_NOT_EXISTS, ret[0]);
        free(ret[0]);
        free(ret);
        return;
    }
    if(p->ocupation == p->capacity)  
    {
        printf(PARK_FULL, ret[0]);
        free(ret[0]);
        free(ret);
        return;
    }
    free(ret[0]);
    mat = malloc(sizeof(char) * MAT);
    date = malloc(sizeof(char) * DATE);
    time_in = malloc(sizeof(char) * TIME);
    if(mat == NULL || date == NULL || time_in == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    if(sscanf(ret[1], "%s %s %s", mat, date, time_in) != 3)  
    {
        printf(NUM_ARGUMENTS);
        free(ret);
        free(mat);
        free(date);
        free(time_in);
        return;
    }
    free(ret);
    new_mat = Build_new_mat(mat);
    if(!Check_dash(mat) || !Check_num_and_let(new_mat)) 
    {
        printf(INVALID_MAT, mat);
        free(date);
        free(time_in);
        return; 
    }
    if(Search_in_Parks(l, new_mat) != NULL)  
    {
        printf(CAR_ERROR, mat);
        free(date);
        free(mat);
        free(time_in);
        return;
    }
    free(mat);
    time * t = date_and_hour_to_int(date, time_in); 
    free(date);
    free(time_in);
    if(t == NULL)
    {
        printf(TIME_ERROR);
        return;
    }
    if(Time_diference(t, Find_last_entry(p)) < 0)
    {
        printf(TIME_ERROR);
        return;

    }
    new_entry = Create_entry(new_mat, t);
    Add_entry_to_list(new_entry, p);
    printf("%s %d\n", p->name, (p->capacity - p->ocupation));
}

void Modo_S(char *s, park_list* l)
{
    char** ret = NULL;
    char* mat = NULL;
    char* date = NULL;
    char* new_mat = NULL;
    char* time_out = NULL;
    char* time_in = NULL;
    park* p = NULL;

    if(Count_Args(s) != 5)
    {
        printf(NUM_ARGUMENTS);
        return;
    }
    ret = Get_Name(s+1);
    p = Find_park_in_lis(ret[0], l);
    if(l->info != NULL && p == NULL) 
    {
        printf(PARK_NOT_EXISTS, ret[0]);
        free(ret[0]);
        free(ret);
        return;
    }
    free(ret[0]);
    mat = malloc(sizeof(char) * MAT);
    date = malloc(sizeof(char) * DATE);
    time_out = malloc(sizeof(char) * TIME);
    if(mat == NULL || date == NULL || time_out == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    if(sscanf(ret[1], "%s %s %s", mat, date, time_out) != 3)  
    {
        printf(NUM_ARGUMENTS);
        free(ret);
        free(mat);
        free(date);
        free(time_out);
        exit(-1);
    }
    free(ret);
    new_mat = Build_new_mat(mat);
    if(!Check_dash(mat) || !Check_num_and_let(new_mat))  
    {
        printf(INVALID_MAT, mat);
        free(mat);
        free(new_mat);
        free(date);
        free(time_out);
        return;
    }
    entry* e = Find_open_entry(p, new_mat);
    if(e == NULL) 
    {
        printf(CARR_ERROR, mat);
        free(mat);
        free(date);
        free(time_out);
        return;
    }
    free(mat);
    time * t = date_and_hour_to_int(date, time_out); 
    free(date);
    if(t == NULL)
    {
        printf(TIME_ERROR);
        free(time_out);
        return;
    }
    if(Time_diference(t, Find_last_entry(p)) < 0)
    {
        printf(TIME_ERROR);
        free(time_out);
        return;
    }
    e->out = t;
    p->ocupation--;
    Calculate_cost(e, p);
    new_mat = Build_old_mat(e->reg);
    time_out = Print_Date_and_Time(e->out);
    time_in = Print_Date_and_Time(e->in);
    printf("%s %s %s %.2f\n", new_mat, time_in, time_out, e->cost);
    free(time_out);
    free(time_in);
    free(new_mat);
}


void Modo_V(char *s, park_list* l)
{
    char* mat = NULL;
    char* new_mat = NULL;
    char* time_in = NULL;
    char* time_out = NULL;
    ordered* new_list = NULL;
    ordered* tempi = NULL;

    if(Count_Args(s) != 2)
    {
        printf(NUM_ARGUMENTS);
        return;
    }
    mat = malloc(sizeof(char) * MAT);
    if(mat == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    if(sscanf(s+1, "%s", mat) != 1)  
    {
        printf(NUM_ARGUMENTS);
        free(mat);
        return;
    }
    new_mat = Build_new_mat(mat);
    if(!Check_dash(mat) || !Check_num_and_let(new_mat)) 
    {
        printf(INVALID_MAT, mat);
        free(mat);
        free(new_mat);
        return;
    }
    if(!Search_in_Parks_out(l, new_mat)) 
    {
        printf(NOT_REG, mat);
        free(mat);
        free(new_mat);
        return;
    }
    new_list = List_ordered_v(l, new_mat);
    for(tempi = new_list; tempi != NULL; tempi = tempi->next)
    {
        time_in = Print_Date_and_Time(tempi->info->in);
        if(tempi->info->out == NULL)
            printf("%s %s\n", tempi->park->name, time_in);
        else
        {
            time_out = Print_Date_and_Time(tempi->info->out);
            printf("%s %s %s\n", tempi->park->name, time_in, time_out);
            free(time_out);
        }
        free(time_in);
    }
}

void Modo_F(char* s, park_list* l)
{
    char** ret = NULL;
    char* date = NULL;
    park* p = NULL;
    float soma = 0.0;
    entries_list* ord = NULL;
    entries_list* temp = NULL;
    time* data_0_0 = Init_time();
    time* data_23_59 = Init_time();

    switch (Count_Args(s))
    {
    case 2:
        ret = Get_Name(s+1);
        p = Find_park_in_lis(ret[0], l);
        if(l->info != NULL && p == NULL)  
        {
            printf(PARK_NOT_EXISTS, ret[0]);
            break;
        }
        ord = Order_list_by_out_date(p->cars);
        for(temp = ord; temp != NULL && temp->info != NULL; temp = temp->next)
        {
            if(temp == ord)
            {
                data_0_0->day = temp->info->out->day;
                data_0_0->month = temp->info->out->month;
                data_0_0->year = temp->info->out->year;
                data_23_59->day = temp->info->out->day;
                data_23_59->month = temp->info->out->month;
                data_23_59->year = temp->info->out->year;
                data_23_59->hour = 23;
                data_23_59->minute = 59;
            }
            if(Time_diference(temp->info->out, data_0_0) >= 0 && Time_diference(temp->info->out, data_23_59) <= 0)
                soma += temp->info->cost;
            else
            {
                printf("%02d-%02d-%02d %.2f\n", data_0_0->day, data_0_0->month, data_0_0->year, soma);
                data_0_0->day = temp->info->out->day;
                data_0_0->month = temp->info->out->month;
                data_0_0->year = temp->info->out->year;
                data_23_59->day = temp->info->out->day;
                data_23_59->month = temp->info->out->month;
                data_23_59->year = temp->info->out->year;
                soma = temp->info->cost;
            }
        }
        if(ord != NULL && ord->info != NULL)
            printf("%02d-%02d-%02d %.2f\n", data_0_0->day, data_0_0->month, data_0_0->year, soma);
        break;
    case 3:
        ret = Get_Name(s+1);
        date = malloc(sizeof(char) * DATE);
        if(sscanf(ret[1], "%s", date) != 1)
        {
            printf(NUM_ARGUMENTS);
            free(date);
            free(ret[0]);
            free(ret);
            break;
        }
        p = Find_park_in_lis(ret[0], l);
        if(l->info != NULL && p == NULL)  // no caso do nome do parque não existir
        {
            printf(PARK_NOT_EXISTS, ret[0]);
            free(ret[0]);
            free(ret);
            break;
        }
        if(!verify_date(date))  // Verifica se a data é válida e posterior à última entrada ou saída
        {
            printf(TIME_ERROR);
            free(ret[0]);
            free(ret);
            free(date);
            break;
        }
        time* t = Init_time();
        t->day = Time_to_int(date);
        t->month = Time_to_int(date + 3);
        t->year = Year_to_int(date + 6);
        if(Time_diference(t, Find_last_entry(p)) > 0)
        {
            printf(TIME_ERROR);
            break;
        }
        ord = Order_list_by_out_date(p->cars);
        int flag = 0;
        for(temp = ord; temp != NULL && temp->info != NULL; temp = temp->next)
        {
            if(temp == ord)
            {
                data_0_0->day = t->day;
                data_0_0->month = t->month;
                data_0_0->year = t->year;
                data_23_59->day = t->day;
                data_23_59->month = t->month;
                data_23_59->year = t->year;
                data_23_59->hour = 23;
                data_23_59->minute = 59;
            }
            if(Time_diference(temp->info->out, data_0_0) >= 0 && Time_diference(temp->info->out, data_23_59) <= 0)
            {
                flag = 1;
                char* new_mat = Build_old_mat(temp->info->reg);
                printf("%s %02d:%02d %.2f\n", new_mat, temp->info->out->hour, temp->info->out->minute, temp->info->cost);
                free(new_mat);
            }
            else
            {
                if(flag == 1)
                    break;
                
            }
        }
        break;
    default:
        printf(NUM_ARGUMENTS);
        break;
    }
    free(data_0_0);
    free(data_23_59);
}

park_list* Modo_R(char* s, park_list* l)
{
    char** ret = NULL;
    park* p = NULL;
    park_list *temp = NULL;
    park_list *ord = NULL;
    ret = Get_Name(s+1);
    p = Find_park_in_lis(ret[0], l);
    if(l->info != NULL && p == NULL)  // no caso do nome do parque não existir
    {
        printf(PARK_NOT_EXISTS, ret[0]);
        free(ret[0]);
        free(ret);
        return l;
    }
    l = Remove_park(p, l);
    ord= Order_parks_by_name(l);
    for(temp = ord; temp != NULL && temp->info != NULL; temp = temp->next)
    {
        printf("%s\n", temp->info->name);
    }
    free(ret[0]);
    free(ret);
    return l;
}

