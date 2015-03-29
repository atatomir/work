const max=1000005;
var t,ti,i:longint;
    ciur:array[0..max+5]of boolean;
    v,vl:array[0..100000]of longint;
    a,b,sum,h:int64;
    bufin,bufout:array[1..65000]of byte;

procedure do_ciur;
var i,h,t,j:longint;
begin
  for i := 2 to max do ciur[i] := true;
  for i := 2 to max do
    if ciur[i] then
    begin
      t := max div i;
      for j := i to t do ciur[i*j] := false;
    end;
end;

procedure Rezolva(pas:longint;prod:int64;sel:longint);
var val:int64;
begin
  if pas <= v[0] then
  begin
    Rezolva(pas+1,prod,sel);
    Rezolva(pas+1,prod*v[pas],sel+1);
  end
  else
  begin
    if sel > 0 then
    begin
      if sel mod 2 = 1 then
        val := a div prod
      else
        val := -(a div prod);

      sum := sum + val;
    end;
  end;

end;

begin
  assign(input,'pinex.in'); reset(input);
  assign(output,'pinex.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  do_ciur();
  vl[0] := 0;
  for i := 2 to max do
    if ciur[i] then
    begin
      inc(vl[0]);
      vl[vl[0]] := i;
    end;


  readln(t);
  for ti := 1 to t do
  begin
    readln(a,b); sum := 0;
    v[0] := 0;
    for i := 1 to vl[0] do
    begin
      if b mod vl[i] = 0 then
      begin
        inc(v[0]);
        v[v[0]] := vl[i];

        while b mod vl[i] = 0 do b := b div vl[i];
      end;
    end;
    if b <> 1 then
    begin
      inc(v[0]); v[v[0]] := b;
    end;

    Rezolva(1,1,0);

    writeln(a-sum);

  end;

  close(input);
  close(output);
end.
