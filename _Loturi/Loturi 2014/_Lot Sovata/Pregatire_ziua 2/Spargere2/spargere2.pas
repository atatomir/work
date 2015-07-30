var n,k,i:Longint;
    a:array[0..100005]of int64;
    bufin:array[1..65000]of byte;
    x:int64;

function max(a,b:int64):int64;
begin
  if a > b then max := a else max := b;
end;

begin
  assign(input,'spargere2.in'); reset(input);
  assign(output,'spargere2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,k);
  read(a[1]);
  for i := 2 to k do
  begin
    read(x);
    if x > a[i-1] then a[i] := x else a[i] := a[i-1];
  end;

  for i := k+1 to n do
  begin
    read(x);
    a[i] := max(a[i-1],x+a[i-k]);
  end;

  if a[n] <0 then a[n] := 0;
  writeln(a[n]);

  close(input);
  close(output);
end.
