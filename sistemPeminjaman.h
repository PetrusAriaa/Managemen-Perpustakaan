#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Peminjaman{
    public:
    string nama;
    string ID;
    string judul;
    string tanggalPinjam;
    string tanggalPengembalian;

    // <<constructor>>
    Peminjaman(string inputNama, string inputID,
    string inputJudul, string inputTanggalPinjam, string inputTanggalPengembalian){
        Peminjaman::nama = inputNama;
        Peminjaman::ID = inputID;
        Peminjaman::judul = inputJudul;
        Peminjaman::tanggalPinjam = inputTanggalPinjam;
        Peminjaman::tanggalPengembalian = inputTanggalPengembalian;
    }

    string getString_nama(){
        return Peminjaman::nama;
    }

    string getString_ID(){
        return Peminjaman::ID;
    }

    string getString_judul(){
        return Peminjaman::judul;
    }

    string getString_tanggalPinjam(){
        return Peminjaman::tanggalPinjam;
    }

    string getString_tanggalPengembalian(){
        return Peminjaman::tanggalPengembalian;
    }

};

//Database
class DBPinjam{
    public:
    ifstream pinjam_in;
    ofstream pinjam_out;
    string fileName;

    DBPinjam(const char* fileName){
        DBPinjam::fileName = fileName;
    }
    //
    void addPeminjaman(Peminjaman dataPinjam){
        DBPinjam::pinjam_out.open(DBPinjam::fileName, ios::app);
        DBPinjam::pinjam_out << dataPinjam.getString_ID() << endl;
        DBPinjam::pinjam_out << dataPinjam.getString_nama() << endl;
        DBPinjam::pinjam_out << dataPinjam.getString_judul() << endl;
        DBPinjam::pinjam_out << dataPinjam.getString_tanggalPinjam() << endl;
        DBPinjam::pinjam_out << dataPinjam.getString_tanggalPengembalian() << endl << endl;
        DBPinjam::pinjam_out.close();
    }
    //
    void displayPeminjaman(Peminjaman dataPinjam){
        string id, nama, judul, tanggalP, tanggalK;
        unsigned short index = 1;

        DBPinjam::pinjam_in.open(DBPinjam::fileName, ios::in);

        while(!DBPinjam::pinjam_in.eof()){
            getline(DBPinjam::pinjam_in, id);
            if((id == "")){
                continue;
            }
            getline(DBPinjam::pinjam_in, nama);
            getline(DBPinjam::pinjam_in, judul);
            getline(DBPinjam::pinjam_in, tanggalP);
            getline(DBPinjam::pinjam_in, tanggalK);
            cout << "==============================" << endl;
            cout << "[" << index++ << "]. " << endl;
            cout << "ID\t\t\t: " << id << endl;
            cout << "Nama\t\t\t: " << nama << endl;
            cout << "Judul\t\t\t: " << judul << endl;
            cout << "Tanggal Peminjaman\t: " << tanggalP << endl;
            cout << "Tanggal Pengembalian\t: " << tanggalK << endl;
        }
        DBPinjam::pinjam_in.close();
    }

    void pengembalian(Peminjaman dataPinjam){
        string id, line, temp;
        ofstream tempFile;
        DBPinjam::pinjam_in.open(DBPinjam::fileName);
        tempFile.open("TempPinjam.txt", ios::app);

        cout << "\n\n      PENGEMBALIAN BUKU" << endl;
        cout << "==============================" << endl;
        cout << "Masukkan ID: ";
        cin >> id;

        while(!DBPinjam::pinjam_in.eof()){
            getline(DBPinjam::pinjam_in, line);

            if(line == id){
                getline(DBPinjam::pinjam_in, line);
                getline(DBPinjam::pinjam_in, line);
                getline(DBPinjam::pinjam_in, line);
                getline(DBPinjam::pinjam_in, line);
                getline(DBPinjam::pinjam_in, line);
                getline(DBPinjam::pinjam_in, line);
            }

            tempFile << line << endl;
        }

        tempFile.close();
        DBPinjam::pinjam_in.close();

        remove("DatabasePeminjaman.txt");
        rename("TempPinjam.txt", "DatabasePeminjaman.txt");
    }
};

void get_displayPeminjaman(){
    string nama, id, judul, tanggal, tanggalK;
    system("cls");
    cout << "       DATA PEMINJAMAN" << endl;
    Peminjaman dataPinjam = Peminjaman(nama, id, judul, tanggal, tanggalK);
    DBPinjam databasePinjam = ("DatabasePeminjaman.txt");
    databasePinjam.displayPeminjaman(dataPinjam);
}
void get_pengembalian(){
    string nama, id, judul, tanggal, tanggalK;
    get_displayPeminjaman();

    Peminjaman dataPinjam = Peminjaman(nama, id, judul, tanggal, tanggalK);
    DBPinjam databasePinjam = ("DatabasePeminjaman.txt");
    databasePinjam.pengembalian(dataPinjam);
}
void get_addPeminjaman(){
    string nama, id, judul, tanggal, tanggalK;
    system("cls");

    cout << "          PEMINJAMAN" << endl;
    cout << "==============================" << endl;
    cout << "Masukkan Nama : ";
    getline(cin, nama);
    cout << "Masukkan ID : ";
    getline(cin, id);
    cout << "Judul Buku : ";
    getline(cin, judul);
    cout << "Tanggal Peminjaman [dd/mm/yyyy] : ";
    getline(cin, tanggal);
    cout << "Tanggal Pengembalian [dd/mm/yyyy] : ";
    getline(cin, tanggalK);

    DBPinjam databasePinjam = ("DatabasePeminjaman.txt");
    Peminjaman dataPinjam = Peminjaman(nama, id, judul, tanggal, tanggalK);
    databasePinjam.addPeminjaman(dataPinjam);
}
//                           o
//          /(O_O)/     |       \(`-`)\                                                     
