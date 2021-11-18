# Tugas Besar IF2110 Algoritma dan Struktur Data

## Deskripsi Program
Program ini dibuat untuk memenuhi Tugas Besar Mata Kuliah Algoritma dan Struktur Data tahun 2021/2022. Mobilita adalah sebuah permainan yang bertujuan untuk membantu Mobita dalam melakukan tugasnya sebagai kurir. Di dalam permainan ini, pemain bertindak sebagai Mobita. Permainan ini dimulai dengan membaca file konfigurasi awal permainan atau hasil simpanan state permainan sebelumnya. Pemain diharuskan untuk mengantarkan semua pesanan yang masuk dengan waktu sesingkat mungkin. Permainan selesai ketika semua pesanan sudah diantarkan.

Program ini berhasil kami selesaikan dengan beberapa fitur, yaitu:
1. NEW GAME untuk memulai permainan
2. LOAD GAME untuk melanjutkan permainan yang telah disimpan sebelumnya
3. MOVE untuk bergerak ke lokasi yang terhubung dengan lokasi sekarang
4. PICK_UP untuk mengambil item di lokasi sekarang
5. DROP_OFF untuk mengantarkan item ke lokasi sekarang
6. MAP untuk menampilkan peta permainan
7. To_DO untuk menampiklkan pesanan yang masuk ke To Do List
8. INVENTORY untuk melihat gadget yang dimiliki pemain dan menggunakannya.
9. HELP untuk menampilkan command yang valid dan kegunaannya.
10. RETURN untuk mengembalikan barang teratas di tas apabila memiliki ability Return to Sender
11. SAVE_GAME untuk menyimpan state game sekarang untuk dilanjutkan di lain waktu
12. EXIT untuk keluar dari permainan


## Cara Kompilasi Program
1. Masuk ke dalam folder src
```bash
cd src
```
2. Kompilasi program dengan perintah gcc
```bash
gcc -o main main.c FileMachine/filemachine.c WordMachine/wordmachine.c WordMachine/charmachine.c Item/item.c LinkedList/list_linked.c LinkedList/node.c Listdin/listdin.c Map/map.c Matrix/matrix.c PColor/pcolor.c Point/point.c Queue/queue.c Time/time.c Stack/stack.c ListPos/listpos.c Utils/showState.c Utils/updatePerishables.c Utils/initializeGame.c Utils/newGame.c Utils/loadGame.c Utils/move.c Utils/handleToDo.c Utils/showHelp.c Utils/pickup.c Utils/dropoff.c Utils/inventory.c Utils/buy.c Utils/returnToSender.c Utils/saveGame.c Utils/other.c Utils/updateSenterPengecil.c Utils/exit_game.c
```

## Cara Menjalankan Program
1. Pastikan sudah berada di dalam folder `src/`
2. Pastikan sudah melakukan kompilasi program seperti instruksi di atas
3. Jalankan Executable file
Untuk Operating System Windows
```bash
main
```
Untuk Operating System Linux
```bash
./main
```

## Struktur Direktori Program
Program ini memiliki 2 Direktori:
1. `docs` yang berisi file laporan Tugas Besar
2. `src` yang berisi source code program

## Anggota Kelompok dan Pembagian Tugas
Program ini dibuat oleh Kelompok 02 Kelas K03 IF2110 - Algoritma dan Struktur Data. Adapun pembagian tugasnya adalah sebagai berikut:
| NIM | Nama  | Tugas  |
| :-----: | :-: | :-: |
| 13520117 | Hafidz Nur Rahman Ghozali | ADT Item, Queue, List, command TO_DO, IN_PROGRESS, Laporan |
| 13520119 | Marchotridyo | ADT Mesin Kata, Mesin Karakter, FIle Machine, Bangunan, List Dinamis, Matrix, Map, command MAP, Integrasi main program |
| 13520137 | Johannes Winson Sukiatmodjo | ADT ListPos, command BUY, command INVENTORY, command HELP, Laporan |
| 1352037 | Muhammad Gilang Ramadhan | ADT Time, Bag, Ability, command Move, Laporan |
| 13520145 | Steven Gianmarg H. Siahaan |  |
| 13520149 | Mohammad Hilmi Rinaldi | command DROP_OFF, laporan |
