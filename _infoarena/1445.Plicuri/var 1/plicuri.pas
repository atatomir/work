type plic=record
       x,y:longint;
       ar:real;
     end;
var n,i,max,c1,c2:longint;
    a:array[0..100001]of plic;
    bufin:array[1..65000]of byte;

procedure QSort(lo,hi:longint);
var i,j,m,y:longint;
    yr:real;
begin
  i := lo; j := hi; m := (i+j)div 2;
  repeat
    while a[i].ar > a[m].ar do inc(i);
    while a[j].ar < a[m].ar do dec(j);
    if i <=j then
    begin
      y := a[i].x; a[i].x := a[j].x; a[j].x := y;
      y := a[i].y; a[i].y := a[j].y; a[j].y := y;
      yr := a[i].ar; a[i].ar := a[j].ar; a[j].ar := yr;
      inc(i); dec(j);
    end;
  until i>j;
  if j > lo then QSort(lo,j);
  if i < hi then QSort(i,hi);
end;

begin
  assign(input,'plicuri.in'); reset(input);
  assign(output,'plicuri.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do
  begin
    readln(a[i].x,a[i].y);
    a[i].ar := (a[i].x+a[i].y)/2;
  end;

  QSort(1,n);
  max := 0; c1 := a[1].x; c2 := a[1].y;
  for i := 2 to n do
  begin   //writeln(a[i].x,' ',a[i].y,' ',a[i].ar:0:1,' ',c1,' ',c2);
    if ((c1 > a[i].x) and (c2 > a[i].y)) or
       ((c1 > a[i].y) and (c2 > a[i].x)) then
    begin
      inc(max);
      c1 := a[i].x;
      c2 := a[i].y;
    end;
  end;


  write(max+1);
  close(input);
  close(output);
end.