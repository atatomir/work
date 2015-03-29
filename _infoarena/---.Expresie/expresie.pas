var n,i,sum:longint;
    a:array[0..1005]of longint;
    max:array[1..3]of int64;
    maxi:array[1..3]of longint;
    v1,v2,v3,vh,v:int64;
    bufin:array[1..65000]of byte;

function near(x1,x2:longint):boolean;
var y1,y2:longint;
begin
  near := false;
  y1 := x1 + 1; y2 := x2+1;

  if (y1 = x2) or (y2 = x1) then
    near := true;

end;

begin
  assign(input,'expresie.in'); reset(input);
  assign(output,'expresie.out'); rewrite(output);
  settextbuf(input,bufin);
 
 readln(n); sum := 0;
  for i := 1 to n do
  begin
    readln(a[i]);
    sum := sum + a[i];
  end;

  max[1] := -5; max[2] := -5; max[3] := -5;

  for i := 1 to n-1 do
  begin
    v1 := a[i]; v2 := a[i+1];
    v1 := v1*v2 - v1 - v2;

    if v1 > max[1] then
    begin
      max[3] := max[2]; maxi[3] := maxi[2];
      max[2] := max[1]; maxi[2] := maxi[1];
      max[1] := v1;     maxi[1] := i;
    end
    else
    if v1 > max[2] then
    begin
      max[3] := max[2]; maxi[3] := maxi[2];
      max[2] := v1;     maxi[2] := i;
    end
    else
    if v1 > max[3] then
    begin
      max[3] := v1;     maxi[3] := i;
    end;
  end;

  if not near(maxi[1],maxi[2]) then
    v := max[1] + max[2]
  else
  if not near(maxi[1],maxi[3]) then
    v := max[1] + max[3]
  else
    v := max[2] + max[3];

  for i := 1 to n-2 do
  begin
    v1 := a[i]; v2 := a[i+1]; v3 := a[i+2];
    vh := v1*v2*v3 - v1 - v2 - v3;
    if vh > v then v := vh;
  end;

  writeln(sum+v);


  close(input);
  close(output);
end.
