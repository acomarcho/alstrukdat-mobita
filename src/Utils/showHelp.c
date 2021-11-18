#include "showHelp.h"

void showHelp() {
  printf("1. MOVE -> Untuk berpindah ke lokasi selanjutnya\n");
  printf("2. PICK_UP -> Untuk mengambil item di lokasi sekarang\n");
  printf("3. DROP_OFF -> Untuk mengantarkan item ke lokasi sekarang\n");
  printf("4. MAP -> Untuk memunculkan peta\n");
  printf("5. TO_DO -> Untuk menampilkan pesanan yang masuk ke To Do List\n");
  printf("6. IN_PROGRESS -> Untuk menampilkan pesanan yang sedang dikerjakan\n");
  printf("7. BUY -> Untuk menampilkan gadget yang dapat dibeli dan membelinya\n");
  printf("8. INVENTORY -> Untuk melihat gadget yang dimiliki dan menggunakannya\n");
  printf("9. HELP -> Untuk mengeluarkan list command dan kegunaannya\n");
  printf("10. RETURN -> Mengembalikan barang teratas di tas apabila memiliki ability return to sender.\n");
  printf("11. SAVE_GAME -> Menyimpan state game sekarang agar nanti bisa di-load.\n");
  printf("12. EXIT -> Keluar dari permainan.\n");
}