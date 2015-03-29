var t,i,j,start,final:longint;
    a:array[-10..510]of smallint;
    rez,nr:int64;
    bufin,bufout:array[1..65000]of byte;
    s:ansistring;

procedure  incrementare;
var y:longint;
begin
  inc(a[final]);
  y := final;
  while a[y] > 9 do
  begin
    a[y] := a[y] -10;
    a[y-1] := a[y-1] + 1;
    dec(y);
  end;
  if y = start-1 then  dec(start);
end;

procedure decrementare;
var y:longint;
begin
  dec(a[final]);
  y := final;
  while a[y] < 0 do
  begin
    a[y] := a[y] + 10;
    a[y-1] := a[y-1] - 1;
    dec(y);
  end;
  if a[start]=0 then inc(start);
end;

procedure div2;
var y:longint;
begin

  for y := start to final do
  begin
    a[y+1] := a[y+1] + (10*(a[y] mod 2));
    a[y] := a[y] div 2;
  end;

  if a[start]=0 then inc(start);

end;


begin
  assign(input,'doi.in'); reset(input);
  assign(output,'doi.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(t);
  for i := 1 to t do
  begin
    readln(s);  rez := 0;   final := 0;   a[0] := 0; a[length(s)] := 0;

    for j := 1 to length(s) do
    begin
      case s[j] of
        '0': begin inc(final); a[final] := 0; end;
        '1': begin inc(final); a[final] := 1; end;
        '2': begin inc(final); a[final] := 2; end;
        '3': begin inc(final); a[final] := 3; end;
        '4': begin inc(final); a[final] := 4; end;
        '5': begin inc(final); a[final] := 5; end;
        '6': begin inc(final); a[final] := 6; end;
        '7': begin inc(final); a[final] := 7; end;
        '8': begin inc(final); a[final] := 8; end;
        '9': begin inc(final); a[final] := 9; end;
      end;
    end;

    start := 1;

    while start <> final do
    begin
      if a[final] mod 2 = 0 then
      begin
        div2;
        inc(rez);
      end
      else
      begin
        nr := a[final-1]*10 + a[final];
        if (nr-1) mod 4 = 0 then
        begin
          decrementare;
          div2;
          rez := rez + 2;
        end
        else
        begin
          incrementare;
          div2;
          rez := rez + 2;
        end;
      end;
    end;

    nr := a[final];
    case nr of
    1:  writeln(rez+1);
    2:  writeln(rez+2);
    3:  writeln(rez+3);
    4:  writeln(rez+3);
    5:  writeln(rez+4);
    6:  writeln(rez+4);
    7:  writeln(rez+5);
    8:  writeln(rez+4);
    9:  writeln(rez+5);
  end;

  end;


  close(input);
  close(output);
end.
