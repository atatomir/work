program br_6_0022;
var f,g:text;
    k,i,nrc:integer;
    n,aux,saux,satean,s:longint;
begin
//citim din fisier
assign(f,'galbeni.in');
assign(g,'galbeni.out');
reset(f);
rewrite(g);
read(f,s); //suma primului satean
read(f,k); //nr de cifre al lui s, 1>=s>=3
read(f,n); //pt al catelea satean verificam aia
saux:=s; //salvam s intr-o variabila.
nrc:=0;
//Descompunere in cifre
for i:=1 to k do
begin
while saux<>0 do
begin
        aux:=saux mod 10;
        if aux<>0 then
                begin
                s:=s*aux;
                nrc:=nrc+1;
                end;
                saux:=saux div 10;
        end;
s:=s*8;
s:=s div 9;
while nrc<k do
begin
        s:=s*10+9;
        nrc:=nrc+1;
end;
if k=1 then
        satean:=s mod 10
        else
        if k=2 then
                satean:=s mod 100
                else
                if k=3 then
                        satean:=s mod 1000;
s:=satean;
saux:=satean;
end;
writeln(g,saux);
close(f);
close(g);
end.


