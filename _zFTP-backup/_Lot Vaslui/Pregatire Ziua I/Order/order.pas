var n,i,pos,ram,p:longint;
    aib:array[0..30005]of longint;

function zeros(x:Longint):longint;
begin
  zeros := (x xor(x-1))and x;
end;

procedure add(x,v:Longint); inline;
begin
  repeat
    aib[x] := aib[x]+v;
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
  assign(input,'order.in'); reset(input);
  assign(output,'order.out'); rewrite(output);

  readln(n);

  for i := 1 to n do add(i,1);

  pos := 2; ram := n;
  for i := 1 to n do
  begin
    pos := pos + i-1;
    pos := pos mod ram; if pos = 0 then pos := ram;

    p := cb(pos);
    write(p,' ');
    add(p,-1);
    dec(ram);
  end;



  close(input);
  close(output);
end.
