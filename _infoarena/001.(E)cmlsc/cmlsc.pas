var n,m,i,j,caut:longint;
    a,b,s:array[0..1050]of byte;
    r:array[0..1050,0..1050]of longint;

function maxim(a,b:longint):longint; begin if a < b then maxim := b else maxim := a; end;

begin
  assign(input,'cmlsc.in'); reset(input);
  assign(output,'cmlsc.out'); rewrite(output);

  readln(n,m);
  for i := 1 to n do read(a[i]); readln();
  for i := 1 to m do read(b[i]);

  for i := 0 to n do r[i,0] := 0;
  for i := 1 to m do r[0,i] := 0;

  for i := 1 to n do
    for j := 1 to m do
      if a[i] = b[j] then
        r[i,j] := r[i-1,j-1]+1
      else
        r[i,j] := maxim(r[i-1,j],r[i,j-1]) ;

  writeln(r[n,m]); caut := r[n,m]; i := n; j := m; s[0] := 0;
  while caut <> 0 do
  begin
    while r[i-1,j] = r[i,j] do dec(i);
    while r[i,j-1] = r[i,j] do dec(j);
    inc(s[0]); s[s[0]] := a[i];
    dec(i); dec(j);
    dec(caut);
  end;

  for i := s[0] downto 1 do write(s[i],' ');

  close(input);
  close(output);
end.