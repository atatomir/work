var f:text;
    i:longint;

begin

assign(f,'cod.in');
rewrite(f);

for i := 1 to 99999 do
begin
write(f,i);
write(f,' ');
end;



end.