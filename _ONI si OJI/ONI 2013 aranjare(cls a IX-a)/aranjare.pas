var n,i:longint;
    bufin,bufout:array[1..65000]of byte;
    a,b:array[1..200001]of longint;

begin
  assign(input,'aranjare.in'); reset(input);
  assign(output,'aranjare.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);

  for i := 1 to n do
  begin
    a[i] := 2*i-1;
  end;
  for i := 1 to n do
  begin
    a[i+n] := 2*i;
  end;

  for i := 1 to 2*n  do
    b[a[i]] := i;

  for i := 1 to 2*n do
  begin
    if a[i] <> i then
    begin
      writeln(i,' ',b[i]);
      a[b[i]] := a[i];
      b[a[i]] := b[i];
    end;
  end;

  close(input);
  close(output);
end.