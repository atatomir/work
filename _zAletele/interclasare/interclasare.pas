program interclasare_siruri_orig_ordonate;
var a,b:array[1..1000]of byte;
    c:array[1..2000]of byte;
    i,j,z,n,m,h:longint;
    bufin,bufout:array[1..65000]of byte;

begin
  assign(input,'interclasare.in'); reset(input);
  assign(output,'interclasare.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n,m);
  for i := 1 to n do read(a[i]);
  readln();
  for i := 1 to m do read(b[i]);

  i := 1; j := 1; z := 0;

  while (i<=n) and (j<=m) do
  begin
    if a[i] < b[j] then
    begin
      inc(z);
      c[z] := a[i];
      inc(i);
    end
    else
    begin
      inc(z);
      c[z] := b[j];
      inc(j);
    end;
  end;

  if i <= n then
  begin
    for h := i to n do
    begin
      inc(z);
      c[z] := a[h];
    end;
  end
  else
  if j <= m then
  begin
    for h := j to m do
    begin
      inc(z);
      c[z] := b[h];
    end;
  end;

  for i := 1 to z do write(c[i],' ');


  close(input);
  close(output);
end.
