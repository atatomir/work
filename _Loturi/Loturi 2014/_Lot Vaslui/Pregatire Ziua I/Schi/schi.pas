var n,i,pos:longint;
    a,sol:array[0..30005]of longint;
    aib:array[0..30005]of longint;

function zeros(x:longint):longint;
begin
  zeros := (x xor(x-1))and x;
end;

procedure add(x,v:longint); inline;
begin
  repeat
    aib[x] := aib[x] + v;
    x := x + zeros(x);
  until x > n;
end;

function sum(x:longint):longint;
begin
  sum := 0;
  repeat
    sum := sum + aib[x];
    x := x - zeros(x);
  until x = 0;
end;

function cb(x:longint):longint;
var i,j,m:longint;
begin
  i := 1; j := n;
  repeat
    m := (i+j)div 2;
    if x <= sum(m) then
      j := m-1
    else
      i := m+1;
  until i > j;
  cb := i;
end;


begin
  assign(input,'schi.in'); reset(input);
  assign(output,'schi.out'); rewrite(output);

  readln(n);
  for i := 1 to n do readln(a[i]);

  for i := 1 to n do add(i,1);

  for i := n downto 1 do
  begin
    pos := cb(a[i]);
    sol[pos] := i;
    add(pos,-1);
  end;

  for i := 1 to n do writeln(sol[i]);

  close(input);
  close(output);
end.