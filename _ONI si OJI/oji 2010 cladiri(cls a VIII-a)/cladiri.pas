var x,y,int,cld,i,niv,max,imax:longint;
    x2,y2,int2:longint;
    a:array[0..10005]of longint;
    bufin:array[1..65000]of byte;

function maxim(a,b:longint):longint;
begin
  if a < 0 then a := -a;
  if b < 0 then b := -b;
  if a < b then maxim := b else maxim := a;
end;


begin
  assign(input,'cladiri.in'); reset(input);
  assign(output,'cladiri.out'); rewrite(output);
  settextbuf(input,bufin);

  cld := 0;
  for i := 0 to 10005 do a[i] := 0;

  readln(x,y,int);
  while not eof(input) do
  begin
    readln(x2,y2,int2);
    niv := maxim(x-x2,y-y2);
    if int2 <= int-niv then
    begin
      inc(cld);
      inc(a[niv]);
    end;
  end;

  writeln(cld);
  max := 0; imax := 0;

  for i := 0 to  10000 do
    if a[i] > max then
    begin
      max := a[i];
      imax := 1;
    end
    else
    begin
      if a[i] = max then inc(imax);
    end;

  writeln(max);
  if max <> 0 then
  for i := 0 to 10000 do
    if a[i] = max then write(i,' ');


  close(input);
  close(output);
end.
