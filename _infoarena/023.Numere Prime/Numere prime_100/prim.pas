const n=2000005;
var ciur:array[1..n]of boolean;
    i,j,h,h2,k:longint;
    v:int64;

begin
  assign(input,'prim.in'); reset(input);
  assign(output,'prim.out'); rewrite(output);

  readln(k);
  for i := 2 to n do ciur[i] := true;

  h := trunc(sqrt(n)) + 1;
  for i := 2 to n do
  begin
    if ciur[i] then
    begin
      dec(k);
      if k = -1 then
      begin
        v := i; v := v*v;
        writeln(v);
        close(input);
        close(output);
        exit;
      end;

      h2 := n div i;
      for j := i to h2 do ciur[i*j] := false;

    end;
  end;

end.
