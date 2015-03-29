var n,i,j:longint;
    a:array[0..100005,1..3]of longint;
    bufin:array[1..65000]of byte;
    a1,a2,b1,b2,c1,c2:int64;
    x,y:real;
    xmin,xmax,ymin,ymax:real;

begin
  assign(input,'drepte3.in'); reset(input);
  assign(output,'drepte3.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to n do readln(a[i,1],a[i,2],a[i,3]);

  for i := 1 to n-1 do
    for j := i+1 to n do
    begin
      a1 := a[i,1]; a2 := a[j,1];
      b1 := a[i,2]; b2 := a[j,2];
      c1 := a[i,3]; c2 := a[j,3];


      y := (c2*a1-c1*a2)/(b1*a2-b2*a1);
      x := (b1*c2-b2*c1)/(a1*b2-a2*b1);

      if (i+j=3) then
      begin
        xmin := x; xmax := x;
        ymin := y; ymax := y;
      end;

      if x < xmin then xmin := x else
      if x > xmax then xmax := x;
      if y < ymin then ymin := y else
      if y > ymax then ymax := y;

    end;

  writeln((xmax-xmin)*(ymax-ymin):0:7);


  close(input);
  close(output);
end.
