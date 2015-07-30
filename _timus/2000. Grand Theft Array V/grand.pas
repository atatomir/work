var n,i,f1,f2,t:longint;
    a:array[1..100001]of longint;
    x1,x2:longint;
    v1,v2:int64;
    intors:boolean;
begin
  readln(n);
  for i := 1 to n do read(a[i]);
  readln();
  readln(x1,x2);
  if x1 > x2 then
  begin
    t := x1;
    x1 := x2;
    x2 := t;
    intors := true;
  end else intors := false;

  v1 := 0; v2 := 0;

  t := x2-x1-1;   if t < 0 then t := 0;

  if t mod 2 = 0 then
  begin
    f1 := x1 + t div 2;
    f2 := f1 + 1;
  end
  else
  begin
    f1 := x1 + t div 2;
    f2 := f1 + 2;
  end;

  for i := 1 to f1 do v1 := v1 + a[i];
  for i := f2 to n do v2 := v2 + a[i];

  if f2-f1 > 1 then
  begin
    if not intors then
      v1 := v1 + a[f1+1]
    else
      v2 := v2 + a[f1+1];
  end;

  if x1=x2 then
  begin
    if v1 < v2 then begin t:=v1;v1:=v2;v2:=t; end;
    v1 := v1 + a[x1];
    v2 := v2 - a[x1];
  end;

  if intors then write(v2,' ',v1) else write(v1,' ',v2);
end.
