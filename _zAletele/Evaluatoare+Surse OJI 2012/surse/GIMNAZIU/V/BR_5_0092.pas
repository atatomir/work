program chibrituri;
var f,g:text;
    n,m,nrv,nrh,s,d,k,l:longint
begin
assign(f,'chibrituri.in');
assign(g,'chibrituri.out');
reset(f);
rewrite(g);
read(f,n);
read(f,m);
nrv:=n div 2+m;
writeln(g,nrv);
s:=n+m;
d:=n-m;
nrh:=s+d;
if nrh<100 then
        begin
        write(g,'00:');
        write(g,nrh);
        end;
k:=nrh;
r:=k mod 10;
k:=k div 10;
l:=nrh mod 10;
nrh:=nrh div 10;
write(g,l*10); write(g,':');  write(g,0); write(g,r);
close(f);
close(g);
end.


