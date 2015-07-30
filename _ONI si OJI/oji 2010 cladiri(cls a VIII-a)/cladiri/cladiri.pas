var x0,y0,cont,int,max,i0:longint;
    i:longint;
    a:array[0..10001]of longint;
    bufin:array[1..65000]of byte;
    x,y,r:longint;

function getint(x,y:longint):longint;
var a,b:longint;
begin
  a := x0 - x; if a < 0 then a := -a;
  b := y0 - y; if b < 0 then b := -b;

  if a > b then
    getint := a
  else
    getint := b;
end;

begin
  assign(input,'cladiri1.in'); reset(input);
  assign(output,'cladiri1.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(x0,y0,i0);
  for i := 0 to 10000 do a[i] := 0;
  cont := 0;

  while not eof(input) do
  begin
    readln(x,y,r);
    int := getint(x,y);
    r := i0 - int  - r;

    if r >= 0 then
    begin
      inc(cont);
      inc(a[int]);
    end;

  end;

  writeln(cont);
  max := a[0];
  for i := 1 to 10000 do
  begin
    if max < a[i] then
      max := a[i];
  end;
  writeln(max);
  if max > 0 then
    for i := 0 to 10000 do
      if a[i] = max then
        write(i,' ');


  close(input);
  close(output);
end.
