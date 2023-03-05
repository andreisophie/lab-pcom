# lab-pcom

Andrei Mărunțiș

## Intrebari si probleme

1. Cum pot escapa caracterele DLE cu inca un DLE daca string-ul meu trebuie sa aiba lungime fixa? Mai jos un exemplu:

Sa presupunem ca vreau sa trimit mesajul `"A DLE"` folosind o structura Frame cu dimensiunea payload-ului de 4. Mesajul trimis va avea header-ul `"DLE STX"` si apoi se proceseaza payload-ul, astfel:

    - Litera A se copiaza pur si simplu
    - Caracterul DLE va fi escapat cu inca un caracter DLE
    - String-ul va ramane cu 1 spatiu liber la final, care va fi ocupat tot cu DLE, care va trebui escapat de asemenea, dar daca fac asta depasesc lungimea fixa a payload-ului!

Pentru a evita aceasta problema, am ignorat in receiver faptul ca orice caracter `DLE` din interiorul payload-ului este urmat de inca un `DLE`

2. Am avut probleme cu dimensiunea structurii, care, desi este declarata cu atributul packed, are dimensiunea mai mare decat ar trebui (la pasul la care inca nu am adaugat campul de timestamp, `sizeof(struct Frame)=44` desi ar trebui sa aiba dimensiunea 42 (30 payload + 4 padding-ul + 8 id-uri = 42)).

3. Aceasta problema s-a accentuat la pasul la care am adaugat timestamp-ul si am marit payload-ul la 100 octeti, structura are acum 6 octeti in plus