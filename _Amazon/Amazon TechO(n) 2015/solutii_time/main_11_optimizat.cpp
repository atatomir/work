#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back

#define maxLabel 1000000

#define TABLE_BEGIN 50000

int labels[maxLabel];
int cpu, last_label_auto, last_label_auto2;

void LABEL(int id) {
    labels[id] = cpu;
}

void LDA(int x) {
    printf("LDA %d\n", x);
    cpu++;
}

void LDA_REF(int x) {
    printf("LDA [%d]\n", x);
    cpu++;
}

void LDA_REF_N() {
    printf("LDA [N]\n");
    cpu++;
}

void LDN(int a) {
    printf("LDN %d\n", a);
    cpu++;
}

void LDN_REF(int a) {
    printf("LDN [%d]\n", a);
    cpu++;
}

void STA(int a) {
    printf("STA [%d]\n", a);
    cpu++;
}

void STA_REF_N() {
    printf("STA [N]\n");
    cpu++;
}

void ADDA(int a) {
    printf("ADDA %d\n", a);
    cpu++;
}

void ADDA_REF(int a) {
    printf("ADDA [%d]\n", a);
    cpu++;
}

void SUBA(int a) {
    printf("SUBA %d\n", a);
    cpu++;
}

void SUBA_REF(int a) {
    printf("SUBA [%d]\n", a);
    cpu++;
}

void JGE(int a) {
    printf("JGE %d\n", a);
    cpu++;
}

void JGE_REF(int a) {
    printf("JGE [%d]\n", a);
    cpu++;
}

void HLT() {
    printf("HLT\n");
    cpu++;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void GIVE_ANSWER(int x) {
    LDA(x);
    STA(0);
    HLT();
}

void JUMP_TO(int x) {
    LDA(0);
    JGE(labels[x]);
}

void MOVE(int a, int b) {
    LDA_REF(a);
    STA(b);
}

void START_FOR() {
    LABEL(++last_label_auto);
}

void END_FOR() {
    JUMP_TO(last_label_auto);
}

void START_FOR_2() {
    LABEL(++last_label_auto2);
}

void END_FOR_2() {
    JUMP_TO(last_label_auto2);
}

void IF_JUMP_TO(int x) {
    JGE(labels[x]);
}

void ADD_REF_VAL(int _ref, int val) {
    LDA_REF(_ref);
    ADDA(val);
    STA(_ref);
}

void SUB_REF_VAL(int _ref, int val) {
    LDA_REF(_ref);
    SUBA(val);
    STA(_ref);
}

void ADD_REF_REF(int _ref, int val) {
    LDA_REF(_ref);
    ADDA_REF(val);
    STA(_ref);
}

void SUB_REF_REF(int _ref, int val) {
    LDA_REF(_ref);
    SUBA_REF(val);
    STA(_ref);
}

void GET_ID(int label_id, int label_id_2) {
    //! X - 30003, Y - 30004, REZ - 30002
    LDA(0);
    STA(30002);

    START_FOR_2();
        LDA_REF(30004);
        SUBA(1);
        STA(30004);
        IF_JUMP_TO(label_id);
            LDA_REF(30002);
            ADDA_REF(30003);
            STA(30002);
            JUMP_TO(label_id_2);
        LABEL(label_id);
            LDA_REF(30002);
            ADDA_REF(2);
            STA(30002);
    END_FOR_2();
    LABEL(label_id_2);
    ADD_REF_VAL(30002, TABLE_BEGIN);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void solve() {
    freopen("01_letsGetToKnowEachOther.tech", "w", stdout);
    cpu = 0;
    last_label_auto = 5000;
    last_label_auto2 = 10000;


    LDA_REF(69999);
    SUBA(1);
    IF_JUMP_TO(500);


    //! incrementam valorile
    ADD_REF_VAL(1, 2);
    ADD_REF_VAL(2, 2);
    ADD_REF_VAL(3, 1);
    ADD_REF_VAL(4, 1);
    ADD_REF_VAL(5, 1);
    ADD_REF_VAL(6, 1);


    //! INITIALIZAM CU -1
    MOVE(1, 30004);
    MOVE(2, 30003);
    GET_ID(1, 2);

    START_FOR();
        LDN_REF(30002);
        LDA(-1);
        STA_REF_N();
        LDA_REF(30002);
        SUBA(1);
        STA(30002);

        SUBA(TABLE_BEGIN);
        IF_JUMP_TO(3);
            JUMP_TO(4);
        LABEL(3);
    END_FOR();
    LABEL(4);

    //! BORDAM MATRICEA


    LDA(TABLE_BEGIN);
    STA(30006);  //POINTER COLOANA

    LDA_REF(2);
    STA(30005); //CONTOR

    START_FOR();
        LDN_REF(30006);
        LDA(10);
        STA_REF_N();

        ADD_REF_VAL(30006, 1);

        LDA_REF(30005);
        SUBA(1);
        STA(30005);

        IF_JUMP_TO(24);
            JUMP_TO(25);
        LABEL(24);
    END_FOR();

    LABEL(25);

    LDA(TABLE_BEGIN);
    ADDA_REF(2);
    STA(30006);

    LDA(TABLE_BEGIN);
    ADDA_REF(2);
    ADDA_REF(2);
    SUBA(1);
    STA(30007);

    LDA_REF(1);
    SUBA(2);
    STA(30005);

    START_FOR();
        LDN_REF(30006);
        LDA(10);
        STA_REF_N();

        LDN_REF(30007);
        LDA(10);
        STA_REF_N();

        ADD_REF_REF(30006, 2);
        ADD_REF_REF(30007, 2);

        LDA_REF(30005);
        SUBA(1);
        STA(30005);

        IF_JUMP_TO(6);
            JUMP_TO(7);
        LABEL(6);
    END_FOR();

    LABEL(7);

    LDA_REF(2);
    STA(30005); //CONTOR

    START_FOR();
        LDN_REF(30006);
        LDA(10);
        STA_REF_N();

        ADD_REF_VAL(30006, 1);

        LDA_REF(30005);
        SUBA(1);
        STA(30005);

        IF_JUMP_TO(8);
            JUMP_TO(9);
        LABEL(8);
    END_FOR();
    LABEL(9);



    //! PUNEM OBSTACOLELE

    LDA_REF(7);
    STA(30008);

    LDA(7);
    STA(30009);

    START_FOR();
        LDA_REF(30008);
        SUBA(1);
        IF_JUMP_TO(10);
            JUMP_TO(11);
        LABEL(10);
            STA(30008);

            ADD_REF_VAL(30009, 1);
            LDN_REF(30009);
            LDA_REF_N();
            ADDA(1);
            STA(30003);

            ADD_REF_VAL(30009, 1);
            LDN_REF(30009);
            LDA_REF_N();
            ADDA(1);
            STA(30004);

            GET_ID(12, 13);

            LDN_REF(30002);
            LDA(10);
            STA_REF_N();
    END_FOR();
    LABEL(11);

    //! ADAUGAM TAMPITII

    LDA_REF(7);
    STA(41000);
    ADDA_REF(41000);
    ADDA(8);
    STA(41000);

    LDN_REF(41000);
    LDA_REF_N();
    STA(30008);
    MOVE(41000, 30009);


    START_FOR();
        LDA_REF(30008);
        SUBA(1);
        IF_JUMP_TO(80);
            JUMP_TO(81);
        LABEL(80);
            STA(30008);

            ADD_REF_VAL(30009, 1);
            LDN_REF(30009);
            LDA_REF_N();
            ADDA(1);
            STA(30003);

            ADD_REF_VAL(30009, 1);
            LDN_REF(30009);
            LDA_REF_N();
            ADDA(1);
            STA(30004);

            GET_ID(82, 83);

            //! INCEPEM AVENTURA... PARK

            LDN_REF(30002); //! MIDDLE
            LDA(10);
            STA_REF_N();

            //! 0
            SUB_REF_REF(30002, 2);
            SUB_REF_REF(30002, 2);
            SUB_REF_REF(30002, 2);
            SUB_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 1
            ADD_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 2
            ADD_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 3
            ADD_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 4
            ADD_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 5
            ADD_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 6
            ADD_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 7
            ADD_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 8
            ADD_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 9
            ADD_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 10
            ADD_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 11
            ADD_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 12
            ADD_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 13
            SUB_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 14
            SUB_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 15
            SUB_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 16
            SUB_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 17
            SUB_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 18
            SUB_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 19
            SUB_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 20
            SUB_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 21
            SUB_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 22
            SUB_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 23
            SUB_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 24
            SUB_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 25
            SUB_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 26
            SUB_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 27
            SUB_REF_REF(30002, 2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 28
            ADD_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            //! 29
            ADD_REF_VAL(30002, 1);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();


            //! AM TERMINAT AVENTURA

    END_FOR();
    LABEL(81);

    //! ADRESA PENTRU SURSA

    MOVE(3, 30003);
    MOVE(4, 30004);

    GET_ID(70, 71);
    MOVE(30002, 30014); // AM PUS SURSA

    //! PUNEM DRONELE

    LDA_REF(7);
    STA(41000);
    ADDA_REF(41000);
    ADDA(8);
    STA(41000);

    LDN_REF(41000);
    LDA_REF_N();
    STA(42000);
    ADDA_REF(42000);
    ADDA_REF(41000);
    ADDA(1);
    STA(30009);

    LDN_REF(30009);
    LDA_REF_N();
    STA(30008);


    START_FOR();
        LDA_REF(30008);
        SUBA(1);
        IF_JUMP_TO(60);
            JUMP_TO(61);
        LABEL(60);
            STA(30008);


            ADD_REF_VAL(30009, 1);
            LDN_REF(30009);
            LDA_REF_N();
            ADDA(1);
            STA(30003);

            ADD_REF_VAL(30009, 1);
            LDN_REF(30009);
            LDA_REF_N();
            ADDA(1);
            STA(30004);

            GET_ID(62, 63);

            LDA_REF(30002); //! VERIFICA DACA E DRONA MEA
            SUBA_REF(30014);
            IF_JUMP_TO(65);
                JUMP_TO(67);
            LABEL(65);
                SUBA(1);
                IF_JUMP_TO(67);
                    JUMP_TO(68); //! E DRONA MEA

            LABEL(67); //! CONTINUA TREABA

            LDN_REF(30002); //! DRONA
            LDA(10);
            STA_REF_N();

            ADD_REF_VAL(30002, 1); //! RIGHT
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            SUB_REF_VAL(30002, 2); //! LEFT
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            ADD_REF_VAL(30002, 1); //! UP
            SUB_REF_REF(30002,2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            ADD_REF_REF(30002,2); //! DOWN
            ADD_REF_REF(30002,2);
            LDN_REF(30002);
            LDA(10);
            STA_REF_N();

            LABEL(68); //! FINAL FOR
    END_FOR();
    LABEL(61);



    //! INITIALIZAM COADA
    LDA(60000);
    STA(30011);

    LDA(59999);
    STA(30012);

    MOVE(5, 30003);
    MOVE(6, 30004);

    GET_ID(14, 15);
    MOVE(30002, 30013); // AM PUS TARGETUL

    MOVE(3, 30003);
    MOVE(4, 30004);

    GET_ID(16, 17);
    MOVE(30002, 30014); // AM PUS SURSA

    //! ELIBEREZ CELULA DRONEI
    LDN_REF(30014);
    LDA(-1);
    STA_REF_N();


    ADD_REF_VAL(30012, 1);
    LDN_REF(30012);
    LDA_REF(30013);
    STA_REF_N();

    //! PARCURGEM COADA
    START_FOR();
        LDA_REF(30012);
        SUBA_REF(30011);

        IF_JUMP_TO(18);
            JUMP_TO(19);
        LABEL(18); // EXTINDE-TE...
            //! RIGHT----------------------------------------
            LDN_REF(30011);
            LDA_REF_N();
            ADDA(1);
            STA(30020);

            LDN_REF(30020);
            LDA_REF_N();

            IF_JUMP_TO(20);
                LDA(4);
                STA_REF_N();

                ADD_REF_VAL(30012, 1);
                LDN_REF(30012);
                LDA_REF(30020);
                STA_REF_N();
            LABEL(20);

            //! LEFT----------------------------------------
            LDN_REF(30011);
            LDA_REF_N();
            SUBA(1);
            STA(30020);

            LDN_REF(30020);
            LDA_REF_N();

            IF_JUMP_TO(21);
                LDA(2);
                STA_REF_N();

                ADD_REF_VAL(30012, 1);
                LDN_REF(30012);
                LDA_REF(30020);
                STA_REF_N();
            LABEL(21);

            //! DOWN----------------------------------------
            LDN_REF(30011);
            LDA_REF_N();
            ADDA_REF(2);
            STA(30020);

            LDN_REF(30020);
            LDA_REF_N();

            IF_JUMP_TO(22);
                LDA(1);
                STA_REF_N();

                ADD_REF_VAL(30012, 1);
                LDN_REF(30012);
                LDA_REF(30020);
                STA_REF_N();
            LABEL(22);

            //! UP----------------------------------------
            LDN_REF(30011);
            LDA_REF_N();
            SUBA_REF(2);
            STA(30020);

            LDN_REF(30020);
            LDA_REF_N();

            IF_JUMP_TO(23);
                LDA(3);
                STA_REF_N();

                ADD_REF_VAL(30012, 1);
                LDN_REF(30012);
                LDA_REF(30020);
                STA_REF_N();
            LABEL(23);

            //! POP
            ADD_REF_VAL(30011, 1);

            //! VERIFICA DACA AI AJUNS
            LDN_REF(30014);
            LDA_REF_N();

            IF_JUMP_TO(19);

    END_FOR();
    LABEL(19);

    LDN_REF(30014);
    LDA_REF_N();

    IF_JUMP_TO(77);
        LDA(0);
        STA(0);
        HLT();

    LABEL(77);
    //STA(0);
    //HLT();



    //! REFACERE DRUM
    LDN_REF(30014);
    LDA_REF_N();

    IF_JUMP_TO(77);
        LDA(0);
        STA(0);
        HLT();
    LABEL(77); //! INCEPE RECONSTITUIREA

    LDA(70000);
    STA(69999);

    MOVE(5, 30003);
    MOVE(6, 30004);

    GET_ID(120, 121);
    MOVE(30002, 30013); // AM PUS TARGETUL

   START_FOR();
        LDA_REF(30013);
        SUBA_REF(30014);

        IF_JUMP_TO(84);
            JUMP_TO(85); //! LA TREABA
        LABEL(84);
            SUBA(1);//
            IF_JUMP_TO(85);
                JUMP_TO(100);

        LABEL(85); //! LA TREABA

        //!------------------------------

        LDN_REF(30014);
        LDA_REF_N();

        LDN_REF(69999);
        STA_REF_N();

       // ADD_REF_VAL(69999, 1);

        LDN_REF(30014);
        LDA_REF_N();

        SUBA(4);
        IF_JUMP_TO(91);
            JUMP_TO(92); //! CATRE VERIFICA 3
        LABEL(91); //! MERGE IN 4 - STANGA
            SUB_REF_VAL(30014, 1);
            //ADD_REF_VAL(30014, 1);
            JUMP_TO(93);

        LABEL(92);
        LDN_REF(30014);
        LDA_REF_N();
        SUBA(3);
        IF_JUMP_TO(94);
            JUMP_TO(95); //! CATRE VERIFICA 2
        LABEL(94); //! MERGE IN 3 - JOS
            ADD_REF_REF(30014, 2);
            JUMP_TO(93);

        LABEL(95);
        LDN_REF(30014);
        LDA_REF_N();
        SUBA(2);
        IF_JUMP_TO(97);
            JUMP_TO(96); //! CATRE VERIFICA 1
        LABEL(97); //! MERGE IN 2 - DREAPTA
            ADD_REF_VAL(30014, 1);
            //SUB_REF_VAL(30014, 1);
            JUMP_TO(93);

        LABEL(96);

        SUB_REF_REF(30014, 2); //! MERGE IN 1 - SUS
        //ADD_REF_REF(30014, 2);

        LABEL(93); //! CICLEAZA

         ADD_REF_VAL(69999, 1);


    END_FOR();

    LABEL(100);

    LDA(70000);
    STA(69999);


    LABEL(500); //! AM AJUNS :D

    LDN_REF(69999);
    LDA_REF_N();
    STA(0);

    ADD_REF_VAL(69999, 1);
    LDA(0);
    //STA(69999);
    HLT();



}

int main()
{
    solve();
    solve();

    return 0;
}
