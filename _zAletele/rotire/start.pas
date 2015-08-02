program inversare;
var n:longint;
    f:text;
    i:byte;

procedure inv;
var uc:byte;
begin
uc := n mod 10;
n := (n div 10) +( 10000000  *  uc);
end;

begin

assign(f,'fout.bin');
rewrite(f);

readln(n);
for i := 1 to 8 do
begin
inv;
writeln(f,n);
end;

close(f);
end.
