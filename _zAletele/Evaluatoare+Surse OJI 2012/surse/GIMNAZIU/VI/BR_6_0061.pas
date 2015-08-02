program p1;
var f,g:text;
    n,i,m,k,max,c,zz,nou:longint;
    x:array[1..100]of longint;
    apar:array[1..100]of longint;
    nrcifre:array[1..100]of longint;
begin
assign(f,'cladiri.in');
assign(g,'cladiri.out');
reset(f); rewrite(g);
readln(f,n);
max:=0;
for i:=1 to n do
    readln(f,x[i]);
for i:=1 to n do
    begin
    m:=x[i];
    //Extrag cifrele si aflu cifra maxima
    while m>0 do
          begin
          c:=m mod 10;
          m:=m div 10;
          nrcifre[i]:=nrcifre[i]+1;
          if c>max then
             max:=c;
          end;
    end;
write(g,max,' '); //Afisez inaltimea celui mai inalt turn
for i:=1 to n do
    begin
    m:=x[i];
    while m>0 do
      begin
       c:=m mod 10;
       m:=m div 10;
       if c=max then
          apar[i]:=1;
      end;
    end;
for i:=1 to n do
    if apar[i]=1 then
       k:=k+1;
writeln(g,k);
//Aflu cate numere sunt palindroame din x[i]
nou:=0;
for i:=1 to n do
    begin
    m:=x[i];
    while m>0 do
          begin
          c:=m mod 10;
          m:=m div 10;
          nou:=nou*10 + c;
          end;
    if x[i]=nou then
       zz:=zz+1;
    nou:=0;
    end;
writeln(g,zz); //Afisez numarul numerelor palindroame
close(f);
close(g);
end.

