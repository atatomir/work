var x,y:array[1..4]of longint;
    q,i:longint;
    d1,d2,d3:int64;
    bufin,bufout:array[1..65000]of byte;
    x1,x2:int64;

begin
  assign(input,'qtri.in'); reset(input);
  assign(output,'qtri.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(q);
  for i := 1 to q do
  begin
    readln(x[1],y[1],x[2],y[2],x[3],y[3],x[4],y[4]);
    d1 := x[1]*y[2] - x[2]*y[1] +
          x[2]*y[4] - x[4]*y[2] +
          x[4]*y[1] - x[1]*y[4];
    d2 := x[2]*y[3] - x[3]*y[2] +
          x[3]*y[4] - x[4]*y[3] +
          x[4]*y[2] - x[2]*y[4];
    d3 := x[3]*y[1] - x[1]*y[3] +
          x[1]*y[4] - x[4]*y[1] +
          x[4]*y[3] - x[3]*y[4];
    x1 := d1*d2; x2 := d2*d3;
    if (x1 > 0) and (x2 > 0)  then
      writeln('DA')
    else
      writeln('NU');
  end;


  close(input);
  close(output);
end.
