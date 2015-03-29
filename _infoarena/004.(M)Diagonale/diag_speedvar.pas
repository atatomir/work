var f,fo:text;
    max:int64;
    x:longint;
    i,j,p,n,h : smallint;
    a:array[1..4000]of int64;
    bufin :array[1..65355] of byte;

begin
  assign(f,'diagonale.in'); reset(f);
  settextbuf(f,bufin);

  readln(f,n);

  h := 4*n-2;
  for i := 1 to h do a[i] := 0;

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(f,x);
      p := i+j-1;
      a[p] := a[p] + x;
      p := 3*n-1+ i-j;
      a[p] := a[p] + x;
    end;
    readln(f);
  end;
  close(f);

  max := a[1];
  for i := 2 to h do
    if a[i] > max then max := a[i];

  assign(fo,'diagonale.out'); rewrite(fo);
  write(fo,max);
  close(fo);

end.
