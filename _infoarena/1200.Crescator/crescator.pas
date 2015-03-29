var n,i,max,nr,e,ant,x,j:longint;
    a:array[1..100001]of longint;
    bufin,bufout:array[1..65000]of byte;
    cont:int64;

begin
  assign(input,'crescator.in');   reset(input);
  assign(output,'crescator.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);  nr := 0;
  read(ant); e := 1;   max := -1;   cont := 0;

  for i := 2 to n do
  begin
    read(x);  //writeln(x,'!',ant);
    if x >= ant then
      inc(e)
    else
    begin
      inc(nr);
      a[nr] := e; if  max < e then max := e;
      e := 1;
    end;
    ant := x;
  end;

  inc(nr) ; a[nr] := e;  if  max < e then max := e;

  //for i := 1 to nr do write(a[i],' ');  writeln();

  for i := 1 to max do
  begin
    for j := 1 to nr do
    begin
      if a[j] - i + 1 >0 then
        cont := cont + a[j] - i +1;
    end;
  end;

  writeln(cont,' ',max);

  close(input);
  close(output);
end.
