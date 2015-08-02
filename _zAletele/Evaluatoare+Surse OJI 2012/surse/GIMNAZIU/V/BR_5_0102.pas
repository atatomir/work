program p2;
var mi,mi1,mi2,mi3,ma,ma1,ma2,ma3,m,a,n,b,c,d,m1,n1,nr1,nr2,nr3,nr4:longint;
    f,g:text;
begin
assign(f, 'chibrituri.in');
assign(g, 'chibrituri.out');
reset(f);
rewrite(g);
readln(f,n);
readln(f,m);
if a or b or c or d=0 then
        begin
        m1:=2;
       n1:=4;
        end;
if a or b or c or d=1 then
        begin
        m1:=0;
       n1:=2;
        end;
if a or b or c or d=2 then
        begin
        m1:=3;
       n1:=2
        end;
if a or b or c or d=3 then
        begin
        m1:=3;
       n1:=2;
        end;
if a or b or c or d=4 then
        begin
        m1:=1;
       n1:=3;
        end;
if a or b or c or d=5 then
        begin
        m1:=3;
       n1:=2;
        end;
if a or b or c or d=6 then
        begin
        m1:=3;
       n1:=3;
        end;
if a or b or c or d=7 then
        begin
        m1:=1;
       n1:=2;
        end;
if a or b or c or d=8then
        begin
        m1:=3;
       n1:=4;
        end;
if a or b or c or d=9then
        begin
        m:=3;
        n:=3;
        end;
ma:=a;
if ma<b then
   ma:=b;
if ma<c then
   ma:=c;
if ma<d then
   ma:=d;
ma1:=a;
if ma1<b then
   ma1:=b;
if ma1<c then
   ma1:=c;
if ma1<d then
   ma1:=d;
ma2:=a;
if ma2<b then
   ma2:=b;
if ma2<c then
   ma2:=c;
if ma2<d then
   ma2:=d;
ma3:=a;
if ma3<b then
   ma3:=b;
if ma3<c then
   ma3:=c;
if ma3<d then
   ma3:=d;
nr1:=ma*10+ma1;
nr2:=ma2*10+ma3;
writeln(g,' ');
write(g,nr1);
write(g, ':');
write(g,nr2);
mi:=a;
if mi>b then
   mi:=b;
if mi>c then
   mi:=c;
if mi>d then
   mi:=d;
mi1:=a;
if mi1>b then
   mi1:=b;
if mi1>c then
   mi1:=c;
if mi1>d then
   mi1:=d;
mi2:=a;
if mi2>b then
   mi2:=b;
if mi2>c then
   mi2:=c;
if mi2>d then
   mi2:=d;
mi3:=a;
if mi3>b then
   mi3:=b;
if mi3>c then
   mi3:=c;
if mi3>d then
   mi3:=d;
nr2:=mi*10+mi1;
nr3:=mi2*10+mi3;
write(g,nr3);
write(g, ':');
write(g,nr4);
close(f);
close(g);
end.