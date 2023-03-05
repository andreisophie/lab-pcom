# Framing

În general, nu suntem interesați in a lucra cu date la nivel de biți.
Aplicațiile pe care le dezvoltăm lucrează cu mesaje, structuri sau fișiere
complete. Nivelul fizic ne permite să transmitem un flux de biți de la un
dispozitiv la altul, dar datele pe care le transmitem sunt structurate în
**blocuri la nivel logic**. Astfel, **protocoalele definite la nivelul
DataLink** se ocupă printre altele de interactiunea 

În exemplul de mai sus, un astfel de bloc logic este reprezentat de biți care
alcătuiesc un byte. Receptorul trebuie să știe să delimiteze între aceste
blocuri pentru a extrage datele corect. Cum **nivelul fizic nu este ideal**, pot
apărea probleme precum desincronizări, astfel că soluția naivă în care spunem că
fiecare 8 biți reprezintă un frame nu este valabilă.

```
010|01000001|01000010|10101
      'A'       'B'
```

Unitatea de informație pe care o vom folosi la nivelul DataLink este **cadrul
(frame)** și reprezintă fluxul de biți care constitue un bloc logic de date.

---
**Note**

Intrebarea la care vrem sa raspundem astazi este:
**Cum face expeditorul (sender) codificarea cadrelor (frames) astfel încât
receptorul (receiver) să le poată extrage eficient din fluxul de biți pe care îl
primește de la nivelul fizic?**

---