#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include"functions.h"


time* Init_time()
{
    time* t;
    t = malloc(sizeof(time));
    if (t == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    t->day = 0;
    t->month = 0;
    t->year = 0;
    t->minute = 0;
    t->hour = 0;
    return t;
}


park* Init_park()
{
    park* p;
    p = malloc(sizeof(park)); 
    if (p == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    p->name = NULL;
    p->capacity = 0;
    p->ocupation = 0;
    p->x = 0.0;
    p->y = 0.0;
    p->z = 0.0;
    p->cars = NULL;
    return p;
}


entry* Init_entry()
{
    entry* e;
    e = malloc(sizeof(entry));
    if (e == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    e->reg[0] = '\0';
    e->in = NULL;
    e->out = NULL;
    return e;
}


entries_list* Init_entries_list()
{
    entries_list* e = NULL;
    e = malloc(sizeof(entries_list));
    if(e == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    e->next = NULL;
    e->info = NULL;
    e->prev = NULL;
    return e;
}


park_list* Init_park_list()
{
    park_list* p = NULL;
    p = malloc(sizeof(park_list));
    if (p == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    p->next = NULL;
    p->info = NULL;
    p->prev = NULL;
    return p;
}


ordered* Init_ordered()
{
    ordered* o = NULL;
    o = malloc(sizeof(ordered));
    if(o == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    o->info = NULL;
    o->next = NULL;
    o->park = NULL;
    o->prev = NULL;
    return o;
}


void Add_park_to_list(park *p,  park_list* l)
{
    park_list* temp = l;
    park_list* new = Init_park_list();
    new->info = p;
    if (l->info == NULL)
    {
        l->info = p;
        free(new);
    }
    else
    {
        for (temp = l; temp->next != NULL; temp = temp->next);
        temp->next = new;   
        new->prev = temp;
    }
}

// Função que adiciona uma entrada no fim de uma lista de entradas

void Add_entry_to_list(entry *e, park *p)
{
    entries_list* temp = p->cars;
    entries_list* new = Init_entries_list();
    new->info = e;
    if (p->cars == NULL)
    {
        p->cars = new;
    }
    else
    {
        for (; temp->next != NULL; temp = temp->next);
        temp->next = new;   
        new->prev = temp;
    }
    p->ocupation++;
}


void Print_park(park_list* p)
{
    park_list* temp = p;
    while (temp != NULL && temp->info != NULL)
    {
        printf("%s %d %d\n", temp->info->name, temp->info->capacity, temp->info->capacity - temp->info->ocupation);
        temp = temp->next;
    }
}


park_list* Remove_park(park* p, park_list* l)
{
    park_list* temp = NULL;
    park_list* aux = NULL;
    for(temp = l; temp != NULL; temp = temp->next)
    {
        if(temp->info == p)
        {
            if(temp->prev!= NULL)
                temp->prev->next = temp->next;
            if(temp->next != NULL)
                temp->next->prev = temp->prev;
            if(temp->next == NULL && temp->prev == NULL)
            {
                Free_park(temp->info);
                temp->info = NULL;
            }
            else
            {
                aux = temp->next;
                Free_park_list_cell(temp);
                if(temp == l)
                    return aux;
                else
                    return l;
            }
            return l;
        }
    }
    return l;
}

void Calculate_cost(entry* e, park* p)
{
    int Total_Min = 0;
    float Cost = 0;
    float new_cost = 0;
    int remaining_min = 0;
    int days = 0;
    Total_Min = Time_diference(e->out, e->in);
    if(Total_Min <= 60) 
    {
        Cost = (Total_Min/15) * p->x;
        if(Total_Min % 15 > 0)
            Cost += p->x;
        if(Cost > p->z)
            Cost = p->z;
    }
    if(Total_Min > 60 && Total_Min < 1440) 
    {
        Cost = 4 * p->x + (((Total_Min - 60)/15) * p->y); 
        if((Total_Min - 60) % 15 > 0)
            Cost += p->y;
        if(Cost > p->z)
            Cost = p->z;   
    }
    if(Total_Min >= 1440) 
    {
        days = Total_Min / 1440;
        remaining_min = Total_Min % 1440;
        Cost = days * p->z;
        if(remaining_min <= 60) 
        {
            new_cost += (remaining_min/15) * p->x;
            if(remaining_min % 15 > 0)
                new_cost += p->x;
            if(new_cost > p->z)
                new_cost = p->z;
        }
        else
        {
            new_cost += 4 * p->x + (((remaining_min - 60)/15) * p->y);
            if((remaining_min - 60) % 15 > 0)
                new_cost += p->y;
            if(new_cost > p->z)
                new_cost = p->z;
        }
        Cost += new_cost;
    }
    e->cost = Cost;
}


park* Find_park_in_lis(char* name, park_list* l)
{
    park_list* temp = l;
    for(temp = l; temp != NULL && temp->info != NULL; temp = temp->next)
    {
        if (strcmp(temp->info->name, name) == 0)
        {
            return temp->info;
        }
    }
    return NULL;
}

// Função que verifica se um carro já esteve dentro de um parque, podendo já ter saído.

entry* Find_entry(park* p, char* new)
{
    entries_list* temp = p->cars;
    for(temp = p->cars; temp != NULL; temp = temp->next)
    {
        if(strcmp(temp->info->reg, new) == 0)
            return temp->info;
    }
    return NULL;
}


entry* Find_open_entry(park* p, char* new)
{
    entries_list* temp = p->cars;
    for(temp = p->cars; temp != NULL; temp = temp->next) 
    {
        if(strcmp(temp->info->reg, new) == 0) 
        {
            if(temp->info->out == NULL) 
                return temp->info;
        }
    }
    return NULL;
}

time* Find_last_entry(park* p)
{
    entries_list* temp = p->cars;
    time* max_in = NULL, *max_out = NULL;
    for(temp = p->cars; temp != NULL; temp = temp->next)
    {   
        if(max_in == NULL)
        {
            max_in = temp->info->in;
        }
        else
        {
            if (Time_diference(max_in, temp->info->in) < 0)
                max_in = temp->info->in;
        }

        
        if(max_out == NULL)
        {
            if(temp->info->out != NULL)
                max_out = temp->info->out;
        }
        else
            if(Time_diference(max_out, temp->info->out) < 0)
                max_out = temp->info->out;   
    }
    if(Time_diference(max_in, max_out) > 0)
        return max_in;
    else
        return max_out;
}

int Count_Args(char* str)
{
	int i = 0, args = 0, txt = 0, special = 0;
	while(i < (int) strlen(str))
    {
		if(!special && str[i] == '"')
        {
			special = 1;
			i++;
			continue;
		}
		if(special){
			if(str[i] == '"')
            {
				special = 0;
				args++;
				i++;
				continue;
			}
			else
            {
				i++;
				continue;
			}
		}
		if(Is_Text(str[i]))
        {
			i++;
			if(txt == 0)
            {
				args++;
				txt = 1;
			}
			continue;
		}
		else
        {
			txt = 0;
			i++;
		}
	}
	return args;
}


int Check_full(park* p)
{
    if (p->ocupation >= p->capacity)
    {
        return TRUE;
    }
    return FALSE;
}


int Get_park_number(park_list* l)
{
    park_list* temp = l;
    int count = 0;
    for (temp = l; temp != NULL; temp = temp->next)
    {
        count++;
    }
    return count;
}

// Função que garante que há pelo menos um par de digitos e um par de letras na matricula

int Check_num_and_let(char *new)
{
    int i, num = 0, let = 0;
    for(i = 0; i < NEW_MAT/2; i++)
    {
        if(isdigit(new[i*2]))
            num = 1;
        if(isalpha(new[i*2]))
            let = 1;
    }
    for(i = 0; i < NEW_MAT/2; i++)
    {
        if(!Check_equal(new + (i*2)))
            return FALSE;
    }
    if(num == 1 && let == 1)
        return TRUE;
    else
        return FALSE;
}

int Check_dash(char* reg)
{
    if(reg[2] != '-' || reg[5] != '-')
    {
        return FALSE;
    }
    return TRUE;
}

// Função que assegura que há sempre um par de letras ou digitos na matricula e que não há letra e digito

int Check_equal(char* num)
{
    if(num[0] >= 'A' && num[0] <= 'Z')
    {
        if (num[1] >= 'A' && num[1] <= 'Z')
        {
            return TRUE;
        }
    }
    if(num[0] >= '0' && num[0] <= '9')
    {
        if (num[1] >= '0' && num[1] <= '9')
        {
            return TRUE;
        }
    }
    return FALSE;
}


char* Build_new_mat(char* reg)
{
    int j;
    unsigned long i;
    char* new = malloc(sizeof(char) * NEW_MAT);
    if(new == NULL)
    {
        puts(MEMO_ERR_MSG);
        return NULL;
    }
    for(i = 0, j = 0; i < strlen(reg) && j < NEW_MAT - 1; i++, j++)
    {
        if(i == 2 || i == 5)
            i++;
        new[j] = reg[i];
    }
    new[j] = '\0';
    return new;
}


char* Build_old_mat(char* reg)
{
    int j;
    unsigned long i;
    char* old = malloc(sizeof(char) * MAT);
    if(old == NULL)
    {
        puts(MEMO_ERR_MSG);
        return NULL;
    }
    for(i = 0, j = 0; i < strlen(reg) && j < MAT - 1; i++, j++)
    {
        if(i == 2 || i == 4)
            old[j++] = '-';
        old[j] = reg[i];
    }
    old[j] = '\0';
    return old;
}


int Time_to_int(char * m)
{
    return ((m[0] - '0') * 10) + (m[1] - '0');
}


int Year_to_int(char * Year)
{
    return Time_to_int(Year) * 100 + Time_to_int(Year + 2);
}


int Day_in_month(int m)
{
    switch (m)
    {
    case 2:
        return 28;
    
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    
    default:
        return -1;
    }
}


int Days_in_months_before(int m)
{
    int i, days;
    days = 0;
    for(i = 1; i < m; i++)
    {
        days += Day_in_month(i);
    }
    return days;
}

int Time_diference(time* t1, time* t2)
{
    int in, out;
    if(t1 == NULL)
        in = 0;
    else
        in = t1->hour * 60 + t1->minute + t1->day * 24 * 60 + 
        Days_in_months_before(t1->month) * 24 * 60 + t1->year * 365 * 24 * 60;
    if(t2 == NULL)
        out = 0;
    else
        out = t2->hour * 60 + t2->minute + t2->day * 24 * 60 +
        Days_in_months_before(t2->month) * 24 * 60 + t2->year * 365 * 24 * 60;
    return in - out;
}

park* Create_Park(char *name, int capacity, float x, float y, float z)
{
    park* p = Init_park();
    p->name = malloc(sizeof(char) * (strlen(name) + 1));
    if(p->name == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    strcpy(p->name, name);
    p->capacity = capacity;
    p->x = x;
    p->y = y;
    p->z = z;
    return p;
}

entry* Create_entry(char* new, time* in)
{
    entry* e = Init_entry();
    strcpy(e->reg, new);
    e->in = in;
    return e;
}

int Is_Text(char c)
{
	if(c >= '0' && c <= '9')
		return TRUE;
	if(c >= 'A' && c <= 'Z')
		return TRUE;
	if(c >= 'a' && c <= 'z')
		return TRUE;
	if(c == '.' || c == '-' || c == ':')
		return TRUE;
	return FALSE;
}

int verify_date(char* s)
{
    int i,j,k;
    if(sscanf(s, "%d-%d-%d", &i, &j, &k) != 3)
        return FALSE;
    if(j < 1 || j > 12 || i < 1 || i > Day_in_month(j) || k < 0)
        return FALSE;
    return TRUE;
}

int verify_hour(char* s)
{
    int i,j;
    if(sscanf(s, "%d:%d", &i, &j) != 2)
        return FALSE;
    if(i < 0 || i > 23 || j < 0 || j > 59)
        return FALSE;
    return TRUE;
}

time* date_and_hour_to_int(char* date, char* hour)
{
    if(!verify_date(date) || !verify_hour(hour))
    {
        return NULL;
    }
    time* t = malloc(sizeof(time));
    if(t == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    t->day = Time_to_int(date);
    t->month = Time_to_int(date + 3);
    t->year = Year_to_int(date + 6);
    sscanf(hour, "%d:%d", &t->hour, &t->minute);
    return t;

}

char* Print_Date_and_Time(time* t)
{
    char* s = malloc(sizeof(char) * (DATE + TIME));
    if(s == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    sprintf(s, "%02d-%02d-%04d %02d:%02d", t->day, t->month, t->year, t->hour, t->minute);
    return s;
}

char** Get_Name(char* str)
{
    int i = 0, size = 0, begin = 0;
    char* new_str = NULL;
    char** ret = NULL;
    ret = malloc(sizeof(char*) * 2);
    if(ret == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }
    while(!Is_Text(str[i]) && str[i] != '"')
    {
        i++;
    }
    begin = i;
    if(str[i] == '"')
    {
        i++;
        size++;
        while(i < (int) strlen(str) && str[i+begin] != '"')
        {
            size++;
            i++;
        }
        new_str = malloc(sizeof(char) * (size + 1));
        i = 0;
        while(i < (int) strlen(str) && str[i + 1 + begin] != '"')
        {
            new_str[i] = str[i + 1 + begin];
            i++;
        }
        new_str[i] = '\0';
        ret[0] = new_str;
        ret[1] = str + begin + i + 2;
    }
    else
    {
        while(i < (int) strlen(str) && Is_Text(str[i]))
        {
            size++;
            i++;
        }
        new_str = malloc(sizeof(char) * (size + 1));
        i = 0;
        while(i < (int) strlen(str) && Is_Text(str[i + begin]))
        {
            new_str[i] = str[i+begin];
            i++;
        }
        new_str[i] = '\0';
        ret[0] = new_str;
        ret[1] = str + begin + i;
    }
    return ret;
}


// Função que chame o Find_open_entry para todos os parques, ou seja, vê se o carro já entrou em algum parque e ainda não saiu.

entry* Search_in_Parks(park_list* l, char* new)
{
    park_list* temp = l;
    entry* e = NULL;
    for(temp = l; temp != NULL; temp = temp->next)
    {
        e = Find_open_entry(temp->info, new);
        if(e != NULL)
            return e;
    }
    return NULL;
}


entry* Search_in_Parks_out(park_list* l, char* new)
{
    park_list* temp = l;
    entry* e = NULL;
    for(temp = l; temp != NULL && temp->info != NULL; temp = temp->next)
    {
        e = Find_entry(temp->info, new);
        if(e != NULL)
            return e;
    }
    return NULL;
}


// Função que retorna uma cópia de uma lista de parques ordenados pelo nome

park_list* Order_parks_by_name(park_list* l)
{
    park_list* temp = l;
    park_list* new = Init_park_list();
    for(temp = l; temp != NULL && temp->info != NULL; temp = temp->next)
    {
        new = Add_to_list_in_order_name(new, temp->info);
    }
    return new;
}


// Função que vai devolver uma copia de uma lista de entradas ordenada por data e hora de saída

entries_list* Order_list_by_out_date(entries_list* l)
{
    entries_list* temp = l;
    entries_list* new = Init_entries_list();
    for(temp = l; temp != NULL; temp = temp->next)
    {
        if(temp->info != NULL && temp->info->out != NULL)
            new = Add_to_list_in_order_out(new, temp->info);
    }
    return new;
}


park_list* Add_to_list_in_order_name(park_list* head, park* p)
{
    park_list* temp, *new, *aux = NULL;
    if(head->info == NULL)
    {
        head->info = p;
        return head;
    }
    new = Init_park_list();
    new->info = p;
    for(temp = head; temp != NULL && temp->info != NULL; aux = temp, temp = temp->next)
    {
        if(strcmp(temp->info->name, p->name) > 0)
        {
            new->next = temp;
            new->prev = temp->prev;
            temp->prev = new;
            if(new->prev == NULL)
                return new;
            new->prev->next = new;
            return head;
        }
    }
    new->prev = aux;
    aux->next = new;
    return head;
}


// Função que vai adicionar uma entrada a uma lista de entradas ordenada por data e hora de saída

entries_list* Add_to_list_in_order_out(entries_list* head, entry* e)
{
    entries_list* temp, *new, *aux = NULL;
    if(head->info == NULL)
    {
        head->info = e;
        return head;
    }
    new = Init_entries_list();
    new->info = e;
    for(temp = head; temp != NULL; aux = temp, temp = temp->next)
    {
        if(Time_diference(temp->info->out, e->out) > 0)
        {
            new->next = temp;
            new->prev = temp->prev;
            temp->prev = new;
            if(new->prev != NULL)
                new->prev->next = new;
            else
                return new;
            return head;
        }
    }
    new->prev = aux;
    aux->next = new;
    return head;
}


// Função que adiciona elementos na lista, ordenadamente.

ordered* Add_to_list_in_order_v(ordered* head, entry* e, park* p)
{
    ordered* temp, *new, *aux = NULL;
    if(head->info == NULL)
    {
        head->info = e;
        head->park = p;
        return head;
    }
    new = Init_ordered();
    new->info = e;
    new->park = p;
    for(temp = head; temp != NULL && temp->info != NULL; aux = temp, temp = temp->next)
    {
        if(strcmp(temp->park->name, p->name) == 0)
        {
            if(Time_diference(temp->info->in, e->in) > 0)
            {
                new->next = temp;
                new->prev = temp->prev;
                temp->prev = new;
                if(new->prev != NULL)
                    new->prev->next = new;
                else
                    return new;
                return head;
            }
        }
        if(strcmp(temp->park->name, p->name) > 0)
        {
            new->next = temp;
            new->prev = temp->prev;
            temp->prev = new;
            if(new->prev == NULL)
                return new;
            new->prev->next = new;
            return head;
        }
    }
    new->prev = aux;
    aux->next = new;
    return head;
}


ordered* List_ordered_v(park_list* l, char* new)
{
    park_list* p_temp;
    entries_list* e_temp;
    ordered* new_entries = Init_ordered();
    for(p_temp = l; p_temp != NULL; p_temp = p_temp->next)
    {
        for(e_temp = p_temp->info->cars; e_temp != NULL; e_temp = e_temp->next)
        {
            if(strcmp(e_temp->info->reg, new) == 0)
                new_entries = Add_to_list_in_order_v(new_entries, e_temp->info, p_temp->info);
        }
    }
    return new_entries;
}

void Free_all_parks(park_list* h) 
{
    park_list* temp = h->next;
    while(temp != NULL)
    {
        Free_park_list_cell(h);
        h = temp;
        temp = temp->next;
    }
}

void Free_park_list_cell(park_list* c) 
{
    Free_park(c->info);
    free(c);
}

void Free_park(park* p) 
{
    free(p->name);
    Free_all_entries(p->cars);
    free(p);
}

void Free_all_entries(entries_list* h) 
{
    entries_list* temp = h->next;
    while(temp != NULL)
    {
        Free_entries_list_cell(h);
        h = temp;
        temp = temp->next;
    }
}

void Free_entries_list_cell(entries_list* c) 
{
    Free_entry(c->info);
    free(c);
}

void Free_entry(entry* e) 
{
    free(e->in);
    if(e->out != NULL)
        free(e->out);
    free(e);
}


