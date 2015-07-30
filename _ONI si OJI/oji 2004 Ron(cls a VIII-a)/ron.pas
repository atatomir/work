var k,l,s,max:longint;

begin
  assign(input,'ron.in'); reset(input);
  assign(output,'ron.out'); rewrite(output);

  readln(k); inc(k);
  readln(l,s);
  max := 0;

  if l = s then
  begin
    writeln('O');
    exit;
  end;

  while k <> 1 do
  begin
    k := (k+2)div 3;
    inc(max);
  end;


  if l = max then
    writeln('L')
  else
  if s = max then
    writeln('S')
  else
    writeln('O');

  close(output);
  close(input);
end.