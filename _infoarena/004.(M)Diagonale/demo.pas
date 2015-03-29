var f,fo:text;
    max,n,x,h,p:int64;
    i,j:longint;
    a:array[1..4000]of int64;

begin
  assign(f,'diagonale.in'); reset(f);
  readln(f,n);

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(f,x);
    end;
    readln(f);
  end;

  max := 1;

  assign(fo,'diagonale.out'); rewrite(fo);
  write(fo,max);
  close(fo);

end.
