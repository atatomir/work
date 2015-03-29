var f,fo:text;
    max ,n:int64;
    s:int64;
    i,j,l:longint;
    a:array[1..1000,1..1000]of longint;
    bufin:array[1..65000]of byte;

begin
  settextbuf(f,bufin);
  assign(f,'diagonale.in'); reset(f);
  readln(f,n);
  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(f,a[i,j]);
    end;
    readln(f);
  end;
  close(f);

  max := a[1,1];

  for i := 1 to n do
  begin
    s:=0;
    j := 0; l := i-1;
    repeat
      inc(j);inc(l);
      s := s + a[j,l];
    until l = n;
    if s > max then max := s;
    s:=0;
    j :=0; l := i+1;
    repeat
      inc(j); l := l-1;
      s := s + a[j,l]
    until l=1;
    if s > max then max := s;
  end;

  for i := 1 to n do
  begin
    s := 0;
    j := n+1; l := i+1;
    repeat
      j := j -1; l := l-1;
      s := s + a[j,l];
    until l = 1;
    if s > max then max := s;
    s :=0;
    j := n+1; l := i -1;
    repeat
      j := j -1; inc(l);
      s := s + a[j,l];
    until l=n;
    if s > max then max := s;
  end;


  assign(fo,'diagonale.out'); rewrite(fo);
  write(fo,max);
  close(fo);

end.
