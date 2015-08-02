var p,po:string;
    n,i:integer;


begin

writeln('Introdu fraza');
readln(p);

po:= '';
n := length(p);

for i := 1 to n do
begin
 if pos(p[i],'aeiouAEIOU') > 0 then
     po := po + p[i] + 'p' + p[i]

else
po:= po + p[i];




end;
writeln(po);







read(p);
end.
