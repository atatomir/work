var n,m,t:longint;
    op:longint;

begin
  assign(input,'dreptunghi.in'); reset(input);
  assign(output,'dreptunghi.out'); rewrite(output);

  readln(n,m);  op := 0;

  while (n<>0)and(m<>0) do
  begin
    if n > m then
    begin
      t := n ; n := m ; m := t;
    end;

    op := op + n*(m div n);
    m := m mod n;

  end;

  writeln(op);

  close(input);
  close(output);
end.
