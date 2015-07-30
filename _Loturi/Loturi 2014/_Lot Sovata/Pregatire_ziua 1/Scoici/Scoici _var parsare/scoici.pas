var n,m,i,j,x,min,val:longint;
    a:array[0..11,0..100005]of longint;
    v:array[0..100005]of ansistring;
    r:array[0..100005]of longint;
    bufin:array[1..65000]of byte;
    max,maxi,maxj,bg,en,si:longint;
    s:ansistring;

procedure QSort(l,h:longint);
var i,j,t:longint;
    x,y:ansistring;
begin
  i := l; j := h; x := v[(i+j)div 2];
  repeat
    while v[i] < x do inc(i);
    while v[j] > x do dec(j);
    if i <= j then
    begin
      y := v[i]; v[i] := v[j]; v[j] := y;
      t := r[i]; r[i] := r[j]; r[j] := t;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

procedure readd(var x:longint);
begin
  x := 0;
  while s[si] = ' ' do inc(si);
  while s[si] <> ' ' do
  begin
    x := x*10 + ord(s[si]) - $30;
    inc(si);
  end;
end;

begin
  assign(input,'scoici.in'); reset(input);
  assign(output,'scoici.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);

  for i := 1 to m do
    for j := 0 to n do
      a[i,j] := 0;

  readln(s); s := s + ' '; si := 1;
  for i := 1 to n do
  begin
    readd(x);
    inc(a[x,i]);
  end;

  for i := 1 to m do
    for j := 1 to n do
      a[i,j] := a[i,j-1] + a[i,j];

  for j := 1 to n do
  begin
    min := a[1,j];
    for i := 2 to m do
      if a[i,j] < min then min := a[i,j];

    for i := 1 to m do
      a[i,j] := a[i,j]-min;
  end;

  for j := 1 to n do
  begin
    v[j] := '';
    for i := 1 to m do
      v[j] := v[j] + char(a[i,j]+3);

    r[j] := j;
  end;

  QSort(1,n);

  r[0] := 0; v[0] := '';
  for i := 1 to m do v[0] := v[0] + char(3);

  bg := r[0]; en := r[0]; max := -1;
  for i := 1 to n do
  begin
    if v[i-1] = v[i] then
    begin
      if r[i] < bg then bg := r[i];
      if r[i] > en then en := r[i];
    end
    else
    begin
      val := en-bg;
      if val > max then
      begin
        max := val;
        maxi := bg+1; maxj := en;
      end;

      bg := r[i]; en := r[i];
    end;

  end;

  val := en-bg;
  if val > max then
  begin
    max := val;
    maxi := bg+1; maxj := en;
  end;

  writeln(maxi,' ',max);

  close(input);
  close(output);
end.
