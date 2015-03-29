var a,r:array[1..16000]of longint;
    i,n:longint;

procedure Imparte(l,h:longint);
var i,k1,k2,k:longint;
begin
  k := h-l+1;
  k1 := (k+1)div 2;
  k2 := k div 2;

  for i := 1 to k do r[i] := a[i+l-1];
  for i := 1 to k1 do a[l+i-1] := r[2*i-1];
  for i := 1 to k2 do a[l+k1+i-1] := r[2*i];

  if k1 > 2 then Imparte(l,l+k1-1);
  if k2 > 2 then Imparte(l+k1,h);
end;

begin
  assign(input,'permavg.in'); reset(input);
  assign(output,'permavg.out'); rewrite(output);

  readln(n);

  for i := 1 to n do a[i] := i;

  Imparte(1,n);

  for i := 1 to n do write(a[i],' ');

  close(input);
  close(output);
end.