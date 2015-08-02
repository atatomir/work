program chibrituri;
var a,n,m:longint;
    f,g:text;
begin
assign(f,'chibrituri.in');
assign(g,'chibrituri.out');
reset(f);
rewrite(g);
read(f,n,m);
a:=m+n;




close(f);
close(g);
end.


