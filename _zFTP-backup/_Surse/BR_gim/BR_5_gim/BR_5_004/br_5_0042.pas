Program piramide;
VAR n,x,k:Byte;
    f,g:TEXT;
BEGIN
   ASSIGN(f,'piramide.in'); RESET(f);
   ASSIGN(g,'piramide.out'); REWRITE(g);
   READLN(f,n,x,k);
   WHILE k<>0 DO BEGIN
                   IF k=1 THEN WRITELN(g,'1 ');
                   IF k=2 THEN WRITELN(g,'2 ');
                   IF k=3 THEN WRITELN(g,'3 ');
                   IF k=4 THEN WRITELN(g,'4 ');
                   IF k=5 THEN WRITELN(g,'5 ');
                   IF k=6 THEN WRITELN(g,'6 ');
                   IF k=7 THEN WRITELN(g,'7 ');
                   IF k=8 THEN WRITELN(g,'8 ');
                   IF k=9 THEN WRITELN(g,'9 ');
                   IF k=10 THEN WRITELN(g,'10');
                   IF k=11 THEN WRITELN(g,'11');
                   IF k=12 THEN WRITELN(g,'12');
                   IF k=13 THEN WRITELN(g,'13');
                   IF k=14 THEN WRITELN(g,'14');
                   IF k=15 THEN WRITELN(g,'15');
                   IF k=16 THEN WRITELN(g,'16');
                   IF k=17 THEN WRITELN(g,'17');
                   IF k=18 THEN WRITELN(g,'18');
                   IF k=19 THEN WRITELN(g,'19');
                   IF k=20 THEN WRITELN(g,'20');
                   IF k=21 THEN WRITELN(g,'21');
                   IF k=22 THEN WRITELN(g,'22');
                   IF k=23 THEN WRITELN(g,'23');
                   IF k=24 THEN WRITELN(g,'24');
                   IF k=25 THEN WRITELN(g,'25');
                   IF k=26 THEN WRITELN(g,'26');
                   IF k=27 THEN WRITELN(g,'27');
                   IF k=28 THEN WRITELN(g,'28');
                   IF k=29 THEN WRITELN(g,'29');
                   IF k=30 THEN WRITELN(g,'30');
                   IF k=31 THEN WRITELN(g,'31');
                   IF k=32 THEN WRITELN(g,'32');
                   IF k=33 THEN WRITELN(g,'33');
                   IF k=34 THEN WRITELN(g,'34');
                   IF k=35 THEN WRITELN(g,'35');
                   IF k=36 THEN WRITELN(g,'36');
                   IF k=37 THEN WRITELN(g,'37');
                   IF k=38 THEN WRITELN(g,'38');
                   IF k=39 THEN WRITELN(g,'39');
                   IF k=40 THEN WRITELN(g,'40');
                END;
   WRITELN(g,n,x,k);
   CLOSE(f);
   CLOSE(g);
END.

