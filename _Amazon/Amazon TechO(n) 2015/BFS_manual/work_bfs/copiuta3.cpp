LDA 0
JGE 33//! START DFS
LDA 50000//! Functie Adresa Tabela (11000 retur, 11001 x, 11002 y, 11003 rez)
STA [11003]
    LDA [11002] //! start 01
    SUBA 1
    STA [11002]
    JGE 12//! -> if 01
        LDA [11003]
        ADDA [11001]
        STA [11003]
        JGE [11000] //! retur
    LDA [11003] //! <- if 01
        ADDA [2]
        STA [11003]
    JGE 4//! ^ stop 01
LDA -1 //! Functie (0 <= x < C) && (0 <= y < R) (11000 retur, 11001 x, 11002 y, 11003 rez)
STA [11003]
LDA [11001]
JGE 22//! -> if 02
    LDA 0
    JGE [11000] //! retur x < 0
SUBA [2]//! <- if 02
    JGE [11000]//! return x >= C
        LDA [11002]
        JGE 28//! -> if 03
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
    JGE 47//! -> if 04
        LDA 0
        JGE 37//! for 01
LDA 6//! <- if 04 , am terminat initializarea , setez obstacolele
STA [71001]
LDA 7
STA [71002]
LDA [71001] //! incep ciclu obstacole
ADDA 2
STA [71001]
LDA [71002]
ADDA 2
STA [71002]
LDA [7]
SUBA 1
JGE 62//! -> if 05 ,mai sunt obiecte
    LDA 0
    JGE 74//! -> if 06, mai departe
LDN 71001 //! <- if 05, mai sunt obiecte
LDA [N]
STA [11001]
LDN 71002
LDA [N]
STA [11002]
LDA 71//! pozitie retur fct
STA [11000]
JGE 2//! CALL FUNCTIE Adresa Tabela
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
JGE 95//! -> if 07 , avem elemente
    LDA 0
    JGE 200//! am terminat !!!!!!!!!!!!!
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
STA [21001]
LDA [71002]
ADDA 1
STA [21002]
LDA 115//! adresa retur
STA [21000]
JGE 210//! CALL FUNCTIE CHECK2
LDA [21003]
JGE 119//! -> if 08 , este ok
    LDA 0
    JGE 130//! du-te la urmatorul caz
LDA [71001]//! <- if 08 , este ok
STA [11001]
LDA [71002]
ADDA 1
STA [11002]
LDA 127//! adresa retur
STA [11000]
JGE 2//! CALL FUNCTIA ADRESA
LDN 11003
LDA 1
STA [N]
LDA [71001]//! CASE 2 : UP (real down)
STA [21001]
LDA [71002]
SUBA 1
STA [21002]
LDA 138//! adresa retur
STA [21000]
JGE 210//! CALL FUNCTIE CHECK2
LDA [21003]
JGE 142//! -> if 09 , este ok
    LDA 0
    JGE 153//! du-te la urmatorul caz
LDA [71001]//! <- if 09 , este ok
STA [11001]
LDA [71002]
SUBA 1
STA [11002]
LDA 150//! adresa retur
STA [11000]
JGE 2//! CALL FUNCTIA ADRESA
LDN 11003
LDA 3
STA [N]
LDA [71001]//! CASE 3 : LEFT (real right)
SUBA 1
STA [21001]
LDA [71002]
STA [21002]
LDA 161//! adresa retur
STA [21000]
JGE 210//! CALL FUNCTIE CHECK2
LDA [21003]
JGE 165//! -> if 10 , este ok
    LDA 0
    JGE 176//! du-te la urmatorul caz
LDA [71001]//! <- if 10 , este ok
SUBA 1
STA [11001]
LDA [71002]
STA [11002]
LDA 173//! adresa retur
STA [11000]
JGE 2//! CALL FUNCTIA ADRESA
LDN 11003
LDA 2
STA [N]
LDA [71001]//! CASE 4 : RIGHT (real left)
ADDA 1
STA [21001]
LDA [71002]
STA [21002]
LDA 184//! adresa retur
STA [21000]
JGE 210//! CALL FUNCTIE CHECK2
LDA [21003]
JGE 188//! -> if 11 , este ok
    LDA 0
    JGE 199//! du-te la SFARSIT(JGE INCEPE CICLU)
LDA [71001]//! <- if 11 , este ok
ADDA 1
STA [11001]
LDA [71002]
STA [11002]
LDA 196//! adresa retur
STA [11000]
JGE 2//! CALL FUNCTIA ADRESA
LDN 11003
LDA 4
STA [N]
JGE 90//! INCEPUT CICLU ^^
LDA [3]//! END BFS, GET SOLUTION
STA [11001]
LDA [4]
STA [11002]
LDA 207//! ADRESA DE RETUR
STA [11000]
JGE 2//! CALL ADRESA TABELA
LDA 0 //!---
JGE 236//!!!!!!!!!!!!!!!!!!!!!!
HLT //!----
LDA -1//! Functia Check2 (21000 retur, 21001 x, 21002 y, 21003 rez)
STA [21003]
LDA [21001]
STA [11001]
LDA [21002]
STA [11002]
LDA 220//! ADRESA RETUR
STA [11000]
JGE 16 //! FUNCTIA CHECK
LDA [11003]
JGE 224//! if E CORECT
    LDA 0
    JGE [21000]
LDA [21001] //! if e corect
STA [11001]
LDA [21002]
STA [11002]
LDA 231//! ADRESA DE RETUR
STA [11000]
JGE 2 //! CALL FCT ADRESA
LDN 11003
LDA [N]
JGE [21000]//! E PROST ! OCUPAT
LDA 1
STA [21003]
JGE [21000]
LDN 11003
LDA [N]
STA [0]
HLT










