var n,i,k:longint;
    a:array[0..3000005]of longint;
    bufin:array[1..65000]of byte;

procedure QSearch(l,h:longint);
var i,j,x,y,mid:longint;
begin
  i := l ; j := h; x := a[i+Random(j-i+1)];
  repeat
    while a[i] < x do inc(i);
    while a[j] > x do dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i > j;

  if (i - j = 2)and(j+1=k) then
    writeln(x)
  else
  begin
    if k <= j then
      QSearch(l,j)
    else
      QSearch(i,h);
  end;


end;

begin
  assign(input,'sdo.in'); reset(input);
  assign(output,'sdo.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,k);
  for i := 1 to n do read(a[i]);
  a[0] := -1; a[n+1] := 2 shl 31;

  Randomize;
  QSearch(1,n);

  close(input);
  close(output);
end.
