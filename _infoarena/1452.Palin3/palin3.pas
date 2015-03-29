var t,ti,i:longint;
    a:array[0..55]of char;

begin
  assign(input,'palin3.in'); reset(input);
  assign(output,'palin3.out'); rewrite(output);

  readln(t);
  for ti := 1 to t do
  begin
    read(a[1]);  i := 1;
    while pos(a[i],'abcdefghijklmnopqrstuvxwyz') <> 0 do
    begin     //writeln(i,a[i]);
      if i >= 3 then
      begin
        if a[i] = a[i-2] then i := i - 3;
      end;

      inc(i); read(a[i]);
    end;
    readln();
    if i = 1 then writeln('DA') else writeln('NU');
  end;




  close(input);
  close(output);
end.