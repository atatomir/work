type element=record
       x,y,e:smallint;
     end;
var n,i,j,ci,cj:longint;
    a:array[0..101,0..101]of smallint;
    max,maxi,maxj:longint;
    c:array[0..10005]of element;

procedure add(x,y,e:longint);
begin
  inc(cj);
  c[cj].x := x; c[cj].y := y; c[cj].e := e;

  //writeln(x,' ',y,' ',e);
end;

procedure Start_Lee(i,j:smallint);
var x,y,e:longint;
begin
  ci := 1; cj := 0;
  add(i,j,0);
  while ci <= cj do
  begin
    x := c[ci].x; y := c[ci].y; e := c[ci].e; inc(ci);
    if a[x,y] + 1 = a[x-1,y] then
    begin
      add(x-1,y,e+1);
    end;
    if a[x,y] + 1 = a[x+1,y] then
    begin
      add(x+1,y,e+1);
    end;
    if a[x,y] + 1 = a[x,y-1] then
    begin
      add(x,y-1,e+1);
    end;
    if a[x,y] + 1 = a[x,y+1] then
    begin
      add(x,y+1,e+1);
    end;

    if e > max then
    begin
      max := e;
      maxi := i;
      maxj := j;
    end;
  end;
end;

begin
  assign(input,'pietre2.in'); reset(input);
  assign(output,'pietre2.out'); rewrite(output);

  readln(n);
  for i := 1 to n do
  begin
    for j :=1 to n do
    begin
      read(a[i,j]);
    end;
    readln();
  end;

  for i := 0 to n+1 do a[0,i] := -5;
  for i := 0 to n+1 do a[n+1,i] := -5;
  for i := 1 to n do a[i,0] := -5;
  for i := 1 to n do a[i,n+1] := -5;

  max := -1; maxi := -1; maxj := -1;

  for i := 1 to n do Start_Lee(1,i);
  for i := 1 to n do Start_Lee(n,i);
  for i := 2 to n-1 do Start_Lee(i,1);
  for i := 2 to n-1 do Start_Lee(i,n);

  writeln(max);
  if max > 0 then
    writeln(maxi,' ',maxj)
  else
    writeln('0 0');

  close(input);
  close(output);
end.
