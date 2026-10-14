#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    char maSach[MAX][20];
    char tenSach[MAX][100];
    int tongSoLuong[MAX];
    int dangMuon[MAX];
    float giaBia[MAX];
    int soLuong = 0;
    
    int choice;
    do {
        printf("\n================ HỆ THỐNG QUẢN LÝ KHO SÁCH ================\n");
        printf("1. Thêm đầu sách mới vào kho\n");
        printf("2. Hiển thị danh sách kho sách\n");
        printf("3. Ghi nhận Mượn / Trả sách và tính phí phạt\n");
        printf("4. Xóa đầu sách khỏi hệ thống kho\n");
        printf("5. Thống kê tổng giá trị tài sản kho sách\n");
        printf("0. Thoát chương trình\n");
        printf("===========================================================\n");
        printf("Lựa chọn của bạn: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Lựa chọn không hợp lệ!\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');
        
        switch(choice) {
            case 1: {
                if (soLuong >= MAX) {
                    printf("Kho sách đã đầy! Không thể thêm mới.\n");
                    break;
                }
                char tempMa[20];
                printf("Nhập mã sách: ");
                fgets(tempMa, sizeof(tempMa), stdin);
                tempMa[strcspn(tempMa, "\n")] = 0;
                
                int trung = 0;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], tempMa) == 0) {
                        trung = 1;
                        break;
                    }
                }
                if (trung) {
                    printf("Lỗi: Mã sách đã tồn tại trong hệ thống!\n");
                    break;
                }
                
                strcpy(maSach[soLuong], tempMa);
                printf("Nhập tên sách: ");
                fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin);
                tenSach[soLuong][strcspn(tenSach[soLuong], "\n")] = 0;
                
                printf("Nhập tổng số lượng: ");
                scanf("%d", &tongSoLuong[soLuong]);
                printf("Nhập giá bìa (VNĐ): ");
                scanf("%f", &giaBia[soLuong]);
                while(getchar() != '\n');
                
                dangMuon[soLuong] = 0;
                soLuong++;
                printf("Thêm đầu sách mới thành công!\n");
                break;
            }
            case 2: {
                if (soLuong == 0) {
                    printf("Kho sách hiện đang rỗng!\n");
                    break;
                }
                printf("--------------------------------------------------------------------------------------------------\n");
                printf("STT | Mã Sách | Tên Sách | Tổng SL | Đang Mượn | Khả Dụng | Giá Bìa (VNĐ)\n");
                printf("--------------------------------------------------------------------------------------------------\n");
                for (int i = 0; i < soLuong; i++) {
                    int khaDung = tongSoLuong[i] - dangMuon[i];
                    printf("%-3d | %-7s | %-20s | %-7d | %-9d | %-8d | %.2f\n", 
                           i + 1, maSach[i], tenSach[i], tongSoLuong[i], dangMuon[i], khaDung, giaBia[i]);
                }
                printf("--------------------------------------------------------------------------------------------------\n");
                break;
            }
            case 3: {
                if (soLuong == 0) {
                    printf("Kho sách đang rỗng, không có sách để mượn trả!\n");
                    break;
                }
                char searchMa[20];
                printf("Nhập mã sách cần thao tác: ");
                fgets(searchMa, sizeof(searchMa), stdin);
                searchMa[strcspn(searchMa, "\n")] = 0;
                
                int pos = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], searchMa) == 0) {
                        pos = i;
                        break;
                    }
                }
                if (pos == -1) {
                    printf("Không tìm thấy mã sách trong hệ thống!\n");
                    break;
                }
                
                printf("Tìm thấy sách: %s (Đang mượn: %d)\n", tenSach[pos], dangMuon[pos]);
                printf("Chọn thao tác (1 - Mượn sách, 2 - Trả sách): ");
                int action;
                scanf("%d", &action);
                while(getchar() != '\n');
                
                if (action == 1) {
                    int slMuon;
                    printf("Nhập số lượng mượn: ");
                    scanf("%d", &slMuon);
                    while(getchar() != '\n');
                    
                    int khaDung = tongSoLuong[pos] - dangMuon[pos];
                    if (slMuon <= 0 || slMuon > khaDung) {
                        printf("Lỗi: Số lượng mượn vượt quá số lượng khả dụng (%d)!\n", khaDung);
                    } else {
                        dangMuon[pos] += slMuon;
                        printf("Ghi nhận mượn thành công %d quyển!\n", slMuon);
                    }
                } else if (action == 2) {
                    int slTra, soNgayQuaHan;
                    printf("Nhập số lượng trả: ");
                    scanf("%d", &slTra);
                    printf("Nhập số ngày quá hạn (0 nếu đúng hạn): ");
                    scanf("%d", &soNgayQuaHan);
                    while(getchar() != '\n');
                    
                    if (slTra <= 0 || slTra > dangMuon[pos]) {
                        printf("Lỗi: Số lượng trả không hợp lệ (vượt quá số lượng đang mượn)!\n");
                    } else {
                        dangMuon[pos] -= slTra;
                        long long tienPhat = 0;
                        if (soNgayQuaHan > 0) {
                            tienPhat = (long long)slTra * soNgayQuaHan * 5000;
                        }
                        printf("--- BIÊN NHẬN TRẢ SÁCH ---\n");
                        printf("Trả thành công: %d quyển.\n", slTra);
                        printf("Phát hiện quá hạn: %d ngày.\n", soNgayQuaHan);
                        printf("Tiền phạt quá hạn (5.000 VNĐ/quyển/ngày): %lld VNĐ.\n", tienPhat);
                    }
                } else {
                    printf("Lựa chọn thao tác không hợp lệ!\n");
                }
                break;
            }
            case 4: {
                if (soLuong == 0) {
                    printf("Kho sách rỗng!\n");
                    break;
                }
                char delMa[20];
                printf("Nhập mã sách cần xóa: ");
                fgets(delMa, sizeof(delMa), stdin);
                delMa[strcspn(delMa, "\n")] = 0;
                
                int pos = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maSach[i], delMa) == 0) {
                        pos = i;
                        break;
                    }
                }
                if (pos == -1) {
                    printf("Không tìm thấy mã sách cần xóa!\n");
                    break;
                }
                
                if (dangMuon[pos] > 0) {
                    printf("Sách đang cho mượn, không thể xóa khỏi hệ thống!\n");
                    break;
                }
                
                for (int i = pos; i < soLuong - 1; i++) {
                    strcpy(maSach[i], maSach[i + 1]);
                    strcpy(tenSach[i], tenSach[i + 1]);
                    tongSoLuong[i] = tongSoLuong[i + 1];
                    dangMuon[i] = dangMuon[i + 1];
                    giaBia[i] = giaBia[i + 1];
                }
                soLuong--;
                printf("Xóa đầu sách thành công!\n");
                break;
            }
            case 5: {
                if (soLuong == 0) {
                    printf("Kho sách rỗng, không có dữ liệu thống kê!\n");
                    break;
                }
                long long totalBooks = 0;
                long long totalBorrow = 0;
                double totalAssetValue = 0;
                
                for (int i = 0; i < soLuong; i++) {
                    totalBooks += tongSoLuong[i];
                    totalBorrow += dangMuon[i];
                    totalAssetValue += (double)tongSoLuong[i] * giaBia[i];
                }
                
                printf("=== BÁO CÁO THỐNG KÊ KHO SÁCH ===\n");
                printf("Tổng số đầu sách khác nhau: %d\n", soLuong);
                printf("Tổng số lượng bản sách trong kho: %lld\n", totalBooks);
                printf("Tổng số sách đang cho mượn: %lld\n", totalBorrow);
                printf("Tổng số sách khả dụng: %lld\n", totalBooks - totalBorrow);
                printf("Tổng giá trị tài sản kho sách: %.2f VNĐ\n", totalAssetValue);
                break;
            }
            case 0:
                printf("Thoát chương trình. Tạm biệt!\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng chọn từ 0 đến 5!\n");
        }
    } while(choice != 0);
    
    return 0;
}