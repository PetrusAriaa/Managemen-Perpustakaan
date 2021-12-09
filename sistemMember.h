#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;

class Membership{
    public:
    string nama;
    string nomor_telepon;
    string ID;

    Membership(string inputNama, string inputNomor_telepon, string inputID){
        Membership::nama = inputNama;
        Membership::nomor_telepon = inputNomor_telepon;
        Membership::ID = inputID;

    }

    string getString_nama(){
        return Membership::nama;
    }

    string getString_nomortelepon(){
        return Membership::nomor_telepon;
    }

    string getString_ID(){
        return Membership::ID;
    }


};

class DBMember{
    public:
    ifstream databaseI;
    ofstream databaseO;
    string fileName;

    DBMember(const char* fileName){
        DBMember::fileName = fileName;
    }

    void addDataMember(Membership data){
        DBMember::databaseO.open(DBMember::fileName, ios::app);
        DBMember::databaseO << data.getString_ID() << endl;
        DBMember::databaseO << data.getString_nama() << endl;
        DBMember::databaseO << data.getString_nomortelepon() << endl << endl;
        DBMember::databaseO.close();
    }

    void displayDataMember(Membership data){
        string nama, nomor, id;
        unsigned short index = 1;
        DBMember::databaseI.open(DBMember::fileName, ios::in);
        
        while(!DBMember::databaseI.eof()){
            getline(DBMember::databaseI, id);
            if((id == "")){
                continue;
            }
            getline(DBMember::databaseI, nama);
            getline(DBMember::databaseI, nomor);
            cout << "==============================" << endl;
            cout << "[" << index++ << "]. " << endl;
            cout << "ID\t\t: " << id << endl;
            cout << "Nama\t\t: " << nama << endl;
            cout << "Nomor Telepon\t: " << nomor << endl;
        }
        DBMember::databaseI.close();
    }

    void editDataMember(Membership data){
        string nama, nomor, line, id, temp;
        ofstream tempFile;
        DBMember::databaseI.open(DBMember::fileName);
        tempFile.open("Temp.txt", ios::app);

        cout << " \n\n      EDIT DATA MEMBER" << endl;
        cout << "==============================" << endl;
        cout << "Masukkan ID Member: ";
        cin >> id;

        while(!DBMember::databaseI.eof()){
            getline(DBMember::databaseI, line);

            if(line == id){
                tempFile << line << endl;
                getline(DBMember::databaseI, line);
                cout << "Nama\t\t: " << line << endl;
                cout << "Ubah nama\t: ";
                cin.ignore(1,'\n');
                getline(cin, nama);
                if (nama == "-"){
                    tempFile << line << endl;
                    goto update_Nomor;
                }
                line.replace(0, line.length(), nama);
                tempFile << line << endl;

                update_Nomor:
                getline(DBMember::databaseI, line);
                cout << "Nomor Telepon\t: " << line << endl;
                temp = line;
                cout << "Ubah Nomor Telepon\t: ";
                getline(cin, nomor);
                if (nomor == "-"){
                    goto lanjut;
                }
                line.replace(0, line.length(), nomor);
            }

            lanjut:
            tempFile << line << endl;
        }

        tempFile.close();
        DBMember::databaseI.close();

        remove("Database.txt");
        rename("Temp.txt", "Database.txt");
    }

    void deleteDataMember(Membership data){
        string id, line, is_continue, temp;
        ofstream tempFile;
        DBMember::databaseI.open(DBMember::fileName);
        tempFile.open("Temp.txt", ios::app);

        cout << "\n\n      DELETE DATA MEMBER" << endl;
        cout << "==============================" << endl;
        cout << "Masukkan ID Member: ";
        cin >> id;

        while(!DBMember::databaseI.eof()){
            getline(DBMember::databaseI, line);
            temp = line;
            
            if(line == id){
                getline(DBMember::databaseI, line);

                cout << "Hapus Member [" << line << "](y/n)?: ";
                cin.ignore(1,'\n');
                getline(cin, is_continue);
                if((is_continue == "Y")|(is_continue == "y")){
                    getline(DBMember::databaseI, line);
                    getline(DBMember::databaseI, line);
                    getline(DBMember::databaseI, line);
                    cout << "///  DATA DIHAPUS  ///" << endl;
                    goto label_continue;
                }else if((is_continue == "N")|(is_continue == "n")){
                    tempFile << temp << endl;
                    goto label_continue;
                }else{
                    cout << "Action Aborted" << endl;
                    tempFile << temp << endl;
                    goto label_continue;
                }
            }

            label_continue:
            tempFile << line << endl;
        }

        tempFile.close();
        DBMember::databaseI.close();

        remove("Database.txt");
        rename("Temp.txt", "Database.txt");


    }
};

int getOption();
void get_DataMember();
void get_DisplayDataMember();
void get_editDataMember();
void get_deleteDataMember();
string getID(string nomor);


void sistemMember(){

    int option = getOption();
    string is_continue;
    enum Option{ADD = 1, DISPLAY, EDIT, DELETE, BACK};

    while(option != BACK){

        switch(option){
            case ADD:
                get_DataMember();
                break;
            case DISPLAY:
                get_DisplayDataMember();
                break;
            case EDIT:
                get_editDataMember();
                break;
            case DELETE:
                get_deleteDataMember();
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
            option = getOption();
        } else if((is_continue == "N")|(is_continue == "n")){
            break;
        } else{
            cout << "Error: Invalid input"<< endl;
            goto label_continue;
        }
    }
}


////////////////////////////////////==============================================================
//ID Generator
string getID(string nomor){

	string id = "";
	for (short i = 0; i < 4; i++){
		id = id + nomor[rand()%12];
	}

    return id;
}

//pengambilan opsi
int getOption(){
    int input;

    system("cls");
    cout << "         MEMBERSHIP." << endl;
    cout << "==============================" << endl;
    cout << "[1] Tambahkan Member" << endl;
    cout << "[2] Tampilkan Data Member" << endl;
    cout << "[3] Ubah Data Member" << endl;
    cout << "[4] Hapus Data Member" << endl;
    cout << "[5] Kembali" << endl;
    cout << "==============================" << endl;
    cout << "Masukkan pilihan[1-5] : ";
    cin >> input;
    cin.ignore(1,'\n');

    return input;
}

//Passing add Data ke Database
void get_DataMember(){
    string nama, nomor_telepon, ID;
    system("cls");

    cout << "       TAMBAHKAN MEMBER" << endl;
    cout << "==============================" << endl;

    cout << "Masukkan Nama : ";
    getline(cin, nama);
    cout << "Masukkan Nomor Telepon : ";
    getline(cin, nomor_telepon);
    ID = getID(nomor_telepon);

    DBMember database = ("Database.txt");
    Membership dataMember = Membership(nama, nomor_telepon, ID);
    database.addDataMember(dataMember);
}

//Passing display Data
void get_DisplayDataMember(){
    string nama, nomor_telepon, ID;
    system("cls");
    cout << "         MEMBERSHIP." << endl;
    Membership dataMember = Membership(nama, nomor_telepon, ID);
    DBMember database = ("Database.txt");
    database.displayDataMember(dataMember);
}

//Passing edit Data di Database
void get_editDataMember(){
    string nama, nomor_telepon, ID;
    get_DisplayDataMember();

    Membership dataMember = Membership(nama, nomor_telepon, ID);
    DBMember database = ("Database.txt");
    database.editDataMember(dataMember);
}

//Passing delete Data di Database
void get_deleteDataMember(){
    string nama, nomor_telepon, ID;
    get_DisplayDataMember();

    Membership dataMember = Membership(nama, nomor_telepon, ID);
    DBMember database = ("Database.txt");
    database.deleteDataMember(dataMember);
}