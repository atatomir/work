var a:array[1..2001]of byte;
    transport:boolean;
    i,n:longint;
    bufin,bufout:array[1..65000]of byte;
    c:char;

procedure imparte;
begin
  transport := false;
  for i := 1 to n do
  begin
    if transport = true then a[i] := 10 + a[i];
    if a[i] mod 2 = 1 then transport := true else transport := false;
    a[i] := a[i] div 2;
  end;
end;

procedure scade2;
begin
  a[n] := a[n] - 2;
  if a[n] < 0 then
  begin
    a[n] := a[n] + 10;
    a[n-1] := a[n-1] - 1;
    for i := n-1 downto 2 do
    begin
      if a[i] < 0 then
      begin
        a[i] := a[i] + 10;
        a[i-1] := a[i-1] -1;
      end
      else
        break;
    end
  end;
end;

begin
  assign(input,'minge.in'); reset(input);
  assign(output,'minge.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  n := 0;
  while not eof(input) do
  begin
    read(c);
    case c of
      '0': begin inc(n); a[n] := 0; end;
      '1': begin inc(n); a[n] := 1; end;
      '2': begin inc(n); a[n] := 2; end;
      '3': begin inc(n); a[n] := 3; end;
      '4': begin inc(n); a[n] := 4; end;
      '5': begin inc(n); a[n] := 5; end;
      '6': begin inc(n); a[n] := 6; end;
      '7': begin inc(n); a[n] := 7; end;
      '8': begin inc(n); a[n] := 8; end;
      '9': begin inc(n); a[n] := 9; end;
    end;
  end;


  if a[n] mod 2 = 1 then  a[n] := a[n]-1 else scade2;

  imparte;

  //if a[n] mod 2 = 1 then
  //begin
    if a[1] > 0 then write(a[1]);
    for i := 2 to n do write(a[i]);
  //end
  //else
  //  write('1');


  close(input);
  close(output);
end.
