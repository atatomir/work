var l,k,n,i:longint;
    r:array[0..1000005]of byte;

function get(x:longint):boolean;
begin
  if x <= 0 then get := true
  else
  begin
    if r[x] =1 then get := true else get := false;
  end;

  if x = 0 then get := false
end;

begin
  readln(l,k,n);
  for i := 1 to 1000000 do
  begin
    if get(i-1) and get(i-k) and get(i-l) then
      r[i] := 0
    else
      r[i] := 1;
  end;

  for i := 1 to n do
  begin
    read(l);
    if r[l] = 1 then write('A') else write('B');
  end;

end.
