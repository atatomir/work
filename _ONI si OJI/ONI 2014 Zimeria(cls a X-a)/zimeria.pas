var op,n,i,j,x,nr:longint;
    v:array['a'..'z']of byte;
    bufin,bufout:array[1..65000]of byte;
    c:char;
    s:string;
    a:array[0..400005]of longint;
    ini:string;


procedure QSort(l,h:longint);
var i,j,x,y:longint;
begin
  i := l; j := h; x := a[(i+j)div 2];
  repeat
    while a[i] < x do inc(i);
    while a[j] > x do dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  assign(input,'zimeria.in'); reset(input);
  assign(output,'zimeria.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(op);
  readln(n);
  readln(ini);
  for i := 1 to 12 do v[ini[i]] := i;

  for i := 1 to n do
  begin
    readln(s);
    x := 0;
    for j := 1 to 5 do
    begin
      x := x * 13 + v[s[j]];
    end;
    a[i] := x;
  end;

  QSort(1,n);

  if op = 1 then
  begin
    nr := 1;
    for i := 2 to n do
      if a[i-1] <> a[i] then inc(nr);
    writeln(nr);
  end
  else
  begin
    for i := 1 to n do
    begin
      s := ''; x := a[i];
      for j := 5 downto 1 do
      begin
        s := ini[x mod 13] + s;
        x := x div 13;
      end;
      writeln(s);
    end;
  end;


  close(input);
  close(output);
end.