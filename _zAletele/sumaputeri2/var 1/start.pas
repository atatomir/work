program calculare_sume_de_puteri_ale_lui_2;

uses crt,sysutils;

var n,i:byte;
    s:int64;

begin
clrscr;
readln(n);
writeln(timetostr(time));

s := (1 shl n+1)-1;
writeln(s);
writeln(timetostr(time));
read(s);

end.
