const t=4;
var ti:longint;
    p,i,v:longint;
    nr:array[0..2]of longint;
    x:int64;
    ok:boolean;

begin
  assign(input,'btree.in'); reset(input);
  assign(output,'btree.out'); rewrite(output);

  read(p);
  for ti := 1 to t do
  begin
    read(x); nr[1] := 0; nr[2] := 0;
    while x <> 0 do
    begin

      v := x mod p; x := x div p;
      if v < 3 then inc(nr[v]) else nr[1] := 1000;
    end;

    if nr[2] = 0 then
      if nr[1] = 2 then ok := true else ok := false
    else
      if nr[1] <= 1 then ok := true else ok := false;

    if nr[1] > 2 then ok := false;

    if ok then write('1 ') else write('0 ');
      //writeln(nr[1],' ',nr[2]);

  end;



  close(input);
  close(output);
end.
