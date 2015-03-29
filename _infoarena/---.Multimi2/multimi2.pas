var i,cont:longint;
    a:array[0..1000000]of boolean;
    caut,n:int64;

begin
  assign(input,'multimi2.in'); reset(input);
  assign(output,'multimi2.out'); rewrite(output);

  readln(n);
  for i := 1 to n do a[i] := false;
  caut := (n*(n+1))div 2; caut := caut div 2;

  i := n ; cont := 0;
  while caut - i >= 0 do
  begin
    a[i] := true;
    caut := caut-i;
    dec(i); inc(cont);
  end;
  a[caut] := true;
  if caut > 0 then inc(cont);

  writeln(((n*(n+1))div 2)mod 2);
  writeln(cont);
  for i := 1 to n do
    if a[i] then
      write(i,' ');
  writeln(); writeln(n-cont);
  for i := 1 to n do
    if not a[i] then
      write(i,' ');




  close(input);
  close(output);
end.