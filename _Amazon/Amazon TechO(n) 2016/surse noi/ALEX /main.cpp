#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long

// ATENTIE nicu
/*#define obstacol -1
#define pachet -3
#define inamic -2*/


#define obstacol -1
#define pachet -1
#define inamic -1

//#define infinite_loop


string file_name = "06_pitchBlack.txt";
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

    void operator-=(int x) {
        push();
        pr(to_string(x) + " - " + name + " !");
    }

    void operator-=(vint x) {
        push();
        x.push();
        pr(" - " + name + " !");
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
        pr(" < ");
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
        pr (name + " " + to_string(pos) + " + !");
    }

    void pop(vint pos) {
        pr (name + " ");
        pos.push();
        pr ("+ !");
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

void vint_var_minus(vint a, varr b, vint pos) {
    pr(a.name + " @ " + b.name + " ");
    pos.push();
    pr("+ @ - ");
}

// -----------------------------------------------------------------------

int defX[4] = {-1, 1, 0, 0};
int defY[4] = {0, 0, -1, 1};
int defId[4] = {2, 1, 4, 3};
vector<int> prm = {0, 1, 2, 3};



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

vint smxx("smxx"), smyy("smyy"), smaux("smaux");
vint bestpair("bestpair"), bestdist("bestdist"), deltax("deltax"), deltay("deltay"),temp("temp");

vint xpa2("xpa2"), ypa2("ypa2"), auxv("auxv");
vint helper("helper"), cntblack("cntblack");
vint nhelp("nhelp"), mhelp("mhelp");

varr llxpa("llxpa", 1111), llypa("llypa", 1111);
varr llxde("llxde", 1111), llyde("llyde", 1111);
varr valid("valid", 55 * 55);
vint useless("useless");

varr dist("dist", 55 * 55);
vint actdist("actdist"), newdist("newdist");
vint idist("idist"), jdist("jdist"), xdist("xdist"), ydist("ydist");
varr shuffleid("shuffleid", 1111);

vint additcnt("additcnt");
varr additfr("additfr", 1111), additse("additse", 1111);

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

void check_unavailable_room() {
    set(nhelp, n); nhelp += -1;
    set(mhelp, m); mhelp += -1;


    set(i, 1);
    i < nhelp;
    WHILE();

        set(j, 1);
        j < mhelp;
        WHILE();

            set(aux, i);
            aux *= m;
            aux += j;

            set(cntblack, 0);

            aux += 1;
            room.eq(aux, -1);
            IF();
                cntblack += 1;
            THEN();

            aux += -2;
            room.eq(aux, -1);
            IF();
                cntblack += 1;
            THEN();

            aux += m;
            aux += 1;
            room.eq(aux, -1);
            IF();
                cntblack += 1;
            THEN();

            aux -= m;
            aux -= m;
            room.eq(aux, -1);
            IF();
                cntblack += 1;
            THEN();

            aux += m;

            pr("cntblack @ 3 >=");
            IF();
                set(room, aux, -1);
            THEN();


            j += 1;
            j < mhelp;
        REPEAT();

        i += 1;
        i < nhelp;
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


    set(aux_room, aux, 1); // nicu - am pus 1, inainte era -1

    l <= r;
    WHILE();
        set(x, Qx, l);
        set(y, Qy, l);
        l += 1;

        for (auto step : prm) {
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

void get_dir_dist(vint xd, vint yd, vint i = idist, vint j = jdist, vint x = xdist, vint y = ydist) {
    // copy room in aux_room
    set(aux, 0);

    set(i, 0);
    i < n;
    WHILE();

        set(j, 0);
        j < m;
        WHILE();
            set(aux_room, aux, room, aux);
            set(dist, aux, 100000);

            aux += 1;
            j += 1;
            j < m;
        REPEAT();

        i += 1;
        i < n;
    REPEAT();



    set(i, 0);
    i < jobs;
    WHILE();
        set(aux, lxpa, i);
        set(aux2, lypa, i);
        aux *= m;
        aux += aux2;
        set(aux_room, aux, 0);

        set(aux, lxde, i);
        set(aux2, lyde, i);
        aux *= m;
        aux += aux2;
        set(aux_room, aux, 0);

        i += 1;
        i < jobs;
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

    set(dist, aux, 1);
    set(aux_room, aux, 1); // nicu - am pus 1, inainte era -1

    l <= r;
    WHILE();
        set(x, Qx, l);
        set(y, Qy, l);
        l += 1;

        set(aux, x);
        aux *= m;
        aux += y;
        set(actdist, dist, aux);
        set(newdist, actdist);
        newdist += 1;

        for (auto step : prm) {
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

                set(dist, aux, newdist);
                set(aux_room, aux, defId[step]);
                r += 1;
                set(Qx, r, xx);
                set(Qy, r, yy);
            THEN();
        }

        l <= r;
    REPEAT();
}

void get_dir_smart(vint xs, vint ys, vint xd, vint yd, vint sol) {
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


    set(aux_room, aux, 1); // nicu - am pus 1, inainte era -1

    l <= r;
    WHILE();
        set(x, Qx, l);
        set(y, Qy, l);
        l += 1;


        for (auto step : prm) {
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

                set(smxx, xx);
                smxx += defX[step];

                set(smyy, yy);
                smyy += defY[step];

                set(smaux, smxx);
                smaux *= m;
                smaux += smyy;

                aux_room.eq(smaux, -1);
                IF();
                    //! nimic
                ELSE();


                    set(aux_room, aux, defId[step]);
                    r += 1;
                    set(Qx, r, xx);
                    set(Qy, r, yy);

                THEN();
            THEN();
        }

        l <= r;
    REPEAT();

    set(aux, xs);
    aux *= m;
    aux += ys;

    set(sol, aux_room, aux);
}

void get_dir_smart2(vint xs, vint ys, vint xd, vint yd, vint sol) {
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


    set(aux_room, aux, 1); // nicu - am pus 1, inainte era -1

    l <= r;
    WHILE();
        set(x, Qx, l);
        set(y, Qy, l);
        l += 1;


        for (auto step : prm) {
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

                set(smxx, xx);
                smxx += defX[step];

                set(smyy, yy);
                smyy += defY[step];

                set(smaux, smxx);
                smaux *= m;
                smaux += smyy;

                pr("valid smaux @ + @ 0 <=");
                IF();
                    //! nimic
                ELSE();

                    set(aux_room, aux, defId[step]);
                    r += 1;
                    set(Qx, r, xx);
                    set(Qy, r, yy);

                THEN();
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
        set(lxpa, i, lxaux, perm[i]);
        set(lypa, i, lyaux, perm[i]);
    }
}

void swap_de(vector<int> perm) {
    int i;

    for (i = 0; i < perm.size(); i++) {
        set(lxaux, i, lxde, i);
        set(lyaux, i, lyde, i);
    }

    for (i = 0; i < perm.size(); i++) {
        set(lxde, i, lxaux, perm[i]);
        set(lyde, i, lyaux, perm[i]);
    }
}

void smart_swap(varr v, varr aux, vector<int> perm) {
    int i;

    for (i = 0; i < perm.size(); i++)
        set(aux, i, v, i);
    for (i = 0; i < perm.size(); i++)
        set(v, i, aux, perm[i]);
}

void swap_varr_varr(varr a, vint p1, varr b, vint p2) {
    a.push(p1);
    b.push(p2);
    a.pop(p1);
    b.pop(p2);
}

void abss(vint x) {
    x < 0;
    IF();
        x *= -1;
    THEN();
}

void pairUp() {
    //set(i, current_job);//nicu

set(i, 0);

    i < jobs;
    WHILE();
        // compute first value
        //set(bestpair, i);//nicu
        set(bestpair, -1);
        set(bestdist, 20000);

        // compute other values
        set(j, i);

        j < jobs;
        WHILE();

            set(deltax, lxpa, i);
            //vint_var_minus(deltax, lxde, j);
            set(temp,lxde,j);
            deltax -= temp;
            abss(deltax);

            set(deltay, lypa, i);
            //vint_var_minus(deltay, lyde, j);
            set(temp,lyde,j);
            deltay -= temp;
            abss(deltay);

            set(aux, deltax);
            aux += deltay;

            aux < bestdist;
            IF();
                set(bestdist, aux);
                set(bestpair, j);
            THEN();

            j += 1;
            j < jobs;
        REPEAT();

        swap_varr_varr(lxde, i, lxde, bestpair);
        swap_varr_varr(lyde, i, lyde, bestpair);


        i += 1;


        i < jobs;
    REPEAT();


}

void pairUp_dist() {
    //set(i, current_job);//nicu

    set(i, 0);

    i < jobs;
    WHILE();
        set(bestpair, i);
        set(bestdist, 100000);

        set(x, lxpa, i);
        set(y, lypa, i);

        get_dir_dist(x, y);
        set(j, i);

        j < jobs;
        WHILE();

            set(aux, lxde, j);
            set(aux2, lyde, j);
            aux *= m;
            aux += aux2;
            set(actdist, dist, aux);

            actdist < bestdist;
            IF();
                set(bestdist, actdist);
                set(bestpair, j);
            THEN();

            j += 1;
            j < jobs;
        REPEAT();

        swap_varr_varr(lxde, i, lxde, bestpair);
        swap_varr_varr(lyde, i, lyde, bestpair);


        i += 1;
        i < jobs;
    REPEAT();


}

void copy_it(varr dest, varr sour, vint how_many) {
    set(i, 0);

    i < how_many;
    WHILE();

        set(dest, i, sour, i);

        i += 1;
        i < how_many;
    REPEAT();
}

void shuffle_boxes() {
    get_dir_dist(xme, yme);

    set(i, 0);

    i < jobs;
    WHILE();
        set(bestpair, i);
        set(bestdist, 100000);

        set(j, i);
        j < jobs;
        WHILE();

            set(aux, lxpa, j);
            set(aux2, lypa, j);
            aux *= m;
            aux += aux2;

            set(actdist, dist, aux);
            actdist < bestdist;
            IF();
                set(bestdist, actdist);
                set(bestpair, j);
            THEN();

            j += 1;
            j < jobs;
        REPEAT();

        swap_varr_varr(lxpa, i, lxpa, bestpair);
        swap_varr_varr(lypa, i, lypa, bestpair);
        set(shuffleid, i, bestpair);

        i += 1;
        i < jobs;
    REPEAT();
}

void get_shuffle_boxes() {
    set(i, 0);

    i < jobs;
    WHILE();

        set(aux, shuffleid, i);
        swap_varr_varr(lxpa, i, lxpa, aux);
        swap_varr_varr(lypa, i, lypa, aux);

        i += 1;
        i < jobs;
    REPEAT();
}

void get_additional() {
    set(i, 0);

    i < additcnt;
    WHILE();

        set(aux, additfr, i);
        set(aux2, additse, i);

        swap_varr_varr(lxpa, aux, lxpa, aux2);
        swap_varr_varr(lypa, aux, lypa, aux2);
        swap_varr_varr(lxde, aux, lxde, aux2);
        swap_varr_varr(lyde, aux, lyde, aux2);

        i += 1;
        i < additcnt;
    REPEAT();
}

void get_nearest() {

    get_dir_dist(xme, yme);

    set(i, current_job);
    set(bestpair, i);
    set(bestdist, 100000);

    i < jobs;
    WHILE();

        set(aux, lxpa, i);
        set(aux2, lypa, i);
        aux *= m;
        aux += aux2;
        set(actdist, dist, aux);

        actdist < bestdist;
        IF();
            set(bestdist, actdist);
            set(bestpair, i);
        THEN();

        i += 1;
        i < jobs;
    REPEAT();

    bestpair == current_job;
    IF();
        // nothing to do
    ELSE();

        swap_varr_varr(lxpa, current_job, lxpa, bestpair);
        swap_varr_varr(lypa, current_job, lypa, bestpair);
        swap_varr_varr(lxde, current_job, lxde, bestpair);
        swap_varr_varr(lyde, current_job, lyde, bestpair);

        additcnt += 1;
        set(additfr, additcnt, current_job);
        set(additse, additcnt, bestpair);

    THEN();
}


int main()
{
    srand(time(NULL));

pr("1");
WHILE();


    clear_room();
    step += 1;
    set(jobs, 0);

    set(cntpa, 0);
    set(cntde, 0);


    set(i, 0);
    i < cnt;
    WHILE();

        // obsetacol -1
        // pachet -3
        // inamic -2

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
            set(room, aux2, obstacol);
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
            set(room, aux2, pachet);
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


        // vagabondul ...//nicu : fara vagabond merge harta 7 !!!!
        objs.eq(aux, 5);
        IF();
            set(xva, x);
            set(yva, y);

            set(aux2, x);
            aux2 *= m;
            aux2 += y;
            set(room, aux2, inamic);

        THEN();


        i += 1;
        i < cnt;
    REPEAT();

    // --------------- BULANELI ---------------------//


    // pentru 2 pachete schimba ordinea pachetelor
    /*pr("jobs @ 2 =");
    IF();
        //swap_pa({1, 0});//original
        //pr("lxpa @ lxpa 1 + @ swap lxpa 1 + ! lxpa !");
        //pr("lypa @ lypa 1 + @ swap lypa 1 + ! lypa !");
        //swap_pa({1, 0});//aduce la primul job 2 pa
        //swap_de({0, 1});
        swap_pa({1, 0});//rows=9, aduce 2 pachete
        swap_de({0, 1});

       // swap_pa({1, 1, 1, 0});//rows=10, aduce 1 pachete
        //swap_de({0, 0, 0, 1});


        n == 11;
        IF();
            swap_pa({1, 0});
        THEN();


    THEN();

    pr("jobs @ 3 =");
    IF();
        //swap_pa({1, 0, 2});
        //swap_de({0, 1, 2});

        swap_pa({1, 0, 2});//original
        swap_de({0, 1, 2});

        //swap_pa({1, 0, 2});


    THEN();

    pr("jobs @ 4 =");
    IF();
        //swap_pa({1, 2, 0, 3});
        //swap_de({3, 2, 1, 0});


        //swap_pa({2, 0, 1, 3});//original
        //swap_de({3, 2, 1, 0});

        //swap_pa({1, 3, 2, 0});
        //swap_de({2, 3, 0, 1});

        //swap_pa({0, 2, 1, 3});primeletrei aduc inca 600000
        //swap_de({2, 0, 1, 3});

        swap_pa({2, 3, 1, 0});//1671824.20
        swap_de({0, 3, 1, 2});

        //swap_pa({0,3,1,2});//1669000.00
        //swap_de({2,1,0,3});

        //swap_pa({0,3,1,2});
        //swap_de({2,1,0,3});


    THEN();*/





    //-------------- TESTS -----------------------
    pr("(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)");

    step == 1;
    IF();
        shuffle_boxes();
        pairUp_dist();

        copy_it(llxde, lxde, jobs);
        copy_it(llyde, lyde, jobs);
    ELSE();
        get_shuffle_boxes();

       // get_additional();
       // get_nearest();

        copy_it(lxde, llxde, jobs);
        copy_it(lyde, llyde, jobs);
    THEN();





    /*pr("jobs @ 4 =");
    IF();

    ELSE();
        pr("-1 quit");
    THEN();*/



    //--------------------------------------------
            current_job >= jobs;//nicu
            IF();

                #ifdef infinite_loop
                    set(current_job, 0); // nicu : atentie rezolva harta 7
                #else
                    pr("-1 quit");
                #endif

            THEN();



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

                #ifdef infinite_loop
                    set(current_job, 0); // nicu : atentie rezolva harta 7
                #else
                    pr("-1 quit");
                #endif

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

    // --- nicu iupiu
    /*get_dir(xme, yme, xme, yme, useless); // doar pleaca din mine.. sa vedem unde pot ajunge

    set(aux, n);
    aux *= m;
    copy_it(valid, aux_room, aux);

    set(dir, 0);
    get_dir_smart2(xpa, ypa, xde, yde, dir);
    dir <= 0;
    IF();
        get_dir_smart(xpa, ypa, xde, yde, dir);
    THEN();*/

    // ----

    get_dir_smart(xpa, ypa, xde, yde, dir); // ADAUGA nicu
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
    set(room, aux2, pachet);

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


    /*pr("dup 0 =");
    IF();
        current_job += 1;
    THEN();*/

    pr("dup 0 =");
    IF();
        pr("drop");
        current_job += 1;
    ELSE();
        pr("quit");
    THEN();


    pr("1");
REPEAT();




    return 0;
}
