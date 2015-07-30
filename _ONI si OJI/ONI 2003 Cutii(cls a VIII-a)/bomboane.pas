var n,t,b,i,pas,pos,dir,amp,gol,max:longint;
    a:array[1..1005]of longint;

begin
  assign(input,'cutii.in'); reset(input);
  assign(output,'cutii.out'); rewrite(output);

  readln(n,t,b); t := t mod (2*n-2);

  for i := 1 to n do a[i] := 0;
  pas := 0; pos := 1; dir := 1;

  repeat
    inc(pas); inc(a[pos]);

    pos := pos + dir*t;

    while (pos<1)or(pos>n) do
    begin
      if pos <= 0 then
      begin
        pos := -pos + 2;
        dir := 1;
      end
      else
      begin
        pos := 2*n-pos;
        dir := -1;
      end;
    end;


  until (pas=b)or(pos = 1);

  amp := b div pas; b := b mod pas;

  for i := 1 to n do a[i] := a[i]*amp;

  pas := 0; pos := 1; dir := 1;
  for i := 1 to b do
  begin
    inc(pas); inc(a[pos]);

    pos := pos + dir*t;

    while (pos<1)or(pos>n) do
    begin
      if pos <= 0 then
      begin
        pos := -pos + 2;
        dir := 1;
      end
      else
      begin
        pos := 2*n-pos;
        dir := -1;
      end;
    end;

  end;


  gol := 0; max := 0;
  for i := 1 to n do
  begin
    if a[i] = 0 then inc(gol);
    if a[i] > max then max := a[i];
  end;

  writeln(gol,' ',max);


  close(input);
  close(output);
end.
