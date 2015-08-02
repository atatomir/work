var f:text;
    a:longint;

begin

assign(f,'cod.in');
reset(f);

repeat

read(f,a);

 if a = 49765 then
 writeln('Ai aflat codul')
 else
 writeln('Codul este gresit');






until a = 49765;
readln(a);





close(f);
end.
