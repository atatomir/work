const vect=50;
var n,p,i,sum,a,b,c,pos,j,scrie:longint;
    v:array[0..vect+5]of longint;
    r:array[0..1005,0..1005]of longint;
 
function cauta(x:longint):boolean;
var i,j,m:longint;
begin
  i := 1; j := vect;
  repeat
    m := (i+j)div 2;
    if x <= v[m] then
      j := m-1
    else
      i := m+1;
  until i > j;
  if x = v[i] then begin pos := i; cauta := true; end else cauta := false;
end;
 
procedure get(sum:longint;var a,b,c:longint); inline;
var i,j:longint;
begin
    for i := 1 to 50 do
      for j := i to 50 do
      begin
        if cauta(v[i]+v[j] - sum) then
        begin
          a := i; b := j; c := pos; exit;
        end;
      end;
end;
 
begin
  assign(input,'patrate5.in'); reset(input);
  assign(output,'patrate5.out'); rewrite(output);
 
  readln(n,p);
  v[0] := vect;
  for i := 1 to vect do v[i] := i*i;
 
  r[1,1] := 2; r[1,2] := 2; sum := 8; r[1,0] := 2;
 
  for i := 3 to n do
  begin
    get(sum,a,b,c);
    for j := 1 to i-2 do
    begin
      inc(r[j,0]);
      r[j,r[j,0]] := c;
    end;
    r[i-1,0] := 2;
    r[i-1,1] := a; r[i-1,2] := b;
    sum := sum + c*c;
 
  end;
 
  writeln(sum); scrie := n-p+1;
  for j := scrie downto 1 do
  begin
    for i := 1 to r[j,0] do write(r[j,i],' ');
    writeln();
  end;
 
 
 
 
  close(input);
  close(output);
end.