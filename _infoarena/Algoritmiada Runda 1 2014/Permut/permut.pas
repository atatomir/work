var n,i:longint;
    bufin:array[1..65000]of byte;
    v:array[1..2,0..100001]of longint;
    val,x1,x2:int64;

procedure QSort(q,l,r:longint);
var i,j,x,y:longint;
begin
  i := l; j := r; x := v[q,(i+j)div 2];
  repeat
    while v[q,i] < x do inc(i);
    while v[q,j] > x do dec(j);
    if i <= j then
    begin
      y := v[q,i] ; v[q,i] := v[q,j]; v[q,j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if i < r then QSort(q,i,r);
  if j > l then QSort(q,l,j);
end;


begin
  assign(input,'permut.in'); reset(input);
  assign(output,'permut.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do read(v[1,i]); readln();
  for i := 1 to n do read(v[2,i]);
  QSort(1,1,n); QSort(2,1,n);

  val := 0;
  for i := 1 to n do
  begin
    x1 := v[1,i] ; x2 := v[2,i];
    val := val + x1*x2;
  end;

  writeln(val);

  close(input);
  close(output);
end.