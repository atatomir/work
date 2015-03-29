const max=3000000;
var f:text;
    k:longint;
    a:array[2..max]of boolean;
    i,j:longint;
    n:int64;
    cont:longint;

begin
  assign(f,'prim.in'); reset(f);
  read(f,k);
  close(f);

  cont:=0;

  for i := 2 to max do a[i]:=true;

  //h:=round(sqrt(k*10));
  for i := 2 to max do
  begin
    if a[i]=true then
    begin
      inc(cont);
      if cont =k+1 then break;
      for j := 2 to (max div i) do
        a[j*i] := false;
    end;
  end;

  {i:= 1;
  inc(k);
  j:=0;
  while k<>j do
  begin
    inc(i);
    if a[i] = true then inc(j);
  end;}

  assign(f,'prim.out'); rewrite(f);
  n:= i*i;
  write(f,n);
  close(f);
end.
