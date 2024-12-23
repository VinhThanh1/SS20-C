#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char maSach[20];
    char tenSach[100];
    char tacGia[100];
    float giaTien;
    char theLoai[50];
} Book;

Book *bookList = NULL;
int bookCount = 0;
void inputBookInfo(Book *book);
void displayBookList();
void addBookAtPosition(); 
void deleteBookByCode();
void updateBookByCode();
void sortBooksByPrice();
void searchBookByName();

int main() {
    int choice;
    do {
        printf("MENU\n");
        printf("1. Nhap so luong va thong tin sach.\n");
        printf("2. Hien thi thong tin sach.\n");
        printf("3. Them sach vao vi tri.\n");
        printf("4. Xoa sach theo ma sach.\n");
        printf("5. Cap nhat thong tin sach theo ma sach.\n");
        printf("6. Sap xep sach theo gia (tang/giam).\n");
        printf("7. Tim kiem sach theo ten sach.\n");
        printf("8. Thoat.\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap so luong sach: ");
                scanf("%d", &bookCount);
                bookList = realloc(bookList, bookCount * sizeof(Book));
                if (bookList == NULL) {
                    printf("Loi cap phat bo nho.\n");
                    exit(1);
                }
                for (int i = 0; i < bookCount; i++) {
                    printf("Nhap thong tin cho sach %d:\n", i + 1);
                    inputBookInfo(&bookList[i]);
                }
                break;
            case 2:
                displayBookList();
                break;
            case 3:
                addBookAtPosition();
                break;
            case 4:
                deleteBookByCode();
                break;
            case 5:
                updateBookByCode();
                break;
            case 6:
                sortBooksByPrice();
                break;
            case 7:
                searchBookByName();
                break;
            case 8:
                printf("Dang thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
                break;
        }
    } while (choice != 8);
    return 0;
}

void inputBookInfo(Book *book) {
    printf("Nhap ma sach: ");
    getchar();
    fgets(book->maSach, 20, stdin);
    book->maSach[strcspn(book->maSach, "\n")] = '\0';

    printf("Nhap ten sach: ");
    fgets(book->tenSach, 100, stdin);
    book->tenSach[strcspn(book->tenSach, "\n")] = '\0';

    printf("Nhap ten tac gia: ");
    fgets(book->tacGia, 100, stdin);
    book->tacGia[strcspn(book->tacGia, "\n")] = '\0';

    printf("Nhap gia tien: ");
    scanf("%f", &book->giaTien);

    printf("Nhap the loai: ");
    getchar();
    fgets(book->theLoai, 50, stdin);
    book->theLoai[strcspn(book->theLoai, "\n")] = '\0';
}

void displayBookList() {
    if (bookCount == 0) {
        printf("Danh sach sach hien tai rong.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        printf("Ma sach: %s\n", bookList[i].maSach);
        printf("Ten sach: %s\n", bookList[i].tenSach);
        printf("Tac gia: %s\n", bookList[i].tacGia);
        printf("Gia tien: %.2f\n", bookList[i].giaTien);
        printf("The loai: %s\n\n", bookList[i].theLoai);
    }
}

void addBookAtPosition() {
    int position;
    printf("Nhap vi tri de them sach: ");
    scanf("%d", &position);

    if (position < 0 || position > bookCount) {
        printf("Vi tri khong hop le.\n");
        return;
    }

    bookList = realloc(bookList, (bookCount + 1) * sizeof(Book));
    if (bookList == NULL) {
        printf("Loi cap phat bo nho.\n");
        exit(1);
    }

    for (int i = bookCount; i > position; i--) {
        bookList[i] = bookList[i - 1];
    }

    printf("Nhap thong tin sach can them:\n");
    inputBookInfo(&bookList[position]);
    bookCount++;
}

void deleteBookByCode() {
    char bookCode[20];
    printf("Nhap ma sach de xoa: ");
    getchar();
    fgets(bookCode, 20, stdin);
    bookCode[strcspn(bookCode, "\n")] = '\0';

    int i;
    for (i = 0; i < bookCount; i++) {
        if (strcmp(bookList[i].maSach, bookCode) == 0) {
            break;
        }
    }

    if (i == bookCount) {
        printf("Khong tim thay sach voi ma nay.\n");
        return;
    }

    for (int j = i; j < bookCount - 1; j++) {
        bookList[j] = bookList[j + 1];
    }

    bookList = realloc(bookList, (bookCount - 1) * sizeof(Book));
    if (bookList == NULL && bookCount > 1) {
        printf("Loi cap phat lai bo nho.\n");
        exit(1);
    }

    bookCount--;
    printf("Sach da duoc xoa.\n");
}

void updateBookByCode() {
    char bookCode[20];
    printf("Nhap ma sach de cap nhat: ");
    getchar();
    fgets(bookCode, 20, stdin);
    bookCode[strcspn(bookCode, "\n")] = '\0';

    int i;
    for (i = 0; i < bookCount; i++) {
        if (strcmp(bookList[i].maSach, bookCode) == 0) {
            break;
        }
    }

    if (i == bookCount) {
        printf("Khong tim thay sach voi ma nay.\n");
        return;
    }

    printf("Nhap thong tin moi cho sach:\n");
    inputBookInfo(&bookList[i]);
}

void sortBooksByPrice() {
    int choice;
    printf("1. Sap xep tang dan theo gia\n");
    printf("2. Sap xep giam dan theo gia\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &choice);

    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = i + 1; j < bookCount; j++) {
            if ((choice == 1 && bookList[i].giaTien > bookList[j].giaTien) ||
                (choice == 2 && bookList[i].giaTien < bookList[j].giaTien)) {
                Book temp = bookList[i];
                bookList[i] = bookList[j];
                bookList[j] = temp;
            }
        }
    }

    printf("Sach da duoc sap xep thanh cong.\n");
}

void searchBookByName() {
    char bookName[100];
    printf("Nhap ten sach de tim kiem: ");
    getchar();
    fgets(bookName, 100, stdin);
    bookName[strcspn(bookName, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(bookList[i].tenSach, bookName) != NULL) {
            printf("Ma sach: %s\n", bookList[i].maSach);
            printf("Ten sach: %s\n", bookList[i].tenSach);
            printf("Tac gia: %s\n", bookList[i].tacGia);
            printf("Gia tien: %.2f\n", bookList[i].giaTien);
            printf("The loai: %s\n\n", bookList[i].theLoai);
            found = 1;
        }
    }

    if (!found) {
        printf("Khong tim thay sach voi ten nay.\n");
    }
}
