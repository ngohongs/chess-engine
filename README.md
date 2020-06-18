# Hra Šachy (téma Šachy)
Autor: Hong Son Ngo


## Téma z Progtestu

Klasická hra Šachy (příp. libovolná varianta - asijské šachy, ...)

Implementujte následující varianty:

1. pro 2 hráče na jednom počítači
2. pro hru proti počítači
3. Hra musí splňovat následující funkcionality:

Hra musí splňovat následující funkcionality:

1. Dodržování všech pravidel dané varianty (u klasické varianty tedy i rošáda, braní mimochodem, proměna pěšce na dámu).
2. Ukládání (resp. načítání) rozehrané hry do (resp. ze) souboru (vytvořte vhodný formát a uživatelské rozhraní)
3. Oznamovat konec hry (šach, mat, pat) a její výsledek.
4. umělá inteligence (škálovatelná nebo alespoň 3 různé druhy, jeden druh můžou být náhodné tahy, ale nestačí implementovat pouze náhodné tahy)

Kde lze využít polymorfismus? (doporučené)

- Ovládání hráčů: lokální hráč, umělá inteligence (různé druhy), síťový hráč
- Pohyby figurek: král, dáma, věž, kůň,...
- Uživatelské rozhraní: konzolové, ncurses, SDL, OpenGL (různé druhy),...
- Pravidla různých variant: klasické šachy, žravé šachy, asijské šachy
- Jednotlivá pravidla: tahy, rošáda, braní mimochodem, proměna (jejich výběr pak může být konfigurovatelný)

## Zadání hry Šachy

Šachy budou mít konzolové uživatelské rozhraní. Po spuštění se hra bude ovládat těmito příkazy.

- `play [p|c][p|c][1|2|3|4|5]` vytvoří hru, první pozice je bílý hráč, druhý černý. `p` znamená hráč, `c` je počítač. Při hře proti počítači je nutno dopsat obtižnost od 1-5.                
- `save [filename]` uloží rozehranou hru do souboru (`filename`)
- `load [filnename]` načte uloženou hru ze souboru (`filename`)
- `board` zobrazí stav herní desky
- `move [source_x][source_y][target_x][target_y][q|r|b|n]` přesune figurku z pozice (`source_x`,`source_y`) na pozici (`target_x`,`target_y`), jestli se jedná o proměnu pěšce, musí být dodána figurka, v kterou se pěšec promění.
- `restart` resetuje hru
- `help` zobrazí nápovědu
- `quit` ukončí program

Výstup aplikace může vypadat takto. Znak dolar značí vstup uživatele. Černé figurky jsou označeny malými pismeny, bílé velkými.
```
Enter a command, for help enter the command 'help':
$ board
Side to turn: WHITE
    A B C D E F G H
  +-----------------+
8 | r n b q k b n r | 8
7 | p p p p p p p p | 7
6 | . . . . . . . . | 6
5 | . . . . . . . . | 5
4 | . . . . . . . . | 4
3 | . . . . . . . . | 3
2 | P P P P P P P P | 2
1 | R N B Q K B N R | 1
  +-----------------+
    A B C D E F G H
Enter a command, for help enter the command 'help':
```

Celá aplikace bude řízena třídou `CApplication`, která se stará oběh hry a interaktuje s uživatelem. Tato třída bude obsahovat třídu `CGame`, která reprezentuje jednu konkretní hru, hlavním účelem třídy je ukládání hry. `CGame` drží herní desku `CBoard` a dva objekty třídy `CPlayer`, které budou představovat dva hráče. `CBoard` je třída, ve které jsou zasazeny objekty třídy `CPiece`.

### Kde mám polymorfismus?

Polymorfismus využívá třída `CPiece`, ta obsahuje abstraktní metodu `MoveSet`, která vrací množinu možných tahů. Jednotlivé šachové figurky `CKing`, `CQueen`, `CRook`, `CBishop`, `CKnight`, `CPawn` pak přetěžují tyto metody podle toho, jak se chovají.

Dále polymorfismu využívá třída `CPlayer`, která obsahuje abstraktní metodu `GetMove`. V případě, že se jedná o lokálního hráče, zeptá se uživatele na další tah. U počítače, který má nastavenou obtížnost na nejlehčí, tak vrátí náhodný tah. U středně těžkého a těžkého počítače bude metoda vracet tah, který budu založen na algoritmu Minimax, který má podle obtížnosti nastavenou hloubku hledaní.
