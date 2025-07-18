#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// khoi tao cau truc
typedef struct Project{
    int id;                               // Mã dự án
    char title[100];                // Tên tên dự án
    char owner[100];            // Tên người quản lý dự án
    int priority;                     // Độ ưu tiên dự án
} Project;

typedef struct FProject {
    Project project;
    struct FProject* next;
}FProject;

typedef struct DProject {
    Project project;
    struct DProject* next;
    struct DProject* prev;
}DProject;
//khoi tao ham them
FProject* createF(Project p) {
    FProject* newProject = (FProject*)malloc(sizeof(FProject));
    newProject->project = p;
    newProject->next = NULL;
    return newProject;
}
DProject* createD(Project p) {
    DProject* newProject = (DProject*)malloc(sizeof(DProject));
    newProject->project = p;
    newProject->next = NULL;
    newProject->prev = NULL;
    return newProject;
}
// menu
void menu() {
    printf("==============  Menu   ==================\n");
    printf("1 . Them du an moi .\n");
    printf("2 . Hien thi danh sach . \n");
    printf("3 . Xoa du an .\n");
    printf("4 . Cap nhat thong tin du an .\n");
    printf("5 . Danh dau du an da hoan thanh .\n");
    printf("6 . Sap xep du an theo do uu tien .\n");
    printf("7 . Tim kiem du an theo ten .\n");
    printf("8 . Thoat chuong trinh .\n");
    printf("========================================\n");
}
//Them du an moi
int idF = 0;
FProject* Fhead = NULL;
FProject* add(FProject* head , Project p) {
    FProject* newProject = createF(p);
    if (head==NULL) {
        head = newProject;
        return head;
    }
    FProject* current = head;
    while (current->next!=NULL) {
        current = current->next;
    }
    current->next = newProject;
    return head;
}
//Hien thi danh sach
void display(FProject* head) {
    if (head==NULL) {
        printf("rong.\n");
        return;
    }
    FProject* current = head;
    while (current!=NULL) {
        printf("id : %d\n" , current->project.id);
        printf("title : %s\n" , current->project.title);
        printf("owner : %s\n" , current->project.owner);
        printf("priority : %d\n" , current->project.priority);
        current = current->next;
        printf("\n");
    }
}
//Xoa du an theo id
FProject* deleteF(FProject* head , int id) {
    if (head==NULL) {
        printf("rong.\n");
        return NULL;
    }
    FProject* current = head;
    FProject *prev = NULL;
    while (current->next!=NULL && current->project.id!=id) {
        current = current->next;
    };
    if (current == NULL) {
        printf(R"(khong tim thay id ban muon xoa ..)");
        return head;
    }
    if (current==head) {
        head = head->next;
        Fhead = current;
        free(current);
        return head;
    }
    prev->next = current->next;
    Fhead = current;
    free(current);
    return head;
}
//Cap nhat thong tin du an
void update(FProject* head) {
    if (head==NULL) {
        printf("rong.\n");
        return;
    }
    int id ;
    printf("nhh id ban muon cap nhat: ");
    scanf("%d" , &id);
    getchar();
    FProject* current = head;
    while (current!=NULL) {
        if (current->project.id==id) {
            printf("id : %d" ,id);
            printf("moi nhap lai ten du an : ");
            fgets(current->project.title,100,stdin);
            current->project.title[strcspn(current->project.title,"\n")] = '\0';
            printf("moi nhap nguoi quan li du an ");
            fgets(current->project.owner,100,stdin);
            current->project.owner[strcspn(current->project.owner,"\n")] = '\0';
            printf("moi nhap lai do uu tien :");
            scanf("%d",&current->project.priority);
            getchar();
            break;
        }
        current = current->next;
    }
}
//Danh dau du an da hoan thanh
DProject* add2(DProject* head , Project p) {
    DProject* newD = createD(p);
    if (head==NULL) {
        head = newD;
        return head;
    }
    DProject* current = head;
    while (current->next!=NULL) {
        current = current->next;
    }
    current->next = newD;
    newD->prev = current;
    return head;
}
//Sap xep du an theo do uu tien
void sort(FProject* head) {
    if (head==NULL) {
        printf("rong.\n");
        return;
    }
    FProject* current = head;
    int swap;
    do {
        swap = 0;
        while (current->next!=NULL) {
            if (current->project.priority < current->next->project.priority) {
                swap = 1;
                Project temp = current->project;
                current->project = current->next->project;
                current->next->project = temp;
            }
            current = current->next;
        }
    }while (swap);
    printf("sap xepthanh cong.\n");
}
//Tim kiem du an theo ten
void search(FProject* head , char name[]) {
    if (head==NULL) {
        printf("rong.\n");
        return;
    }
    FProject* current = head;

    while (current!=NULL) {
        if (strstr(current->project.title,name)!=NULL) {
            printf("id : %d\n" , current->project.id);
            printf("title : %s\n" , current->project.title);
            printf("owner : %s\n" , current->project.owner);
            printf("priority : %d\n" , current->project.priority);
            printf("\n");
        }
        current = current->next;
    }
}
int main(void) {
    int choice;
    Project p;
    FProject* head = NULL;
    DProject* DHead = NULL;
    do {
        menu();
        printf("Lua chon cua ban : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                idF = idF + 1;
                p.id = idF;
                printf("id : %d\n" , p.id);
                getchar();
                printf("moi nhap ten du an :");
                fgets(p.title, 100, stdin);
                p.title[strcspn(p.title, "\n")] = '\0';
                printf("moi nhap ten nguoi quan li du an : ");
                fgets(p.owner, 100, stdin);
                p.owner[strcspn(p.owner, "\n")] = '\0';
                printf("moi nhap do uu tien du an :");
                scanf("%d", &p.priority);
                getchar();
                head = add(head,p);
                break;
            case 2:
                display(head);
                break;
            case 3:
                int id;
                printf("nhap id ban muon xoa :");
                scanf("%d", &id);
                getchar();
                head = deleteF(head,id);
                break;
            case 4:
                update(head);
                break;
            case 5:
                int id2;
                printf("nhap id ban muon danh dau hoan thanh :");
                scanf("%d", &id2);
                getchar();
                head = deleteF(head,id2);
                p.id = Fhead->project.id;
                strcpy(p.title,Fhead->project.title);
                strcpy(p.owner,Fhead->project.owner);
                p.priority = Fhead->project.priority;
                DHead = add(DHead,p);
                break;
            case 6:
                sort(head);
                break;
            case 7:
                char name[100];
                printf("nhap ten du an ban muon tim kiem :");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                search(head,name);
                break;
            case 8:
                printf("Thoat chuong trinh!!!!");
                break;
            default:
                printf("khong co lua chon nay ....");
        }
    }while (choice!=8);
    return 0;
}