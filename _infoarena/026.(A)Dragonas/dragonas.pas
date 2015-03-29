var t,ti:longint;
    n,m,l1,c1,l2,c2,h1,h2:longint;

begin
  assign(input,'dragonas.in'); reset(input);
  assign(output,'dragonas.out'); rewrite(output);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n,m);
    readln(l1,c1,l2,c2);

    if l1 > l2 then
      writeln('Lulu')
    else
    begin
      h1 := l2 - l1;
      h2 := c2 - c1; if h2 < 0 then h2 := -h2;

      if h1 < h2 then
        writeln('Lulu')
      else
        writeln('Smaug');

    end;

  end;



  close(input);
  close(output);
end.