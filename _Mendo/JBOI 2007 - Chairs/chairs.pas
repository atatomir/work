var n,i,a,b,d,max:longint;
    v:array[1..2,0..2005]of longint;
    s:ansistring;

procedure parse(var a,b:longint);inline;
var r,i:longint;
begin
  a := 0; b := 0;
  readln(s);

  r := 0;
  for i := 1 to 2 do r := r*10 + ord(s[i])-$30;
  a := a + 3600*r;

  r := 0;
  for i := 4 to 5 do r := r*10 + ord(s[i])-$30;
  a := a + 60*r;

  r := 0;
  for i := 7 to 8 do r := r*10 + ord(s[i])-$30;
  a := a + r;

  r := 0;
  for i := 10 to 11 do r := r*10 + ord(s[i])-$30;
  b := b + 3600*r;

  r := 0;
  for i := 13 to 14 do r := r*10 + ord(s[i])-$30;
  b := b + 60*r;

  r := 0;
  for i := 16 to 17 do r := r*10 + ord(s[i])-$30;
  b := b + r;

end;

procedure QSort(l,h:longint);
var i,j,x,y,x2:longint;
begin
  i := l; j := h; x := v[2,(i+j)div 2]; x2 := v[1,(i+j)div 2];
  repeat
    while (v[2,i] < x)or((v[2,i] = x)and(v[1,i] < x2)) do inc(i);
    while (v[2,j] > x)or((v[2,j] = x)and(v[1,j] > x2)) do dec(j);
    if i <= j then
    begin
      y := v[1,i] ; v[1,i] := v[1,j] ; v[1,j] := y;
      y := v[2,i] ; v[2,i] := v[2,j] ; v[2,j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  {assign(input,'chairs.in'); reset(input);
  assign(output,'chairs.out'); rewrite(output); }

  readln(n);
  for i := 1 to n do
  begin
    parse(a,b);
    v[1,2*i-1] := 1; v[2,2*i-1] := a;
    v[1,2*i] := -1; v[2,2*i] := b+1;
  end;

  QSort(1,2*n);

  d := 0; max := 0;
  for i := 1 to 2*n do
  begin
    d := d + v[1,i];
    if d > max then max := d;
  end;

  writeln(max);

  {close(input);
  close(output); }
end.