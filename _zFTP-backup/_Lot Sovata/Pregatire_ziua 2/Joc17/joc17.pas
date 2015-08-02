var t,ti,n,m:longint;
    s:string;

begin
  assign(input,'joc17.in'); reset(input);
  assign(output,'joc17.out'); rewrite(output);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n,m);
    if (n*m) mod 2 = 1 then s := 'First' else s := 'Second';
    writeln('Case ',ti,': ',s);
  end;


  close(input);
  close(output);
end.