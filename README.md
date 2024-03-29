# langautom


## Table des symboles 
int a,b; -> rajouter a,b dans la table de symboles
a=3;     -> declarer 3 comme var temporaire dans table symbole , (mettre à la fin) AFC @255 3, COP @a @255 -> liberer l'espace var temp
b=a+5; -> expr: expr tplus expr
|-> affectation> var tegal expr
AFC @tmp 5
ADD @tmp(res) @a @tmp
COP @b @tmp
liberer l'espace var temp



D'aores vous combien au max vous avec besoin de var temporaires et pourquoi?

asm orienté mémoire
Si st tableau:
_________
| 0   | a | -> var déclaré
| 1   | b | -> 
|     |   |
| 255 | 3 | -> var temp

avantage inconvénement implementation de la st avec tableau
- taille fixe
- acces en O(1)

liste chainée
- taille dynamique
- acces en O(n)


insert -> should return index of the element
AFC @temp 5
$$ = @temp

search -> return index of the element

tId, $$ = recherche($1)

declarer en haut
%type<nb> 

## INterpreteur
```python
    lines = open("asm.txt", "r").readlines()
    asm = [l.split(" ") for l in lines]
    asm = [[l[0]] + [int(x) for x in l[1:]] for l in asm]
    mem = [0] * 256

    ip = 0
    while ip < len(asm):
        if asm[ip][0] == "AFC":
            mem[asm[ip][1]] = asm[ip][2]
            ip += 1
        elif ...
    


```
