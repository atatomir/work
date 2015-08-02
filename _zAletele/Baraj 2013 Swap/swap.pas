var a:array[1..90001]of char;
    stiva:array[1..50001]of longint;
    cost:int64;
    n,i,s,desc,cont:longint;
    x:char;

begin
  assign(input,'swap.in'); reset(input);
  assign(output,'swap.out'); rewrite(output);

  readln(n);

  s := 0; cost := 0;
  for i := 1 to n do
  begin
    read(x); a[i] := x;
    if x = '(' then
    begin
      inc(s);
      stiva[s] := i;
    end
    else
    begin
      cost := cost + i - stiva[s] ;
      dec(s);
    end;
  end;

  writeln(cost);

  desc := 0; cont := 0;

  for i := 1 to n-1 do
  begin
    if (a[i] = '(') and (a[i+1] = ')') then
    begin
      if desc > 0 then
        inc(cont);
    end;


    if a[i] = '(' then inc(desc) else dec(desc);
  end;

  if cont = 0 then
  begin
    writeln('-1');
    writeln('0');
  end
  else
  begin
    writeln(cost-2);
    writeln(cont);
  end;


  close(input);
  close(output);
end.