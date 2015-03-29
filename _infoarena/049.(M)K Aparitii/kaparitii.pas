var n,k,i,j,x,t:longint;
    a:array[1..10,0..9]of longint;
    bufin:array[1..65000]of byte;
    s:array[1..10]of byte;

begin
  assign(input,'aparitii.in'); reset(input);
  assign(output,'aparitii.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,k);
  for i := 1 to 10 do
    for j := 0 to 9 do a[i,j] := 0;

  for i := 1 to n do
  begin
    read(x); t := 0;
    while x <> 0 do
    begin
      inc(t);
      inc(a[t,x mod 10]);
      x := x div 10;
    end;
  end;

  for i := 1 to 10 do
  begin
    s[i] := 0;
    for j := 0 to 9 do
    begin
      if a[i,j] mod k <> 0 then
      begin
        s[i] := j;
        break;
      end;
    end;
  end;

  i := 10;
  while s[i] = 0 do dec(i);

  for j := i downto 1 do write(s[j]);

  close(input);
  close(output);
end.
