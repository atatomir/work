const max = 95;
var t,ti,r,p,i:longint;  gasit:boolean;
    rs:array[0..100]of byte; ri:longint;
    ip:array[0..100]of byte; pi:longint;
    nr:array[0..100]of byte; nri:longint;

function verif:boolean;
var i:longint;
    ok:boolean;
begin
  ok := true;
  for i := 1 to nri do
    if (nr[i] <> 2) and (nr[i] <> 3) and (nr[i] <> 5) and (nr[i] <> 7) then
    begin
      ok := false;
      break;
    end;
  verif := ok;
end;

procedure add;
var i:longint;
begin
  nr[nri+1] := 0;
  for i := 1 to max do
  begin
    nr[i] := nr[i] + ip[i];
    nr[i+1] := nr[i+1] +(nr[i] div 10);
    nr[i] := nr[i] mod 10;
  end;
  for i := nri+1 to max do
    if nr[i] <> 0 then inc(nri);
end;

begin
  assign(input,'cifre4.in'); reset(input);
  assign(output,'cifre4.out'); rewrite(output);

  readln(t); gasit := false;
  for ti := 1 to t do
  begin
    readln(r,p);
    ri := 0; pi := 0; nri := 0;
    while r <> 0 do
    begin
      inc(ri);
      rs[ri] := r mod 10; nr[ri] := r mod 10;
      r := r div 10;
    end;
    while p <> 0 do
    begin
      inc(pi);
      ip[pi] := p mod 10;
      p := p div 10;
    end;
    nri := ri;
    for i := pi+1 to max do ip[i] := 0;
    for i := nri+1 to max do nr[i] := 0;

    while nri <= max do
    begin
      if not verif then
        add
      else
      begin
        gasit := true;
        break;
      end;
    end;

    if not gasit then writeln('-1') else
    begin
      for i := nri downto 1 do write(nr[i]);
      writeln();
    end;
  end;


  close(input);
  close(output);
end.