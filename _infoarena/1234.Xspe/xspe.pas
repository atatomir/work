var n,i,st:longint;
    a,b:array[1..1000001]of longint;
    bufin,bufout:array[1..65000]of byte;
    stiva:array[0..1000001]of longint;


begin
  assign(input,'xspe.in'); reset(input);
  assign(output,'xspe.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);


  readln(n);
  for i := 1 to n do read(a[i]);

  st := 0; stiva[0] := 0;

  for i := n downto 1 do
  begin

    while  stiva[st] >= a[i] do begin st := st-1; end;
    inc(st);
    stiva[st] := a[i];

    b[i] := a[i] + stiva[st-1];

  end;


  for i := 1 to n do write(b[i],' ');

  close(input);
  close(output);
end.
