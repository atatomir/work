var n,i,x,p:longint;
    aib,sol:array[0..50005]of longint;
    bufin,bufout:array[1..65000]of byte;

function zeros(x:longint):longint;
begin
  zeros := (x xor (x-1))and x;
end;

procedure add(x,v:longint);inline;
begin
  repeat
    aib[x] := aib[x] + v;
    x := x + zeros(x);
  until x > n;
end;

function sum(x:longint):longint;
begin
  sum := 0;

  if x > n then begin sum := 100000; exit; end;

  repeat
    sum := sum + aib[x];
    x := x - zeros(x);
  until x = 0;
end;

function cb(x:longint):longint;
var v,pas,h:longint;
begin
  cb := 0; v := 1 shl 17;
  for pas := 17 downto 1 do
  begin
    v := v shr 1; h := sum(cb+v); writeln(h,' ',x,' ',v);
    if x >= h then
    begin
      cb := cb + v;
    end;
  end;
end;

begin
  assign(input,'concurs1.in'); reset(input);
  assign(output,'concurs1.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 1 to n do begin aib[i] := 0; sol[i] := 0; end;
  for i := 1 to n do add(i,1);

  for i := 1 to n do
  begin
    read(x); inc(x);

    if n-i+1 < x then begin writeln('NU ARE SOLUTIE'); close(input); close(output); exit; end;

    p := cb(x);

    sol[i] := p;
    add(p,-1);

  end;

  for i := 1 to n do write(sol[i],' ');

  close(input);
  close(output);
end.
