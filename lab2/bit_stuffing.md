# Bit stuffing

O posibila metoda de framing o reprezinta **bit stuffing**. Vom folosi
folosi `01111110` ca și delimitator de cadre.

De exemplu, dacă vrem sa trimitem `0100` atunci o sa îl codam ca și
`01111110|0100|01111110`. Receptorul, doar dupa ce a primit `0111110` va incepe
sa citeasca continutul cadrului.

Ce facem in cazul in care vrem sa trimitem 6 biti de 1, `111111`? Regula este
simpla, dupa fiecare `11111`, se insereaza un 0. Astfel, delimitatorul
`01111110` nu o sa apara niciodata in continutul unui cadru.

```
Sender
111111 -> 1111101

Receiver
1111101 -> 111111
1111100 -> 111110
```

Putem dezvolta astfel un protocol foarte simplu de nivel 2. Specificatia acestui
protocol contine structura cadrului si regula definita pentru a nu intalnii
delimitatorul in datele pe care le vom transmite (payload).

```
DELIM|PAYLOAD|DELIM
```