var n,i,j,y,k:longint;
    a,b:array[0..200005]of longint;
    bufout:array[1..65000]of byte;

begin
  assign(input,'aranjare2.in'); reset(input);
  assign(output,'aranjare2.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(n);

  for i := 1 to n do
  begin
    a[2*i-1] := i;
    a[2*i] := i+n;

    b[i] := 2*i-1;
    b[i+n] := 2*i;
  end;

  for i := 1 to 2*n do
  begin
    if a[i] <> i then
    begin
      j := a[i];
      writeln(i,' ',j);

      y := b[i]; b[i] := b[j]; b[j] := y;

      k := b[j];
      a[k] := j; a[i] := i;
    end;

    //for y := 1 to 2*n do write(a[y],' '); writeln();
  end;




  close(input);
  close(output);
end.
