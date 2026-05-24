# Task 2 — Develop Your Own Core Loop

## Konsep Game: Rock Paper Scissors RPG

Game berbasis giliran di mana player melawan musuh menggunakan pilihan Rock, Paper, atau Scissors. Terdapat sistem streak yang memberikan bonus damage ketika player menang 2 atau 3 ronde berturut-turut.

---

## Step 1 — Core Loop

1. Player memilih aksi (Rock / Paper / Scissors)
2. Sistem menentukan aksi musuh secara random
3. Sistem meresolve pertarungan (siapa yang menang ronde ini)
4. Hitung damage berdasarkan hasil dan streak saat ini
5. Update streak (menang → streak+1, jika streak mencapai 3 → reset ke 0 setelah bonus diberikan, kalah → reset ke 0)
6. Update HP player dan musuh
7. Cek kondisi menang/kalah
8. Ulangi sampai salah satu HP = 0

---

## Step 2 — Invariant

Urutan berikut **tidak boleh diubah**:

1. Phase 1 harus sebelum Phase 3 → tidak bisa resolve tanpa aksi dari player
2. Phase 3 harus sebelum Phase 4 → damage dihitung berdasarkan hasil resolve
3. Phase 4 harus sebelum Phase 5 → streak di-update setelah damage ditentukan
4. Phase 5 harus sebelum Phase 6 → HP diupdate setelah semua kalkulasi selesai
5. Phase 6 harus sebelum Phase 7 → cek kondisi menang/kalah harus pakai HP terbaru

Komponen yang **harus selalu ada**:

1. `Character` — menyimpan HP dan nama (player & enemy)
2. `CombatResolver` — menentukan pemenang ronde berdasarkan RPS
3. `StreakTracker` — melacak streak kemenangan dan menentukan damage
4. `GameSession` — mengontrol urutan loop (invariant)

---

## Step 3 — Mutable Elements

| # | Elemen | Penjelasan |
|---|---|---|
| 1 | **Damage formula** | Saat ini `damage = 1`. Bisa diubah menjadi `attack - defense` tanpa mengubah loop |
| 2 | **Bonus damage amount** | Saat ini streak 2 = +1, streak 3 = +2. Bisa diubah nilainya tanpa menyentuh GameSession |
| 3 | **Enemy AI logic** | Saat ini random. Bisa diubah menjadi weighted atau strategis, tetap terjadi di Phase 2 |
| 4 | **Streak threshold untuk bonus** | Saat ini batas streak adalah 3. Bisa diubah ke 4 atau lebih |
| 5 | **HP awal player & enemy** | Saat ini keduanya 15. Bisa dibedakan atau diubah tanpa mengubah struktur loop |

Semua elemen di atas hanya mengubah **nilai atau cara kalkulasi** di dalam phase, bukan urutan phase itu sendiri.

---

## Refleksi

### 1. Apa struktur invariant dari game ini?

Struktur invariant adalah **urutan phase** di dalam `GameSession::PlayRound()`. Setiap ronde harus selalu menjalankan phase berikut secara berurutan:

1. Player memilih aksi
2. Enemy memilih aksi (random)
3. Resolve pertarungan
4. Hitung damage & update streak
5. Update HP
6. Cek kondisi menang/kalah

Urutan ini dijaga ketat di dalam `GameSession` dan tidak boleh berubah karena setiap phase bergantung pada hasil phase sebelumnya.

### 2. Bagian mana yang bersifat mutable?

Bagian yang bersifat mutable adalah: formula damage di `StreakTracker`, logika AI musuh di `CombatResolver`, nilai HP awal di `GameSession` constructor, besar bonus damage per streak, dan threshold batas streak. Semua perubahan ini tidak memengaruhi urutan phase sama sekali.

### 3. Jika ingin menambahkan fitur baru, kelas mana yang akan berubah?

- Ingin tambah **tipe serangan baru (misal Lizard/Spock)** → ubah `CombatResolver` saja
- Ingin tambah **sistem mana/energy** → tambah kelas baru `ManaSystem`, tidak perlu ubah `GameSession`
- Ingin ubah **cara hitung bonus damage** → ubah `StreakTracker` saja
- `GameSession` hampir tidak perlu diubah karena ia hanya mengatur urutan, bukan isi dari setiap phase

### 4. Jika urutan loop diubah, apa yang akan rusak?

- Jika **cek menang/kalah dipindah sebelum update HP** → game bisa tidak mendeteksi kematian karena HP belum diperbarui
- Jika **resolve dipindah sebelum player memilih** → tidak ada aksi yang bisa di-resolve
- Jika **update streak dipindah sebelum resolve** → streak di-update tanpa tahu siapa yang menang, menyebabkan bonus damage salah diberikan
- Jika **damage dihitung sebelum resolve** → tidak diketahui siapa yang seharusnya menerima damage
