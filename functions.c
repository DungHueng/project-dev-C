#include<stdio.h>
#include"functions.h"
#include<string.h>

void lobbyMenu(int choice){
    printf("*******HE THONG QUAN LY DANH MUC HANG HOA*******\n");
    printf("_____________THONG TIN DANH MUC________________\n");
    printf("===============================================\n");
    printf("[1] Quan ly danh muc.\n");
    printf("[2] Quan ly san pham.\n");
    printf("[3] Thoat.\n");
    printf("===============================================\n");
    printf("Moi ban nhap lua chon: ");
}

void danhmucMenu(int choiceDanhmuc){
    printf("================================================\n");
    printf("[1] Xem thong tin danh muc.\n"); 
    printf("[2] Them danh muc.\n"); 
    printf("[3] Sua danh muc.\n"); 
    printf("[4] Xoa danh muc.\n"); 
    printf("[5] Tim kiem danh muc.\n"); 
    printf("[6] Thoat.\n"); 
    printf("================================================\n");
    printf("Moi nhap lua chon: ");
}

void viewdanhmuc(){ // Hien thi danh muc
    FILE *ptr = fopen("danhmuc.dat", "rb"); // mo che do doc
    if (ptr == NULL){ // xac minh xem tep co mo duoc khong
        printf("Loi mo tep.\n");
        return 0;
    }
    danhmuc view;
    printf("|=======|===========================|=============|\n");
    printf("|  ID   |       Ten danh muc        |  So luong   |\n");
    printf("|=======|===========================|=============|\n");
    while (fread(&view, sizeof(danhmuc), 1, ptr) != NULL){ // doc tep 'danhmuc.dat'
        printf("|%6d | %-25s | %11d |\n",
            view.id,
            view.namedanhmuc,
            view.quantity);
        printf("|-------|---------------------------|-------------|\n");    
    }
    printf("|=======|===========================|=============|\n");
    fclose(ptr);
}

void adddanhmuc(){
    FILE *ptr = fopen("danhmuc.dat", "ab");
    if (ptr == NULL){
        printf("Loi mo tep.\n");
        return 0;
    }
    danhmuc add[50]; // mang chua 50 phan tu
    int n;
    printf("Nhap so luong danh muc muon nhap: ");
    scanf("%d", &n);
    getchar();
    for (int i=0; i<n; i++){
        printf("Moi ban nhap thong tin. \n");
        printf("ID: ");
        scanf("%d", &add[i].id);
        getchar();
        printf("Ten cua danh muc: ");
        fgets(add[i].namedanhmuc, sizeof(add[i].namedanhmuc), stdin);
        add[i].namedanhmuc[strcspn(add[i].namedanhmuc, "\n")] = '\0';
        fflush(stdin);
        printf("So luong danh muc: ");
        scanf("%d", &add[i].quantity);
        getchar();
    }
    fwrite(add, sizeof(danhmuc), n, ptr);
    printf("Cac san pham da duoc them thanh cong!\n");
    fclose(ptr);
}

void editdanhmuc() {
    int addEdit;
    danhmuc edit;
    FILE *ptr = fopen("danhmuc.dat", "rb");
    
    if (ptr == NULL) {
        printf("Khong the mo tep.\n");
        return 0;
    }

    fseek(ptr, 0, SEEK_END); // Di chuyen con tro den cuoi tep
    int totalProducts = ftell(ptr)/sizeof(danhmuc); // Tinh so luong danh muc co trong tep
    fseek(ptr, 0, SEEK_SET); // di chuyen con tro ve dau tep

    printf("Ban muon sua danh muc nao, vui long nhap ID: ");
    scanf("%d", &addEdit);
    while (addEdit < 1 || addEdit > totalProducts) {
        printf("khong co id ban muon sua \n", totalProducts);
        scanf("%d", &addEdit);
    }

    printf("Chi tiet danh muc:\n");
    fseek(ptr, (addEdit - 1) * sizeof(danhmuc), SEEK_SET); // 'fseek' dung de xac dinh con tro tai vi tri cu the
    fread(&edit, sizeof(danhmuc), 1, ptr);
    printf("|=======|===========================|=============|\n");
    printf("|  ID   |       Ten danh muc        |   So luong  |\n");
    printf("|=======|===========================|=============|\n");
    printf("|%6d | %-25s | %11d |\n",
        edit.id,
        edit.namedanhmuc,
        edit.quantity);
    printf("|-------|---------------------------|-------------|\n");
    printf("|=======|===========================|=============|\n");

    printf("Tien hanh chinh sua san pham...\n");
    getchar();
    printf("Ten moi cua danh muc: ");
    fgets(edit.namedanhmuc, sizeof(edit.namedanhmuc), stdin);
    edit.namedanhmuc[strcspn(edit.namedanhmuc, "\n")] = '\0';
    fflush(stdin);

    printf("So luong danh muc: ");
    scanf("%d", &edit.quantity);
    getchar();

    fseek(ptr, (addEdit - 1) * sizeof(danhmuc), SEEK_SET); // dich chuyen con tro ve tep can chinh sua
    fwrite(&edit, sizeof(danhmuc), 1, ptr);

    fclose(ptr);
}

void deleteDanhMuc() {
    int delID, confirmDelete, found = 0; // 'found' giup xem danh muc can xoa co ton tai hay khong
    danhmuc temp;
    FILE *ptr = fopen("danhmuc.dat", "rb");
    FILE *tempPtr = fopen("temp.dat", "wb");

    if (ptr == NULL || tempPtr == NULL) {
        printf("Khong the mo tep.\n");
        return 0;
    }

    printf("Ban muon xoa danh muc nao, vui long nhap ID: ");
    scanf("%d", &delID);

    while (fread(&temp, sizeof(danhmuc), 1, ptr) != NULL) { // Kiem tra xem danh muc can xoa co ton tai hay khong
        if (temp.id == delID) {
            found = 1; // danh muc can xoa da duoc tim thay
            printf("Thong tin danh muc can xoa.\n");
            printf("|=======|===========================|=============|\n");
            printf("|  ID   |       Ten danh muc        |   So luong  |\n");
            printf("|=======|===========================|=============|\n");
            printf("|%6d | %-25s | %11d |\n",
                   temp.id,
                   temp.namedanhmuc,
                   temp.quantity);
            printf("|=======|===========================|=============|\n");

            printf("Ban co chac chan muon xoa danh muc nay khong?\n");
            printf("1.Chap nhan.\n");
            printf("2.khong.\n");
            scanf("%d", &confirmDelete);

            if (confirmDelete == 1) {
                printf("Dang tien hanh xoa...\n");
                continue; // Bo qua danh muc nay va ghi vao file tam
            } else {
                printf("Huy thao tac xoa.\n");
                fclose(ptr);
                fclose(tempPtr);
                remove("temp.dat"); // Xaa file tam
                return 0;
            }
        }
        fwrite(&temp, sizeof(danhmuc), 1, tempPtr); // Sao chep cac danh muc khac
    }


    fclose(ptr);
    fclose(tempPtr);

    if (found) {
        remove("danhmuc.dat");
        rename("temp.dat", "danhmuc.dat");
        printf("Danh muc da duoc xoa thanh cong.\n");
    } else {
        remove("temp.dat");
        printf("Khong tim thay danh muc co ID. %d.\n", delID);
    }
}

