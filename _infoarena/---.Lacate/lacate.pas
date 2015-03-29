var n,i,j,k:longint;
    a:array[0..260,0..260]of longint;
    bufout:array[1..65000]of byte;

begin
  assign(input,'lacate.in'); reset(input);
  assign(output,'lacate.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(n);

  k := 0;
  for i := 1 to n do
    for j := i to n-1 do
    begin
      inc(k);
      a[i,j] := k;
      a[j+1,i] := k;
    end;

  writeln(k,' ',n-1);
  for i := 1 to n do
  begin
    for j := 1 to n-1 do write(a[i,j],' ');
    writeln();
  end;


  close(input);
  close(output);
end.