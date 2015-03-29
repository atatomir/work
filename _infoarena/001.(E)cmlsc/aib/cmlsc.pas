var n,m,i,j,max,p,cont:longint;
    a,b,r,v:array[0..1050]of byte;
    aib:array[0..1050]of longint;
    rez:array[0..1050,1..2]of longint;

function zeros(x:longint):longint;
begin
  zeros := (x and (x-1))xor x;
end;

function maxim(pos:longint):longint;
begin
  maxim := aib[pos];
  repeat
    if maxim < aib[pos] then maxim := aib[pos];
    pos := pos - zeros(pos);
  until pos = 0;
end;

procedure add(pos,v:longint);inline;
begin
  repeat
    if aib[pos] < v then
    begin
     aib[pos] := v;
     pos := pos + zeros(pos);
    end
    else
      break;
  until pos > n;
end;

begin
  assign(input,'cmlsc.in'); reset(input);
  assign(output,'cmlsc.out'); rewrite(output);

  readln(n,m);
  for i := 1 to n do read(a[i]); readln();
  for i := 1 to m do read(b[i]);

  for i := 0 to n do aib[i] := 0;

  for i := 1 to m do
  begin
    max := 0; cont := 0;
    for j := 1 to n do
      if a[j] = b[i] then
      begin
        max := maxim(j-1)+1;
        if r[j] < max then r[j] := max;
        inc(cont); rez[cont,1] := j; rez[cont,2] := max;
      end;
    for j := 1 to cont do add(rez[j,1],rez[j,2]);
  end;


  max := 0;
  for i := 1 to n do
    if r[i] > max then max := r[i];

  writeln(max); p := max;

  for i := n downto 1 do
    if r[i] = max then
    begin
      v[max] := a[i];
      dec(max);
    end;

  for i := 1 to p do write(v[i],' ');

  close(input);
  close(output);
end.