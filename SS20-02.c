#include <stdio.h>
#include <string.h>

struct Product {
    char maSP[20];
    char tenSP[50];
    float giaNhap;
    float giaBan;
    int soLuong;
};

struct Product sanPhams[100];
int soLuongSP = 0;
float doanhThu = 0.0;

void nhapSanPham() {
    struct Product spMoi;
    printf("Nhap ma san pham: ");
    scanf("%s", spMoi.maSP);
    printf("Nhap ten san pham: ");
    scanf("%s", spMoi.tenSP);
    printf("Nhap gia nhap: ");
    scanf("%f", &spMoi.giaNhap);
    printf("Nhap gia ban: ");
    scanf("%f", &spMoi.giaBan);
    printf("Nhap so luong: ");
    scanf("%d", &spMoi.soLuong);

    for (int i = 0; i < soLuongSP; i++) {
        if (strcmp(sanPhams[i].maSP, spMoi.maSP) == 0) {
            sanPhams[i].soLuong += spMoi.soLuong;
            doanhThu -= spMoi.giaNhap * spMoi.soLuong;
            printf("San pham da ton tai, chi tang so luong.\n");
            return;
        }
    }

    sanPhams[soLuongSP++] = spMoi;
    doanhThu -= spMoi.giaNhap * spMoi.soLuong;
    printf("Nhap san pham thanh cong!\n");
}

void hienThiSanPham() {
    for (int i = 0; i < soLuongSP; i++) {
        printf("%d. Ma: %s, Ten: %s, Gia nhap: %.2f, Gia ban: %.2f, So luong: %d\n",
               i+1, sanPhams[i].maSP, sanPhams[i].tenSP, sanPhams[i].giaNhap, sanPhams[i].giaBan, sanPhams[i].soLuong);
    }
}

void capNhatSanPham() {
    char maSP[20];
    printf("Nhap ma san pham can cap nhat: ");
    scanf("%s", maSP);

    for (int i = 0; i < soLuongSP; i++) {
        if (strcmp(sanPhams[i].maSP, maSP) == 0) {
            printf("Nhap ten san pham moi: ");
            scanf("%s", sanPhams[i].tenSP);
            printf("Nhap gia nhap moi: ");
            scanf("%f", &sanPhams[i].giaNhap);
            printf("Nhap gia ban moi: ");
            scanf("%f", &sanPhams[i].giaBan);
            printf("Nhap so luong moi: ");
            scanf("%d", &sanPhams[i].soLuong);
            printf("Cap nhat san pham thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay san pham voi ma %s.\n", maSP);
}

void sapXepSanPham(int tangDan) {
    for (int i = 0; i < soLuongSP - 1; i++) {
        for (int j = i + 1; j < soLuongSP; j++) {
            if ((tangDan && sanPhams[i].giaBan > sanPhams[j].giaBan) || (!tangDan && sanPhams[i].giaBan < sanPhams[j].giaBan)) {
                struct Product temp = sanPhams[i];
                sanPhams[i] = sanPhams[j];
                sanPhams[j] = temp;
            }
        }
    }
    printf("Sap xep san pham thanh cong!\n");
}

void timKiemSanPham() {
    char tenSP[50];
    printf("Nhap ten san pham can tim: ");
    scanf("%s", tenSP);

    for (int i = 0; i < soLuongSP; i++) {
        if (strcmp(sanPhams[i].tenSP, tenSP) == 0) {
            printf("%d. Ma: %s, Ten: %s, Gia nhap: %.2f, Gia ban: %.2f, So luong: %d\n",
                   i+1, sanPhams[i].maSP, sanPhams[i].tenSP, sanPhams[i].giaNhap, sanPhams[i].giaBan, sanPhams[i].soLuong);
            return;
        }
    }
    printf("Khong tim thay san pham voi ten %s.\n", tenSP);
}

void banSanPham() {
    char maSP[20];
    int soLuongBan;
    printf("Nhap ma san pham can ban: ");
    scanf("%s", maSP);
    printf("Nhap so luong can ban: ");
    scanf("%d", &soLuongBan);

    for (int i = 0; i < soLuongSP; i++) {
        if (strcmp(sanPhams[i].maSP, maSP) == 0) {
            if (sanPhams[i].soLuong < soLuongBan) {
                printf("Khong con du hang.\n");
                return;
            } else if (sanPhams[i].soLuong == 0) {
                printf("Het hang.\n");
                return;
            } else {
                sanPhams[i].soLuong -= soLuongBan;
                doanhThu += soLuongBan * sanPhams[i].giaBan;
                printf("Ban san pham thanh cong!\n");
                return;
            }
        }
    }
    printf("Khong tim thay san pham voi ma %s.\n", maSP);
}

void hienThiDoanhThu() {
    printf("Doanh thu hien tai: %.2f\n", doanhThu);
}

int main() {
    int choice;
    while (1) {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia (tang/giam)\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Doanh thu hien tai\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                nhapSanPham();
                break;
            case 2:
                hienThiSanPham();
                break;
            case 3:
                nhapSanPham();
                break;
            case 4:
                capNhatSanPham();
                break;
            case 5: {
                printf("a. Giam dan theo gia\n");
                printf("b. Tang dan theo gia\n");
                char subChoice;
                scanf(" %c", &subChoice);
                if (subChoice == 'a') {
                    sapXepSanPham(0);
                } else if (subChoice == 'b') {
                    sapXepSanPham(1);
                } else {
                    printf("Lua chon khong hop le.\n");
                }
                break;
            }
            case 6:
                timKiemSanPham();
                break;
            case 7:
                banSanPham();
                break;
            case 8:
                hienThiDoanhThu();
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                return 0;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    }
}
