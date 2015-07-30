type pozitie = record
       i,j:smallint;
     end;
var n,m,q,y,i,j,ti,t,max:longint;
    a:array[0..1005,0..1005]of longint;
    bufin:array[1..65000]of byte;
    x1,y1,x2,y2,c:longint;
    co:array[0..1000005]of pozitie;
    bg,en:longint;

procedure add(i,j:longint); inline;
begin
  a[i,j] := -1;
  inc(en);
  co[en].i := i;
  co[en].j := j;
end;

procedure start_it(i,j:longint);
begin
  bg := 1; en := 0;
  add(i,j);

  while bg <= en do
  begin
    i := co[bg].i; j := co[bg].j;
    inc(bg);
    if a[i-1,j] = 1 then add(i-1,j);
    if a[i+1,j] = 1 then add(i+1,j);
    if a[i,j-1] = 1 then add(i,j-1);
    if a[i,j+1] = 1 then add(i,j+1);
  end;

  if en > max then max := en;
end;

begin
  assign(input,'sahara.in'); reset(input);
  assign(output,'sahara.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m,q);

  for i := 0 to n+1 do
    for j := 0 to m+1 do
      a[i,j] := 0;

  readln(t);
  for ti := 1 to t do
  begin
    readln(x1,y1,x2,y2,c);
    for i := x1 to x2 do
      for j := y1 to y2 do
        a[i,j] := a[i,j] + c;
  end;

  for i := 1 to n do
    for j := 1 to m do
      if a[i,j] >= q then
        a[i,j] := 1
      else
        a[i,j] := 0;


  max := 0;
  for i := 1 to n do
    for j := 1 to m do
      if a[i,j] = 1 then
        start_it(i,j);

  writeln(max);


  close(input);
  close(output);
end.