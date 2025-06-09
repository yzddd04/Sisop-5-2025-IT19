# Sisop-5-2025-IT-Template

## Kelompok

No | Nama | NRP
--- | --- | ---
1 |	Ahmad Yazid Arifuddin	| 5027241040
2	| Muhammad Ziddan Habibi |	5027241122
3	| Andi Naufal Zaki	| 5027241059

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan

- Jalankan `make build` di terminal
- Kemudian buka bocsh 2.8
- Load file bochsrc.txt
- Start
- Proses booting dimulai

## Dokumentasi Kode

#### Kernel.h
```c
#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "std_type.h"

extern void putInMemory(int segment, int address, char character);
extern int interrupt(int number, int AX, int BX, int CX, int DX);
unsigned int getBiosTick();

void printString(char* str);
void readString(char* buf);
void clearScreen();

#endif // __KERNEL_H__
```
File `kernel.h` adalah **header file utama** dalam proyek sistem operasi sederhana seperti *EorzeOS*. Fungsinya adalah sebagai **deklarasi fungsi-fungsi dasar kernel** yang akan digunakan di berbagai file `.c` atau `.asm`.

Secara umum, file ini berisi *deklarasi antarmuka* untuk:

1. **Menampilkan teks ke layar** (`printString`, `putInMemory`)
2. **Membaca input dari keyboard** (`readString`)
3. **Membersihkan layar** (`clearScreen`)
4. **Mengakses waktu dari BIOS** (`getBiosTick`)
5. **Memanggil interrupt BIOS dengan parameter register** (`interrupt`)

File ini **tidak berisi implementasi**, melainkan hanya memberitahu compiler bahwa fungsi-fungsi tersebut *ada dan akan didefinisikan di tempat lain*. Dengan begitu, file lain seperti `kernel.c` atau `shell.c` bisa menggunakan fungsi-fungsi ini tanpa error saat kompilasi.

Intinya:
`kernel.h` berperan sebagai **pintu masuk fungsi-fungsi dasar kernel** — agar modul lain bisa mencetak ke layar, menerima input, mengatur layar, dan memanggil layanan BIOS dengan mudah.

#### shell.h

```c
#ifndef __SHELL_H__
#define __SHELL_H__

#include "std_type.h"

void shell();
void parseCommand(char *buf, char *cmd, char arg[2][64]);
void executeCommand(char *buf);

#endif // __SHELL_H__
```

File `shell.h` adalah **header file** untuk modul *shell* dalam sistem operasi buatanmu (seperti EorzeOS). Fungsinya adalah untuk **mendeklarasikan fungsi-fungsi utama yang berkaitan dengan shell**, yaitu antarmuka tempat pengguna bisa mengetik perintah.

### Inti dari fungsinya:

` shell.h` digunakan untuk memberitahu compiler bahwa ada tiga fungsi penting yang akan diimplementasikan di file lain (kemungkinan di `shell.c`), yaitu:

1. **`shell()`**
   Fungsi utama yang menjalankan *shell loop*. Biasanya ini akan mencetak prompt, menerima input dari pengguna, memprosesnya, dan menjalankan perintah yang sesuai. Ini inti dari bagaimana pengguna berinteraksi dengan OS lewat teks.

2. **`parseCommand(char *buf, char *cmd, char arg[2][64])`**
   Memecah string input pengguna menjadi *perintah utama* (`cmd`) dan *argumen* (`arg`). Misalnya, jika pengguna mengetik:

   ```
   copy file1.txt file2.txt
   ```

   Maka:

   * `cmd = "copy"`
   * `arg[0] = "file1.txt"`
   * `arg[1] = "file2.txt"`

3. **`executeCommand(char *buf)`**
   Menjalankan perintah berdasarkan input. Fungsi ini akan memanggil fungsi lain sesuai perintah yang diminta pengguna. Misalnya, jika input `"clear"`, maka fungsi `clearScreen()` akan dipanggil.

---

### Kesimpulan

📌 **`shell.h` adalah antarmuka untuk shell command-line buatanmu**.
Fungsi-fungsinya mendukung proses:

* Menampilkan prompt dan membaca perintah (`shell`)
* Memecah input jadi perintah dan argumen (`parseCommand`)
* Menjalankan perintah dari input pengguna (`executeCommand`)

File ini sangat penting agar file lain dalam sistem tahu cara memanggil fungsi-fungsi shell tanpa perlu tahu detail implementasinya.

#### std_lib.h

```c
#ifndef __STD_LIB_H__
#define __STD_LIB_H__

#include "std_type.h"

int div(int a, int b);
int mod(int a, int b);

bool strcmp(char *str1, char *str2);
void strcpy(char *dst, char *src);
void clear(byte *buf, unsigned int size);

void atoi(char *str, int *num);
void itoa(int num, char *str);

#endif // __STD_LIB_H__
```
File `std_lib.h` adalah **header file** untuk pustaka fungsi standar (standard library) buatan sendiri dalam sistem operasi sederhana seperti *EorzeOS*.

Fungsinya adalah menyediakan **fungsi-fungsi dasar manipulasi angka, string, dan memori** yang biasanya tersedia di C standard library (`<string.h>`, `<stdlib.h>`, dll.), tetapi karena OS ini berjalan tanpa sistem operasi lain, semua harus dibuat sendiri dari nol.

---

### Fungsi-fungsi yang dideklarasikan:

1. **`int div(int a, int b)`**
   Fungsi pembagian: membagi `a` dengan `b`, mengembalikan hasil bagi bulatnya.

2. **`int mod(int a, int b)`**
   Fungsi modulo: mengembalikan sisa pembagian `a` dengan `b`.

---

3. **`bool strcmp(char *str1, char *str2)`**
   Membandingkan dua string. Mengembalikan `true` jika isi `str1` sama dengan `str2`.

4. **`void strcpy(char *dst, char *src)`**
   Menyalin isi string `src` ke `dst`.

5. **`void clear(byte *buf, unsigned int size)`**
   Mengisi array `buf` dengan nilai nol sebanyak `size` byte. Mirip dengan `memset(buf, 0, size)` di C standar.

---

6. **`void atoi(char *str, int *num)`**
   Mengubah string berisi angka (misalnya `"123"`) menjadi integer dan disimpan di `*num`. Mirip `atoi()` pada C.

7. **`void itoa(int num, char *str)`**
   Mengubah integer (`num`) menjadi string yang disimpan di `str`. Mirip `itoa()` pada C.

---

### Kesimpulan

📌 **`std_lib.h` adalah header untuk pustaka fungsi dasar OS kamu**, yang mencakup:

* Aritmetika sederhana (`div`, `mod`)
* Operasi string (`strcmp`, `strcpy`)
* Operasi memori (`clear`)
* Konversi antara string dan integer (`atoi`, `itoa`)

File ini memungkinkan kamu menulis program dan shell dengan kemampuan dasar **tanpa bergantung pada C library bawaan**, karena OS kamu berdiri sendiri dan tidak menjalankan libc standar.

#### std_type.h

```c
#ifndef __STD_TYPE_H__
#define __STD_TYPE_H__

typedef unsigned char byte;

typedef char bool;
#define true 1
#define false 0

#endif // __STD_YPE_H__
```

File `std_type.h` adalah **header file untuk definisi tipe data dasar** dalam sistem operasi buatanmu (seperti *EorzeOS*).

Karena kamu tidak menggunakan library standar C (seperti `stdint.h` atau `stdbool.h`), file ini membuat **alias tipe dan nilai boolean** yang akan digunakan di seluruh proyek.

---

### Penjelasan isi:

```c
typedef unsigned char byte;
```

Membuat alias `byte` untuk `unsigned char` (8-bit).
Digunakan untuk menyatakan data 1 byte, biasanya di memori atau buffer.

---

```c
typedef char bool;
#define true 1
#define false 0
```

Karena C tidak memiliki tipe boolean bawaan secara eksplisit (sebelum C99), kamu mendefinisikan sendiri:

* `bool` adalah alias dari `char` (cukup untuk menyimpan 0 atau 1).
* `true` diset ke `1`
* `false` diset ke `0`

---

### Kesimpulan

📌 **`std_type.h` adalah definisi dasar tipe yang dibutuhkan oleh seluruh proyek OS-mu**, supaya bisa:

* Menyatakan boolean (`true`, `false`, `bool`)
* Menyatakan byte (`byte`)

File ini penting untuk menjaga konsistensi dan kemudahan penulisan tipe data dalam kode kernel dan library kamu.









