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

- `play ...` vytvoří hru, program se dotáže, jestli se jedná o hru proti počítači a jeho obtížnost,
nebo o hru s dalším hráčem
- `save [filename]` uloží rozehranou hru do souboru (`filename`)
- `load [filnename]` načte uloženou hru ze souboru (`filename`)
- `board` zobrazí stav herní desky
- `move [source_x][source_y] [target_x][target_y]` přesune figurku z pozice (`source_x`,`source_y`) na pozici (`target_x`,`target_y`)
- `help` zobrazí nápovědu
- `quit` ukončí program

Výstup aplikace může vypadat takto. Znak dolar značí vstup uživatele.
```
Zadejte příkaz, pro nápovědu příkaz help:
$ board
  A   B   C   D   E   F   G   H
+---+---+---+---+---+---+---+---+
|B R|B N|B B|B Q|B K|B B|B N|B R| 1
+---+---+---+---+---+---+---+---+
|B P|B P|B P|B P|B P|B P|B P|B P| 2
+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   | 3
+---+---+---  ______+---+---+---+---+---+
|   |   |   |   |   |   |   |   | 4
+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   | 5
+---+---+---+---+---+---+---+---+
|   |   |   |   |   |   |   |   | 6
+---+---+---+---+---+---+---+---+
|W P|W P|W P|W P|W P|W P|W P|W P| 7
+---+---+---+---+---+---+---+---+
|W R|W N|W B|W Q|W K|W B|W N|W R| 8
+---+---+---+---+---+---+---+---+
Zadejte příkaz, pro nápovědu příkaz help:
```

Celá aplikace bude řízena třídou `CApplication`, která se stará oběh hry a interaktuje s uživatelem. Tato třída bude obsahovat třídu `CGame`, která reprezentuje jednu konkretní hru, hlavním účelem třídy je ukládání hry. `CGame` drží herní desku `CBoard` a dva objekty třídy `CPlayer`, které budou představovat dva hráče. `CBoard` je třída, ve které jsou zasazeny objekty třídy `CPiece`.

### Kde mám polymorfismus?

Polymorfismus využívá třída `CPiece`, ta obsahuje abstraktní metodu `MoveSet`, která vrací množinu možných tahů. Jednotlivé šachové figurky `CKing`, `CQueen`, `CRook`, `CBishop`, `CKnight`, `CPawn` pak přetěžují tyto metody podle toho, jak se chovají.

Dále polymorfismu využívá třída `CPlayer`, která obsahuje abstraktní metodu `GetMove`. V případě, že se jedná o lokálního hráče, zeptá se uživatele na další tah. U počítače, který má nastavenou obtížnost na nejlehčí, tak vrátí náhodný tah. U středně těžkého a těžkého počítače bude metoda vracet tah, který budu založen na algoritmu Minimax, který má podle obtížnosti nastavenou hloubku hledaní.
