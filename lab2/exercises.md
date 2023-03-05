# Exercitii
In cele ce urmeaza vom punele bazele unui mic protocol de nivel DataLink peste un **mediu fizic
ideal** (fara pierderi/coruperi).

> **Scheletul laboratorului se găsește
[aici](https://gitlab.cs.pub.ro/pcom/pcom-laboratoare-public/-/tree/master/lab2),
tot acolo se găsește și un README.md cu funcționalitatea disponibila**.

**1\.** Vrem sa implementam un protocol de nivel DataLink care folosește
tehnica byte stuffing pentru a trimite siruri de caractere ca payload. La aceast
exercitiu o sa presupunem o transmisie de tip Point-to-Point asa ca nu trebuie
sa specificam destinatia in protocol. Pentru simplitate, payload va avea mereu
30 de bytes si nu vom include un camp `size` in header. Frame-ul il putem
structura astfel:

```C
/* Atributul este folosit pentru a anunta compilatorul sa nu alinieze structura */    
__attribute__((packed))    
/* DELIM | DATE | DELIM */    
struct Frame {    
    char frame_delim_start[2]; /* DEL STX */    
    char payload[30];  /* Datele pe care vrem sa le transmitem */    
    char frame_delim_end[2]; /* DEL ETX */    
};
```

---
**NOTE**

Executați scriptul `./run_experiment.sh` pentru a observa un demo al
funcționalitaților disponibile. Acesta porneste un simulator de nivel
fizic si ruleaza `./recv` si `./send`.

Un sir de caractere precum `char buffer[1024]` reprezintă un sir de bytes,
astfel putem face operații precum `((struct Frame) buffer)->frame_delim[0]` sau
`memcpy(buffer, &frame, sizeof(struct Frame))`.

---

**2\.** Acum ca am reușit sa trimitem primele noastre frame-uri care conțin
șiruri de caractere, vrem sa extindem protocolul pentru a functionea intr-un
mediu de transmisie Point-to-Multipoint. Avem mai multe dispozitive legate la
acelasi cablu (e.g. dispozitivele masoarara tensiunea de pe cablu) si fiecare este
identificat printr-un intreg. 

Extindem protocolului nostru prin adaugarea a doua noi campuri, sursa si
destinatie. Structura de date de mai jos reprezinta continutul frame-ului pe
care vrem sa il transmitem. Adaptati atat implementarea protocolului din
sender cat si din receiver pentru a functiona peste noile constrangeri.

```C
/* Atributul este folosit pentru a anunta compilatorul sa nu alinieze structura */
__attribute__((packed))
/* DELIM | SOURCE | DEST | PAYLOAD | DELIM */
struct Frame {
	char frame_delim_start[2]; /* DEL STX */
	int source; /* Identificator SURSA */
	int dest; /* Identificator DESTINATIE */
	char payload[30]; /* Datele pe care vrem sa le transmitem */
	char frame_delim_end[2]; /* DEL ETX */
};
```

**3\.**
Vrem sa masuram delay-ul pentru a transmite un frame de 100 bytes si unul de
300. In sender vom trimite un frame ce contine un timestamp, in receiver vom
masura latenta(diferenta de timp intre timestamp si timpul curent). Ce observam?
(Puteti folosi orice metoda de masurare a timpului precum cele prezente
[articolul
urmator](https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9).
