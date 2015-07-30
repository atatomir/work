var n,i,j,x,y:longint;
    bufout:array[1..65000]of byte;
    a:array[1..200,1..100]of longint;

begin
  assign(input,'sume.in'); reset(input);
  assign(output,'sume.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(n);

    for i := 1 to n do
      for j := 1 to n do
        a[i,j] := n*(i-1)+j;
    for i := 1 to n do
      for j := 1 to n do
        a[i+n,j] := n*(i-1)+j;

    for i := 1 to n do
    begin
      x := i; y := 1;
      for j := 1 to n do
      begin
        write(a[x,y],' ');
        inc(x); inc(y);
      end;
      writeln();

    end;



  close(input);
  close(output);
end.