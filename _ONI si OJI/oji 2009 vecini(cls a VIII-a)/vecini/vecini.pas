var n,m,k,i,j,x,y,max,imax,val:longint;
    a,v:array[0..1001,0..1001]of byte;
    bufin:array[1..65000]of byte;

function invert(x,y:longint):longint;
begin
  invert := 8;

  if (i = 1)or(i = n) then  invert := invert - 3;
  if (j = 1)or(j = m) then  invert := invert - 3;
  if ((i = 1)and(j = 1)) or
     ((i = 1)and(j = m)) or
     ((i = n)and(j = 1)) or
     ((i = n)and(j = m)) then inc(invert);

end;

begin
  assign(input,'vecini.in'); reset(input);
  assign(output,'vecini.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m,k);
  for i := 0 to n+1 do
    for j := 0 to m+1 do
    begin
      a[i,j] := 0;
      v[i,j] := 0;
    end;

  for i := 1 to k do
  begin
    readln(x,y); inc(v[x,y]);
    inc(a[x-1,y]);
    inc(a[x,y-1]);
    inc(a[x+1,y]);
    inc(a[x,y+1]);
    inc(a[x-1,y-1]);
    inc(a[x+1,y+1]);
    inc(a[x-1,y+1]);
    inc(a[x+1,y-1]);
  end;

  max := -5; imax := -5;
  for i := 1 to n do
    for j := 1 to m do
    begin
      val := a[i,j];
      if v[i,j] = 0 then val := invert(i,j)-val;

      if val > max then
      begin
        max := val;
        imax := 1;
      end
      else
      if val = max then
        inc(imax);
    end;

  writeln(max,' ',imax);

  close(input);
  close(output);
end.
