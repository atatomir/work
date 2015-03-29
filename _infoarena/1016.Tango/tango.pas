const modd=999983;
var n,i,j,k,x:longint;
    r:int64;
    v:array[0..8]of longint;
    a:array[0..100001]of longint;
    bufin:array[1..65000]of byte;

procedure Calcul;
var m:int64;
begin
  r := 1; k := k div 8; m := v[8];

  while k > 0 do
  begin
    if k and 1 = 1 then r := (r * m)mod modd;
    m := (m * m)mod modd;
    k := k shr 1;
  end;

end;


begin
  assign(input,'tango.in'); reset(input);
  assign(output,'tango.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,k);
  for i := 1 to n do read(a[i]);
  v[0] := 1;

  for i := 1 to 8 do
  begin
    v[i] := 0;

    for j := 1 to n do
    begin
      x := i - a[j];
      if x >= 0 then  v[i] := (v[i] + v[x])mod modd;
    end;

  end;

  Calcul;

  writeln(r);


  close(input);
  close(output);
end.
