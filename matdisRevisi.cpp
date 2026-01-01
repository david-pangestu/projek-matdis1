#include <iostream>
#include <string> 
using namespace std;

// Fungsi input standar untuk |A|, |B|, |C|
void inputNilai(string label, int &nilai) {
    do {
        cout << "Masukkan " << label << " : ";
        cin >> nilai;
        if (nilai < 0) {
            cout << "   [ERROR] Nilai himpunan tidak boleh negatif! Silakan ulangi.\n";
        }
    } while (nilai < 0);
}

// FUNGSI: Input Semesta Opsional (Validasi Negatif)
void inputSemestaOpsional(int &S, int &TidakKeduanya, int &UnionFromSemesta) {
    cout << "[INFO SEMESTA]" << endl;
    
    // Validasi Semesta tidak boleh negatif
    do {
        cout << "Masukkan Total Semesta (ketik 0 jika tidak ada/tidak diketahui): ";
        cin >> S;
        if (S < 0) cout << "   [ERROR] Semesta tidak boleh negatif!\n";
    } while (S < 0);

    if (S == 0) {
        TidakKeduanya = 0;
        UnionFromSemesta = 0;
        cout << ">> Mode: Input Manual Standar (Tanpa Semesta)\n";
    } else {
        // Validasi Tidak Keduanya tidak boleh negatif
        do {
            cout << "Masukkan Yang TIDAK keduanya : ";
            cin >> TidakKeduanya;
            if (TidakKeduanya < 0) 
                cout << "   [ERROR] Nilai tidak boleh negatif!\n";
            else if (TidakKeduanya > S) {
                cout << "   [WARNING] Tidak keduanya > Semesta. Dianggap 0.\n";
                TidakKeduanya = 0;
                break; // Keluar loop jika logic salah tapi tidak negatif (handle error logic)
            }
        } while (TidakKeduanya < 0);

        UnionFromSemesta = S - TidakKeduanya;
        cout << ">> Mode: Semesta Terdeteksi. Gabungan (|A U B|) diketahui = " << UnionFromSemesta << endl;
    }
    cout << "-------------------------------------------------------------------------\n";
}

// Validasi Irisan Parsial (Cek Negatif + Logic)
void inputValidasiIrisan(int A, int B, int &AirisanB) {
    do {
        cout << "Masukkan |A ∩ B| : ";
        cin >> AirisanB;
        
        // 1. Cek Negatif
        if (AirisanB < 0) {
            cout << "   [ERROR] Irisan tidak boleh negatif!\n";
            continue; // Ulangi loop
        }

        // 2. Cek Logika Himpunan
        if (A < B){
            if (AirisanB > A) cout << "   [ERROR] |A ∩ B| tidak boleh > |A|. Ulangi!\n";
        } else if (B < A){
            if (AirisanB > B) cout << "   [ERROR] |A ∩ B| tidak boleh > |B|. Ulangi!\n";
        } else if (A == B) {
            if (AirisanB > A && AirisanB > B) cout << "   [ERROR] Input salah. Ulangi!\n";
        }
    } while (AirisanB < 0 || AirisanB > A || AirisanB > B);
}

// Validasi Gabungan (Cek Negatif + Logic)
void inputValidasiGabungan(int A, int B, int &AgabunganB) {
    do {
        cout << "Masukkan |A ∪ B| : ";
        cin >> AgabunganB;

        // 1. Cek Negatif
        if (AgabunganB < 0) {
            cout << "   [ERROR] Gabungan tidak boleh negatif!\n";
            continue;
        }

        // 2. Cek Logika Himpunan
        if (AgabunganB > A + B) {
            cout << "   [ERROR] |A ∪ B| melebihi |A| + |B|. Ulangi!\n";
        } else if (A < B) {
            if (AgabunganB < B) cout << "   [ERROR] |A ∪ B| tidak boleh < |B|. Ulangi!\n";
        } else if (B < A) {
            if (AgabunganB < A) cout << "   [ERROR] |A ∪ B| tidak boleh < |A|. Ulangi!\n";
        }
    } while (AgabunganB < 0 || AgabunganB > A + B || AgabunganB < A || AgabunganB < B);
}

// Helper Irisan Parsial untuk 3 Himpunan (Cek Negatif)
void inputIrisanParsial(string labelA, int valA, string labelB, int valB, int &irisan) {
    do {
        cout << "Masukkan |" << labelA << " ∩ " << labelB << "| : "; 
        cin >> irisan;
        if (irisan < 0) {
             cout << "   [ERROR] Irisan tidak boleh negatif!\n";
        } else if (irisan > valA || irisan > valB) {
             cout << "   [ERROR] Irisan parsial terlalu besar. Ulangi!\n";
        }
    } while (irisan < 0 || irisan > valA || irisan > valB);
}


// --- FUNGSI UTAMA PER KASUS ---

void hitungGabunganDua() {
    int S, Tidak, UnionFromS;
    int A, B, AirisanB, AgabunganB;

    cout << "--------------------------- Hitung |A ∪ B| ------------------------------" << endl;
    inputSemestaOpsional(S, Tidak, UnionFromS);

    inputNilai("|A|", A);
    inputNilai("|B|", B);
    inputValidasiIrisan(A, B, AirisanB);

    AgabunganB = A + B - AirisanB;
    
    cout << "\n================================= HASIL =================================" << endl;
    cout << "|A ∪ B| = " << A << " + " << B << " - " << AirisanB << " = " << AgabunganB << endl;

    if (S > 0) {
        cout << "(Cek Validitas: Berdasarkan Semesta, Gabungan seharusnya = " << UnionFromS << ")";
        if (AgabunganB == UnionFromS) cout << " [COCOK]\n";
        else cout << " [TIDAK COCOK - Cek Data Soal]\n";
    }
}

void hitungIrisanDua() {
    int S, Tidak, UnionFromS;
    int A, B, AirisanB, AgabunganB;

    cout << "-------------------------- Hitung |A ∩ B| -------------------------------" << endl;
    inputSemestaOpsional(S, Tidak, UnionFromS);

    inputNilai("|A|", A);
    inputNilai("|B|", B);

    // LOGIKA HYBRID
    if (S > 0) {
        AgabunganB = UnionFromS;
        cout << "Nilai |A ∪ B| otomatis diambil dari (Semesta - Tidak Keduanya) : " << AgabunganB << endl;
    } else {
        inputValidasiGabungan(A, B, AgabunganB);
    }

    AirisanB = A + B - AgabunganB;
    cout << "\n================================= HASIL =================================" << endl;
    cout << "|A ∩ B| = " << A << " + " << B << " - " << AgabunganB << " = " << AirisanB << endl;
}

int hitungBedaSetangkup(int A, int B, int AirisanB) {
    int AbedasetangkupB = A + B - 2 * AirisanB;
    return AbedasetangkupB;
}

void hitungGabunganTiga() {
    int S, Tidak, UnionFromS;
    int A, B, C, AirisanB, AirisanC, BirisanC, ABCirisan, ABCgabungan;

    cout << "----------------------- Hitung |A ∪ B ∪ C|-------------------------------" << endl;
    inputSemestaOpsional(S, Tidak, UnionFromS);

    inputNilai("|A|", A); inputNilai("|B|", B); inputNilai("|C|", C);
    
    // Irisan parsial sudah ada validasi negatif di dalam fungsi
    inputIrisanParsial("A", A, "B", B, AirisanB);
    inputIrisanParsial("A", A, "C", C, AirisanC);
    inputIrisanParsial("B", B, "C", C, BirisanC);

    do {
        cout << "Masukkan |A ∩ B ∩ C| : "; cin >> ABCirisan;
        
        // Validasi Negatif & Logika
        if (ABCirisan < 0) {
            cout << "   [ERROR] Irisan pusat tidak boleh negatif!\n";
        } else if (ABCirisan > AirisanB || ABCirisan > AirisanC || ABCirisan > BirisanC) {
             cout << "   [ERROR] Irisan pusat terlalu besar dari irisan parsial. Ulangi!\n";
        }
    } while (ABCirisan < 0 || ABCirisan > AirisanB || ABCirisan > AirisanC || ABCirisan > BirisanC);

    ABCgabungan = A + B + C - AirisanB - AirisanC - BirisanC + ABCirisan;
    
    cout << "\n================================= HASIL =================================" << endl;
    cout << "|A ∪ B ∪ C| = " << ABCgabungan << endl;
    
    if (S > 0) {
        cout << "(Info: Berdasarkan Semesta, Total Gabungan adalah " << UnionFromS << ")\n";
    }
}


void tampilkanMenu() {
    cout << "Pilih rumus yang ingin digunakan:" << endl;
    cout << "1. Hitung |A ∪ B| (Gabungan 2 Himpunan)" << endl;
    cout << "2. Hitung |A ∩ B| (Irisan 2 Himpunan)" << endl;
    cout << "3. Hitung |A ⊕ B| (Beda Setangkup 2 Himpunan)" << endl;
    cout << "4. Hitung |A ∪ B ∪ C| (Gabungan 3 Himpunan)" << endl;
    cout << "5. Keluar" << endl;
    cout << "Pilihan anda : ";
}

int main() {
    int pilihan;
    char lanjut;
    string teksSoal;

    do {
		system("cls");
        cout << "\n=========================================================================" << endl;
        cout << "                 KALKULATOR PRINSIP INKLUSI-EKSKLUSI" << endl;
        cout << "=========================================================================" << endl;
        
        // --- INPUT SOAL ---
        cout << "Silakan ketik/paste soal anda di bawah ini (Tekan Enter jika ingin skip):" << endl;
        cout << ">> ";
        getline(cin, teksSoal); 

		cout << "\n-------------------------------------------------------------------------" << endl;
        cout << "----------------------------- SOAL ANDA ---------------------------------" << endl;
        cout << "\"" << teksSoal << "\"" << endl;
        cout << "-------------------------------------------------------------------------" << endl;

        tampilkanMenu();
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
        case 1: hitungGabunganDua(); break;
        case 2: hitungIrisanDua(); break;
        case 3: {
			int S, Tidak, UnionFromS;
			int A, B, AirisanB;
		
			cout << "-------------------- Hitung |A ⊕ B| (Beda Setangkup) --------------------" << endl;
			inputSemestaOpsional(S, Tidak, UnionFromS);

			inputNilai("|A|", A);	
			inputNilai("|B|", B);
			inputValidasiIrisan(A, B, AirisanB);
			
			cout << "\n================================= HASIL =================================" << endl;
			cout << "|A ⊕ B| = " << A << " + " << B << " - 2 * " << AirisanB << " = " << hitungBedaSetangkup(A, B, AirisanB); 
			break;
		}
        case 4: hitungGabunganTiga(); break;
        case 5: return 0;
        default: cout << "Pilihan tidak valid"; break;
        }

        cout << "\nApakah ingin lanjut hitung soal lain? (y/n) : ";
        cin >> lanjut;

    } while (lanjut == 'Y' || lanjut == 'y');

    return 0;
}
