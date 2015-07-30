var a:array[0..1,1..100]of longint;
    n,i,j,s,d:longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'neuroni.in'); reset(input);
  assign(output,'neuroni.out'); rewrite(output);
  settextbuf(input,bufin);

  read(n); read(a[0,1]); s := 0; d := 1;

  for i := 1 to n-1 do
  begin
    for j := 1 to i+1 do a[d,j] := 0;

    if i mod 2 = 0 then
      for j := 1 to i do
      begin
        a[d,j] := a[d,j] + (a[s,j]+1)div 2;
        a[d,j+1] := a[s,j] div 2;
      end
    else
      for j := 1 to i do
      begin
        a[d,j+1] := (a[s,j]+1)div 2;
        a[d,j] := a[d,j] + a[s,j] div 2;
      end;

    s := (s + 1) mod 2; d := (d + 1) mod 2;


  end;

  for i := 1 to n do write(a[s,i],' ');

  close(input);
  close(output);
end.
