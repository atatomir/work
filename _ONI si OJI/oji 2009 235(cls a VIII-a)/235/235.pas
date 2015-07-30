var n,i,t,x,secv,p:longint;
    a:array[0..500001]of longint;
    bufin:array[1..65000]of byte;

function verif(p,x:longint):boolean;
begin
  while x mod p = 0 do x := x div p;
  if x = 1 then
    verif := true
  else
    verif := false;
end;

begin
  assign(input,'235.in'); reset(input);
  assign(output,'235.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); t := 0;  a[0] := 0;
  for i := 1 to n do
  begin
    readln(x);
    if x <> 1 then
    begin
      if x mod 3 = 0 then
      begin
        if verif(3,x) then
        begin
          inc(t);
          a[t] := a[t-1]-1;
        end;
      end
      else
      if x mod 5 = 0 then
      begin
        if verif(5,x) then
        begin
          inc(t);
          a[t] := a[t-1]+1;
        end;
      end;
    end;
  end;

  writeln(t); secv := 0;

  for i := 1 to t-1 do
  begin
    p := 1;
    while i+ p*2 - 1 <= t do
    begin
      p := p*2;
      if a[i-1] = a[i+p-1] then inc(secv);
    end;


  end;

  writeln(secv);

  close(input);
  close(output);
end.
