var bufin,bufout:array[1..65000]of byte;
    n,i,max,imax,t,j:longint;
    a:array[1..500001]of longint;

begin
  assign(input,'algsort.in'); reset(input);
  assign(output,'algsort.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 1 to n do read(a[i]);

  for i := 1 to n-1 do
  begin
    max := a[i];
    imax := i;

    for j := i+1 to n do
    begin
      if max > a[j] then
      begin
        max := a[j];
        imax := j;
      end;
    end;

    if i <> imax then
    begin
      t := a[i];
      a[i] := max;
      a[imax] := t;
    end;
  end;

  for i := 1 to n do write(a[i],' ');

  close(input);
  close(output);
end.
