var n,m:longint;
    max,a,b:int64;

begin
  assign(input,'dmin2.in'); reset(input);
  assign(output,'dmin2.out'); rewrite(output);

  readln(n,m);
  a := n;
  b := m;
      max := (a-1)*(a-2) div 2 -b;
      //if m > (n-1)*(n-2) div 2 then max := 0 else max := max - m ;
      //if max<0 then max := 0;
      write(max);



  close(input);
  close(output);
end.
