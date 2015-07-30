var n,i,j:longint;
    a:array[1..1001]of integer;
    r:array[1..1001]of longint;
    suma:int64;
    bufin,bufout:array[1..65000]of byte;


procedure down(x:longint);
var t:longint;
begin
  for t := 1 to x do
    inc(r[t]);
  inc(a[x+1]);
end;

procedure up(x:longint);
var t:longint;
begin
  for t := n downto x+1 do
    inc(r[t]);
  dec(a[x+1]);
end;

begin
  assign(input,'butoane.in'); reset(input);
  assign(output,'butoane.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);   suma := 0;
  for i := 1 to n do
  begin
    read(a[i]);
    suma := suma + a[i];
  end;

  suma := suma div n;
  for i := 1 to n do r[n] := 0;

  for i := 1 to n-1 do
  begin

    {for j := 1 to n do write(a[j],' ');
    writeln();
    for j := 1 to n do write(r[j],' ');
    writeln();    writeln();     }

    if a[i] < suma then
    begin
      for j := 1 to suma - a[i] do up(i);
    end
    else
    if a[i] > suma then
    begin
      for j := 1 to a[i]-suma do down(i);
    end;

    a[i] := suma;

  end;



  for i := 1 to n do writeln(r[i]);

  close(input);
  close(output);
end.
