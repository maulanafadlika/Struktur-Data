## Penyelesaian Soal

### 1. Jalur Terpendek dari A ke K

Untuk menemukan jalur terpendek dari node A ke node K, kita dapat menggunakan algoritma Dijkstra. Berikut adalah graf dengan bobot pada tiap edge:

- **Nodes**: A, B, C, D, E, F, G, H, I, J, K
- **Edges dengan Bobot**:
  - (A, B, 10)
  - (A, C, 11)
  - (A, D, 10)
  - (B, E, 14)
  - (C, E, 7)
  - (C, F, 30)
  - (C, H, 20)
  - (C, G, 19)
  - (D, G, 20)
  - (E, K, 20)
  - (F, K, 15)
  - (G, I, 3)
  - (H, I, 3)
  - (H, J, 3)
  - (I, J, 3)
  - (I, K, 25)
  
Setelah semua node diproses, kita bisa menentukan jalur terpendek dari A ke K dengan mengikuti jalur yang memberikan bobot terkecil, yaitu:

    A -> C (11)
    C -> E (7)
    E -> K (20)

Total bobot adalah 11 + 7 + 20 = 38. Jadi, jalur terpendek dari A ke K adalah A -> C -> E -> K dengan total bobot 38.



### 2. Edge yang Terhubung Berdasarkan Directed Graph

Berikut adalah daftar edge yang terhubung dalam graf terarah:

- A -> B
- A -> C
- A -> D
- B -> E
- C -> E
- C -> F
- C -> G
- C -> H
- D -> G
- E -> K
- F -> K
- G -> I
- H -> I
- H -> J
- I -> J
- I -> K
