var t,ti:longint;
    n,k,i,j,v1,v2,r:longint;
    a:array[0..2,0..100005]of longint;
    bufin:array[1..65000]of byte;

procedure QSort(l,h:longint);
var i,j,x,y:longint;
begin
  i := l ; j := h ; x := a[1,(i+j)div 2];
  repeat
    while a[1,i] < x do inc(i);
    while a[1,j] > x do dec(j);
    if i <=j then
    begin
      y := a[1,i]; a[1,i] := a[1,j]; a[1,j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  assign(input,'kcover.in'); reset(input);
  assign(output,'kcover.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);

  for ti := 1 to t do
  begin
    readln(n,k);
    for i := 1 to n do
    begin
      read(a[1,i]);
    end;
    readln();

    QSort(1,n);
    r := a[1,1];
    for i := 1 to n do
    begin
      a[1,i] := a[1,i] - r;
      a[0,i] := a[1,i];
    end;

    for i := 2 to k do
    begin
      a[2,i] := 0;
      for j := i+1 to n do
      begin
        v1 := a[1,j-1]; v2 := a[2,j-1] + a[0,j] - a[0,j-1];
        if v1 < v2 then
          a[2,j] := v1
        else
          a[2,j] := v2;
      end;

      for j := i to n do a[1,j] := a[2,j];


    end;

    writeln(a[1,n]);

  end;



  close(input);
  close(output);
end.