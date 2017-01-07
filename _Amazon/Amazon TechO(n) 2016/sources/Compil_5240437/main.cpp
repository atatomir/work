#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

string file_name = "05_intoTheDarkness.txt";
bool opened = false;

void pr(string to_print) {
    if (!opened)
        freopen(file_name.c_str(), "w", stdout);
    opened = true;

    cout << to_print << '\n';
    cerr << to_print << '\n';
}

struct vint {
    string name;

    vint(string _name) {
        name = _name;

        if (name == "input_rows" || name == "input_cols" || name == "input_objects_count") return;
        pr("variable " + name);
    }

    void push() {
        pr(name + " @ ");
    }

    void pop() {
        pr (name + "!");
    }

    void operator+=(int x) {
        push();
        pr(to_string(x) + " + " + name + " !");
    }

    void operator+=(vint x) {
        push();
        x.push();
        pr(" + " + name + " !");
    }

    void operator*=(int x) {
        push();
        pr(to_string(x) + " * " + name + " !");
    }

    void operator*=(vint x) {
        push();
        x.push();
        pr(" * " + name + " !");
    }

    void operator==(vint x) {
        push();
        x.push();
        pr("=");
    }

    void operator==(int x) {
        push();
        pr(to_string(x) + " = ");
    }

    void operator<=(vint x) {
        push();
        x.push();
        pr("<= ");
    }

    void operator>=(vint x) {
        push();
        x.push();
        pr(">= ");
    }

    void operator<(vint x) {
        push();
        x.push();
        pr("< ");
    }

    void operator<=(int x) {
        push();
        pr(to_string(x));
        pr(" <= ");
    }

    void operator<(int x) {
        push();
        pr(to_string(x));
        pr(" < ");
    }
};

struct varr {
    string name;
    int len;

    varr(string _name, int _len) {
        name = _name;
        len = _len;

        if (name == "input_objects") return;
        pr("variable " + name + " " + to_string(len) + " cells");
    }

    void push(int pos) {
        pr(name + " " + to_string(pos) + " + @ ");
    }

    void push(vint pos) {
        pr(name);
        pos.push();
        pr(" + @ ");
    }

    void pop(int pos) {
        pr (name + " " + to_string(pos) + " !");
    }

    void eq(int pos, int x) {
        pr(name + " " + to_string(pos) + " + @ " + to_string(x) + " =");
    }

    void eq(vint pos, int x) {
        pr(name + " ");
        pos.push();
        pr(" + @ " + to_string(x) + " =");
    }
};

void set(vint a, int b) {
    pr(to_string(b) + " " + a.name + " !");
}

void set(vint a, vint b) {
    b.push();
    pr(a.name + " !");
}

void set(vint a, varr b, int pos) {
    b.push(pos);
    pr(a.name + " !");
}

void set(varr a, int pos, int b) {
    pr(to_string(b) + " " + a.name + " " + to_string(pos) + " + !");
}

void set(varr a, int pos, vint b) {
    b.push();
    pr(a.name + " " + to_string(pos) + " + !");
}

void set(varr a, int ppos, varr b, int pos) {
    b.push(pos);
    pr(a.name + " " + to_string(ppos) + " + !");
}

void set(varr a, vint pos, int b) {
    pr(to_string(b) + " " + a.name);
    pos.push();
    pr("+ !");
}

void set(varr a, vint pos, vint b) {
    b.push();
    pr(a.name);
    pos.push();
    pr("+ !");
}

void set(vint a, varr b, vint pos) {
    pr(b.name);
    pos.push();
    pr("+ @ ");

    pr(a.name + " !");
}

void set(varr a, vint p1, varr b, vint p2) {
    pr(b.name);
    p2.push();
    pr("+ @ ");

    pr(a.name);
    p1.push();
    pr("+ !");
}

void IF() {
    pr("if");
}

void ELSE() {
    pr("else");
}

void THEN() {
    pr("then");
}

void WHILE() {
    pr("while");
}

void REPEAT() {
    pr("repeat");
}

// -----------------------------------------------------------------------

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};
int defId[4] = {2, 1, 4, 3};


vint n("input_rows"), m("input_cols"), cnt("input_objects_count");
varr objs("input_objects", 0);

vint xme("xme"), yme("yme");
vint xpa("xpa"), ypa("ypa");
vint xde("xde"), yde("yde");
vint xva("xva"), yva("yva");
varr room("room", 55 * 55), aux_room("aux_room", 55 * 55);

vint xne("xne"), yne("yne");

vint i("i"), j("j"), aux("aux"), aux2("aux2"), x("x"), y("y");
vint xx("xx"), yy("yy"), dir("dir"), dir2("dir2");

vint l("l"), r("r");
varr Qx("qx", 55 * 55), Qy("qy", 55 * 55);

varr ddx("ddx", 6), ddy("ddy", 6);
vint jobs("jobs"), step("step");

varr lxpa("lxpa", 1111), lypa("lypa", 1111);
varr lxde("lxde", 1111), lyde("lyde", 1111);
vint cntpa("cntpa"), cntde("cntde"), current_job("current_job");
varr lxaux("lxaux", 1111), lyaux("lyaux", 1111);


void compute_dd() {
    set(ddx, 1, -1);
    set(ddx, 2, +1);
    set(ddx, 3, 0);
    set(ddx, 4, 0);

    set(ddy, 1, 0);
    set(ddy, 2, 0);
    set(ddy, 3, -1);
    set(ddy, 4, +1);
}

void clear_room() {
    set(aux, 0);

    set(i, 0);
    i < n;
    WHILE();

        set(j, 0);
        j < m;
        WHILE();
            set(room, aux, 0);

            aux += 1;
            j += 1;
            j < m;
        REPEAT();

        i += 1;
        i < n;
    REPEAT();
}

void get_dir(vint xs, vint ys, vint xd, vint yd, vint sol) {
    // copy room in aux_room
    set(aux, 0);

    set(i, 0);
    i < n;
    WHILE();

        set(j, 0);
        j < m;
        WHILE();
            set(aux_room, aux, room, aux);

            aux += 1;
            j += 1;
            j < m;
        REPEAT();

        i += 1;
        i < n;
    REPEAT();


    set(l, 0);
    set(r, 0);
    set(Qx, 0, xd);
    set(Qy, 0, yd);

    set(aux, xd);
    aux *= m;
    aux += yd;

    // protectie zid
    aux_room.eq(aux, -1);
    IF();
        l += 1;
    THEN();


    set(room, aux, -1);

    l <= r;
    WHILE();
        set(x, Qx, l);
        set(y, Qy, l);
        l += 1;

        for (int step = 0; step < 4; step++) {
            set(xx, x);
            xx += defX[step];

            set(yy, y);
            yy += defY[step];

            set(aux, xx);
            aux *= m;
            aux += yy;

            aux_room.push(aux);
            IF();
                //! nimic
            ELSE();
                set(aux_room, aux, defId[step]);
                r += 1;
                set(Qx, r, xx);
                set(Qy, r, yy);
            THEN();
        }

        l <= r;
    REPEAT();

    set(aux, xs);
    aux *= m;
    aux += ys;

    set(sol, aux_room, aux);
}

void swap_pa(vector<int> perm) {
    int i;

    for (i = 0; i < perm.size(); i++) {
        set(lxaux, i, lxpa, i);
        set(lyaux, i, lypa, i);
    }

    for (i = 0; i < perm.size(); i++) {
        set(lxpa, perm[i], lxaux, i);
        set(lypa, perm[i], lyaux, i);
    }
}

void swap_de(vector<int> perm) {
    int i;

    for (i = 0; i < perm.size(); i++) {
        set(lxaux, i, lxde, i);
        set(lyaux, i, lyde, i);
    }

    for (i = 0; i < perm.size(); i++) {
        set(lxde, perm[i], lxaux, i);
        set(lyde, perm[i], lyaux, i);
    }
}

int main()
{
    clear_room();
    step += 1;
    set(jobs, 0);

    set(cntpa, 0);
    set(cntde, 0);

    set(i, 0);
    i < cnt;
    WHILE();

        // get x and y
        set(aux, i);
        aux *= 3;

        set(aux2, aux);
        aux2 += 1;
        set(y, objs, aux2);

        set(aux2, aux);
        aux2 += 2;
        set(x, objs, aux2);

        // obstacol
        objs.eq(aux, 1);
        IF();
            set(aux2, x);
            aux2 *= m;
            aux2 += y;
            set(room, aux2, -1);
        THEN();

        // pachet
        objs.eq(aux, 2);
        IF();
            set(lxpa, cntpa, x);
            set(lypa, cntpa, y);
            cntpa += 1;

            jobs += 1;

            // added now
            set(aux2, x);
            aux2 *= m;
            aux2 += y;
            set(room, aux2, -1);
            // -----------

        THEN();

        // destinatie
        objs.eq(aux, 3);
        IF();
            set(lxde, cntde, x);
            set(lyde, cntde, y);
            cntde += 1;
        THEN();

        // me
        objs.eq(aux, 4);
        IF();
            set(xme, x);
            set(yme, y);
        THEN();

        // vagabondul ...
        objs.eq(aux, 5);
        IF();
            set(xva, x);
            set(yva, y);

            set(aux2, x);
            aux2 *= m;
            aux2 += y;
            set(room, aux2, -1);
        THEN();


        i += 1;
        i < cnt;
    REPEAT();

    // --------------- BULANELI ---------------------//
    // pentru 2 pachete schimba ordinea pachetelor
    pr("jobs @ 2 =");
    IF();
        swap_pa({1, 0});
        //pr("lxpa @ lxpa 1 + @ swap lxpa 1 + ! lxpa !");
        //pr("lypa @ lypa 1 + @ swap lypa 1 + ! lypa !");
    THEN();

    pr("jobs @ 3 =");
    IF();
        swap_pa({1, 0, 2});
        swap_de({0, 1, 2});
    THEN();

    pr("jobs @ 4 =");
    IF();
        swap_pa({1, 2, 0, 3});
        swap_de({3, 2, 1, 0});
    THEN();


    //-------------- TESTS -----------------------
    /*pr("(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)");
    pr("jobs @ 4 =");
    IF();
        //set(jobs, 2); // nicu
    ELSE();
        pr("-1 quit");
    THEN();*/
    //--------------------------------------------



    set(xpa, lxpa, current_job);
    set(ypa, lypa, current_job);
    set(xde, lxde, current_job);
    set(yde, lyde, current_job);

    // check if you are done
    xpa == xde;
    IF();
        ypa == yde;
        IF();
            current_job += 1;

            current_job >= jobs;
            IF();
                pr("-1 quit");
            THEN();
        THEN();
    THEN();

    set(xpa, lxpa, current_job);
    set(ypa, lypa, current_job);
    set(xde, lxde, current_job);
    set(yde, lyde, current_job);

    // elibereaza pachetul
    // added now
    set(aux2, xpa);
    aux2 *= m;
    aux2 += ypa;
    set(room, aux2, 0);
    // -----------


    get_dir(xpa, ypa, xde, yde, dir);
    compute_dd();

    set(xne, xpa);
    set(yne, ypa);

    xne.push();
    ddx.push(dir);
    pr("-");
    xne.pop();

    yne.push();
    ddy.push(dir);
    pr("-");
    yne.pop();

    // pachetul devine obstacol
    set(aux2, xpa);
    aux2 *= m;
    aux2 += ypa;
    set(room, aux2, -1);

    // drum robot-pozitie de impins
    get_dir(xme, yme, xne, yne, dir2);
    dir2.push();

    xne == xme;
    IF();
        yne == yme;
        IF();
            dir.push();
        THEN();
    THEN();

    /*xme == 2;
    IF();
        yme == 2;
        IF();

            dir2 == 4;
            IF();
                pr("-1");
            ELSE();
                //pr("0");
            THEN();

        THEN();
    THEN();*/

    /*yme == 2;
    IF();
        pr("-1");
    ELSE();
        //pr("0");
    THEN();*/

    //-------------- TESTS -----------------------
    /*step == 1;
    IF();
        pr("dup 4 =");
        IF();
            pr("11");
        THEN();
    THEN();*/
    //--------------------------------------------

    pr("dup 0 =");
    IF();
        current_job += 1;
        //pr("-1 quit");
    THEN();



    return 0;
}
