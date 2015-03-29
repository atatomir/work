uses sysutils;
const nr=276997;
var x:int64;
    i,q,r:longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'dtcsu.in'); reset(input);
  assign(output,'dtcsu.out'); rewrite(output);
  settextbuf(input,bufin);

  for i := 1 to nr do readln();
  readln(q);  r := 0;
  for i := 1 to q do
  begin
    readln(x);
    while x mod 2 <> 0 do x := x div 2;
    while x mod 3 <> 0 do x := x div 3;
    while x mod 5 <> 0 do x := x div 5;
    while x mod 7 <> 0 do x := x div 7;

    if x = 1 then inc(r);
  end;

  write(r);

  close(input);
  close(output);
end.