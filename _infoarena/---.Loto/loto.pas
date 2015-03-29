type struct = record
       v,x1,x2,x3:longint;
     end;
var n,s,i,j,k,h,p:longint;
    a:array[0..105]of longint;
    v:array[0..1000005]of struct;
    bufin:array[1..65000]of byte;
    gasit:boolean;

procedure add(x:longint);inline;
begin
  inc(v[0].v);
  v[v[0].v].v:= x;
  v[v[0].v].x1:= a[i];
  v[v[0].v].x2:= a[j];
  v[v[0].v].x3:= a[k];
end;

procedure QSort(l,h:longint);
var i,j,x:longint;
    y:struct;
begin
  i := l ; j := h; x := v[(i+j)div 2].v;
  repeat
    while v[i].v < x do inc(i);
    while v[j].v > x do dec(j);
    if i <= j then
    begin
      y := v[i]; v[i] := v[j]; v[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

function cb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := v[0].v;
  repeat
    m := (i+j)div 2;
    if x <= v[m].v then
      j := m - 1
    else
      i := m + 1;
  until i > j;
  if v[i].v = x then cb := i else cb := -1;
end;

begin
  assign(input,'loto.in'); reset(input);
  assign(output,'loto.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,s);
  for i := 1 to n do read(a[i]);

  v[0].v := 0;
  for i := 1 to n do
    for j := i to n do
      for k := j to n do
        add(a[i]+a[j]+a[k]);

  QSort(1,v[0].v);

  gasit := false;
  for i := 1 to v[0].v do
  begin
    h := cb(s-v[i].v);
    if h <> -1 then
    begin
      v[i].v := -5; v[h].v := -5;
      if i = h then v[i].v := -7;
      gasit := true;
      break;
    end;
  end;

  if not gasit then
    writeln(-1)
  else
  begin
    p := 0;

    for i := 1 to n do
      for j := i to n do
        for k := j to n do
        begin
          inc(p);
          if v[p].v = -5 then write(v[p].x1,' ',v[p].x2,' ',v[p].x3,' ');
          if v[p].v = -7 then write(v[p].x1,' ',v[p].x2,' ',v[p].x3,' ',v[p].x1,' ',v[p].x2,' ',v[p].x3,' ');
        end;

  end;


  close(input);
  close(output);
end.
