#include <iostream>
#include "sistemMember.h"
#include "sistemPeminjaman.h"
using namespace std;

int getMainOption();

int main(){
    
    int option = getMainOption();
    string is_continue;
    enum Option{PINJAM = 1, KEMBALIKAN, DISPLAY, MEMBERSHIP, EXIT};

    while(option != EXIT){
        switch(option){
            case PINJAM:
                cout << "Lakukan Peminjaman" << endl;
                get_addPeminjaman();
                break;
            case KEMBALIKAN:
                get_pengembalian();
                break;
            case DISPLAY:
                get_displayPeminjaman();
                break;
            case MEMBERSHIP:
                sistemMember();
                break;
            default:
                cout << "Error: Invalid input" << endl;
                break;
        }

        label_continue:
        cout << "==============================" << endl;
        cout << "\nLanjutkan?[y/n] : ";
        cin >> is_continue;
        cin.ignore(1,'\n');
        if ((is_continue == "Y")|(is_continue == "y")){
            option = getMainOption();
        } else if((is_continue == "N")|(is_continue == "n")){
            break;
        } else{
            cout << "Error: Invalid input"<< endl;
            goto label_continue;
        }

    }

    return 0;
}

//pengambilan opsi
int getMainOption(){
    int input;

    system("cls");
    cout << "SELAMAT DATANG DI PERPUSTAKAAN" << endl;
    cout << "==============================" << endl;
    cout << "[1] Peminjaman" << endl;
    cout << "[2] Pengembalian" << endl;
    cout << "[3] Lihat Data Peminjaman" << endl;
    cout << "[4] Membership" << endl;
    cout << "[5] Exit" << endl;
    cout << "==============================" << endl;
    cout << "Masukkan pilihan[1-5] : ";
    cin >> input;
    cin.ignore(1,'\n');

    return input;
}