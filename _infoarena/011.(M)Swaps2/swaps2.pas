var n,nr,i,j,cont,caut:longint;
    r:array[1..2,1..501]of smallint;
    a:array[1..1001]of char;

begin
  assign(input,'swaps2.in'); reset(input);
  assign(output,'swaps2.out'); rewrite(output);

  readln(n);   nr := 0; cont := 0;
  for i := 1 to n do
  begin
    read(a[i]);
    if a[i] = '1' then inc(nr);
  end;

  caut := 0;
  for i := (n-nr+1) to n do
    if a[i] = '0' then inc(caut);

  i := 1;
  j := n;
  while caut > 0 do
  begin
    while a[i] = '0' do inc(i);
    while a[j] = '1' do dec(j);

    inc(cont); r[1,cont] := i; r[2,cont] := j;
    dec(caut);
    inc(i); dec(j);
  end;

  writeln(cont);
  for i := 1 to cont do
    writeln(r[1,i],' ',r[2,i]);



  close(input);
  close(output);
end.
