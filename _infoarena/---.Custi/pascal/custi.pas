var n,i,j:longint;
    a:array[0..1005,0..1005]of byte;
    bufin,bufout:array[1..65000]of byte;
    v:array[0..1001]of longint;

function min(a,b,c:longint):longint;
begin
  min := a;
  if min > b then min := b;
  if min > c then min := c;
end;

begin
  assign(input,'custi.in'); reset(input);
  assign(output,'custi.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 0 to n do
  begin
    a[i,0] := 0;
    a[0,i] := 0;
  end;

  for i := 1 to n do
  begin
    for j := 1 to n do
    begin
      read(a[i,j]);
      if a[i,j] = 1 then
        a[i,j] := min(a[i-1,j]+1,a[i,j-1]+1,a[i-1,j-1]+1);
      inc(v[a[i,j]]);
    end;
    readln();
  end;

  for i := n-1 downto 1 do
    v[i] := v[i] + v[i+1];

  for i := 1 to n do
    writeln(v[i]);


  close(input);
  close(output);
end.
