LDA 50000//! Functie Adresa Tabela (11000 retur, 11001 x, 11002 y, 11003 rez)
STA [11003]
    LDA [11002] //! start 01
    SUBA 1
    STA [11002]
    JGE //! -> if 01
        LDA [11003]
        ADDA [11001]
        STA [11003]
        JGE [11000] //! retur
    LDA [11003] //! <- if 01
        ADDA [2]
        STA [11003]
    JGE //! ^ stop 01
LDA -1 //! Functie (0 <= x < C) && (0 <= y < R) (11000 retur, 11001 x, 11002 y, 11003 rez)
STA [11003]
LDA [11001]
JGE //! -> if 02
    LDA 0
    JGE [11000] //! retur x < 0
SUBA [2]//! <- if 02
    JGE [11000]//! return x >= C
        LDA [11002]
        JGE //! -> if 03
            LDA 0
            JGE [11000] //! retur y < 0
        SUBA [1] //! <- if 03
            JGE [11000] //! retur y >= R
        LDA 1
        STA [11003]
        JGE [11000] //! retur ok
LDA 50000  //! Start program BFS
STA [71001] //! *INITIALIZARE TABELA -1
LDA 55000
STA [71002]
LDN [71001] //! for 01
    LDA -1
    STA [N]
    LDA [71001]
    ADDA 1
    STA [71001]
    SUBA [71002]
    JGE //! -> if 04
        LDA 0
        JGE //! for 01
LDA 6//! <- if 04 , am terminat initializarea , setez obstacolele
STA [71001]
LDA 7
STA [71002]
LDA [71001]
ADDA 2
STA [71001]
LDA [71002]
ADDA 2
STA [71002]
LDA [7]
SUBA 1
JGE //! -> if 05 ,mai sunt obiecte
    LDA 0
    JGE //! -> if 06, mai departe
LDN 71001
LDA [N]
STA [11001]
LDN 71002
LDA [N]
STA [11002]
LDA //! pozitie retur fct
STA [11000]
JGE //! CALL FUNCTIE Adresa Tabela
LDN 11003 //! aici ma intorc ^^
LDA 10
STA [N]
LDA 13000 //! <- if 06 , mai departe initializam coada
STA [12998]
LDA 12999
STA [12999]
LDA 12999 //! ADAUG UN ELEM IN COADA (X)
ADDA 1
STA [12999]
LDN 12999
LDA [5]
STA [N]
LDA 12999 //! ADAUG UN ELEM IN COADA (Y)
ADDA 1
STA [12999]
LDN 12999
LDA [6]
STA [N]
LDA [12999] //! inceput ciclu
SUBA [12998]
JGE //! -> if 07 , avem elemente
    LDA 0
    JGE //! am terminat !!!!!!!!!!!!!
LDN 12998 //! <- if 07, avem elemnte
LDA [N]
STA [71001]
LDA [12998]
ADDA 1
STA [12998]
LDN 12998
LDA [N]
STA [71002]
LDA [12998]
ADDA 1
STA [12998]
LDA [71001]//! CASE 1 : DOWN (up real)
STA [11001]
LDA [71002]
ADDA 1
STA [71002]
LDA //! adresa retur
STA [11000]
JGE //! CALL FUNCTIE CHECK
LDA [11003]
JGE //! -> if 08 , este ok
    LDA 0
    JGE //! du-te la urmatorul caz
LDA [71001]//! <- if 08 , este ok
STA [11001]
LDA [71002]
ADDA 1
STA [11002]
LDA //! adresa retur
STA [11000]
JGE //! CALL FUNCTIA ADRESA
LDN 11003
LDA 1
STA [N]
LDA [71001]//! CASE 2 : UP (real down)
STA [11001]
LDA [71002]
SUBA 1
STA [71002]
LDA //! adresa retur
STA [11000]
JGE //! CALL FUNCTIE CHECK
LDA [11003]
JGE //! -> if 09 , este ok
    LDA 0
    JGE //! du-te la urmatorul caz
LDA [71001]//! <- if 09 , este ok
STA [11001]
LDA [71002]
SUBA 1
STA [11002]
LDA //! adresa retur
STA [11000]
JGE //! CALL FUNCTIA ADRESA
LDN 11003
LDA 3
STA [N]
LDA [71001]//! CASE 3 : LEFT (real right)
SUBA 1
STA [11001]
LDA [71002]
STA [71002]
LDA //! adresa retur
STA [11000]
JGE //! CALL FUNCTIE CHECK
LDA [11003]
JGE //! -> if 10 , este ok
    LDA 0
    JGE //! du-te la urmatorul caz
LDA [71001]//! <- if 10 , este ok
SUBA 1
STA [11001]
LDA [71002]
STA [11002]
LDA //! adresa retur
STA [11000]
JGE //! CALL FUNCTIA ADRESA
LDN 11003
LDA 2
STA [N]
LDA [71001]//! CASE 4 : RIGHT (real left)
ADDA 1
STA [11001]
LDA [71002]
STA [71002]
LDA //! adresa retur
STA [11000]
JGE //! CALL FUNCTIE CHECK
LDA [11003]
JGE //! -> if 11 , este ok
    LDA 0
    JGE //! du-te la SFARSIT(JGE INCEPE CICLU)
LDA [71001]//! <- if 11 , este ok
ADDA 1
STA [11001]
LDA [71002]
STA [11002]
LDA //! adresa retur
STA [11000]
JGE //! CALL FUNCTIA ADRESA
LDN 11003
LDA 4
STA [N]
JGE //! INCEPUT CICLU ^^








