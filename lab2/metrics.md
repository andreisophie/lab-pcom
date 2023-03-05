## Metrici

Pentru a putea studia performanta unui protocol de nivel DataLink ne intereseaza
urmatoarele metrici:

  - **Bandwidth** - se măsoară în biți / secunda și reprezinta
    cantitatea de informație care poate fi transmisa într-o unitate de
    timp pe legătura de date
  - **Delay** - se măsoară în secunde și reprezinta timpul care le ia
    unor date trimise printr-un mediu să ajungă la destinație
  - **Bandwidth delay product (BDP)** - reprezinta numarul total de biti ce se pot afla
    pe un link la un anumit moment de timp  


Legătura de date poate fi asemănata cu un cilindru în care datele sunt introduse
de către transmițător și primite de către receptor. Aria secțiunii cilindrului
reprezinta viteza de transmisie, iar înălțimea este timpul de propagare. Volumul
cilindrului determina cantitatea de informație aflată pe legătura de date, la un
anumit moment de timp. Deci, cantitatea de informație aflata pe link la un
anumit moment de timp este: Bandwidth × Delay.

![](images/bdp.png)

Tabelul de mai jos prezinta mai multe metrici pentru link-uri existente.

| Tip Link            | Bandwidth | One-Way Distance | Delay   | Bandwidth x Delay (BDP) |
|---------------------|-----------|------------------|---------|-------------------------|
| Wireless LAN        | 54 Mbps   | 50 m             | 0.15 us | 18 bits                 |
| Satellite           | 1 Gbps    | 35000 km         | 115 ms  | 230 Mb                  |
| Cross-country fiber | 10 Gbps   | 4000 km          | 40 ms   | 400 Mb                  |