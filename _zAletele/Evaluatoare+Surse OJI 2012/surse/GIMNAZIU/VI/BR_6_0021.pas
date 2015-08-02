program br_6_0021;
var f,g:text;
    n,max,aux,i,nrpalindrom,maxswitch,nrcumax:integer;
    nr:array[1..10000] of longint;
    x,xnou,xsave,y,nrcuburi,aux1,aux2:longint;
    pal:array[1..10000] of longint;
    begin
assign(f,'cladiri.in');
assign(g,'cladiri.out');
reset(f);
rewrite(g);
readln(f,n);
for i:=1 to n do
read(f,nr[i]);
max:=0;
for i:=1 to n do       //a), partea cu max.
        begin
        x:=nr[i];
        while x>0 do
                begin
                aux:=x mod 10;
                x:=x div 10;
                if max<aux then
                        max:=aux;
                end;
        end;
//b)
xnou:=0;
nrpalindrom:=0;
for i:=1 to n do
        begin
        x:=nr[i];
        xsave:=x;
        while x<>0 do
                begin
                aux:=x mod 10;
                x:=x div 10;
                xnou:=xnou*10+aux;
                end;
        pal[i]:=xnou;
        if xsave=xnou then
                nrpalindrom:=nrpalindrom+1;
        xnou:=0;
        end;
nrcuburi:=0;
for i:=1 to n do
begin
x:=nr[i];
xsave:=x;
maxswitch:=0;
while x<>0 do
                begin
                aux:=x mod 10;
                x:=x div 10;
                if aux=max then
                        if maxswitch=0 then
                                begin
                                maxswitch:=1;
                                nrcumax:=nrcumax+1;
                                end;
                end;
end;
for i:=1 to n do
begin
x:=nr[i];
y:=pal[i];
if x<>y then
        begin
        repeat
                begin
                aux1:=x mod 10;
                aux2:=y mod 10;
                if aux1>aux2 then
                        repeat
                        begin
                                nrcuburi:=nrcuburi+1;
                                aux2:=aux2+1;
                        end;
        until aux1=aux2
    else
                        if aux1<aux2 then
                         repeat
                                begin
                                nrcuburi:=nrcuburi+1;
                                aux1:=aux1+1;
                        end;
                        until aux1=aux2;
                x:=x div 10;
                y:=y div 10;
                end;
    until x=y;
                end;
end;
writeln(g,max,' ',nrcumax);
writeln(g,nrpalindrom);
writeln(g,nrcuburi div 2);
close(f);
close(g);
end.
