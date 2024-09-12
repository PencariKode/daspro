/**************************************************************************************************
* Kelompok 2
* Panji Briant Depari (241402034)
* Sutanto (241402037)
* Farel Reza Saputra (241402007)
*
* Nama file : A2_241402034_01.c
*
* Tugas pertama untuk per-kelompok
* Program untuk menghitung sudah berapa hari kita hidup sejak lahir hingga waktu sekarang.
*
* Program ini menghitung total hari menggunakan "for loop" sebanyak 3x sesuai dengan kode di bawah
**************************************************************************************************/

#include <stdio.h>
#include <time.h>

int isKabisat(int);
int getTanggal(int, int);

int main() {
    //Kode di bawah berguna untuk mendapatkan waktu saat ini (current time)
    struct tm waktuNow;
    time_t unixNow;

    time(&unixNow);
    localtime_s(&waktuNow, &unixNow);
    //
    
    int hari = 0, hariAkhir = 0,
    hariSelisih = 0; //hariSelisih menunjukkan total tanggal dari awal sampai akhir bulan sesuai input user
    int dd, mm, yyyy;

    // Meminta user memasukkan tanggal lahir dengan format yang ditentukan
    printf("Masukkan tanggal lahir anda sesuai dengan format (dd-mm-yyyy) (contoh: 17-08-1997)\n");
    printf("Jangan mempersingkat tahun!\n");
    printf("Masukkan tanggal lahirmu! (dd-mm-yyyy): ");
    scanf("%d-%d-%d", &dd, &mm, &yyyy);
    //

    // Jika tahun yang di-input lebih dari tahun saat ini maka program berakhir dan memberikan pesan di bawah
    if ((yyyy > (waktuNow.tm_year+1900))) {
        printf("Tahun tidak valid!\nTidak dapat menghitung masa depan!!!");
        return 1;
    }

    // Jika penanggalan yang di-input sama dengan penanggalan sekarang, maka program tidak perlu dijalankan dan hanya akan memberi value 0 untuk variabel hari.
    if ((yyyy == (waktuNow.tm_year+1900)) && (dd == (waktuNow.tm_mday)) && (mm == (waktuNow.tm_mon+1))) {
        hari = 0;

    // Namun jika penanggalannya berbeda maka program akan dijalankan sebagaimana mestinya.
    } else {

        //Untuk menunjukkan berapa total hari pada tahun lahir yang di-input (yyyy)
        int hariAwal = isKabisat(yyyy) ? 366 : 365;

        // Melakukan pengecekan, di mana jika tahun input sama dengan tahun sekarang maka value hariAwal harus 0.
        if (yyyy == (waktuNow.tm_year+1900)) hariAwal = 0;

        //Mengitung jumlah hari yang berada pada tanggal 01 Januari tahun ke-(yyyy+1) sampai 31 Desember 1 tahun kurang dari sekarang dengan memperhatikan tahun kabisat
        for (yyyy; yyyy < (waktuNow.tm_year-1+1900); ++yyyy){
            hari += isKabisat(yyyy) ? 366 : 365;
        }

        // Kode di bawah bertugas menentukan berapa jumlah hari pada saat user lahir sampai tanggal 31 Desember tahun-yyyy
        // for (int i = 1; i <= mm; i++) {
        for (int i = 1; i < mm; i++) {
            hariSelisih += getTanggal(yyyy, i);
        }
        // hariAwal -= (hariSelisih - (getTanggal(yyyy, mm) - dd));
        hariAwal -= (hariSelisih + dd);
        //

        //Kode dibawah ini bertugas menghitung jumlah hari pada 01 Januari di tahun ini sampai dengan tanggal (tepat) saat ini
        for (int i = 1; i <= waktuNow.tm_mon; i++) {
            hariAkhir += getTanggal(waktuNow.tm_year, i);
        }
        hariAkhir += waktuNow.tm_mday;
        //

        hari += hariAkhir + hariAwal; //Menghitung semua total hari dari tanggalyang di-input hingga tanggal sekarang

    }

    // Jika value hari kurang dari 0 karena penanggalan lebih dari tanggal sekarang, maka program berhenti dan menampilkan pesan di bawah
    if (hari < 0) {
        printf("Penanggalan tidak valid!");
        return 1;
    }

    printf("\nKamu sudah hidup selama %d hari", hari); // Menampilkan output dari program
 
    return 0;
}


// Fungsi ini bertugas mengecek apakah tahun yang dimasukkan adalah kabisat atau tidak, dan akan mengembalikan nilai 0 atau 1
int isKabisat(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// Fungsi ini digunakan untuk mendapatkan total tanggal yang terdapat pada bulan ke-n dan jika tahun yang dimasukkan adalah kabisat maka bulan ke-2 akan me-return angka 29
int getTanggal(int tahun, int bulan) {
    int tgl[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isKabisat(tahun)) tgl[1] = 29;
    return tgl[bulan-1];
}




/* 
******************************************************************************************
* Kami juga menyeddiakan kode yang lebih efisien dari segi waktu seperti kode dibawah ini
* Kode dibawah menggunakan fungsi-fungsi bawaan dari compiler yang merupakan fungsi yang 
* dibuat sedemikian rupa untuk menjaga efisiensi waktu. 
* kode di bawah juga membuat size file menjadi relatif lebih kecil
* Namun kode dibawah tidak bisa menghitung hari sebelum tanggal 01 Januari 1970
******************************************************************************************

int main() {
    time_t unixInput, unixNow;
    struct tm waktuNow, waktuInput;
    // int jlhKabisat = 0;
    int dd, mm, yyyy; //Input

    // meminta user untuk memasukkan tanggal lahir mereka
    printf("Masukkan tanggal lahir anda sesuai dengan format (dd-mm-yyyy) (contoh: 17-08-1997)\n");
    printf("Jangan mempersingat tahun!\n");
    printf("Masukkan : ");
    scanf("%d-%d-%d", &dd, &mm, &yyyy);

    if(yyyy < 1970) {
        printf("Tidak dapat menghitung hari sebelum tahun 1970!");
        return 1;
    }

    waktuInput.tm_year = yyyy - 1900; //dikurangi 1900 untuk menghemat memory
    waktuInput.tm_mon = mm - 1; //tanggal dimulai dari 0
    waktuInput.tm_mday = dd;
    waktuInput.tm_hour = 0;
    waktuInput.tm_min = 0;
    waktuInput.tm_sec = 0;

    unixInput = mktime(&waktuInput); //mendapatkan unix timestamp untuk tanggal yang di-input user

    //Mendapatkan waktu sekarang
    time(&unixNow);

    // localtime_r(&waktuNow, &unixNow); //mengubah waktu dari GMT ke GMT+7
    //Jika code dibawah tidak bekerja, gunakan kode diatas! karena fungsi "localtime_(s/r) itu tergantung compiler yang digunakan"
    localtime_s(&waktuNow, &unixNow); //mengubah waktu dari GMT ke GMT+7
    
    //menghitung selisih detik antara waktu input-an dengan waktu sekarang
    double selisihDetik = (unixNow - unixInput);
    ///mengkonversi detik menjadi hari dengan memperhatikan tahun kabisat
    int selisihHari = selisihDetik / (60*60*24); // + jlhKabisat;

    printf("Kamu sudah hidup selama %d hari.", selisihHari);

    return 0;
}

 */
