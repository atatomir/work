var t,ti:longint;
    n,p,k,i,h,x,h2:longint;
    a:array[0..15001]of longint;
    ciur:array[0..30001]of boolean;
    bufin:array[1..65000]of byte;

procedure Do_ciur;
var i,j:longint;
    h,h2:longint;
begin
  for i := 0 to 30001 do ciur[i] := true;

  h := trunc(sqrt(30000))+1;
  for i := 2 to h do
  begin
    if ciur[i] = true then
    begin
      h2 := 30000 div i;
      for j := 2 to h2 do
        ciur[i*j] := false;
    end;
  end;

end;

function prim(x:longint):boolean;
begin
  if x = 1 then
    prim := false
  else
  begin
    while x mod p = 0 do x := x div p;
    prim := ciur[x];
  end;
end;

begin
  assign(input,'secvente1.in'); reset(input);
  assign(output,'secvente1.out'); rewrite(output);
  settextbuf(input,bufin);

  Do_ciur;

  readln(t);
  for ti := 1 to t do
  begin
    readln(n,p,k);
    h := 0;
    for i := 1 to n do
    begin
      readln(x);
      if prim(x) then
      begin
        inc(h);
        a[h] := i;
      end;
    end;

    h2 := h - k +1 ;
    if h2 <=0 then
      writeln(0)
    else
    begin
      writeln(h2);
      for i := 1 to h2 do
        writeln(a[i],' ',a[i+k-1]);
    end;

  end;


  close(input);
  close(output);
end.
