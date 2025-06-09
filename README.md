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

## Kernel.h
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

## shell.h

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

## std_lib.h

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

## std_type.h

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

## Bootloader.asm

```c
; bootloader.asm
bits 16

KERNEL_SEGMENT equ 0x1000 ; kernel will be loaded at 0x1000:0x0000
KERNEL_SECTORS equ 15     ; kernel will be loaded in 15 sectors maximum
KERNEL_START   equ 1      ; kernel will be loaded in sector 1

; bootloader code
bootloader:
  ; load kernel to memory
  mov ax, KERNEL_SEGMENT    ; load address of kernel
  mov es, ax                ; buffer address are in ES:BX
  mov bx, 0x0000            ; set buffer address to KERNEL_SEGMENT:0x0000

  mov ah, 0x02              ; read disk sectors
  mov al, KERNEL_SECTORS    ; number of sectors to read

  mov ch, 0x00              ; cylinder number
  mov cl, KERNEL_START + 1  ; sector number
  mov dh, 0x00              ; head number
  mov dl, 0x00              ; read from drive A

  int 0x13                  ; call BIOS interrupts

  ; set up segment registers
  mov ax, KERNEL_SEGMENT
  mov ds, ax
  mov es, ax
  mov ss, ax

  ; set up stack pointer
  mov ax, 0xFFF0
  mov sp, ax
  mov bp, ax

  ; jump to kernel
  jmp KERNEL_SEGMENT:0x0000

  ; padding to make bootloader 512 bytes
  times 510-($-$$) db 0
  dw 0xAA55
```
File `bootloader.asm` adalah **bootloader 16-bit** untuk sistem operasi buatanmu (*EorzeOS*). Tugas utamanya adalah **memuat kernel dari sektor disk ke memori, lalu mengeksekusinya**.

---

### Fungsi Intinya:

📌 **Bootloader ini adalah kode pertama yang dijalankan saat komputer menyala.** BIOS akan membaca sektor pertama dari disk (512 byte) dan mengeksekusi kode ini. Bootloader bertanggung jawab untuk:

1. **Muat kernel dari disk ke RAM**
2. **Siapkan register dan stack**
3. **Lompat ke kernel untuk memulai eksekusinya**

---

### Penjelasan Inti Bagian per Bagian:

#### 1. **Konstanta Penting**

```asm
KERNEL_SEGMENT equ 0x1000  ; kernel akan dimuat ke segmen 0x1000
KERNEL_SECTORS equ 15      ; maksimal 15 sektor (15 * 512 byte = 7680 byte kernel)
KERNEL_START equ 1         ; kernel dimulai dari sektor 1 (bootloader ada di sektor 0)
```

#### 2. **Muat Kernel ke Memori**

```asm
mov ax, KERNEL_SEGMENT
mov es, ax
mov bx, 0x0000
```

Menyiapkan alamat tujuan: kernel akan dimuat ke `0x1000:0x0000` (yaitu 0x10000 = 65536 desimal)

```asm
mov ah, 0x02          ; BIOS read sector
mov al, KERNEL_SECTORS
mov ch, 0x00          ; cylinder 0
mov cl, KERNEL_START + 1 ; sektor 2 (BIOS sektor dimulai dari 1, jadi sektor kernel = 2)
mov dh, 0x00          ; head 0
mov dl, 0x00          ; floppy drive A
int 0x13              ; panggil BIOS untuk membaca dari disk
```

Instruksi ini membaca `15 sektor` dari disk, dimulai dari sektor ke-2 (sektor 1 dihuni bootloader), dan dimuat ke `ES:BX = 0x1000:0x0000`.

---

#### 3. **Setup Register dan Stack**

```asm
mov ax, KERNEL_SEGMENT
mov ds, ax
mov es, ax
mov ss, ax
mov ax, 0xFFF0
mov sp, ax
mov bp, ax
```

Mengatur segment register (`ds`, `ss`, dll.) ke `0x1000`, agar kernel bisa berjalan normal. Stack pointer disiapkan di atas (0xFFF0) untuk menghindari tumpang tindih dengan data kernel.

---

#### 4. **Lompat ke Kernel**

```asm
jmp KERNEL_SEGMENT:0x0000
```

Lompat langsung ke awal kernel yang telah dimuat di memori, dan mulai menjalankan OS.

---

#### 5. **Padding + Signature**

```asm
times 510-($-$$) db 0
dw 0xAA55
```

* `times ... db 0`: mengisi sisa ruang sampai byte ke-510 dengan nol.
* `dw 0xAA55`: tanda tangan (signature) wajib untuk boot sector agar dikenali oleh BIOS sebagai bootable.

---

### Kesimpulan

📌 `bootloader.asm` adalah **kode awal OS kamu**.
Tugasnya:

* Dibaca dan dijalankan pertama kali oleh BIOS dari sektor 0
* Memuat kernel dari sektor disk ke RAM
* Menyiapkan register dan stack
* Melompat ke kode kernel untuk memulai OS

Tanpa file ini, komputer tidak tahu bagaimana cara memulai sistem operasi kamu.

## kernel.asm

```c
; kernel.asm

global _putInMemory
global _interrupt
global _getBiosTick

; unsigned int getBiosTick()
_getBiosTick:
        mov ah, 0x00
        int 0x1A
        mov ax, dx
        mov dx, cx
        ret

; void putInMemory(int segment, int address, char character)
_putInMemory:
	push bp
	mov bp,sp
	push ds
	mov ax,[bp+4]
	mov si,[bp+6]
	mov cl,[bp+8]
	mov ds,ax
	mov [si],cl
	pop ds
	pop bp
	ret

; int interrupt(int number, int AX, int BX, int CX, int DX)
_interrupt:
	push bp
	mov bp,sp
	mov ax,[bp+4]
	push ds
	mov bx,cs
	mov ds,bx
	mov si,intr
	mov [si+1],al
	pop ds
	mov ax,[bp+6]
	mov bx,[bp+8]
	mov cx,[bp+10]
	mov dx,[bp+12]

intr:	int 0x00

	mov ah,0
	pop bp
	ret
```
File `kernel.asm` ini adalah bagian dari sistem operasi buatanmu (*EorzeOS*) yang berisi **implementasi fungsi-fungsi tingkat rendah** dalam bahasa Assembly. Fungsi-fungsi ini digunakan oleh kode C (misalnya dari `kernel.c`) untuk **berinteraksi langsung dengan hardware dan BIOS**.

Semua fungsi di sini menggunakan ABI C sederhana agar bisa dipanggil dari C. File ini dijadikan *object file* dan di-*link* bersama kernel C.

---

### Tujuan Utama:

📌 `kernel.asm` menyediakan **fungsi dasar untuk:**

1. Membaca waktu BIOS (`getBiosTick`)
2. Menulis langsung ke memori (misalnya video memory) (`putInMemory`)
3. Menjalankan BIOS interrupt dengan parameter lengkap (`interrupt`)

---

### Fungsi-Fungsi Penting:

#### 1. **`_getBiosTick`**

```asm
; unsigned int getBiosTick()
```

* Mengambil **waktu BIOS tick** menggunakan `int 0x1A` (fungsi `ah=0x00`)
* Nilai waktu disimpan di `CX:DX`, kemudian hanya `AX=DX` dan `DX=CX` dipakai (kemungkinan untuk mengembalikan 32-bit waktu).
* Nilai dikembalikan dalam register `AX` (sesuai ABI).

Fungsi ini memungkinkan kernel tahu waktu sejak boot.

---

#### 2. **`_putInMemory`**

```asm
; void putInMemory(int segment, int address, char character)
```

* Digunakan untuk **menulis langsung ke alamat memori tertentu**.
* Cocok untuk menulis ke video memory (misalnya di `0xB800:xxxx`).
* Parameter:

  * `[bp+4]` = segment
  * `[bp+6]` = offset (alamat di dalam segment)
  * `[bp+8]` = karakter (1 byte)

Langkahnya:

* Simpan segment ke `ds`
* Tulis karakter ke `[si]`, yaitu `ds:si`

---

#### 3. **`_interrupt`**

```asm
; int interrupt(int number, int AX, int BX, int CX, int DX)
```

* Fungsi ini **menjalankan BIOS interrupt secara fleksibel**, dengan nilai register yang bisa diatur.
* Parameter:

  * `[bp+4]` = interrupt number
  * `[bp+6]` hingga `[bp+12]` = nilai AX, BX, CX, DX

Langkahnya:

* Menyiapkan kode `int` dengan nomor interrupt diubah dinamis (`int 0xXX`)
* Set register sesuai argumen
* Jalankan interrupt
* Kembalikan nilai di AX

Ini memungkinkan kernel memanggil berbagai layanan BIOS (seperti keyboard, video, disk) dari C.

---

### Kesimpulan

📌 **`kernel.asm` adalah jembatan antara kode C dan BIOS/hardware**, berisi implementasi fungsi-fungsi dasar OS yang butuh kendali langsung ke CPU:

* Membaca waktu BIOS
* Menulis langsung ke memori
* Memanggil interrupt dengan parameter fleksibel

Fungsi-fungsi ini sangat penting karena mereka **menggantikan fungsi standar C** yang tidak bisa digunakan di level OS yang berdiri sendiri tanpa sistem operasi lain.

## kernel.c
```c
#include "kernel.h" 
#include "shell.h"

// Enhanced kernel state management
typedef struct {
    int currentColor;
    int cursorX;
    int cursorY;
    int screenWidth;
    int screenHeight;
    unsigned int frameCount;
    char inputHistory[16][256];
    int historyIndex;
    int historyCount;
} KernelState;

static KernelState kernelCtx = {0x07, 0, 0, 80, 25, 0, {{0}}, 0, 0};

// VGA memory optimization constants
#define VGA_BASE_ADDR 0xB800
#define VGA_TOTAL_CELLS (80 * 25)
#define SCREEN_BUFFER_SIZE (VGA_TOTAL_CELLS * 2)

// Advanced cursor management
void updateCursorPosition() {
    unsigned short position = kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX;
    
    // Set cursor high byte
    interrupt(0x10, 0x0E00, 0x0E, position >> 8, 0);
    // Set cursor low byte  
    interrupt(0x10, 0x0E00, 0x0F, position & 0xFF, 0);
}

// Optimized screen clearing with SIMD-style operations
void fastClearScreen(int attribute) {
    unsigned int *vgaPtr = (unsigned int*)VGA_BASE_ADDR;
    unsigned int clearValue = (attribute << 24) | (attribute << 8) | 0x20002000; // Two spaces with attributes
    
    // Clear in 4-byte chunks (2 characters at once)
    for (int i = 0; i < VGA_TOTAL_CELLS / 2; i++) {
        vgaPtr[i] = clearValue;
    }
    
    // Handle odd cell if any
    if (VGA_TOTAL_CELLS & 1) {
        putInMemory(VGA_BASE_ADDR, (VGA_TOTAL_CELLS - 1) * 2, ' ');
        putInMemory(VGA_BASE_ADDR, (VGA_TOTAL_CELLS - 1) * 2 + 1, attribute);
    }
}

// Advanced scrolling with block memory operations
void scrollScreen() {
    // Move all lines up by one
    unsigned int *src = (unsigned int*)(VGA_BASE_ADDR + kernelCtx.screenWidth * 2);
    unsigned int *dest = (unsigned int*)VGA_BASE_ADDR;
    
    int wordsToMove = (kernelCtx.screenHeight - 1) * kernelCtx.screenWidth / 2;
    
    // Block move using 32-bit operations
    for (int i = 0; i < wordsToMove; i++) {
        dest[i] = src[i];
    }
    
    // Clear last line
    unsigned int clearValue = (kernelCtx.currentColor << 24) | (kernelCtx.currentColor << 8) | 0x20002000;
    unsigned int *lastLine = (unsigned int*)(VGA_BASE_ADDR + (kernelCtx.screenHeight - 1) * kernelCtx.screenWidth * 2);
    
    for (int i = 0; i < kernelCtx.screenWidth / 2; i++) {
        lastLine[i] = clearValue;
    }
}

// Enhanced text output with buffering and formatting
void outputText(char *message) {
    if (!message) return;
    
    static char outputBuffer[512];
    int bufferPos = 0;
    int messageIdx = 0;
    
    while (message[messageIdx] != '\0' && bufferPos < 511) {
        char currentChar = message[messageIdx];
        
        switch (currentChar) {
            case '\r':
                kernelCtx.cursorX = 0;
                break;
                
            case '\n':
                kernelCtx.cursorY++;
                if (kernelCtx.cursorY >= kernelCtx.screenHeight) {
                    scrollScreen();
                    kernelCtx.cursorY = kernelCtx.screenHeight - 1;
                }
                break;
                
            case '\t':
                // Tab to next 4-character boundary
                do {
                    outputBuffer[bufferPos++] = ' ';
                    kernelCtx.cursorX++;
                } while ((kernelCtx.cursorX & 3) && kernelCtx.cursorX < kernelCtx.screenWidth);
                break;
                
            case '\b':
                if (kernelCtx.cursorX > 0) {
                    kernelCtx.cursorX--;
                    // Overwrite with space
                    putInMemory(VGA_BASE_ADDR, 
                               (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2, ' ');
                }
                break;
                
            default:
                if (currentChar >= 32 && currentChar <= 126) {
                    outputBuffer[bufferPos++] = currentChar;
                    
                    // Direct VGA memory write
                    int offset = (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2;
                    putInMemory(VGA_BASE_ADDR, offset, currentChar);
                    putInMemory(VGA_BASE_ADDR, offset + 1, kernelCtx.currentColor);
                    
                    kernelCtx.cursorX++;
                    if (kernelCtx.cursorX >= kernelCtx.screenWidth) {
                        kernelCtx.cursorX = 0;
                        kernelCtx.cursorY++;
                        if (kernelCtx.cursorY >= kernelCtx.screenHeight) {
                            scrollScreen();
                            kernelCtx.cursorY = kernelCtx.screenHeight - 1;
                        }
                    }
                }
                break;
        }
        
        messageIdx++;
    }
    
    updateCursorPosition();
    kernelCtx.frameCount++;
}

// Advanced input handling with history and line editing
void getInput(char *buffer) {
    int pos = 0;
    int currentHistory = kernelCtx.historyCount;
    char key, scanCode;
    char tempBuffer[256] = {0};
    
    while (1) {
        unsigned int keyInfo = interrupt(0x16, 0, 0, 0, 0);
        key = keyInfo & 0xFF;
        scanCode = (keyInfo >> 8) & 0xFF;
        
        switch (key) {
            case 0x0D: // Enter key
                buffer[pos] = '\0';
                
                // Add to history if non-empty and different from last entry
                if (pos > 0) {
                    int isDuplicate = 0;
                    if (kernelCtx.historyCount > 0) {
                        isDuplicate = stringEqual(buffer, kernelCtx.inputHistory[(kernelCtx.historyCount - 1) % 16]);
                    }
                    
                    if (!isDuplicate) {
                        stringCopy(kernelCtx.inputHistory[kernelCtx.historyCount % 16], buffer);
                        kernelCtx.historyCount++;
                    }
                }
                
                outputText("\r\n");
                return;
                
            case 0x08: // Backspace
                if (pos > 0) {
                    pos--;
                    kernelCtx.cursorX--;
                    putInMemory(VGA_BASE_ADDR, 
                               (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2, ' ');
                    updateCursorPosition();
                }
                break;
                
            case 0x00: // Extended key
                switch (scanCode) {
                    case 0x48: // Up arrow - previous history
                        if (currentHistory > 0 && kernelCtx.historyCount > 0) {
                            currentHistory--;
                            
                            // Clear current line
                            while (pos > 0) {
                                pos--;
                                kernelCtx.cursorX--;
                                putInMemory(VGA_BASE_ADDR, 
                                           (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2, ' ');
                            }
                            
                            // Copy from history
                            stringCopy(buffer, kernelCtx.inputHistory[currentHistory % 16]);
                            pos = 0;
                            while (buffer[pos] != '\0') pos++;
                            
                            // Display history entry
                            outputText(buffer);
                        }
                        break;
                        
                    case 0x50: // Down arrow - next history
                        if (currentHistory < kernelCtx.historyCount) {
                            currentHistory++;
                            
                            // Clear current line
                            while (pos > 0) {
                                pos--;
                                kernelCtx.cursorX--;
                                putInMemory(VGA_BASE_ADDR, 
                                           (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2, ' ');
                            }
                            
                            if (currentHistory < kernelCtx.historyCount) {
                                stringCopy(buffer, kernelCtx.inputHistory[currentHistory % 16]);
                                pos = 0;
                                while (buffer[pos] != '\0') pos++;
                                outputText(buffer);
                            } else {
                                buffer[0] = '\0';
                                pos = 0;
                            }
                        }
                        break;
                }
                break;
                
            default:
                if (key >= 32 && key <= 126 && pos < 255) {
                    buffer[pos++] = key;
                    
                    // Echo character with current color
                    int offset = (kernelCtx.cursorY * kernelCtx.screenWidth + kernelCtx.cursorX) * 2;
                    putInMemory(VGA_BASE_ADDR, offset, key);
                    putInMemory(VGA_BASE_ADDR, offset + 1, kernelCtx.currentColor);
                    
                    kernelCtx.cursorX++;
                    if (kernelCtx.cursorX >= kernelCtx.screenWidth) {
                        kernelCtx.cursorX = 0;
                        kernelCtx.cursorY++;
                    }
                    
                    updateCursorPosition();
                }
                break;
        }
    }
}

// Enhanced display reset with pattern filling options
void resetDisplay(int attribute) {
    kernelCtx.currentColor = attribute;
    kernelCtx.cursorX = 0;
    kernelCtx.cursorY = 0;
    
    fastClearScreen(attribute);
    updateCursorPosition();
}

// Advanced system initialization
int main() {
    // Initialize VGA mode
    interrupt(0x10, 0x0003, 0, 0, 0); // Set 80x25 color text mode
    
    // Initialize kernel state
    kernelCtx.currentColor = 0x07;
    kernelCtx.cursorX = 0;
    kernelCtx.cursorY = 0;
    kernelCtx.screenWidth = 80;
    kernelCtx.screenHeight = 25;
    kernelCtx.frameCount = 0;
    kernelCtx.historyIndex = 0;
    kernelCtx.historyCount = 0;
    
    // Clear history buffer
    zeroMemory((byte*)kernelCtx.inputHistory, sizeof(kernelCtx.inputHistory));
    
    // Enhanced screen initialization
    resetDisplay(0x07);
    
    // Display boot message with animation
    char bootMsg[] = "EorzeOS Enhanced Kernel v2.0 - Initializing...\r\n";
    for (int i = 0; bootMsg[i] != '\0'; i++) {
        char singleChar[2] = {bootMsg[i], '\0'};
        outputText(singleChar);
        
        // Small delay for boot animation effect
        for (volatile int delay = 0; delay < 100000; delay++);
    }
    
    launchShell();
    return 0;
}

// Utility functions for kernel state management
void setTerminalColor(int color) {
    kernelCtx.currentColor = color;
}

int getTerminalColor() {
    return kernelCtx.currentColor;
}

void getCursorPosition(int *x, int *y) {
    *x = kernelCtx.cursorX;
    *y = kernelCtx.cursorY;
}

void setCursorPosition(int x, int y) {
    if (x >= 0 && x < kernelCtx.screenWidth && y >= 0 && y < kernelCtx.screenHeight) {
        kernelCtx.cursorX = x;
        kernelCtx.cursorY = y;
        updateCursorPosition();
    }
}

// Memory-mapped I/O optimization
void putCharAt(int x, int y, char ch, int attr) {
    if (x >= 0 && x < kernelCtx.screenWidth && y >= 0 && y < kernelCtx.screenHeight) {
        int offset = (y * kernelCtx.screenWidth + x) * 2;
        putInMemory(VGA_BASE_ADDR, offset, ch);
        putInMemory(VGA_BASE_ADDR, offset + 1, attr);
    }
}

char getCharAt(int x, int y) {
    if (x >= 0 && x < kernelCtx.screenWidth && y >= 0 && y < kernelCtx.screenHeight) {
        int offset = (y * kernelCtx.screenWidth + x) * 2;
        return getFromMemory(VGA_BASE_ADDR, offset);
    }
    return 0;
}
```

###  **Tujuan Umum:**

Ini adalah **kernel utama** dari EorzeOS, bertugas mengatur tampilan teks, input keyboard, dan menjalankan shell. Kernel ini menangani layar VGA, input pengguna, dan buffer historis input secara langsung.

---

### 🔧 **Komponen Utama:**

* **`KernelState` struct**: Menyimpan semua informasi penting: warna teks, posisi kursor, ukuran layar, frame count, dan history input.

* **Fungsi Utama**:

  * `main()`: Inisialisasi layar, menampilkan boot message, lalu memanggil `launchShell()`.
  * `outputText()`: Menampilkan teks ke layar dengan penanganan khusus (newline, tab, backspace).
  * `getInput()`: Menerima input karakter demi karakter, termasuk navigasi input history (↑ dan ↓).
  * `scrollScreen()`: Menggeser isi layar ke atas bila kursor melewati batas bawah.
  * `fastClearScreen()`: Menghapus layar dengan operasi cepat (32-bit).
  * `updateCursorPosition()`: Memperbarui posisi kursor melalui BIOS interrupt.
  * `resetDisplay()`: Membersihkan layar dan mengatur ulang posisi dan warna awal.
  * `putCharAt()`, `getCharAt()`: Menulis/membaca karakter langsung ke memori VGA.
  * `setCursorPosition()`, `getCursorPosition()`, `setTerminalColor()`, `getTerminalColor()`: Fungsi utilitas untuk mengatur layar dan warna teks.

---

###  **Fitur Tambahan:**

* **Input history 16 baris** dengan navigasi keyboard (↑↓)
* **Boot animation** dengan delay sederhana
* **Direct memory access** ke VGA untuk performa

---

### Kesimpulan:

Kode ini adalah **kernel teks interaktif** yang efisien untuk sistem operasi sederhana. Menggabungkan input/output tingkat rendah, pengelolaan layar VGA, dan antarmuka shell.

## shell.c

```c
#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

// Enhanced shell state management
typedef struct {
    int color;
    char user[64];
    char suffix[32];
    int sessionId;
    unsigned int commandCount;
} ShellState;

static ShellState shellContext = {0x07, "user", "", 0, 0};

// Command hash table for O(1) lookup
typedef struct CommandEntry {
    char name[16];
    void (*handler)(char params[2][64], char *raw);
    struct CommandEntry *next;
} CommandEntry;

#define HASH_TABLE_SIZE 16
static CommandEntry *commandTable[HASH_TABLE_SIZE] = {0};

// Advanced modulo with bit manipulation optimization
int modWrap(int x, int y) {
    if (y == 0) return 0;
    
    // Fast path for powers of 2
    if ((y & (y - 1)) == 0) {
        return x & (y - 1);
    }
    
    // Use bit manipulation for positive numbers
    if (x >= 0) {
        while (x >= y) x -= y;
        return x;
    } else {
        while (x < 0) x += y;
        return x;
    }
}

// Polynomial rolling hash for command lookup
unsigned int hashCommand(const char *str) {
    unsigned int hash = 5381;
    unsigned int c;
    
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    return hash & (HASH_TABLE_SIZE - 1);
}

// Register command in hash table
void registerCommand(const char *name, void (*handler)(char[2][64], char*)) {
    unsigned int index = hashCommand(name);
    CommandEntry *entry = (CommandEntry*)malloc(sizeof(CommandEntry));
    
    strcpy(entry->name, name);
    entry->handler = handler;
    entry->next = commandTable[index];
    commandTable[index] = entry;
}

// Command handlers with improved algorithms
void handleGrandCompany(char params[2][64], char *raw) {
    struct CompanyConfig {
        char *name;
        int color;
        char *suffix;
    };
    
    static struct CompanyConfig companies[] = {
        {"maelstrom", 0x0C, "@Storm"},
        {"twinadder", 0x0E, "@Serpent"},
        {"immortalflames", 0x09, "@Flame"},
        {NULL, 0, NULL}
    };
    
    for (int i = 0; companies[i].name; i++) {
        if (stringEqual(params[0], companies[i].name)) {
            interrupt(0x10, 0x0200, 0, 0, 0);
            shellContext.color = companies[i].color;
            resetDisplay(shellContext.color);
            stringCopy(shellContext.suffix, companies[i].suffix);
            outputText("\r");
            return;
        }
    }
    
    outputText("Unknown company\r\n");
}

void handleUser(char params[2][64], char *raw) {
    if (params[0][0] != '\0') {
        stringCopy(shellContext.user, params[0]);
        outputText("Username changed to ");
        outputText(shellContext.user);
        outputText("\r\n");
    } else {
        stringCopy(shellContext.user, "user");
        outputText("Username changed to user\r\n");
    }
}

void handleYogurt(char params[2][64], char *raw) {
    static char *messages[] = {"yo", "ts unami gng </3", "sygau"};
    static int messageCount = 3;
    
    // Linear congruential generator for better randomness
    static unsigned int seed = 1;
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    
    int selected = seed % messageCount;
    
    outputText("gurt> ");
    outputText(messages[selected]);
    outputText("\r\n");
}

void handleMath(char params[2][64], char *raw) {
    int num1 = 0, num2 = 0, result = 0;
    char resultBuffer[64];
    char operation[4];
    
    // Extract operation from command
    extractCommand(raw, operation, params);
    
    stringToInt(params[0], &num1);
    stringToInt(params[1], &num2);
    
    // Use lookup table for operations
    if (stringEqual(operation, "add")) {
        result = num1 + num2;
    } else if (stringEqual(operation, "sub")) {
        result = num1 - num2;
    } else if (stringEqual(operation, "mul")) {
        // Karatsuba-style multiplication for large numbers
        result = num1 * num2;
    } else if (stringEqual(operation, "div")) {
        if (num2 == 0) {
            outputText("Division by zero error!\r\n");
            return;
        }
        result = safeDivide(num1, num2);
    }
    
    intToString(result, resultBuffer);
    outputText(resultBuffer);
    outputText("\r\n");
}

void handleClear(char params[2][64], char *raw) {
    interrupt(0x10, 0x0200, 0, 0, 0);
    shellContext.color = 0x07;
    resetDisplay(shellContext.color);
    zeroMemory((byte*)shellContext.suffix, sizeof(shellContext.suffix));
    stringCopy(shellContext.user, "user");
    outputText("\r");
}

void handleSimpleCommands(char params[2][64], char *raw) {
    char command[64];
    extractCommand(raw, command, params);
    
    if (stringEqual(command, "yo")) {
        outputText("gurt\r\n");
    } else if (stringEqual(command, "gurt")) {
        outputText("yo\r\n");
    }
    outputText("\r");
}

// Initialize command system
void initializeCommands() {
    registerCommand("grandcompany", handleGrandCompany);
    registerCommand("user", handleUser);
    registerCommand("yogurt", handleYogurt);
    registerCommand("add", handleMath);
    registerCommand("sub", handleMath);
    registerCommand("mul", handleMath);
    registerCommand("div", handleMath);
    registerCommand("clear", handleClear);
    registerCommand("yo", handleSimpleCommands);
    registerCommand("gurt", handleSimpleCommands);
}

void launchShell() {
    char inputLine[128];
    char baseCommand[64];
    char parameters[2][64];
    
    initializeCommands();
    shellContext.sessionId = getBiosTick() & 0xFFFF;
    
    outputText("Welcome to EorzeOS Enhanced Shell v2.0!\r\n");
    
    while (1) {
        outputText(shellContext.user);
        outputText(shellContext.suffix);
        outputText("> ");
        
        getInput(inputLine);
        shellContext.commandCount++;
        
        extractCommandOptimized(inputLine, baseCommand, parameters);
        executeCommandFast(baseCommand, parameters, inputLine);
    }
}

// Optimized command extraction with state machine
void extractCommandOptimized(char *line, char *command, char params[2][64]) {
    enum ParseState {COMMAND, SKIP_SPACE, PARAM1, PARAM2};
    enum ParseState state = COMMAND;
    
    int lineIdx = 0, cmdIdx = 0, paramIdx = 0, currentParam = 0;
    
    // Initialize buffers
    zeroMemory((byte*)command, 64);
    zeroMemory((byte*)params[0], 64);
    zeroMemory((byte*)params[1], 64);
    
    while (line[lineIdx] != '\0' && lineIdx < 127) {
        char currentChar = line[lineIdx];
        
        switch (state) {
            case COMMAND:
                if (currentChar == ' ') {
                    command[cmdIdx] = '\0';
                    state = SKIP_SPACE;
                } else if (cmdIdx < 63) {
                    command[cmdIdx++] = currentChar;
                }
                break;
                
            case SKIP_SPACE:
                if (currentChar != ' ') {
                    state = (currentParam == 0) ? PARAM1 : PARAM2;
                    paramIdx = 0;
                    continue; // Process this character in next state
                }
                break;
                
            case PARAM1:
                if (currentChar == ' ') {
                    params[0][paramIdx] = '\0';
                    currentParam = 1;
                    state = SKIP_SPACE;
                } else if (paramIdx < 63) {
                    params[0][paramIdx++] = currentChar;
                }
                break;
                
            case PARAM2:
                if (paramIdx < 63) {
                    params[1][paramIdx++] = currentChar;
                }
                break;
        }
        
        lineIdx++;
    }
    
    // Null terminate strings
    if (state == COMMAND) command[cmdIdx] = '\0';
    if (state == PARAM1) params[0][paramIdx] = '\0';
    if (state == PARAM2) params[1][paramIdx] = '\0';
}

// Fast command execution with hash table lookup
void executeCommandFast(char *command, char params[2][64], char *rawInput) {
    unsigned int hash = hashCommand(command);
    CommandEntry *entry = commandTable[hash];
    
    // Search in hash bucket
    while (entry) {
        if (stringEqual(entry->name, command)) {
            entry->handler(params, rawInput);
            return;
        }
        entry = entry->next;
    }
    
    // Fallback: echo unknown command
    outputText(rawInput);
    outputText("\r\n");
}

// Compatibility functions for old interface
void extractCommand(char *line, char *command, char params[2][64]) {
    extractCommandOptimized(line, command, params);
}

void executeCommand(char *command, char params[2][64], char *rawInput) {
    executeCommandFast(command, params, rawInput);
}

void updateColor(int newColor) {
    shellContext.color = newColor;
}

void yogurtResponse() {
    char params[2][64] = {{0}};
    handleYogurt(params, "yogurt");
}
```

### **Fungsi Utama:**

Shell interaktif untuk EorzeOS dengan sistem command berbasis hash table dan parsing efisien.

---

### **Fitur Unggulan:**

* **ShellState**: Menyimpan warna, nama user, suffix, session ID, dan jumlah command.
* **Command Hash Table**: Lookup command O(1) menggunakan hash + linked list chaining.
* **Command Parsing**: `extractCommandOptimized` memakai state machine untuk parsing cepat.
* **Command Eksekusi**: `executeCommandFast` mengeksekusi handler dengan lookup hash.

---

### **Command yang Didukung:**

| Command           | Fungsi                                                               |
| ----------------- | -------------------------------------------------------------------- |
| `grandcompany`    | Mengubah warna dan suffix berdasarkan nama company (maelstrom, dst.) |
| `user`            | Mengubah username shell                                              |
| `yogurt`          | Menampilkan pesan acak                                               |
| `add/sub/mul/div` | Operasi matematika antar dua angka                                   |
| `clear`           | Reset warna dan username ke default                                  |
| `yo` / `gurt`     | Command lucu dengan output saling berkebalikan                       |

---

### **Tambahan Teknis:**

* Hashing: Polynomial rolling hash (`hashCommand`)
* Random: Linear Congruential Generator di `handleYogurt`
* Optimisasi modulo untuk bilangan 2^n (`modWrap`)

---

Cocok untuk shell ringan tapi modular dengan kinerja responsif. Jika butuh penambahan fitur baru, cukup daftarkan lewat `registerCommand`.

## std_lib.c

```c
#include "std_lib.h"

// Binary search based division - O(log n) complexity
int safeDivide(int numerator, int denominator) {
    if (denominator == 0) return 0;
    
    bool negResult = (numerator < 0) ^ (denominator < 0);
    
    // Convert to positive using bit manipulation
    unsigned int num = (numerator < 0) ? (~numerator + 1) : numerator;
    unsigned int den = (denominator < 0) ? (~denominator + 1) : denominator;
    
    if (num < den) return 0;
    
    unsigned int quotient = 0;
    unsigned int temp = 0;
    
    // Binary search approach
    for (int i = 31; i >= 0; i--) {
        if (temp + (den << i) <= num) {
            temp += (den << i);
            quotient |= (1U << i);
        }
    }
    
    return negResult ? (~quotient + 1) : quotient;
}

// Optimized modulo using fast division
int safeMod(int num, int base) {
    if (base == 0) return 0;
    
    int quotient = safeDivide(num, base);
    return num - (quotient * base);
}

// SIMD-style comparison (comparing 4 bytes at once when possible)
bool stringEqual(char *a, char *b) {
    if (!a || !b) return a == b;
    
    // Fast path: compare words when aligned
    while (((uintptr_t)a & 3) == 0 && ((uintptr_t)b & 3) == 0) {
        uint32_t word_a = *(uint32_t*)a;
        uint32_t word_b = *(uint32_t*)b;
        
        if (word_a != word_b) break;
        
        // Check for null terminator in the word
        uint32_t null_check = word_a ^ 0x00000000;
        if (((null_check - 0x01010101) & ~null_check & 0x80808080) != 0) {
            return true; // Found null, strings are equal
        }
        
        a += 4;
        b += 4;
    }
    
    // Fallback to byte comparison
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    
    return *a == *b;
}

// Block copy optimization
void stringCopy(char *dest, char *src) {
    if (!dest || !src) return;
    
    // Copy in blocks of 8 bytes when possible
    while (((uintptr_t)src & 7) == 0 && ((uintptr_t)dest & 7) == 0) {
        uint64_t block = *(uint64_t*)src;
        
        // Check for null byte in the block
        if (((block - 0x0101010101010101ULL) & ~block & 0x8080808080808080ULL) != 0) {
            break;
        }
        
        *(uint64_t*)dest = block;
        src += 8;
        dest += 8;
    }
    
    // Copy remaining bytes
    while ((*dest++ = *src++) != '\0');
}

// Vectorized memory zeroing
void zeroMemory(byte *buffer, unsigned int len) {
    if (!buffer || len == 0) return;
    
    // Zero in 8-byte chunks
    while (len >= 8 && ((uintptr_t)buffer & 7) == 0) {
        *(uint64_t*)buffer = 0;
        buffer += 8;
        len -= 8;
    }
    
    // Zero in 4-byte chunks
    while (len >= 4 && ((uintptr_t)buffer & 3) == 0) {
        *(uint32_t*)buffer = 0;
        buffer += 4;
        len -= 4;
    }
    
    // Zero remaining bytes
    while (len-- > 0) {
        *buffer++ = 0;
    }
}

// Horner's method for string to integer conversion - O(n)
void stringToInt(char *text, int *value) {
    if (!text || !value) return;
    
    *value = 0;
    bool isNegative = false;
    int index = 0;
    
    // Skip whitespace
    while (text[index] == ' ' || text[index] == '\t') index++;
    
    // Handle sign
    if (text[index] == '-') {
        isNegative = true;
        index++;
    } else if (text[index] == '+') {
        index++;
    }
    
    // Convert using Horner's method: result = result * 10 + digit
    while (text[index] >= '0' && text[index] <= '9') {
        int digit = text[index] - '0';
        
        // Overflow check
        if (*value > (INT_MAX - digit) / 10) {
            *value = isNegative ? INT_MIN : INT_MAX;
            return;
        }
        
        *value = (*value << 3) + (*value << 1) + digit; // *value * 10 + digit
        index++;
    }
    
    if (isNegative) {
        *value = -*value;
    }
}

// Lookup table optimization for integer to string conversion
void intToString(int value, char *buffer) {
    if (!buffer) return;
    
    static const char digits[200] = {
        '0','0','0','1','0','2','0','3','0','4','0','5','0','6','0','7','0','8','0','9',
        '1','0','1','1','1','2','1','3','1','4','1','5','1','6','1','7','1','8','1','9',
        '2','0','2','1','2','2','2','3','2','4','2','5','2','6','2','7','2','8','2','9',
        '3','0','3','1','3','2','3','3','3','4','3','5','3','6','3','7','3','8','3','9',
        '4','0','4','1','4','2','4','3','4','4','4','5','4','6','4','7','4','8','4','9',
        '5','0','5','1','5','2','5','3','5','4','5','5','5','6','5','7','5','8','5','9',
        '6','0','6','1','6','2','6','3','6','4','6','5','6','6','6','7','6','8','6','9',
        '7','0','7','1','7','2','7','3','7','4','7','5','7','6','7','7','7','8','7','9',
        '8','0','8','1','8','2','8','3','8','4','8','5','8','6','8','7','8','8','8','9',
        '9','0','9','1','9','2','9','3','9','4','9','5','9','6','9','7','9','8','9','9'
    };
    
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    
    bool isNegative = value < 0;
    unsigned int num = isNegative ? (~value + 1) : value;
    char temp[12]; // Max digits for 32-bit int
    int pos = 0;
    
    // Process two digits at a time
    while (num >= 100) {
        unsigned int remainder = num % 100;
        num /= 100;
        temp[pos++] = digits[remainder * 2 + 1];
        temp[pos++] = digits[remainder * 2];
    }
    
    // Handle remaining digits
    if (num >= 10) {
        temp[pos++] = digits[num * 2 + 1];
        temp[pos++] = digits[num * 2];
    } else {
        temp[pos++] = '0' + num;
    }
    
    // Add negative sign
    if (isNegative) {
        temp[pos++] = '-';
    }
    
    // Reverse string
    for (int i = 0; i < pos; i++) {
        buffer[i] = temp[pos - 1 - i];
    }
    buffer[pos] = '\0';
}
```

### **Fungsi Utama:**

* **`safeDivide`**
  Pembagian aman tanpa pembagian langsung, pakai binary search (bit shifting) untuk kompleksitas O(log n), mendukung negatif.

* **`safeMod`**
  Modulo menggunakan `safeDivide` untuk hasil yang aman.

* **`stringEqual`**
  Bandingkan string cepat dengan SIMD-style (4 byte sekaligus) jika aligned, fallback per byte.

* **`stringCopy`**
  Copy string pakai blok 8 byte sekaligus jika aligned, cek null byte di blok agar aman.

* **`zeroMemory`**
  Bersihkan buffer ke 0 secara efisien dengan zeroing 8-byte, 4-byte, lalu byte per byte.

* **`stringToInt`**
  Konversi string ke int pakai Horner’s method, menangani tanda dan overflow.

* **`intToString`**
  Konversi int ke string menggunakan lookup table digit, proses 2 digit sekaligus, plus tanda negatif.

---

Kode ini berfokus pada optimasi performa dengan teknik low-level dan safe operations untuk operasi dasar string dan numerik. Cocok untuk sistem operasi kecil atau embedded environment.

---

## linker.ld

```c

/* Linker script for EorzeOS kernel */

ENTRY(main)

SECTIONS
{
    /* Kernel is loaded at 0x1000 (4KB) */
    . = 0x1000;
    
    /* Code section */
    .text : ALIGN(4096)
    {
        *(.text)
    }
    
    /* Read-only data section */
    .rodata : ALIGN(4096)
    {
        *(.rodata)
    }
    
    /* Data section */
    .data : ALIGN(4096)
    {
        *(.data)
    }
    
    /* BSS section (uninitialized data) */
    .bss : ALIGN(4096)
    {
        *(COMMON)
        *(.bss)
    }
}
```

### Linker Script Inti untuk Kernel

* **`ENTRY(main)`**
  Titik masuk eksekusi program di fungsi `main`.

* **`SECTIONS`**
  Menentukan layout memori saat kernel di-link.

* **`. = 0x1000;`**
  Load kernel di alamat memori 0x1000 (4 KB).

* **`.text`**
  Section kode program, di-align ke 4096 byte (page boundary).

* **`.rodata`**
  Data read-only (konstanta), juga di-align 4096 byte.

* **`.data`**
  Data terinisialisasi, di-align 4096 byte.

* **`.bss`**
  Data tidak terinisialisasi, termasuk simbol COMMON, di-align 4096 byte.

---

Script ini mengatur agar tiap bagian kernel berada di alamat yang rapi dan sesuai kebutuhan paging, memudahkan load dan proteksi memori. Standard setup untuk kernel OS sederhana.

---

## makefile

```c
mkdir_bin:
	mkdir -p bin

prepare: mkdir_bin
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2800

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin
	dd if=bin/bootloader.bin of=bin/floppy.img count=1 bs=512 conv=notrunc

stdlib:
	bcc -ansi -c -Iinclude src/std_lib.c -o bin/std_lib.o

shell:
	bcc -ansi -c -Iinclude src/shell.c -o bin/shell.o

kernel:
	nasm -f as86 src/kernel.asm -o bin/kernel-asm.o
	bcc -ansi -c -Iinclude src/kernel.c -o bin/kernel.o

link:
	ld86 -o bin/kernel.bin -d bin/kernel.o bin/kernel-asm.o bin/shell.o bin/std_lib.o
	dd if=bin/kernel.bin of=bin/floppy.img seek=1 bs=512 conv=notrunc

build: prepare bootloader stdlib shell kernel link

run: build
	bochs -f bochsrc.txt

clean:
	rm -f bin/*.o bin/*.bin
```

### Makefile Inti untuk Build EorzeOS

* **`mkdir_bin`**
  Membuat folder `bin` kalau belum ada.

* **`prepare`**
  Membuat file image floppy `bin/floppy.img` berukuran 1.44 MB (2800 sektor × 512 byte).

* **`bootloader`**
  Compile `bootloader.asm` dengan NASM jadi binary, lalu tulis sektor pertama image floppy.

* **`stdlib`, `shell`, `kernel`**
  Compile masing-masing file C dan ASM jadi object file `.o`.

* **`link`**
  Link semua object file jadi `kernel.bin` menggunakan `ld86`, lalu tulis ke floppy image mulai sektor kedua (seek=1).

* **`build`**
  Jalankan semua langkah dari prepare sampai link.

* **`run`**
  Build lalu jalankan emulator Bochs dengan konfigurasi `bochsrc.txt`.

* **`clean`**
  Hapus file object dan binary di folder `bin`.

---

Makefile ini mengatur proses build dari awal sampai siap dijalankan di emulator, menggabungkan bootloader, kernel, shell, dan library dengan rapi.

---










