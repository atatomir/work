var a,v,best:array[0..100001]of longint;
    n,i,poz,j,t:longint;

function cb(val:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := v[0];
  while i <= j do
  begin
    m := (i+j)div 2;
    if val <= v[m] then
      j := m-1
    else
      i := m+1;
  end;
  cb := i;
end;


begin
  assign(input,'scmax.in'); reset(input);
  assign(output,'scmax.out'); rewrite(output);

  readln(n);
  for i := 1 to n do read(a[i]);

  v[1] := a[1];
  v[0] := 1;
  best[1] := 1;

  for i := 2 to n do
  begin
    poz := cb(a[i]);
    v[poz] := a[i];
    best[i] := poz;
    if v[0] < poz then v[0] := poz;
  end;

  writeln(v[0]);

  j := v[0];  t := 0;
  while i >= 1 do
  begin
    if best[i] = j then
    begin
      dec(j);
      inc(t); v[t] := a[i];
    end;
    dec(i);
  end;

  for i := t downto 1 do write(v[i],' ');

  close(input);
  close(output);
end.
