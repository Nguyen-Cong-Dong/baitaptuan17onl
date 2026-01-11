#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

#define MAX 20 // So luong dinh toi da

// Ten cac tinh thanh tuong ung voi chi so 1 -> 11
string tenTinh[] = {
    "", "Ha Noi", "Hai Duong", "Hai Phong", "Uong Bi", "Bac Giang",
    "Bac Ninh", "Thai Nguyen", "Son Tay", "Hoa Binh", "Phu Ly", "Hung Yen"
};

// CACH 1: MA TRAN LAN CAN
int A[MAX][MAX]; // Ma tran ke
int n = 11;      // So dinh

void khoiTaoMaTran() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            A[i][j] = 0;
        }
    }
}

void themCungMaTran(int u, int v) {
    // Do thi vo huong
    // A[i][j] = 1 neu co duong di
    A[u][v] = 1;
    A[v][u] = 1;
}

// CACH 2: DANH SACH LAN CAN
struct Node {
    int vertex;       // Dinh ke
    struct Node* link; // Con tro den nut tiep theo
};

// Mang chua dia chi nut dau tien
Node* V[MAX];

void khoiTaoDanhSach() {
    for (int i = 1; i <= n; i++) {
        V[i] = NULL;
    }
}

// Ham them nut vao danh sach ke cua u
void themCungDanhSach(int u, int v) {
    // Them v vao danh sach cua u
    Node* p = new Node;
    p->vertex = v;
    p->link = V[u];
    V[u] = p;

    // Vi la do thi vo huong, them u vao danh sach cua v
    Node* q = new Node;
    q->vertex = u;
    q->link = V[v];
    V[v] = q;
}

// THUAT TOAN DUYET BFS (Dung Ma tran de uu tien thu tu lon -> be)
bool visited[MAX];

void BFS(int v) {
    // Khoi tao mang danh dau
    for (int i = 1; i <= n; i++) visited[i] = false;

    queue<int> q; // Hang doi

    // Quy tac 1: Duyet dinh xuat phat, danh dau va day vao queue
    cout << "BFS: ";
    visited[v] = true;
    q.push(v);

    cout << tenTinh[v]; // Hien thi dinh dau tien

    // Quy tac 3: Lap lai cho den khi hang doi rong
    while (!q.empty()) {
        int u = q.front(); // Lay dinh dau hang doi (Quy tac 2)
        q.pop();

        // Duyet cac dinh ke
        for (int j = n; j >= 1; j--) {
            if (A[u][j] == 1 && !visited[j]) {
                visited[j] = true;       // Danh dau
                cout << " -> " << tenTinh[j]; // Hien thi
                q.push(j);               // Day vao queue
            }
        }
    }
    cout << endl;
}

// Ham hien thi danh sach lien ket de kiem tra
void inDanhSachLienKet() {
    cout << "\nBieu dien bang Danh sach lan can (Adjacency List):" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "V[" << i << "] (" << tenTinh[i] << "): ";
        Node* p = V[i];
        while (p != NULL) {
            cout << p->vertex << " -> ";
            p = p->link;
        }
        cout << "NULL" << endl;
    }
}

// Ham hien thi ma tran de kiem tra
void inMaTran() {
    cout << "\nBieu dien bang Ma tran lan can (Adjacency Matrix):" << endl;
    cout << "   ";
    for (int i = 1; i <= n; i++) cout << i << " ";
    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << (i < 10 ? "  " : " ");
        for (int j = 1; j <= n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Khoi tao du lieu
    khoiTaoMaTran();
    khoiTaoDanhSach();

    // D1: Ha Noi (1) - Hai Duong (2)
    themCungMaTran(1, 2); themCungDanhSach(1, 2);
    // D2: Hai Duong (2) - Hung Yen (11)
    themCungMaTran(2, 11); themCungDanhSach(2, 11);
    // D3: Hung Yen (11) - Phu Ly (10)
    themCungMaTran(11, 10); themCungDanhSach(11, 10);
    // D4: Phu Ly (10) - Ha Noi (1)
    themCungMaTran(10, 1); themCungDanhSach(10, 1);
    // D5: Ha Noi (1) - Hoa Binh (9)
    themCungMaTran(1, 9); themCungDanhSach(1, 9);
    // D6: Ha Noi (1) - Son Tay (8)
    themCungMaTran(1, 8); themCungDanhSach(1, 8);
    // D7: Ha Noi (1) - Thai Nguyen (7)
    themCungMaTran(1, 7); themCungDanhSach(1, 7);
    // D8: Ha Noi (1) - Bac Ninh (6)
    themCungMaTran(1, 6); themCungDanhSach(1, 6);
    // D9: Bac Ninh (6) - Bac Giang (5)
    themCungMaTran(6, 5); themCungDanhSach(6, 5);
    // D10: Bac Giang (5) - Uong Bi (4)
    themCungMaTran(5, 4); themCungDanhSach(5, 4);
    // D11: Bac Ninh (6) - Uong Bi (4)
    themCungMaTran(6, 4); themCungDanhSach(6, 4);
    // D12: Uong Bi (4) - Hai Phong (3)
    themCungMaTran(4, 3); themCungDanhSach(4, 3);
    // D13: Hai Phong (3) - Hai Duong (2)
    themCungMaTran(3, 2); themCungDanhSach(3, 2);

    // Yeu cau 1: Hien thi cau truc luu tru
    inMaTran();
    inDanhSachLienKet();

    // Yeu cau 2: Duyet BFS
    cout << "\n-----------------------------" << endl;
    cout << "Ket qua duyet BFS (Uu tien dinh lon truoc):" << endl;
    BFS(1); // Bat dau tu Ha Noi

    return 0;
}