var i:longint;
    v:array[0..50]of longint;
    num,k,val,maxx,l,r,m:int64;

procedure Divizori();inline;
var i:longint;
    h,n:int64;
begin
  h := trunc(sqrt(num))+1; n := num;
  v[0] := 0;
  for i := 2 to h do
    if n mod i = 0 then
    begin
      inc(v[0]);
      v[v[0]] := i;
      while n mod i = 0 do n := n div i;
    end;
  if n > 1 then begin inc(v[0]); v[v[0]] := n; end;
end;

procedure Rezolva(pas:longint;prod:int64;sel:longint);
begin
  if pas < v[0] then
  begin
    Rezolva(pas+1,prod,sel);
    Rezolva(pas+1,prod*v[pas+1],sel+1);
  end
  else
  begin
    if sel > 0 then
    begin
      if (sel and 1)=0 then
        prod := -(maxx div prod)
      else
        prod := maxx div prod;

      val := val + prod;
    end;
  end;

end;

function nr_prim(max:int64):int64;
begin
  val := 0; maxx := max;
  Rezolva(0,1,0);
  nr_prim := max - val;
end;

begin
  assign(input,'frac.in'); reset(input);
  assign(output,'frac.out'); rewrite(output);

  readln(num,k);
  Divizori();

  l := 1; r := 1 shl 61;

  repeat
    m := (l+r)div 2;
    if k <= nr_prim(m) then
      r := m-1
    else
      l := m+1;
  until l > r;

  writeln(l);


  close(input);
  close(output);
end.