var n,i,j,l:longint;
    s:string;
    a:array[2..7,0..260]of longint;
    iesi:boolean;

procedure finished;inline;
begin
  iesi := true;
end;

begin
  readln(n); l := n;
  readln(s);

  for i := 2 to 7 do
    for j := 0 to n+1 do
      a[i,j] := 0;

  for i := 1 to n do
  begin
    if s[i] = '?' then
    begin
      a[2,i] := a[2,i-1]+1;
      a[3,i] := a[3,i-1]+1;
      a[5,i] := a[5,i-1]+1;
      a[7,i] := a[7,i-1]+1;
    end
    else
    begin
      a[ord(s[i])-$30,i] := a[ord(s[i])-$30,i-1]+1;
    end;
  end;

  iesi := false;
  for i := 1 to l do
    if a[2,i] = 2 then finished;
  for i := 1 to l do
    if a[3,i] = 3 then finished;
  for i := 1 to l do
    if a[5,i] = 5 then finished;
  for i := 1 to l do
    if a[7,i] = 7 then finished;

  if not iesi then writeln('boring') else writeln('cool');
end.