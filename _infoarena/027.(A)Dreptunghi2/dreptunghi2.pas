var t,ti:longint;
    n,i,x,y,h1,h2:longint;
    bufin:array[1..65000]of byte;
    min1,min2,max1,max2:longint;
    xx,yy:array[1..3]of real;
    l1,l2:real;

procedure intersect(b1,b2:longint;var x,y:real);
begin
  x := (b2 - b1)/2;
  y := x + b1;
end;

begin
  assign(input,'dreptunghi2.in'); reset(input);
  assign(output,'dreptunghi2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    readln(x,y);
    min1 := y - x; max1 := y - x;
    min2 := y + x; max2 := y + x;

    for i := 2 to n do
    begin
      readln(x,y);
      h1 := y-x; h2 := y + x;
      if h1 < min1 then
        min1 := h1
      else
      if h1 > max1 then
        max1 := h1;

      if h2 < min2 then
        min2 := h2
      else
      if h2 > max2 then
        max2 := h2;
    end;

    intersect(max1,max2,xx[1],yy[1]);
    intersect(min1,max2,xx[2],yy[2]);
    intersect(min1,min2,xx[3],yy[3]);

    l1 := sqrt(sqr(xx[1]-xx[2])+sqr(yy[1]-yy[2]));
    l2 := sqrt(sqr(xx[2]-xx[3])+sqr(yy[2]-yy[3]));
    l1 := l1*l2;


    writeln(l1:0:3);
  end;



  close(input);
  close(output);
end.