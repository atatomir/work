var a:string;
    i:integer;

begin

read(a);

for i := 1 to length(a) do
begin

   if (ord(a[i]) >$40) and( ord(a[i]) < $60) then
   a[i] := chr(ord(a[i]) + $20)
   else
   a[i] := chr(ord(a[i]) - $20);
end;
write(a);
read(a);
end.








end;
