var n,i,x,max,maxi:longint;
    a:array[0..1000005]of longint;
    bufin,bufout:array[1..65000]of byte;

begin
  assign(input,'mincinosi.in'); reset(input);
  assign(output,'mincinosi.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  for i := 0 to n do a[i] := 0;
  for i := 1 to n do
  begin
    read(x);  //writeln(x);
    inc(a[x]);
  end;

  max := -1;  maxi := -1;

  for i := 0 to n do
  begin
    if a[i] + i = n then
    begin
      if a[i] > max then
      begin
        max := a[i];
        maxi := i;
      end;
    end;
  end;

  close(input);
  assign(input,'mincinosi.in'); reset(input);
  settextbuf(input,bufin);

  readln(n);   writeln(max);
  for i := 1 to n do
  begin
    read(x);
    if x = maxi then
      writeln(i);
  end;               //writeln('TEST');

  close(input);
  close(output);
end.