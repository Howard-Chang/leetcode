typedef struct {
    int start;
    int end;
     struct MyCalendar* next;
} MyCalendar;

MyCalendar* myCalendarCreate() {
    MyCalendar* obj=(MyCalendar*)malloc(sizeof(MyCalendar));
    obj->start=-1;
    obj->end=-1;
    obj->next=NULL;
    return obj;
}

bool myCalendarBook(MyCalendar* obj, int start, int end) {
    MyCalendar* front=obj;
    MyCalendar* p=obj->next;
    while(p){
        if(p->start>start){
            printf("front->start:%d ",front->start);
            printf("front->end:%d ",front->end);
            printf("start:%d ",start);
            
            if(front->start<start&&front->end<=start&&end<=p->start){
                MyCalendar* q=(MyCalendar*)malloc(sizeof(MyCalendar));
                q->start=start;
                q->end=end;
                q->next=p;
                front->next=q;
                return true;
            }else{
                return false;
            }
        }else{
            front=p;
            p=p->next;
        }
    }
    if(p==NULL&&front->end<=start){
        printf("front->end:%d ",front->end);
        printf("start:%d ",start);
        
        MyCalendar* q=(MyCalendar*)malloc(sizeof(MyCalendar));
        q->start=start;
        q->end=end;
        q->next=p;
        front->next=q;
        return true;
    }
    return false;
}

void myCalendarFree(MyCalendar* obj) {
    free(obj);
}

/**
 * Your MyCalendar struct will be instantiated and called as such:
 * struct MyCalendar* obj = myCalendarCreate();
 * bool param_1 = myCalendarBook(obj, start, end);
 * myCalendarFree(obj);
 */
