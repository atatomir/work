var n,i,j,unu,CONT:longint;
    a:array[1..100003]of longint;
    bufin,bufout:array[1..65000]of byte;

begin
  assign(input,'move.in'); reset(input);
  assign(output , 'move.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n); cont := 0;
  for i := 1 to n do
  begin
    read(a[i]);
    if a[i] = 1 then unu := i;
  end;

  i := unu;     writeln(unu-1); cont := unu-1;

  while (a[i]<=n)and(i<=n) do
  begin
    j := i;
    while ((a[j+1])<>0)and(j+1<=n)  do inc(j); inc(j);
    if a[i] + 1 = a[j] then
    begin
      i := j;
    end
    else
    begin
      j := 0;
      while ((a[j+1] <> 0)or(a[j+1]<>(a[i]+1)))and(j+1<=n) do inc(j); inc(j);
      a[j] := 0;
      inc(a[i]);  dec(cont);
      if cont >= 0 then writeln(a[i]+1,' ',a[i]);

    end;

  end;


  close(input);
  close(output);
end.